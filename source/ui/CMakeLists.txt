project(watcher-ui)
add_custom_command(
    OUTPUT default
    COMMAND cp ARGS -r ${CMAKE_CURRENT_SOURCE_DIR}/themes ${CMAKE_BINARY_DIR}/
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/themes
    COMMENT "Copying official theme file..."
)

add_custom_target(
    default_ui_copy ALL
    DEPENDS default
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

qt5_add_resources(rc_out "resource.qrc") 
qt5_wrap_ui(ui_generated
    "configwindow.ui"
    "pluginpanel.ui"
    "themepanel.ui"
)

set(src
    "qml_window_base.cxx"
    "versionwindow.cxx"
    "pluginpanel.cxx"
    "themepanel.cxx"
    "multiple_scroll_area.cxx"
    "theme_scroll_area.cxx"
    "filechooser.cxx"
    "license.cxx"
    "tabcontents_base.cxx"
    "tabwindow_base.cxx"
    "topicview.cxx"

    "configwindow/constructor.cxx"
    "configwindow/properties.cxx"
    "configwindow/signals_slots.cxx"
    "configwindow/ui_creation.cxx"
    "configwindow/listing.cxx"
    "configwindow/events.cxx"
    "configwindow/functions.cxx"
    
    "rootwindow/constructor.cxx"
    "rootwindow/signals_slots.cxx"
    "rootwindow/roottabcontents.cxx"

    "boardwindow/constructor.cxx"
    "boardwindow/signals_slots.cxx"
    "boardwindow/boardtabcontents.cxx"

    "responsewindow/constructor.cxx"
    "responsewindow/signals_slots.cxx"
    "responsewindow/responsepanel.cxx"
    "responsewindow/responsetabcontents.cxx"
    "responsewindow/responseview.cxx"
)
qt5_wrap_cpp(moc_src
    "configwindow.h"
    "rootwindow.h"
    "boardwindow.h"
    "boardtabcontents.h"
    "roottabcontents.h"
    "responsepanel.h"
    "responsetabcontents.h"
    "responseview.h"
    "responsewindow.h"
)


add_library(watcher_ui SHARED ${ui_generated} ${src} ${moc_src} ${rc_out})
set_property(TARGET watcher_ui PROPERTY LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
target_link_libraries(watcher_ui storage loader logging manager)
qt5_use_modules(watcher_ui Core Widgets Quick Qml Network)

install(
    TARGETS watcher_ui
    LIBRARY DESTINATION "lib/watcher"
    ARCHIVE DESTINATION "lib/watcher"
    RUNTIME DESTINATION "bin"
)
