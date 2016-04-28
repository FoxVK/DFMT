#-------------------------------------------------
#
# Project created by QtCreator 2015-09-11T11:05:47
#
#-------------------------------------------------

QTPLUGIN += svg

QT       += core gui
QT       += svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dfmtgui
TEMPLATE = app


SOURCES += main.cpp\
        mainwin.cpp \
    device.cpp \
    devices.cpp \
    deviceform.cpp \
    nodeviceform.cpp

HEADERS  += mainwin.h \
    device.h \
    devices.h \
    deviceform.h \
    nodeviceform.h

FORMS    += mainwin.ui \
    deviceform.ui \
    nodeviceform.ui

RESOURCES += \
    icons.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libdfmt/release/ -ldfmt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libdfmt/debug/ -llibdfmt
else:unix:!macx: LIBS += -L$$OUT_PWD/../libdfmt/ -ldfmt


unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += libusb-1.0

INCLUDEPATH += $$PWD/../libdfmt
DEPENDPATH += $$PWD/../libdfmt

win32-g++:CONFIG(release, debug|release): #PRE_TARGETDEPS += $$OUT_PWD/../libdfmt/release/libdfmt.a
else:win32-g++:CONFIG(debug, debug|release): #PRE_TARGETDEPS += $$OUT_PWD/../libdfmt/debug/libdfmt.a
else:unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../libdfmt/libdfmt.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lusb-win/ -lusb-1.0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lusb-win/ -lusb-1.0

win32:INCLUDEPATH += $$PWD/../lusb-win/
win32:DEPENDPATH += $$PWD/../lusb-win/


INCLUDEPATH += $$PWD/../libdfmt
DEPENDPATH += $$PWD/../libdfmt
