TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.c \
        mwindow.c

LIBS += -L/usr/lib64/ncurses6 -lncursesw
INCLUDEPATH += /usr/include/ncurses6/ncurses
DEPENDPATH += /usr/include/ncurses6/ncurses

LIBS += -L/usr/lib64/panel.h -lpanel
INCLUDEPATH += /usr/include/panel.h
DEPENDPATH += /usr/include/panel.h

HEADERS += \
    mwindow.h
