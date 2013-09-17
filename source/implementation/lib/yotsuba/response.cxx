#include "api_urls.h"
#include "response.h"
#include <QtDebug>
#include <QString>
#include <QList>
#include <QDateTime>
#include <QHash>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QAbstractNetworkCache>
#include <QtNetwork/QNetworkReply>
namespace yotsuba{
    response::response(QNetworkAccessManager *accessManager, QObject *parent):plugin::response(parent){
        this->_accessManager=accessManager;
        this->_body=new QString();
        this->_creation_date=new QDateTime();
        this->_images=new QHash<QUrl,QImage>();
        this->_email=new QString();
        this->_topic_url=new QUrl();
    }
    response::~response(){
        delete this->_body;
        delete this->_creation_date;
        delete this->_images;
        delete this->_topic_url;
        delete this->_email;
    }
    
    const QString &response::email() const{return *(this->_email);}
    const QString &response::body() const{return *(this->_body);}
    const QDateTime &response::creation_date() const{return *(this->_creation_date);}
    const QUrl &response::response_url() const{return *(this->_topic_url);}
    const QHash<QUrl,QImage> &response::images() const{return *(this->_images);}
    const quint64 response::resID() const{return this->_resID;}
    
    void response::setBody(const QString &body){(*this->_body)=body;}
    void response::setCreationDate(const QDateTime &creation_date){(*this->_creation_date)=creation_date;}
    void response::setResponseUrl(const QUrl &url){(*this->_topic_url)=url;}
    void response::setImages(const QHash<QUrl, QImage> &images){(*this->_images)=images;}
    void response::setResID(const quint64 &resID){this->_resID=resID;}
    void response::setEmail(const QString &email){(*this->_email)=email;}
    void response::fetchImage(const QUrl &url){
        connect(this->_accessManager,SIGNAL(finished(QNetworkReply*)),SLOT(_fetching_image_finished(QNetworkReply*)));
        this->_accessManager->get(create_request(url));
    }
    void response::_fetching_image_finished(QNetworkReply *reply){
        if(!this->_accessManager->disconnect(SIGNAL(finished(QNetworkReply*)),this,SLOT(_fetching_image_finished(QNetworkReply*)))){
            qWarning()<<"Yotsuba.Response.FetchingImage:Signal disconnection failed";
        }
        if(reply->error()!=QNetworkReply::NoError){
            qWarning()<<"Response.FetchImage:Fetching Error";
            qWarning()<<"    ErrorString:"<<reply->errorString();
            emit this->fetchingImageFailed(reply->error(),reply->url(),reply->errorString());
            reply->close();
            return;
        }
        this->_images->insert(reply->url(),QImage::fromData(reply->readAll()));
        reply->close();
    }
}
