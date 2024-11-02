#include "arabic2.h"

namespace arabic2 {

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
            if (isArabicAlphabet(ch) || std::iswspace(ch)) {
                result.push_back(ch);
            }
        }
    } else {
        std::cerr << "Error: Could not open file " << fileName << std::endl;
    }

    return result;
}

void zipfsLawExercise(const std::string& fileName) {
    std::vector<wchar_t> content = readBook(fileName);
    
    // Step 1: Extract words
    std::vector<std::wstring> words;
    std::wstring currentWord;
    
    for (wchar_t ch : content) {
        if (std::iswspace(ch) && !currentWord.empty()) {
            words.push_back(currentWord);
            currentWord.clear();
        } else if (isArabicAlphabet(ch)) {
            currentWord += ch;
        }
    }
    if (!currentWord.empty()) {
        words.push_back(currentWord);
    }

    // Step 2: Compute frequencies
    std::vector<std::pair<std::wstring, int> > frequencies;

    for (const auto& word : words) {
        auto it = std::find_if(frequencies.begin(), frequencies.end(), 
                               [&word](const std::pair<std::wstring, int>& p) { return p.first == word; });
        if (it != frequencies.end()) {
            it->second++;
        } else {
            frequencies.emplace_back(word, 1);
        }
    }

    // Step 3: Sort frequencies in descending order
    std::sort(frequencies.begin(), frequencies.end(), 
              [](const std::pair<std::wstring, int>& a, const std::pair<std::wstring, int>& b) {
                  return a.second > b.second;
              });

    // Step 4: Display results
    std::wcout << L"Word Frequencies according to Zipf's Law:" << std::endl;
    for (const auto& pair : frequencies) {
        std::wcout << pair.first << L": " << pair.second << std::endl;
    }
}

} // namespace arabic


