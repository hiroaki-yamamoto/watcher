#include <QVector>
#include <QtDebug>
#include <QString>
#include <QtWidgets/QMessageBox>

#include <loader/board.h>
#include <loader/topic.h>

#include "boardtabcontents.h"
namespace ui{
    BoardTabContents::BoardTabContents(plugin::board *board, QObject *parent):QObject(parent){
        this->_board=board;
        connect(this->_board,SIGNAL(get_topics_finished(QVector<plugin::topic*>)),
                SLOT(get_topics_finished(QVector<plugin::topic*>)));
        connect(this->_board,SIGNAL(get_topics_failed(QNetworkReply::NetworkError,QString)),
                SLOT(get_topics_failed(QNetworkReply::NetworkError,QString)));
        this->_board->get_topics();
    }
    void BoardTabContents::get_topics_finished(const QVector<plugin::topic *> &topics){
        for(plugin::topic *topic:topics){
            qDebug()<<"Topic Name:"<<topic->title();
            qDebug()<<"    Author:"<<topic->author();
            qDebug()<<"     Desc.:"<<topic->description();
            qDebug()<<"      UUID:"<<topic->identifier().toString();
        }
    }

    void BoardTabContents::get_topics_failed(const QNetworkReply::NetworkError err,const QString &err_str){
        QString err_msg=tr("Getting Topics Failed:%1\n    UUID:%2").arg(err_str,this->_board->identifier().toString());
        QMessageBox::critical(nullptr,tr("Getting Topics Failed."),err_msg);
        qWarning()<<err_msg;
    }
}
