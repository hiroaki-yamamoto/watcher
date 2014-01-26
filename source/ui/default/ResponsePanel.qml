import QtQuick 2.0

Rectangle{
    id:root
    height:titleArea.height+bodyArea.height
    width:640
    border{
        width:1
        color:"black"
    }
    color:"transparent"

    property string title:"Title"
    property string author:"Anonymouse Corward"
    property string email:"anonymous@exmaple.com"
    property string post_time:"1970-01-01 00:00:00 UTC"
    property string body:"(^q^)"
    property string uuid:"00000000-0000-0000-0000-000000000000"
    property string responseURL:"http://example.com/responses/blablabla"
    
    signal linkActivated(var linkURL);
    Rectangle{
        id:titleArea
        anchors{
            top:root.top
            left:root.left
            right:root.right
        }
        height:titleBar.contentHeight
        
        border{
            width:1
            color:"black"
        }
        color:"transparent"

        Text{
            id:titleBar
            anchors.fill:parent
            textFormat: Text.RichText
            onLinkActivated: root.linkActivated(link)
            text:{
                "<table width=\""+titleBar.width+"\">"+
                "<tr><td><p align=\"left\">"+root.title+"</p></td><td><p align=\"right\">"+root.post_time+"</p></td></tr>"+
                "<tr><td><p align=\"left\">"+root.author+"</p></td><td><p align=\"right\"><a href=\"mailto:"+root.email+"\">"+root.email+"</a></p></td></tr>"+
                "</table>"
            }
        }
    }
    Rectangle{
        id:bodyArea
        height:{
            var areaHeight=bodyText.height+(bodyText.anchors.margins*2)
            if(imageFlick.visible) areaHeight+=imageFlick.height+(imageFlick.anchors.margins*2)
            areaHeight
        }
        color:"transparent"
        border{
            width:1
            color:"black"
        }
        anchors{
            top:titleArea.bottom
            left:root.left
            right:root.right
        }
        TextEdit{
            id:bodyText
            readOnly:true
            wrapMode:TextEdit.Wrap
            textFormat: TextEdit.RichText
            selectByMouse: true
            anchors{
                margins:5
                top:bodyArea.top
                left:bodyArea.left
                right:bodyArea.right
            }
            height: bodyText.contentHeight
            text:root.body
            onLinkActivated: root.linkActivated(link)
        }
        ImageFlicker{
            id:imageFlick
            height:50
            visible:false
            anchors{
                margins:5
                top:bodyText.bottom
                left:bodyArea.left
                right:bodyArea.right
            }
            areaPanel.onChildrenChanged: {
                imageFlick.visible=(areaPanel.children.length>0)
                var areaHeight=bodyText.height+(bodyText.anchors.margins*2)
                if(imageFlick.visible) imageFlick.height+(imageFlick.anchors.margins*2)
            }

            function addImage(link_url,source_url,uuid){
                var createdComponent=Qt.createComponent("LinkImage.qml")
                if(createdComponent.status===Component.Ready){
                    var createdContent=createdComponent.createObject(imageFlick.areaPanel,
                                                                     {"imageURI":link_url,
                                                                      "source"  :source_url,
                                                                       "uuid"   :uuid
                                                                     })
                    return createdContent
                }
            }
        }
    }
    /*
        linkURI:URI to show by browser when the image is clicked.
        sourceURL:URL of the actual image.
        return value: Generated Item. i.e. LinkImage.
    */
    function addImage(linkURI,sourceURL,uuid){
        var image=imageFlick.addImage(linkURI,sourceURL,uuid)
        if(image===undefined) console.log("Couldn't create Linked Image:{linkURI:"+linkURI+",sourceURL:"+sourceURL+"}")
        else return image
    }
}
