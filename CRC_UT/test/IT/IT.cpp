#include <gtest/gtest.h>
#include <sstream>
#include "Code.h"

// Redirects std::cout to a stringstream and returns the output as a string
std::string getOutputFromFunction(void (*func)()) {
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    func();
    std::cout.rdbuf(old);
    return buffer.str();
}

TEST(IntegrationTest, PrintHelloWorld) {
    std::string output = getOutputFromFunction(printHelloWorld);
    EXPECT_EQ(output, "Hello, World!\n");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
