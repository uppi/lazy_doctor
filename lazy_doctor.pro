#-------------------------------------------------
#
# Project created by QtCreator 2013-11-07T14:37:36
#
#-------------------------------------------------
QT_SELECT = qt5
QT += core gui widgets sql printsupport
CONFIG += c++11

TARGET = lazy_doctor
TEMPLATE = app

SOURCES += main.cpp\
    core.cpp \
    pattern.cpp \
    patternstorage.cpp \
    imagepattern.cpp \
    renderedimagepattern.cpp \
    renderedpattern.cpp \
    patternlistwidget.cpp \
    imagefield.cpp \
    presetstorage.cpp \
    presetcombobox.cpp \
    clientstorage.cpp \
    mainwindow.cpp \
    imagepatterneditor.cpp \
    clientform.cpp \
    clientsearchdialog.cpp

HEADERS  += \
    core.h \
    pattern.h \
    patternstorage.h \
    imagepattern.h \
    renderedpattern.h \
    renderedimagepattern.h \
    patternlistwidget.h \
    imagefield.h \
    presetstorage.h \
    presetcombobox.h \
    clientstorage.h \
    mainwindow.h \
    imagepatterneditor.h \
    clientform.h \
    clientsearchdialog.h

OTHER_FILES += \
    data/sample_request.json \
    data/sample_pattern_config.json
