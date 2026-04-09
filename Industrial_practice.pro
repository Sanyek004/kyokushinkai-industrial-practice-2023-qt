#-------------------------------------------------
#
# Project created by QtCreator 2023-05-02T12:41:51
#
#-------------------------------------------------

QT       += core gui sql    printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Industrial_practice
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    search_student.cpp \
    search_coach.cpp \
    search_table.cpp \
    mixed.cpp \
    single.cpp \
    coach.cpp

HEADERS += \
        mainwindow.h \
    connect.h \
    search_student.h \
    search_coach.h \
    search_table.h \
    mixed.h \
    single.h \
    coach.h

FORMS += \
        mainwindow.ui \
    search_student.ui \
    search_coach.ui \
    search_table.ui \
    mixed.ui \
    single.ui \
    coach.ui
