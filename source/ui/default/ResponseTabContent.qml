import QtQuick 2.0
Item{
    id:root
    property string title   :"Untitled"
    property string uuid    :"00000000-0000-0000-0000-000000000000"
    property alias topicURL :location.url

    readonly property alias currentSelectedTabContent:tab.currentPanel
    
    signal currentTabChanged(var previous,var current)
    signal closeButtonClicked(var text,var uuid)
    
    Tab{
        id:responses
        useClosebutton: true
        onCurrentTabChanged: root.currentTabChanged(previous,current)
        onCloseButtonClicked: root.closeButtonClicked(text,uuid)
    }
}
