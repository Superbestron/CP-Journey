cmake_minimum_required(VERSION 3.13)  # CMake version check
project(CP_Journey)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 23)            # Enable c++23 Standard

# Add debugging flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -Wshadow -D_GLIBCXX_DEBUG -D_GLIBCXX_ASSERTIONS")
find_package(OpenSSL REQUIRED)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(CP_Journey CS3103/A2L1.cpp)

target_link_libraries(CP_Journey OpenSSL::SSL OpenSSL::Crypto)
