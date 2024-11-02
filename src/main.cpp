#include "../include/sess17.h"

int main() {
    std::string fileName = "sess17.txt"; // Replace with actual file name
    std::vector<char> content = alexa::readBook(fileName);
    std::map<std::string, int> wordFreq = alexa::computeWordFrequency(content);
    int uniqueWordCount = alexa::countUniqueWords(content);
    std::multimap<int, std::string> sortedFreq = alexa::sortFrequencies(wordFreq);

    // Display word frequencies
    std::cout << "Word Frequencies:" << std::endl;
    for (const auto& pair : wordFreq) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    // Display unique word count
    std::cout << "\nNumber of unique words: " << uniqueWordCount << std::endl;

    // Display sorted frequencies
    std::cout << "\nSorted Word Frequencies (Descending):" << std::endl;
    for (auto it = sortedFreq.rbegin(); it != sortedFreq.rend(); ++it) {
        std::cout << it->second << ": " << it->first << std::endl;
    }

    // Export sorted frequencies to file
    std::string outputFileName = "f2.txt";
    alexa::exportFrequenciesToFile(sortedFreq, outputFileName);
    std::cout << "\nExported frequencies to " << outputFileName << std::endl;

    // Print hapax legomena
    alexa::printHapaxLegomena(sortedFreq);

    return 0;
}
