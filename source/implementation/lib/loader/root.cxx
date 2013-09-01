#include "root.h"
namespace plugin{
    QObject *root::this_object(){return qobject_cast<QObject *>(this);}
    void root::closing(){}
    void root::open_option(QWidget *sender){}
}
