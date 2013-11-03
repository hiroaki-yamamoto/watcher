#include "tabcontents_base.h"
#include "responseview.h"
#include "responsepanel.h"
#include <QtQuick/QQuickItem>
#include <QtWidgets/QMessageBox>
#include <QString>
#include <QDateTime>
#include <QUrl>
#include <logging/logging.h>

#include <loader/response.h>
#include <loader/topic.h>


namespace ui{
    ResponseView::ResponseView(plugin::topic *topic, TabContentsBase *parent):QObject(parent){
        this->_item=parent->addTab(topic->title(),topic->identifier());
        connect(topic,SIGNAL(get_responses_finished(QVector<plugin::response*>)),
                      SLOT(responseLoaded(QVector<plugin::response*>)));
        connect(topic,SIGNAL(get_responses_failed(QNetworkReply::NetworkError,QString)),
                      SLOT(responseFetchingFailed(QNetworkReply::NetworkError,QString)));
        topic->get_responses();
    }
    
    void ResponseView::responseLoaded(const QVector<plugin::response *> &responses){
        for(plugin::response *response:responses) this->addItem(response);
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
        this->_panels[res->identifier()]=new ResponsePanel(res,this);
    }
    QQuickItem *ResponseView::_addItem(const QString &title, const QString &author, const QString &email, 
                                       const QDateTime &post_time, const QString &body, const QUuid &uuid,
                                       const QUrl &responseURL){
        QVariant invoke_result;
        bool succeeded=QMetaObject::invokeMethod(this->_item,"addResponse",
                                                 Q_RETURN_ARG(QVariant,invoke_result),Q_ARG(QVariant,QVariant(title)),
                                                 Q_ARG(QVariant,QVariant(author)),Q_ARG(QVariant,QVariant(email)),
                                                 Q_ARG(QVariant,QVariant(post_time.toString())),Q_ARG(QVariant,QVariant(body)),
                                                 Q_ARG(QVariant,QVariant(uuid)),Q_ARG(QVariant,responseURL));
        if(!succeeded){
            qWarning()<<this<<"Calling _addItem failed. Here is the Info.";
            qWarning()<<this<<"    title:"<<title;
            qWarning()<<this<<"    uuid:"<<uuid;
            qWarning()<<this<<"    responseURL:"<<responseURL;
        }
        return invoke_result.value<QQuickItem *>();
    }
}
