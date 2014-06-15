import QtQuick 2.0

Rectangle{
    id:root
    property alias model:imageFlick.model

    width:50
    height:50
    border{
       width:1
       color:"black"
    }
    color:"transparent"
    clip:true
    ListView{
        id:imageFlick
        onContentXChanged: scrollBar.position=imageFlick.contentX/imageFlick.contentWidth
        anchors{
            top:root.top
            left:root.left
            right:root.right
            bottom:scrollBar.top
        }
        spacing:2
        flickableDirection: ListView.HorizontalFlick
        orientation:ListView.Horizontal
        model:ListModel{}
        delegate:LinkImage{
            id:img
            height:imageFlick.height-2
            fillMode:Image.PreserveAspectFit
            imageURI: LinkURI
            source: SourceURI
            uuid: UUID
        }
    }
   ScrollBar{
       id:scrollBar
       orientation: Qt.Horizontal
       anchors{
           bottom:root.bottom
           left:root.left
           right:root.right
       }
       pageheight: imageFlick.contentHeight
       pagewidth: imageFlick.contentWidth
       onPositionChanged:{
           if(!imageFlick.flicking&&!imageFlick.moving) imageFlick.contentX=imageFlick.contentWidth*position
       }
   }
}
