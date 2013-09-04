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
        }
    }
}
