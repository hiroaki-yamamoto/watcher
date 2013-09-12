#include <loader/root.h>
#include <loader/category.h>
#include <loader/board.h>
#include <QtDebug>
#include "boardwindow.h"
#include "boardtabcontents.h"
namespace ui{
    void BoardWindow::_createRelationBetweenSignalsAndSlots(){
        for(const QString &childName:this->_children.uniqueKeys()){
            if(childName=="reload")     connect(this->_children.value(childName),SIGNAL(clicked()),SLOT(_reload()));
            else if(childName=="close") connect(this->_children.value(childName),SIGNAL(clicked()),SLOT(_close()));
        }
    }

    void BoardWindow::addTabContents(plugin::board *board){
        plugin::category *category=qobject_cast<decltype(category)>(board->parent());
        if(category==nullptr){
            qWarning()<<"("<<this->objectName()<<"): Adding Tab Contents Failed (the pointer of the parent object is null.)";
        }
        plugin::root *root=qobject_cast<decltype(root)>(category->parent());
        if(root==nullptr){
            qWarning()<<"("<<this->objectName()<<"): Adding Tab Contents Failed (the pointer of the parent object is null.)";
        }
        QPair<QString,QUuid> &&key=qMakePair(root->title(),root->identifier());
        if(this->_tabcontents.contains(key)){
            BoardTabContents *contents=qobject_cast<decltype(contents)>(this->_tabcontents[key]);
        }else{
            this->_tabcontents.insert(key,new BoardTabContents(root->title(),root->identifier(),this));
        }
    }

    void BoardWindow::removeTopics(plugin::board *board){
        
    }

    void BoardWindow::_responseMode(plugin::topic *topic){
        
    }
    void BoardWindow::_reload(){
        qDebug()<<"ReloadClicked";
    }
    void BoardWindow::_close(){
        this->setVisible(false);
    }
}
