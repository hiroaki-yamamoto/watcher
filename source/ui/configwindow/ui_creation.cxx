#include<QtWidgets/QHBoxLayout>
#include<QtWidgets/QVBoxLayout>

#include "configwindow.h"

#include "filechooser.h"

#include "property_storage.h"
#include "setting_default.h"
namespace ui{
    void ConfigDialog::_create_LayoutsInGeneralPanel(){
        //Create Widgets to place layouts.
        QWidget     *pluginLayoutWidget=new QWidget(this->generalConfig),
                    *themeLayoutWidget=new QWidget(this->generalConfig);
        //The layouts to be placed on the widget described above.
        QHBoxLayout *pluginLayout=new QHBoxLayout(pluginLayoutWidget),
                    *themeLayout=new QHBoxLayout(themeLayoutWidget);
        
        //Default margins are too large. (By default, 11 pixels in all directions.)
        pluginLayout->setContentsMargins(0,0,0,0);
        themeLayout->setContentsMargins(0,0,0,0);
        
        //Place label and filechooser onto the layouts.
        pluginLayout->addWidget(this->_pluginPathLabel);
        pluginLayout->addWidget(this->_plugin_dir);
        themeLayout->addWidget(this->_themePathLabel);
        themeLayout->addWidget(this->_theme_dir);
        
        //Set the layout to the corresponding layout widget.
        pluginLayoutWidget->setLayout(pluginLayout);
        themeLayoutWidget->setLayout(themeLayout);
        
        //Set size policy of the labels to deny stretching.
        this->_pluginPathLabel->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Preferred);
        this->_themePathLabel->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Preferred);
        
        //Set background colors of plugin list and theme list. (Default color is dark...)
        this->_plugin_list->setBackgroundRole(QPalette::Base);
        this->_theme_list->setBackgroundRole(QPalette::Base);
        //Create layout of generalConfig.
        QVBoxLayout *generalLayout=new QVBoxLayout(this->generalConfig);
        //Place widgets to the layout.
        generalLayout->addWidget(this->_generalLabel);
        generalLayout->addWidget(this->_pathLabel);
        generalLayout->addWidget(pluginLayoutWidget);
        generalLayout->addWidget(themeLayoutWidget);
        generalLayout->addStretch();
        
        //Set the layout to generalConfig.
        this->generalConfig->setLayout(generalLayout);
    }
    void ConfigDialog::_create_filechooser(){
        this->_plugin_dir=new ui::FileChooser(
                    QFileInfo(this->_property->get(default_value::setting_default::name_plugin_root_dir()).toString()),
                    ui::FileChooser::Dir,
                    "Plugin Root Directory",
                    this
                    );
        this->_theme_dir=new ui::FileChooser(
                    QFileInfo(this->_property->get(default_value::setting_default::name_theme_root_dir()).toString()),
                    ui::FileChooser::Dir,
                    "Theme Root Directory",
                    this
                    );
    }
}
