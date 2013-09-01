#pragma once
#include <loader/root.h>
#include <QUuid>
#include <QString>
#include <QIcon>
#include <random>

namespace test{
    class root:public plugin::root{
            Q_OBJECT
            Q_PLUGIN_METADATA(IID "net.hysoft.watcher.plugin" FILE "root.json")
            Q_INTERFACES(plugin::root)
        public:
            root(QObject *parent=nullptr);
            ~root();
            void get_categories();
            bool enable_option() const;
            const QString &version() const;
            const QIcon &icon() const;
        private:
            std::mt19937 *_mt;
            const QString _ver="Testing";
            const QIcon _icon=QIcon::fromTheme("applications-development");
    };
}
