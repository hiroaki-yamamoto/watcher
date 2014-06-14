#include "tabcontents_base.h"
#include "tabwindow_base.h"
#include <QtDebug>
#include <QtQuick/QQuickItem>
#include <QUuid>
#include <QtQml/QJSValue>
#include <logging/logging.h>

using namespace logging;
namespace ui {
    TabContentsBase::TabContentsBase(const QString &title, const QUuid &uuid,
                                     TabWindowBase *parent)
        : QObject(parent) {
        this->setObjectName(uuid.toString());
        if (parent == nullptr) {
            qWarning() << "Tab" << qMakePair(title, uuid)
                       << "parent=null is not allowed.";
            this->deleteLater();
            return;
        }
        this->_parentWindow = parent;
        this->_parentTab = nullptr;
        // If adding tab is failed, RootTabContents should be deleted.
        if ((this->_tabcontents = this->_parentWindow->addTab(title, uuid)) ==
            nullptr) {
            qWarning() << this << "Adding tab failed.";
            this->deleteLater();
            return;
        }
        this->_tabcontents->setObjectName(uuid.toString());
        connect(this->_tabcontents,
                SIGNAL(closeButtonClicked(QJSValue, QJSValue)),
                SLOT(_closeButtonClicked(QJSValue, QJSValue)));
    }
    TabContentsBase::TabContentsBase(const QString &title, const QUuid &uuid,
                                     TabContentsBase *parent)
        : QObject(parent) {
        this->setObjectName(uuid.toString());
        if (parent == nullptr) {
            qWarning() << "Tab" << qMakePair(title, uuid)
                       << "parent=null is not allowed.";
            this->deleteLater();
            return;
        }
        this->_parentTab = parent;
        this->_parentWindow = nullptr;
        // If adding tab is failed, RootTabContents should be deleted.
        if ((this->_tabcontents = this->_parentTab->addTab(title, uuid)) ==
            nullptr) {
            qWarning() << this << "Adding tab failed.";
            this->deleteLater();
            return;
        }
        this->setObjectName(uuid.toString());
        connect(this->_tabcontents,
                SIGNAL(closeButtonClicked(QVariant, QVariant)),
                SLOT(_closeButtonClicked(QVariant, QVariant)));
    }

    QString TabContentsBase::title() const {
        return this->_tabcontents->property("title").toString();
    }
    QUuid TabContentsBase::UUID() const {
        return this->_tabcontents->property("uuid").toString();
    }
    QQuickItem *TabContentsBase::addTab(const QString &title,
                                        const QUuid &uuid) {
        QVariant variant;
        if (!QMetaObject::invokeMethod(
                 this->_tabcontents, "addTab", Q_RETURN_ARG(QVariant, variant),
                 Q_ARG(QVariant, QVariant(title)),
                 Q_ARG(QVariant, QVariant(uuid.toString())))) {
            qWarning() << this
                       << "Adding Tab failed:" << qMakePair(title, uuid);
            return nullptr;
        } else
            return variant.value<QQuickItem *>();
    }

    void TabContentsBase::removeTab(const QString &title, const QUuid &uuid) {
        const QPair<QString, QUuid> &&key = qMakePair(title, uuid);
        if (this->_childrenTabs.contains(key)) {
            this->_childrenTabs[key]->deleteLater();
            this->_childrenTabs.remove(key);
        } else {
            qWarning() << this
                       << "Not found:" << qMakePair(title, uuid.toString());
        }
    }
    void TabContentsBase::_closeButtonClicked(const QJSValue &title,
                                              const QJSValue &uuid) {
        this->removeTab(title.toString(), uuid.toString());
    }
    void TabContentsBase::setTitle(const QString &title) {
        QString &&previous = this->title();
        this->_tabcontents->setProperty("title", title);
        if (title != previous) emit this->titleChanged();
    }
    void TabContentsBase::setUUID(const QUuid &uuid) {
        QUuid &&previous = this->UUID();
        this->_tabcontents->setProperty("uuid", uuid.toString());
        if (uuid != previous) emit this->uuidChanged();
    }

    TabContentsBase *TabContentsBase::_getCurrentTabContents() {
        QQuickItem *currentTab =
            this->_tabcontents->property("currentSelectedTabContent")
                .value<QQuickItem *>();
        if (currentTab == nullptr) {
            qDebug() << this << "currentSelectedTabContent is null.";
            return nullptr;
        }
        QUuid tab_uuid = QUuid(currentTab->property("uuid").toString());
        QString tab_title = currentTab->property("title").toString();
        QPair<QString, QUuid> tab_key = qMakePair(tab_title, tab_uuid);
        if (!this->_childrenTabs.contains(tab_key)) {
            qDebug() << this << "TabContent (" << tab_key
                     << ") couldn't be found.";
            return nullptr;
        } else
            return this->_childrenTabs[tab_key];
    }

    void TabContentsBase::deleteLater() {
        if (this->_childrenTabs.size() > 0) {
            for (const QPair<QString, QUuid> &key :
                 this->_childrenTabs.uniqueKeys()) {
                for (TabContentsBase *base : this->_childrenTabs.values(key))
                    base->deleteLater();
            }
            this->_childrenTabs.clear();
        }
        if (this->_tabcontents != nullptr) {
            qDebug() << this << "Deleting tab:" << this->objectName();
            this->_tabcontents->deleteLater();
        } else {
            qDebug() << this << "Tab is null";
        }
        QObject::deleteLater();
    }
}
