#include "response.h"
namespace plugin {
    QObject *response::this_object(){return qobject_cast<QObject *>(this);}
}
