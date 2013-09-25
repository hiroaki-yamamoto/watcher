import QtQuick 2.0

Rectangle{
   id:root
   property alias areaPanel:imageArea
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
           x:0
           y:0
           width:50
           height:imageFlick.height
           onChildrenChanged: {
               var extendwidth=0
               for(children_index in imageArea.children){
                   imageArea.children[children_index].fillMode=Image.PreserveAspectFit
                   imageArea.children[children_index].height*=root.height/children_index.height
                   imageArea.children[children_index].width=imageArea.paintedWidth
                   extendwidth+=imageArea.children[children_index].width
               }
               if(extendwidth>0) imageArea.width=extendwidth
               else imageArea.width=50
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
