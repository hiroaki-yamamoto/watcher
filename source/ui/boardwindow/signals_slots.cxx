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
        auto &&key=qMakePair(board->title(),board->identifier());
        qDebug()<<"Key:"<<key;
        this->_tabContents.insert(key,new BoardTabContents(board,this));
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
