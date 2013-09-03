#pragma once
#include <QUrl>
#include <loader/topic.h>
#include <QString>
namespace plugin{
    class response;
}
class QNetworkAccessManager;
namespace yotsuba{
    class topic:public plugin::topic{
            Q_OBJECT
            friend class board;
        public:
            topic(QNetworkAccessManager *accessManager,QObject *parent=nullptr);
            const QUrl &topic_url() const;
            bool readonly() const;
            void get_responses();
            void post(const plugin::response &res);
            qulonglong topicID() const;
        public slots:
            void setTopicID(const qulonglong &topicID);
            void setTopicURL(const QUrl &url);
        private slots:
            void getDataFinished(QNetworkReply *reply);
        private:
            quint64 _topicID;
            QString _name;
            QUrl _url;
            QNetworkAccessManager *_accessmanager;
    };
}
