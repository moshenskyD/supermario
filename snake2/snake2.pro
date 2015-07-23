#-------------------------------------------------
#
# Project created by QtCreator 2015-07-18T05:30:33
#
#-------------------------------------------------

QT       += core gui
QT += opengl



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = snake2
TEMPLATE = app


SOURCES += main.cpp

HEADERS  += \
    texture.h \
    collision.h \
    coords.h

QMAKE_LIBS_OPENGL = -lGL -lglut -lGLU

FORMS    += mainwindow.ui

OTHER_FILES += \
    mario_jump.bmp
