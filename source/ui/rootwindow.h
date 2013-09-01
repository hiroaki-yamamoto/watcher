#pragma once
#include <QString>
#include <QUuid>
#include <QHash>
#include <QPair>
#include <QtQuick/QQuickView>

#include "qml_window_base.h"
#include "plugin_loader.h"

template <class T> class QList;
namespace storage{
    class property_storage;
}
namespace plugin{
    class root;
    class board;
}

namespace ui{
    class ConfigDialog;
    class BoardWindow;
    class VersionWindow;
    class RootTabContents;
    class RootWindow:public QMLWindowBase{
        Q_OBJECT
        Q_PROPERTY(bool active READ isActive)
        public:
            RootWindow(const QString &title,
                       const QIcon &icon,
                       loader::plugin_loader &loader,
                       storage::property_storage &property,
                       QWindow *parent=nullptr
                    );
            QList<plugin::root *> *plugins() const;
            storage::property_storage *property() const;
        private slots:
            void _show_version_window();
            void _config();
            void _go_back();
            void _go_forward();
            void _reloadView();
            void _openBookmark();
            void _import_setting();
            void _export_setting();
            void _property_changed(const QString &key,const QVariant &prev,const QVariant &now);
            void _createRelationBetweenSignalsAndSlots();
            void _plugin_loaded();
            
            void _topicMode(plugin::board *board);
            void _tabContentStateChanged(const QVariant &previous,const QVariant &current);
            void _tabContentStateChanged();
        private:
            RootTabContents *_getCurrentTabContent();
            ConfigDialog *_config_dialog;
            VersionWindow *_version;
            BoardWindow *_boardwindow;
            loader::plugin_loader *_loader;
            QHash<QPair<QString,QUuid>,RootTabContents *> _tabcontents;
            storage::property_storage *_property;
    };
}
