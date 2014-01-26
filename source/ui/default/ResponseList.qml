import QtQuick 2.0
Item{
    id:root
    readonly property bool debug:false
    width:100
    height:100
    clip: true
    Flickable{
        id:panelView
        flickableDirection: Flickable.VerticalFlick
        anchors{
            top:root.top
            bottom:root.bottom
            left:root.left
            right:scroll.left
        }
        onContentYChanged: scroll.position=contentY/contentHeight

        Column{
            id:responsePage
            x:5
            y:5
            spacing: 5
            width:panelView.width-(x*2)
            onHeightChanged: panelView.contentHeight=responsePage.height+responsePage.y*2
        }
        function addPanel(title,author,email,post_time,body,uuid,URL){
            var createdComponent=Qt.createComponent("ResponsePanel.qml")
            if(createdComponent.status===Component.Ready){
                var createdContent=createdComponent.createObject(responsePage,
                                                                    {"title"        :title,
                                                                     "author"       :author,
                                                                     "email"        :email,
                                                                     "post_time"    :post_time,
                                                                     "body"         :body,
                                                                     "uuid"         :uuid,
                                                                     "responseURL"  :URL,
                                                                     "anchors.left"     :responsePage.left,
                                                                     "anchors.right"    :responsePage.right
                                                                    }
                                                                 )
                return createdContent
            }
        }
    }
    ScrollBar{
        id:scroll
        orientation:Qt.Vertical
        anchors{
            right:root.right
            top:root.top
            bottom: root.bottom
        }
        pagewidth:panelView.contentWidth
        pageheight:panelView.contentHeight
    
        onPositionChanged:{
            if(!panelView.flicking&&!panelView.moving) panelView.contentY=panelView.contentHeight*position
        }
    }
    function addPanel(title,author,email,post_time,body,uuid,URL){
        return panelView.addPanel(title,author,email,post_time,body,uuid,URL)
    }
    Component.onCompleted:{
        if(debug){
            for(var i=0;i<100;i++){
                var panel=addPanel("test"+i,
                         "Anonymouse",
                         "anon@example.com",
                         "Fri Sep 27 11:27:44 JST 2013 ("+i+")",
                         "This is a test.("+i+")",i,
                         "http://example.com/boards/ex/res/"+i)
                panel.addImage("http://example.com","icons/640magenta.jpg")
                panel.addImage("http://example.com","icons/300300cyan.png")
            }
        }
    }
}
