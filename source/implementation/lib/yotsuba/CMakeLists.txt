project(yotsuba)
find_package(OpenMP REQUIRED)
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
set_property(TARGET yotsuba PROPERTY COMPILE_FLAGS "${OpenMP_CXX_FLAGS}")
target_link_libraries(yotsuba loader gomp)
set_property(TARGET yotsuba PROPERTY LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/plugins")
qt5_use_modules(yotsuba Core Network)
install(TARGETS yotsuba LIBRARY DESTINATION "share/watcher/plugins")
