cmake_minimum_required(VERSION 3.10)
project(JenkinsDemo)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(HelloWorld Code/Code.cpp)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/Code)

# Add Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add the test executable
add_executable(unit_test CRC_UT/UT.cpp)
target_link_libraries(unit_test ${GTEST_LIBRARIES} pthread)

# Add HelloWorld library to unit_test
target_link_libraries(unit_test HelloWorld)
