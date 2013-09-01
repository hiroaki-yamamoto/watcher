TEMPLATE=lib
TARGET=4chan

HEADERS+=board.h \
        category.h \
        response.h \
        root.h \
        topic.h \
        error.h \
        attribute.h \
        enum_convert.h \
        api_urls.h

SOURCES+=board.cxx \
        category.cxx \
        response.cxx \
        root.cxx \
        topic.cxx \
        error.cxx \
        attribute.cxx \
        enum_convert.cxx \
        api_urls.cxx

OTHER_FILES+=CMakeLists.txt \
            root.json
