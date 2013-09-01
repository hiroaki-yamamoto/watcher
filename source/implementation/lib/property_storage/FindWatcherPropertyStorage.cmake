set(WatcherPropertyStorage_LIBRARIES "storage")
set(WatcherPropertyStorage_HEADERS "property_storage.h")
set(WatcherPropertyStorage_VERSION 1.0)

foreach(header IN LISTS WatcherPropertyStorage_HEADERS)
    find_path(INTERNAL_HEADERS_DIR "${header}" HINTS "/usr/include/watcher/property_storage" "/usr/local/include/watcher/property_storage")
    
    list(FIND WatcherPropertyStorage_INCLUDE_DIR ${INTERNAL_HEADERS_DIR} result)
    if(result EQUAL -1)
        list(APPEND WatcherPropertyStorage_INCLUDE_DIR ${INTERNAL_HEADERS_DIR})
    endif(result EQUAL -1)
    unset(INTERNAL_HEADERS_DIR CACHE)
endforeach(header)

foreach(library IN LISTS WatcherPropertyStorage_LIBRARIES)
    find_library(INTERNAL_LIBRARIES "${library}" HINTS "/usr/lib/watcher" "/usr/local/lib/watcher")
    list(FIND WatcherPropertyStorage_LIBRARIES_DIR ${INTERNAL_LIBRARIES} result)
    if(result EQUAL -1)
        list(APPEND WatcherPropertyStorage_LIBRARIES_DIR ${INTERNAL_LIBRARIES})
    endif(result EQUAL -1)
    unset(INTERNAL_LIBRARIES_DIR CACHE)
endforeach(library)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(WatcherPropertyStorage
    REQUIRED_VARS 
        WatcherPropertyStorage_INCLUDE_DIR WatcherPropertyStorage_LIBRARIES_DIR
    VERSION_VAR MODULE_VERSION
    HANDLE_COMPONENTS
)
