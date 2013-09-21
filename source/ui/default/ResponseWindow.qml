import QtQuick 2.0
Rectangle{
    id:root
    width:900
    height:640
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
                id:post
                objectName:"post"
                style:post.style_mode.icon
                radius:2
                icon:"icons/post.png"
                anchors.verticalCenter: menuLayout.verticalCenter
            }
            Button{
                id:reload
                objectName:"reload"
                style:post.style_mode.icon
                radius:2
                icon:"icons/reload.png"
                anchors.verticalCenter: menuLayout.verticalCenter
            }
        }
    }
}
