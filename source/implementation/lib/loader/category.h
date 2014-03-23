#pragma once
/*
 * Here is a exception about the license.
 * NOTICE: This code is licensed under the terms of the latest version of LGPLv3. Not GPLv3.
 *                                                                        ~~~~~~
 */
#include <QUuid>
#include <QtNetwork/QNetworkReply>

#include <loader/content_base.h>

template<class T>class QVector;
class QString;

namespace plugin{
    class board;
    //Category
    class category:public content_base{
            Q_OBJECT
            using content_base::content_base;
        public slots:
            virtual void get_boards()=0;
        signals:
             void get_boards_finished(const QVector<plugin::board *> &boards);
             void get_boards_failed(const QNetworkReply::NetworkError err,const QString &err_str);
    };
}
