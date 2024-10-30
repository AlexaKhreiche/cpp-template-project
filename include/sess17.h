#ifndef SESS17_H
#define SESS17_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <set>

namespace alexa {

/**
 * @brief Reads a book from a specified file and extracts alphabetic characters.
 * 
 * This function reads the contents of the specified file and returns a vector
 * containing only the alphabetic characters found in the file. Non-alphabetic
 * characters are replaced with spaces.
 * 
 * @param fileName The name of the file to read from.
 * @return A vector of characters containing the alphabetic characters from the file.
 */
std::vector<char> readBook(std::string fileName);

/**
 * @brief Computes the frequency of each word in the provided book.
 * 
 * This function takes a vector of characters and calculates how many times each
 * unique word appears in the book.
 * 
 * @param book A vector of characters representing the contents of the book.
 * @return A map where keys are words and values are their respective frequencies.
 */
std::map<std::string, int> computeWordFrequency(const std::vector<char>& book);

/**
 * @brief Counts the number of unique words in the provided book.
 * 
 * This function analyzes the contents of the book and returns the count of unique
 * words found.
 * 
 * @param book A vector of characters representing the contents of the book.
 * @return The number of unique words in the book.
 */
int countUniqueWords(const std::vector<char>& book);

/**
 * @brief Sorts word frequencies in descending order.
 * 
 * This function takes a map of word frequencies and returns a multimap sorted
 * by frequency in descending order.
 * 
 * @param frequencies A map where keys are words and values are their frequencies.
 * @return A multimap with frequencies as keys and words as values, sorted in descending order.
 */
std::multimap<int, std::string> sortFrequencies(const std::map<std::string, int>& frequencies);

/**
 * @brief Exports sorted word frequencies to a specified output file.
 * 
 * This function writes the sorted frequencies into a file, with each line containing
 * the rank, frequency, and word.
 * 
 * @param sortedFreq A multimap containing the sorted word frequencies.
 * @param outputFileName The name of the file to which frequencies will be exported.
 */
void exportFrequenciesToFile(const std::multimap<int, std::string>& sortedFreq, const std::string& outputFileName);

/**
 * @brief Prints hapax legomena from the sorted frequency data.
 * 
 * This function displays words that appear only once (hapax legomena) and the total
 * count of such words.
 * 
 * @param sortedFreq A multimap containing the sorted word frequencies.
 */
void printHapaxLegomena(const std::multimap<int, std::string>& sortedFreq);

} // namespace alexa

#endif // SESS17_H
