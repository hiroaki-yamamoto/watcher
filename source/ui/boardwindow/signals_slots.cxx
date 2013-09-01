#include <loader/board.h>
#include <QtDebug>
#include "boardwindow.h"
#include "boardtabcontents.h"
namespace ui{
    void BoardWindow::addTabContents(plugin::board *board){
        auto &&key=qMakePair(board->title(),board->identifier());
        qDebug()<<"Key:"<<key;
        this->_tabContents.insert(key,new BoardTabContents(board,this));
    }

    void BoardWindow::removeTopics(plugin::board *board){
        
    }

    void BoardWindow::responseMode(plugin::topic *topic){
        
    }
}
