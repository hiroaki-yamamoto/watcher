#include "pixelmanager.h"

namespace manager{
    PixelManager::PixelManager(const QHash<QUuid, QPair<QUrl, QPixmap> > &pixmaps):
        QQuickImageProvider(QQuickImageProvider::Pixmap),QHash<QUuid,QPair<QUrl,QPixmap>>(pixmaps){}
    QPixmap PixelManager::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize){
        QPixmap pixmap=(*this)[id].second;
        if(requestedSize.isValid()) pixmap=pixmap.scaled(requestedSize);
        (*size)=pixmap.size();
        return pixmap;
    }
    PixelManager::operator ImageManager() const{
        ImageManager im;
        for(const QUuid &key:this->uniqueKeys()){
            const QPair<QUrl, QPixmap> &value=(*this)[key];
            im[key]=qMakePair(value.first,value.second.toImage());
        }
        return im;
    }
}
