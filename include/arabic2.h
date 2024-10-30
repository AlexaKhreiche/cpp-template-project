#ifndef ARABIC2_H
#define ARABIC2_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <locale>
#include <codecvt>
#include <algorithm>

namespace arabic2 {

/**
 * @brief Sets up the locale for handling wide character output.
 * 
 * This function sets the global locale to "en_US.UTF-8" and imbues
 * std::wcout to use the current locale for wide character output.
 */
void setupLocale();

/**
 * @brief Checks if a character is an Arabic alphabet character.
 * 
 * This function checks if a given wide character is in the Arabic Unicode block.
 * 
 * @param ch The character to check.
 * @return True if the character is Arabic, otherwise false.
 */
bool isArabicAlphabet(wchar_t ch);

/**
 * @brief Reads a book from a specified file and extracts Arabic characters.
 * 
 * This function reads the contents of the specified file and returns a vector
 * containing only the Arabic characters found in the file. Non-Arabic
 * characters are replaced with spaces.
 * 
 * @param fileName The name of the file to read from.
 * @return A vector of wide characters containing the Arabic characters from the file.
 */
std::vector<wchar_t> readBook(const std::string& fileName);

/**
 * @brief Analyzes the contents of a book file and computes word frequencies.
 * 
 * This function reads the Arabic text, extracts words, computes their frequencies,
 * and displays the results according to Zipf's Law.
 * 
 * @param fileName The name of the file to analyze.
 */
void zipfsLawExercise(const std::string& fileName);

} // namespace arabic

#endif // ARABIC2_H
