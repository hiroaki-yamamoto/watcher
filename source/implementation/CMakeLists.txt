project(watcher-exe)
add_custom_command(
    OUTPUT git_commit
    COMMAND sh create_version ARGS ${CMAKE_CURRENT_BINARY_DIR}/version
    DEPENDS "${CMAKE_SOURCE_DIR}/.git"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Generating version information."
)
add_custom_target(write_git_commit ALL
    DEPENDS git_commit
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_subdirectory(lib)
set(src "main.cxx"
        "setting_loader.cxx"
        "plugin_loader.cxx"
        "setting_default.cxx"
)

add_executable(watcher ${src})
set_property(TARGET watcher PROPERTY RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
target_link_libraries(watcher watcher_ui storage loader logging)

qt5_use_modules(watcher Core Widgets)
add_dependencies(watcher write_git_commit)
install(
    TARGETS watcher
    LIBRARY DESTINATION "lib/watcher"
    ARCHIVE DESTINATION "lib/watcher"
    RUNTIME DESTINATION "bin"
)
