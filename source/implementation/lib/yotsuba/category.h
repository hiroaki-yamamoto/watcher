#pragma once
#include <loader/category.h>
#include <QString>
#include <QUrl>
#include <QDateTime>
#include <random>
namespace plugin{
    class topic;
}
class QNetworkAccessManager;
class QNetworkReply;
template <class S,class T> class QHash;
namespace yotsuba{
    class category:public plugin::category{
            Q_OBJECT
            friend class root;
        public:
            category(std::mt19937 *mt, QNetworkAccessManager *manager, QHash<QUrl, QDateTime> *last_modified, QObject *parent=nullptr);
            void get_boards();
        public slots:
            void setWorkSafe(const bool ws);
        private slots:
            void getDataFinished(QNetworkReply *reply);
        private:
            bool _ws;
            std::mt19937 *_mt;
            QNetworkAccessManager *_accessmanager;
            QHash<QUrl,QDateTime> *_last_modified;
    };
}
