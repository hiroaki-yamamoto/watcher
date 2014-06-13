#pragma once
#include <QString>
#include <loader/category.h>
class QUuid;
namespace test {
    class category : public plugin::category {
        Q_OBJECT
       public:
        category(const QString &name, const QUuid &id,
                 QObject *parent = nullptr);
       public
    slots:
        void get_boards();
    };
}
