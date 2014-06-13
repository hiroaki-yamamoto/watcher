import QtQuick 2.0
Item{
    id:root
    width:640
    height:480
    property string title:"Untitle"
    property string uuid:"00000000-0000-0000-0000-000000000000"
    property alias topicURL:location.url
    readonly property bool debug:false
    readonly property bool hasAnimation:false
    signal closeButtonClicked(var text,var uuid)
    
    LocationBar{
        id:location
        anchors{
            margins:5
            top:root.top
            left:root.left
            right:root.right
        }
    }
    ResponseList{
        id:responseList
        anchors{
            margins:5
            top:location.bottom
            bottom:root.bottom
            left:root.left
            right:root.right
        }
    }
    function updatePanel(UUID,factor){
        return responseList.updatePanel(UUID,factor)
    }
    function addResponse(title,author,email,post_time,body,uuid,URL,imageInfo){
        var generatedContent=responseList.addPanel(title,author,email,post_time,body,uuid,URL,imageInfo)
        if(generatedContent===undefined) console.log("Couldn't create response panel.")
        else return generatedContent
    }
    Component.onCompleted: {
        if(debug){
            for(var i=0;i<100;i++){
                var response=addResponse("Test Response"+i,"Anonymouse"+i,"sage","Sun Sep 29 2013 10:46:46."+i,
                                                    "This is a test \n The test number is:"+i,i,
                                                    "http://example.com/boards/example/example_topic/"+i)
                response.addImage("http://example.com","icons/640magenta.jpg")
                response.addImage("http://example.com","icons/300300cyan.png")
            }
        }
    }
}
