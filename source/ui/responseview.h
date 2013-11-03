#pragma once
#include <QtNetwork/QNetworkReply>
#include <QObject>
#include <QHash>
#include <QUuid>
#include <QVector>

class QQuickItem;
class QString;
class QDateTime;
class QUrl;

namespace plugin{
    class topic;
    class response;
}

namespace ui{
    class TabContentsBase;
    class ResponsePanel;
    class ResponseView:public QObject{
            friend class ResponsePanel;
            Q_OBJECT
        public:
            ResponseView(plugin::topic *topic,TabContentsBase *parent=nullptr);
        public slots:
            void responseLoaded(const QVector<plugin::response *> &responses);
            void responseFetchingFailed(const QNetworkReply::NetworkError err,const QString &err_str);
            void addItem(plugin::response *res);
        private:
            QQuickItem *_addItem(const QString &title,const QString &author,
                                const QString &email,const QDateTime &post_time,
                                const QString &body, const QUuid &uuid,
                                const QUrl &responseURL);
            QQuickItem *_item;
            QHash<QUuid,ResponsePanel *> _panels;
    };
}
