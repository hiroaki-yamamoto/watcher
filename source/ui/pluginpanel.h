#pragma once
#include <ui_pluginpanel.h>
#include <QtWidgets/QtWidgets>
#include <QIcon>

class QString;
namespace plugin{
    class root;
}
namespace ui{
   class PluginPanel:public QWidget,private Ui::pluginpanel{
           Q_OBJECT
           Q_PROPERTY(QString pluginTitle READ pluginTitle WRITE setPluginTitle)
           Q_PROPERTY(QString pluginDesc READ pluginDesc WRITE setPluginDesc)
           Q_PROPERTY(QString pluginVersion READ pluginVersion WRITE setPluginVersion)
           Q_PROPERTY(QString pluginAuthor READ pluginAuthor WRITE setPluginAuthor)
           Q_PROPERTY(bool pluginEnabled READ pluginEnabled WRITE setPluginEnabled)
       public:
           PluginPanel(const QString &title,const QString &author,const QString &description,
                       const QIcon &icon,plugin::root *plugin_root,const bool pluginEnabled,QWidget *parent=nullptr);
           bool pluginEnabled() const;
           QString pluginTitle() const;
           QString pluginDesc() const;
           QString pluginAuthor() const;
           QString pluginVersion() const;
           const plugin::root* plugin_instance() const;
       signals:
           void enableChanged(bool enabled);
       public slots:
           void setPluginTitle(const QString &title);
           void setPluginDesc(const QString &desc);
           void setPluginVersion(const QString &version);
           void setPluginEnabled(const bool enable);
           void setPluginIcon(const QIcon &icon,const QIcon::Mode mode);
           void setPluginAuthor(const QString &author);
       private slots:
           void optionClicked();
       private:
           plugin::root *_plugin_root;
           QIcon _pluginIcon;
   };
}
