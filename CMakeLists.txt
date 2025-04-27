cmake_minimum_required(VERSION 3.20)
project(ArrayBasedLinkedList)

set(CMAKE_CXX_STANDARD 17)           # Use C++17
include_directories(include)         # Headers in 'include/'

add_executable(LinkedListTester      # Build executable
        src/main.cpp                     # Source files
)

# Optional: Enable stricter compiler warnings
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(LinkedListTester PRIVATE -Wall -Wextra -pedantic)
endif()