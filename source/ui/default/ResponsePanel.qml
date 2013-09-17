import QtQuick 2.0
Item{
    id:root
    property string title:"Untitled"
    property string author:"Anonymouse"
    property string email:"anonymouse@example.com"
    property string post_time:"Unknown"
    property string body:"Unknown"
    property string uuid:"00000000-0000-0000-0000-000000000000"
    property url    responseURL:"http://example.com/responses/blablabla"
    property list<LinkImage> images
}
