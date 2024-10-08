cmake_minimum_required(VERSION 3.5)
project(crc_8 VERSION 2.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

SET(CMAKE_CXX_FLAGS "-O0")
SET(CMAKE_C_FLAGS "-O0")
SET(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
SET(GCC_COVERAGE_LINK_FLAGS "-lgcov")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

# Include Header Files
include_directories(${CMAKE_SOURCE_DIR}/inc)

# Include Dependent Libraries
add_subdirectory(${CMAKE_SOURCE_DIR}/Test/CRC_UT/googletest-main)

# Main Post Processing Code
set(MAIN_SRC ${CMAKE_SOURCE_DIR}/Test/CRC_UT/src/Code.cpp)

# UNIT_TEST
set(UT_SRC ${CMAKE_SOURCE_DIR}/Test/CRC_UT/test/UT/UT.cpp)

# INTEGRATION_TEST
set(IT_SRC ${CMAKE_SOURCE_DIR}/Test/CRC_UT/test/IT/IT.cpp)

# Gtest - UT
add_executable(unit_test ${UT_SRC} ${MAIN_SRC})
target_link_libraries(unit_test GTest::gtest_main GTest::gmock_main)

# Gtest - IT
add_executable(integration_test ${IT_SRC} ${MAIN_SRC})
target_link_libraries(integration_test GTest::gtest_main GTest::gmock_main)
