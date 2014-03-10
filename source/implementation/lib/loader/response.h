#pragma once
/*
 * Here is a exception about the license.
 * NOTICE: This code is licensed under the terms of the latest version of LGPLv3. Not GPLv3.
 *                                                                        ~~~~~~
 */
#include <QObject>
#include <QImage>
#include <QUrl>

#include <loader/content_base.h>
#include <manager/imagemanager.h>

class QString;
class QDateTime;
template <class S,class T> class QHash;
namespace plugin{
    class response:public content_base{
            Q_OBJECT
            using content_base::content_base;
        public:
            //Topic creator info.
            virtual const QString &email() const=0;
            //Topic title and the body
            virtual const QString &body() const=0;
            virtual const QDateTime &creation_date() const=0;
            virtual const QUrl &response_url() const=0;
            //Image cache.
            virtual manager::ImageManager *images() const=0;
            //virtual const QHash<QUrl,QImage> &images() const=0;
    };
}
