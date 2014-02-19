#pragma once
#include<QUuid>
#include<QUrl>
#include<QImage>
#include<QPixmap>
template<class S,class T> class QHash;
namespace manager{
    QHash<QUuid,QPair<QUrl,QImage>> convertImage(const QHash<QUrl,QImage> &map);
    QHash<QUuid,QPair<QUrl,QPixmap>> convertPixmap(const QHash<QUrl,QPixmap> &map);
}
