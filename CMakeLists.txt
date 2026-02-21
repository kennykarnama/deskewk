cmake_minimum_required(VERSION 3.10)
project(deskewk VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)

set(FETCHCONTENT_QUIET OFF)
set(CMAKE_MESSAGE_LOG_LEVEL STATUS)
set(CMAKE_VERBOSE_MAKEFILE ON)

include(FetchContent)
FetchContent_Declare(
  boost
  URL https://archives.boost.io/release/1.90.0/source/boost_1_90_0.tar.gz
  URL_HASH SHA256=5e93d582aff26868d581a52ae78c7d8edf3f3064742c6e77901a1f18a437eea9
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
  ${SRC_DIR}/geotransform.cpp
  ${SRC_DIR}/deskew_v1.cpp
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
