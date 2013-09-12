#include <QVector>
#include <QtDebug>
#include <QString>
#include <QtQuick/QQuickItem>
#include <QtWidgets/QMessageBox>

#include <loader/board.h>

#include "boardtabcontents.h"
namespace ui{
    BoardTabContents::BoardTabContents(const QString &title,const QUuid &uuid,TabWindowBase *parent):
        TabContentsBase(title,uuid,parent){}
    BoardTabContents::BoardTabContents(const QString &title,const QUuid &uuid,TabContentsBase *parent):
        TabContentsBase(title,uuid,parent){}
    void BoardTabContents::addBoard(plugin::board *board){
        //TODO:Implement the function
    }
}
