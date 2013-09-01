#include <QtQuick/QQuickItem>
#include <QtDebug>
#include <QPair>
#include <QUuid>
#include "roottabcontents.h"
#include "rootwindow.h"

namespace ui{
    RootTabContents *RootWindow::_getCurrentTabContent(){
        QQuickItem *currentTab=this->rootObject()->property("currentSelectedTabContent").value<QQuickItem *>();
        QUuid tab_uuid=QUuid(currentTab->property("uuid").toString());
        QString tab_title=currentTab->property("title").toString();
        QPair<QString,QUuid> tab_key=qMakePair(tab_title,tab_uuid);
        if(!this->_tabcontents.contains(tab_key)){
            qDebug()<<"("<<this->objectName()<<": TabContent Named:"<<tab_title<<" couldn't be found.";
            return nullptr;
        }else return this->_tabcontents[tab_key];
    }
}
