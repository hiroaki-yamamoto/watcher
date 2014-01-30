import QtQuick 2.2

Rectangle{
    id:root
    property variant model:ListModel{}

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
        onContentYChanged: scrollBar.position=contentX/contentWidth
        anchors{
            top:root.top
            left:root.left
            right:root.right
            bottom:scrollBar.top
        }
        spacing:2
        flickableDirection: Flickable.HorizontalFlick

        model:root.model

        delegate:LinkImage{
            fillMode:Image.PreserveAspectFit
            height:imageFlick.height
            imageURI: URI
            source: sourceURI
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
