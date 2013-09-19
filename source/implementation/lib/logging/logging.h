#include<QString>
#include<QUuid>
class QObject;
class QDebug;
template <class S,class T> class QPair;
namespace logging{
    QDebug &operator<<(QDebug &in,const QObject *object);
    QDebug &operator<<(QDebug &in,const QObject &object);
    QDebug &operator<<(QDebug &in,const QPair<QString,QUuid> &title_uuid);
}
