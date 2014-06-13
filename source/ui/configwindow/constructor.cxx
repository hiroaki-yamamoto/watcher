#include <QList>

#include "configwindow.h"
#include "qml_window_base.h"

#include <cstdio>
#include <cassert>
namespace ui {
    ConfigDialog::ConfigDialog(storage::property_storage *property,
                               loader::plugin_loader *loader,
                               QMLWindowBase *QMLParent, QWidget *parent)
        : QDialog(parent) {
        assert(property != nullptr);
        this->setupUi(this);
        this->_parent = QMLParent;
        this->_loader = loader;
        this->_property = property;
        this->_clear_disabled_plugins_list = this->_clear_selected_theme =
            false;
        this->_create_filechooser();

        this->_create_LayoutsInGeneralPanel();

        // Search themes and plugins.
        this->_list_theme_dir();
        this->_list_plugins();
        this->_createRelationUIandSetting();

        // Set properties.
        this->_connectSignals();
        this->updateProperties();

        // Select First column.
        this->configMenu->item(0)->setSelected(true);
    }
}
