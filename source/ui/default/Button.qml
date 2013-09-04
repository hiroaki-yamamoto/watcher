import QtQuick 2.0
import QtGraphicalEffects 1.0

Rectangle {
    id:button
    QtObject{
        id:style_mode_private
        property int text:1
        property int detail:2
        property int icon:4
        property int withClose:8
    }
    
    property alias text:label.text
    property alias detail:subLabel.text
    property bool show_tooltip:false
    property bool centering:false
    property alias tooltip_title:hint.title
    property alias tooltip_body:hint.body
    property alias textSize:label.font.pixelSize
    property alias detailedTextSize:subLabel.font.pixelSize
    property alias style_mode:style_mode_private
    property int style:style_mode.text
    property alias icon:icon_picture.source
    property alias icon_size:icon_picture.sourceSize
    property bool selectable:false
    
    property alias textColor:label.color
    property alias detailedTextColor:subLabel.color
    property color hoveredColor:"#40FFFFFF"
    property color pressedColor:"#80FFFFFF"
    property color normalColor:"transparent"
    
    property var buttonClickedEvent:function(sender){}
    property var closeButtonClickedEvent:function(sender){}
    
    signal entered()
    signal exited()
    signal pressed()
    signal released()
    signal clicked()
    signal selected()
    signal deselected()
    signal closeButtonClicked()
    Text{
        id: label
        font{
            pixelSize:24
            bold:true
        }
        width: contentWidth
        height: contentHeight
        anchors.margins:button.anchors.margins
        states:[
            State{
                name:"CenterMode"
                when:button.centering
                PropertyChanges {
                    target: label
                    anchors.centerIn:button
                }
            },
            State{
                name:"NonCenterMode"
                when:!button.centering
                PropertyChanges {
                    target: label
                    anchors{
                        verticalCenter:{
                            if((button.style&button.style_mode.text)===button.style_mode.text&&
                                    (button.style&button.style_mode.detail)!==button.style_mode.detail){
                                button.verticalCenter
                            } else undefined
                        }
                        left:           ((button.style&button.style_mode.icon)===button.style_mode.icon)?icon_picture.right:button.left
                        top:            ((button.style&button.style_mode.detail)===button.style_mode.detail)?button.top:undefined
                    }
                }
            }
        ]
        visible:((button.style&button.style_mode.text)===button.style_mode.text)
        color:"black"
    }
    Text{
        id: subLabel
        anchors{
            margins:button.anchors.margins
            top:label.bottom
            left:label.left
        }
        font{
            pixelSize: label.font.pixelSize/2
            italic: true
        }
        color:label.color
        visible:(parent.style&parent.style_mode.detail)===parent.style_mode.detail&&!parent.centering
    }
    MouseArea{
        id: mouse_area
        anchors.fill:parent
        hoverEnabled: true
        property bool mouseEntered:false
        states:[
            State{
                name:"Enabled"
                when:button.enabled
                PropertyChanges{
                    target:mouse_area
                    onEntered:{
                        mouse_area.mouseEntered=true
                        button.state='MouseHoverState'
                    }
                    onExited:{
                        mouse_area.mouseEntered=false
                        button.state='MouseExitState'
                    }
                    onCanceled: button.state='MouseExitState'
                    onPressed:  button.state='MousePressState'
                    onReleased: button.state='MouseReleaseState'
                    onClicked:  button.performClick()
                }
            },
            State{
                name:"Disabled"
                when:!button.enabled
            }
        ]
    }
    Image{
        id:icon_picture
        asynchronous: true
        visible:(button.style&button.style_mode.icon)===button.style_mode.icon&&!button.centering
        anchors{
            centerIn:(button.style===button.style_mode.icon)?button:undefined
            verticalCenter:((button.style!==button.style_mode.icon)&&(button.style&button.style_mode.icon)===button.style_mode.icon)?button.verticalCenter:undefined
            left:((button.style!==button.style_mode.icon)&&(button.style&button.style_mode.icon)===button.style_mode.icon)?button.left:undefined
        }
        anchors.margins: button.anchors.margins
    }
    Rectangle{
        id:closeButton
        visible:((button.style&button.style_mode.withClose)===button.style_mode.withClose)&!button.centering
        property int margin:5
        width:closeImg.sourceSize.width+margin
        height:closeImg.sourceSize.width+margin
        anchors{
            margins:5
            verticalCenter: button.verticalCenter
            right: button.right
        }
        Image{
            id:closeImg
            asynchronous: true
            source: "icons/dialog-close.png"
            anchors.centerIn: closeButton
        }
        MouseArea{
            id: closeImgMouseArea
            anchors.fill: closeImg
            hoverEnabled: true
            property bool mouseEntered:false
            states:[
                State{
                    name: "Enabled"
                    when: button.enabled&&closeImg.visible
                    PropertyChanges{
                        target:closeImgMouseArea
                        onClicked:button.closeButtonClicked();
                        onEntered:{
                            closeImgMouseArea.mouseEntered=true;
                            closeButton.state="Entered"
                        }
                        onExited:{
                            closeImgMouseArea.mouseEntered=false;
                            closeButton.state="Exited"
                        }
                        onPressed:closeButton.state="Pressed"
                        onReleased:closeButton.state="Released"
                    }
                },
                State{
                    name: "Disabled"
                    when: !(button.enabled&&closeImg.visible)
                }
            ]
        }
        states:[
            State{
                name:"Entered"
                PropertyChanges{
                    target:closeButton
                    color:button.hoveredColor
                    border{
                        width:1
                        color:"gray"
                    }
                }
            },
            State{
                name:"Exited"
                PropertyChanges{
                    target:closeButton
                    color:button.normalColor
                    border{
                        width:0
                        color:"transparent"
                    }
                }
            },
            State{
                name:"Pressed"
                PropertyChanges{
                    target:closeButton
                    color:button.pressedColor
                    border{
                        width:1
                        color:"gray"
                    }
                }
            },
            State{
                name:"Released"
                PropertyChanges{
                    target:closeButton
                    color:(closeImgMouseArea.mouseEntered)?button.hoveredColor:button.normalColor
                    border{
                        width:1
                        color:"gray"
                    }
                }
            }

        ]
        state:"Exited"
    }

    Colorize{
        id:icon_colorize
        anchors.fill:icon_picture
        source:icon_picture
        saturation:0.0
        hue:0.0
        lightness:0.0
        states:[
            State{
                name:"Enabled"
                when:button.enabled
                PropertyChanges{
                    target:icon_colorize
                    visible:false
                }
            },
            State{
                name:"Disabled"
                when:!button.enabled
                PropertyChanges{
                    target:icon_colorize
                    visible:true
                }
            }
        ]
        state:"Enabled"
    }

    ToolTip{
        id:hint
        anchors.top:button.verticalCenter
        anchors.left: button.horizontalCenter
        Timer{
            id:hint_timer
            interval:1000
            repeat:false
            running:false
            onTriggered:{
                if(window.active) hint.show()
            }
        }
        onVisibleChanged:parent.z+=(visible)?1:-1

        function stop_timer_and_close(){
            hint_timer.stop()
            hint.close()
        }
    }
    
    QtObject{
        id:private_functions
        function calcWidth(){
            var value=40
            if(button.style===button.style_mode.icon) return icon_picture.sourceSize.width+icon_picture.anchors.margins+button.anchors.margins*2
            if((button.style&(button.style_mode.text|button.style_mode.detail))===(button.style_mode.text|button.style_mode.detail)){
                value+=(label.paintedWidth>=subLabel.paintedWidth)?label.paintedWidth:subLabel.paintedWidth
            }
            else if((button.style&button.style_mode.text)===button.style_mode.text)     value+=label.paintedWidth
            else if((button.style&button.style_mode.detail)===button.style_mode.detail) value+=subLabel.paintedWidth
            
            if((button.style&button.style_mode.icon)===button.style_mode.icon)              value+=icon_picture.paintedWidth
            if((button.style&button.style_mode.withClose)===button.style_mode.withClose)    value+=closeButton.width
            return value
        }
        function calcHeight(){
            var value=button.anchors.margins*2
            var heights={
                "icon":icon_picture.anchors.margins+icon_picture.sourceSize.height,
                "label":label.anchors.margins+label.paintedHeight,
                "subLabel":subLabel.anchors.margins+subLabel.paintedHeight
            }
            if((button.style&button.style_mode.icon)===button.style_mode.icon&&heights.icon>value)          value+=heights.icon
            if((button.style&button.style_mode.text)===button.style_mode.text&&heights.label>value)         value+=heights.label
            if((button.style&button.style_mode.detail)===button.style_mode.detail)  value+=heights.subLabel

            return value
        }
    }
    
    anchors.margins:5
    width:  private_functions.calcWidth()
    height: private_functions.calcHeight()

    border{
        width: 1
        color: textColor
    }
    color:normalColor

    states:[
        State{
            name: 'MouseHoverState'
            PropertyChanges{
                target: button
                color: (selectable&&focus)?pressedColor:hoveredColor
            }
            StateChangeScript{
                name:"EnterScript"
                script:{
                    if((!selectable||!focus)&&show_tooltip) hint_timer.restart()
                    entered();
                }
            }
        },
        State{
            name: 'MouseExitState'
            PropertyChanges{
                target: button
                color: (selectable&&focus)?pressedColor:normalColor
            }
            StateChangeScript{
                name:"ExitScript"
                script:{
                    if((!selectable||!focus)&&show_tooltip) hint.stop_timer_and_close();
                    exited();
                }
            }
        },
        State{
            name: 'MousePressState'
            PropertyChanges{
                target:button
                color:pressedColor
            }
            StateChangeScript{
                name:"PressScript"
                script:{
                    if(!selectable&&show_tooltip) hint.stop_timer_and_close();
                    pressed();
                }
            }
        },
        State{
            name: 'MouseReleaseState'
            PropertyChanges{
                target:button
                color:(mouse_area.mouseEntered)?hoveredColor:normalColor
            }
            StateChangeScript{
                name:"ReleaseScript"
                script:{released();}
            }
        },
        State{
            name: 'DisabledState'
            when: !button.enabled
        },
        State{
            name: "EnabledState"
            when: button.enabled
        }
    ]
    
    function select(){
        color=pressedColor;
        focus=true;
        selected();
    }
    function deselect(){
        color=normalColor;
        focus=false;
        deselected();
    }

    function performClick(){
        if(!enabled) return;
        if(selectable&&!focus) select();
        else if(selectable&&focus) deselect();
        buttonClickedEvent(button);
        clicked();
    }
}
