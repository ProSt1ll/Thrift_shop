cmake_minimum_required(VERSION 2.8.4)

project(TgBot)

set(CMAKE_CXX_STANDARD 11)

file(GLOB INCLUDE "Headers/*.h")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fprofile-arcs -ftest-coverage -fPIC -O0")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov")

file(GLOB SOURCE "src/*.cpp")
file(GLOB INCLUDE "include/*" "include/*" )

set(Boost_USE_MULTITHREADED ON)

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost 1.74.0 REQUIRED)
add_definitions(-DBOOST_BIND_GLOBAL_PLACEHOLDERS)

find_package(CURL)
include_directories(/usr/local/include ${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIR})
if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    add_definitions(-DHAVE_CURL)
endif()


add_library(lib ${INCLUDE} ${SOURCE} )

add_executable(main main.cpp)

enable_testing()

find_package(GTest REQUIRED)

#add_executable(tests tests/Tests.cpp)

#target_link_libraries(tests GTest::gtest_main lib gmock)

target_link_libraries(main lib /usr/local/lib/libTgBot.a ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES} ${CURL_LIBRARIES})