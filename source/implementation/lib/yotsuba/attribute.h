#pragma once
#include <QJsonValue>
template <class S,class T> class QPair;
template <class T> class QVector;
class QRegExp;
class QString;
namespace yotsuba{
    extern const QVector< QPair<QString,QJsonValue::Type> > required_attributes;
    extern const QRegExp supported_image_extension;
    extern const QRegExp supported_url_protocol;
}
