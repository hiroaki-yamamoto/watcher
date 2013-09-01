#include <QtWidgets/QApplication>
#include <QDir>
#include <QString>
#include <QMultiHash>
#include "setting_default.h"
namespace default_value{
    setting_default::setting_default(const int element_size, QObject *parent):storage::property_storage(element_size,"default value",parent){
        this->__data.insert(default_value::setting_default::name_plugin_root_dir(),
                  default_value::setting_default::watcher_etc_dir()+QDir::separator()+"plugins");
        this->__data.insert(default_value::setting_default::name_theme_root_dir(),
                  default_value::setting_default::watcher_etc_dir()+QDir::separator()+"themes");
        this->__data.insert(default_value::setting_default::name_display_thumbnails(),true);
        this->__data.insert(default_value::setting_default::name_display_anchors(),true);
        this->__data.insert(default_value::setting_default::name_disabled_plugins_uuid(),QVariantList());
        this->__data.insert(default_value::setting_default::name_theme_selected_dir(),
                            QDir(this->get(default_value::setting_default::name_theme_root_dir()).toString()).absoluteFilePath("default"));
    }
    bool setting_default::readOnly(){return true;}
    
    const QString setting_default::name_plugin_root_dir(){return "PluginRootDir";}
    const QString setting_default::name_theme_root_dir(){return "ThemeRootDir";}
    const QString setting_default::name_display_thumbnails(){return "DisplayThumbnails";}
    const QString setting_default::name_display_anchors(){return "DisplayAnchors";}
    const QString setting_default::name_theme_selected_dir(){return "SelectedThemeDirectory";}
    const QString setting_default::name_disabled_plugins_uuid(){return "DisabledPlugins";}
    const QFileInfo setting_default::setting_path(){
        return QFileInfo(setting_default::watcher_etc_dir()+QDir::separator()+"setting");
    }
    const QString setting_default::default_theme_name(){return "default";}
    const QString setting_default::watcher_etc_dir(){
    #ifdef DEBUG
        return qApp->applicationDirPath();
    #else
        return QDir::homePath()+QDir::separator()+"watcher";
    #endif
    }
    const bool setting_default::watcher_plugin_enable_flag(){return true;}
}
