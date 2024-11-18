cmake_minimum_required(VERSION 3.10)

project(asm)

add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_executable(asm asm/asm.cpp asm/main.cpp utils/stack/stack.cpp)
