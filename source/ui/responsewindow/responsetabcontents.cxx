#include "responsetabcontents.h"
#include <loader/topic.h>
namespace ui{
    ResponseTabContents::ResponseTabContents(plugin::topic *topic, TabWindowBase *parent):
        TabContentsBase(topic->title(),topic->identifier(),parent){
        this->_topic=topic;
    }
}
