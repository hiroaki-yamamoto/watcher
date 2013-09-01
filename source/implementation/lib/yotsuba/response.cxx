#include "response.h"
#include <QString>
#include <QList>
#include <QDateTime>
#include <QHash>
namespace yotsuba{
    response::response(QObject *parent):plugin::response(parent){
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
    const bool response::has_images() const{return this->_has_images;}
    const quint64 response::num_images() const{return this->_images->size();}
    const quint64 response::resID() const{return this->_resID;}
    
    void response::setBody(const QString &body){(*this->_body)=body;}
    void response::setCreationDate(const QDateTime &creation_date){(*this->_creation_date)=creation_date;}
    void response::setResponseUrl(const QUrl &url){(*this->_topic_url)=url;}
    void response::setImages(const QHash<QUrl, QImage> &images){(*this->_images)=images;}
    void response::setHasImages(const bool has_images){this->_has_images=has_images;}
    void response::setResID(const quint64 &resID){this->_resID=resID;}
    void response::setEmail(const QString &email){(*this->_email)=email;}
}
