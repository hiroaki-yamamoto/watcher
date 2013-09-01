#pragma once
#include <QUrl>
#include <QtNetwork/QNetworkRequest>
class QString;
namespace yotsuba{
    QUrl api_domain();
    QUrl board_list_url();
    QUrl topic_list_url(const QString &board_dir);
    QUrl response_list_url(const QString &board_dir,const qulonglong &topicID);
    QUrl image_url(const QString &board_dir,const qulonglong &tim,const QString &ext);
    QNetworkRequest create_request(const QUrl &url);
}
