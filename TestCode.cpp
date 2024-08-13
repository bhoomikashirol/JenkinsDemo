#include <gtest/gtest.h>
#include <string>

std::string getHelloWorld();

TEST(HelloWorldTest, OutputCheck) {
    EXPECT_EQ(getHelloWorld(), "Hello World");
}
