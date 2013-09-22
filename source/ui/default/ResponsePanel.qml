import QtQuick 2.0

Item{
    id:root
    height:titleArea.height+bodyArea.height
    width:640
    property alias title:titleText.text
    property alias author:authorText.text
    property string email:"anonymous@exmaple.com"
    property alias post_time:dateText.text
    property alias body:bodyText.text
    property string uuid:"00000000-0000-0000-0000-000000000000"
    property url    responseURL:"http://example.com/responses/blablabla"
    property list<LinkImage> images
    
    signal linkActivated(var linkURL);
    
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
            text:"Untitled"
            anchors{
                margins:5
                top:titleArea.top
                left:titleArea.left
            }
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
            text:"<a href=\""+root.email+"\">"+root.email+"</a>"
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
        height:bodyText.contentHeight
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
            anchors.fill: bodyArea
            text:"The quick brown fox jumps over the lazy dog."
        }
    }
}
