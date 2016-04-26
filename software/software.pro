TEMPLATE = subdirs

SUBDIRS += \
    dfmtgui \
    libdfmt

dfmtgui.depends = libdfmt
