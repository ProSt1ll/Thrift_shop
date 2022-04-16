cmake_minimum_required(VERSION 3.15)

project(ThriftShop_server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-g -O0 -Wextra -Wall -Wextra -Wpedantic -lgcov --coverage)
add_link_options( -O0 -lgcov --coverage)

file(GLOB SOURCE "server/src/*.cpp")
file(GLOB INCLUDE "server/include/*.h")

find_package (Threads REQUIRED)
add_compile_options(-pthread)
find_package(Boost REQUIRED)

include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
add_library(server_lib ${INCLUDE} ${SOURCE} )

add_executable(main.out server/main.cpp)
target_link_libraries(main.out server_lib ${Boost_LIBRARIES})

enable_testing()
find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

add_executable(tests server/tests/mock_server.cpp)
target_link_libraries(tests GTest::gtest_main lib gmock)


