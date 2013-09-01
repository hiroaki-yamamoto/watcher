#pragma once
#include <QHash>
#include "qml_window_base.h"
namespace plugin{
    class root;
    class board;
    class topic;
}
namespace ui{
    class BoardWindow:public QMLWindowBase{
            Q_OBJECT
        public:
            BoardWindow(const QString &title,
                        const QIcon &icon,
                        QList<plugin::root *> *plugins,
                        storage::property_storage *property,
                        QWindow *parent=nullptr);
            QList<plugin::root *> *plugins() const;
            storage::property_storage *property() const;
        public slots:
            void addTopics(plugin::board *board);
            void removeTopics(plugin::board *board);
            void responseMode(plugin::topic *topic);
    };
}
