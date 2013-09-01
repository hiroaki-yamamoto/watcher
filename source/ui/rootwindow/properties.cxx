#include <QList>

#include <loader/root.h>
#include "rootwindow.h"
#include "property_storage.h"
namespace ui{
    QList<plugin::root *>       *RootWindow::plugins()  const   {return this->_loader->instances();}
    storage::property_storage   *RootWindow::property() const   {return this->_property;}
}
