#pragma once
#include <QJsonValue>
#include <QString>
namespace yotsuba{
    QString convert_qjsonvalue_type_to_qstring(const QJsonValue::Type &type);
}
