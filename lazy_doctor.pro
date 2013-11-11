#-------------------------------------------------
#
# Project created by QtCreator 2013-11-07T14:37:36
#
#-------------------------------------------------
QT_SELECT = qt5
QT += core gui widgets
CONFIG += c++11

TARGET = lazy_doctor
TEMPLATE = app

SOURCES += main.cpp\
        lazymainwindow.cpp \
    core.cpp \
    pattern.cpp \
    patternstorage.cpp \
    imagepattern.cpp \
    renderedimagepattern.cpp \
    renderedpattern.cpp \
    patternlistwidget.cpp \
    infoform.cpp \
    imagefield.cpp

HEADERS  += lazymainwindow.h \
    core.h \
    pattern.h \
    patternstorage.h \
    imagepattern.h \
    renderedpattern.h \
    renderedimagepattern.h \
    patternlistwidget.h \
    infoform.h \
    imagefield.h

OTHER_FILES += \
    data/sample_request.json \
    data/sample_pattern_config.json