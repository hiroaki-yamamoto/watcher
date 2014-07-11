#include "setting_loader.h"
#include "setting_default.h"
#include <QtDebug>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QByteArray>
#include <property_storage.h>
#include <logging/logging.h>
using namespace logging;
namespace loader {
    setting_loader::setting_loader(const QString &file, const int element_size,
                                   const QString &objName) {
        this->_storage = new storage::property_storage(element_size, objName);
        this->_default = new default_value::setting_default();
        this->_file = file;
    }
    setting_loader::~setting_loader() {
        delete this->_storage;
        delete this->_default;
    }

    storage::property_storage &setting_loader::storage() const {
        return (*this->_storage);
    }
    QString setting_loader::filePath() const { return this->_file; }
    bool setting_loader::read() {
        QFile setting_in(this->_file);
        setting_in.open(QIODevice::ReadOnly);
        bool success = false;
        if (setting_in.error() != QFileDevice::NoError) {
            qWarning() << this
                       << "Setting file couldn't be read:" << this->_file;
        } else {
            this->_storage->fromJsonDocument(
                QJsonDocument::fromJson(setting_in.readAll()));
            qDebug() << this << "Read setting file:" << this->_file;
            success = true;
        }
        setting_in.close();
        this->_storage->differencial_copy(*this->_default);
        return success;
    }
    bool setting_loader::write() {
        QFileInfo fileinfo(this->_file);
        QDir &&dir = fileinfo.dir();
        if (!dir.exists()) {
            dir.cdUp();
            dir.mkpath(fileinfo.absolutePath());
        }
        QFile setting_out(this->_file);
        setting_out.open(QIODevice::WriteOnly | QIODevice::Truncate);
        setting_out.write(
            ((*this->_storage) - (*this->_default)).toJsonDocument().toJson());
        setting_out.close();
        qDebug() << this << "Wrote setting to:" << this->_file;
        return true;
    }
}
