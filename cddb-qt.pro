#-------------------------------------------------
#
# Project created by QtCreator 2020-07-27T20:38:27
#
#-------------------------------------------------

QMAKE_CXXFLAGS += -std=c++17
QT       += core gui
QT       += widgets
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cddb-qt
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    addalbumdialog.cpp \
    addartistdialog.cpp \
    album.cpp \
    albumdialog.cpp \
    artist.cpp \
    artistdialog.cpp \
    cddb.cpp \
    editalbumdialog.cpp \
    editartistdialog.cpp \
    editgenredialog.cpp \
    genredialog.cpp \
        main.cpp \
        mainwindow.cpp \
    addgenredialog.cpp \
    genre.cpp \
    artistview.cpp \
    genreview.cpp \
    albumview.cpp \
    markdownview.cpp \
    partialdate.cpp \
    partialdateedit.cpp

HEADERS += \
    addalbumdialog.h \
    addartistdialog.h \
    album.h \
    albumdialog.h \
    artist.h \
    artistdialog.h \
    cddb.h \
    editalbumdialog.h \
    editartistdialog.h \
    editgenredialog.h \
    genredialog.h \
        mainwindow.h \
    addgenredialog.h \
    genre.h \
    artistview.h \
    genreview.h \
    albumview.h \
    markdownview.h \
    partialdate.h \
    partialdateedit.h

FORMS +=
