import QtQuick 2.0
Item{
    id:root
    property string title:"Untitle"
    property string uuid:"00000000-0000-0000-0000-000000000000"
    property alias topicURL:location.url
    
    LocationBar{
        id:location
        anchors{
            margins:5
            top:root.top
            left:root.left
            right:root.right
        }
    }
}
