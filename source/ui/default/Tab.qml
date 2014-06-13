import QtQuick 2.0
import QtQml 2.0

Item{
    id:root
    
    property Item           tabPanel        :panel
    property alias          currentPanel    :panel.current
    property bool           useClosebutton  :false
    property int            orientation     :Qt.Horizontal
    property alias          titleBorder     :view_rect.border
    property alias          contentBorder   :panel.border
    signal closeButtonClicked(var text,var uuid)
    signal currentTabChanged(var previous,var current)
       
    clip: true
    Button{
        id:dummy_button
        text:"This is a dummy button."
        textSize: 12
        visible: false
    }
    Rectangle{
        id:view_rect
        z:1
        border{
            width:1
            color:"black"
        }
        clip:true
        VisualDataModel{
            id:buttons_model
            model:ListModel{id:titleModel}
            property Item selected:null
            property Item toDeselect:null
            delegate:Button{
                id:button
                textSize:root.button_size
                style:(useClosebutton)?button.style_mode.text|button.style_mode.withClose:button.style_mode.text
                property int index:idex
                property string uuid: identifier
                text:title
                selectable:true
                Component.onCompleted:{
                    if(index==0) select()
                }
                onSelected: {
                    buttons_model.selected=button
                    if(buttons_model.toDeselect!=null&&buttons_model.toDeselect!=button)
                        buttons_model.toDeselect.deselect()
                    buttons_model.toDeselect=button
                    panel.select(index)
                }
                onDeselected: if(buttons_model.selected===button) button.select()
                onCloseButtonClicked: root.closeButtonClicked(button.text,button.uuid)
            }
        }
        ListView{
            id:button_view
            model:buttons_model
            clip: false
            z:0
        }

        color:"transparent"
    }
    Rectangle{
        id:panel
        clip:true
        border{
            color:"black"
            width:1
        }
        color:"transparent"
        z:0
        property Item current:null
        property Item previous:null
        onChildrenChanged: {
            titleModel.clear()
            for(var index in children){
                titleModel.append({"title":children[index].title,"idex":index,"identifier":children[index].uuid})
                children[index].titleChanged.connect(reloadTitleBar)
                children[index].uuidChanged.connect(reloadTitleBar)
                if(index>0)children[index].visible=false
            }
        }
        
        //These functions are private. Don't use them out of this module.
        onCurrentChanged:{
            if(previous!==null)previous.visible=false
            if(current!==null)current.visible=true
            currentTabChanged(previous,current)
            previous=current
        }
        function reloadTitleBar(){
            titleModel.clear()
            for(var index in children){
                titleModel.append({"title":children[index].title,"idex":index,"identifier":children[index].uuid})
                if(index>0)children[index].visible=false
            }
        }

        function select(i){
            current=children[i]
        }
    }
    property alias button_size:dummy_button.textSize
    states:[
        State{
            name:"Horizontal"
            when:root.orientation==Qt.Horizontal
            PropertyChanges{
                target: view_rect
                height:dummy_button.height
                width:parent.width
                x: parent.x
                y: parent.y
                /*
                anchors{
                    margins:5
                    top:parent.top
                    left:parent.left
                    right:parent.right
                }
                */
            }
            PropertyChanges{
                target: button_view
                orientation:ListView.Horizontal
                anchors.fill: view_rect
            }
            PropertyChanges{
                target:panel
                anchors{
                    margins:5
                    top:view_rect.bottom
                    bottom:parent.bottom
                    left:parent.left
                    right:parent.right
                }
            }
            
        },
        State{
            name:"Vertical"
            when:root.orientation==Qt.Vertical
            PropertyChanges{
                target: view_rect
                width:dummy_button.height
                anchors{
                    margins:5
                    top:parent.top
                    bottom:parent.bottom
                    left:parent.left
                }
            }
            PropertyChanges{
                target: button_view
                width:view_rect.height
                height:view_rect.width
                orientation:ListView.Horizontal
                transformOrigin:Item.TopLeft
                layoutDirection:ListView.RightToLeft
                rotation:-90
                x:0
                y:view_rect.height
            }
            PropertyChanges{
                target:panel
                anchors{
                    margins:5
                    top:parent.top
                    bottom:parent.bottom
                    left:view_rect.right
                    right:parent.right
                }
            }
        }
    ]
}
