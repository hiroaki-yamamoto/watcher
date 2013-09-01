project(watcher_loader)
qt5_wrap_cpp(generated_moc
    "category.h"
    "board.h"
    "topic.h"
    "response.h"
)
add_library(loader SHARED
    "root.cxx"
    "content_base.cxx"
    ${generated_moc}
)
set_property(TARGET loader PROPERTY LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
qt5_use_modules(loader Core Widgets)
install(
    TARGETS loader
    LIBRARY DESTINATION "lib/watcher"
    ARCHIVE DESTINATION "lib/watcher"
    RUNTIME DESTINATION "bin"
)
file(GLOB plugin_headers RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "*.h")
install(FILES ${plugin_headers} DESTINATION "include/watcher/loader")
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/FindWatcherLoader.cmake 
        DESTINATION share/cmake-${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}/Modules)
