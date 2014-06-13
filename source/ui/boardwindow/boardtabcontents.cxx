#include <QVector>
#include <QtDebug>
#include <QString>
#include <QtQuick/QQuickItem>
#include <QtWidgets/QMessageBox>

#include <loader/board.h>
#include <logging/logging.h>

#include "boardtabcontents.h"
#include "topicview.h"
using namespace logging;
namespace ui {
    BoardTabContents::BoardTabContents(const QString &title, const QUuid &uuid,
                                       TabWindowBase *parent)
        : TabContentsBase(title, uuid, parent) {}
    void BoardTabContents::addBoard(plugin::board *board) {
        if (board == nullptr) {
            qWarning() << this << "Board must not be null.";
            return;
        }
        const QPair<QString, QUuid> &&key =
            qMakePair(board->title(), board->identifier());
        if (this->_childrenTabs.contains(key)) {
            qWarning() << this << "The TopicView " << key
                       << " has already existed.";
            // qWarning()<<this<<"The TopicView key has already existed.";
        } else {
            this->_childrenTabs[key] = new TopicView(board, this);
            connect(this->_childrenTabs[key],
                    SIGNAL(buttonClicked(QString, QUuid, plugin::topic *)),
                    SLOT(_buttonClicked(QString, QUuid, plugin::topic *)));
        }
    }
    void BoardTabContents::reload() {
        TopicView *currentTopic = qobject_cast<decltype(currentTopic)>(
            this->_getCurrentTabContents());
        if (currentTopic == nullptr) {
            qWarning() << this << "Reloading Failed. currentTopic is null.";
            return;
        }
        currentTopic->reload();
    }

    void BoardTabContents::_buttonClicked(const QString &text, const QUuid &id,
                                          plugin::topic *topic) {
        Q_UNUSED(text)
        Q_UNUSED(id)
        emit this->responseMode(topic);
    }
}
