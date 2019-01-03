cmake_minimum_required(VERSION 3.5)
project(LaboratorioProgrammazione)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

add_subdirectory(test)

set(SOURCE_FILES main.cpp Matrice.h)
add_executable(matrici ${SOURCE_FILES})

add_library(mytest ${SOURCE_FILES})
target_link_libraries(matrici mytest)