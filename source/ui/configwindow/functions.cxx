#include "configwindow.h"
#include <QtWidgets/QApplication>
#include <QtDebug>

#include <property_storage/property_storage.h>
#include <logging/logging.h>
#include <setting_default.h>
#include <QVariant>

using namespace logging;
namespace ui {
    int ConfigDialog::exec() {
        this->_modified_setting
            [default_value::setting_default::name_disabled_plugins_uuid()] =
            this->_property->get(
                default_value::setting_default::name_disabled_plugins_uuid());
        int ret = QDialog::exec();
        this->close();
        return ret;
    }
    bool ConfigDialog::_confirm_and_copy_move(QDir previous, const QDir current,
                                              bool *actual_copied) {
        switch (this->_show_copy_confirm()) {
            case QMessageBox::Yes: {
                if (!previous.exists() || !current.exists()) {
                    this->_show_not_found();
                    if (actual_copied != nullptr) (*actual_copied) = false;
                    return false;
                }
                if (!previous.isReadable() || !current.isReadable()) {
                    this->_show_permission_denied();
                    if (actual_copied != nullptr) (*actual_copied) = false;
                    return false;
                }
                QList<QFileInfo> not_copied;
                bool copy_failed = false;
                for (const QFileInfo &old_info : previous.entryInfoList(
                         QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot |
                         QDir::Readable)) {
                    if (QFile::copy(
                            old_info.absoluteFilePath(),
                            current.absoluteFilePath(old_info.fileName())))
                        qDebug() << this
                                 << "Copied:" << old_info.absoluteFilePath()
                                 << " -> " << current.absoluteFilePath(
                                                  old_info.fileName());
                    else {
                        qWarning() << this
                                   << "Copying:" << old_info.absoluteFilePath()
                                   << " -> "
                                   << current.filePath(old_info.fileName())
                                   << " failed.";
                        copy_failed = true;
                        not_copied << old_info;
                    }
                }
                if (not_copied.size() == 0) {
                    if (this->_show_confirm_old_dir_removal() ==
                        QMessageBox::Yes) {
                        if (previous.removeRecursively())
                            this->_show_remove_completed(previous);
                        else
                            this->_show_remove_failed(previous);
                    } else
                        this->_show_copy_completed(previous.absolutePath());
                } else
                    this->_show_copy_failed(not_copied);
                if (actual_copied != nullptr) (*actual_copied) = !copy_failed;
            } break;
            case QMessageBox::Cancel:
                if (actual_copied != nullptr) (*actual_copied) = false;
                return false;
            case QMessageBox::No:
            default:
                if (actual_copied != nullptr) (*actual_copied) = false;
                break;
        }
        return true;
    }
}
