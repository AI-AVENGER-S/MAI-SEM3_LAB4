cmake_minimum_required(VERSION 3.14)
project(lab4 CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(lab4
    main.cpp
)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

add_executable(tests
    tests/tests01.cpp
)

target_link_libraries(tests
    PRIVATE
        GTest::gtest_main
        Threads::Threads
)

enable_testing()
include(GoogleTest)
gtest_discover_tests(tests)
