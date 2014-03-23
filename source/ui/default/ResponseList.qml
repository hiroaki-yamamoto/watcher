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
            imageInfoObj:ImageInfo
            onLinkActivated:{
                console.log(linkURL)
                Qt.openUrlExternally(linkURL)
            }
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
    /*
    factor: factor to change. the format must be an formatted map like this:
        title: (str) title
        author: (str) author
        email: (str) email
        post_time: (str) post date
        body: (str) the body of the response
        imageInfo: (imageInfoObject) the image info
    Note: All values are optional.
    */
    
    function updatePanel(UUID,factor){
        var matchIndex=null;
        for(var index=0;index<responseModel.count;index++){
            var candidate=responseModel.get(index)
            if(candidate.responseUUID===UUID.toString()){
                matchIndex=index
                break
            }
        }
        if(matchIndex==null){
            console.log("Nothing matched. skipped.")
            return
        }
        for(var key in factor){
            var el=factor[key]
            switch(key){
                case "title":
                    responseModel.setProperty(matchIndex,"responseTitle",el)
                    break
                case "author":
                    responseModel.setProperty(matchIndex,"responseAuthor",el)
                    break
                case "email":
                    responseModel.setProperty(matchIndex,"responseEmail",el)
                    break
                case "post_time":
                    responseModel.setProperty(matchIndex,"responsePostTime",el)
                    break
                case "body":
                    responseModel.setProperty(matchIndex,"responseBody",el)
                    break
                case "imageInfo":
                    responseModel.setProperty(matchIndex,"ImageInfo",JSON.stringify(el))
                    break
                case "URL":
                    responseModel.setProperty(matchIndex,"URL",el)
                    break
            }
        }
    }
    function addPanel(title,author,email,post_time,body,uuid,URL,imageInfo){
        var responseInfo={
                "responseTitle":title,
                "responseAuthor":author,
                "responseEmail":email,
                "responsePostTime":post_time,
                "responseBody":body,
                "responseUUID":uuid.toString(),
                "URL":URL.toString(),
                "ImageInfo":JSON.stringify(imageInfo)
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
