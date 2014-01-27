import QtQuick 2.0
Item{
    id:root
    property string title:"Untitled"
    signal buttonClicked(var sender_button)
    signal hideAnimationCompleted()
    signal showAnimationCompleted()

    ScrollBar{
        id:category_scroll
        orientation:Qt.Vertical
        anchors{
            right:root.right
            top:root.top
            bottom: root.bottom
        }
        pagewidth:buttonListView.contentWidth
        pageheight:buttonListView.contentHeight
    
        onPositionChanged:{
            if(!buttonListView.flicking&&!buttonListView.moving) buttonListView.contentY=buttonListView.contentHeight*position
        }
    }
    ListView{
        id:buttonListView
        anchors{
            top:root.top
            bottom:root.bottom
            left:root.left
            right:category_scroll.left
        }

        property int width_holder:buttonListView.width

        model:category_model
        clip: true

        VisualDataModel{
            id:category_model
            model:ListModel{id:category_list}
            delegate:Button{
                property string uuid:id
                id:button
                width:buttonListView.width
                text:txt
                detail:detail_txt
                show_tooltip: has_tooltip
                tooltip_title: title_tooltip
                tooltip_body: body_tooltip
                style: (detail!=="")?(button.style_mode.detail|button.style_mode.text):button.style_mode.text
                clip:false
                onClicked: root.buttonClicked(button);
            }
        }
        states:[
            State{
                name:"buttonsExposed"
                PropertyChanges{
                    target:buttonListView
                    width:width_holder
                    opacity:1
                    visible:true
                }
            },
            State{
                name:"buttonsHidden"
                PropertyChanges {
                    target: buttonListView
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
                        if(buttonListView.state=="buttonsHidden") root.hideAnimationCompleted()
                        else if(buttonListView.state=="buttonsExposed") root.showAnimationCompleted()
                    }
                }
                SequentialAnimation{
                    id:hideAnimation
                    ParallelAnimation{
                        NumberAnimation{
                            id:width_hide_animation
                            target:buttonListView
                            property: "width"
                            duration: 200
                        }
                        NumberAnimation{
                            target:buttonListView
                            property:"opacity"
                            duration: width_hide_animation.duration
                        }
                    }
                    PropertyAnimation{
                        target:buttonListView
                        property:"visible"
                    }
                }
            }
        ]
        onContentYChanged: category_scroll.position=contentY/contentHeight
        state:"buttonsExposed"
    }
    function hide(){
        buttonListView.state="buttonsHidden"
    }
    function show(){
        buttonListView.state="buttonsExposed"
    }
    function addButton(button_text,detail_text,uuid,has_tooltip,title_tooltip,body_tooltip){
        category_list.append(
                    {
                        "txt"           :button_text,
                        "detail_txt"    :detail_text,
                        "id"            :uuid,
                        "has_tooltip"   :has_tooltip,
                        "title_tooltip" :title_tooltip,
                        "body_tooltip"  :body_tooltip
                    }
                    )
    }
    function clearButtons(){category_list.clear()}
}
