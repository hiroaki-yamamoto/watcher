import QtQuick 2.0
Item{
    id: tabContentRoot
    clip: true

    property string title:"Untitled"
    property string uuid:"00000000-0000-0000-0000-000000000000"
    property var buttonClickedEvent:function(sender_button){}
    property bool hasAnimation:true
    readonly property bool debug:false
    
    signal buttonClicked(var sender_button)
    signal hideAnimationCompleted()
    signal showAnimationCompleted()
    //Prevent error message "No such signal"
    signal closeButtonClicked(var text,var uuid)
    ButtonListView{
        id:category
        anchors.fill: tabContentRoot
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
        category.addButton(button_text,detail_text,uuid,false,"","")
    }
    function clearButtons(){category.clearButtons();}
    function hide(){category.hide()}
    function show(){category.show()}
    Component.onCompleted:{
        if(debug){
            for(var i=10;i<100;i++){
                addButton(tabContentRoot.title+"::Test "+i,"","00000000-0000-0000-0000-0000000000"+i)
            }
        }
    }
}
