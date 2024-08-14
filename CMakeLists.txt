cmake_minimum_required(VERSION 3.10)
project(JenkinsDemo)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the source files
add_executable(unit_test
    ${CMAKE_SOURCE_DIR}/Code/Code.cpp
    ${CMAKE_SOURCE_DIR}/CRC_UT/test/UT.cpp
)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/Code)
include_directories(${CMAKE_SOURCE_DIR}/CRC_UT/src)

# Link GTest library
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
target_link_libraries(unit_test ${GTEST_LIBRARIES} pthread)

# Set the output directory for the build files
set_target_properties(unit_test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build
)
