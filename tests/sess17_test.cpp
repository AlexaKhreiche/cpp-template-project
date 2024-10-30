#include <gtest/gtest.h>
#include "sess17.h"

namespace alexa {

TEST(WordFrequencyTest, BasicFrequencyCount) {
    // Prepare a sample vector representing text with some repeated words
    std::vector<char> sampleText = {
        'H', 'e', 'l', 'l', 'o', ' ', 
        'W', 'o', 'r', 'l', 'd', ' ', 
        'H', 'e', 'l', 'l', 'o', ' ',
        'A', 'L', 'E', 'X', 'A'
    };

    // Expected frequency result
    std::map<std::string, int> expectedFrequency = {
        {"Hello", 2},
        {"World", 1},
        {"ALEXA", 1}
    };

    // Call the function to get the actual frequency result
    std::map<std::string, int> actualFrequency = alexa::computeWordFrequency(sampleText);

    // Compare expected and actual results
    EXPECT_EQ(actualFrequency, expectedFrequency);
}

} // namespace alexa

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
