#pragma once
#include <QString>
#include <loader/category.h>
#include <random>
class QUuid;
namespace test{
    class category:public plugin::category{
            Q_OBJECT
        public:
            category(std::mt19937 *mt,const QString &name,const QUuid &id,QObject *parent=nullptr);
        public slots:
            void get_boards();
        private:
            std::mt19937 *_mt;
    };
}
