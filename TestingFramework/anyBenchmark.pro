TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += qt

QMAKE_CXXFLAGS += -std=c++11
#QMAKE_CXXFLAGS -= -O1
#QMAKE_CXXFLAGS += -O2


TARGET = benchmark

SOURCES += src/main.cpp \
    src/benchmaker.cpp \
    tests/matrixMultiplying/regularMultiplier.cpp \
    tests/matrixMultiplying/matrixMultiplier.cpp \
    tests/matrixMultiplying/transposedMultiplier.cpp \
    tests/matrixMultiplying/recursiveMultiplier.cpp \
    tests/binaryTree/splayTree.cpp \
    tests/binaryTree/bTree.cpp \
    tests/binaryTree/testTreeAdapter.cpp

HEADERS += \
    src/benchmaker.h \
    src/testObject.h \
    tests/matrixMultiplying/regularMultiplier.h \
    tests/matrixMultiplying/matrixMultiplier.h \
    tests/matrixMultiplying/transposedMultiplier.h \
    tests/matrixMultiplying/recursiveMultiplier.h \
    tests/matrixMultiplying/arrayMaster.h \
    tests/binaryTree/vanEmdeBoasTree.h \
    tests/binaryTree/iTree.h \
    tests/binaryTree/splayTree.h \
    tests/binaryTree/bTree.h \
    tests/binaryTree/testTreeAdapter.h \
    tests/binaryTree/treeTestLauncher.h \
    tests/matrixMultiplying/multiplicationTestLauncher.h

