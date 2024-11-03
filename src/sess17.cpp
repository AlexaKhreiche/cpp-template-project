#include "../include/sess17.h"

namespace alexa {

    std::vector<char> readBook(std::string fileName) {  //takes a filename as input, opens the file and reads its content character by character.
        std::vector<char> result; //creates the 'result' vector 
        std::ifstream file(fileName); //input file stream used to read from a file 

        if (file.is_open()) { //check if we can open the file 
            char ch;
            while (file.get(ch)) { //goes through the characters of the files 
                if (std::isalpha(ch)) { //checks if the character is alphabetic 
                    result.push_back(ch); //if it is it puts it in the result vector 
                } else {
                    result.push_back(' '); //or else it replaces the character with a space 
                }
            }
        } else {
            std::cerr << "error! file not openable!" << fileName << std::endl; //outputs an error if the file couldnt be opened
        }

        return result;
    }

    std::map<std::string, int> computeWordFrequency(const std::vector<char>& book) { //compute wrod frequency function - std::map is used because it automatically organizes the words in alphabetical order (by key) and allows u to search, insert..
        std::map<std::string, int> wordFrequency; //creates wrodfrequency map to store the word counts where keys are words and values are frequencies.

        std::stringstream ss; //used to treat the 'book' vector as a text stream
        
        for (char ch : book) {
            ss << ch; //Appends each character from book into ss
        }
        
        std::string word; // declares a string 'word' to hold each extracted word
        while (ss >> word) { // extracts each word from 'ss'
            wordFrequency[word]++; // increments the frequency count of 'word' in the map
        }

        return wordFrequency;
    }

    int countUniqueWords(const std::vector<char>& book) { //function to count number of unique words 
        std::set<std::string> uniqueWords; // creates a set 'uniqueWords' to store unique words only
        std::stringstream ss; // creates a string stream 'ss' to build a text stream from 'book'.

        for (char ch : book) {
            ss << ch;  //appends each character in book to 'ss'.
        }
        
        std::string word; //declares string var 'word' to hold each extracted word
        while (ss >> word) {
            uniqueWords.insert(word); //inserts each word from ss into the set 'uniquewords' 
        }

        return uniqueWords.size(); //count of unique words 
    }

    std::multimap<int, std::string> sortFrequencies(const std::map<std::string, int>& frequencies) { // function to sort word frequencies in ascending order
        std::multimap<int, std::string> sortedFrequencies; //creates a multimap 'sortedFrequencies' with frequencies as keys and words as values

        for (const auto& pair : frequencies) { // iterates over each (word, frequency) pair in 'frequencies'
            sortedFrequencies.insert({pair.second, pair.first}); //inserts each frequency-word pair into 'sortedFrequencies'
        }

        return sortedFrequencies;
    }

    void exportFrequenciesToFile(const std::multimap<int, std::string>& sortedFreq, const std::string& outputFileName) {  // function to export sorted frequencies to a specified output file.
        std::ofstream outFile(outputFileName); // opens an output file stream for writing to 'outputFileName'

        if (!outFile.is_open()) {  // checks if the output file was successfully opened.
            std::cerr << "Error! Could not open file " << outputFileName << std::endl;
            return;
        }

        int rank = 1; // initializes the rank variable to track the frequency ranking, starting from 1.
        for (auto it = sortedFreq.rbegin(); it != sortedFreq.rend(); ++it) { // iterates over 'sortedFreq' in reverse order (high to low frequency).
            outFile << rank << " " << it->first << " " << it->second << "\n";  // writes the rank, frequency, and word to 'outFile'.
            ++rank; // increments the rank for the next entry
        }
    } 

    void printHapaxLegomena(const std::multimap<int, std::string>& sortedFreq) { // function to print hapax legomena (words that appear only once)
        int hapaxCount = 0; // initializes a counter 'hapaxCount' to count words with a frequency of 1
        std::cout << "\nHapax Legomena (words that appear only once):" << std::endl; 

        for (const auto& pair : sortedFreq) { // iterates over each frequency-word pair in 'sortedFreq'
            if (pair.first == 1) { // checks if the frequency is 1 (indicating a hapax legomenon)
                ++hapaxCount; //increments the count 
                if (hapaxCount <= 10) { // Prints only the first 10 hapax legomena 
                    std::cout << pair.second << std::endl; //prints the word
                }
            }
        }

        std::cout << "\nTotal number of hapax legomena: " << hapaxCount << std::endl;  // prints total count of hapax legomena.
    }
}

