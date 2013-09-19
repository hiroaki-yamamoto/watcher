#include <QtDebug>
#include <logging/logging.h>
#include <loader/response.h>

#include "topic.h"
namespace test{
    topic::topic(std::mt19937 *mt, const QString &title, const QString &author, const QUuid &id,const QUrl &topicURL, QObject *parent):plugin::topic(parent){
        if(mt==nullptr){
            qWarning()<<this<<"mt must not be null."<<endl;
        }
        this->_mt=mt;
        this->setTitle(title);
        this->setAuthor(author);
        this->setIdentifier(id);
        this->_topicURL=topicURL;
    }
    bool topic::readonly() const{return true;}

    const QUrl &topic::topic_url() const{return this->_topicURL;}
    void topic::get_responses(){
        
    }
    void topic::post(const plugin::response &response){
        
    }
}
