import QtQuick 2.0
Item{
    id:root
    width:640
    height:480
    property string title   :"Untitled"
    property string uuid    :"00000000-0000-0000-0000-000000000000"

    readonly property alias currentSelectedTabContent:responses.currentPanel
    readonly property bool debug:false
    
    signal currentTabChanged(var previous,var current)
    signal closeButtonClicked(var text,var uuid)
    
    Tab{
        id:responses
        orientation: Qt.Vertical
        anchors.fill: root
        useClosebutton: true
        onCurrentTabChanged: root.currentTabChanged(previous,current)
        onCloseButtonClicked: root.closeButtonClicked(text,uuid)
        function addTab(tabText,uuid){
            var createdComponent=Qt.createComponent("ResponseView.qml")
            if(createdComponent.status===Component.Ready){
                var createdContent=createdComponent.createObject(responses.tabPanel,
                                                                 {
                                                                     "title":tabText,
                                                                     "uuid":uuid,
                                                                     "anchors.fill":responses.tabPanel
                                                                 })
                return createdContent
            }
        }
    }
    function addTab(tabText,uuid){
        var createdComponent=responses.addTab(tabText,"http://example.com/",uuid)
        if(createdComponent===undefined) console.log("Couldn't create response view:{tabTitle:"+tabText+", uuid:"+uuid+"}")
        else return createdComponent
    }
    Component.onCompleted: {
        if(debug){
            for(var i=0;i<10;i++){
                var genTab=addTab("test"+i,i)
                //title,author,email,post_time,body,uuid,URL
                for(var j=0;j<100;j++){
                    genTab.addResponse("Test"+j,"Anonymouse"+j,"anon@example.com",
                                       "Sun Sep 29 2013 10:46:46."+j,"This is a test ["+i+","+j+"]",j)
                }
                genTab.topicURL="http://example.com/boards/example/"+i
            }
        }
    }
}
