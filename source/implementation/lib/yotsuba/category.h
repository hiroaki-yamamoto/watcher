#pragma once
#include <loader/category.h>
#include <QString>
#include <random>
namespace plugin{
    class topic;
}
class QNetworkReply;
namespace yotsuba{
    class category:public plugin::category{
            Q_OBJECT
            friend class root;
        public:
            category(std::mt19937 *_mt,QObject *parent=nullptr);
            void get_boards();
        public slots:
            void setWorkSafe(const bool ws);
        private slots:
            void getDataFinished(QNetworkReply *reply);
        private:
            bool _ws;
            std::mt19937 *_mt;
    };
}
