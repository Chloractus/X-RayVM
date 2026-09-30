cmake_minimum_required(VERSION 3.10)
project(XRayVM)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(XRayVM
    src/core/main.cpp
    src/core/VM.cpp
)

target_compile_options(XRayVM PRIVATE -Wall -Wextra)
