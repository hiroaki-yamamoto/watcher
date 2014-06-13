#pragma once
#include <loader/topic.h>
#include <loader/response.h>
#include <QUrl>
#include <QVector>
class QString;
class QUuid;
namespace test {
    class topic : public plugin::topic {
        Q_OBJECT
       public:
        topic(const QString &title, const QString &author, const QUuid &id,
              const QUrl &topicURL, QObject *parent = nullptr);
        void get_responses();
        bool readonly() const;
        const QUrl &topic_url() const;
       public
    slots:
        void post();

       private:
        QUrl _topicURL;
        QVector<plugin::response *> _resposes;
    };
}
