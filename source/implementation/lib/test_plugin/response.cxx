#include "response.h"
namespace test{
    response::response(const QString &title, const QString &body, const QString &author, const QString &email, 
                       const QDateTime &creation_date, const QUrl &res_url, const QUuid &id, QObject *parent):plugin::response(parent){
        this->setTitle(title);
        this->setDescription(body);
        this->setAuthor(author);
        this->setIdentifier(id);
        this->_images=new manager::ImageManager();
        this->_email=email;
        this->_creation_date=creation_date;
        this->_response_url=res_url;
    }
    void response::fetchImage(const QUrl &link_url, const QImage &image){
        QUuid &&uuid=QUuid::createUuidV5(this->identifier(),link_url.toString());
        this->_images->insert(uuid,qMakePair(link_url,image));
    }
    const QString &response::email()            const{return this->_email;}
    const QString &response::body()             const{return this->description();}
    const QDateTime &response::creation_date()  const{return this->_creation_date;}
    const QUrl &response::response_url()        const{return this->_response_url;}
    manager::ImageManager *response::images() const{return this->_images;}
}
