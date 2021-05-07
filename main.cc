/**
    @file main.cc
    The main file for pShell. This is the file that is compiled and run.
*/

#include "lib/helper_functions.hh"
#include "lib/calc_cmd.hh"
#include "lib/tri_cmd.hh"
#include "lib/help_cmd.hh"
#include "lib/multife_command.hh"
#include "lib/small_commands.hh"

#include <iostream>
#include <vector>
#include <string>

// Defining superglobal variables.

// Number that stores the last number used in Calculator.
// It is used to let the calculator remember the number between uses.
double CalcNumber = 0;

/**
    @fn int CommandCycle(const int kLayers)
    The function called each time the shell asks for a main-command.
    
    @param[in] kLayers The kLayers constant from main().
    @param[out] exit_code The exit code.
 */
int CommandCycle(const int kLayers) {
    std::string user_input;
    std::vector<std::string> cmds;

    std::getline(std::cin, user_input);
    cmds = helper::SplitString(user_input, "; ");

    helper::ConvertToLower(cmds[0]);

    // Testing for main commands. Sorted in order of implementation.
    if (cmds[0] == "quit" or cmds[0] == "exit")
        exit(0);

    if (cmds[0] == "calc")
        calc::main(kLayers + 1);
    
    if (cmds[0] == "tri")
        tri::main(kLayers + 1);
    
    if (cmds[0] == "help")
        help::main(kLayers + 1, cmds);

    if (cmds[0] == "multife" || cmds[0] == "os")
        multife::main(kLayers + 1);

    if (cmds[0] == "echo" && cmds.size() > 1) {
        std::cout << cmds[1] << '\n';
    }

    if (cmds[0] == "time" || cmds[0] == "date") {
        small_functions::time_command(kLayers + 1);
    }

    return 0;
}

int main(void) {
    std::cout << "pShell v3.0.0" << '\n';

    // I'm using a constant int, because the layers should always be 0 for main.
    const int kLayers = 0;

    while (true) {
        CommandCycle(kLayers);
    }

    return 0;
}