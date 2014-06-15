#pragma once
#include <QString>
#include <QUuid>
#include <QHash>
#include <QPair>
#include <QtQuick/QQuickView>

#include "tabwindow_base.h"
#include "plugin_loader.h"

template <class T>
class QList;

class QJSValue;

namespace storage {
    class property_storage;
}
namespace plugin {
    class root;
    class board;
}

namespace ui {
    class ConfigDialog;
    class BoardWindow;
    class VersionWindow;
    class RootTabContents;
    class RootWindow : public TabWindowBase {
        Q_OBJECT
        Q_PROPERTY(bool active READ isActive)
       public:
        RootWindow(const QString &title, const QIcon &icon,
                   loader::plugin_loader &loader,
                   storage::property_storage &property,
                   QMLWindowBase *parent = nullptr);
       private
    slots:
        void _show_version_window();
        void _config();
        void _go_back();
        void _go_forward();
        void _reloadView();
        void _openBookmark();
        void _import_setting();
        void _export_setting();
        void _property_changed(const QString &key, const QVariant &prev,
                               const QVariant &now);
        void _createRelationBetweenSignalsAndSlots();
        void _plugin_loaded();

        void _topicMode(plugin::board *board);
        void _tabContentStateChanged(const QJSValue &previous,
                                     const QJSValue &current);
        void _tabContentStateChanged();

       private:
        ConfigDialog *_config_dialog;
        VersionWindow *_version;
        BoardWindow *_boardwindow;
        loader::plugin_loader *_loader;
    };
}
