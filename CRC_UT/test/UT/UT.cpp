// UT.cpp
#include "gtest/gtest.h"
#include "Code.h"
 
TEST(HelloWorldTest, OutputCheck) {
    testing::internal::CaptureStdout();
    printHelloWorld();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Hello, World!\n");
}
 
// Main function to run the tests
int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
