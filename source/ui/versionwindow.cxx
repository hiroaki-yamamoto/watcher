#include <QtQuick/QQuickItem>
#include <QtQml/QQmlContext>

#include <QtWidgets/QApplication>

#include <QFileInfo>
#include <QDir>
#include <QtDebug>
#include <QDesktopServices>

#include "versionwindow.h"
#include "license.h"
#include "property_storage.h"
#include "setting_default.h"
namespace ui{
    VersionWindow::VersionWindow(const QString &title, const QIcon &icon,QMLWindowBase *parent):
        QMLWindowBase(title,icon){
        this->_parent=parent;
        this->rootContext()->setContextProperty("copyright",short_license());
        this->rootContext()->setContextProperty("applicationName",qApp->applicationName());
        this->_loadQMLFile("VersionWindow.qml");
        this->setFlags(Qt::Dialog);
        this->setModality(Qt::ApplicationModal);
        this->setResizeMode(QQuickView::SizeRootObjectToView);
        for(const QString &objName:this->_children.uniqueKeys()){
            if(objName=="body")         connect(this->_children.value(objName),SIGNAL(linkActivated(QString)),SLOT(_linkActivated(QString)));
            else if(objName=="close")   connect(this->_children.value(objName),SIGNAL(clicked()),SLOT(_closeButtonClicked()));
        }
        if(this->property()!=nullptr){
            connect(this->property(),
                    SIGNAL(propertyChanged(QString,QVariant,QVariant)),
                    SLOT(_propertyChanged(QString,QVariant,QVariant)));
        }
    }
    void VersionWindow::_closeButtonClicked(){this->close();}
    void VersionWindow::_propertyChanged(const QString &name, const QVariant &prev, const QVariant &now){
        Q_UNUSED(prev);
    #ifdef EXPERIMENT
        if(name==default_value::setting_default::name_theme_selected_dir()){
            if(now.type()==QMetaType::QString) this->_loadQMLFile(QFileInfo(now.toString(),"VersionWindow.qml"));
            else qWarning()<<this->objectName()<<": Setting key:"<<default_value::setting_default::name_theme_selected_dir()<<" has an invalid value type.";
        }
    #endif
    }
    
    void VersionWindow::_linkActivated(const QString &link){QDesktopServices::openUrl(QUrl(link));}
    QList<plugin::root *> *VersionWindow::plugins() const{return (this->_parent!=nullptr)?this->_parent->plugins():nullptr;}
    storage::property_storage *VersionWindow::property() const{return (this->_parent!=nullptr)?this->_parent->property():nullptr;}
}
