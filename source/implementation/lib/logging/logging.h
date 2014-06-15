#include <QString>
#include <QUuid>
class QObject;
class QDebug;
template <class S, class T>
struct QPair;
namespace logging {
    QDebug &operator<<(QDebug &in, const QPair<QString, QUuid> &title_uuid);
}
