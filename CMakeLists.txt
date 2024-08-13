cmake_minimum_required(VERSION 3.10)

# Set the project name
project(HelloWorld)

# Add the executable for the main code
add_executable(HelloWorld Code/Code.cpp)

# Include the header files
include_directories(Code)

# Add the executable for the tests with the correct path
add_executable(HelloWorldTest Test/CRC_UT/test/UT/UT.cpp)

# Link the Google Test library
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
target_link_libraries(HelloWorldTest ${GTEST_LIBRARIES} pthread)

# Link the main code with the test executable
target_link_libraries(HelloWorldTest HelloWorld)
