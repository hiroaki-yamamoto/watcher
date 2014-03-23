#include <logging/logging.h>
#include <QtDebug>
#include "board.h"
#include "topic.h"
using namespace logging;
namespace test{
    board::board(const QString &name, const QUuid &id, QObject *parent):plugin::board(parent){
        this->setObjectName(name);
        this->setTitle(name);
        this->setIdentifier(id);
        QString copied_name=this->title();
        copied_name.replace(" ","_");
        this->_board_url=QString("http://example.com/boards/%1").arg(copied_name);
        qDebug()<<this<<"board URI="<<this->_board_url;
    }
    const QUrl &board::board_url() const{return this->_board_url;}
    void board::get_topics(){
        QVector<plugin::topic *> topics;
        for(quint16 count=0;count<100;count++){
            QUuid topic_id=QUuid::createUuidV5(this->identifier(),QString::number(count));
            topics<<new test::topic(QString("Test Topic Title: %1").arg(count),"Anonymous",
                              topic_id,this->board_url().resolved(QString("topic-%1").arg(topic_id.toString())),this);
        }
        emit this->get_topics_finished(topics);
    }
}
