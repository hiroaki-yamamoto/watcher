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
    class ResponseView;
    class ResponsePanel:public QObject{
            Q_OBJECT
            Q_PROPERTY(QString title READ title)
            Q_PROPERTY(QString author READ author)
            Q_PROPERTY(QString email READ email)
            Q_PROPERTY(QDateTime postTime READ post_time)
            Q_PROPERTY(QString body READ body)
            Q_PROPERTY(QUuid UUID READ UUID)
            Q_PROPERTY(QUrl responseURL READ responseURL)
        public:
            ResponsePanel(const plugin::response *res,ResponseView *parent);
            QString title() const;
            QString author() const;
            QString email() const;
            QDateTime post_time() const;
            QString body() const;
            QUuid UUID() const;
            QUrl responseURL() const;
            const plugin::response *response() const;
        public slots:
            void setResponse(const plugin::response *res);
        private:
            const plugin::response *_response;
            QQuickItem *_item;
            manager::ImageManager _imageManager;
            manager::PixelManager _pixelManager;
    };
}
