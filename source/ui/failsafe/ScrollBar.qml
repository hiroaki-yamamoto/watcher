import QtQuick 2.0

Rectangle {
    id:scroll_back
    property int orientation: Qt.Vertical;
    /* position property must be between 0.0 and 1.0. */
    property real position:0;
    
    color:"#80FFFFFF";
    
    width: (orientation==Qt.Vertical)?10:width;
    height: (orientation==Qt.Horizontal)?10:height;
    clip: true;
    
    property real pagewidth:10;
    property real pageheight:10;
    
    Rectangle{
        id:scroll_forward
        
        property real width_rate:parent.width/parent.pagewidth
        property real height_rate:parent.height/parent.pageheight
        
        color:"#80000000";
        
        width:(parent.orientation==Qt.Horizontal)?parent.width*width_rate:parent.width
        height:(parent.orientation==Qt.Vertical)?parent.height*height_rate:parent.height
        
        MouseArea{
            anchors.fill: parent;
            drag.target: scroll_forward
            drag.axis:(parent.parent.orientation==Qt.Vertical)?Drag.YAxis:Drag.XAxis
            drag.minimumX:0
            drag.minimumY:0
            drag.maximumX:parent.parent.width-parent.width
            drag.maximumY:parent.parent.height-parent.height
        }
        onXChanged: if(orientation==Qt.Horizontal) position=x/parent.width
        onYChanged: if(orientation==Qt.Vertical) position=y/parent.height
    }
    
    onPositionChanged:{
        switch(orientation){
        case Qt.Vertical:
            scroll_forward.y=height*position;
            break;
        case Qt.Horizontal:
            scroll_forward.x=width*position;
            break;
        default:
            console.debug("Orientation property is invalid.");
        }
    }
}
