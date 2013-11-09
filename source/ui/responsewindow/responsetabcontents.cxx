#include <QPair>
#include <QtDebug>

#include <loader/topic.h>

#include "responsetabcontents.h"
#include "responseview.h"
namespace ui{
    ResponseTabContents::ResponseTabContents(const QString &tabName, const QUuid &tabID, TabWindowBase *parent):
        TabContentsBase(tabName,tabID,parent){}
    void ResponseTabContents::addTopic(plugin::topic *topic){
        this->_childrenTabs[qMakePair(topic->title(),topic->identifier())]=new ResponseView(topic,this);
    }
    void ResponseTabContents::reload(){
        ResponseView *responseview=qobject_cast<decltype(responseview)>(this->_getCurrentTabContents());
        if(responseview==nullptr){
            qWarning()<<"Couldn't find currently selected tab.";
            return;
        }
        responseview->reload();
    }
}
