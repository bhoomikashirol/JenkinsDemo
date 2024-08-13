cmake_minimum_required(VERSION 3.10)

# Set the project name
project(JenkinsDemo)

# Add the executable for the main code
add_executable(HelloWorld Code.cpp)

# Add the executable for the tests
add_executable(runTests ~/Downloads/Crc_UT/test/UT/UT.cpp)

# Link the Google Test library
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
