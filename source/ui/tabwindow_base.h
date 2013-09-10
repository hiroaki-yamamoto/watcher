#pragma once
#include <QHash>
#include <QPair>
#include <QString>
#include <QUuid>

#include "qml_window_base.h"
namespace ui{
    class TabContentsBase;
    class TabWindowBase:public QMLWindowBase{
            Q_OBJECT
        public:
            using QMLWindowBase::QMLWindowBase;
        protected:
            TabContentsBase *_getCurrentTabContents();
            QHash<QPair<QString,QUuid>,TabContentsBase *> _tabcontents;
    };
}
