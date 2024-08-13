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

#include "gtest/gtest.h"
#include "../../src/Crc_32.c"

/*****************************************************************************
* Function Name: Crc_8_TC_01
* Description: calculate an 8-bit cyclic redundancy check (CRC) value with     first call to calculate the CRC is TRUE
* Parameters: 
* Called functions: 
* Global Data: Also describe any global data manipulated through pointers.
* Return Value: 
* Exceptions: 
*****************************************************************************/
TEST(Crc32P4Calculate, Crc32P4Calculate_IT_TC_01)
{
    // Define a test input
    uint8 testInput = 5;

    // Call the function with the test input
    uint32 result = Crc32P4Calculate(testInput);

    // Define the expected output. This would typically be a known output for the given input.
    // For this example, let's assume the expected output is 12345.
    uint32 expectedOutput = 0xCF46E179;

    // Check the function output against the expected output
    ASSERT_EQ(result, expectedOutput);
}

TEST(CrcCalculate, CalculateCRC32P4)
{
    // Define a sample input
    uint8 input[] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
    uint32 length = sizeof(input);
    uint32 start_value = 0xFFFFFFFF;
    uint32 expected_output = 0x48A072F3;

    // Call the Crc_CalculateCRC32P4 function with the sample input
    uint32 output = Crc_CalculateCRC32P4(input, length, start_value, TRUE);

    // Check the output against the expected value
    ASSERT_EQ(output, expected_output);
    
}

TEST(CrcCalculate, CalculateCRC32P4_IsFirstCall)
{
    // Define a sample input
    uint8 input[] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
    uint32 length = sizeof(input);
    uint32 start_value = 0xFFFFFFFF;
    uint32 expected_output1 = 0x48A072F3;
    uint32 expected_output2 = 0x8896F960;

    // Test initializing the CRC value when Crc_IsFirstCall is true
    uint32 output = Crc_CalculateCRC32P4(input, length, start_value, TRUE);
    ASSERT_EQ(output, expected_output1);

    // Test not modifying the CRC value when Crc_IsFirstCall is false
    output = Crc_CalculateCRC32P4(input, length, start_value, FALSE);
    ASSERT_EQ(output, expected_output2);
}

TEST(CrcCalculate, CalculateCRC32P4_DifferentStartValue) {
    uint8 input[] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
    uint32 length = sizeof(input);
    uint32 start_value = 0xDEADBEEF;
    uint32 expected_output = 0x48A072F3;

    uint32 output = Crc_CalculateCRC32P4(input, length, start_value, TRUE);

    ASSERT_EQ(output, expected_output);
}

TEST(CrcCalculate, CalculateCRC32P4_ZeroLength) {
    uint8 input[] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
    uint32 length = 0;
    uint32 start_value = 0xFFFFFFFF;
    uint32 expected_output = 0x0000;

    uint32 output = Crc_CalculateCRC32P4(input, length, start_value, TRUE);

    ASSERT_EQ(output, expected_output);
}

int main(int argc, char **argv) 
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
