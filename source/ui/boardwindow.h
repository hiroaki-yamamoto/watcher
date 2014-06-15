#pragma once
#include <QHash>
#include <QPair>
#include <QUuid>
#include <QString>
#include "tabwindow_base.h"
namespace plugin {
    class root;
    class board;
    class topic;
}
namespace ui {
    class BoardTabContents;
    class ResponseWindow;
    class BoardWindow : public TabWindowBase {
        Q_OBJECT
        Q_PROPERTY(QList<plugin::root *> *plugins READ plugins)
        Q_PROPERTY(storage::property_storage *property READ property)
       public:
        BoardWindow(const QString &title, const QIcon &icon,
                    QList<plugin::root *> *plugins,
                    storage::property_storage *property,
                    QMLWindowBase *parent = nullptr);
       public
    slots:
        void addTabContents(plugin::board *board);
       private
    slots:
        void _responseMode(plugin::topic *topic);
        void _createRelationBetweenSignalsAndSlots();
        void _reload();
        void _close();

       private:
        ResponseWindow *_responseWindow;
    };
}
