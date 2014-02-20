#pragma once
#include <loader/response.h>
#include <QHash>
#include <QImage>
#include <QDateTime>
#include <QUrl>

namespace test{
    class response:public plugin::response{
            Q_OBJECT
        public:
            response(const QString &title,const QString &body,const QString &author,const QString &email,
                     const QDateTime &creation_date,const QUrl &res_url,const QUuid &id,QObject *parent);
            const QString &email() const;
            const QString &body() const;
            const QDateTime &creation_date() const;
            const QUrl      &response_url() const;
            manager::ImageManager *images() const;
        public slots:
            void fetchImage(const QUrl &link_url,const QImage &image);
        private:
            manager::ImageManager *_images;
            QString _email;
            QDateTime _creation_date;
            QUrl _response_url;
    };
}
