#pragma once
#include <QFileInfo>
#include <QString>
#include <property_storage.h>
namespace default_value {
    class setting_default : public storage::property_storage {
        Q_OBJECT
       public:
        setting_default(const int element_size = 10, QObject *parent = nullptr);
        bool readOnly();
        static const QString name_plugin_root_dir();
        static const QString name_theme_root_dir();
        static const QString name_display_thumbnails();
        static const QString name_display_anchors();
        static const QString name_theme_selected_dir();
        static const QString default_theme_name();
        static const QFileInfo setting_path();
        static const QString watcher_etc_dir();
        static const QString name_disabled_plugins_uuid();
        static const bool watcher_plugin_enable_flag();
    };
}
