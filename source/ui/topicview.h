#pragma once
#include <QHash>
#include <QPair>
#include <QString>
#include <QUuid>
#include<QtNetwork/QNetworkReply>
#include "tabcontents_base.h"
namespace plugin{
    class board;
    class topic;
}
template<class T> class QVector;

namespace ui{
    class TopicView:public TabContentsBase{
            Q_OBJECT
        public:
            TopicView(plugin::board *board,TabContentsBase *parent=nullptr);
        public slots:
            void addButton(const QString &title,const QString &detail,const QUuid &uuid);
        signals:
            void buttonClicked(const QString &title,const QUuid &uuid,plugin::topic *topic);
        private slots:
            void _buttonClicked(const QVariant &variant);
            void _getTopicsFinished(const QVector<plugin::topic *> &topics);
            void _getTopicsFailed(const QNetworkReply::NetworkError err,const QString &err_str);
        private:
            QHash<QPair<QString,QUuid>,plugin::topic *> _topics;
    };
}
