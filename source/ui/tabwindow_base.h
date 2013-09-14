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
            TabWindowBase(const QString &title,
                           const QIcon &icon,
                           QMLWindowBase *parent=nullptr);
        public slots:
            virtual QQuickItem *addTab(const QString &title,const QUuid &uuid);
            virtual void removeTab(const QString &title,const QUuid &uuid);
            virtual void _closeButtonClicked(const QVariant &title,const QVariant &uuid);
            virtual void _loaded();
        protected:
            TabContentsBase *_getCurrentTabContents();
            QHash<QPair<QString,QUuid>,TabContentsBase *> _tabcontents;
    };
}
