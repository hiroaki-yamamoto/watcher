#pragma once
#include <loader/topic.h>
#include <random>
#include <QUrl>
class QString;
class QUuid;
namespace test{
    class topic:public plugin::topic{
            Q_OBJECT
        public:
            topic(std::mt19937 *mt,const QString &title,const QString &author,const QUuid &id,const QUrl &topicURL,QObject *parent=nullptr);
            void get_responses();
            bool readonly() const;
            const QUrl &topic_url() const;
        private:
            std::mt19937 *_mt;
            QUrl _topicURL;
    };
}
