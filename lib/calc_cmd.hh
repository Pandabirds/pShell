/**
    @file calc.hh
    The header file that contains the calculator for pShell.
 */

#ifndef PSHELL_LIB_CALC_CMD_HH_
#define PSHELL_LIB_CALC_CMD_HH_

#include "helper_functions.hh"
#include "help_cmd.hh"

#include <math.h>

#include <iostream>
#include <string>

namespace calc {

    /**
        @fn inline int ProcessCommands(const int kLayers, const std::vector<std::string> kCmds, double &calc_number)
        The function used to process commands from the user.

        @param[in] kCmds A vector of the commands.
        @param[out] exit_Code The exit code of the function.
    */
    inline int ProcessCommands(const int kLayers, const std::vector<std::string> kCmds, double &calc_number) {
        if (kCmds[0] == "quit") {
            exit(0);
        }

        if (kCmds[0] == "exit") {
            return 1;
        }

        if (kCmds.size() >= 2) {
            if (kCmds[0] == "add" && helper::OnlyDigits(kCmds[1], true) && kCmds[1] != "") {
                calc_number += stod(kCmds[1]);
            }

            if (kCmds[0] == "sub" && helper::OnlyDigits(kCmds[1], true) && kCmds[1] != "") {
                calc_number -= stod(kCmds[1]);
            }

            if (kCmds[0] == "mul" && helper::OnlyDigits(kCmds[1], true) && kCmds[1] != "") {
                calc_number *= stod(kCmds[1]);
            }

            if (kCmds[0] == "div" && helper::OnlyDigits(kCmds[1], true) && kCmds[1] != "" && kCmds[1] != "0") {
                calc_number /= stod(kCmds[1]);
            }

            if (kCmds[0] == "pow" && helper::OnlyDigits(kCmds[1], true) && kCmds[1] != "") {
                calc_number = pow(calc_number, stod(kCmds[1]));
            }

            if (kCmds[0] == "rot" && helper::OnlyDigits(kCmds[1], true) && kCmds[1] != "") {
                calc_number = pow(calc_number, 1.0 / stod(kCmds[1]));
            }
        }

        if (kCmds[0] == "sqrt") {
            calc_number = sqrt(calc_number);
        }

        if (kCmds[0] == "trunc") {
            calc_number = trunc(calc_number);
        }

        if (kCmds[0] == "sin") {
            calc_number = sin(calc_number);
        }

        if (kCmds[0] == "cos") {
            calc_number = cos(calc_number);
        }

        if (kCmds[0] == "tan") {
            calc_number = tan(calc_number);
        }

        if (calc_number != 0) {
            if (kCmds[0] == "log") {
                calc_number = log(calc_number);
            }

            if (kCmds[0] == "log2") {
                calc_number = log2(calc_number);
            }

            if (kCmds[0] == "log10") {
                calc_number = log10(calc_number);
            }
        }


        if (kCmds[0] == "help") {
            help::main(kLayers + 1, std::vector<std::string> ({"help", "calc"}));
        }


        if (helper::OnlyDigits(kCmds[0], true)) {
            calc_number = stod(kCmds[0]);
        }

        return EXIT_SUCCESS;
    }

    /**
        @fn inline int CalcCycle(const int kLayers, double &calc_number)
        The function called each time the calculator asks for a command.

        @param[in] kLayers The amount of layers to print out.
        @param[out] exit_code The exit code.
    */
    inline int CalcCycle(const int kLayers, double &calc_number) {
        std::string user_input;
        std::vector<std::string> cmds;

        std::cout << helper::AutoIndent(kLayers + 1) << "<" << calc_number << ">" << '\n';

        std::cout << helper::AutoIndent(kLayers);
        std::getline(std::cin, user_input);
        cmds = helper::SplitString(user_input, "; ");
        helper::ConvertToLower(cmds[0]);

        // Processing user commands.
        if (ProcessCommands(kLayers + 1, cmds, calc_number))
            return 1;
        
        return EXIT_SUCCESS;
    }

    /**
        @fn inline double main(const int kLayers, double &calc_number)
        The function that starts running the calculator.

        @param[out] exit_Code The exit code for the calculator.
    */
    inline int main(const int kLayers, double &calc_number) {
        std::cout << helper::AutoIndent(kLayers - 1 ? kLayers != 0 : kLayers) << "-CALC-" << '\n';

        while (true) {
            if (CalcCycle(kLayers, calc_number) == 1) break;
        }

        std::cout << helper::AutoIndent(kLayers - 1 ? kLayers != 0 : kLayers) << "-CALC-" << '\n';
        return EXIT_SUCCESS;
    }
}

#endif