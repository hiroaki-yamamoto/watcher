import QtQuick 2.0

Item{
    id:root
    readonly property bool debug:false
    width:100
    height:100
    clip: true

    ListModel{id: responseModel}
    ListView{
        id: panelView
        spacing: 5
        model: responseModel
        delegate:ResponsePanel{
            title:responseTitle
            author:responseAuthor
            email:responseEmail
            post_time:responsePostTime
            body:responseBody
            uuid:responseUUID
            responseURL:URL
            width:panelView.width-anchors.rightMargin
        }
        flickableDirection: Flickable.VerticalFlick
        anchors{
            top:root.top
            bottom:root.bottom
            left:root.left
            right:scroll.left
        }
        onContentYChanged: scroll.position=contentY/contentHeight
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
        var responseInfo={
                "responseTitle":title,
                "responseAuthor":author,
                "responseEmail":email,
                "responsePostTime":post_time,
                "responseBody":body,
                "responseUUID":uuid.toString(),
                "URL":URL.toString()
            }
        responseModel.append(responseInfo)
        return responseInfo
    }
    Component.onCompleted:{
        /*
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
        }*/
    }
}
