import QtQuick 2.0

Rectangle {
    id:tooltips_root
    smooth: true
    visible:false
    Text{
        id:title_label
        anchors{
            margins:parent.anchors.margins
            top:parent.top
            left:parent.left
        }
        font{
            bold:true
        }
        color:"lightsteelblue"
        wrapMode: Text.WordWrap
        opacity:1
    }
    Text{
        id:body_label
        anchors{
            margins:parent.anchors.margins
            top:title_label.bottom
            left:parent.left
        }
        color:title_label.color
        wrapMode: Text.WordWrap
        opacity:1
    }
    Rectangle{
        id:shadow
        color:"#80000000"
        width:parent.width
        height: parent.height
        z:parent.z-1
        anchors{
            margins:2
            top:parent.top
            left:parent.left
        }
    }

    property alias title:title_label.text
    property alias body:body_label.text
    anchors.margins:5
    width:(anchors.margins*2)+((title_label.paintedWidth<body_label.paintedWidth)?body_label.paintedWidth:title_label.paintedWidth)
    height:(anchors.margins*4)+body_label.paintedHeight+title_label.paintedHeight
    gradient:Gradient{
        GradientStop{position:0; color:"black"}
        GradientStop{position:1; color:Qt.darker("lightsteelblue",2.0)}
    }
    opacity:0
    SequentialAnimation{
        id:show_animation
        PropertyAnimation{
            target:tooltips_root;
            property:"visible"
            to:true
        }
        NumberAnimation{
            target:tooltips_root
            property:"opacity"
            to:0.8
            duration:250
        }
    }
    SequentialAnimation{
        id:hide_animation
        NumberAnimation{
            target:tooltips_root
            property:"opacity"
            to:0
            duration:250
        }
        PropertyAnimation{
            target:tooltips_root;
            property:"visible"
            to:false
        }
    }

    function show(){show_animation.start();}
    function close(){hide_animation.start();}
}
