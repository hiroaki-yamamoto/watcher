#pragma once
#include <QObject>
#include <QtNetwork/QNetworkReply>
#include "tabcontents_base.h"
namespace plugin{
    class board;
    class topic;
}
class QQuickItem;
class QString;
class QUuid;
class TabWindowBase;

namespace ui{
    class BoardTabContents:public TabContentsBase{
            Q_OBJECT
        public:
            //I want to use constructor inheritence, but compiler outputs version confliction error.
            BoardTabContents(const QString &title,const QUuid &uuid,TabWindowBase *parent=nullptr);
        public slots:
            void addBoard(plugin::board *board);
            void reload();
        signals:
            void responseMode(plugin::topic *topic);
        private slots:
            void _buttonClicked(const QString &text,const QUuid &id,plugin::topic *topic);
    };
}
