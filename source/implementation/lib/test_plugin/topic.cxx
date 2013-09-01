#include <QtDebug>

#include "topic.h"
namespace test{
    topic::topic(std::mt19937 *mt, const QString &title, const QString &author, const QUuid &id,const QUrl &topicURL, QObject *parent):plugin::topic(parent){
        if(mt==nullptr){
            qWarning()<<"mt must not be null."<<endl;
        }
        this->_mt=mt;
        this->setTitle(title);
        this->setAuthor(author);
        this->setIdentifier(id);
        this->_topicURL=topicURL;
    }
    bool topic::readonly() const{return false;}

    const QUrl &topic::topic_url() const{return this->_topicURL;}
    void topic::get_responses(){
        
    }
}
