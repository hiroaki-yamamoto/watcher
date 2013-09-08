import QtQuick 2.0
Item{
    id: root
    readonly property bool debug:true
    property string title       :"Untitled"
    property string uuid        :"00000000-0000-0000-0000-000000000000"
    
    signal currentTabChanged(var previous,var current)
    signal closeButtonClicked(var text,var uuid)
    
    anchors.fill: parent
    Tab{
        id:tab
        anchors.fill: root
        useClosebutton: true
        orientation: Qt.Vertical
        onCurrentTabChanged: root.currentTabChanged(previous,current)
        onCloseButtonClicked: root.closeButtonClicked(text,uuid)
        function addTab(tabText,uuid){
            var createdComponent=Qt.createComponent("TopicView.qml")
            if(createdComponent.status===Component.Ready){
                var createdContent=createdComponent.createObject()
                createdContent.title=tabText
                createdContent.uuid=uuid
                createdContent.parent=tab.tabPanel
                return createdContent
            }
        }
    }
    function addTab(tabText,uuid){
        var createdTab=tab.addTab(tabText,uuid);
        if(createdTab===undefined) console.log("Couldn't add TopicView:{Text:"+tabText+",UUID:"+uuid+"}")
        else return createdTab;
    }
    Component.onCompleted: {
        if(root.debug){
            addTab("TestTab1","00000000-0000-0000-0000-000000000000")
            addTab("TestTab2","00000000-0000-0000-0000-000000000001")
        }
    }
}
