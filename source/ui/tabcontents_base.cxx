#include "tabcontents_base.h"
#include "qml_window_base.h"
#include<QtDebug>
#include<QtQuick/QQuickItem>
#include<QUuid>
namespace ui{
    TabContentsBase::TabContentsBase(const QString &title, const QUuid &uuid, QMLWindowBase *parent):QObject(parent){
        this->setObjectName(uuid.toString());
        if(parent==nullptr){
            qWarning()<<"Tab{Title:"<<title<<", uuid:"<<uuid.toString()<<"}: parent=null is not allowed.";
            this->deleteLater();
            return;
        }
        this->_parent=parent;
        QVariant tabcontent;
        //If adding tab is failed, RootTabContents should be deleted.
        if(!QMetaObject::invokeMethod(this->_parent->rootObject(),"addTab",Q_RETURN_ARG(QVariant,tabcontent),
                                  Q_ARG(QVariant,QVariant(title)),
                                  Q_ARG(QVariant,QVariant(uuid.toString())))){
            qWarning()<<"("<<this->objectName()<<"): Adding tab failed.";
            this->deleteLater();
            return;
        }
        this->_tabcontents=tabcontent.value<QQuickItem *>();
        this->_tabcontents->setObjectName(uuid.toString());
    }
    QString TabContentsBase::title() const{return this->_tabcontents->property("title").toString();}
    QUuid TabContentsBase::UUID() const{return this->_tabcontents->property("uuid").toString();}
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
