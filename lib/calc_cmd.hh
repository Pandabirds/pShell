/**
    @file calc.hh
    The header file that contains the calculator for pShell.
 */

#ifndef PSHELL_LIB_CALC_CMD_HH_
#define PSHELL_LIB_CALC_CMD_HH_

#include "helper_functions.hh"

#include <math.h>

#include <iostream>
#include <string>

extern double CalcNumber;

namespace calc {

    /**
        @fn inline int ProcessCommands(const std::vector<std::string> cmds)
        The function used to process commands from the user.

        @param[in] cmds A vector of the commands.
        @param[out] exit_Code The exit code of the function.
    */
    inline int ProcessCommands(const std::vector<std::string> cmds) {
        if (cmds[0] == "quit") {
            exit(0);
        }

        if (cmds[0] == "exit") {
            return 1;
        }

        if (cmds[0] == "add" && cmds.size() >= 1)
            if (helper::OnlyDigits(cmds[1], true) && cmds[1] != "")
                CalcNumber += stod(cmds[1]);

        if (cmds[0] == "sub" && cmds.size() >= 1)
            if (helper::OnlyDigits(cmds[1], true) && cmds[1] != "")
                CalcNumber -= stod(cmds[1]);

        if (cmds[0] == "mul" && cmds.size() >= 1)
            if (helper::OnlyDigits(cmds[1], true) && cmds[1] != "")
                CalcNumber *= stod(cmds[1]);

        if (cmds[0] == "div" && cmds.size() >= 1)
            if (helper::OnlyDigits(cmds[1], true) && cmds[1] != "" && cmds[1] != "0")
                CalcNumber /= stod(cmds[1]);

        if (cmds[0] == "pow" && cmds.size() >= 1)
            if (helper::OnlyDigits(cmds[1], true) && cmds[1] != "")
                CalcNumber = pow(CalcNumber, stod(cmds[1]));

        if (cmds[0] == "rot" && cmds.size() >= 1)
            if (helper::OnlyDigits(cmds[1], true) && cmds[1] != "")
                CalcNumber = pow(CalcNumber, 1.0 / stod(cmds[1]));

        if (cmds[0] == "sqrt")
            CalcNumber = sqrt(CalcNumber);

        if (cmds[0] == "trunc")
            CalcNumber = trunc(CalcNumber);

        if (cmds[0] == "sin")
            CalcNumber = sin(CalcNumber);

        if (cmds[0] == "cos")
            CalcNumber = cos(CalcNumber);

        if (cmds[0] == "tan")
            CalcNumber = tan(CalcNumber);

        if (CalcNumber != 0) {
            if (cmds[0] == "log")
                CalcNumber = log(CalcNumber);

            if (cmds[0] == "log2")
                CalcNumber = log2(CalcNumber);

            if (cmds[0] == "log10")
                CalcNumber = log10(CalcNumber);
        }

        if (helper::OnlyDigits(cmds[0], true))
            CalcNumber = stod(cmds[0]);

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
        if (ProcessCommands(cmds))
            return 1;
        
        return 0;
    }

    /**
        @fn inline int main(const int kLayers)
        The function that starts running the calculator.

        @param[out] exit_Code The exit code for the calculator.
    */
    inline int main(const int kLayers) {

        while (true) {
            if (CalcCycle(kLayers) == 1) break;
        }

        std::cout << "-CALC-" << '\n';
        return 0;
    }
}

#endif