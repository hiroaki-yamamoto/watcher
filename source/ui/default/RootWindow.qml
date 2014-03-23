import QtQuick 2.0

Rectangle {
    id:viewRoot
    objectName: "viewRoot"
    width:600
    height:640
    readonly property bool debug:false
    readonly property alias currentSelectedTabContent:tab.currentPanel
    signal currentTabChanged(var previous,var current)
    signal tabCreated(var createdTab)
    //Prevent "No such signal"
    signal closeButtonClicked(var text,var uuid)
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
            id:menu_row
            anchors.fill: menu_background
            spacing:2
            Button{
                id:back
                objectName:"back"
                style:style_mode.icon
                icon:"icons/go-previous.png"
                show_tooltip: true
                tooltip_title: qsTr("Go back")
                tooltip_body: qsTr("Go back to previous view.")
                radius:2
                anchors.verticalCenter: menu_row.verticalCenter
            }
            
            Button{
                id:next
                objectName:"next"
                style:style_mode.icon
                show_tooltip: true
                icon:"icons/go-next.png"
                tooltip_title:qsTr("Go forward")
                tooltip_body:qsTr("Go forward.")
                radius:2
                anchors.verticalCenter: menu_row.verticalCenter
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
                anchors.verticalCenter: menu_row.verticalCenter
            }
            Spacer{
                toFit: menu_row
                color:"lightgray"
                anchors.verticalCenter: menu_row.verticalCenter
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
                anchors.verticalCenter: menu_row.verticalCenter
            }
            
            Spacer{
                toFit: menu_row
                color:"lightgray"
                anchors.verticalCenter: menu_row.verticalCenter
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
                anchors.verticalCenter: menu_row.verticalCenter
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
                anchors.verticalCenter: menu_row.verticalCenter
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
                anchors.verticalCenter: menu_row.verticalCenter
            }

            Spacer{
                toFit: menu_row
                color:"lightgray"
                anchors.verticalCenter: menu_row.verticalCenter
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
                anchors.verticalCenter: menu_row.verticalCenter
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
                anchors.verticalCenter: menu_row.verticalCenter
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
                    var createdContent=createdComponent.createObject(tab.tabPanel,{
                                                                         "title":tabText,
                                                                         "uuid":uuid,
                                                                         "anchors.fill":tab.tabPanel
                                                                     })
                    return createdContent
                }
            }
        }
    }
    function addTab(tabText,uuid){
        var createdTab=tab.addTab(tabText,uuid)
        if(createdTab===undefined) console.log("TabContent("+tabText+":"+uuid+") couldn't be created.");
        else return createdTab;
    }
    

    Component.onCompleted: {
        if(debug){
            var createdContent1=addTab("CategoryView1","00000000-0000-0000-0000-000000000000")
            createdContent1.buttonClickedEvent=function(sender_button){
                console.log("Clicked");
            }
            var createdContent2=addTab("CategoryView2","00000000-0000-0000-0000-000000000001")
        }
    }
}
