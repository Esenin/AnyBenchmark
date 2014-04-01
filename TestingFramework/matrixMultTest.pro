TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += qt

QMAKE_CXXFLAGS += -std=c++11

TARGET = benchmark

SOURCES += src/main.cpp \
    src/benchmaker.cpp \
    tests/matrixMultiplying/regularMultiplier.cpp \
    tests/matrixMultiplying/matrixMultiplier.cpp \
    tests/matrixMultiplying/transposedMultiplier.cpp \
    tests/matrixMultiplying/recursiveMultiplier.cpp

HEADERS += \
    src/benchmaker.h \
	src/testObject.h \
    tests/matrixMultiplying/regularMultiplier.h \
    tests/matrixMultiplying/matrixMultiplier.h \
    tests/matrixMultiplying/transposedMultiplier.h \
    tests/matrixMultiplying/recursiveMultiplier.h \
    tests/matrixMultiplying/arrayMaster.h

