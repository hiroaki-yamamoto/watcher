#include "responsewindow.h"
#include "responsetabcontents.h"
#include <QString>
#include <QDebug>
#include <QtWidgets/QMessageBox>
#include <QtDebug>

#include <logging/logging.h>
#include <loader/topic.h>
#include <loader/board.h>
#include <loader/category.h>
#include <loader/root.h>

using namespace logging;
namespace ui {
    void ResponseWindow::_createRelationBetweenSignalsAndSlots() {
        for (const QString &key : this->_children.uniqueKeys()) {
            if (key == "post")
                connect(this->_children[key], SIGNAL(clicked()),
                        SLOT(_postButtonClicked()));
            if (key == "reload")
                connect(this->_children[key], SIGNAL(clicked()),
                        SLOT(_reload()));
        }
    }
    void ResponseWindow::addTopic(plugin::topic *th) {
        if (th == nullptr) {
            qWarning() << this << "Topic argument is null.";
            return;
        }
        plugin::board *boa = qobject_cast<decltype(boa)>(th->parent());
        if (boa == nullptr) {
            QMessageBox::critical(nullptr, tr("Internal Error"),
                                  tr("The address of board is null"));
            qWarning() << this << "Topic info:{ID:" << th->identifier()
                       << ", title:" << th->title() << "}";
            return;
        }
        plugin::category *cat = qobject_cast<decltype(cat)>(boa->parent());
        if (cat == nullptr) {
            QMessageBox::critical(nullptr, tr("Internal Error"),
                                  tr("The address of category is null"));
            qWarning() << this << "Board info:{ID:" << boa->identifier()
                       << ", title:" << boa->title() << "}";
            return;
        }
        plugin::root *rot = qobject_cast<decltype(rot)>(cat->parent());
        if (rot == nullptr) {
            QMessageBox::critical(nullptr, tr("Internal Error"),
                                  tr("The address of root is null"));
            qWarning() << this << "Category Info:{ID:" << cat->identifier()
                       << ", title:" << boa->title() << "}";
            return;
        }
        QPair<QString, QUuid> &&key =
            qMakePair(rot->title(), rot->identifier());
        if (this->_tabcontents.contains(key)) {
            ResponseTabContents *content =
                qobject_cast<decltype(content)>(this->_tabcontents[key]);
            if (content != nullptr) {
                content->addTopic(th);
            } else {
                content = new ResponseTabContents(rot->title(),
                                                  rot->identifier(), this);
                this->_tabcontents[key] = content;
                content->addTopic(th);
            }
        } else {
            ResponseTabContents *content =
                new ResponseTabContents(rot->title(), rot->identifier(), this);
            this->_tabcontents[key] = content;
            content->addTopic(th);
        }
    }
    void ResponseWindow::_postButtonClicked() { qDebug() << this << "post"; }
    void ResponseWindow::_reload() {
        ResponseTabContents *tab =
            qobject_cast<decltype(tab)>(this->_getCurrentTabContents());
        if (tab == nullptr) {
            qWarning() << this << "Current selected tab couldn't be found";
            return;
        }
        tab->reload();
    }
}
