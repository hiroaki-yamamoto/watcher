import QtQuick 2.0

Rectangle{
   id:root
   property alias areaPanel:imageArea
   width:50
   height:50
   border{
       width:1
       color:"black"
   }
   color:"transparent"
   clip:true

   Flickable{
       id:imageFlick
       anchors{
           top:root.top
           left:root.left
           right:root.right
           bottom:scrollBar.top
       }

       flickableDirection: Flickable.HorizontalFlick
   
       Row{
           id:imageArea
           spacing:2
           width:50
           height:imageFlick.height
           onChildrenChanged: {
               var hasChild=false
               for(var children_index in imageArea.children){
                   imageArea.children[children_index].fillMode=Image.PreserveAspectFit
                   imageArea.children[children_index].height=imageArea.height
                   imageArea.children[children_index].width=imageArea.paintedWidth
                   hasChild=true
               }
               if(!hasChild) imageArea.width=50
           }
       }
       contentWidth: imageArea.width
       contentHeight: imageArea.height
       onContentYChanged: scrollBar.position=contentX/contentWidth
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
