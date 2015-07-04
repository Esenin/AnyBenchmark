cmake_minimum_required(VERSION 3.2)
project(AnyBenchmark)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++") # use for clang debugging
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lc++abi")

set(SOURCE_FILES
    src/pipelineHandlers/benchmarkEvent.h
    src/pipelineHandlers/consoleWriter.cpp
    src/pipelineHandlers/consoleWriter.h
    src/pipelineHandlers/fileWriter.cpp
    src/pipelineHandlers/fileWriter.h
    src/pipelineHandlers/iEventHandler.h
    src/pipelineHandlers/pipelineHolder.cpp
    src/pipelineHandlers/pipelineHolder.h
    src/benchmaker.cpp
    src/main.cpp
    include/benchmaker.h
    include/iTestObject.h
    tests/matrixMultiplying/arrayMaster.h
    tests/matrixMultiplying/matrixMultiplier.cpp
    tests/matrixMultiplying/matrixMultiplier.h
    tests/matrixMultiplying/multiplicationTestLauncher.h
    tests/matrixMultiplying/recursiveMultiplier.cpp
    tests/matrixMultiplying/recursiveMultiplier.h
    tests/matrixMultiplying/regularMultiplier.cpp
    tests/matrixMultiplying/regularMultiplier.h
    tests/matrixMultiplying/transposedMultiplier.cpp
    tests/matrixMultiplying/transposedMultiplier.h)

add_executable(AnyBenchmark ${SOURCE_FILES})