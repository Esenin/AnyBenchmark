TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += static

QMAKE_CXXFLAGS += -std=c++14
#QMAKE_CXXFLAGS += -O2

CONFIG(debug, debug | release) {
	CONFIGURATION = debug
} else {
	CONFIGURATION = release

}

DESTDIR = $$PWD/bin/$$CONFIGURATION

OBJECTS_DIR = $$PWD/build/$$CONFIGURATION/obj
MOC_DIR = $$PWD/build/$$CONFIGURATION/moc


TARGET = benchmark

SOURCES += src/main.cpp \
    src/benchmaker.cpp \
    tests/matrixMultiplying/regularMultiplier.cpp \
    tests/matrixMultiplying/matrixMultiplier.cpp \
    tests/matrixMultiplying/transposedMultiplier.cpp \
    tests/matrixMultiplying/recursiveMultiplier.cpp \
    src/pipelineHandlers/fileWriter.cpp \
    src/pipelineHandlers/consoleWriter.cpp \
    src/pipelineHandlers/pipelineHolder.cpp


HEADERS += \
    src/benchmaker.h \
    tests/matrixMultiplying/regularMultiplier.h \
    tests/matrixMultiplying/matrixMultiplier.h \
    tests/matrixMultiplying/transposedMultiplier.h \
    tests/matrixMultiplying/recursiveMultiplier.h \
    tests/matrixMultiplying/arrayMaster.h \
    tests/matrixMultiplying/multiplicationTestLauncher.h \
    src/iTestObject.h \
    src/pipelineHandlers/fileWriter.h \
    src/pipelineHandlers/consoleWriter.h \
    src/pipelineHandlers/pipelineHolder.h \
    src/pipelineHandlers/benchmarkEvent.h \
    src/pipelineHandlers/iEventHandler.h


OTHER_FILES +=

