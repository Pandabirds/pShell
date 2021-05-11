/**
    @file small_commands.hh
    A header file for very small files.
*/

#ifndef PSHELL_LIB_SMALL_FUNCTIONS_HH_
#define PSHELL_LIB_SMALL_FUNCTIONS_HH_

#include "helper_functions.hh"

#include <time.h>
#include <unistd.h>

#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>

namespace small_functions {
    /**
        @fn inline void TimeCommand(const int kLayers)
        Outputs the current time.

        @param[in] kLayers The number of layers to output with.
    */
    inline void TimeCommand(const int kLayers) {
        time_t raw_time;
        time(&raw_time);

        struct tm* date;
        date = localtime(&raw_time);

        std::cout << helper::AutoIndent(kLayers) << asctime(date);
    }

    // Variable to tell the thread to stop if the user presses enter.
    static bool IsStopwatchStopped = false;

    inline void StopwatchThread(const int kLayers) {
        using namespace std::literals::chrono_literals;
        const auto start = std::chrono::system_clock::now();

        while (!IsStopwatchStopped) {
            auto current = std::chrono::system_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(current - start);
            size_t seconds = duration.count();
            std::cout << helper::AutoIndent(kLayers) << seconds % 60 << ' ' << (seconds / 60) % 60 << ' ' <<  (seconds / 3600) % 60 << '\r';
        }
    }

    inline void Stopwatch(const int kLayers) {
        IsStopwatchStopped = false;
        std::thread stopwatch_thread(StopwatchThread, kLayers);

        std::cin.get();

        IsStopwatchStopped = true;
        if (stopwatch_thread.joinable()) {
            stopwatch_thread.join();
        }
        
        // Clears extra output
        std::cout << "\r                         \r";
    }
}

#endif