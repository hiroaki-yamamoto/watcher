#pragma once
#include <loader/response.h>
#include <QUrl>
#include <QImage>
class QDateTime;
class QString;
class QUrl;
template<class S,class T> class QHash;

namespace yotsuba{
    /*
     * Response class is written with very trickky coding.
     * First, to avoid using include compiler instruction, all variables and return values are references or pointers.
     */
    class response:public plugin::response{
            Q_OBJECT
            friend class topic;
        public:
            response(QObject *parent=nullptr);
            ~response();
            const QString &email() const;
            const QString &body() const;
            const QDateTime &creation_date() const;
            const QUrl &response_url() const;
            const QHash<QUrl,QImage> &images() const;
            const bool has_images() const;
            const quint64 num_images() const;
            const quint64 resID() const;
        public slots:
            void setEmail(const QString &email);
            void setBody(const QString &body);
            void setCreationDate(const QDateTime &creation_date);
            void setResponseUrl(const QUrl &url);
            void setImages(const QHash<QUrl,QImage> &images);
            void setHasImages(const bool has_images);
            void setResID(const quint64 &resID);
        private:
            QString *_body,*_email;
            QDateTime *_creation_date;
            QUrl *_topic_url;
            QHash<QUrl,QImage> *_images;
            quint64 _resID;
            bool _has_images;
    };
}
