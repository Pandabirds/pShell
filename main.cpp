#include "lib/calc.hpp"
#include "lib/helper_functions.hpp"

#include <iostream>
#include <vector>
#include <string>

int main() {
    std::cout << "pShell v3.0.0" << std::endl;

    while (true) {
        std::string user_input;
        std::vector<std::string> cmds;

        std::getline(std::cin, user_input);
        cmds = helper::SplitString(user_input, "; ");

        // Converting the first command in cmds to be lowercase.
        helper::ConvertToLower(cmds[0]);

        // Testing for main commands.
        // Sorted in order of implementation.
        if (cmds[0] == "calc") {
            calc::main();
        }
    }

    return 0;
}