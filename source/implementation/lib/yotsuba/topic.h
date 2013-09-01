#pragma once
#include <QUrl>
#include <QHash>
#include <loader/topic.h>
#include <QString>
namespace plugin{
    class response;
}
namespace yotsuba{
    class topic:public plugin::topic{
            Q_OBJECT
            friend class board;
        public:
            topic(QObject *parent=nullptr);
            const QUrl &topic_url() const;
            bool readonly() const;
            void get_responses();
            qulonglong topicID() const;
        public slots:
            void setTopicID(const qulonglong &topicID);
            void setTopicURL(const QUrl &url);
            void setReadOnly(const bool &readonly);
        private slots:
            void getDataFinished(QNetworkReply *reply);
        private:
            quint64 _topicID;
            QString _name;
            QUrl _url;
            bool _readonly;
    };
}
