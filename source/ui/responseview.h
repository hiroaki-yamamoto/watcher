#pragma once
#include <QObject>
#include <QHash>
#include <QUuid>

class QQuickItem;
class QString;
class QDateTime;
class QUrl;

namespace plugin{
    class response;
}

namespace ui{
    class TabContentsBase;
    class ResponsePanel;
    class ResponseView:public QObject{
            friend class ResponsePanel;
            Q_OBJECT
        public:
            ResponseView(TabContentsBase *parent=nullptr);
            void addItem(plugin::response *res);
        private:
            QQuickItem *_addItem(const QString &title,const QString &author,
                                const QString &email,const QDateTime &post_time,
                                const QString &body, const QUuid &uuid,
                                const QUrl &responseURL);
            QQuickItem *item;
            QHash<QUuid,ResponsePanel *> _panels;
    };
}
