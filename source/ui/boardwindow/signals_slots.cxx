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
        /*
        plugin::category *category;
        if((category=qobject_cast<plugin::category *>(board->parent()))==nullptr){
            qWarning()<<"("<<this->objectName()<<")"<<"Couldn't get parent of board. Adding board to "+this->objectName()+"failed";
            return;
        }
        qDebug()<<"("<<this->objectName()<<"): Category:"<<"{title:"<<category->title()<<", UUID:"<<category->identifier().toString()<<"}";
        
        plugin::root *root;
        if((root=qobject_cast<plugin::root *>(category->parent()))==nullptr){
            qWarning()<<"("<<this->objectName()<<")"<<"Couldn't get root of. Adding board to "+this->objectName()+"failed";
            return;
        }
        qDebug()<<"("<<this->objectName()<<"): Root:"<<"{title:"<<root->title()<<", UUID:"<<root->identifier().toString()<<"}";
        auto &&key=qMakePair(root->title(),root->identifier());
        if(this->_tabcontents.contains(key)){
            
        }else{
            qDebug()<<"Adding:"<<key;
            this->_tabcontents.insert(key,new BoardTabContents(root->title(),root->identifier(),board,this));
        }
        */
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
