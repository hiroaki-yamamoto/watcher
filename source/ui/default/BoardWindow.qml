import QtQuick 2.0
Rectangle{
    id:root
    width:  900
    height: 300
    gradient: Gradient{
        GradientStop{position:0;color:"lightgray"}
        GradientStop{position:1;color:"gray"}
    }
    Rectangle{
        id:menu
        z:1
        height:45
        anchors{
            top:root.top
            left:root.left
            right:root.right
        }
        
        gradient: Gradient{
            GradientStop{position: 0;color:"lightgray"}
            GradientStop{position:0.5;color:"gray"}
            GradientStop{position: 1;color:"lightgray"}
        }
        Row{
            id:menuLayout
            anchors.fill: menu
            spacing: 2
            Button{
                id:reload
                objectName: "reload"
                style:reload.style_mode.icon
                icon: "icons/reload.png"
                show_tooltip: true
                tooltip_title: qsTr("Reload")
                tooltip_body: qsTr("Reload board list.")
                radius:2
                anchors.verticalCenter: menuLayout.verticalCenter
            }
            Spacer{
                toFit: menuLayout
                color:"lightgray"
            }
            Button{
                id:close
                objectName: "close"
                style:reload.style_mode.icon
                icon: "icons/dialog-close-22.png"
                show_tooltip: true
                tooltip_title: qsTr("Close")
                tooltip_body: qsTr("Close "+window.title+".")
                anchors.verticalCenter: menuLayout.verticalCenter
                radius:2
            }
        }
    }
}
