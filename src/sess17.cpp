#include "../include/sess17.h"

namespace alexa {

    std::vector<char> readBook(std::string fileName) {
        std::vector<char> result;
        std::ifstream file(fileName);

        if (file.is_open()) {
            char ch;
            while (file.get(ch)) {
                if (std::isalpha(ch)) {
                    result.push_back(ch);
                } else {
                    result.push_back(' ');
                }
            }
        } else {
            std::cerr << "Error: Could not open file " << fileName << std::endl;
        }

        return result;
    }

    std::map<std::string, int> computeWordFrequency(const std::vector<char>& book) {
        std::map<std::string, int> wordFrequency;
        std::stringstream ss;
        
        for (char ch : book) {
            ss << ch;
        }
        
        std::string word;
        while (ss >> word) {
            wordFrequency[word]++;
        }

        return wordFrequency;
    }

    int countUniqueWords(const std::vector<char>& book) {
        std::set<std::string> uniqueWords;
        std::stringstream ss;

        for (char ch : book) {
            ss << ch;
        }
        
        std::string word;
        while (ss >> word) {
            uniqueWords.insert(word);
        }

        return uniqueWords.size();
    }

    std::multimap<int, std::string> sortFrequencies(const std::map<std::string, int>& frequencies) {
        std::multimap<int, std::string> sortedFrequencies;

        for (const auto& pair : frequencies) {
            sortedFrequencies.insert({pair.second, pair.first});
        }

        return sortedFrequencies;
    }

    void exportFrequenciesToFile(const std::multimap<int, std::string>& sortedFreq, const std::string& outputFileName) {
        std::ofstream outFile(outputFileName);

        if (!outFile.is_open()) {
            std::cerr << "Error: Could not open file " << outputFileName << std::endl;
            return;
        }

        int rank = 1; // Start rank at 1
        for (auto it = sortedFreq.rbegin(); it != sortedFreq.rend(); ++it) {
            outFile << rank << " " << it->first << " " << it->second << "\n";
            ++rank;
        }

        outFile.close();
    }

    void printHapaxLegomena(const std::multimap<int, std::string>& sortedFreq) {
        int hapaxCount = 0;
        std::cout << "\nHapax Legomena (words that appear only once):" << std::endl;

        for (const auto& pair : sortedFreq) {
            if (pair.first == 1) {
                ++hapaxCount;
                if (hapaxCount <= 10) { // Print only the first 10 hapax legomena for demonstration
                    std::cout << pair.second << std::endl;
                }
            }
        }

        std::cout << "\nTotal number of hapax legomena: " << hapaxCount << std::endl;
    }
}

