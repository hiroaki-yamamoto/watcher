#include <QVariant>
#include <QtQuick/QQuickItem>
#include <QtDebug>
#include "tabwindow_base.h"
#include "tabcontents_base.h"
namespace ui{
    TabWindowBase::TabWindowBase(const QString &title,const QIcon &icon,QMLWindowBase *parent):QMLWindowBase(title,icon,parent){
        connect(this,SIGNAL(loaded()),SLOT(_loaded()));
    }
    void TabWindowBase::_loaded(){
        connect(this->rootObject(),SIGNAL(closeButtonClicked(QVariant,QVariant)),SLOT(_closeButtonClicked(QVariant,QVariant)));
    }
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
    void TabWindowBase::removeTab(const QString &title,const QUuid &uuid){
        const QPair<QString,QUuid> &&key=qMakePair(title,uuid);
        if(this->_tabcontents.contains(key)){
            this->_tabcontents[key]->deleteLater();
            this->_tabcontents.remove(key);
        }else{
            qWarning()<<"("<<this->objectName()<<"): Not found:{title:"<<title<<","<<uuid.toString()<<"}";
        }
    }
    void TabWindowBase::_closeButtonClicked(const QVariant &title,const QVariant &uuid){
        this->removeTab(title.toString(),uuid.toString());
    }
}