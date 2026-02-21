cmake_minimum_required(VERSION 3.10)
project(deskewk VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
  boost
  GIT_REPOSITORY https://github.com/boostorg/boost.git
  GIT_TAG boost-1.84.0
)
FetchContent_MakeAvailable(boost)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

add_executable(deskewk
  ${SRC_DIR}/main.cpp
  ${SRC_DIR}/io.cpp
  ${SRC_DIR}/grayscale.cpp
  ${SRC_DIR}/cc.cpp
  ${SRC_DIR}/projection.cpp
  ${SRC_DIR}/threshold.cpp
)

target_include_directories(deskewk PRIVATE ${SRC_DIR} ${CMAKE_SOURCE_DIR}/stb ${boost_SOURCE_DIR})

if(NOT MSVC)
  target_compile_options(deskewk PRIVATE -Wall -Wextra -pedantic)
endif()

target_link_libraries(deskewk PRIVATE m)

option(BUILD_TESTS "Build tests" OFF)
if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

install(TARGETS deskewk RUNTIME DESTINATION bin)
