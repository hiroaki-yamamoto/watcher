#include "category.h"
#include "board.h"
#include <QObject>
#include <QVector>
#include <QtDebug>
#include <QUuid>
#include <QByteArray>
#include <logging/logging.h>
using namespace logging;
namespace test {
    category::category(const QString &name, const QUuid &id, QObject *parent)
        : plugin::category(parent) {
        this->setTitle(name);
        this->setIdentifier(id);
    }
    void category::get_boards() {
        QVector<plugin::board *> boards;
        for (size_t i = 1; i < 101; i++) {
            boards << new test::board(
                          QString("Board %1").arg(QString::number(i)),
                          QUuid::createUuidV5(this->identifier(),
                                              QString::number(i)),
                          this);
        }
        emit this->get_boards_finished(boards);
    }
}
