/**
    @file help_cmd.hh
    The header file that contains the help command for pShell.
*/

#ifndef PSHELL_LIB_HELP_CMD_HH_
#define PSHELL_LIB_HELP_CMD_HH_

#include "helper_functions.hh"

#include <iostream>
#include <vector>

namespace help {
    /**
        @fn inline int main(const int kLayers, std::vector<std::string> kCmds)
        The main function for the help command.

        @param[in] kLayers The amount of layers to print at.
        @param[in] kCmds A vector holding the user-commands.
        @param[out] exit_code The exit code.
    */
    inline int main(const int kLayers, const std::vector<std::string> kCmds) {
        std::cout << helper::AutoIndent(kLayers - 1 ? kLayers != 0 : kLayers) << "-HELP-" << '\n';

        if (kCmds.size() >= 2) {
            if (kCmds[1] == "syntax") {
                std::cout << helper::AutoIndent(kLayers) << "The basic syntax for commands is: \"command; option; option; option\"" << '\n';
                std::cout << helper::AutoIndent(kLayers) << "When you add too little options, the command simply won't start." << '\n';
                std::cout << helper::AutoIndent(kLayers) << "However, if you add too many, it will work, but only use the first n options, where n is the amount of options the command is built to use." << '\n';
            }

            if (kCmds[1] == "calc") {
                std::cout << helper::AutoIndent(kLayers) << "calc : The pShell basic calculator." << '\n';
                std::cout << helper::AutoIndent(kLayers) << "It works by having a \"current number\", which is displays after each command." << '\n';
                std::cout << helper::AutoIndent(kLayers) << "You use commands to edit the current number." << '\n';
                std::cout << '\n';
                std::cout << helper::AutoIndent(kLayers) << "add; [n] : Adds [n] to the current number." << '\n';
                std::cout << helper::AutoIndent(kLayers) << "cos : Sets the current number to the cos of itself." << '\n';
                std::cout << helper::AutoIndent(kLayers) << "div; [n] : Divides the current number by [n]." << '\n';
                std::cout << helper::AutoIndent(kLayers) << "exit : Exits the Calculator." << '\n';
                std::cout << helper::AutoIndent(kLayers) << "help : Shows this menu." << '\n';
                std::cout << helper::AutoIndent(kLayers) << "log : Sets the current number to the log of itself." << '\n';
                std::cout << helper::AutoIndent(kLayers) << "log2 : Sets the current number to the log2 of itself." << '\n';
                std::cout << helper::AutoIndent(kLayers) << "log10 : Sets the current number to the log10 of itself." << '\n';
                std::cout << helper::AutoIndent(kLayers) << "mul; [n] : Multiplies the current number by [n]." << '\n';
                std::cout << helper::AutoIndent(kLayers) << "pow; [n] : Exponentiates the current number by [n]." << '\n';
                std::cout << helper::AutoIndent(kLayers) << "quit : Exits pShell." << '\n';
                std::cout << helper::AutoIndent(kLayers) << "rot; [n] : Sets the current number to the [n]th root of the current number.." << '\n';
                std::cout << helper::AutoIndent(kLayers) << "sin : Sets the current number to the sin of itself." << '\n';
                std::cout << helper::AutoIndent(kLayers) << "sub; [n] : Subtracts [n] from the current number." << '\n';
                std::cout << helper::AutoIndent(kLayers) << "sqrt : Sets the current number to the square root of the current number." << '\n';
                std::cout << helper::AutoIndent(kLayers) << "tan : Sets the current number to the tan of itself." << '\n';
                std::cout << helper::AutoIndent(kLayers) << "trunc : Truncates a decimal by removing everything after \".\"." << '\n';
                std::cout << helper::AutoIndent(kLayers) << "[n] : Sets the current number to [n]." << '\n';
            }

            if (kCmds[1] == "multife" || kCmds[1] == "os") {
                std::cout << helper::AutoIndent(kLayers) << "multife : The multi-purpose file explorer" << '\n';
                std::cout << helper::AutoIndent(kLayers) << "The multife command is primarily a file explorer," << '\n';
                std::cout << helper::AutoIndent(kLayers) << "but can also be used for various other things such as reading and writing files." << '\n';
                std::cout << '\n';
                std::cout << helper::AutoIndent(kLayers) << "List of Commands:" << '\n';
                std::cout << helper::AutoIndent(kLayers + 1) << "back; [repeats] : Equivalent to doing \"cd; ..\" [repeats] number of times." << '\n';
                std::cout << helper::AutoIndent(kLayers + 1) << "cd; [dir] : Changes the CWD to [dir]. Works with \"..\", and can use paths like \"../Documents/src\"" << '\n';
                std::cout << helper::AutoIndent(kLayers + 1) << "del; [name] : Deletes a file or driectory." << '\n';
                std::cout << helper::AutoIndent(kLayers + 1) << "du : Disk usage command." << '\n';
                std::cout << helper::AutoIndent(kLayers + 1) << "exit : Exits multife." << '\n';
                std::cout << helper::AutoIndent(kLayers + 1) << "help : Shows this menu." << '\n';
                std::cout << helper::AutoIndent(kLayers + 1) << "ls : Lists the items in the CWD." << '\n';
                std::cout << helper::AutoIndent(kLayers + 1) << "move; [name]; [new path] : Moves a file or directory from the CWD with the name [name] to [new path]." << '\n';
                std::cout << helper::AutoIndent(kLayers + 1) << "newdir : Creates a new directory in the CWD." << '\n';
                std::cout << helper::AutoIndent(kLayers + 1) << "newfile; [name] : Creates a new file in the CWD." << '\n';
                std::cout << helper::AutoIndent(kLayers + 1) << "quit : Quits pShell." << '\n';
                std::cout << helper::AutoIndent(kLayers + 1) << "read; [name] : Reads a file, along with indexing the lines." << '\n';
                std::cout << helper::AutoIndent(kLayers + 1) << "rename; [current name] [new name] : Renames a file or directory with [current name] in the CWD to [new name]." << '\n';
                std::cout << helper::AutoIndent(kLayers + 1) << "typewrite; [name] : Uses the typewriter command. If [name] is of a file that doesn't exist, it will create a new file, if it does, it will begin appending. Let's you edit a file like a typewriter, but without the ability to go upwards." << '\n';
                std::cout << helper::AutoIndent(kLayers + 1) << "writel; [path]; [line#]; [content] : Changes line [line#] in the file [path] to [content]." << '\n';
            }
        }

        if (kCmds.size() == 1) {
            std::cout << helper::AutoIndent(kLayers) << "Welcome to the pShell Help Menu." << '\n';
            std::cout << helper::AutoIndent(kLayers) << "You can get help about a certain command by typing \"help; [cmd]\"." << '\n';
            std::cout << helper::AutoIndent(kLayers) << "There are also other special help sections, such as:" << '\n';
            std::cout << helper::AutoIndent(kLayers + 1) << "help; syntax : Shows help about the syntax of pShell." << '\n';
            std::cout << '\n';
            std::cout << helper::AutoIndent(kLayers) << "Here's a list of the main commands you can do:" << '\n';
            std::cout << helper::AutoIndent(kLayers + 1) << "calc : Starts the calculator." << '\n';
            std::cout << helper::AutoIndent(kLayers + 1) << "cmd; [command] : Executes a command in the operating system's terminal." << '\n';
            std::cout << helper::AutoIndent(kLayers + 1) << "echo; [message] : Prints [message] to the console." << '\n';
            std::cout << helper::AutoIndent(kLayers + 1) << "exit : Quits pShell." << '\n';
            std::cout << helper::AutoIndent(kLayers + 1) << "multife : Starts the multi-purpose file explorer." << '\n';
            std::cout << helper::AutoIndent(kLayers + 1) << "help : Shows help." << '\n';
            std::cout << helper::AutoIndent(kLayers + 1) << "quit : Quits pShell." << '\n';
        }

        std::cout << helper::AutoIndent(kLayers - 1 ? kLayers != 0 : kLayers) << "-HELP-" << '\n';
        return EXIT_SUCCESS;
    }
}

#endif