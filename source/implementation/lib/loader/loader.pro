TEMPLATE=lib
TARGET=loader
INCLUDEPATH += ..
HEADERS+=root.h category.h board.h topic.h response.h content_base.h
SOURCES+=response.cxx root.cxx content_base.cxx
OTHER_FILES+=CMakeLists.txt FindWatcherLoader.cmake 
