TEMPLATE=lib
TARGET=test_plugin

HEADERS +=  board.h \
            category.h \
            response.h \
            root.h \
            topic.h

SOURCES +=  board.cxx \
            category.cxx \
            response.cxx \
            root.cxx \
            topic.cxx

OTHER_FILES+=CMakeLists.txt root.json

RESOURCES += \
    images.qrc
