#include "attribute.h"
#include <QString>
#include <QPair>
#include <QVector>
#include <QRegExp>
namespace yotsuba{
    const QVector< QPair<QString,QJsonValue::Type> > required_attributes={
            QPair<QString,QJsonValue::Type>("no",QJsonValue::Double),
            QPair<QString,QJsonValue::Type>("resto",QJsonValue::Double),
            QPair<QString,QJsonValue::Type>("now",QJsonValue::String),
            QPair<QString,QJsonValue::Type>("time",QJsonValue::Double),
        };
    const QRegExp supported_image_extension=QRegExp("bmp|gif|jpg|jpe|jfif|jfi|jif|pbm|pgm|ppm|xbm|xpm");
    const QRegExp supported_url_protocol=QRegExp("ftp|http");
}
