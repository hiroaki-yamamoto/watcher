project(yotsuba)
add_library(yotsuba SHARED 
    "api_urls.cxx"
    "attribute.cxx"
    "board.cxx"
    "category.cxx"
    "enum_convert.cxx"
    "error.cxx"
    "response.cxx"
    "root.cxx"
    "topic.cxx"
)
set_property(TARGET yotsuba PROPERTY LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/plugins")
qt5_use_modules(yotsuba Core Network Widgets)
install(TARGETS yotsuba LIBRARY DESTINATION "share/watcher/plugins")
