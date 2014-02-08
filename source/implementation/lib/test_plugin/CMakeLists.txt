project(test_plugin)
qt5_add_resources(resource "images.qrc")

add_custom_command(
    OUTPUT images
    COMMAND cp ARGS -r ${CMAKE_CURRENT_SOURCE_DIR}/images ${CMAKE_BINARY_DIR}/plugins
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/images
    COMMENT "Copying test images..."
)

add_custom_target(
    test_images_copy ALL
    DEPENDS images
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

add_library(test_plugin SHARED 
    "board.cxx"
    "category.cxx"
    "response.cxx"
    "root.cxx"
    "topic.cxx"
    ${resource}
)

set_property(TARGET test_plugin PROPERTY LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/plugins")
target_link_libraries(test_plugin loader)
qt5_use_modules(test_plugin Core Network Widgets)
install(TARGETS test_plugin LIBRARY DESTINATION "share/watcher/plugins")
