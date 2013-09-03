#pragma once
#include <QUrl>
#include <QByteArray>
#include <loader/board.h>
#include <QObject>
#include <QString>
#include <random>

class QNetworkReply;
class QNetworkAccessManager;
template<class S,class T> class QHash;
namespace plugin{
    class topic;
}
namespace yotsuba{
    class board:public plugin::board{
            Q_OBJECT
            friend class category;
        public:
            board(std::mt19937 *mt,QHash<QUrl,QByteArray> *last_modified,QNetworkAccessManager *accessManager,QObject *parent=nullptr);
            const QString &board_dir() const;
            const QUrl &board_url() const;
            void get_topics();
        public slots:
            void setBoardURL(const QUrl &url);
            void setBoardDirName(const QString &dir);
        private slots:
            void getDataFinished(QNetworkReply *reply);
        private:
            std::mt19937 *_mt;
            QString _dir;
            QUrl _board_url;
            QHash<QUrl,QByteArray> *_last_modified;
            QNetworkAccessManager *_accessmanager;
    };
}
