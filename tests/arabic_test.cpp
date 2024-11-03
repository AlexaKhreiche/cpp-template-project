#include <gtest/gtest.h>
#include "arabic.h"  

namespace alexa_arabic {

// Test for computing word frequency with basic ASCII input
TEST(WordFrequencyTest, SimpleFrequencyCount) {
    // Prepare a simple ASCII vector representing text
    std::vector<wchar_t> sampleText = {
        L'H', L'e', L'l', L'l', L'o', L' ', 
        L'W', L'o', L'r', L'l', L'd', L' ', 
        L'H', L'e', L'l', L'l', L'o'
    };

    // Expected frequency result
    std::map<std::wstring, int> expectedFrequency = {
        {L"Hello", 2},
        {L"World", 1}
    };

    // Call the function to get the actual frequency result
    std::map<std::wstring, int> actualFrequency = computeWordFrequency(sampleText);

    // Compare expected and actual results
    EXPECT_EQ(actualFrequency, expectedFrequency);
}

} 

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
