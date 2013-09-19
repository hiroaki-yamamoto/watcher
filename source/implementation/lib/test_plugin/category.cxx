#include "category.h"
#include "board.h"
#include <QObject>
#include <QVector>
#include <QtDebug>
#include <QUuid>
#include <logging/logging.h>
using namespace logging;
namespace test{
    category::category(std::mt19937 *mt, const QString &name, const QUuid &id, QObject *parent):plugin::category(parent){
        if(mt==nullptr){
            qWarning()<<this<<"mt must not be nulltpr.";
            this->deleteLater();
            return;
        }
        this->_mt=mt;
        this->setTitle(name);
        this->setIdentifier(id);
    }
    void category::get_boards(){
        QVector<plugin::board *> boards;
        for(size_t i=1;i<101;i++){
            unsigned int random_number=(*this->_mt)();
            boards<<new test::board(this->_mt,QString("Board %1").arg(QString::number(i)),
                                    QUuid::createUuidV5(this->identifier(),
                                                        QByteArray((const char *)&random_number,sizeof(random_number))),this);
        }
        emit this->get_boards_finished(boards);
    }
}
