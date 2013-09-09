import QtQuick 2.0
Item{
    id:root
    property string title:"Untitled"
    property string uuid:"00000000-0000-0000-0000-000000000000"
    property bool debug:true
    property bool hasAnimation:false
    
    signal buttonClicked(var sender_button)
    signal hideAnimationCompleted()
    signal showAnimationCompleted()
    
    anchors.fill: parent
    LocationBar{
        id:locationBar
        anchors{
            margins:5
            top:root.top
            left:root.left
            right:root.right
        }
    }
    Rectangle{
        id:viewRoot
        color:"transparent"
        border{
            width:1
            color:"black"
        }

        anchors{
            margins:5
            top:locationBar.bottom
            bottom:root.bottom
            left:root.left
            right:root.right
        }
        ButtonListView{
            id:topicButtons
            anchors.fill: viewRoot
            onButtonClicked: root.buttonClicked(sender_button)
            onHideAnimationCompleted: root.hideAnimationCompleted()
            onShowAnimationCompleted: root.showAnimationCompleted()
        }
    }
    function addButton(text,detail,uuid){topicButtons.addButton(text,detail,uuid,false,"","")}
    Component.onCompleted: {
        if(debug){
            for(var i=10;i<51;i++){
                root.addButton("Test::"+i,"test","00000000-0000-0000-0000-0000000000"+i)
            }
            for(var i=51;i<100;i++){
                root.addButton("Test::"+i,"","00000000-0000-0000-0000-0000000000"+i)
            }
        }
    }
}
