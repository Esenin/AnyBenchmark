TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += qt
CONFIG += static

QMAKE_CXXFLAGS += -std=c++11
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
    tests/binaryTree/bTree.cpp \
    tests/binaryTree/testTreeAdapter.cpp \
    tests/binaryTree/vEBLayoutBinTree.cpp \
    tests/binaryTree/avlTree.cpp \
    tests/binaryTree/stlMap.cpp

HEADERS += \
    src/benchmaker.h \
    src/testObject.h \
    tests/matrixMultiplying/regularMultiplier.h \
    tests/matrixMultiplying/matrixMultiplier.h \
    tests/matrixMultiplying/transposedMultiplier.h \
    tests/matrixMultiplying/recursiveMultiplier.h \
    tests/matrixMultiplying/arrayMaster.h \
    tests/binaryTree/iTree.h \
    tests/binaryTree/bTree.h \
    tests/binaryTree/testTreeAdapter.h \
    tests/binaryTree/treeTestLauncher.h \
    tests/matrixMultiplying/multiplicationTestLauncher.h \
    tests/binaryTree/vEBLayoutBinTree.h \
    tests/binaryTree/avlTree.h \
    tests/binaryTree/stlMap.h

