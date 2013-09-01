project(property_storage)
add_library(storage SHARED "property_storage.cxx" "operators.cxx")
set_property(TARGET storage PROPERTY LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
target_link_libraries(storage ${libserializer_LIBRARIES})
qt5_use_modules(storage Core)
install(
    TARGETS storage
    LIBRARY DESTINATION "lib/watcher"
    ARCHIVE DESTINATION "lib/watcher"
    RUNTIME DESTINATION "bin"
)
install(FILES "property_storage.h" DESTINATION "include/watcher/property_storage")
install(FILES "FindWatcherPropertyStorage.cmake" DESTINATION "share/cmake-${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}/Modules")
