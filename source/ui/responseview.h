#pragma once
#include <QtNetwork/QNetworkReply>
#include <QObject>
#include <QHash>
#include <QUuid>
#include <QVector>

#include <manager/imagemanager.h>

#include "tabcontents_base.h"

class QQuickItem;
class QString;
class QDateTime;
class QUrl;

namespace plugin{
    class topic;
    class response;
}

namespace ui{
    class ResponsePanel;
    class ResponseView:public TabContentsBase{
            friend class ResponsePanel;
            Q_OBJECT
        public:
            ResponseView(plugin::topic *topic,TabContentsBase *parent=nullptr);
        public slots:
            QQuickItem *addTab(const QString &title, const QUuid &uuid);
            void responseLoaded(const QVector<plugin::response *> &responses);
            void responseFetchingFailed(const QNetworkReply::NetworkError err,const QString &err_str);
            void addItem(plugin::response *res);
            void reload();
        private slots:
            void updateImageInfo();
        private:
            QQuickItem *_addItem(const QString &title, const QString &author,
                                const QString &email, const QDateTime &post_time,
                                const QString &body, const QUuid &uuid,
                                const QUrl &responseURL, manager::ImageManager *imageManager);
            plugin::topic *_topic;
            QHash<QPair<QString,QUuid>,QObject *> _childrenItems;
    };
}
