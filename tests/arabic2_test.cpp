#include <gtest/gtest.h>
#include "arabic2.h"  // Include the header file for the functions to be tested

namespace arabic2 {

// Test for checking if a character is Arabic
TEST(ArabicTest, IsArabicAlphabet) {
    EXPECT_TRUE(isArabicAlphabet(L'ا'));  // Arabic character
    EXPECT_TRUE(isArabicAlphabet(L'ب'));  // Arabic character
    EXPECT_FALSE(isArabicAlphabet(L'A')); // Non-Arabic character
    EXPECT_FALSE(isArabicAlphabet(L'1')); // Non-Arabic character
}

} 

// Main function for running all tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
