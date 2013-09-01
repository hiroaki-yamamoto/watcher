import QtQuick 2.0

Rectangle {
    id:viewRoot
    objectName: "viewRoot"
    width:600
    height:640
    property bool debug:false
    property alias currentSelectedTabContent:tab.currentPanel
    signal currentTabChanged(var previous,var current)
    Rectangle{
        id:menu_background
        anchors{
            top:parent.top
            left:parent.left
            right:parent.right
        }

        height: 45
        z:1
        
        gradient: Gradient{
            GradientStop{position: 0;color:"lightgray"}
            GradientStop{position:0.5;color:"gray"}
            GradientStop{position: 1;color:"lightgray"}
        }
        color:"gray"
        Row{
            anchors{
                margins:5
                verticalCenter: parent.verticalCenter
                left:parent.left
            }
            spacing:2
            Button{
                id:back
                objectName:"back"
                style:style_mode.icon
                icon:"icons/go-previous.png"
                show_tooltip: true
                tooltip_title: qsTr("Go back")
                tooltip_body: qsTr("Go back to previous view.")
            }
            
            Button{
                id:next
                objectName:"next"
                style:style_mode.icon
                show_tooltip: true
                icon:"icons/go-next.png"
                tooltip_title:qsTr("Go forward")
                tooltip_body:qsTr("Go forward.")
            }

            Button{
                id:reload
                objectName:"reload"
                style:style_mode.icon
                icon:"icons/reload.png"
                show_tooltip: true
                tooltip_title: qsTr("Reload")
                tooltip_body: qsTr("Reload category list.")
                radius:2
            }
            Rectangle{
                width:1
                height:parent.height
                color:"lightgray"
            }
            Button{
                id:bookmark
                objectName:"bookmark"
                style:style_mode.icon
                icon:"icons/bookmark_manager.png"
                show_tooltip:  true
                tooltip_title: qsTr("Bookmark")
                tooltip_body: qsTr("Open Bookmark Manager")
                radius:2
            }
            
            Rectangle{
                width:1
                height:parent.height
                color:"lightgray"
            }
            Button{
                id:config
                objectName:"config"
                style:style_mode.icon
                icon:"icons/configure.png"
                radius:2
                show_tooltip: true
                tooltip_title: qsTr("Settings")
                tooltip_body:qsTr("Configure settings.")
            }
            Button{
                id:save
                objectName:"save"
                style:style_mode.icon
                icon:"icons/fileexport.png"
                radius:2
                show_tooltip: true
                tooltip_title: qsTr("Export")
                tooltip_body:qsTr("Export settings and Bookmarks.")
            }
            Button{
                id:open
                objectName:"open"
                style:style_mode.icon
                icon:"icons/fileimport.png"
                radius:2
                show_tooltip: true
                tooltip_title: qsTr("Import")
                tooltip_body:qsTr("Import settings and Bookmarks.")
            }

            Rectangle{
                width:1
                height:parent.height
                color:"lightgray"
            }
            Button{
                id:info
                objectName:"info"
                style:style_mode.icon
                icon:"icons/info.png"
                radius:2
                show_tooltip: true
                tooltip_title:qsTr("About")
                tooltip_body:qsTr("About this software")
            }
            Button{
                id:exit
                objectName:"exit"
                style:style_mode.icon
                icon:"icons/exit.png"
                radius:2
                show_tooltip: true
                tooltip_title: "Exit"
                tooltip_body: qsTr("Quit this application")
            }
        }
    }
    Rectangle{
        id:category_background
        anchors{
            top:menu_background.bottom
            bottom: parent.bottom
            left:parent.left
            right:parent.right
        }
        clip:true
        gradient:Gradient{
            GradientStop{position:0;color:"lightgray"}
            GradientStop{position:1;color:"gray"}
        }
        Tab{
            id:tab;
            anchors.fill: parent
            onCurrentTabChanged: viewRoot.currentTabChanged(previous,current)
            function addTab(tabText,uuid){
                var createdComponent=Qt.createComponent("RootTabContent.qml")
                if(createdComponent.status===Component.Ready){
                    var createdContent=createdComponent.createObject()
                    createdContent.title=tabText
                    createdContent.uuid=uuid
                    createdContent.parent=tab.tabPanel
                    return createdContent
                }
            }
        }
    }
    function addTab(tabText,uuid){return tab.addTab(tabText,uuid)}

    Component.onCompleted: {
        if(debug){
            var createdContent1=addTab("CategoryView1")
            createdContent1.buttonClickedEvent=function(sender_button){
                console.log("Clicked");
            }
    
            var createdContent2=addTab("CategoryView2")
            for(var i=0;i<256;i++) addButton(createdContent1,"test "+i)
            for(var i=0;i<100;i++) addButton(createdContent2,"test2 "+i)
        }
    }
}
