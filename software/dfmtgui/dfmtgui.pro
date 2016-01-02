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
    device.cpp \
    devices.cpp \
    deviceform.cpp

HEADERS  += mainwin.h \
    device.h \
    devices.h \
    deviceform.h

FORMS    += mainwin.ui \
    deviceform.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libdfmt -ldfmtwin32 -L$$PWD/../libdfmt/lusb-win -lusb-1.0
else:unix: LIBS += -L$$PWD/../libdfmt -ldfmt -lusb-1.0

INCLUDEPATH += $$PWD/../libdfmt
DEPENDPATH += $$PWD/../libdfmt

RESOURCES += \
    icons.qrc
