cmake_minimum_required(VERSION 3.20)

project(server_lib_s)

set(SOURCE_LIB Server.cpp Connection.cpp Handler.cpp Crawler.cpp interface_BD.cpp )

add_library(server_lib STATIC ${SOURCE_LIB})