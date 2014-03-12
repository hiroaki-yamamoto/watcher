#include "responsewindow.h"
#include "responsetabcontents.h"
#include "tabcontents_base.h"
#include "responseview.h"
#include "responsepanel.h"
#include <QtQuick/QQuickItem>
#include <QtWidgets/QMessageBox>
#include <QString>
#include <QLatin1String>
#include <QDateTime>
#include <QUrl>
#include <QPair>
#include <logging/logging.h>

#include <loader/response.h>
#include <loader/topic.h>

#include <manager/imagemanager.h>
#include <manager/pixelmanager.h>


namespace ui{
    ResponseView::ResponseView(plugin::topic *topic, TabContentsBase *parent):
        TabContentsBase(topic->title(),topic->identifier(),parent){
        this->_topic=topic;
        connect(this->_topic,SIGNAL(get_responses_finished(QVector<plugin::response*>)),
                      SLOT(responseLoaded(QVector<plugin::response*>)));
        connect(this->_topic,SIGNAL(get_responses_failed(QNetworkReply::NetworkError,QString)),
                      SLOT(responseFetchingFailed(QNetworkReply::NetworkError,QString)));
        if(this->_tabcontents->property("hasAnimation").toBool()){
            connect(this->_tabcontents,SIGNAL(hideAnimationCompleted()),this->_topic,SLOT(get_responses()));
            if(!QMetaObject::invokeMethod(this->_tabcontents,"startHideAnimation")){
                this->_tabcontents->disconnect(SIGNAL(hideAnimationCompleted()),this->_topic,SLOT(get_responses()));
                this->_topic->get_responses();
            }
        }else this->_topic->get_responses();
        this->_tabcontents->setProperty("topicURL",QVariant(topic->topic_url().toString()));
    }
    QQuickItem *ResponseView::addTab(const QString &title, const QUuid &uuid){
        Q_UNUSED(title)
        Q_UNUSED(uuid)
        return new QQuickItem(this->_tabcontents);
    }
    void ResponseView::reload(){
        if(this->_tabcontents->property("hasAnimation").toBool()){
            connect(this->_tabcontents,SIGNAL(hideAnimationCompleted()),this->_topic,SLOT(get_responses()));
            if(!QMetaObject::invokeMethod(this->_tabcontents,"startHideAnimation")){
                this->_tabcontents->disconnect(SIGNAL(hideAnimationCompleted()),this->_topic,SLOT(get_responses()));
                this->_topic->get_responses();
            }
        }else this->_topic->get_responses();
    }
    
    void ResponseView::responseLoaded(const QVector<plugin::response *> &responses){
        plugin::topic *topic=qobject_cast<decltype(topic)>(this->sender());
        if(this->_tabcontents->property("hasAnimation").toBool()){
            this->_tabcontents->disconnect(SIGNAL(hideAnimationCompleted()),topic,SLOT(get_responses()));
        }
        for(auto &panel:this->_childrenTabs.values()) panel->deleteLater();
        this->_childrenTabs.clear();
        for(plugin::response *response:responses) this->addItem(response);
        if(this->_tabcontents->property("hasAnimation").toBool()) QMetaObject::invokeMethod(this->_tabcontents,"startShowAnimation");
    }
    
    void ResponseView::responseFetchingFailed(const QNetworkReply::NetworkError err, const QString &err_str){
        Q_UNUSED(err)
        QMessageBox::warning(nullptr,tr("Response Fetching failed"),
                             tr(
                                 "<p>Fetching responses failed. Please make sure the response page exists exactly.</p>"
                                 "<p>Error message:%1</p>"
                                 ).arg(err_str));
    }

    void ResponseView::addItem(plugin::response *res){
        this->_childrenItems[qMakePair(res->title(),res->identifier())]=new ResponsePanel(res,this);
    }
    
    QQuickItem *ResponseView::_addItem(const QString &title, const QString &author, const QString &email, 
                                       const QDateTime &post_time, const QString &body, const QUuid &uuid,
                                       const QUrl &responseURL,manager::ImageManager *images){
        ResponseTabContents *parentTabContents=qobject_cast<ResponseTabContents *>(this->_parentTab);
        ResponseWindow *parentWindow=parentTabContents->parentWindow();
        QQmlEngine *windowEngine=parentWindow->engine();
        /*
        Image Information object format:
        [
            {
                "LinkURI":"http://example.com",
                "SourceURI":"image://ResponseUUID/ImageUUID
                "UUID":"ImageUUID"
            }
        ]
        */
        //TODO: Add image provider
        windowEngine->addImageProvider(uuid.toString().replace("{","").replace("}",""),images);
        
        QVariantList imageInfoList;
        for(QUuid &imageUUID:images->uniqueKeys()){
            auto &&value=images->value(imageUUID);
            QVariantMap imageInfo;
            imageInfo["LinkURI"]=value.first.toString();
            imageInfo["SourceURI"]=QString("image://%1/%2").arg(uuid.toString().replace("{","").replace("}",""),
                                                        imageUUID.toString().replace("{","").replace("}",""));
            imageInfo["UUID"]=imageUUID.toString();
            imageInfoList<<imageInfo;
        }
        
        QVariant invoke_result;
        bool succeeded=QMetaObject::invokeMethod(this->_tabcontents,"addResponse",
                                                 Q_RETURN_ARG(QVariant,invoke_result),Q_ARG(QVariant,QVariant(title)),
                                                 Q_ARG(QVariant,QVariant(author)),Q_ARG(QVariant,QVariant(email)),
                                                 Q_ARG(QVariant,QVariant(post_time.toString())),Q_ARG(QVariant,QVariant(body)),
                                                 Q_ARG(QVariant,QVariant(uuid)),Q_ARG(QVariant,responseURL),
                                                 Q_ARG(QVariant,imageInfoList));
        if(!succeeded){
            qWarning()<<this<<"Calling _addItem failed. Here is the Info.";
            qWarning()<<this<<"    title:"<<title;
            qWarning()<<this<<"    uuid:"<<uuid;
            qWarning()<<this<<"    responseURL:"<<responseURL;
        }
        return invoke_result.value<QQuickItem *>();
    }
}
