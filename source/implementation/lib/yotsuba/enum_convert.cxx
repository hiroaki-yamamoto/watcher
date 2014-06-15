#include "enum_convert.h"
namespace yotsuba {
    QString convert_qjsonvalue_type_to_qstring(const QJsonValue::Type &type) {
        switch (type) {
            case QJsonValue::Null:
                return "Null";
            case QJsonValue::Bool:
                return "Bool";
            case QJsonValue::Double:
                return "Double";
            case QJsonValue::String:
                return "String";
            case QJsonValue::Array:
                return "Array";
            case QJsonValue::Object:
                return "Object";
            case QJsonValue::Undefined:
                return "Undefined";
            default:
                return QString::number((int)type, 16);
        }
    }
}
