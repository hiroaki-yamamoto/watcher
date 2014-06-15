#include <QPair>
#include <QtDebug>

#include <loader/topic.h>

#include "responsetabcontents.h"
#include "responseview.h"
#include "responsewindow.h"
namespace ui {
    ResponseTabContents::ResponseTabContents(const QString &tabName,
                                             const QUuid &tabID,
                                             ResponseWindow *parent)
        : TabContentsBase(tabName, tabID, parent) {}
    ResponseWindow *ResponseTabContents::parentWindow() const {
        return qobject_cast<ResponseWindow *>(this->_parentWindow);
    }
    void ResponseTabContents::addTopic(plugin::topic *topic) {
        qDebug() << topic->title();
        qDebug() << topic->identifier();
        this->_childrenTabs[qMakePair(topic->title(), topic->identifier())] =
            new ResponseView(topic, this);
    }
    void ResponseTabContents::reload() {
        ResponseView *responseview = qobject_cast<decltype(responseview)>(
            this->_getCurrentTabContents());
        if (responseview == nullptr) {
            qWarning() << "Couldn't find currently selected tab.";
            return;
        }
        responseview->reload();
    }
}
