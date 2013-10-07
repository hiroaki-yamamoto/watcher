#pragma once
#include <QObject>
#include <QDateTime>
#include <QUrl>
#include <QUuid>
#include <QHash>
#include <QPair>

#include <manager/imagemanager.h>
#include <manager/pixelmanager.h>

class QQuickItem;
namespace plugin{
    class response;
}
namespace ui{
    class ResponsePanel:public QObject{
            Q_OBJECT
            Q_PROPERTY(QString title READ title WRITE setTitle)
            Q_PROPERTY(QString author READ author WRITE setAuthor)
            Q_PROPERTY(QString email READ email WRITE setEmail)
            Q_PROPERTY(QDateTime postTime READ post_time WRITE setPostTime)
            Q_PROPERTY(QString body READ body WRITE setBody)
            Q_PROPERTY(QUuid UUID READ uuid WRITE setUUID)
            Q_PROPERTY(QUrl responseURL READ responseURL WRITE setResponseURL)
        public:
            ResponsePanel(plugin::response *res,QObject *parent);
            QString title() const;
            QString author() const;
            QString email() const;
            QDateTime post_time() const;
            QString body() const;
            QUuid UUID() const;
            QUrl responseURL() const;
        public slots:
            void setTitle(const QString &title);
            void setAuthor(const QString &author);
            void setEmail(const QString &email);
            void setPostTime(const QDateTime &post_time);
            void setBody(const QString &body);
            void setUUID(const QUuid &id);
            void setResponseURL(const QUrl &url);
        private:
            QQuickItem *_item;
            manager::ImageManager _imageManager;
            manager::PixelManager _pixelManager;
    };
}
