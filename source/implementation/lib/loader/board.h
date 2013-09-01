#pragma once
/*
 * Here is a exception about the license.
 * NOTICE: This code is licensed under the terms of the latest version of LGPLv3. Not GPLv3.
 *                                                                        ~~~~~~
 */
#include <QtNetwork/QNetworkReply>
#include <loader/content_base.h>

template<class T> class QVector;
class QString;
class QUrl;
namespace plugin{
    class topic;
    //Board
    class board:public content_base{
            Q_OBJECT
            using content_base::content_base;
        public:
            virtual const QUrl &board_url() const=0;
            virtual void get_topics()=0;
        signals:
            void get_topics_finished(const QVector<plugin::topic *> &topics);
            void get_topics_failed(const QNetworkReply::NetworkError err,const QString &err_str);
    };
}
