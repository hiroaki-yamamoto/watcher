#include <QVector>
#include <QtQuick/QQuickItem>
#include <QtWidgets/QMessageBox>
#include <QtDebug>
#include <QUrl>

#include <loader/board.h>
#include <loader/topic.h>
#include <logging/logging.h>

#include "topicview.h"

using namespace logging;
namespace ui {
    TopicView::TopicView(plugin::board *board, TabContentsBase *parent)
        : TabContentsBase(board->title(), board->identifier(), parent) {
        this->_board = board;
        connect(this->_board,
                SIGNAL(get_topics_finished(QVector<plugin::topic *>)),
                SLOT(_getTopicsFinished(QVector<plugin::topic *>)));
        connect(this->_board,
                SIGNAL(get_topics_failed(QNetworkReply::NetworkError, QString)),
                SLOT(_getTopicsFailed(QNetworkReply::NetworkError, QString)));
        if (this->_tabcontents->property("hasAnimation").toBool()) {
            connect(this->_tabcontents, SIGNAL(hideAnimationCompleted()),
                    this->_board, SLOT(get_topics()));
            if (!QMetaObject::invokeMethod(this->_tabcontents,
                                           "startHideAnimation")) {
                this->_tabcontents->disconnect(SIGNAL(hideAnimationCompleted()),
                                               this->_board,
                                               SLOT(get_topics()));
                this->_board->get_topics();
            }
        } else
            this->_board->get_topics();
        this->_tabcontents->setProperty(
            "boardURL", QVariant(board->board_url().toString()));
        connect(this->_tabcontents, SIGNAL(buttonClicked(QVariant)),
                SLOT(_buttonClicked(QVariant)));
    }
    void TopicView::addButton(const QString &title, const QString &detail,
                              const QUuid &uuid) {
        if (!QMetaObject::invokeMethod(
                 this->_tabcontents, "addButton",
                 Q_ARG(QVariant, QVariant(title)),
                 Q_ARG(QVariant, QVariant(detail)),
                 Q_ARG(QVariant, QVariant(uuid.toString())))) {
            qWarning() << this << "Adding a button failed:{title:" << title
                       << ",detail:" << detail << ","
                       << "uuid:" << uuid << "}";
        }
    }
    void TopicView::clearButtons() {
        if (!QMetaObject::invokeMethod(this->_tabcontents, "clearButtons"))
            qWarning() << this << "Deleting buttons failed.";
    }

    void TopicView::_getTopicsFinished(const QVector<plugin::topic *> &topics) {
        if (this->_tabcontents->property("hasAnimation").toBool()) {
            this->_tabcontents->disconnect(SIGNAL(hideAnimationCompleted()),
                                           this->_board, SLOT(get_topics()));
        }
        this->clearButtons();
        for (plugin::topic *topic : topics) {
            this->_topics[qMakePair(topic->title(), topic->identifier())] =
                topic;
            this->addButton(topic->title(), topic->author(),
                            topic->identifier());
        }
        if (this->_tabcontents->property("hasAnimation").toBool()) {
            QMetaObject::invokeMethod(this->_tabcontents, "startShowAnimation");
        }
    }
    void TopicView::reload() {
        if (this->_tabcontents->property("hasAnimation").toBool()) {
            connect(this->_tabcontents, SIGNAL(hideAnimationCompleted()),
                    this->_board, SLOT(get_topics()));
            if (!QMetaObject::invokeMethod(this->_tabcontents,
                                           "startHideAnimation")) {
                this->_tabcontents->disconnect(SIGNAL(hideAnimationCompleted()),
                                               this->_board,
                                               SLOT(get_topics()));
                this->_board->get_topics();
            }
        } else
            this->_board->get_topics();
    }

    void TopicView::_getTopicsFailed(const QNetworkReply::NetworkError err,
                                     const QString &err_str) {
        QMessageBox::critical(nullptr, tr("Getting Topics failed"),
                              tr("Getting topics failed:%1\n"
                                 "Board Title:%2\n"
                                 "UUID:%3\n").arg(err_str, this->title(),
                                                  this->UUID().toString()));
    }
    void TopicView::_buttonClicked(const QVariant &variant) {
        QQuickItem *button = variant.value<decltype(button)>();
        const QUuid id(button->property("uuid").toString());
        const QString &&str = button->property("text").toString();
        const QPair<QString, QUuid> &&key = qMakePair(str, id);
        if (this->_topics[key]) {
            emit this->buttonClicked(str, id, this->_topics[key]);
        } else {
            qWarning() << this << "No such a topic:" << key;
        }
    }
}
