import QtQuick 2.0
Image{
    id:root
    property url imageURI:"http://example.com"
    property string uuid:"00000000-0000-0000-0000-000000000000"
    source: "icons/warn160.png"
    width:root.paintedWidth
    height:root.paintedHeight
    MouseArea{
        anchors.fill:root
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor
 
        onClicked:{
            if(root.imageURI&&root.imageURI.toString()!=="") Qt.openUrlExternally(root.imageURI)
        }
    }
}
