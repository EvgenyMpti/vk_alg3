cmake_minimum_required(VERSION 3.10)
project(VK_alg3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

include_directories(include)

add_executable(VK_alg3 prefix.cpp test.cpp)
target_link_libraries(VK_alg3 ${GTEST_LIBRARIES})

