import QtQuick 2.0

Rectangle {
    id:scroll_back
    property int orientation: Qt.Vertical;
    /* position property must be between 0.0 and 1.0. */
    property real position:0;
    
    color:"#80FFFFFF";

    width:10
    height:10
    clip: true;
    
    property real pagewidth:10;
    property real pageheight:10;
    
    Rectangle{
        id:scroll_forward
        z:1
        property real width_rate:parent.width/parent.pagewidth
        property real height_rate:parent.height/parent.pageheight
        
        color:"#80000000";
        
        width:(parent.orientation==Qt.Horizontal)?parent.width*width_rate:parent.width
        height:(parent.orientation==Qt.Vertical)?parent.height*height_rate:parent.height
        MouseArea{
            anchors.fill: parent;
            preventStealing: true
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
    MouseArea{
        anchors.fill: parent;
        z:0.5
        onPressed:{
            switch(orientation){
            case Qt.Vertical:
                var vresult=mouseY-scroll_forward.height/2;
                if(vresult<0) scroll_forward.y=mouseY
                else if(mouseY+scroll_forward.height/2>parent.height){
                    scroll_forward.y=parent.height-scroll_forward.height;
                }else{
                    scroll_forward.y=vresult;
                }
                break
            case Qt.Horizontal:
                var hresult=mouseX-scroll_forward.width/2;
                if(hresult<0) scroll_forward.x=mouseX
                else if(mouseX+scroll_forward.width/2>parent.width){
                    scroll_forward.x=parent.width-scroll_forward.width;
                }else{
                    scroll_forward.x=hresult;
                }
                break
            }
        }
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
