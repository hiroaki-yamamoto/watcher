#pragma once
#include <QHash>
#include <QPair>
#include <QString>
#include <QUuid>

#include "qml_window_base.h"

class QJSValue;

namespace ui {
    class TabContentsBase;
    class TabWindowBase : public QMLWindowBase {
        Q_OBJECT
       public:
        TabWindowBase(const QString &title, const QIcon &icon,
                      QList<plugin::root *> *plugins,
                      storage::property_storage *property,
                      QMLWindowBase *parent = nullptr);
       public
    slots:
        virtual QQuickItem *addTab(const QString &title, const QUuid &uuid);
        virtual void removeTab(const QString &title, const QUuid &uuid);
        virtual void _closeButtonClicked(const QJSValue &title,
                                         const QJSValue &uuid);
        virtual void _loaded();
        void deleteLater();

       protected:
        TabContentsBase *_getCurrentTabContents();
        QHash<QPair<QString, QUuid>, TabContentsBase *> _tabcontents;
    };
}
