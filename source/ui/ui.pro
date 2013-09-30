TEMPLATE = lib

HEADERS +=      rootwindow.h \
                versionwindow.h \
                configwindow.h \
                boardwindow.h \
                pluginpanel.h \
                multiple_scroll_area.h \
                themepanel.h \
                theme_scroll_area.h \
                filechooser.h \
                qml_window_base.h \
                license.h \
                roottabcontents.h \
                boardtabcontents.h \
                topicwindow.h \
                tabcontents_base.h \
                tabwindow_base.h \
                responsewindow.h \
                responselist.h \
                responsepanel.h \
                responsetabcontents.h \
                responseview.h \
                topicview.h

SOURCES +=      versionwindow.cxx \
                configwindow/constructor.cxx \
                configwindow/listing.cxx \
                configwindow/events.cxx \
                configwindow/functions.cxx \
                configwindow/ui_creation.cxx \
                configwindow/signals_slots.cxx \
                configwindow/properties.cxx \
                rootwindow/constructor.cxx \
                rootwindow/signals_slots.cxx \
                rootwindow/roottabcontents.cxx \
                boardwindow/constructor.cxx \
                boardwindow/signals_slots.cxx \
                boardwindow/boardtabcontents.cxx \
                responsewindow/constructor.cxx \
                responsewindow/signals_slots.cxx \
                responsewindow/responselist.cxx \
                responsewindow/responsepanel.cxx \
                responsewindow/responsetabcontents.cxx \
                responsewindow/responseview.cxx \
                pluginpanel.cxx \
                multiple_scroll_area.cxx \
                themepanel.cxx \
                theme_scroll_area.cxx \
                filechooser.cxx \
                qml_window_base.cxx \
                license.cxx \
                tabcontents_base.cxx \
                tabwindow_base.cxx \
                topicview.cxx

OTHER_FILES+=   default/Button.qml \
                default/RootWindow.qml \
                default/ToolTip.qml Tab.qml \ 
                default/ButtonListView.qml \
                default/VersionWindow.qml \
                default/Tab.qml \
                default/ScrollBar.qml \
                default/info.json \
                default/RootTabContent.qml \
                default/BoardWindow.qml \
                default/BoardTabContent.qml\
                default/TopicView.qml\
                default/ResponseWindow.qml\
                default/ResponseTabContent.qml\
                default/ResponseView.qml\
                default/ResponsePanel.qml\
                default/ResponseList.qml\ 
                default/Spacer.qml \
                default/LocationBar.qml \
                default/LinkImage.qml \
                default/ImageFlicker.qml \
                failsafe/RootWindow.qml \
                failsafe/VersionWindow.qml \
                failsafe/ToolTip.qml \
                failsafe/ScrollBar.qml \
                failsafe/BoardWindow.qml \
                CMakeLists.txt

FORMS+=         configwindow.ui \
                pluginpanel.ui \
                themepanel.ui

RESOURCES +=    resource.qrc 
