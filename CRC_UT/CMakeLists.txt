cmake_minimum_required(VERSION 3.5)
project(crc_8 VERSION 2.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

SET(CMAKE_CXX_FLAGS "-O0")
SET(CMAKE_C_FLAGS "-O0")
SET(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage ")
SET(GCC_COVERAGE_LINK_FLAGS "-lgcov")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

# Include Header Files
include_directories(inc)

# Include Dependent Libraries
# find_package(GTest REQUIRED)
# include_directories(${GTEST_INCLUDE_DIRS})
# enable_testing()
add_subdirectory(googletest-main)

# Main Post Processing Code
set(MAIN_SOURCE
    src/Code.cpp
)


#INTERGARTION_TEST
#set(IT_SRC  ${MAIN_SOURCE}
#    test/IT/IT.cpp
#)

#UNIT_TEST
set(UT_SRC 
    ${MAIN_SOURCE}
    test/UT/UT.cpp  
   )

# Gtest - IT
#add_executable(integration_test ${IT_SRC})
#target_link_libraries(integration_test  GTest::gtest_main)


# Gtest - UT
add_executable(unit_test ${UT_SRC})
target_link_libraries(unit_test  GTest::gtest_main GTest::gmock_main) 
