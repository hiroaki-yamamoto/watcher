import QtQuick 2.0
ListView{
    id:root
    property string title
    property alias list_model:category_model.model
    property int width_holder:root.width
    
    signal buttonClicked(var sender_button)
    signal hideAnimationCompleted()
    signal showAnimationCompleted()
    
    model:category_model
    clip: true
    
    VisualDataModel{
        id:category_model
        model:ListModel{id:category_list}
        delegate:Button{
            property string uuid:id
            id:button
            width:root.width
            text:txt
            detail:detail_txt
            show_tooltip: has_tooltip
            tooltip_title: title_tooltip
            tooltip_body: body_tooltip
            style: (detail!=="")?(button.style_mode.detail|button.style_mode.text):button.style_mode.text
            clip:false
            onClicked: buttonClicked(button);
        }
    }
    states:[
        State{
            name:"buttonsExposed"
            PropertyChanges{
                target:root
                width:width_holder
                opacity:1
                visible:true
            }
        },
        State{
            name:"buttonsHidden"
            PropertyChanges {
                target: root
                width:0
                opacity:0
                visible:false
            }
        }
    ]
    transitions: [
        Transition{
            id:hiddenTransition
            from: "buttonsExposed"
            to: "buttonsHidden"
            reversible:true
            onRunningChanged:{
                if(!running){
                    if(root.state=="buttonsHidden") root.hideAnimationCompleted()
                    else if(root.state=="buttonsExposed") root.showAnimationCompleted()
                }
            }
            SequentialAnimation{
                id:hideAnimation
                ParallelAnimation{
                    NumberAnimation{
                        id:width_hide_animation
                        target:root
                        property: "width"
                        duration: 200
                    }
                    NumberAnimation{
                        target:root
                        property:"opacity"
                        duration: width_hide_animation.duration
                    }
                }
                PropertyAnimation{
                    target:root
                    property:"visible"
                }
            }
        }
    ]
    state:"buttonsExposed"
    function hide(){
        root.state="buttonsHidden"
    }
    function show(){
        root.state="buttonsExposed"
    }
}
