#include "responsewindow.h"
namespace ui{
    ResponseWindow::ResponseWindow(const QString &title, const QIcon &icon, 
                                   QList<plugin::root *> *plugins, 
                                   storage::property_storage *property, 
                                   QMLWindowBase *parent):TabWindowBase(title,icon,plugins,property,parent){
        this->_loadQMLFile("ResponseWindow.qml");
    }
}
