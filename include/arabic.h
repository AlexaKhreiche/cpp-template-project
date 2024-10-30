#ifndef ARABIC_H
#define ARABIC_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <locale>
#include <codecvt>

namespace alexa_arabic {

/**
 * @brief Sets up the locale for UTF-8 output.
 */
void setupLocale();

/**
 * @brief Checks if a character is an Arabic alphabet.
 * 
 * @param ch The character to check.
 * @return true if the character is Arabic; otherwise false.
 */
bool isArabicAlphabet(wchar_t ch);

/**
 * @brief Reads a book from a specified file and extracts Arabic characters.
 * 
 * This function reads the contents of the specified file and returns a vector
 * containing only the Arabic characters found in the file. Non-Arabic characters
 * are replaced with spaces.
 * 
 * @param fileName The name of the file to read from.
 * @return A vector of wide characters containing the Arabic characters from the file.
 */
std::vector<wchar_t> readBook(const std::string& fileName);

/**
 * @brief Computes the frequency of each word in the provided book.
 * 
 * @param book A vector of wide characters representing the contents of the book.
 * @return A map where keys are words and values are their respective frequencies.
 */
std::map<std::wstring, int> computeWordFrequency(const std::vector<wchar_t>& book);

/**
 * @brief Counts the number of unique words in the provided book.
 * 
 * @param book A vector of wide characters representing the contents of the book.
 * @return The number of unique words in the book.
 */
int countUniqueWords(const std::vector<wchar_t>& book);

/**
 * @brief Sorts word frequencies in descending order.
 * 
 * @param frequencies A map where keys are words and values are their frequencies.
 * @return A multimap with frequencies as keys and words as values, sorted in descending order.
 */
std::multimap<int, std::wstring> sortFrequencies(const std::map<std::wstring, int>& frequencies);

/**
 * @brief Exports sorted word frequencies to a specified output file.
 * 
 * @param sortedFreq A multimap containing the sorted word frequencies.
 * @param outputFileName The name of the file to which frequencies will be exported.
 */
void exportFrequenciesToFile(const std::multimap<int, std::wstring>& sortedFreq, const std::string& outputFileName);

/**
 * @brief Prints hapax legomena from the sorted frequency data.
 * 
 * This function displays words that appear only once (hapax legomena) and the total
 * count of such words.
 * 
 * @param sortedFreq A multimap containing the sorted word frequencies.
 */
void printHapaxLegomena(const std::multimap<int, std::wstring>& sortedFreq);

} // namespace arabic

#endif // ARABIC_H
