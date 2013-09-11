#include <QVector>
#include <QtDebug>
#include <QString>
#include <QtQuick/QQuickItem>
#include <QtWidgets/QMessageBox>

#include <loader/board.h>

#include "boardtabcontents.h"
namespace ui{
    BoardTabContents::BoardTabContents(const QString &root_title, const QUuid &root_uuid, TabWindowBase *parent):
        TabContentsBase(root_title,root_uuid,parent){
        /*
        this->_board=board;
        connect(this->_board,SIGNAL(get_topics_finished(QVector<plugin::topic*>)),
                SLOT(_get_topics_finished(QVector<plugin::topic*>)));
        connect(this->_board,SIGNAL(get_topics_failed(QNetworkReply::NetworkError,QString)),
                SLOT(_get_topics_failed(QNetworkReply::NetworkError,QString)));
        this->_board->get_topics();
        */
    }
    QQuickItem *BoardTabContents::addTab(const QString &title, const QUuid &uuid){
        QVariant variant;
        if(!QMetaObject::invokeMethod(this->_tabcontents,"addTab",Q_RETURN_ARG(QVariant,variant),
                                      Q_ARG(QVariant,QVariant(title)),Q_ARG(QVariant,QVariant(uuid.toString())))){
            qWarning()<<"("<<this->objectName()<<"):Adding Tab failed:{title:"<<title<<",uuid:"<<uuid.toString()<<"}";
            return nullptr;
        }else return variant.value<QQuickItem *>();
    }

    /*
    void BoardTabContents::_get_topics_finished(const QVector<plugin::topic *> &topics){
        for(plugin::topic *topic:topics){
            qDebug()<<"Topic Name:"<<topic->title();
            qDebug()<<"    Author:"<<topic->author();
            qDebug()<<"     Desc.:"<<topic->description();
            qDebug()<<"      UUID:"<<topic->identifier().toString();
        }
    }

    void BoardTabContents::_get_topics_failed(const QNetworkReply::NetworkError err,const QString &err_str){
        QString err_msg=tr("Getting Topics Failed:%1\n    UUID:%2").arg(err_str,this->_board->identifier().toString());
        QMessageBox::critical(nullptr,tr("Getting Topics Failed."),err_msg);
        qWarning()<<err_msg;
    }
    */
}
