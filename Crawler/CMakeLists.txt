cmake_minimum_required(VERSION 3.14)

### hunter ###
include("hunter/HunterGate.cmake")
HunterGate(
        URL "https://github.com/cpp-pm/hunter/archive/v0.23.297.tar.gz"
        SHA1 "3319fe6a3b08090df7df98dee75134d68e2ef5a3"
)

### base settings ###

project(Crawler)

set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fprofile-arcs -ftest-coverage -fPIC -O0")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov")

### directories variables ###

file(GLOB SOURCES "Sources/*.cpp")
file(GLOB INCLUDE "Headers/*.h")
file(GLOB EXC "main.cpp")
file(GLOB EXC_TEST "Tests/*.cpp")

### hunter ###

hunter_add_package(nlohmann_json)
hunter_add_package(GTest)

find_package(nlohmann_json CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)

### making executables, linking libraries ###

add_library(lib ${INCLUDE} ${SOURCES})
add_executable(main ${EXC})
target_link_libraries(lib nlohmann_json::nlohmann_json)
target_link_libraries(main lib)

add_executable(tests ${EXC_TEST})

target_link_libraries(tests GTest::gtest_main)
target_link_libraries(tests lib)
