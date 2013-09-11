#pragma once
#include <QObject>
#include <QtNetwork/QNetworkReply>
#include "tabcontents_base.h"
#include "tabwindow_base.h"
namespace plugin{
    class board;
    class topic;
}
class QQuickItem;
class QString;
class QUuid;

namespace ui{
    class BoardTabContents:public TabContentsBase{
            Q_OBJECT
        public:
            BoardTabContents(const QString &root_title,const QUuid &root_uuid,TabWindowBase *parent=nullptr);
        signals:
            void responseMode(plugin::topic *topic);
        public slots:
            QQuickItem *addTab(const QString &title, const QUuid &uuid);
    };
}
