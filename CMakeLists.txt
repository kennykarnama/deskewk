cmake_minimum_required(VERSION 3.14)
project(deskewk VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Library
add_library(deskewk_lib
    src/deskew.cpp
)
target_include_directories(deskewk_lib PUBLIC include)

# Executable
add_executable(deskewk src/main.cpp)
target_link_libraries(deskewk PRIVATE deskewk_lib)

enable_testing()
add_subdirectory(tests)
