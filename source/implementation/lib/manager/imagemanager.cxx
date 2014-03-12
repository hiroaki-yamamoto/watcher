#include "imagemanager.h"
#include <QDebug>

namespace manager{
    ImageManager::ImageManager(const QHash<QUuid,QPair<QUrl,QImage>> &images):
        QQuickImageProvider(QQuickImageProvider::Image),QHash<QUuid,QPair<QUrl,QImage>>(images){}
    QImage ImageManager::requestImage(const QString &id, QSize *size, const QSize &requestedSize){
        QImage image=(*this)[id].second;
        if(requestedSize.isValid()) image=image.scaled(requestedSize);
        (*size)=image.size();
        return image;
    }
}
