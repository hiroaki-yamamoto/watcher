#pragma once
#include <loader/root.h>
#include <QUuid>
#include <QString>
#include <QIcon>

namespace test{
    class root:public plugin::root{
            Q_OBJECT
            Q_PLUGIN_METADATA(IID "net.hysoft.watcher.plugin" FILE "root.json")
            Q_INTERFACES(plugin::root)
        public:
            root(QObject *parent=nullptr);
            bool enable_option() const;
            const QString &version() const;
            const QIcon &icon() const;
        public slots:
            void get_categories();
        private:
            const QString _ver="Testing";
            const QIcon _icon=QIcon::fromTheme("applications-development");
    };
}
