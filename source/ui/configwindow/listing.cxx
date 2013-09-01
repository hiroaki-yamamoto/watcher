#include <QObject>
#include <QList>
#include <QDebug>

#include <loader/root.h>

#include "configwindow.h"

#include "pluginpanel.h"
#include "setting_default.h"
#include "plugin_loader.h"
#include "themepanel.h"

namespace ui{
    void ConfigDialog::_list_plugins(){
        this->_plugin_list->clear();
        for(plugin::root *root:this->_loader->instances()->toStdList()){
            PluginPanel *p_panel=
                    new PluginPanel(root->title(),root->author(),root->description(),root->icon(),root,
                                    !(this->_property->exists(default_value::setting_default::name_disabled_plugins_uuid())&&
                                      this->_property->get(default_value::setting_default::name_disabled_plugins_uuid()).toList().contains(root->identifier().toString())),
                                    this->_plugin_list);
            connect(p_panel,SIGNAL(enableChanged(bool)),SLOT(_plugin_enabled_changed(bool)));
            (*this->_plugin_list)<<p_panel;
        }
    }
    
    void ConfigDialog::_list_theme_dir(){
        QVector<QDir> dirs;
        if(this->_modified_setting.value(default_value::setting_default::name_theme_root_dir()).type()==QMetaType::QString){
            dirs<<QDir(this->_modified_setting.value(default_value::setting_default::name_theme_root_dir()).toString());
        }else if(this->_property->get(default_value::setting_default::name_theme_root_dir()).type()==QMetaType::QString){
            dirs<<QDir(this->_property->get(default_value::setting_default::name_theme_root_dir()).toString());
        }else{
            qWarning()<<default_value::setting_default::name_theme_root_dir()<<"is invalid type.";
            return;
        }
        qDebug()<<"Theme root directories:"<<dirs;
        this->_theme_list->setThemeRootDirs(dirs);
        if(this->_property->exists(default_value::setting_default::name_theme_selected_dir())){
            if(this->_property->get(default_value::setting_default::name_theme_selected_dir()).type()==QMetaType::QString){
                const QString &&selected_theme_dir_str=this->_property->get(default_value::setting_default::name_theme_selected_dir()).toString();
                if(!selected_theme_dir_str.isEmpty()){
                    const QDir &&selected_theme_dir=selected_theme_dir_str;
                    if(selected_theme_dir.exists()){
                        QDir selected_parent=selected_theme_dir;
                        if(selected_parent.cdUp()){
                            bool root_has_selected=false;
                            for(const QDir &root:dirs) if(selected_parent==root) root_has_selected=true;
                            if(root_has_selected){
                                this->_theme_list->selectDir(selected_theme_dir);
                            }else{
                                qWarning()<<this->objectName()<<": The selected theme is out of the root theme directory.";
                                this->_select_theme_index0();
                            }
                        }else{
                            qWarning()<<this->objectName()<<": parent directory couldn't be found.";
                            this->_select_theme_index0();
                        }
                    }else{
                        qWarning()<<this->objectName()<<": The selected theme directory couldn't be found.";
                        this->_select_theme_index0();
                    }
                }else{
                    qWarning()<<this->objectName()<<": "<<default_value::setting_default::name_theme_selected_dir()<<" in "<<
                                this->_property->objectName()<<" is empty.";
                    this->_select_theme_index0();
                }
            }else{
                qWarning()<<this->objectName()<<": "<<default_value::setting_default::name_theme_selected_dir()<<" in "<<
                            this->_property->objectName()<<" is an invalid types.";
                this->_select_theme_index0();
            }
        }else{
            qWarning()<<this->objectName()<<":"
                     <<default_value::setting_default::name_theme_selected_dir()
                    <<" couldn't be found in "<<this->_property->objectName()<<".";
            this->_select_theme_index0();
        }
    }
    void ConfigDialog::_select_theme_index0(){
        qWarning()<<this->objectName()<<": Select first theme.";
        ui::ThemePanel *panel=qobject_cast<ui::ThemePanel *>((*(this->_theme_list))[0]);
        if(panel!=nullptr){
            panel->setSelected(true);
            this->_clear_selected_theme=false;
            this->_modified_setting[default_value::setting_default::name_theme_selected_dir()]=panel->dir().absolutePath();
        }else{
            qWarning()<<"("<<this->objectName()<<"): The first panel is null.";
        }
    }
}
