#pragma once
/*
 * Here is a exception about the license.
 * NOTICE: This code is licensed under the terms of the latest version of LGPLv3. Not GPLv3.
 *                                                                        ~~~~~~
 */
#include <QtNetwork/QNetworkReply>
#include <loader/content_base.h>

class QString;
class QUrl;
template<class T>class QVector;

namespace plugin{
    class response;
    //Topic (well known as "thread" in 2ch.)
    class topic:public content_base{
            Q_OBJECT
            using content_base::content_base;
        public:
            virtual void get_responses()=0;
            virtual bool readonly() const=0;
            virtual const QUrl &topic_url() const=0;
            virtual void post(const response &res)=0;
        signals:
            void post_finished(const response &res);
            void post_failed(const QNetworkReply::NetworkError err,const QString &err_str);
            void get_responses_finished(const QVector<plugin::response *> &responses);
            void get_responses_failed(const QNetworkReply::NetworkError err,const QString &err_str);
            void get_response_warning(const QNetworkReply::NetworkError err,const QUrl &url,const QString &err_str);
    };
}
