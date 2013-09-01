#include <QCloseEvent>
#include <QtDebug>
#include <QtWidgets/QMessageBox>

#include "property_storage.h"
#include "setting_default.h"
#include "configwindow.h"
#include "qml_window_base.h"

namespace ui{
    void ConfigDialog::closeEvent(QCloseEvent *event){
    #ifndef EXPERIMENT
        bool require_reboot=false;
    #endif
        if(this->_clear_disabled_plugins_list){
            this->_property->set(default_value::setting_default::name_disabled_plugins_uuid(),QVariantList());
            this->_modified_setting.remove(default_value::setting_default::name_disabled_plugins_uuid());
            this->_clear_disabled_plugins_list=false;
        }
        if(this->_clear_selected_theme){
            this->_property->set(default_value::setting_default::name_theme_selected_dir(),QString());
            this->_modified_setting.remove(default_value::setting_default::name_theme_selected_dir());
            this->_clear_selected_theme=false;
        }
        for(const QString &name:this->_modified_setting.uniqueKeys()){
    #ifndef EXPERIMENT
            if(name==default_value::setting_default::name_theme_selected_dir()) require_reboot=true;
    #endif
            this->_property->set(name,this->_modified_setting[name]);
        }
        this->_modified_setting.clear();
        event->accept();
    #ifndef EXPERIMENT
        if(require_reboot){
            QMessageBox::StandardButton &&result=QMessageBox::question(this,tr("Setting modification restarting required"),
                                                                       tr("To apply the changes needs restarting this application.\n"
                                                                          "Do you want to restart it now?"),QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
            switch(result){
               case QMessageBox::Yes:
                    if(this->_parent!=nullptr) this->_parent->restartApplication();
                    else qWarning()<<"Restarting failed. QMLWindowBase parent couldn't be found!";
                    break;
               default: break;
            }
        }
    #endif
    }
}
