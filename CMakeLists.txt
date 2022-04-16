cmake_minimum_required(VERSION 3.22)

project(Thrift_shop)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Обработка ворнингов
add_compile_options(-g -O0 -Wextra -Wall -Wextra -Wpedantic -lgcov --coverage)
add_link_options( -O0 -lgcov --coverage)

# Поиск файлов в директории server/src
include_directories(server/src)

add_subdirectory(server/src)

# Пакет без которого все крашится
find_package (Threads REQUIRED)
add_compile_options(-pthread)

find_package(Boost CONFIG REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

add_executable(main.out server/main.cpp)
target_link_libraries(main.out ${Boost_LIBRARIES})


