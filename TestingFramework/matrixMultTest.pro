TEMPLATE = app
CONFIG += console
CONFIG += c++11
CONFIG -= app_bundle
CONFIG += qt

TARGET = MultiplierBenchmark

SOURCES += src/main.cpp \
    src/benchmaker.cpp \
    src/regularMultiplier.cpp \
    src/matrixMultiplier.cpp \
    src/transposedMultiplier.cpp \
    src/recursiveMultiplier.cpp

HEADERS += \
    src/benchmaker.h \
    src/regularMultiplier.h \
    src/matrixMultiplier.h \
    src/transposedMultiplier.h \
    src/recursiveMultiplier.h \
    src/arrayMaster.h

