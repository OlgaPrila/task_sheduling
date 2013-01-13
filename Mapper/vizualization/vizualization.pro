#-------------------------------------------------
#
# Project created by QtCreator 2012-12-11T10:09:58
#
#-------------------------------------------------

QT       += core gui

TARGET = vizualization
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ../mapper/timebasedalgorithm.cpp \
    ../mapper/nullscanner.cpp \
    ../mapper/nullparser2.cpp \
    ../mapper/nullparser.cpp \
#    ../mapper/main.cpp \
    ../mapper/graphprinter.cpp \
    ../mapper/graph.cpp \
    ../mapper/configurator.cpp \
    ../mapper/algorithm.cpp \
    ../mapper/abstractresultprinter.cpp

HEADERS  += mainwindow.h \
    ../mapper/timebasedalgorithm.h \
    ../mapper/result.h \
    ../mapper/nullscanner.h \
    ../mapper/nullparser2.h \
    ../mapper/nullparser.h \
    ../mapper/graphprinter.h \
    ../mapper/graph.h \
    ../mapper/configurator.h \
    ../mapper/algorithm.h \
    ../mapper/abstractscanner.h \
    ../mapper/abstractresultprinter.h \
    ../mapper/abstractparser.h \
    ../mapper/abstractalgorithm.h

FORMS    += mainwindow.ui
