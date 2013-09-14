#include <QVector>
#include <QtQuick/QQuickItem>
#include <QtWidgets/QMessageBox>
#include <QtDebug>
#include <QUrl>

#include <loader/board.h>
#include <loader/topic.h>

#include "topicview.h"

namespace ui{
    TopicView::TopicView(plugin::board *board, TabContentsBase *parent):
        TabContentsBase(board->title(),board->identifier(),parent){
        connect(board,SIGNAL(get_topics_finished(QVector<plugin::topic*>)),
                SLOT(_getTopicsFinished(QVector<plugin::topic*>)));
        connect(board,SIGNAL(get_topics_failed(QNetworkReply::NetworkError,QString)),
                SLOT(_getTopicsFailed(QNetworkReply::NetworkError,QString)));
        board->get_topics();
        this->_tabcontents->setProperty("boardURL",QVariant(board->board_url().toString()));
    }
    void TopicView::addButton(const QString &title, const QString &detail, const QUuid &uuid){
        if(!QMetaObject::invokeMethod(this->_tabcontents,"addButton",
                                  Q_ARG(QVariant,QVariant(title)),
                                  Q_ARG(QVariant,QVariant(detail)),
                                  Q_ARG(QVariant,QVariant(uuid.toString())))){
            qWarning()<<"("<<this->objectName()<<"): Adding a button failed:{title:"<<title<<",detail:"
                     <<detail<<","<<"uuid:"<<uuid<<"}";
        }
    }

    void TopicView::_getTopicsFinished(const QVector<plugin::topic *> &topics){
        for(plugin::topic *topic:topics){
            this->_topics[qMakePair(topic->title(),topic->identifier())]=topic;
            this->addButton(topic->title(),topic->author(),topic->identifier());
        }
    }
    void TopicView::_getTopicsFailed(const QNetworkReply::NetworkError err, const QString &err_str){
        QMessageBox::critical(nullptr,tr("Getting Topics failed"),tr("Getting topics failed:%1\n"
                                                                     "Board Title:%2\n"
                                                                     "UUID:%3\n").arg(err_str,this->title(),this->UUID().toString()));
    }
    void TopicView::_buttonClicked(const QVariant &variant){
        QQuickItem *button=variant.value<decltype(button)>();
        const QUuid id(button->property("uuid").toString());
        const QString &&str=button->property("text").toString();
        const QPair<QString,QUuid> &&key=qMakePair(str,id);
        if(this->_topics[key]){
            emit this->buttonClicked(str,id,this->_topics[key]);
        }else{
            qWarning()<<"("<<this->objectName()<<"): No such a topic:{title:"<<str<<", id:"<<id<<"}";
        }
    }
}
