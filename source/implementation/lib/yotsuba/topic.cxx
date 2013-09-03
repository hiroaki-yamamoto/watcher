#include "board.h"
#include "topic.h"
#include "api_urls.h"
#include "error.h"
#include "attribute.h"
#include "enum_convert.h"
#include "response.h"

#include <QtWidgets/QApplication>
#include <QVector>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QAbstractNetworkCache>
#include <QtNetwork/QNetworkReply>
#include <QImage>
#include <QDateTime>
#include <QList>
#include <QHash>
#include <QFileInfo>
#include <QRegExp>

#include <QtDebug>

#include <string>
#include <sstream>

using namespace std;

namespace yotsuba{
    topic::topic(QNetworkAccessManager *accessManager, QObject *parent):plugin::topic(parent){
        this->_accessmanager=accessManager;
    }
    const QUrl &topic::topic_url() const{return this->_url;}
    qulonglong topic::topicID() const{return this->_topicID;}
    bool topic::readonly() const{return true;}
    void topic::setTopicURL(const QUrl &url){this->_url=url;}
    void topic::setTopicID(const qulonglong &topicID){this->_topicID=topicID;}
    void topic::post(const plugin::response &res){}
    void topic::get_responses(){
        connect(this->_accessmanager,SIGNAL(finished(QNetworkReply*)),SLOT(getDataFinished(QNetworkReply*)));
        board *parent=qobject_cast<board *>(this->parent());
        this->_accessmanager->get(create_request(response_list_url(parent->board_dir(),this->_topicID)));
    }
    void topic::getDataFinished(QNetworkReply *reply){
        if(!this->_accessmanager->disconnect(SIGNAL(finished(QNetworkReply*)),this,SLOT(getDataFinished(QNetworkReply*)))){
            qWarning()<<"Yotsuba.Topic:Signal disconnection failed.";
        }
        if(reply->error()!=QNetworkReply::NoError){
            emit this->get_responses_failed(reply->error(),reply->errorString());
            reply->close();
            return;
        }
        QByteArray raw_data=reply->readAll();
        reply->close();
        QJsonDocument &&doc=QJsonDocument::fromJson(raw_data);
        if(doc.isNull()){
            emit this->get_responses_failed(QNetworkReply::UnknownContentError,generate_invalid_document(reply->url(),raw_data));
            return;
        }
        QJsonObject &&root=doc.object();
        if(!root.contains("posts")){
            emit this->get_responses_failed(QNetworkReply::UnknownContentError,generate_key_not_found("posts"));
            return;
        }
        QJsonValue &&posts=root["posts"];
        if(!posts.isArray()){
            emit this->get_responses_failed(QNetworkReply::UnknownContentError,generate_invalid_type("posts","Array"));
            return;
        }
        QJsonArray &&posts_array=posts.toArray();
        QVector<plugin::response *> responses;
        for(const QJsonValue &&post:posts_array){
            if(!post.isObject()){
                emit this->get_responses_failed(QNetworkReply::UnknownContentError,generate_invalid_type("The element in posts","Object"));
                return;
            }
            QJsonObject &&post_object=post.toObject();
            //Check required attribute
            for(const QPair<QString,QJsonValue::Type> &required_attribute:required_attributes){
                if(!post_object.contains(required_attribute.first)){
                    emit this->get_responses_failed(QNetworkReply::UnknownContentError,generate_key_not_found(required_attribute.first));
                    return;
                }
                if(post_object[required_attribute.first].type()!=required_attribute.second){
                    emit this->get_responses_failed(QNetworkReply::UnknownContentError,
                                                    generate_invalid_type(required_attribute.first,
                                                                          convert_qjsonvalue_type_to_qstring(required_attribute.second)));
                    return;
                }
            }
            
            yotsuba::board *parent=qobject_cast<yotsuba::board *>(this->parent());
            yotsuba::response *res=new yotsuba::response(this->_accessmanager,this);
            res->setResID(post_object["no"].toDouble());
            res->setResponseUrl(QUrl(response_list_url(parent->board_dir(),this->topicID())));
            res->setCreationDate(QDateTime::fromTime_t(post_object["time"].toDouble()));
            connect(res,SIGNAL(fetchingImageFailed(QNetworkReply::NetworkError,QUrl,QString)),
                    SIGNAL(get_response_warning(QNetworkReply::NetworkError,QUrl,QString)));
            if(post_object["name"].isString())  res->setAuthor(post_object["name"].toString());
            if(post_object["email"].isString()) res->setAuthor(post_object["email"].toString());
            if(post_object["sub"].isString())   res->setTitle(post_object["sub"].toString());
            
            if(post_object["com"].isString()){
                QString &&body=post_object["com"].toString();
                stringstream stream;
                stream<<body.toStdString();
                QList<QUrl> image_urls;
                while(!stream){
                    string url_candidate;
                    stream>>url_candidate;
                    QUrl url(QString::fromStdString(url_candidate));
                    QFileInfo info(url.path());
                    if(supported_url_protocol.exactMatch(url.scheme())){
                        if(supported_image_extension.exactMatch(info.suffix())){image_urls<<url;}
                        body=body.replace(url.toString(),QString("<a href=\"%1\">%1</a>").arg(url.toString()));
                    }
                }
                for(const QUrl &image_url:image_urls) res->fetchImage(image_url);
                res->setBody(QString("<div id=p%1>%2</div>").arg(QString::number(res->resID()),body));
            }
            if(post_object["filename"].isString()&&post_object["ext"].isString()&&
                    post_object["filedeleted"].toDouble()==0.0f){
                if(!post_object.contains("tim")){
                    emit this->get_responses_failed(QNetworkReply::UnknownContentError,
                                                    generate_key_not_found("tim"));
                    return;
                }
                if(!post_object["tim"].isDouble()){
                    emit this->get_responses_failed(QNetworkReply::UnknownContentError,
                                                    generate_invalid_type("tim","double"));
                    return;
                }
                qulonglong tim=(qulonglong)post_object["tim"].toDouble();
                res->fetchImage(image_url(parent->board_dir(),tim,post_object["ext"].toString()));
            }
            res->setIdentifier(QUuid::createUuidV5(this->identifier(),QString::number(res->resID())));
            responses<<res;
        }
        emit this->get_responses_finished(responses);
    }    
}
