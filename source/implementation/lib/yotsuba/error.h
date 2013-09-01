#pragma once
#include <QString>
class QByteArray;
class QUrl;
namespace yotsuba{
    QString generate_invalid_type(const QString &obj_name,const QString &expect_type);
    QString generate_invalid_document(const QUrl &fetched_url,const QByteArray &data);
    QString generate_key_not_found(const QString &key_name);
    QString generate_required_attribute_invalid(const QString &attribute_name);
    //QString generate_image_request_error(const QUrl &url);
}
