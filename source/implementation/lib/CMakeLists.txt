project(libs)
add_subdirectory("loader")
add_subdirectory("property_storage")
add_subdirectory("yotsuba")

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug" OR BUILD_TEST_PLUGIN)
    add_subdirectory("test_plugin")
endif("${CMAKE_BUILD_TYPE}" STREQUAL "Debug" OR BUILD_TEST_PLUGIN)
