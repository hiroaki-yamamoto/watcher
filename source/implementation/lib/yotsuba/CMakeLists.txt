project(yotsuba)
option(YOTSUBA_TRACE_HEADER "Trace HTTP request header and response header" OFF)
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
    "trace.cxx"
)
if(YOTSUBA_TRACE_HEADER)
    add_definitions(DTRACE_HEADER)
endif(YOTSUBA_TRACE_HEADER)
set_property(TARGET yotsuba PROPERTY LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/plugins")
qt5_use_modules(yotsuba Core Network Widgets)
install(TARGETS yotsuba LIBRARY DESTINATION "share/watcher/plugins")
