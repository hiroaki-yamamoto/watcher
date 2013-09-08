import QtQuick 2.0
Item{
    id:root
    property string title:"Untitled"
    property string uuid:"00000000-0000-0000-0000-000000000000"
    anchors.fill: parent
    LocationBar{
        id:locationBar
        anchors{
            margins:5
            top:root.top
            left:root.left
            right:root.right
        }
    }
    Item{
        id:viewRoot
    }
}
