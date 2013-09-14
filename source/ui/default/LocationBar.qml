import QtQuick 2.0
Item{
    id:root
    height:text_back.height
    property alias url:url_text.text
    Rectangle{
        id:text_back
        radius:3
        gradient: Gradient{
            GradientStop{position:0;color:"lightgray"}
            GradientStop{position:1;color:"gray"}
        }
        border{
            color:"black"
            width:1
        }

        anchors{
            margins:2
            left:root.left
            right:open_button.left
            top:open_button.top
            bottom:open_button.bottom
        }
        TextEdit{
            id:url_text
            anchors{
                margins:5
                fill: text_back
            }
            readOnly:true
            selectByMouse: true
        }
    }
    Button{
        id:open_button
        style:open_button.style_mode.icon
        icon:"icons/open-browser.png"
        radius:3
        anchors{
            margins:2
            right:root.right
            verticalCenter: root.verticalCenter
        }

        onClicked:{
            Qt.openUrlExternally(url_text.text)
        }
    }
}
