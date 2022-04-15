cmake_minimum_required(VERSION 3.14)
project(BI)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fprofile-arcs -ftest-coverage -O0")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lsqlite3 -pthread -lgcov")

file(GLOB SOURCES "sources/*.cpp")
file(GLOB INCLUDE "headers/*.h")
file(GLOB EXC "main.cpp")
file(GLOB EXC_TEST "tests/*.cpp")

message("SOURCES = ${SOURCES}")
message("INCLUDE = ${INCLUDE}")

add_library(lib ${INCLUDE} ${SOURCES})
SET_TARGET_PROPERTIES(lib PROPERTIES LINKER_LANGUAGE CXX)

add_executable(tests ${EXC_TEST})
target_link_libraries(tests gmock)
target_link_libraries(tests lib)
