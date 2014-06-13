#include <libserializer/serializer.h>
#include "property_storage.h"
using namespace storage;
serializer &storage::operator<<(serializer &out, const property_storage &data) {
    out << QVariant(data.__data);
    return out;
}

serializer &storage::operator>>(serializer &in, property_storage &data) {
    QVariant value;
    in >> value;
    data.__data = value.toHash();
    return in;
}

serializer &operator<<(serializer &out, const QVariant &data) {
    bool success = false;
    if (data.canConvert(QMetaType::ULongLong)) {
        qulonglong value = data.toULongLong(&success);
        if (success) {
            out << (int)QMetaType::ULongLong << value;
            return out;
        }
    }
    if (data.canConvert(QMetaType::LongLong)) {
        qlonglong value = data.toLongLong(&success);
        if (success) {
            out << (int)QMetaType::LongLong << value;
            return out;
        }
    }
    if (data.canConvert(QMetaType::Double)) {
        double value = data.toDouble(&success);
        if (success) {
            out << (int)QMetaType::Double << value;
            return out;
        }
    }

    if (data.canConvert(QMetaType::QString))
        out << (int)QMetaType::QString << data.toString().toStdString();
    else if (data.canConvert(QMetaType::QVariantList))
        out << (int)QMetaType::QVariantList << data.toList().toStdList();
    else if (data.canConvert(QMetaType::QVariantHash)) {
        QVariantHash hash = data.toHash();
        out << (int)QMetaType::QVariantHash << hash.uniqueKeys().size();
        for (const QString &key : hash.uniqueKeys())
            out << key.toStdString() << hash.values(key).toStdList();
    } else if (data.canConvert(QMetaType::QVariantMap)) {
        QVariantMap mp = data.toMap();
        out << (int)QMetaType::QVariantHash << mp.uniqueKeys().size();
        for (const QString &key : mp.uniqueKeys())
            out << key.toStdString() << mp.values(key).toStdList();
    } else
        throw invalid_argument("The data type is unserializable type.");
    return out;
}

serializer &operator>>(serializer &in, QVariant &data) {
    int type;
    in >> type;
    data.clear();
    switch ((QMetaType::Type)type) {
        case QMetaType::ULongLong: {
            qulonglong value;
            in >> value;
            data.setValue(value);
        } break;
        case QMetaType::LongLong: {
            qlonglong value;
            in >> value;
            data.setValue(value);
        } break;
        case QMetaType::Double: {
            double value;
            in >> value;
            data.setValue(value);
        } break;
        case QMetaType::QString: {
            string str;
            in >> str;
            data.setValue(QString::fromStdString(str));
        } break;
        case QMetaType::QVariantList: {
            list<QVariant> lst;
            in >> lst;
            data.setValue(QVariantList::fromStdList(lst));
        } break;
        case QMetaType::QVariantHash: {
            QVariantHash hash;
            int size;
            in >> size;
            for (int index = 0; index < size; index++) {
                string key;
                list<QVariant> values;
                in >> key >> values;
                for (const QVariant &value : values)
                    hash.insertMulti(QString::fromStdString(key), value);
            }
            data.setValue(hash);
        } break;
        case QMetaType::QVariantMap: {
            QVariantMap mp;
            int size;
            in >> size;
            for (int index = 0; index < size; index++) {
                string key;
                list<QVariant> values;
                in >> key >> values;
                for (const QVariant &value : values)
                    mp.insertMulti(QString::fromStdString(key), value);
            }
            data.setValue(mp);
        } break;
        default:
            throw logic_error("Undeserializable type.");
            break;
    }
    return in;
}
