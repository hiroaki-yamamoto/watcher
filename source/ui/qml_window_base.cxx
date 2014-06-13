#include <QList>
#include <QObject>
#include <QDir>

#include <QDebug>
#include <QProcess>

#include <QtQuick/QQuickItem>
#include <QtQml/QQmlContext>
#include <QtQml/QQmlEngine>

#include <QtWidgets/QMessageBox>
#include <QtWidgets/QApplication>

#include <loader/root.h>

#include "qml_window_base.h"
#include "property_storage.h"
#include "setting_default.h"
namespace ui {
    QMLWindowBase::QMLWindowBase(const QString &title, const QIcon &icon,
                                 QList<plugin::root *> *plugins,
                                 storage::property_storage *property,
                                 QMLWindowBase *parent)
        : QQuickView(nullptr) {
        this->setObjectName(title);
        this->setTitle(title);
        this->setIcon(icon);
        this->_parent = parent;
        this->_plugins = plugins;
        this->_property = property;
        if (this->_parent != nullptr)
            connect(this->_parent, SIGNAL(visibleChanged(bool)),
                    SLOT(_parentVisibleChanged(bool)));
    }
    QMLWindowBase *QMLWindowBase::parent() const { return this->_parent; }
    QFileInfo QMLWindowBase::_getQMLFileFromSelectedThemes(
        const QString &file) {
        QFileInfo info = QFileInfo();
        const QString &&selected_theme =
            default_value::setting_default::name_theme_selected_dir();
        const QString &&name_theme_root =
            default_value::setting_default::name_theme_root_dir();

        if (this->property()->exists(selected_theme) &&
            this->property()->get(selected_theme).type() ==
                QMetaType::QString &&
            !this->property()->get(selected_theme).toString().isEmpty()) {
            info.setFile(QDir(this->property()->get(selected_theme).toString()),
                         file);
        } else if (this->property()->exists(name_theme_root) &&
                   this->property()->get(name_theme_root).type() ==
                       QMetaType::QString) {
            info.setFile(
                QDir(this->property()->get(name_theme_root).toString()),
                default_value::setting_default::default_theme_name() +
                    QDir::separator() + file);
        }
        return info;
    }

    void QMLWindowBase::_loadQMLFile(const QFileInfo &info) {
        this->setFlags(Qt::Window);
        this->setResizeMode(QQuickView::SizeRootObjectToView);

        if (info.exists()) {
            this->setSource(QUrl::fromLocalFile(info.absoluteFilePath()));
            this->_filename = info.fileName();
        } else {
            QMessageBox::critical(
                nullptr, tr("UI Setting is invalid."),
                tr("The specified theme directory:%1 couldn't be found.\n"
                   "Running as faisafe mode.").arg(info.absoluteFilePath()));
            this->setTitle(this->title() + tr(" (Failsafe mode)"));
            this->setSource(QUrl("qrc:///themes/failsafe/" + info.fileName()));
        }
        this->setMinimumSize(this->sizeHint());
        this->rootContext()->setContextProperty("window", this);
        this->rootContext()->setContextProperty("property", this->property());
        emit this->loaded();
    }
    void QMLWindowBase::_loadQMLFile(const QString &file) {
        QFileInfo info = this->_getQMLFileFromSelectedThemes(file);
        this->_loadQMLFile(info);
    }

    void QMLWindowBase::setSource(const QUrl &new_source) {
        QQuickView::setSource(new_source);
        this->_collectChildren();
    }

    void QMLWindowBase::_collectChildren() {
        this->_children.clear();
        for (QObject *object : this->rootObject()->findChildren<QObject *>())
            this->_children.insertMulti(object->objectName(), object);
    }
    void QMLWindowBase::_reloadQMLFile() {
        QFileInfo info = this->_getQMLFileFromSelectedThemes(this->_filename);
        this->_loadQMLFile(info);
    }
    void QMLWindowBase::exitApplication() {
        this->close();
        qApp->quit();
        qDebug() << "Application Exit.";
    }
    void QMLWindowBase::restartApplication() {
        this->exitApplication();
        QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
    }
    void QMLWindowBase::_parentVisibleChanged(const bool visible) {
        if (!visible) this->setVisible(false);
    }
    void QMLWindowBase::setParent(QMLWindowBase *parent) {
        if (this->_parent != nullptr)
            this->_parent->disconnect(SIGNAL(visibleChanged(bool)), this,
                                      SLOT(_parentVisibleChanged(bool)));
        this->_parent = parent;
        if (this->_parent != nullptr)
            connect(this->_parent, SIGNAL(visibleChanged(bool)),
                    SLOT(_parentVisibleChanged(bool)));
    }
    QList<plugin::root *> *QMLWindowBase::plugins() const {
        return this->_plugins;
    }
    storage::property_storage *QMLWindowBase::property() const {
        return this->_property;
    }
}
