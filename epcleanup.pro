QT += core network
QT -= gui

TARGET = epcleanup
CONFIG -= console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    cleaner.cpp \
    reader.cpp \
    logger.cpp

HEADERS += \
    cleaner.h \
    reader.h \
    logger.h

