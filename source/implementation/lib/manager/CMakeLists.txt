project(watcher-logging)
set(source
    "imagemanager.cxx"
    "pixelmanager.cxx"
)
add_library(manager SHARED ${source})
set_property(TARGET logging PROPERTY LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
qt5_use_modules(manager Core Widgets)
install(
    TARGETS manager
    LIBRARY DESTINATION "lib/watcher"
    ARCHIVE DESTINATION "lib/watcher"
    RUNTIME DESTINATION "bin"
)
file(GLOB plugin_headers RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "*.h")
install(FILES ${plugin_headers} DESTINATION "include/watcher/manager")
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/FindWatcherManager.cmake 
        DESTINATION share/cmake-${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}/Modules)
