TEMPLATE=subdirs
SUBDIRS+=lib
HEADERS+=   setting_loader.h \
            plugin_loader.h \
            setting_default.h

SOURCES+=   main.cxx \
            setting_loader.cxx \
            plugin_loader.cxx \
            setting_default.cxx

OTHER_FILES += CMakeLists.txt
