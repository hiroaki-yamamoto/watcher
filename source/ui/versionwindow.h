#pragma once
#include "qml_window_base.h"
namespace ui {
    class VersionWindow : public QMLWindowBase {
        Q_OBJECT
        Q_PROPERTY(bool active READ isActive)
       public:
        VersionWindow(const QString &title, const QIcon &icon,
                      QList<plugin::root *> *plugins,
                      storage::property_storage *property,
                      QMLWindowBase *parent = nullptr);
       private
    slots:
        void _linkActivated(const QString &link);
        void _propertyChanged(const QString &name, const QVariant &prev,
                              const QVariant &now);
        void _closeButtonClicked();
    };
}
