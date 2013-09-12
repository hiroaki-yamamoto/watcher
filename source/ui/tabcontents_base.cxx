#include "tabcontents_base.h"
#include "tabwindow_base.h"
#include<QtDebug>
#include<QtQuick/QQuickItem>
#include<QUuid>
namespace ui{
    TabContentsBase::TabContentsBase(const QString &title, const QUuid &uuid, TabWindowBase *parent):QObject(parent){
        this->setObjectName(uuid.toString());
        if(parent==nullptr){
            qWarning()<<"Tab{Title:"<<title<<", uuid:"<<uuid.toString()<<"}: parent=null is not allowed.";
            this->deleteLater();
            return;
        }
        this->_parentWindow=parent;
        this->_parentTab=nullptr;
        //If adding tab is failed, RootTabContents should be deleted.
        if((this->_tabcontents=this->_parentWindow->addTab(title,uuid))==nullptr){
            qWarning()<<"("<<this->objectName()<<"): Adding tab failed.";
            this->deleteLater();
            return;
        }
        this->_tabcontents->setObjectName(uuid.toString());
    }
    TabContentsBase::TabContentsBase(const QString &title, const QUuid &uuid,TabContentsBase *parent):QObject(parent){
        this->setObjectName(uuid.toString());
        if(parent==nullptr){
            qWarning()<<"Tab{Title:"<<title<<", uuid:"<<uuid.toString()<<"}: parent=null is not allowed.";
            this->deleteLater();
            return;
        }
        this->_parentTab=parent;
        this->_parentWindow=nullptr;
        //If adding tab is failed, RootTabContents should be deleted.
        if((this->_tabcontents=this->_parentTab->addTab(title,uuid))==nullptr){
            qWarning()<<"("<<this->objectName()<<"): Adding tab failed.";
            this->deleteLater();
            return;
        }
        this->_tabcontents->setObjectName(uuid.toString());
    }
    
    QString TabContentsBase::title() const{return this->_tabcontents->property("title").toString();}
    QUuid TabContentsBase::UUID() const{return this->_tabcontents->property("uuid").toString();}
    QQuickItem *TabContentsBase::addTab(const QString &title,const QUuid &uuid){
        QVariant variant;
        if(!QMetaObject::invokeMethod(this->_tabcontents,"addTab",Q_RETURN_ARG(QVariant,variant),
                                      Q_ARG(QVariant,QVariant(title)),Q_ARG(QVariant,QVariant(uuid.toString())))){
            qWarning()<<"("<<this->objectName()<<"):Adding Tab failed:{title:"<<title<<",uuid:"<<uuid.toString()<<"}";
            return nullptr;
        }else return variant.value<QQuickItem *>();
    }
    void TabContentsBase::setTitle(const QString &title){
        QString &&previous=this->title();
        this->_tabcontents->setProperty("title",title);
        if(title!=previous) emit this->titleChanged();
    }
    void TabContentsBase::setUUID(const QUuid &uuid){
        QUuid &&previous=this->UUID();
        this->_tabcontents->setProperty("uuid",uuid.toString());
        if(uuid!=previous) emit this->uuidChanged();
    }
    
    TabContentsBase *TabContentsBase::_getCurrentTabContents(){
        QQuickItem *currentTab=this->_tabcontents->property("currentSelectedTabContent").value<QQuickItem *>();
        if(currentTab==nullptr){
            qDebug()<<"("<<this->objectName()<<": currentSelectedTabContent is null.";
            return nullptr;
        }
        QUuid tab_uuid=QUuid(currentTab->property("uuid").toString());
        QString tab_title=currentTab->property("title").toString();
        QPair<QString,QUuid> tab_key=qMakePair(tab_title,tab_uuid);
        if(!this->_childrenTabs.contains(tab_key)){
            qDebug()<<"("<<this->objectName()<<": TabContent Named:"<<tab_title<<" couldn't be found.";
            return nullptr;
        }else return this->_childrenTabs[tab_key];
    }

    void TabContentsBase::deleteLater(){
        if(this->_tabcontents!=nullptr){
            qDebug()<<"("<<this->objectName()<<"):"<<"Deleting tab:"<<this->objectName();
            this->_tabcontents->deleteLater();
        }else{
            qDebug()<<"("<<this->objectName()<<"):Tab is null";
        }
        QObject::deleteLater();
    }
}
