#include "../include/arabic.h"

int main() {
    alexa_arabic::setupLocale();

    std::string fileName = "arabic.txt"; 
    std::vector<wchar_t> content = alexa_arabic::readBook(fileName);
    std::map<std::wstring, int> wordFreq = alexa_arabic::computeWordFrequency(content);
    int uniqueWordCount = alexa_arabic::countUniqueWords(content);
    std::multimap<int, std::wstring> sortedFreq = alexa_arabic::sortFrequencies(wordFreq);

    // Display word frequencies and unique words
    std::wcout << L"\nNumber of unique words: " << uniqueWordCount << std::endl;
    std::wcout << L"\nSorted Word Frequencies (Descending):" << std::endl;
    for (auto it = sortedFreq.rbegin(); it != sortedFreq.rend(); ++it) {
        std::wcout << it->second << L": " << it->first << std::endl;
    }

    // Export sorted frequencies to file
    std::string outputFileName = "word_frequencies_arabic.txt";
    alexa_arabic::exportFrequenciesToFile(sortedFreq, outputFileName);
    std::cout << "\nExported frequencies to " << outputFileName << std::endl;

    // Print hapax legomena
    alexa_arabic::printHapaxLegomena(sortedFreq);

    return 0;
}
