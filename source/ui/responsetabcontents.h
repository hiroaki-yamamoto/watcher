#pragma once
#include<QtQuick/QQuickItem>

#include "tabcontents_base.h"
class QString;
class QUuid;
namespace plugin{
    class topic;
}
namespace ui{
    class ResponseWindow;
    class ResponseTabContents:public TabContentsBase{
            Q_OBJECT
        public:
            ResponseTabContents(const QString &tabName,const QUuid &tabID,ResponseWindow *parent=nullptr);
            ResponseWindow *parentWindow() const;
            void addTopic(plugin::topic *topic);
            void reload();
    };
}
