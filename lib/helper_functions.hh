/**
    @file helper_functions.hh
    @brief A collection of helpful functions that ease the creation of pShell.
    
    @namespace helper
    @brief A namespace containing the helper functions.
        @fn inline std::vector<std::string> SplitString(std::string str, const std::string kDelimiter)
        @brief Splits a string using a second string as a delimiter.

        @fn inline int ConvertToLower(std::string& str)
        @brief Converts a string to lowercase, then return a 0 if it was successful.
        
        @fn inline std::string ReturnAsLower(std::string str)
        @brief Returns a string as lowercase.
        
        @fn inline std::string AutoIndent(int layers)
        @brief Returns (4 * layers) spaces. Used for quick indentation throughout the shell.
        
        @fn inline bool OnlyDigits(const std::string str, const bool kForMath = false)
        @brief Returns a boolean value indicating whether or not the given string only
        contains digits.
        
        @fn inline bool IsStringInVector(std::string str, std::vector<std::string> vector)
        @brief Returns a boolean value indicating whether or not a given string is in a vector. 
        contains digits.

        @fn inline size_t CountDigits(unsigned int number)
        @brief Returns the amount of digits in an unsigned integer.
 */

#ifndef PSHELL_LIB_HELPER_FUNCTIONS_HH_
#define PSHELL_LIB_HELPER_FUNCTIONS_HH_

#include <iostream>
#include <vector>
#include <string>
#include <any>
#include <fstream>
#include <limits>

namespace helper {
    /**
        Splits a string using a second string as a delimiter.

        @param[in] str The string to split.
        @param[in] kDelimiter The delimiter.
        @param[out] split_string A vector of the split strings.
     */
    inline std::vector<std::string> SplitString(std::string str, const std::string kDelimiter) {
        // Using position variable to measure the distance between cases of the delimiter.
        size_t position = 0;

        // Variable used for temporary storage of each token,
        // unnecessary, but makes the code cleaner.
        std::string token;

        // The vector that will be returned that stores all the split strings.
        // Using a vector is the most convenient option due to the lack of size
        // restrictions.
        std::vector<std::string> output_vector;
        while ((position = str.find(kDelimiter)) != std::string::npos) {
            token = str.substr(0, position);
            output_vector.push_back(token);

            // Shortens the string to continue.
            str.erase(0, position + kDelimiter.length());
        }
        // Pushes the last token to the vector. This doesn't happen 
        // automatically because we assume there is no case of the delimiter at 
        // the end of the string.
        output_vector.push_back(str);

        return output_vector;
    }

    /**
        Converts a string to lowercase, then return a 0 if it was successful.

        @param[in] str The string to convert.
        @param[out] exit_code The exit code, 0 if successful.
     */
    inline int ConvertToLower(std::string& str) {
        for (auto &character : str)
            character = std::tolower(character);
        return 0;
    }

    /**
        Returns a string as lowercase.

        @param[in] str The string to return as lowercase.
        @param[out] lowercase_str The string as lowercase.
     */
    inline std::string ReturnAsLower(std::string str) {
        helper::ConvertToLower(str);
        return str;
    }

    /**
        Returns (4 * layers) spaces. Used for quick indentation throughout the shell.

        @param[in] layers An integer representing the amount of layers of indentation.
        @param[out] indent The string made from the spaces to be used for indentation.
     */
    inline std::string AutoIndent(const int layers) {
        std::string output_string = "";
        for (int i = 0; i < layers; ++i) {
            output_string.append("    ");
        }
        return output_string;
    }

    /**
        Returns a boolean value indicating whether or not the given string only 
        contains digits.

        @param[in] str The string to test.
        @param[in] kForMath Whether or not to include the extra symbol(s): '-', '.', 
        it will also only accept one case of '.' if kForMath is true. kForMath is 
        set to false by default.
        @param[out] are_there_only_digits Whether or not there are only digits in str.
     */
    inline bool OnlyDigits(const std::string str, const bool kForMath = false) {
        
        if (kForMath) {
            bool can_fit_minus = false;
            bool can_fit_decimal = false;
            for (const auto &character : str) {
                if (!(std::isdigit(character) || (!can_fit_minus && character == '-') || (!can_fit_decimal && character == '.')))
                    return false;
                if (character == '.')
                    can_fit_decimal = true;
                if (character == '-')
                    can_fit_minus = true;
            }
        }

        if (!kForMath) {
            for (const auto &character : str) {
                if (!std::isdigit(character))
                    return false;
            }
        }
        return true;
    }

    /**
        Returns a boolean value indicating whether or not a given string is in a 
        vector.

        @param[in] str The string to search for.
        @param[in] vector The vector to search through.
        @param[out] is_string_in_vector Whether or not str was found in vector.
     */
    inline bool IsStringInVector(std::string str, std::vector<std::string> vector) {
        bool flag = true;
        for (const auto &element : vector) {
            if (element == str) {
                flag = false;
                break;
            }
        }

        return flag;
    }

    /**
        Returns the amount of digits in an unsigned integer.

        @param[in] number The unsigned number to count the digits of.
        @param[out] count The amount of digits in the number.
    */
    inline size_t CountDigits(unsigned int number) {
        size_t count = 0;
        while (number /= 10) {
            count++;
        }
        return count;
    } 
}

#endif