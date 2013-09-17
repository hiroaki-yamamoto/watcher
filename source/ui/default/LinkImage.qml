import QtQuick 2.0
Image{
    id:root
    property url imageURI:"http://example.com"
    source: "icons/warn160.png"
    MouseArea{
        anchors.fill:root
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor
 
        onClicked:{
            if(root.imageURI&&root.imageURI.toString()!=="") Qt.openUrlExternally(root.imageURI)
        }
    }
}
