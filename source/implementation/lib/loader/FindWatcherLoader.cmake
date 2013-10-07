set(WatcherLoader_LIBRARIES "loader")
set(WatcherLoader_HEADERS "board.h" "category.h" "content_base.h" "response.h" "root.h" "topic.h")
set(WatcherLoader_VERSION 1.0)

foreach(header IN LISTS WatcherLoader_HEADERS)
    find_path(INTERNAL_HEADERS_DIR "${header}" HINTS "/usr/include/watcher/loader" "/usr/local/include/watcher/loader")
    list(FIND WatcherLoader_INCLUDE_DIR ${INTERNAL_HEADERS_DIR} result)
    if(result EQUAL -1)
        list(APPEND WatcherLoader_INCLUDE_DIR ${INTERNAL_HEADERS_DIR})
    endif(result EQUAL -1)
    unset(INTERNAL_HEADERS_DIR CACHE)
endforeach(header)

foreach(library IN LISTS WatcherLoader_LIBRARIES)
    find_library(INTERNAL_LIBRARIES "${library}" HINTS "/usr/lib/watcher" "/usr/local/lib/watcher")
    list(FIND WatcherLoader_LIBRARIES_DIR ${INTERNAL_LIBRARIES} result)
    if(result EQUAL -1)
        list(APPEND WatcherLoader_LIBRARIES_DIR ${INTERNAL_LIBRARIES})
    endif(result EQUAL -1)
    unset(INTERNAL_LIBRARIES_DIR CACHE)
endforeach(library)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(WatcherLoader
    REQUIRED_VARS WatcherLoader_INCLUDE_DIR WatcherLoader_LIBRARIES_DIR
    VERSION_VAR MODULE_VERSION
    HANDLE_COMPONENTS
)
