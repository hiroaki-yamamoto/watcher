#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>
#include <QVector>
#include <QPair>
#include <QtDebug>
#include <QHash>
#include "api_urls.h"
#include "attribute.h"
#include "board.h"
#include "topic.h"
#include "error.h"
#include "enum_convert.h"
#include "trace.h"
namespace yotsuba{
    board::board(std::mt19937 *mt,QHash<QUrl,QDateTime> *last_modified,QNetworkAccessManager *accessManager,QObject *parent):plugin::board(parent){
        if(mt==nullptr){
            qWarning()<<"mt must not be null.";
            this->deleteLater();
            return;
        }
        this->_last_modified=last_modified;
        this->_accessmanager=accessManager;
        this->_mt=mt;
    }

    const QString &board::board_dir() const{return this->_dir;}
    const QUrl &board::board_url() const{return this->_board_url;}
    void board::setBoardURL(const QUrl &url){this->_board_url=url;}
    void board::setBoardDirName(const QString &dir){this->_dir=dir;}
    void board::get_topics(){
        connect(this->_accessmanager,SIGNAL(finished(QNetworkReply*)),SLOT(getDataFinished(QNetworkReply*)));
        this->_accessmanager->get(create_request(topic_list_url(this->_dir)));
    }
    void board::getDataFinished(QNetworkReply *reply){
        traceReply(*reply);
        if(reply->error()!=QNetworkReply::NoError){
            reply->close();
            emit this->get_topics_failed(reply->error(),reply->errorString());
            return;
        }
        this->_last_modified->insert(reply->url(),reply->header(QNetworkRequest::LastModifiedHeader).toDateTime());
        qDebug()<<"Last Modified:"<<this->_last_modified->value(reply->url());
        QByteArray raw_data=reply->readAll();
        reply->close();
        QJsonDocument &&document=QJsonDocument::fromJson(raw_data);
        if(document.isNull()){
            emit this->get_topics_failed(QNetworkReply::UnknownContentError,
                                         generate_invalid_document(reply->url(),raw_data));
            return;
        }
        if(!document.isArray()){
            emit this->get_topics_failed(QNetworkReply::UnknownContentError,
                                         generate_invalid_type("Document","Array"));
            return;
        }
        QJsonArray &&root_array=document.array();
        QVector<plugin::topic *> topics;
        for(const QJsonValue &&page:root_array){
            if(!page.isObject()){
                emit this->get_topics_failed(QNetworkReply::UnknownContentError,
                                             generate_invalid_type("The element of array","Object"));
                return;
            }
            QJsonObject &&el=page.toObject();
            if(!el.contains("threads")){
                emit this->get_topics_failed(QNetworkReply::UnknownContentError,generate_key_not_found("threads"));
                return;
            }
            QJsonValue &&topic_list_value=el["threads"];
            if(!topic_list_value.isArray()){
                emit this->get_topics_failed(QNetworkReply::UnknownContentError,generate_invalid_type("threads","Array."));
                return;
            }
            QJsonArray &&topic_list=topic_list_value.toArray();
            for(QJsonArray::ConstIterator &&topic_ref=topic_list.constBegin();topic_ref<topic_list.constEnd();topic_ref++){
                if(!(*topic_ref).isObject()){
                    emit this->get_topics_failed(QNetworkReply::UnknownContentError,generate_invalid_type("The element of \"threads\"","Object"));
                    return;
                }
                QJsonObject &&topic_obj=(*topic_ref).toObject();
                //Check type of required attribute. (See attirbute.cxx for details.)
                for(const QPair<QString,QJsonValue::Type> &required_attribute:required_attributes){
                    if(!topic_obj.contains(required_attribute.first)){
                        emit this->get_topics_failed(QNetworkReply::UnknownContentError,generate_key_not_found(required_attribute.first));
                        return;
                    }
                    if(topic_obj[required_attribute.first].type()!=required_attribute.second){
                        emit this->get_topics_failed(QNetworkReply::UnknownContentError,
                                                     generate_invalid_type(required_attribute.first,
                                                                           convert_qjsonvalue_type_to_qstring(required_attribute.second)));
                        return;
                    }
                }
                yotsuba::topic *topic=new yotsuba::topic(this->_last_modified,this->_accessmanager,this);
                topic->setTopicID(topic_obj["no"].toDouble());
                topic->setTopicURL(this->board_url().resolved("res/"+QString::number(topic->topicID())));
                topic->setIdentifier(QUuid::createUuidV5(this->identifier(),QString::number(topic->topicID())));
                QString subject=topic_obj["sub"].toString(),name=topic_obj["name"].toString();
                if(subject.isEmpty()) subject="Untitled";
                if(name.isEmpty()) name="Anonymouse";
                topic->setTitle(subject);
                topic->setAuthor(name);
                if(topic_obj.contains("com")&&topic_obj["com"].isString())
                    topic->setDescription(topic_obj["com"].toString());
                topics<<topic;
            }
        }
        emit this->get_topics_finished(topics);
        this->_accessmanager->disconnect();
    }
}
