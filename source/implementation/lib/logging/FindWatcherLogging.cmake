set(WatcherLogging_LIBRARIES "logging")
set(WatcherLogging_HEADERS "logging.h")
set(WatcherLogging_VERSION 1.0)

foreach(header IN LISTS WatcherLogging_HEADERS)
    find_path(INTERNAL_HEADERS_DIR "${header}" HINTS "/usr/include/watcher/logging" "/usr/local/include/watcher/logging")
    
    list(FIND WatcherLogging_INCLUDE_DIR ${INTERNAL_HEADERS_DIR} result)
    if(result EQUAL -1)
        list(APPEND WatcherLogging_INCLUDE_DIR ${INTERNAL_HEADERS_DIR})
    endif(result EQUAL -1)
    unset(INTERNAL_HEADERS_DIR CACHE)
endforeach(header)

foreach(library IN LISTS WatcherLogging_LIBRARIES)
    find_library(INTERNAL_LIBRARIES "${library}" HINTS "/usr/lib/watcher/logging" "/usr/local/lib/watcher/logging")
    list(FIND WatcherLogging_LIBRARIES_DIR ${INTERNAL_LIBRARIES} result)
    if(result EQUAL -1)
        list(APPEND WatcherLogging_LIBRARIES_DIR ${INTERNAL_LIBRARIES})
    endif(result EQUAL -1)
    unset(INTERNAL_LIBRARIES_DIR CACHE)
endforeach(library)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(WatcherLogging
    REQUIRED_VARS 
        WatcherLogging_INCLUDE_DIR WatcherLogging_LIBRARIES_DIR
    VERSION_VAR MODULE_VERSION
    HANDLE_COMPONENTS
)
