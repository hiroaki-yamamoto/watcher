#pragma once
#include <loader/board.h>
#include <QString>
#include <QUrl>
class QUuid;
namespace test{
    class board:public plugin::board{
            Q_OBJECT
            using plugin::board::board;
        public:
            board(const QString &name, const QUuid &id, QObject *parent=nullptr);
            const QUrl &board_url() const;
        public slots:
            void get_topics();
        private:
            QUrl _board_url;
            quint64 _num;
    };
}
