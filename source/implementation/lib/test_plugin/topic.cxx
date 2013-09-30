#include <QtDebug>
#include <logging/logging.h>
#include <loader/response.h>

#include "topic.h"
namespace test{
    topic::topic(const QString &title, const QString &author, const QUuid &id,const QUrl &topicURL, QObject *parent):plugin::topic(parent){
        this->setTitle(title);
        this->setAuthor(author);
        this->setIdentifier(id);
        this->_topicURL=topicURL;
    }
    bool topic::readonly() const{return false;}

    const QUrl &topic::topic_url() const{return this->_topicURL;}
    void topic::get_responses(){
        
    }
    void topic::post(){
        
    }
}
