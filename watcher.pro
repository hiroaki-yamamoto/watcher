TEMPLATE = subdirs
INCLUDEPATH += .
QT+=qml quick widgets
QMAKE_CXXFLAGS+= -std=gnu++11
SUBDIRS=source
OTHER_FILES+=CMakeLists.txt
