#include <QImage>
#include <QtQuick/QQuickItem>

#include <loader/response.h>

#include "responsepanel.h"
#include "responseview.h"

namespace ui{
    ResponsePanel::ResponsePanel(const plugin::response *res, ResponseView *parent):
        QObject(parent){
        this->_response=res;
        this->_item=parent->_addItem(this->title(),this->author(),
                                            this->email(),this->post_time(),
                                            this->body(),this->UUID(),this->responseURL());
        
    }
    QString     ResponsePanel::title()          const{return this->_response->title();}
    QString     ResponsePanel::author()         const{return this->_response->author();}
    QString     ResponsePanel::email()          const{return this->_response->email();}
    QDateTime   ResponsePanel::post_time()      const{return this->_response->creation_date();}
    QString     ResponsePanel::body()           const{return this->_response->body();}
    QUuid       ResponsePanel::UUID()           const{return this->_response->identifier();}
    QUrl        ResponsePanel::responseURL()    const{return this->_response->response_url();}
    
    const plugin::response *ResponsePanel::response() const {return this->_response;}
    void ResponsePanel::setResponse(const plugin::response *res){this->_response=res;}
}
