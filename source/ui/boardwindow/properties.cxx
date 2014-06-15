#include "boardwindow.h"
namespace ui {
    QList<plugin::root *> *BoardWindow::plugins() const {
        return this->_plugins;
    }
    storage::property_storage *BoardWindow::property() const {
        return this->_property;
    }
}
