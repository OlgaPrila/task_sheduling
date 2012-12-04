TEMPLATE = app
CONFIG += console testlib
#CONFIG -= qt

SOURCES += \
    abstractresultprinter.cpp \
    configurator.cpp \
    main.cpp \
    nullparser.cpp \
    nullscanner.cpp \
    algorithm.cpp \
    graphprinter.cpp


HEADERS += \
    configurator.h \
    abstractalgorithm.h \
    abstractparser.h \
    graph.h \
    abstractresultprinter.h \
    result.h \
    abstractscanner.h \
    nullparser.h \
    nullscanner.h \
    algorithm.h \
    graphprinter.h

SUBDIRS += test

LIBS += -lboost_graph
