#pragma once
#include<QtQuick/QQuickItem>

#include "tabcontents_base.h"
namespace plugin{
    class topic;
}
namespace ui{
    class ResponseTabContents:TabContentsBase{
            Q_OBJECT
        public:
            ResponseTabContents(plugin::topic *topic,TabWindowBase *parent=nullptr);
        private:
            plugin::topic *_topic;
    };
}
