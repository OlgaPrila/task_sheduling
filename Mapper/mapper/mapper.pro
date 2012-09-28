TEMPLATE = app
CONFIG += console testlib
CONFIG -= qt

SOURCES += main.cpp \
    dag_line.cpp

HEADERS += \
    dag_node.h \
    dag_line.h

SUBDIRS += test
