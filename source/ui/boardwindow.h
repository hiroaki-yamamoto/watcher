#pragma once
#include <QHash>
#include <QPair>
#include <QUuid>
#include <QString>
#include "qml_window_base.h"
namespace plugin{
    class root;
    class board;
    class topic;
}
namespace ui{
    class BoardTabContents;
    class BoardWindow:public QMLWindowBase{
            Q_OBJECT
            Q_PROPERTY(QList<plugin::root *> *plugins READ plugins)
            Q_PROPERTY(storage::property_storage *property READ property)
        public:
            BoardWindow(const QString &title,
                        const QIcon &icon,
                        QList<plugin::root *> *plugins,
                        storage::property_storage *property,
                        QWindow *parent=nullptr);
            QList<plugin::root *> *plugins() const;
            storage::property_storage *property() const;
        public slots:
            void addTabContents(plugin::board *board);
            void removeTopics(plugin::board *board);
            void responseMode(plugin::topic *topic);
        private:
            QHash<QPair<QString,QUuid>,BoardTabContents *> _tabContents;
            QList<plugin::root *> *_plugins;
            storage::property_storage *_property;
    };
}
