#pragma once
#include <QtQuick/QQuickImageProvider>
#include <QHash>
#include <QPair>
#include <QUrl>
#include <QUuid>
#include <QImage>

namespace manager {
    class ImageManager : public QQuickImageProvider,
                         public QHash<QUuid, QPair<QUrl, QImage>> {
       public:
        ImageManager(const QHash<QUuid, QPair<QUrl, QImage>> &images =
                         QHash<QUuid, QPair<QUrl, QImage>>());
        QImage requestImage(const QString &id, QSize *size,
                            const QSize &requestedSize);
    };
}
