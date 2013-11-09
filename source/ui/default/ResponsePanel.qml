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

    property string title:titleText.text
    property alias author:authorText.text
    property string email:"anonymous@exmaple.com"
    property alias post_time:dateText.text
    property alias body:bodyText.text
    property string uuid:"00000000-0000-0000-0000-000000000000"
    property string responseURL:"http://example.com/responses/blablabla"
    
    signal linkActivated(var linkURL);
    //This signal exsits to avoid "no such signal".
    signal closeButtonClicked(var text,var uuid)
    
    onEmailChanged:{
        emailText.text="<a href=\""+root.email+"\">"+root.email+"</a>"
    }
    onResponseURLChanged:{
        if (root.responseURL===undefined||root.responseURL.toString()==="")
            titleText.text=root.title
        else
            titleText.text="<a href=\""+root.responseURL.toString()+"\">"+root.title+"</a>"
    }
    
    Rectangle{
        id:titleArea
        anchors{
            top:root.top
            left:root.left
            right:root.right
        }
        height:emailText.y+emailText.contentHeight+emailText.anchors.margins*2
        border{
            width:1
            color:"black"
        }
        color:"transparent"
        Text{
            id:titleText
            text:{
                if (root.responseURL===undefined||root.responseURL.toString()==="") return root.title
                else return "<a href=\""+root.responseURL.toString()+"\">"+root.title+"</a>"
            }
            anchors{
                margins:5
                top:titleArea.top
                left:titleArea.left
            }
            onLinkActivated: root.linkActivated(link)
        }
        Text{
            id:authorText
            text:"anonymous"
            font.italic:true
            anchors{
                margins:5
                top:titleText.bottom
                left:titleText.left
            }
        }

        Text{
            id:dateText
            text:"Unknown"
            anchors{
                margins:5
                top:titleArea.top
                right:titleArea.right
            }
        }
        
        Text{
            id:emailText
            text:"<a href=\"mailto:"+root.email+"\">"+root.email+"</a>"
            anchors{
                margins:5
                top:dateText.bottom
                right:titleArea.right
            }
            onLinkActivated: root.linkActivated(link)
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
            text:"The quick brown fox jumps over the lazy dog."
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
