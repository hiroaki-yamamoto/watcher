project(watcher-bin)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(libserializer REQUIRED)

if(EXPERIMENTAL)
    add_definitions(-DEXPERIMENT)
    mesage(STATUS "Experimental mode. The software made by this mode has a lot of bugs!")
endif(EXPERIMENTAL)

if(NOT UNIX)
    message(FATAL_ERROR "This software uses POSIX API. Unfortunately, your operating system is not based on POSIX.")
endif(NOT UNIX)

if(CMAKE_COMPILER_IS_GNUCXX)
    execute_process(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
    if(GCC_VERSION VERSION_LESS "4.7")
        set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS}")
    else(GCC_VERSION VERSION_LESS "4.7")
        set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
    endif(GCC_VERSION VERSION_LESS "4.7")
else(CMAKE_COMPILER_IS_GNUCXX)
    message(FATAL_ERROR "This software uses GNU C++ Compiler. Unfortunately, your compiler is not GNUCXX.")
endif(CMAKE_COMPILER_IS_GNUCXX)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
    add_definitions(-DDEBUG)
    message(STATUS "Debugging mode is enabled. This is not recommended for normal uses.")
endif(CMAKE_BUILD_TYPE STREQUAL "Debug")

include_directories(
    ${libserializer_INCLUDE_DIR}
    "${CMAKE_CURRENT_SOURCE_DIR}/ui"
    "${CMAKE_CURRENT_SOURCE_DIR}/implementation"
    "${CMAKE_CURRENT_SOURCE_DIR}/implementation/lib"
    "${CMAKE_CURRENT_SOURCE_DIR}/implementation/lib/property_storage"
    "${CMAKE_CURRENT_SOURCE_DIR}/implementation/lib/loader"
    "${CMAKE_CURRENT_SOURCE_DIR}/implementation/lib/logging"
)
add_subdirectory(implementation)
add_subdirectory(ui)

install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ui/default
    DESTINATION "share/watcher/themes"
)
