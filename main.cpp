/**
 * @file main.cpp
 * @brief The main file for pShell. This is the file that is compiled and run.
 * 
 * @fn int CommandCycle(const int kLayers)
 * @brief The function called each time the shell asks for a main-command.
 * 
 * @fn int main(void)
 * @brief The main function of pShell. Returns 0 if successful.
 */

#include "lib/helper_functions.hpp"
#include "lib/calc.hpp"

#include <iostream>
#include <vector>
#include <string>

// Defining superglobal variables.

// Number that stores the last number used in Calculator.
// It is used to let the calculator remember the number between uses.
double CalcNumber = 0;

/**
 * The function called each time the shell asks for a main-command.
 * 
 * @param kLayers The kLayers constant from main().
 * @return The exit code.
 */
int CommandCycle(const int kLayers) {
    std::string user_input;
    std::vector<std::string> cmds;

    std::getline(std::cin, user_input);
    cmds = helper::SplitString(user_input, "; ");

    helper::ConvertToLower(cmds[0]);

    // Testing for main commands. Sorted in order of implementation.
    if (cmds[0] == "quit" or cmds[0] == "exit") {
        exit(0);
    }

    if (cmds[0] == "calc") {
        calc::main(kLayers + 1);
    }

    return 0;
}


int main(void) {
    std::cout << "pShell v3.0.0" << std::endl;

    // I'm using a constant int, because the layers should always be 0 for main.
    const int kLayers = 0;

    while (true) {
        CommandCycle(kLayers);
    }

    return 0;
}