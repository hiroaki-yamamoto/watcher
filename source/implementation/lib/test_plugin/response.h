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
            response(const QString &title,const QString &desc,const QString &author,const QString &email,
                     const QString &body,const QDateTime &creation_date,const QUrl &res_url,const QUuid &id,QObject *parent);
            const QString &email() const;
            const QString &body() const;
            const QDateTime &creation_date() const;
            const QUrl      &response_url() const;
            const QHash<QUrl,QImage> &images() const;
        public slots:
            void fetchImage(const QUrl &link_url,const QImage &image);
        private:
            QHash<QUrl,QImage> _images;
            QString _email,_body;
            QDateTime _creation_date;
            QUrl _response_url;
    };
}
