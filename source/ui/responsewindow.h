#pragma once
#include "tabwindow_base.h"

namespace plugin{
    class root;
    class topic;
}
namespace storage{
    class property_storage;
}
template <class S> class QList;
namespace ui{
    class ResponseWindow:public TabWindowBase{
            Q_OBJECT
        public:
            ResponseWindow(const QString &title,
                        const QIcon &icon,
                        QList<plugin::root *> *plugins,
                        storage::property_storage *property,
                        QMLWindowBase *parent=nullptr);
            void addTopic(plugin::topic *th);
        private slots:
            void _createRelationBetweenSignalsAndSlots();
            void _postButtonClicked();
            void _reload();
    };
}
