import QtQuick 2.0
Item{
    id: tabContentRoot
    anchors.fill: parent
    clip: true

    property string title:"Untitled"
    property string uuid: "00000000-0000-0000-0000-000000000000"
    property alias model:category.list_model
    property var buttonClickedEvent:function(sender_button){}
    property bool hasAnimation:true
    readonly property bool debug:false
    
    signal buttonClicked(var sender_button)
    signal hideAnimationCompleted()
    signal showAnimationCompleted()
    
    ScrollBar{
        id:category_scroll
        orientation:Qt.Vertical
        anchors{
            right:parent.right
            top:parent.top
            bottom: parent.bottom
        }
        pagewidth:category.contentWidth
        pageheight:category.contentHeight
    
        onPositionChanged:{
            if(!category.flicking&&!category.moving) category.contentY=category.contentHeight*position
        }
    }
    ButtonListView{
        id:category
        anchors{
            top:parent.top
            bottom:parent.bottom
            left:parent.left
            right:category_scroll.left
        }

        onContentYChanged: category_scroll.position=contentY/contentHeight
        onButtonClicked:{
            parent.buttonClicked(sender_button)
            parent.buttonClickedEvent(sender_button)
        }
        onHideAnimationCompleted:{
            if(debug) console.log("Hide Animation Completed.")
            tabContentRoot.hideAnimationCompleted()
        }
        onShowAnimationCompleted:{
            if(debug) console.log("Show Animation Completed.")
            tabContentRoot.showAnimationCompleted()
        }
    }
    function addButton(button_text,detail_text,uuid){
        category.list_model.append(
                    {
                        "txt"           :button_text,
                        "detail_txt"    :detail_text,
                        "id"            :uuid,
                        "has_tooltip"   :false,
                        "title_tooltip" :"",
                        "body_tooltip"  :""
                    }
                    )
    }
    function clearButtons(){category.list_model.clear()}
    function hide(){category.hide()}
    function show(){category.show()}
    Component.onCompleted:{
        for(var i=10;i<100;i++){
            addButton(tabContentRoot.title+"::Test "+i,"","00000000-0000-0000-0000-0000000000"+i)
        }
    }
}
