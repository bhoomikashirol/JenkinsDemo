/****************************************************************************
* Company:
* File Name:
* Author:
* Version:
* Date:
* Operating Environment: 
* Compiler with Version Number: 
* Description: Unit Test file for verifying Crc_8 module
* Requirement ID:
* LLD ID :
* Revisers Name:
* Date:
* Customer Bug No./ CMF No.:
* Brief description of the fix/enhancement:
* Created by Tata Elxsi Ltd., ADAS
*Copyright 2023 Tata Elxsi Ltd.
*All rights reserved. 
This code contains information that is proprietary to Tata Elxsi Ltd. No part of this code may be reproduced or used in whole or part in any form or by any means - graphic, electronic or mechanical without the written permission of Tata Elxsi Ltd. 

****************************************************************************/

/*****************************************************************************
* Function Name: Crc_8_TC_01
* Description: calculate an 8-bit cyclic redundancy check (CRC) value with     first call to calculate the CRC is TRUE
* Parameters: 
* Called functions: 
* Global Data: Also describe any global data manipulated through pointers.
* Return Value: 
* Exceptions: 
*****************************************************************************/
#include "gtest/gtest.h"
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

