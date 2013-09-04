import QtQuick 2.0
Rectangle{
    id:root
    property variant toFit:undefined
    height:toFit.height
    anchors{
        top:toFit.top
        bottom: toFit.Bottom
    }

    width:2
}
