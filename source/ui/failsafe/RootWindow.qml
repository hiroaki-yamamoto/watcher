import QtQuick 2.0
Rectangle{
    id:rootWindow
    Row{
        id:horizontalLayout
        spacing:2
        Button{
            id:config
            objectName:"config"
            icon: "qrc:///themes/failsafe/icons/config"
            style: style_mode.icon
            show_tooltip: true
            tooltip_title: qsTr("Settings")
            tooltip_body:qsTr("Configure settings.")
        }
        Button{
            id:info
            objectName:"info"
            icon: "qrc:///themes/failsafe/icons/info"
            style: style_mode.icon
            show_tooltip: true
            tooltip_title: qsTr("About")
            tooltip_body: qsTr("About this software")
        }
        Button{
            id:exit
            objectName:"exit"
            icon: "qrc:///themes/failsafe/icons/exit"
            style: style_mode.icon
            show_tooltip:true
            tooltip_title:qsTr("Quit")
            tooltip_body:qsTr("Quit this software")
        }
        anchors{
            verticalCenter: parent.verticalCenter
            horizontalCenter: parent.horizontalCenter
        }
    }
    width: 200
    height: 200
    color: "magenta"
}
