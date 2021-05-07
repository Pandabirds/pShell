/**
    @file small_commands.hh
    @brief A header file for very small files.
    
    @namespace small_functions
    @brief The namespace for storing the functions for the small commands.
        @fn inline void time_command(const int kLayers)
        @brief Outputs the current time.
*/

#ifndef PSHELL_LIB_SMALL_FUNCTIONS_HH_
#define PSHELL_LIB_SMALL_FUNCTIONS_HH_

#include "helper_functions.hh"

#include <time.h>

#include <iostream>

namespace small_functions {
    /** 
        Outputs the current time.

        @param[in] kLayers The number of layers to output with.
    */
    inline void time_command(const int kLayers) {
        time_t raw_time;
        time(&raw_time);

        struct tm* date;
        date = localtime(&raw_time);

        std::cout << helper::AutoIndent(kLayers) << asctime(date);
    }
}

#endif