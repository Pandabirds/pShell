/**
 * @file helper_functions.hpp
 * @brief A collection of helpful functions that ease the creation of pShell.
 * 
 * @fn std::vector<std::string> SplitString(std::string str, std::string delimiter)
 * @brief Split a string using a second string as a delimiter.
 * 
 * @fn int ConvertToLower(std::string& str)
 * @brief Convert a string to lowercase, then return a 0 if it was successful.
 * 
 * @fn std::string ReturnAsLower(std::string str)
 * @brief Return a string as lowercase.
 */

#pragma once
#include <iostream>
#include <vector>
#include <string>

namespace helper {
    /**
     * Split a string using a second string as a delimiter.
     * 
     * @param str The string to split.
     * @param delimiter The delimiter.
     * @return A vector of the split strings.
     */
    std::vector<std::string> SplitString(std::string str, std::string delimiter) {
        // Using position variable to measure the distance between cases of the delimiter.
        size_t position = 0;

        // Variable used for temporary storage of each token,
        // unnecessary, but makes the code cleaner.
        std::string token;

        // The vector that will be returned that stores all the split strings.
        // Using a vector is the most convenient option due to the lack of size
        // restrictions.
        std::vector<std::string> output_vector;

        // Keeps repeating until all the delimiters have been found.
        // If there is still a delimiter, the position goes straight to it.
        while ((position = str.find(delimiter)) != std::string::npos) {
            token = str.substr(0, position);
            output_vector.push_back(token);

            // Shortens the string to continue.
            str.erase(0, position + delimiter.length());
        }
        // Pushes the last token to the vector. This doesn't happen 
        // automatically because we assume there is no case of the delimiter at 
        // the end of the string.
        output_vector.push_back(str);

        return output_vector;
    }

    /**
     * Convert a string to lowercase, then return a 0 if it was successful.
     * 
     * @param str The string to convert.
     * @return The exit code, 0 if successful.
     */
    int ConvertToLower(std::string& str) {
        for (auto &character : str)
            character = std::tolower(character);
        return 0;
    }

    /**
     * Return a string as lowercase.
     * 
     * @param str The string to return as lowercase.
     * @return The string as lowercase.
     */
    std::string ReturnAsLower(std::string str) {
        helper::ConvertToLower(str);
        return str;
    }
}