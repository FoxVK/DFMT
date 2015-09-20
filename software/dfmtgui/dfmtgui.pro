#-------------------------------------------------
#
# Project created by QtCreator 2015-09-11T11:05:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dfmtgui
TEMPLATE = app


SOURCES += main.cpp\
        mainwin.cpp \
    device.cpp

HEADERS  += mainwin.h \
    device.h

FORMS    += mainwin.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libdfmt -ldfmt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libdfmt -ldfmt
else:unix: LIBS += -L$$PWD/../libdfmt -ldfmt -lusb-1.0

INCLUDEPATH += $$PWD/../libdfmt
DEPENDPATH += $$PWD/../libdfmt

#win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../libdfmt/libdfmt.a
#else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../libdfmt/libdfmt.a
#else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../libdfmt/dfmt.lib
#else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../libdfmt/dfmt.lib
#else:unix: PRE_TARGETDEPS += $$PWD/../../../libdfmt/libdfmt.a
