cmake_minimum_required(VERSION 3.21)

project(
    Engine 
    VERSION 1.0
    DESCRIPTION "A Search Engine"
    LANGUAGES CXX
)


set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# 暂时使用硬编码
set(LEVELDB_INCLUDE_DIRS /opt/homebrew/Cellar/leveldb/1.23_1/include)
set(LEVELDB_LIBRARIES /opt/homebrew/Cellar/leveldb/1.23_1/lib)

file(
    GLOB_RECURSE 
    SOURCES
    # "main.cpp"
    "src/*.cpp"
)

file(
    GLOB_RECURSE
    CPPJIEBA_SOURCES
    "cppjieba/include/*.hpp"
)

file(
    GLOB_RECURSE
    INCLUDES
    "include/*.h"
)


find_package(fmt REQUIRED)

include_directories(cppjieba/include)
# link_directories("cpp")

add_executable(${PROJECT_NAME} ${SOURCES} ${INCLUDES} ${CPPJIEBA_SOURCES})

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    ${LEVELDB_LIBRARIES}/libleveldb.dylib
    fmt::fmt
)

target_include_directories(
    ${PROJECT_NAME} 
    PRIVATE 
    ${CMAKE_SOURCE_DIR}/include 
    ${CMAKE_SOURCE_DIR}/cppjieba/include
    ${CMAKE_SOURCE_DIR}/cppjieba/deps/limonp/include
    ${LEVELDB_INCLUDE_DIRS}
)

target_compile_options(${PROJECT_NAME} PRIVATE
    -O0
    -Wall       # 打开所有警告
    # -Wextra      # 打开额外的警告
    -Werror     # 将警告视为错误
    -pedantic   # 启用严格的 C++ 标准
)
