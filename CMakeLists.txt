cmake_minimum_required(VERSION 3.14)

project(TgBot)

set(CMAKE_CXX_STANDARD 11)

file(GLOB INCLUDE "Headers/*.h")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fprofile-arcs -ftest-coverage -fPIC -O0")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov")

file(GLOB SOURCE "src/*.cpp")
file(GLOB INCLUDE "include/*")
find_package(Boost 1.65.1 REQUIRED)
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
add_library(lib ${INCLUDE} ${SOURCE} )

add_executable(main main.cpp)

enable_testing()

find_package(GTest REQUIRED)

add_executable(tests tests/Tests.cpp)

target_link_libraries(tests GTest::gtest_main lib gmock)

target_link_libraries(main lib ${Boost_LIBRARIES})