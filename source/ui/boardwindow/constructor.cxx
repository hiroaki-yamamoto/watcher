#include "boardwindow.h"
namespace ui{
    BoardWindow::BoardWindow(const QString &title,
                             const QIcon &icon,
                             QList<plugin::root *> *plugins,
                             storage::property_storage *property,
                             QMLWindowBase *parent):QMLWindowBase(title,icon,parent){
        this->_plugins=plugins;
        this->_property=property;
        QMLWindowBase::_loadQMLFile("BoardWindow.qml");
        this->_createRelationBetweenSignalsAndSlots();
    }
}
