#ifndef PSHELL_LIB_HELP_CMD_HH_
#define PSHELL_LIB_HELP_CMD_HH_

#include "helper_functions.hh"

#include <iostream>
#include <vector>

namespace help {
    inline int main(const int kLayers, std::vector<std::string> cmds) {
        std::cout << "-HELP-" << '\n';

        if (cmds.size() == 1) {
            std::cout << helper::AutoIndent(kLayers) << "Welcome to the pShell Help Menu" << '\n';
            std::cout << helper::AutoIndent(kLayers) << "You can get help about a certain command by typing \"help; [cmd]\"" << '\n';
            std::cout << helper::AutoIndent(kLayers) << "There are also other special help sections, such as:" << '\n';
            std::cout << helper::AutoIndent(kLayers + 1) << "-help; syntax : Shows help about the syntax of pShell." << '\n';
            std::cout << '\n';
            std::cout << helper::AutoIndent(kLayers) << "Here's a list of the main commands you can do:" << '\n';
            std::cout << helper::AutoIndent(kLayers + 1) << "-calc; Starts the calculator." << '\n';
            std::cout << helper::AutoIndent(kLayers + 1) << "-exit; Quits pShell." << '\n';
            std::cout << helper::AutoIndent(kLayers + 1) << "-multife; Starts the multi-purpose file explorer." << '\n';
            std::cout << helper::AutoIndent(kLayers + 1) << "-help : Shows help." << '\n';
            std::cout << helper::AutoIndent(kLayers + 1) << "-quit : Quits pShell." << '\n';
            std::cout << helper::AutoIndent(kLayers + 1) << "-tri; Starts the triangle calculator." << '\n';
        }

        std::cout << "-HELP-" << '\n';
        return 0;
    }
}

#endif