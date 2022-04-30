cmake_minimum_required(VERSION 3.14)

### hunter ###
include("hunter/HunterGate.cmake")
HunterGate(
        URL "https://github.com/cpp-pm/hunter/archive/v0.23.278.tar.gz"
        SHA1 "35fa55bc1dfcf9f4d7264f8bb26cd1759ce1ae07"
)

### base settings ###

project(Crawler)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "")
#set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fprofile-arcs -ftest-coverage -fPIC -O0 -pthread")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov")

### directories variables ###

file(GLOB SOURCES "Sources/*.cpp")
file(GLOB INCLUDE "Headers/*.h")
file(GLOB EXC "main.cpp")
file(GLOB EXC_TEST "Tests/*.cpp")

### hunter ###

hunter_add_package(asio)
hunter_add_package(Beast)
hunter_add_package(Boost)
hunter_add_package(gumbo)
hunter_add_package(nlohmann_json)
hunter_add_package(GTest)

find_package(asio CONFIG REQUIRED)
find_package(Beast CONFIG REQUIRED)
find_package(Boost CONFIG REQUIRED)
find_package(gumbo CONFIG REQUIRED)
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
