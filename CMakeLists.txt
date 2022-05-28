cmake_minimum_required(VERSION 3.14)
### hunter ###
include("hunter/HunterGate.cmake")
HunterGate(
        URL "https://github.com/cpp-pm/hunter/archive/v0.23.278.tar.gz"
        SHA1 "35fa55bc1dfcf9f4d7264f8bb26cd1759ce1ae07"
)

project(ThriftShop_server)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fprofile-arcs -ftest-coverage -fPIC -O0 -pthread")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -l sqlite3 -lgcov")

set(CMAKE_THREAD_LIBS_INIT "-lpthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)


#add_compile_options(-g -O0 -Wextra -Wall -Wextra -Wpedantic -lgcov --coverage)
#add_link_options( -O0 -lgcov --coverage)

##bd
file(GLOB SOURCES_BD "interface_bd/sources/*.cpp")
file(GLOB INCLUDE_BD "interface_bd/headers/*.h")

message("SOURCES_BD = ${SOURCES_BD}")
message("INCLUDE_BD = ${INCLUDE_BD}")

add_library(lib_bd ${INCLUDE_BD} ${SOURCES_BD})
#SET_TARGET_PROPERTIES(lib_bd PROPERTIES LINKER_LANGUAGE CXX))


##end_bd

##Crawler
### directories variables ###

file(GLOB SOURCES_Cr "Crawler/Sources/*.cpp")
file(GLOB INCLUDE_Cr "Crawler/Headers/*.h")

### hunter ###


hunter_add_package(asio)

hunter_add_package(gumbo)

hunter_add_package(nlohmann_json)


find_package(asio CONFIG REQUIRED)
find_package(Beast CONFIG REQUIRED)
find_package(Boost CONFIG REQUIRED)
find_package(gumbo CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

### making executables, linking libraries ###

add_library(lib_cr ${INCLUDE_Cr} ${SOURCES_Cr})
target_link_libraries(lib_cr nlohmann_json::nlohmann_json gumbo::gumbo Beast::Beast asio::asio_headeronly)
##end_crawler

add_compile_options(-pthread)
find_package (Threads REQUIRED)
#find_package(Boost REQUIRED)


file(GLOB SOURCE "server/src/*.cpp")
file(GLOB INCLUDE "server/include/*.h")

include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
add_library(server_lib ${INCLUDE} ${SOURCE} )

add_executable(main.out server/main.cpp)
target_link_libraries(main.out server_lib Threads::Threads nlohmann_json::nlohmann_json)
target_link_libraries(main.out lib_bd)
target_link_libraries(main.out -I/usr/include/mysql -L/usr/lib/x86_64-linux-gnu -lgtest -lmysqlclient -lpthread)
target_link_libraries(main.out lib_cr)


# Async HTTP Client
#add_executable(client client.cpp)
#target_link_libraries(client Threads::Threads nlohmann_json::nlohmann_json ${Boost_LIBRARIES})
