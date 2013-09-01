#include "pluginpanel.h"
#include <loader/root.h>
namespace ui{
    PluginPanel::PluginPanel(const QString &title, const QString &author, const QString &description,
                                 const QIcon &icon, plugin::root *plugin_root, 
                                 const bool pluginEnabled, QWidget *parent):QWidget(parent){
        this->_plugin_root=plugin_root;
        this->setupUi(this);
        this->setPluginIcon(icon,QIcon::Normal);
        this->setPluginTitle(title);
        this->setPluginDesc(description);
        this->setPluginEnabled(pluginEnabled);
        this->setPluginAuthor(author);
        this->setPluginVersion(plugin_root->version());
        connect(this->_option,SIGNAL(clicked()),SLOT(optionClicked()));
        connect(this->_enabled,SIGNAL(clicked(bool)),SLOT(setPluginEnabled(bool)));
        connect(this->_enabled,SIGNAL(clicked(bool)),SIGNAL(enableChanged(bool)));
    }
    QString PluginPanel::pluginTitle() const{return this->_pluginTitle->text();}
    QString PluginPanel::pluginDesc() const{return this->_pluginDesc->text();}
    QString PluginPanel::pluginAuthor() const{return this->_author->text();}
    QString PluginPanel::pluginVersion() const{return this->_version->text();}
    void PluginPanel::setPluginTitle(const QString &title){this->_pluginTitle->setText(title);}
    void PluginPanel::setPluginDesc(const QString &desc){this->_pluginDesc->setText(desc);}
    void PluginPanel::setPluginVersion(const QString &version){this->_version->setText(version);}
    bool PluginPanel::pluginEnabled() const{return this->_enabled->isChecked();}
    void PluginPanel::setPluginEnabled(const bool enable){
        this->_enabled->setChecked(enable);
        if(enable){
            this->_option->setEnabled(this->_plugin_root->enable_option());
            this->setPluginIcon(this->_pluginIcon,QIcon::Normal);
        }else{
            this->_option->setEnabled(false);
            this->setPluginIcon(this->_pluginIcon,QIcon::Disabled);
        }
    }
    void PluginPanel::optionClicked(){this->_plugin_root->open_option(this);}
    void PluginPanel::setPluginIcon(const QIcon &icon, const QIcon::Mode mode){
        this->_pluginIcon=icon;
        this->_icon->setPixmap(this->_pluginIcon.pixmap(32,mode));
    }
    void PluginPanel::setPluginAuthor(const QString &author){this->_author->setText(author);}
    
    const plugin::root* PluginPanel::plugin_instance() const{return this->_plugin_root;}
}
