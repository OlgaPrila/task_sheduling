TEMPLATE = app
CONFIG += console testlib
CONFIG -= qt

SOURCES += main.cpp \
    dag_tree.cpp

HEADERS += \
    dag_node.h \
    dag_line.h \
    dag_tree.h

SUBDIRS += test
