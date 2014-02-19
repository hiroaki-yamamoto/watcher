#include "imageconverter.h"
#include <QHash>
#include <QPair>
#include <QImage>
#include <random>
namespace manager{
    std::mt19937 __random_number__;
    template<class T>
    QHash<QUuid,QPair<QUrl,T>> convert(const QHash<QUrl,T> &hash,const QUuid &baseUUID){
        QHash<QUuid,QPair<QUrl,T>> result;
        for(QUrl &url:hash.keys()){
            QUuid &&key=QUuid::createUuidV5(baseUUID,url.toString()+QString::number(__random_number__()));
            result[key]=qMakePair(url,hash[url]);
        }
        return result;
    }
    QHash<QUuid,QPair<QUrl,QImage>> convertImage(const QHash<QUrl,QImage> &map){
        return convert<QImage>(map,
                               QUuid::createUuidV5(QUuid("{b894f363-65ff-45f8-891f-a8f1912d01be}"),
                                                   QString::number(__random_number__())
                                                   )
                               );
    }
    QHash<QUuid,QPair<QUrl,QPixmap>> convertPixmap(const QHash<QUrl,QPixmap> &map){
        return convert<QPixmap>(map,
                               QUuid::createUuidV5(QUuid("{b894f363-65ff-45f8-891f-a8f1912d01be}"),
                                                   QString::number(__random_number__())
                                                   )
                               );
    }
}
