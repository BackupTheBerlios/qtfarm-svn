QMAKE_RPATH = -Wl,-rpath \
    \$$ORIGIN

# LIBS += \$$ORIGIN\
TEMPLATE = app
CONFIG += wwwidgets
QT += core \
    gui \
    sql \
    xml \
    network
HEADERS = centraltab.h \
    cornerwidget.h \
    widgetfilter.h \
    listtableview.h \
    dockwidgetlist.h \
    dialogpluginsettings.h \
    qtfarmplugininterfaces.h \
    plugindialog.h \
    qtfarm.h
SOURCES = centraltab.cpp \
    cornerwidget.cpp \
    widgetfilter.cpp \
    listtableview.cpp \
    dockwidgetlist.cpp \
    dialogpluginsettings.cpp \
    plugindialog.cpp \
    qtfarm.cpp \
    main.cpp
FORMS = centraltab.ui \
    cornerwidget.ui \
    widgetfilter.ui \
    dockwidgetlist.ui \
    dialogpluginsettings.ui
TARGET = qtfarm
win32 { 
    debug:DESTDIR = ../debug/
    release:DESTDIR = ../release/
}
else:DESTDIR = ../bin/
TARGET = QtFarm
RESOURCES = qtfarm.qrc
