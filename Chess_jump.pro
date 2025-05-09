#-------------------------------------------------
#
# Project created by QtCreator 2019-04-03T21:38:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Chess_jump
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    human_game_vs.cpp \
    human_choose_vs.cpp \
    vs.cpp

HEADERS  += widget.h \
    human_game_vs.h \
    human_choose_vs.h \
    vs.h

FORMS    += widget.ui \
    human_game_vs.ui \
    human_choose_vs.ui \
    vs.ui

RESOURCES += \
    Image.qrc

OTHER_FILES += \
    image/Luffy.png
