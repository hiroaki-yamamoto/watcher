#include <QVariant>
#include <QtQuick/QQuickItem>
#include <QtDebug>
#include "tabwindow_base.h"
namespace ui{
    TabContentsBase *TabWindowBase::_getCurrentTabContents(){
        QQuickItem *currentTab=this->rootObject()->property("currentSelectedTabContent").value<QQuickItem *>();
        if(currentTab==nullptr){
            qDebug()<<"("<<this->objectName()<<": currentSelectedTabContent is null.";
            return nullptr;
        }
        QUuid tab_uuid=QUuid(currentTab->property("uuid").toString());
        QString tab_title=currentTab->property("title").toString();
        QPair<QString,QUuid> tab_key=qMakePair(tab_title,tab_uuid);
        if(!this->_tabcontents.contains(tab_key)){
            qDebug()<<"("<<this->objectName()<<": TabContent Named:"<<tab_title<<" couldn't be found.";
            return nullptr;
        }else return this->_tabcontents[tab_key];
    }
    QQuickItem *TabWindowBase::addTab(const QString &title, const QUuid &uuid){
        QVariant variant;
        if(!QMetaObject::invokeMethod(this->rootObject(),"addTab",Q_RETURN_ARG(QVariant,variant),
                Q_ARG(QVariant,QVariant(title)),Q_ARG(QVariant,QVariant(uuid.toString())))){
            return nullptr;
        }else return variant.value<QQuickItem *>();
    }
}
