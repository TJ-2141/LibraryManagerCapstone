cmake_minimum_required(VERSION 3.16)
project(LibraryManagerCapstone VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)
enable_testing()

add_library(library_core
    src/Book.cpp
    src/Member.cpp
    src/Loan.cpp
    src/Algorithms.cpp
    src/Storage.cpp
    src/Library.cpp
)

target_include_directories(library_core PUBLIC include)

if (MSVC)
    target_compile_options(library_core PRIVATE /W4 /permissive-)
else()
    target_compile_options(library_core PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_executable(library_manager src/main.cpp)
target_link_libraries(library_manager PRIVATE library_core)

add_executable(library_tests tests/test_library.cpp)
target_link_libraries(library_tests PRIVATE library_core)

add_test(NAME library_unit_tests COMMAND library_tests)
