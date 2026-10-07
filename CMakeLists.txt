cmake_minimum_required(VERSION 3.20)

project(cpp_starter
    VERSION 0.1.0
    DESCRIPTION "A minimal, dependency-free C++23 starter project"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 生成 compile_commands.json，供 clangd / VS Code IntelliSense 使用
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 单配置生成器（Ninja / Makefiles）下没指定就用 Debug
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# ---------------------------------------------------------------- 编译选项
# /utf-8 是必须的：源码里有中文字面量，不加 MSVC 会按本地代码页解释而乱码
if(MSVC)
    add_compile_options(/W4 /utf-8 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# ---------------------------------------------------------------- 库
add_library(cpp_starter STATIC
    src/greet.cpp)

target_include_directories(cpp_starter PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

# ---------------------------------------------------------------- 可执行文件
add_executable(cpp_starter_app
    src/main.cpp)

target_link_libraries(cpp_starter_app PRIVATE cpp_starter)

# ---------------------------------------------------------------- 测试
enable_testing()

add_executable(cpp_starter_tests
    tests/test_greet.cpp)

target_link_libraries(cpp_starter_tests PRIVATE cpp_starter)

add_test(NAME greet_tests COMMAND cpp_starter_tests)
