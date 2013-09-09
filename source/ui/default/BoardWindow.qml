import QtQuick 2.0
Rectangle{
    id:root
    readonly property bool debug:true
    
    signal currentTabChanged(var previous,var current)
    signal closeButtonClicked(var text,var uuid)
    
    width:  900
    height: 640
    gradient: Gradient{
        GradientStop{position:0;color:"lightgray"}
        GradientStop{position:1;color:"gray"}
    }
    Rectangle{
        id:menu
        z:1
        height:45
        anchors{
            top:root.top
            left:root.left
            right:root.right
        }
        
        gradient: Gradient{
            GradientStop{position: 0;color:"lightgray"}
            GradientStop{position:0.5;color:"gray"}
            GradientStop{position: 1;color:"lightgray"}
        }
        Row{
            id:menuLayout
            anchors.fill: menu
            spacing: 2
            Button{
                id:reload
                objectName: "reload"
                style:reload.style_mode.icon
                icon: "icons/reload.png"
                show_tooltip: true
                tooltip_title: qsTr("Reload")
                tooltip_body: qsTr("Reload board list.")
                radius:2
                anchors.verticalCenter: menuLayout.verticalCenter
            }
            Spacer{
                toFit: menuLayout
                color:"lightgray"
            }
            Button{
                id:close
                objectName: "close"
                style:reload.style_mode.icon
                icon: "icons/dialog-close-22.png"
                show_tooltip: true
                tooltip_title: qsTr("Close")
                tooltip_body: qsTr("Close "+window.title+".")
                anchors.verticalCenter: menuLayout.verticalCenter
                radius:2
            }
        }
    }
    Tab{
        id:boardTab
        anchors{
            margins:5
            top:menu.bottom
            bottom:root.bottom
            left:root.left
            right:root.right
        }
        useClosebutton: true
        contentBorder.width: 0
        onCurrentTabChanged: root.currentTabChanged(previous,current)
        onCloseButtonClicked: root.closeButtonClicked(text,uuid)
        function addTab(tabText,uuid){
            var createdComponent=Qt.createComponent("BoardTabContent.qml")
            if(createdComponent.status===Component.Ready){
                var createdContent=createdComponent.createObject(boardTab.tabPanel,{"title":tabText,"uuid":uuid})
                return createdContent
            }
        }
    }
    function addTab(text,uuid){
        var createdTab=boardTab.addTab(text,uuid);
        if(createdTab===undefined){
            console.log("TabContent("+text+":"+uuid+") couldn't be created.");
        }else return createdTab;
    }
    Component.onCompleted: {
        if(root.debug){
            var testTab1=boardTab.addTab("test1","00000000-0000-0000-0000-000000000000")
            var testTab2=boardTab.addTab("test2","00000000-0000-0000-0000-000000000001")
        }
    }
}
