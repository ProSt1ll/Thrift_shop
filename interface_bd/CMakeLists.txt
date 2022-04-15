cmake_minimum_required(VERSION 3.14)

include("hunter/HunterGate.cmake")
HunterGate(
        URL "https://github.com/cpp-pm/hunter/archive/v0.23.297.tar.gz"
        SHA1 "3319fe6a3b08090df7df98dee75134d68e2ef5a3"
)

project(BI)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fprofile-arcs -ftest-coverage -fPIC -O0")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -l sqlite3 -lgcov")

file(GLOB SOURCES "sources/*.cpp")
file(GLOB INCLUDE "headers/*.h")
file(GLOB EXC "main.cpp")
file(GLOB EXC_TEST "tests/*.cpp")

message("SOURCES = ${SOURCES}")
message("INCLUDE = ${INCLUDE}")

hunter_add_package(GTest)

find_package(GTest CONFIG REQUIRED)

add_library(lib ${INCLUDE} ${SOURCES})
SET_TARGET_PROPERTIES(lib PROPERTIES LINKER_LANGUAGE CXX)

add_executable(tests ${EXC_TEST})
target_link_libraries(tests gmock)
target_link_libraries(tests lib)
