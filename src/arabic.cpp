#include "arabic.h"

namespace alexa_arabic {

void setupLocale() {
    std::locale::global(std::locale("en_US.UTF-8"));
    std::wcout.imbue(std::locale());
}

bool isArabicAlphabet(wchar_t ch) {
    return (ch >= L'\u0600' && ch <= L'\u06FF'); // Arabic Unicode block
}

std::vector<wchar_t> readBook(const std::string& fileName) {
    std::vector<wchar_t> result;
    std::wifstream file(fileName);
    file.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));

    if (file.is_open()) {
        wchar_t ch;
        while (file.get(ch)) {
            if (isArabicAlphabet(ch)) {
                result.push_back(ch);
            } else if (std::iswspace(ch) || ch == L'\u200C') {
                result.push_back(L' ');
            } else {
                result.push_back(L' ');
            }
        }
    } else {
        std::cerr << "Error: Could not open file " << fileName << std::endl;
    }

    return result;
}

std::map<std::wstring, int> computeWordFrequency(const std::vector<wchar_t>& book) {
    std::map<std::wstring, int> wordFrequency;
    std::wstringstream ss;

    for (wchar_t ch : book) {
        ss << ch;
    }

    std::wstring word;
    while (ss >> word) {
        wordFrequency[word]++;
    }

    return wordFrequency;
}

int countUniqueWords(const std::vector<wchar_t>& book) {
    std::set<std::wstring> uniqueWords;
    std::wstringstream ss;

    for (wchar_t ch : book) {
        ss << ch;
    }

    std::wstring word;
    while (ss >> word) {
        uniqueWords.insert(word);
    }

    return uniqueWords.size();
}

std::multimap<int, std::wstring> sortFrequencies(const std::map<std::wstring, int>& frequencies) {
    std::multimap<int, std::wstring> sortedFrequencies;

    for (const auto& pair : frequencies) {
        sortedFrequencies.insert({pair.second, pair.first});
    }

    return sortedFrequencies;
}

void exportFrequenciesToFile(const std::multimap<int, std::wstring>& sortedFreq, const std::string& outputFileName) {
    std::wofstream outFile(outputFileName);
    outFile.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));

    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file " << outputFileName << std::endl;
        return;
    }

    int rank = 1;
    for (auto it = sortedFreq.rbegin(); it != sortedFreq.rend(); ++it) {
        outFile << rank << L" " << it->first << L" " << it->second << L"\n";
        ++rank;
    }

    outFile.close();
}

void printHapaxLegomena(const std::multimap<int, std::wstring>& sortedFreq) {
    int hapaxCount = 0;
    std::wcout << L"\nHapax Legomena (words that appear only once):" << std::endl;

    for (const auto& pair : sortedFreq) {
        if (pair.first == 1) {
            ++hapaxCount;
            if (hapaxCount <= 10) { // Print only the first 10 hapax legomena for demonstration
                std::wcout << pair.second << std::endl;
            }
        }
    }

    std::wcout << L"\nTotal number of hapax legomena: " << hapaxCount << std::endl;
}

} // namespace arabic
