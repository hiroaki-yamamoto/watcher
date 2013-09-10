#pragma once
#include <QtQuick/QQuickView>

#include <QUrl>
#include <QList>
#include <QMultiHash>
#include <QString>
#include <QFileInfo>

class QObject;
template <class T> class QList;

namespace storage{
    class property_storage;
}
namespace plugin{
    class root;
}

namespace ui{
    class QMLWindowBase:public QQuickView{
            Q_OBJECT
            Q_PROPERTY(QMLWindowBase *parent READ parent WRITE setParent)
            Q_PROPERTY(QList<plugin::root *>* plugins READ plugins)
            Q_PROPERTY(storage::property_storage* property READ property)
        public:
            QMLWindowBase(const QString &title,
                          const QIcon &icon,
                          QMLWindowBase *parent=nullptr);
            virtual QList<plugin::root *> *plugins() const=0;
            virtual storage::property_storage *property() const=0;
            QMLWindowBase *parent() const;
        public slots:
            void setSource(const QUrl &new_source);
            void exitApplication();
            void restartApplication();
            void setParent(QMLWindowBase *parent);
        protected:
            virtual QFileInfo _getQMLFileFromSelectedThemes(const QString &file);
            /*
             *Key: ObjectName, Value: object itself.
             *If the key is empty, the key will be "undefined".
             *In addition to it, the multi values of "undefined" is acceptable. You'll need to consider about this.
             */
            QHash<QString,QObject *> _children;
        protected slots:
            virtual void _loadQMLFile(const QFileInfo &info);
            virtual void _loadQMLFile(const QString &file);
            virtual void _reloadQMLFile();
        private slots:
            void _parentVisibleChanged(const bool visible);
        private:
            QString _filename;
            QMLWindowBase *_parent;
            void _collectChildren();
    };
}
