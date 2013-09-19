#pragma once
#include <loader/response.h>
#include <QUrl>
#include <QImage>
#include <QtNetwork/QNetworkReply>
class QString;
template<class S,class T> class QHash;
class QNetworkAccessManager;

namespace yotsuba{
    /*
     * Response class is written with very tricky coding.
     * First, to avoid using include compiler instruction, all variables and return values are references or pointers.
     */
    class response:public plugin::response{
            Q_OBJECT
            friend class topic;
        public:
            response(QNetworkAccessManager *accessManager,QObject *parent=nullptr);
            ~response();
            const QString &email() const;
            const QString &body() const;
            const QDateTime &creation_date() const;
            const QUrl &response_url() const;
            const QHash<QUrl,QImage> &images() const;
            const quint64 resID() const;
        public slots:
            void fetchImage(const QUrl &url);
            void setEmail(const QString &email);
            void setBody(const QString &body);
            void setCreationDate(const QDateTime &creation_date);
            void setResponseUrl(const QUrl &url);
            void setImages(const QHash<QUrl,QImage> &images);
            void setHasImages(const bool has_images);
            void setResID(const quint64 &resID);
        signals:
            void fetchingImageFailed(QNetworkReply::NetworkError err,const QUrl &url,const QString &errStr);
        private slots:
            void _fetching_image_finished(QNetworkReply *reply);
        private:
            QNetworkAccessManager *_accessManager;
            QString *_body,*_email;
            QDateTime *_creation_date;
            QUrl *_topic_url;
            QHash<QUrl,QImage> *_images;
            quint64 _resID;
            bool _has_images;
    };
}
