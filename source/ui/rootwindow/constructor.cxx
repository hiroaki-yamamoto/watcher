#include <QUuid>
#include <QtQml/QQmlEngine>
#include <QtWidgets/QApplication>

#include <loader/root.h>

#include "rootwindow.h"
#include "configwindow.h"
#include "versionwindow.h"
#include "boardwindow.h"
namespace ui{
    RootWindow::RootWindow(const QString &title, 
                               const QIcon &icon, 
                               loader::plugin_loader &loader, 
                               storage::property_storage &property, 
                               QWindow *parent):QMLWindowBase(title,icon,parent){
        this->_loader=&loader;
        this->_property=&property;
        this->_config_dialog=new ConfigDialog(this->_property,this->_loader,this);
        this->_version=new VersionWindow("About",this->icon(),this);
        this->_boardwindow=new BoardWindow("TopicView",this->icon(),this->_loader->instances(),this->_property,this);
        this->_loadQMLFile("RootWindow.qml");
        this->_createRelationBetweenSignalsAndSlots();
        this->_plugin_loaded();
        if(this->_children.contains("bookmark")) this->_children["bookmark"]->setProperty("enabled",false);
        connect(this->engine(),SIGNAL(quit()),SLOT(exitApplication()));
    }
}
