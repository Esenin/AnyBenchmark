# Author: Ivan Senin (senin-i-i@ya.ru)

cmake_minimum_required(VERSION 3.2)
project(AnyBenchmark)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if(NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++") # use for clang debugging
  #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lc++abi")
  endif()


set(SOURCE_FILES
    TestingFramework/src/pipelineHandlers/benchmarkEvent.h
    TestingFramework/src/pipelineHandlers/consoleWriter.cpp
    TestingFramework/src/pipelineHandlers/consoleWriter.h
    TestingFramework/src/pipelineHandlers/fileWriter.cpp
    TestingFramework/src/pipelineHandlers/fileWriter.h
    TestingFramework/src/pipelineHandlers/iEventHandler.h
    TestingFramework/src/pipelineHandlers/pipelineHolder.cpp
    TestingFramework/src/pipelineHandlers/pipelineHolder.h
    TestingFramework/src/benchmaker.cpp
    TestingFramework/include/benchmaker.h
    TestingFramework/include/iTestObject.h
    TestingFramework/include/constants.h)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/TestingFramework/include)

target_link_libraries(${PROJECT_NAME})
