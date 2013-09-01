#pragma once
#include <QtWidgets/QMessageBox>
#include <memory>
#include <ui_configwindow.h>

namespace storage{class property_storage;}
namespace plugin{class root;}
namespace loader{class plugin_loader;}
class QAbstractItemModel;
template<class T> class QList;
template<class K,class V> class QHash;
namespace ui{
    class FileChooser;
    class ThemePanel;
    class QMLWindowBase;
    class ConfigDialog:public QDialog,private Ui::ConfigDialog_template{
            Q_OBJECT
        public:
            ConfigDialog(storage::property_storage *property,
                         loader::plugin_loader *loader,QMLWindowBase *QMLParent=nullptr,QWidget *parent=nullptr);
        public slots:
            void updateProperties();
            int exec();
        protected:
            void closeEvent(QCloseEvent *event);
        private:
            storage::property_storage *_property;
            loader::plugin_loader *_loader;
            FileChooser *_plugin_dir,*_theme_dir;
            QHash<QString,QWidget *> _setting_object;
            QHash<QString,QVariant> _modified_setting;
            QMLWindowBase *_parent;
            bool _clear_disabled_plugins_list;
            bool _clear_selected_theme;
            
            void _show_copy_completed(const QString &old_dir);
            void _show_copy_failed(const QList<QFileInfo> &not_copied);
            void _show_not_found();
            void _show_permission_denied();
            void _show_remove_completed(const QDir &old_dir);
            void _show_remove_failed(const QDir &old_dir);
            QMessageBox::StandardButton _show_confirm_old_dir_removal();
            QMessageBox::StandardButton _show_copy_confirm();
            /*This function shows copy confirmation dialog and copy/move files in previous.
             *When copying/moving has succeeded, this function returns true.
             *Otherwise, returns false.
             */
            bool _confirm_and_copy_move(QDir previous, const QDir current,bool *actual_copied=nullptr);

        private slots:
            void _list_plugins();
            void _list_theme_dir();
            void _create_filechooser();
            void _create_LayoutsInGeneralPanel();
            void _createRelationUIandSetting();
            void _connectSignals();
            void _changePage(QListWidgetItem *current,QListWidgetItem *previous);
            void _pluginFilePathChanged(const QFileInfo &previous, const QFileInfo &now, bool &cancel);
            void _themeFilePathChanged(const QFileInfo &previous, const QFileInfo &now, bool &cancel);
            void _display_thumbnails_checked_changed(const bool checked);
            void _display_anchor_checked_changed(const bool checked);
            void _theme_selection_dir_changed(const ThemePanel *panel);
            void _setVariantToUI(QWidget *ui,const QVariant &value);
            void _plugin_enabled_changed(bool enabled);
            void _select_theme_index0();
    };
}
