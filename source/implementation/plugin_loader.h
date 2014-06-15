#pragma once
#include <QString>
#include <QObject>
template <class T>
class QList;
class QPluginLoader;
namespace plugin {
    class root;
}

namespace loader {
    class plugin_loader : public QObject {
        Q_OBJECT
       public:
        plugin_loader(const QString &root_dir,
                      const QString &objName = QString(),
                      QObject *parent = nullptr);
        ~plugin_loader();
        QString root_dir() const;
        void setRootDir(const QString &root_dir);
        bool load();
        bool unload();
        bool reload(const QString &root_dir);
        bool reload();
        QList<plugin::root *> *instances() const;
    signals:
        void loaded();

       private:
        QList<QPluginLoader *> *_loaders;
        QList<plugin::root *> *_instances;
        QString _root_dir;
    };
}
