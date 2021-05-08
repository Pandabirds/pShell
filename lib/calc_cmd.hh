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

extern double CalcNumber;

namespace calc {

    /**
        @fn inline int ProcessCommands(const std::vector<std::string> cmds)
        The function used to process commands from the user.

        @param[in] kCmds A vector of the commands.
        @param[out] exit_Code The exit code of the function.
    */
    inline int ProcessCommands(const int kLayers, const std::vector<std::string> kCmds) {
        if (kCmds[0] == "quit") {
            exit(0);
        }

        if (kCmds[0] == "exit") {
            return 1;
        }

        if (kCmds.size() >= 2) {
            if (kCmds[0] == "add" && helper::OnlyDigits(kCmds[1], true) && kCmds[1] != "") {
                CalcNumber += stod(kCmds[1]);
            }

            if (kCmds[0] == "sub" && helper::OnlyDigits(kCmds[1], true) && kCmds[1] != "") {
                CalcNumber -= stod(kCmds[1]);
            }

            if (kCmds[0] == "mul" && helper::OnlyDigits(kCmds[1], true) && kCmds[1] != "") {
                CalcNumber *= stod(kCmds[1]);
            }

            if (kCmds[0] == "div" && helper::OnlyDigits(kCmds[1], true) && kCmds[1] != "" && kCmds[1] != "0") {
                CalcNumber /= stod(kCmds[1]);
            }

            if (kCmds[0] == "pow" && helper::OnlyDigits(kCmds[1], true) && kCmds[1] != "") {
                CalcNumber = pow(CalcNumber, stod(kCmds[1]));
            }

            if (kCmds[0] == "rot" && helper::OnlyDigits(kCmds[1], true) && kCmds[1] != "") {
                CalcNumber = pow(CalcNumber, 1.0 / stod(kCmds[1]));
            }
        }

        if (kCmds[0] == "sqrt") {
            CalcNumber = sqrt(CalcNumber);
        }

        if (kCmds[0] == "trunc") {
            CalcNumber = trunc(CalcNumber);
        }

        if (kCmds[0] == "sin") {
            CalcNumber = sin(CalcNumber);
        }

        if (kCmds[0] == "cos") {
            CalcNumber = cos(CalcNumber);
        }

        if (kCmds[0] == "tan") {
            CalcNumber = tan(CalcNumber);
        }

        if (CalcNumber != 0) {
            if (kCmds[0] == "log") {
                CalcNumber = log(CalcNumber);
            }

            if (kCmds[0] == "log2") {
                CalcNumber = log2(CalcNumber);
            }

            if (kCmds[0] == "log10") {
                CalcNumber = log10(CalcNumber);
            }
        }

        if (kCmds[0] == "help") {
            help::main(kLayers + 1, std::vector<std::string> ({"help", "calc"}));
        }


        if (helper::OnlyDigits(kCmds[0], true)) {
            CalcNumber = stod(kCmds[0]);
        }

        return 0;
    }

    /**
        @fn inline int CalcCycle(const int kLayers)
        The function called each time the calculator asks for a command.

        @param[in] kLayers The amount of layers to print out.
        @param[out] exit_code The exit code.
    */
    inline int CalcCycle(const int kLayers) {
        std::string user_input;
        std::vector<std::string> cmds;

        std::cout << helper::AutoIndent(kLayers + 1) << "<" << CalcNumber << ">" << '\n';

        std::cout << helper::AutoIndent(kLayers);
        std::getline(std::cin, user_input);
        cmds = helper::SplitString(user_input, "; ");
        helper::ConvertToLower(cmds[0]);

        // Processing user commands.
        if (ProcessCommands(kLayers + 1, cmds))
            return 1;
        
        return 0;
    }

    /**
        @fn inline int main(const int kLayers)
        The function that starts running the calculator.

        @param[out] exit_Code The exit code for the calculator.
    */
    inline int main(const int kLayers) {
        std::cout << helper::AutoIndent(kLayers - 1 ? kLayers != 0 : kLayers) << "-CALC-" << '\n';

        while (true) {
            if (CalcCycle(kLayers) == 1) break;
        }

        std::cout << helper::AutoIndent(kLayers - 1 ? kLayers != 0 : kLayers) << "-CALC-" << '\n';
        return 0;
    }
}

#endif