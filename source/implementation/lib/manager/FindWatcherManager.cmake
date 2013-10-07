set(WatcherManager_LIBRARIES "manager")
set(WatcherManager_HEADERS "imagemanager.h")
set(WatcherManager_VERSION 1.0)

foreach(header IN LISTS WatcherManager_HEADERS)
    find_path(INTERNAL_HEADERS_DIR "${header}" HINTS "/usr/include/watcher/manager" "/usr/local/include/watcher/manager")
    
    list(FIND WatcherManager_INCLUDE_DIR ${INTERNAL_HEADERS_DIR} result)
    if(result EQUAL -1)
        list(APPEND WatcherManager_INCLUDE_DIR ${INTERNAL_HEADERS_DIR})
    endif(result EQUAL -1)
    unset(INTERNAL_HEADERS_DIR CACHE)
endforeach(header)

foreach(library IN LISTS WatcherManager_LIBRARIES)
    find_library(INTERNAL_LIBRARIES "${library}" HINTS "/usr/lib/watcher/manager" "/usr/local/lib/watcher/manager")
    list(FIND WatcherManager_LIBRARIES_DIR ${INTERNAL_LIBRARIES} result)
    if(result EQUAL -1)
        list(APPEND WatcherManager_LIBRARIES_DIR ${INTERNAL_LIBRARIES})
    endif(result EQUAL -1)
    unset(INTERNAL_LIBRARIES_DIR CACHE)
endforeach(library)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(WatcherManager
    REQUIRED_VARS 
        WatcherManager_INCLUDE_DIR WatcherManager_LIBRARIES_DIR
    VERSION_VAR MODULE_VERSION
    HANDLE_COMPONENTS
)
