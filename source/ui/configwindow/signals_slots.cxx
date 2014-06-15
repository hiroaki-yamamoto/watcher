#include <loader/root.h>
#include <QUuid>
#include <QFileInfo>
#include <QFile>
#include <QList>
#include <QtDebug>

#include "configwindow.h"

#include "filechooser.h"
#include "themepanel.h"

#include "property_storage.h"
#include "setting_default.h"
#include "plugin_loader.h"
#include "pluginpanel.h"
namespace ui {
    void ConfigDialog::_connectSignals() {
        connect(this->configMenu, SIGNAL(currentItemChanged(QListWidgetItem *,
                                                            QListWidgetItem *)),
                SLOT(_changePage(QListWidgetItem *, QListWidgetItem *)));
        connect(this->_plugin_dir,
                SIGNAL(filePathChanged(QFileInfo, QFileInfo, bool &)),
                SLOT(_pluginFilePathChanged(QFileInfo, QFileInfo, bool &)));
        connect(this->_theme_dir,
                SIGNAL(filePathChanged(QFileInfo, QFileInfo, bool &)),
                SLOT(_themeFilePathChanged(QFileInfo, QFileInfo, bool &)));
        connect(this->displayThumbnailCheckbox, SIGNAL(clicked(bool)),
                SLOT(_display_thumbnails_checked_changed(bool)));
        connect(this->anchorCheckbox, SIGNAL(clicked(bool)),
                SLOT(_display_anchor_checked_changed(bool)));
        connect(this->_theme_list, SIGNAL(themeSelected(const ThemePanel *)),
                SLOT(_theme_selection_dir_changed(const ThemePanel *)));
        connect(this->_loader, SIGNAL(loaded()), SLOT(_list_plugins()));
    }

    void ConfigDialog::_changePage(QListWidgetItem *current,
                                   QListWidgetItem *previous) {
        Q_UNUSED(previous);
        for (int index = 0; index < this->configMenu->children().size();
             index++)
            if (current == this->configMenu->item(index)) {
                this->configPages->setCurrentIndex(index);
                break;
            }
    }
    void ConfigDialog::_pluginFilePathChanged(const QFileInfo &previous,
                                              const QFileInfo &now,
                                              bool &cancel) {
        bool actual_copied = false;
        bool &&succeeded = this->_confirm_and_copy_move(
            previous.absoluteFilePath(), now.absoluteFilePath(),
            &actual_copied);
        cancel = !succeeded;
        if (succeeded) {
            this->_clear_disabled_plugins_list = !actual_copied;
            this->_modified_setting
                [default_value::setting_default::name_plugin_root_dir()] =
                now.filePath();
            QMessageBox::information(this, tr("Applying information"),
                                     tr("To apply this change, you need to "
                                        "close this configuration dialog."));
        }
    }
    QMessageBox::StandardButton ConfigDialog::_show_copy_confirm() {
        return QMessageBox::question(
            this, tr("Confirm"),
            tr("Do you want to copy the files in the previous directory?"),
            QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel,
            QMessageBox::Yes);
    }

    QMessageBox::StandardButton ConfigDialog::_show_confirm_old_dir_removal() {
        return QMessageBox::question(
            this, tr("Copying completed"),
            tr("Copying completed. Do you want to remove old directory?"),
            QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }

    void ConfigDialog::_show_remove_completed(const QDir &old_dir) {
        QMessageBox::information(
            this, tr("Removal Completed"),
            tr("Removing %1 completed.").arg(old_dir.absolutePath()),
            QMessageBox::Ok);
    }
    void ConfigDialog::_show_remove_failed(const QDir &old_dir) {
        QMessageBox::warning(
            this, tr("Removal Failed"),
            tr("Removing %1 failed. The contents in the directory may be lost!")
                .arg(old_dir.absolutePath()),
            QMessageBox::Ok);
    }

    void ConfigDialog::_show_not_found() {
        QMessageBox::critical(this, tr("Moving files failed"),
                              tr("The source directory or the specified "
                                 "destination directory doesn't exists."),
                              QMessageBox::Ok);
    }

    void ConfigDialog::_show_copy_completed(const QString &old_dir) {
        QMessageBox::information(
            this, tr("Copying completed"),
            tr("Copying %1 and its contents completed.").arg(old_dir),
            QMessageBox::Ok);
    }
    void ConfigDialog::_show_copy_failed(const QList<QFileInfo> &not_copied) {
        QString paths;
        for (const QFileInfo &path : not_copied)
            paths += QString("%1\n").arg(path.absoluteFilePath());
        paths.remove(paths.size() - 1, 1);
        QMessageBox::information(
            this, tr("Copying failed"),
            tr("Copying the contents failed.<br />"
               "The following contents were not copied.<br />"
               "%1").arg(paths));
    }
    void ConfigDialog::_show_permission_denied() {
        QMessageBox::critical(
            this, tr("Moving files failed"),
            tr("The source directory or the specified destination directory "
               "doesn't have readble permission."),
            QMessageBox::Ok);
    }

    void ConfigDialog::_themeFilePathChanged(const QFileInfo &previous,
                                             const QFileInfo &now,
                                             bool &cancel) {
        bool actual_copied = false;
        bool succeeded = this->_confirm_and_copy_move(
            previous.absoluteFilePath(), now.absoluteFilePath(),
            &actual_copied);
        cancel = !succeeded;
        if (succeeded) {
            this->_clear_selected_theme = !actual_copied;
            this->_modified_setting
                [default_value::setting_default::name_theme_root_dir()] =
                now.filePath();
            this->_list_theme_dir();
            QMessageBox::information(
                this, tr("Select the theme"),
                tr("Theme Root Dir has been changed."
                   "Choosing the theme form Theme Tab is needed."
                   "If the theme is choosen, Fail-Safe Theme will be applied."),
                QMessageBox::Ok);
        }
    }
    void ConfigDialog::_display_thumbnails_checked_changed(const bool checked) {
        this->_modified_setting
            [default_value::setting_default::name_display_thumbnails()] =
            QVariant(checked);
    }
    void ConfigDialog::_display_anchor_checked_changed(const bool checked) {
        this->_modified_setting
            [default_value::setting_default::name_display_anchors()] =
            QVariant(checked);
    }
    void ConfigDialog::_theme_selection_dir_changed(const ThemePanel *panel) {
        this->_clear_selected_theme = false;
        this->_modified_setting
            [default_value::setting_default::name_theme_selected_dir()] =
            panel->dir().absolutePath();
    }
    void ConfigDialog::_plugin_enabled_changed(bool enabled) {
        PluginPanel *sender_panel =
            qobject_cast<decltype(sender_panel)>(this->sender());
        QVariantList &&disabled_plugin_list =
            this->_modified_setting
                [default_value::setting_default::name_disabled_plugins_uuid()]
                    .toList();
        const QVariant &&id =
            QVariant(sender_panel->plugin_instance()->identifier());
        if (!enabled) {
            if (!disabled_plugin_list.contains(id)) disabled_plugin_list << id;
        } else {
            if (disabled_plugin_list.contains(id))
                disabled_plugin_list.removeAll(id);
        }
        this->_modified_setting
            [default_value::setting_default::name_disabled_plugins_uuid()] =
            disabled_plugin_list;
        qDebug() << this->_modified_setting[default_value::setting_default::
                                                name_disabled_plugins_uuid()];
    }
}
