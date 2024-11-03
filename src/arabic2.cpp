/* session 19 hw*/

#include "arabic2.h" 

namespace arabic2 { 

void setupLocale() {
    std::locale::global(std::locale("en_US.UTF-8")); 
    std::wcout.imbue(std::locale()); // imbues 'std::wcout' with the global locale so it can display Arabic text correctly
}

bool isArabicAlphabet(wchar_t ch) { 
    return (ch >= L'\u0600' && ch <= L'\u06FF'); // checks if the character is in the Arabic Unicode range
}

std::vector<wchar_t> readBook(const std::string& fileName) { // reads Arabic characters from the file, keeping only Arabic letters and whitespace
    std::vector<wchar_t> result; // creates a vector to store characters we want
    std::wifstream file(fileName); // opens a wide-character file stream to read Unicode (Arabic) text from the specified file
    file.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>)); // sets the file to use UTF-8 encoding for Arabic text

    if (file.is_open()) {
        wchar_t ch;
        while (file.get(ch)) {
            if (isArabicAlphabet(ch) || std::iswspace(ch)) { // only keeps Arabic letters and whitespace, ignores other characters
                result.push_back(ch); // adds Arabic or whitespace characters to 'result'
            }
            
        }
    } else {
        std::cerr << "Error: Could not open file " << fileName << std::endl; 
    }

    return result; 
}

void zipfsLawExercise(const std::string& fileName) { // new function for Zipf's Law analysis based on word frequency
    std::vector<wchar_t> content = readBook(fileName); // reads the Arabic content of the file into a vector
    
    // Step 1: Extract words
    std::vector<std::wstring> words; // creates a vector to store words extracted from the content
    std::wstring currentWord; // stores the current word being built from consecutive Arabic characters
    
    for (wchar_t ch : content) {
        if (std::iswspace(ch) && !currentWord.empty()) { // if a whitespace is found and we have a word we add it to 'words'
            words.push_back(currentWord); // adds the complete word to 'words'
            currentWord.clear(); // clears currentWord to start building the next word
        } else if (isArabicAlphabet(ch)) { // if the character is Arabic:
            currentWord += ch; // then it adds the character to currentWord
        }
    }
    if (!currentWord.empty()) { // if there’s a leftover word after the loop
        words.push_back(currentWord); // adds it to 'words'
    }

    // Step 2: Compute frequencies
    std::vector<std::pair<std::wstring, int> > frequencies; // stores pairs of words and their counts
    
    for (const auto& word : words) { // iterates over each word
        auto it = std::find_if(frequencies.begin(), frequencies.end(), 
                               [&word](const std::pair<std::wstring, int>& p) { return p.first == word; }); // searches for the word in frequencies
        if (it != frequencies.end()) {
            it->second++; // if found count increments 
        } else {
            frequencies.emplace_back(word, 1); // if not found, adds it with a count of 1
        }
    }
    // unlike the previous code which used a std::map, this code manually tracks frequencies with a vector of pairs

    // Step 3: Sort frequencies in descending order
    std::sort(frequencies.begin(), frequencies.end(), 
              [](const std::pair<std::wstring, int>& a, const std::pair<std::wstring, int>& b) {
                  return a.second > b.second; // sorts by frequency in descending order
              });
    // unlike previous code where we used std::multimap for sorting- here, std::sort is used on a vector of pairs

    // Step 4: Display results
    std::wcout << L"Word Frequencies according to Zipf's Law:" << std::endl; 
    for (const auto& pair : frequencies) {
        std::wcout << pair.first << L": " << pair.second << std::endl; // prints each word and its frequency
    }
    // unlike prev code, instead of exporting to a file, this code just displays word frequencies 
}

} 
