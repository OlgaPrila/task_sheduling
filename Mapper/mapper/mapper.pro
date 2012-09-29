TEMPLATE = app
CONFIG += console testlib
CONFIG -= qt

SOURCES += main.cpp \
    dag_line.cpp \
    dag_mapper.cpp

HEADERS += \
    dag_node.h \
    dag_line.h \
    dag_mapper.h

SUBDIRS += test
