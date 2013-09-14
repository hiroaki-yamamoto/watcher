#include <QVector>
#include <QtDebug>
#include <QString>
#include <QtQuick/QQuickItem>
#include <QtWidgets/QMessageBox>

#include <loader/board.h>

#include "boardtabcontents.h"
#include "topicview.h"
namespace ui{
    BoardTabContents::BoardTabContents(const QString &title,const QUuid &uuid,TabWindowBase *parent):
        TabContentsBase(title,uuid,parent){}
    void BoardTabContents::addBoard(plugin::board *board){
        const QPair<QString,QUuid> &&key=qMakePair(board->title(),board->identifier());
        if(this->_childrenTabs.contains(key)){
            qWarning()<<"("<<this->objectName()<<"):The TopicView {title:"<<key.first<<
                        ",uuid:"<<key.second.toString()<<"} has already existed.";
        }else{
            this->_childrenTabs[key]=new TopicView(board,this);
        }
    }
}
