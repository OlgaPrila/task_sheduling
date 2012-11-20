TEMPLATE = app
CONFIG += console testlib
#CONFIG -= qt

SOURCES += \
    configurator.cpp \
    result.cpp \
    main.cpp

HEADERS += \
    configurator.h \
    abstractalgorithm.h \
    abstractparser.h \
    graph.h \
    abstractresultprinter.h \
    result.h \
    abstractscanner.h

SUBDIRS += test

LIBS += -lboost_graph
