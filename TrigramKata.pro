QT       -= core
QT       -= gui

TARGET = TrigramKata
CONFIG   += console
CONFIG   -= app_bundle
QMAKE_POST_LINK += ./TrigramKata

TEMPLATE = app

SOURCES += main.cpp \
    TrigramTest.cpp \
    Trigram.cpp

LIBS += -L$$(GMOCK_ROOT) -lgmock
INCLUDEPATH += $$(GMOCK_ROOT)/include
DEPENDPATH += $$(GMOCK_ROOT)/include
PRE_TARGETDEPS += $$(GMOCK_ROOT)/libgmock.a

LIBS += -L$$(GTEST_ROOT) -lgtest
INCLUDEPATH += $$(GTEST_ROOT)/include
DEPENDPATH += $$(GTEST_ROOT)/include
PRE_TARGETDEPS += $$(GTEST_ROOT)/libgtest.a

HEADERS += \
    Trigram.h







