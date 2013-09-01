#include <QtDebug>
#include <QObject>
#include <QString>
#include <QUrl>
#include "error.h"
namespace yotsuba{
    QString generate_invalid_type(const QString &obj_name,const QString &expect_type){
        return QObject::tr("The type of \"%1\" must be %2.").arg(obj_name,expect_type);
    }
    QString generate_invalid_document(const QUrl &fetched_url, const QByteArray &data){
        qDebug()<<"URL:"<<fetched_url.toString();
        qDebug()<<"Data:"<<data;
        return QObject::tr("The data is invalid.");
    }
    QString generate_key_not_found(const QString &key_name){return QObject::tr("Key %1 couldn't be found.").arg(key_name);}
    QString generate_required_attribute_invalid(const QString &attribute_name){
        return QObject::tr("Required attribute \"%1\" is invalid type.(i.e. null or unknown type.)").arg(attribute_name);
    }
    //QString generate_image_request_error(const QUrl &url){return QObject::tr("Image: %1 couldn't be loaded.",url.toString());}
}
