#include "logging.h"
#include <QPair>
#include <QDebug>
namespace logging {
    QDebug &operator<<(QDebug &in, const QPair<QString, QUuid> &title_uuid) {
        in << "{title:" << title_uuid.first << ","
           << "UUID:" << title_uuid.second << "}";
        return in;
    }
}
