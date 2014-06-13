#include "boardwindow.h"
#include "responsewindow.h"
namespace ui {
    BoardWindow::BoardWindow(const QString &title, const QIcon &icon,
                             QList<plugin::root *> *plugins,
                             storage::property_storage *property,
                             QMLWindowBase *parent)
        : TabWindowBase(title, icon, plugins, property, parent) {
        this->_loadQMLFile("BoardWindow.qml");
        this->_createRelationBetweenSignalsAndSlots();
        this->_responseWindow = new ResponseWindow(
            tr("Response View"), this->icon(), this->plugins(),
            this->property(), this->parent());
    }
}
