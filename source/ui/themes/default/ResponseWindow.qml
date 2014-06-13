import QtQuick 2.0
Rectangle{
    id:root
    readonly property bool debug:false
    readonly property alias currentSelectedTabContent:plugin_tab.currentPanel
    
    signal currentTabChanged(var previous,var current)
    signal closeButtonClicked(var text,var uuid)
    
    width:900
    height:640
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
                id:post
                objectName:"post"
                style:post.style_mode.icon
                radius:2
                icon:"icons/post.png"
                anchors.verticalCenter: menuLayout.verticalCenter
            }
            Button{
                id:reload
                objectName:"reload"
                style:post.style_mode.icon
                radius:2
                icon:"icons/reload.png"
                anchors.verticalCenter: menuLayout.verticalCenter
            }
        }
    }
    Tab{
        id:plugin_tab
        useClosebutton: true
        anchors{
            margins:5
            top:menu.bottom
            bottom:root.bottom
            left:root.left
            right:root.right
        }
        onCurrentTabChanged: root.currentTabChanged(previous,current)
        onCloseButtonClicked: root.closeButtonClicked(text,uuid)
        function addTab(tabText,uuid){
            var createdComponent=Qt.createComponent("ResponseTabContent.qml")
            if(createdComponent.status===Component.Ready){
                var createdContent=createdComponent.createObject(plugin_tab.tabPanel,{
                                                                     "title":tabText, "uuid":uuid,
                                                                     "anchors.fill":plugin_tab.tabPanel
                                                                 })
                return createdContent
            }
        }
    }
    function addTab(tabText,uuid){
        var genTab=plugin_tab.addTab(tabText,uuid)
        if(genTab===undefined) console.log("Couldn't create Tab:{title:"+tabText+", uuid:"+uuid+"}")
        else return genTab
    }
    Component.onCompleted: {
        if(debug){
            for(var i=0;i<3;i++){
                var pluginTab=addTab("test"+i,i)
                for(var j=0;j<3;j++){
                    var topicTab=pluginTab.addTab("test["+i+","+j+"]")
                    topicTab.topicURL="http://exmaple.com/boards/"+i+"/"+j
                    for(var k=0;k<100;k++){
                        topicTab.addResponse("Test "+k,"Anonymouse"+k,"anon@example.com",
                                             "Sun Sep 29 2013 10:46:46."+k,"This is a test ["+i+","+j+","+k+"]",k,
                                             "http://example.com/boards/response/"+i+"/"+j+"/"+k)
                    }
                }
            }
        }
    }
}
