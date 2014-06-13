#pragma once
#include <QHash>
#include <QPair>
#include <QString>
#include <QUuid>

class TabContentsBase;
namespace ui {
    class TabBase {
       protected:
        virtual TabContentsBase *_getCurrentTabContents();
        QHash<QPair<QString, QUuid>, TabContentsBase *> _tabcontents;
    };
}
