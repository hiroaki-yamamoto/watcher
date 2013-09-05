#pragma once
#include <QObject>
#include <QtNetwork/QNetworkReply>
namespace plugin{
    class board;
    class topic;
}
template <class T> class QVector;

namespace ui{
    class BoardTabContents:public QObject{
            Q_OBJECT
        public:
            BoardTabContents(plugin::board *board,QObject *parent=nullptr);
        signals:
            void responseMode(plugin::topic *topic);
        private slots:
            void _get_topics_finished(const QVector<plugin::topic *> &topics);
            void _get_topics_failed(const QNetworkReply::NetworkError err,const QString &err_str);
        private:
            plugin::board *_board;
    };
}
