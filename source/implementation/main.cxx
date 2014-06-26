#include <QtWidgets/QApplication>
#include <QtDebug>
#include <QDir>
#include <QPluginLoader>
#include <QStringList>
#include <QList>

// version is made by create_version. It is a bash script to retrieve git
// commit.
#include <version>

#include "rootwindow.h"
#include "setting_loader.h"
#include "setting_default.h"
#include "plugin_loader.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    app.setApplicationName("Watcher");
    app.setApplicationVersion(version);

    qDebug() << "Version:" << app.applicationVersion();

    loader::setting_loader setting(
        default_value::setting_default::setting_path().filePath(), 5,
        "Watcher core setting");
    setting.read();
    QString &&plugin_root_dir =
        setting.storage()
            [default_value::setting_default::name_plugin_root_dir()].toString();
    loader::plugin_loader plugin_finder(plugin_root_dir, "Plugin Loader");
    qDebug() << "Plugin Dir: " << plugin_root_dir;
    plugin_finder.load();

    ui::RootWindow *window = new ui::RootWindow(
        QObject::tr("Watcher"), QIcon(), plugin_finder, setting.storage());
    window->setObjectName("RootWindow");
    window->show();
    int exit_code = app.exec();
    window->deleteLater();
    setting.write();
    plugin_finder.unload();
    return exit_code;
}
