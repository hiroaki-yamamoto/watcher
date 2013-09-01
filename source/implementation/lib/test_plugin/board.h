#pragma once
#include <loader/board.h>
#include <QString>
#include <QUrl>
#include <random>
class QUuid;
namespace test{
    class board:public plugin::board{
            Q_OBJECT
            using plugin::board::board;
        public:
            board(std::mt19937 *mt,const QString &name,const QUuid &id,QObject *parent=nullptr);
            const QUrl &board_url() const;
            void get_topics();
        private:
            QUrl _board_url;
            std::mt19937 *_mt;
    };
}
