TEMPLATE = lib
CONFIG += staticlib
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

unix: TARGET = dfmt #avoid use liblib in ouput file


SOURCES += main.c \
    src/device.c \
    src/devices.c \
    src/hl_rds.c \
    src/hl_tuning.c \
    src/libdfmt.c \
    src/ll_i2c.c \
    src/ll_ping.c \
    src/lusb_error_tr.c \
    src/ml_command.c \
    src/ml_property.c \
    src/test.c


QMAKE_LINK = $$QMAKE_LINK_C


unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += libusb-1.0

HEADERS += \
    libdfmt.h \
    libdfmt_cmds_props.h \
    include/devices.h \
    include/libdfmt_device.h \
    include/libdfmt_tuner.h \
    include/lusb_error_tr.h \
    include/shared.h

INCLUDEPATH += $$PWD/include/

