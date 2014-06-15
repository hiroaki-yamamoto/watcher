import QtQuick 2.0

Rectangle{
    width:400
    height:300
    gradient: Gradient{
        GradientStop{color: "lightgray"; position:0}
        GradientStop{color: "gray"; position:1}
    }
    
    Rectangle{
        id:title
        border{
            width:1
            color:"black"
        }
        color:"transparent"
        Text{
            id:label
            text:applicationName
            font{
                pointSize:12
                bold: true
            }
            anchors{
                margins:5
                verticalCenter:parent.verticalCenter
                left:parent.left
            }
        }
        anchors{
            margins:5
            top:parent.top
            left:parent.left
            right:parent.right
        }
        height:label.height+anchors.margins*2;
    }
    Rectangle{
        border{
            width:1
            color:"black"
        }
        color:"transparent"
        clip:true
        anchors{
            margins:5
            top:title.bottom
            bottom:closeButton.top
            left:parent.left
            right:parent.right
        }
        ScrollBar{
            id:bar
            orientation: Qt.Vertical
            anchors{
                margins:5
                right:parent.right
                top:parent.top
                bottom: parent.bottom
            }
            pagewidth:body_background.contentWidth
            pageheight:body_background.contentHeight

            onPositionChanged:{
                if(!body_background.flicking&&!body_background.moving) body_background.contentY=body_background.contentHeight*position
            }
        }
        Flickable{
            id:body_background
            clip:true;
            anchors{
                margins:5
                left:parent.left
                right:bar.left
                top:parent.top
                bottom:parent.bottom
            }
            contentWidth:width
            contentHeight:(body.height>parent.height)?body.height:parent.height;
            flickableDirection:Flickable.VerticalFlick

            TextEdit{
                id:body
                objectName:"body"
                readOnly:true
                wrapMode:TextEdit.Wrap
                textFormat: TextEdit.RichText
                selectByMouse: true
                text: copyright
                anchors{
                    left:parent.left
                    right:parent.right
                    top:parent.top
                }
                height:contentHeight
            }
            onContentYChanged: bar.position=contentY/contentHeight
        }
    }

    Button{
        id:closeButton
        objectName:"close"
        text:"Close"
        centering:true
        textSize:12
        radius:2
        anchors{
            bottom:parent.bottom
            right:parent.right
        }
    }
}
