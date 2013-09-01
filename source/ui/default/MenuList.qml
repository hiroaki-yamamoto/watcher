import QtQuick 1.1
import "./"

Rectangle {
    id:menuRoot
    width: 480
    height: 640
    signal drawCompleted()

    gradient: Gradient{
        GradientStop{position:0;color: "white"}
        GradientStop{position:1;color:"gray"}
    }
    signal view_pressed()
    signal view_released()
    
    ListModel{id:menuModel}
    ListView{
        id:list
        anchors.fill: parent
        model:menuModel

        delegate:Button{
            property string name:identifier
            id:name
            text:txt
            width:list.width
            z:0
        }
    }
}
