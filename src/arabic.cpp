/* 
this program reads Arabic characters from the file arabic.txt, replaces non alphabetic characters with a space,
computes word frequencies, counts unique words, sorts word frequencies, exports results to a file, 
and displays "hapax legomena" (words that appear only once). 
*/



#include "arabic.h"

namespace alexa_arabic {

void setupLocale() { // sets up the global locale to support UTF-8 for handling Arabic characters.
    std::locale::global(std::locale("en_US.UTF-8")); // sets the global locale to "en_US.UTF-8", which supports Unicode for Arabic text.
    std::wcout.imbue(std::locale()); // imbues 'std::wcout' with the global locale for correct Arabic character display in the console.
}


bool isArabicAlphabet(wchar_t ch) { // checks if a character is within the Arabic Unicode block.
    return (ch >= L'\u0600' && ch <= L'\u06FF'); // returns true if the character is between Unicode points U+0600 and U+06FF, representing Arabic script.
}

std::vector<wchar_t> readBook(const std::string& fileName) { // reads the arabic characters from the file and returns them in a vector plus replaces non-Arabic ch with spaces.
    std::vector<wchar_t> result; // 'result": 'vector to store the Arabic chs and spaces
    std::wifstream file(fileName); // opens a wide-character file stream to read Unicode text from the file
    file.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>)); // imbues the file stream with a UTF-8 codec for correctly interpreting Arabic characters.
//imbue: a method that sets or applies a specific locale to an input or output stream (such as std::ifstream, std::ofstream, std::wifstream..
//Setting a locale with imbue allows you to specify an encoding (like UTF-8) to ensure characters are read and written correctly for ex for arabic right-->left


    if (file.is_open()) { //checks if file can open 
        wchar_t ch; //stores each character as wide char in 'ch' var
        while (file.get(ch)) { //reads each ch in the file 
            if (isArabicAlphabet(ch)) { //if the ch is an arabic letter 
                result.push_back(ch); //it affes it to the vector result 
            } else if (std::iswspace(ch) || ch == L'\u200C') { //checks if the character is a whitespace or if its a 'zero-width-non-joiner' (breaks the connection of the chs in the word)
                result.push_back(L' '); //adds a space to result 
            } else {
                result.push_back(L' ');  // any other character also gets replaced with a space
            }
        }
    } else {
        std::cerr << "Error: Could not open file " << fileName << std::endl;
    }

    return result;
}

    std::map<std::wstring, int> computeWordFrequency(const std::vector<wchar_t>& book) { // counts how often each word appears
        std::map<std::wstring, int> wordFrequency; // creates a map to store word counts, with words as keys and their frequencies as values
        std::wstringstream ss; // makes a string stream to treat 'book' as a continuous stream of text
        
        for (wchar_t ch : book) {
            ss << ch; // adds each character to 'ss' to form a text stream
        }
        
        std::wstring word; // declares a string to store each word as it's read
        while (ss >> word) { // extracts each word from 'ss' (separated by spaces)
            wordFrequency[word]++; // increases the count for this word in the map
        }

        return wordFrequency; 
    }

    int countUniqueWords(const std::vector<wchar_t>& book) { // counts the number of unique words
        std::set<std::wstring> uniqueWords; // creates a set to store unique words
        std::wstringstream ss; // makes a wide string stream to treat 'book' as text
        
        for (wchar_t ch : book) {
            ss << ch; // adds each character to 'ss'
        }
        
        std::wstring word; // declares a string to store each word as it's read
        while (ss >> word) { // extracts each word from 'ss'
            uniqueWords.insert(word); // adds each word to 'uniqueWords' (duplicates automatically ignored since 'string')
        }

        return uniqueWords.size(); //returns number of unique words
    }

    std::multimap<int, std::wstring> sortFrequencies(const std::map<std::wstring, int>& frequencies) { // sorts words by their frequency
        std::multimap<int, std::wstring> sortedFrequencies; // creates multimap to store frequency as key and words as values (allows multiple words with the same frequency)
        
        for (const auto& pair : frequencies) { // iterates over each (word, frequency) pair in 'frequencies'
            sortedFrequencies.insert({pair.second, pair.first}); // inserts each frequency-word pair into 'sortedFrequencies'
        }

        return sortedFrequencies; 
    }


    void exportFrequenciesToFile(const std::multimap<int, std::wstring>& sortedFreq, const std::string& outputFileName) { // puts sorted word frequencies to an output file
        std::wofstream outFile(outputFileName); // opens a wide-character output-filestream for writing
        outFile.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>)); // sets the stream to use UTF-8 encoding for the Arabic text
        
        if (!outFile.is_open()) { // checks if the output file opened successfully
            std::cerr << "Error: Could not open file " << outputFileName << std::endl; // prints an error if the file couldn't be opened
            return; 
        }

        int rank = 1; // initializes rank to track frequency ranking starting w 1
        for (auto it = sortedFreq.rbegin(); it != sortedFreq.rend(); ++it) { // iterates over 'sortedFreq' in reverse (high to low frequency)
            outFile << rank << L" " << it->first << L" " << it->second << L"\n"; // writes rank, frequency, and word to the output file
            ++rank; // increases the rank for the next entry
        }
    }

    void printHapaxLegomena(const std::multimap<int, std::wstring>& sortedFreq) { // prints words that appear only once
        int hapaxCount = 0; // counter for the number of hapax legomena
        std::wcout << L"\nHapax Legomena (words that appear only once):" << std::endl; 
        
        for (const auto& pair : sortedFreq) { // iterates over each frequency-word pair in 'sortedFreq'
            if (pair.first == 1) { // if the frequency is 1 (=hapax legomenon)
                ++hapaxCount; // increase the hapax count
                if (hapaxCount <= 10) { // limits output to the first 10 hapax legomena 
                    std::wcout << pair.second << std::endl; // prints the word 
                }
            }
        }

        std::wcout << L"\nTotal number of hapax legomena: " << hapaxCount << std::endl; // prints total count of hapax legomena
    }

} 