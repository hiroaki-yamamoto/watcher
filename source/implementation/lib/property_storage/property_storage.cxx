#include <QJsonDocument>
#include <QJsonObject>
#include <QtDebug>

#include <algorithm>
#include <stdexcept>
#include <string>
#include <list>

#include "property_storage.h"

#include <logging/logging.h>

using namespace std;
using namespace logging;

namespace storage {
    property_storage::property_storage(const int element_size,
                                       const QString &objName, QObject *parent)
        : QObject(parent) {
        this->setObjectName(objName);
        this->_element_size = element_size;
        qDebug() << "Property storage has been initialized as "
                 << this->objectName();
    }
    property_storage::property_storage(const property_storage &other,
                                       const int element_size,
                                       const QString &objName,
                                       QObject *parent) {
        property_storage(element_size, objName, parent);
        this->__data = other.__data;
        qDebug() << "Property storage has been initialized as "
                 << this->objectName() << " and based on "
                 << other.objectName();
        this->dump();
    }
    void property_storage::fromJsonDocument(const QJsonDocument &document) {
        if(!document.isObject()){
            qWarning()<<"This JSON file seems not to be right syntax";
            return;
        }
        QJsonObject &&obj = document.object();
        this->__data = obj.toVariantMap();
    }
    const int &property_storage::elementSize() const {
        return this->_element_size;
    }
    void property_storage::setElementSize(const int size) {
        this->_element_size = size;
    }

    bool property_storage::readOnly() { return false; }

    void property_storage::set(const QString &key, const QVariant &value) {
        if (this->readOnly()) {
            qDebug() << this << "Readonly";
            return;
        }
        QVariant previous_value = this->__data.value(key);

        if (previous_value != value) {
            qDebug() << this << "Dump Before Adding";
            this->dump();

            this->__data.insertMulti(key, value);
            this->shrink(key);

            qDebug() << this << "Dump After Adding";
            this->dump();
            emit this->propertyChanged(key, previous_value, value);
        }
    }
    QVariant property_storage::get(const QString &key) const {
        return this->__data.value(key);
    }
    QVariant property_storage::operator[](const QString &key) const {
        return this->get(key);
    }
    bool property_storage::exists(const QString &key) const {
        return this->__data.keys().contains(key);
    }
    void property_storage::undo(const QString &key) {
        QVariant previous_value = this->__data.take(key),
                 now = this->__data.value(key);
        emit this->propertyChanged(key, previous_value, now);
    }

    void property_storage::undo() {
        for (auto key : this->__data.keys()) {
            QVariant previous_value = this->__data.take(key),
                     now = this->__data.value(key);
            emit this->propertyChanged(key, previous_value, now);
        }
    }
    bool property_storage::unset(const QString &key) {
        int before_value_size = this->__data.values(key).size(),
            after_value_size = this->__data.remove(key);
        emit this->propertyRemoved(key);
        return (before_value_size == after_value_size);
    }
    void property_storage::clear() {
        this->__data.clear();
        emit this->propertyCleared();
    }
    void property_storage::differencial_copy(const property_storage &setting) {
        if (this->readOnly()) {
            qWarning() << this << "ReadOnly";
            return;
        }
        for (const QString &key : setting.__data.uniqueKeys()) {
            if (!this->exists(key))
                this->__data.insertMulti(key, setting.get(key));
        }
        qDebug() << this
                 << "Differencial Copied from: " << setting.objectName();
        this->dump();
    }
    void property_storage::copy(const QString &key,
                                const QVariantList &values) {
        for (auto &&it = values.cbegin(); it < values.cend(); it++) {
            this->__data.insertMulti(key, *it);
        }
    }

    property_storage property_storage::operator-(
        const property_storage &operandB) const {
        property_storage ret(this->elementSize(),
                             this->objectName() + "::operator-", nullptr);
        for (const QString &opA_key : this->__data.uniqueKeys()) {
            QVariantList &&values_opA = this->__data.values(opA_key);
            if (operandB.exists(opA_key)) {
                QVariantList &&values_opB = operandB.__data.values(opA_key);
                if (values_opA != values_opB) {
                    ret.copy(opA_key, values_opA);
                }
            } else {
                ret.copy(opA_key, values_opA);
            }
        }
        return ret;
    }
    void property_storage::shrink(const QString &key) {
        for (auto &&it = this->__data.end() - 1;
             it != this->__data.begin() &&
                 this->__data.count(key) > this->_element_size;
             it--) {
            if (it.key() == key) {
                qDebug() << this << "Removed:{" << it.key() << ":" << it.value()
                         << "}";
                it = this->__data.erase(it);
            }
        }
        this->dump();
    }

    property_storage &property_storage::operator=(
        const property_storage &operandB) {
        this->__data.clear();
        this->__data = operandB.__data;
        return (*this);
    }
    property_storage &property_storage::operator-=(
        const property_storage &operandB) {
        (*this) = (*this) - operandB;
        return (*this);
    }
    property_storage property_storage::operator+(
        const property_storage &operandB) const {
        property_storage ret(((this->elementSize() > operandB.elementSize())
                                  ? this->elementSize()
                                  : operandB.elementSize()),
                             this->objectName() + "::operator+", nullptr);
        ret = (*this);
        for (const QString &key : operandB.__data.uniqueKeys()) {
            QVariantList &&values_opA = ret.__data.values(key);
            if (ret.exists(key)) {
                QVariantList &&values_opB = operandB.__data.values(key);
                if (values_opA != values_opB) ret.copy(key, values_opB);
            } else {
                ret.copy(key, values_opA);
            }
        }
        return ret;
    }
    property_storage property_storage::operator+=(
        const property_storage &operandB) {
        (*this) = (*this) + operandB;
        return (*this);
    }
    void property_storage::dump() {
        qDebug() << "Property Storage Dump. Object Name:" << this->objectName();
        for (const QString &str : this->__data.uniqueKeys()) {
            qDebug() << "    Name:" << str;
            for (const QVariant &var : this->__data.values(str)) {
                qDebug() << "        Value:" << var;
            }
        }
    }
    QJsonDocument property_storage::toJsonDocument() const{
        qDebug()<<"Converting QJsonDocument.. Name:"<<this->objectName();
        return QJsonDocument(QJsonObject::fromVariantMap(this->__data));
    }
}
