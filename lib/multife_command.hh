/**
    @file multife_command.hh
    @brief The header file that contains the multi-purpoes file explorer for pShell.
    
    @namespace multife
    @brief The set of functions used by the calculator to function.
        @fn inline bool FileExists(const std::string kPath)
        @brief Function for testing if a file exists or not. It uses the C file 
        handling for the conditional.

        @fn inline int BackDirectory(const unsigned int kRepeats)
        @brief Function used by the user to go up a certain amount of directories.

        @fn inline int DeleteItem(const std::string kPath, const int kLayers, const std::vector<std::string> kCmds)
        @brief Deletes an item with user confirmation, for multife commands.

        @fn std::fstream& GotoLine(std::fstream& file, unsigned int num)
        @brief Sets a file's current line.

        @fn bool IsFile(const std::string kPath)
        @brief Returns a boolean value indicating whether or not the given path leads
        to a file.

        @fn inline int VectorToFile(const std::string kPath, const std::vector<std::string> kLineHolder)
        @brief Outputs all the strings in a vector into a file.

        @fn std::vector<std::string> FileToVector(std::string path)
        @brief Returns a vector holding the lines of a file as strings.

        @fn inline size_t CountLines(const std::string kPath)
        @brief Returns the amount of lines in a file.

        @fn inline std::string AlignIndex(const int kIndex, const int kHighestIndex)
        @brief Aligns an index number to fit with a highest index, and returns it as a string.

        @fn inline int PrintFile(const std::string kPath, const int kLayers, const bool kAddLineNumbers = true)
        @brief Prints the lines of a file.

        @fn std::string GetCurrentWorkingDirectory()
        @brief Returns the cwd without using c-strings and getcwd().

        @fn inline void DuCommand(const std::string kPath, const int kLayers)
        @brief The du command in multife.

        @fn int ListCurrentWorkingDirectory(const int kLayers)
        @brief Prints out the contents of the current working directory.

        @fn inline int WriteFileLine(const std::string kPath, const unsigned int kLineNumber, const std::string kContent)
        @brief Overwrites a single line in a file.

        @fn inline int TypeWrite(const std::string kPath, const int kLayers)
        @brief The multife typewriter command.

        @fn int ProcessCommands(std::vector<std::string> cmds, const int kLayers)
        @brief The function that processes user commands.

        @fn int MultifeCommandCycle (const int kLayers)
        @brief The function called each time the calculator asks for a command.

        @fn std::fstream& GotoLine(std::fstream& file, unsigned int num)
        @brief Sets a file's current line.
    */

//TODO: 21/5/0X
//TODO: add creating files
//TODO: add creating directories

#ifndef PSHELL_LIB_MULTIFE_COMMAND_HH_
#define PSHELL_LIB_MULTIFE_COMMAND_HH_

#include "helper_functions.hh"

#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/statvfs.h>

#include <iostream>
#include <fstream>
#include <string>

namespace multife {

    /**
        Function for testing if a file exists or not. It uses the C file handling
        for the conditional.

        @param kPath the path of the file.
        @return Whether or not the file exists.
    */
    inline bool FileExists(const std::string kPath) {
        FILE* target_file;
        
        if ((target_file = fopen(kPath.c_str(), "r"))) {
            return true;
        }

        return false;
    }

    /**
        Function used by the user to go up a certain amount of directories.

        @param kRepeats The amount of times to go up a directory.
        @return The exit code.
    */
    inline int BackDirectory(const unsigned int kRepeats) {
        
        for (size_t i = 0; i < kRepeats; i++) {
            chdir("..");
        }

        return 0;
    }

    /**
        Sets a file's current line.
        https://stackoverflow.com/questions/5207550/in-c-is-there-a-way-to-go-to-a-specific-line-in-a-text-file
        
        @param file The variable containing the file handler.
        @param num The line number (Starts from 0)
        @return A reference to the file.
     */
    inline std::fstream& GotoLine(std::fstream& file, unsigned int num) {
        file.seekg(std::ios::beg);
        for(size_t i = 1; i < num; ++i){
            file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }
        return file;
    }

    /**
        Returns a boolean value indicating whether or not the given path leads to a file.

        @param kPath The path of the file as a string.
        @return Whether or not the path leads to a file.
     */
    inline bool IsFile(const std::string kPath) {
        // https://stackoverflow.com/questions/146924/how-can-i-tell-if-a-given-path-is-a-directory-or-a-file-c-c#146938
        struct stat s;
        if (stat(kPath.c_str(), &s) == 0) {
            if (s.st_mode & S_IFREG) {
                return true;
            }
        }

        return false;
    }

    /**
        Deletes an item with user confirmation, for multife commands.

        @param kPath The path of the file to delete.
        @param kLayers The amount of layers to print at.
        @param kCmds The user commands, incase the user wants to automatically bypass the confirmation.
    */
    inline int DeleteItem(const std::string kPath, const int kLayers, const std::vector<std::string> kCmds) {
        if (kCmds.size() > 2) {
            if (kCmds[2] == "bypass") {
                system(("rm -r " + kPath).c_str());
                return 0;
            }
        }

        std::string user_confirm;
        std::cout << helper::AutoIndent(kLayers) << "Are you sure you want to delete " << kPath << "? (y/n)" << '\n'; 
        std::cout << helper::AutoIndent(kLayers);
        std::getline(std::cin, user_confirm);
        if (!(user_confirm == "y")) {
            return 0;
        }

        // Bit of a hacky solution but it works.
        system(("rm -r " + kPath).c_str());

        return 0;
    }

    /**
        Outputs all the strings in a vector into a file.

        @param kPath The path to the file.
        @param kLineHolder A vector of std::string holding all the lines to be added.
        @return The exit code.
     */
    inline int VectorToFile(const std::string kPath, const std::vector<std::string> kLineHolder) {
        
        std::ofstream target_file;
        target_file.open(kPath, std::ios::out);

        if (!target_file) {
            return 1;
        }

        for (const auto& line : kLineHolder) {
            target_file << line << '\n';
        }

        target_file.close();
        return 0;
    }

    /**
        Returns a vector holding the lines of a file as strings.

        @param kPath The path to the file.
        @return A vector holding the lines of the file as strings.
     */
    inline std::vector<std::string> FileToVector(const std::string kPath) {
        std::vector<std::string> line_holder;

        std::ifstream target_file;
        target_file.open(kPath, std::ios::in);
        if (!target_file) {
            return line_holder;
        }

        std::string line;
        while (std::getline(target_file, line)) {
            line_holder.push_back(line);
        }

        target_file.close();

        return line_holder;
    }

    /**
        Returns the amount of lines in a file.

        @param kPath The path to the file.
        @return The amount of lines in the file.
     */
    inline size_t CountLines(const std::string kPath) {
        return FileToVector(kPath).size();
    }

    /**
        Aligns an index number to fit with a highest index, and returns it as a string.

        @param kIndex The index number to align.
        @param kHighestIndex The highest index, or the length the string should be.
        @return The aligned index number as a string.
    */
    inline std::string AlignIndex(const int kIndex, const int kHighestIndex) {
        std::string aligned = std::to_string(kIndex);
        const size_t kHighestIndexDigits = helper::CountDigits(kHighestIndex);
        const size_t kIndexDigits = helper::CountDigits(kIndex);

        for (size_t i = 0; i < kHighestIndexDigits - kIndexDigits; i++) {
            aligned += " ";
        }
        
        return aligned;
    }

    /**
        Prints the lines of a file.

        @param kPath The path to the file.
        @param kLayers The amount of layers it is printing at. Use 0 for normal
        printing.
        @param kAddLineNumbers Boolean whether or not to add line numbers, default is true.
        @return The exit code.
     */
    inline int PrintFile(const std::string kPath, const int kLayers, const bool kAddLineNumbers = true) {
        std::vector<std::string> line_holder = FileToVector(kPath);
        for (size_t i = 0; i < line_holder.size(); ++i) {
            const int kHighestIndex = line_holder.size() - 1;
            
            std::cout << helper::AutoIndent(kLayers);
            if (kAddLineNumbers) {
                std::cout << AlignIndex(i, kHighestIndex) << "│";
            }
            std::cout << line_holder[i] << '\n';
        }

        return 0;
    }

    /**
        Returns the current working directory without using c-strings and getcwd().

        @return The current working directory.
     */
    inline std::string GetCurrentWorkingDirectory(void) {
        const unsigned int kMax = 1024;
        char buffer[kMax];
        getcwd(buffer, kMax);
        return std::string(buffer);
    }

    /**
        The du command in multife.

        @param kPath The path of the directory to use.
        @param kLayers The amount of layers to print out with.
    */
    inline void DuCommand(const std::string kPath, const int kLayers) {
        
        struct statvfs buffer;
        statvfs(kPath.c_str(), &buffer);

        unsigned long block_size = buffer.f_bsize;
        unsigned long free_space = buffer.f_bavail / block_size;
        unsigned long total_space = buffer.f_blocks / block_size;
        unsigned long used_space = (buffer.f_blocks - buffer.f_bavail) / block_size;
        
        std::cout << helper::AutoIndent(kLayers + 1) << "Free: " << free_space << '\n';
        std::cout << helper::AutoIndent(kLayers + 1) << "Used: " << used_space << '\n';
        std::cout << helper::AutoIndent(kLayers + 1) << "Total: " << total_space << '\n';
    }

    /**
        Prints out the contents of the current working directory.

        @param kLayers The amount of layers it is printing at. Use 0 for normal printing.
        @return The exit code.
     */
    inline int ListCurrentWorkingDirectory(const int kLayers) {
        struct dirent* entry;
        DIR *dir = opendir(".");
        if (dir == NULL) {
            return 1;
        }

        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_name != std::string(".")) {
                std::string type;
                if (IsFile(GetCurrentWorkingDirectory() + "/" + std::string(entry->d_name))) {
                    type = "FIL";
                }

                if (type != "FIL") {
                    type = "DIR";
                }

                std::cout << helper::AutoIndent(kLayers) << "<" << type << "> <" << entry->d_name << ">" << '\n';
            }
        }

        return 0;
    }

    /**
        Overwrites a single line in a file.

        @param kPath The path of the file to change a line in.
        @param kLineNumber The line number.
        @param kContent What to change the line to.
        @return The exit code.
     */
    inline int WriteFileLine(const std::string kPath, const unsigned int kLineNumber, const std::string kContent) {
        std::vector<std::string> lines_to_write = FileToVector(kPath);

        lines_to_write[kLineNumber] = kContent;

        std::ofstream target_file;
        target_file.open(kPath, std::ios::out);

        for (const auto& line : lines_to_write) {
            target_file << line << '\n';
        }

        target_file.close();

        return 0;
    }

    /**
        The multife typewriter command.

        @param kPath The path of the file to edit.
        @param kLayers The amount of layers to print with.
        @return The exit code.
    */
    inline int TypeWrite(const std::string kPath, const int kLayers) {

        std::fstream target_file;

        if (FileExists(kPath)) {
            PrintFile(kPath, kLayers, false);
        }
        
        if (!FileExists(kPath)) {
            target_file.open(kPath, std::ios::out);
            target_file.close();
        }

        target_file.open(kPath, std::ios::app);

        while (true) {
            std::cout << helper::AutoIndent(kLayers);

            std::string input;
            std::getline(std::cin, input);

            for (const auto& character : input) {
                if (character == 27) {
                    goto Exited;
                }
            }

            target_file << input << std::endl;
        }
        Exited:

        target_file.close();
        return 0;
    }

    /**
        The function that processes user commands.

        @param cmds A vector of strings containing the commands to process.
        @param kLayers The amount of layers to print at.
        @return The exit code.
     */
    inline int ProcessCommands(std::vector<std::string> cmds, const int kLayers) {
        if (cmds[0] == "quit") {
            exit(0);
        }

        if (cmds[0] == "exit") {
            return 1;
        }

        // I'm doing length-checks like this so it looks nicer when I add more
        // commands.
        if (cmds.size() > 1) {

            if (cmds.size() > 2) {
                if (cmds.size() > 3) {
                    if (cmds[0] == "writel" && helper::OnlyDigits(cmds[2])) {
                        WriteFileLine(cmds[1], stoi(cmds[2]), cmds[3]);
                    }
                }

                if (cmds[0] == "rename") {
                    std::rename((GetCurrentWorkingDirectory()  + "/" + cmds[1]).c_str(), (GetCurrentWorkingDirectory() + "/" + cmds[2]).c_str());
                }

                if (cmds[0] == "move") {
                    std::rename((GetCurrentWorkingDirectory() + "/" + cmds[1]).c_str(), (cmds[2] + "/" + cmds[1]).c_str());
                }
            }

            if (cmds[0] == "cd") {
                chdir(cmds[1].c_str());
            }

            if (cmds[0] == "read") {
                PrintFile(cmds[1], kLayers + 1);
            }

            if (cmds[0] == "typewrite") {
                TypeWrite(cmds[1], kLayers + 1);
            }

            if (cmds[0] == "del" || cmds[0] == "delete") {
                DeleteItem(cmds[1], kLayers + 1, cmds);
            }

            if (cmds[0] == "back") {
                BackDirectory(stoi(cmds[1]));
            }
        }

        if (cmds[0] == "ls" || cmds[0] == "dir") {
            ListCurrentWorkingDirectory(kLayers + 1);
        }

        if (cmds[0] == "du" || cmds[0] == "disk") {
            DuCommand(GetCurrentWorkingDirectory(), kLayers + 1);
        }

        return 0;
    }

    /**
        The function called each time the calculator asks for a command.

        @param kLayers The amount of layers to print at.
        @return The exit code.
     */
    inline int MultifeCommandCycle (const int kLayers) {
        std::string user_input;
        std::vector<std::string> cmds;

        std::cout << helper::AutoIndent(kLayers) << GetCurrentWorkingDirectory() << "::";
        std::getline(std::cin, user_input);
        cmds = helper::SplitString(user_input, "; ");
        helper::ConvertToLower(cmds[0]);

        if (ProcessCommands(cmds, kLayers)) {
            return 1;
        }

        return 0;
    }

    inline int main(const int kLayers) {
        std::cout << "-MULTIFE-" << '\n';
        while (true) {
            if (MultifeCommandCycle(kLayers) == 1)
                break;
        }
        std::cout << "-MULTIFE-" << '\n';
        return 0;
    }
}

#endif