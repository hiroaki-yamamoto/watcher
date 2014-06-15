#pragma once
#include <loader/root.h>
#include <QHash>
#include <QUrl>
#include <QByteArray>
#include <QString>
#include <QUuid>
#include <QIcon>
#include <random>
namespace plugin {
    class category;
}
class QNetworkAccessManager;
class QNetworkDiskCache;
namespace yotsuba {
    class root : public plugin::root {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID "net.hysoft.watcher.plugin" FILE "root.json")
        Q_INTERFACES(plugin::root)
       public:
        root();
        ~root();
        bool enable_option() const;
        const QString &version() const;
        const QIcon &icon() const;
        const quint32 random_number();
       public
    slots:
        void get_categories();

       private:
        std::mt19937 *_mt;
        QString _ver;
        const QIcon _icon = QIcon::fromTheme("application-x-executable");
        QNetworkAccessManager *_accessManager;
        QNetworkDiskCache *_cache;
    };
}
