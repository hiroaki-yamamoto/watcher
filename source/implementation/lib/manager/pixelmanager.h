#pragma once
#include <QtQuick/QQuickImageProvider>
#include <QHash>
#include <QPair>
#include <QUrl>
#include <QUuid>
#include <QPixmap>

#include <manager/imagemanager.h>

namespace manager {
    class PixelManager : public QQuickImageProvider,
                         public QHash<QUuid, QPair<QUrl, QPixmap>> {
       public:
        PixelManager(const QHash<QUuid, QPair<QUrl, QPixmap>> &pixmaps =
                         QHash<QUuid, QPair<QUrl, QPixmap>>());
        QPixmap requestPixmap(const QString &id, QSize *size,
                              const QSize &requestedSize);
        operator ImageManager() const;
    };
}
