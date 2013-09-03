#include <QUrl>
#include <QByteArray>
#include <QtNetwork/QNetworkRequest>
#include <QtDebug>
#include <QHash>
#include "api_urls.h"
namespace yotsuba{
    QNetworkRequest create_request(const QUrl &url){
        QNetworkRequest request(url);
        request.setHeader(QNetworkRequest::UserAgentHeader,"Watcher Yotsuba Plugin");
        return request;
    }
    
    QUrl api_domain(){
        QUrl domain_url("http://api.4chan.org/");
        qDebug()<<"4chan API domain URL:"<<domain_url;
        return domain_url;
    }
    QUrl board_list_url(){
        QUrl &&result=api_domain().resolved(QUrl("/boards.json"));
        qDebug()<<"4chan API board list URL:"<<result;
        return result;
    }
    QUrl topic_list_url(const QString &board_dir){
        QUrl &&result=api_domain().resolved(QUrl("/"+board_dir+"/catalog.json"));
        qDebug()<<"4chan API topic list URL:"<<result;
        return result;
    }
    QUrl response_list_url(const QString &board_dir, const qulonglong &topicID){
        QUrl &&result=api_domain().resolved(QUrl("/"+board_dir+"/"+QString::number(topicID)+".json"));
        qDebug()<<"4chan API response list URL:"<<result;
        return result;
    }
    QUrl image_url(const QString &board_dir, const qulonglong &tim, const QString &ext){
        return QUrl(QString("http://images.4chan.org/%1/src/%2.%3").arg(board_dir,QString::number(tim),ext));
    }
}
