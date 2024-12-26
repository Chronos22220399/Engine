cmake_minimum_required(VERSION 3.21)

project(
    Engine 
    VERSION 1.0
    DESCRIPTION "A Search Engine"
    LANGUAGES CXX
)


set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 第三方库目录
# set(THIRD_PARTY_DIR ${CMAKE_SOURCE_DIR}/thirdparty)
# 暂时使用硬编码
# set(LEVELDB_INCLUDE_DIRS /opt/homebrew/Cellar/leveldb/1.23_2/include)
# set(LEVELDB_LIBRARIES /opt/homebrew/Cellar/leveldb/1.23_2/lib)

# archlinux 上
find_package(leveldb REQUIRED)

file(
    GLOB_RECURSE 
    SOURCES
    # "main.cpp"
    "src/*.cpp"
    "demo/*.hpp"
)

file(
    GLOB_RECURSE
    CPPJIEBA_SOURCES
    "thirdparty/cppjieba/include/*.hpp"
)

file(
    GLOB_RECURSE
    INCLUDES
    "include/*.h"
)


find_package(fmt REQUIRED)

include_directories(thirdparty/cppjieba/include)
# link_directories("cpp")

add_executable(${PROJECT_NAME} ${SOURCES} ${INCLUDES} ${CPPJIEBA_SOURCES})

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    # ${LEVELDB_LIBRARIES}/libleveldb.dylib
    leveldb
    fmt::fmt
)

target_include_directories(
    ${PROJECT_NAME} 
    PRIVATE 
    ${CMAKE_SOURCE_DIR}/include 
    ${CMAKE_SOURCE_DIR}/thirdparty/cppjieba/include
    ${CMAKE_SOURCE_DIR}/thirdparty/cppjieba/deps/limonp/include
    ${CMAKE_SOURCE_DIR}/demo
    # ${LEVELDB_INCLUDE_DIRS}
    leveldb
)

target_compile_options(${PROJECT_NAME} PRIVATE
    -O0
    -Wall       # 打开所有警告
    # -Wextra      # 打开额外的警告
    -Werror     # 将警告视为错误
    -pedantic   # 启用严格的 C++ 标准
)
