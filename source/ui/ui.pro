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
                topicwindow.h

SOURCES +=      versionwindow.cxx \
                configwindow/constructor.cxx \
                configwindow/listing.cxx \
                configwindow/events.cxx \
                configwindow/functions.cxx \
                configwindow/ui_creation.cxx \
                configwindow/signals_slots.cxx \
                configwindow/properties.cxx \
                rootwindow/constructor.cxx \
                rootwindow/properties.cxx \
                rootwindow/signals_slots.cxx \
                rootwindow/functions.cxx \
                boardwindow/constructor.cxx \
                boardwindow/functions.cxx \
                boardwindow/properties.cxx \
                boardwindow/signals_slots.cxx \
                pluginpanel.cxx \
                multiple_scroll_area.cxx \
                themepanel.cxx \
                theme_scroll_area.cxx \
                filechooser.cxx \
                qml_window_base.cxx \
                license.cxx \
                roottabcontents.cxx \
                boardtabcontents.cxx

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
                default/Spacer.qml \
                default/LocationBar.qml \
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
