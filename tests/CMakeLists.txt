cmake_minimum_required(VERSION 3.14)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

add_executable(deskewk_tests test_deskew.cpp)
target_link_libraries(deskewk_tests PRIVATE deskewk_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(deskewk_tests)
