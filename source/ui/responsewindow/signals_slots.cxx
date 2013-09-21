#include "responsewindow.h"
#include <QString>
#include <QDebug>
#include <logging/logging.h>

using namespace logging;
namespace ui{
    void ResponseWindow::_createRelationBetweenSignalsAndSlots(){
        for(const QString &key:this->_children.uniqueKeys()){
            if(key=="post")     connect(this->_children[key],SIGNAL(clicked()),SLOT(_postButtonClicked()));
            if(key=="reload")   connect(this->_children[key],SIGNAL(clicked()),SLOT(_reload()));
        }
    }
    void ResponseWindow::_postButtonClicked(){
        qDebug()<<this<<"post";
    }
    void ResponseWindow::_reload(){
        qDebug()<<this<<"reload";
    }
}
