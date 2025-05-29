QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    coord.cpp \
    main.cpp \
    mainwindow.cpp \
    tile.cpp \
    tilemap.cpp

HEADERS += \
    coord.h \
    mainwindow.h \
    tile.h \
    tilemap.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += resources.qrc \
    resources.qrc
