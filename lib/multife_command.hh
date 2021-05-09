/**
    @file multife_command.hh
    The header file that contains the multi-purpoes file explorer for pShell.
*/

#ifndef PSHELL_LIB_MULTIFE_COMMAND_HH_
#define PSHELL_LIB_MULTIFE_COMMAND_HH_

#include "helper_functions.hh"
#include "help_cmd.hh"

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
        @fn inline bool FileExists(const std::string kPath)

        Function for testing if a file exists or not. It uses the C file handling
        for the conditional.

        @param[in] kPath the path of the file.
        @param[out] does_file_exist Whether or not the file exists.
    */
    inline bool FileExists(const std::string kPath) {
        FILE* target_file;
        
        if ((target_file = fopen(kPath.c_str(), "r"))) {
            fclose(target_file);
            return true;
        }

        return false;
    }

    /**
        @fn inline int BackDirectory(const unsigned int kRepeats)
        Function used by the user to go up a certain amount of directories.

        @param[in] kRepeats The amount of times to go up a directory.
        @param[out] exit_code The exit code.
    */
    inline int BackDirectory(const unsigned int kRepeats) {
        
        for (size_t i = 0; i < kRepeats; ++i) {
            chdir("..");
        }

        return 0;
    }

    /**
        @fn inline std::fstream& GotoLine(std::fstream& file, unsigned int num)
        Sets a file's current line.
        https://stackoverflow.com/questions/5207550/in-c-is-there-a-way-to-go-to-a-specific-line-in-a-text-file
        
        @param[in] file The variable containing the file handler.
        @param[in] num The line number (Starts from 0)
        @param[out] file A reference to the file.
    */
    inline std::fstream& GotoLine(std::fstream& file, unsigned int num) {
        file.seekg(std::ios::beg);
        for(size_t i = 1; i < num; ++i){
            file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }
        return file;
    }

    /**
        @fn inline bool IsFile(const std::string kPath)
        Returns a boolean value indicating whether or not the given path leads to a file.

        @param[in] kPath The path of the file as a string.
        @param[out] is_file Whether or not the path leads to a file.
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
        @fn inline int DeleteItem(const std::string kPath, const int kLayers, const std::vector<std::string> kCmds)
        Deletes an item with user confirmation, for multife commands.

        @param[in] kPath The path of the file to delete.
        @param[in] kLayers The amount of layers to print at.
        @param[in] kCmds The user commands, incase the user wants to automatically bypass the confirmation.
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
        @fn inline int VectorToFile(const std::string kPath, const std::vector<std::string> kLineHolder)
        Outputs all the strings in a vector into a file.

        @param[in] kPath The path to the file.
        @param[in] kLineHolder A vector of std::string holding all the lines to be added.
        @param[out] exit_code The exit code.
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
        @fn inline std::vector<std::string> FileToVector(const std::string kPath)
        Returns a vector holding the lines of a file as strings.

        @param[in] kPath The path to the file.
        @param[out] line_holder A vector holding the lines of the file as strings.
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
        @fn inline size_t CountLines(const std::string kPath)
        Returns the amount of lines in a file.

        @param[in] kPath The path to the file.
        @param[out] count The amount of lines in the file.
    */
    inline size_t CountLines(const std::string kPath) {
        return FileToVector(kPath).size();
    }

    /**
        @fn inline std::string AlignIndex(const int kIndex, const int kHighestIndex)
        Aligns an index number to fit with a highest index, and returns it as a string.

        @param[in] kIndex The index number to align.
        @param[in] kHighestIndex The highest index, or the length the string should be.
        @param[out] output_string The aligned index number as a string.
    */
    inline std::string AlignIndex(const int kIndex, const int kHighestIndex) {
        std::string aligned = std::to_string(kIndex);
        const size_t kHighestIndexDigits = helper::CountDigits(kHighestIndex);
        const size_t kIndexDigits = helper::CountDigits(kIndex);

        for (size_t i = 0; i < kHighestIndexDigits - kIndexDigits; ++i) {
            aligned += " ";
        }
        
        return aligned;
    }

    /**
        @fn inline int PrintFile(const std::string kPath, const int kLayers, const bool kAddLineNumbers = true)
        Prints the lines of a file.

        @param[in] kPath The path to the file.
        @param[in] kLayers The amount of layers it is printing at. Use 0 for normal
        printing.
        @param[in] kAddLineNumbers Boolean whether or not to add line numbers, default is true.
        @param[out] exit_code The exit code.
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
        @fn inline std::string GetCurrentWorkingDirectory(void)
        Returns the current working directory without using c-strings and getcwd().

        @param[out] cwd The current working directory.
    */
    inline std::string GetCurrentWorkingDirectory(void) {
        const unsigned int kMax = 1024;
        char buffer[kMax];
        getcwd(buffer, kMax);
        return std::string(buffer);
    }

    /**
        @fn inline int CreateDirectory(const std::string kName)
        Create a directory in the cwd.

        @param[in] kName The name of the directory to create.
        @param[out] exit_code The exit code.
    */
    inline int CreateDirectory(const std::string kName) {
        if (mkdir(kName.c_str(), 0777) == -1) {
            return 1;
        };
        
        return 0;
    }

    /**
        @fn inline int CreateFile(const std::string kName)
        Creates a file in the cwd.

        @param[in] kName The name of the file to create.
        @param[out] exit_code The exit code.
    */
    inline int CreateFile(const std::string kName) {
        std::ofstream target_file;
        target_file.open(kName, std::ios::out);

        if (!target_file) {
            return 1;
        }

        target_file.close();
        
        return 0;
    }

    /**
        @fn inline void DuCommand(const std::string kPath, const int kLayers)
        The du command in multife.

        @param[in] kPath The path of the directory to use.
        @param[in] kLayers The amount of layers to print out with.
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
        @fn inline int ListCurrentWorkingDirectory(const int kLayers)
        Prints out the contents of the current working directory.

        @param[in] kLayers The amount of layers it is printing at. Use 0 for normal printing.
        @param[out] exit_code The exit code.
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
        @fn inline int WriteFileLine(const std::string kPath, const unsigned int kLineNumber, const std::string kContent)
        Overwrites a single line in a file.

        @param[in] kPath The path of the file to change a line in.
        @param[in] kLineNumber The line number.
        @param[in] kContent What to change the line to.
        @param[out] exit_code The exit code.
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
        @fn inline int TypeWrite(const std::string kPath, const int kLayers)
        The multife typewriter command.

        @param[in] kPath The path of the file to edit.
        @param[in] kLayers The amount of layers to print with.
        @param[out] exit_code The exit code.
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
        @file inlien int ExecuteFile(const std::string kPath)
        Tests if a file is executable, if it is, executes it using system().

        @param[in] kPath The path to the file to execute.
        @param[out] exit_code The exit code.
    */
    inline int ExecuteFile(const std::string kPath) {
        if (!access(kPath.c_str(), X_OK) && IsFile(kPath)) {
            system(("./" + kPath).c_str());
        }
        return 0;
    }

    /**
        @fn inline int ProcessCommands(std::vector<std::string> kCmds, const int kLayers)
        The function that processes user commands.

        @param[in] kCmds A vector of strings containing the commands to process.
        @param[in] kLayers The amount of layers to print at.
        @param[out] exit_code The exit code.
    */
    inline int ProcessCommands(const std::vector<std::string> kCmds, const int kLayers) {
        if (kCmds[0] == "quit") {
            exit(0);
        }

        if (kCmds[0] == "exit") {
            return 1;
        }

        // I'm doing length-checks like this so it looks nicer when I add more
        // commands.
        if (kCmds.size() > 1) {

            if (kCmds.size() > 2) {
                if (kCmds.size() > 3) {
                    if (kCmds[0] == "writel" && helper::OnlyDigits(kCmds[2])) {
                        WriteFileLine(kCmds[1], stoi(kCmds[2]), kCmds[3]);
                    }
                }

                if (kCmds[0] == "rename") {
                    std::rename((GetCurrentWorkingDirectory()  + "/" + kCmds[1]).c_str(), (GetCurrentWorkingDirectory() + "/" + kCmds[2]).c_str());
                }

                if (kCmds[0] == "move") {
                    std::rename((GetCurrentWorkingDirectory() + "/" + kCmds[1]).c_str(), (kCmds[2] + "/" + kCmds[1]).c_str());
                }
            }

            if (kCmds[0] == "cd") {
                chdir(kCmds[1].c_str());
            }

            if (kCmds[0] == "read") {
                PrintFile(kCmds[1], kLayers + 1);
            }

            if (kCmds[0] == "typewrite") {
                TypeWrite(kCmds[1], kLayers + 1);
            }

            if (kCmds[0] == "del" || kCmds[0] == "delete") {
                DeleteItem(kCmds[1], kLayers + 1, kCmds);
            }

            if (kCmds[0] == "back") {
                BackDirectory(stoi(kCmds[1]));
            }

            if (kCmds[0] == "newfile") {
                CreateFile(kCmds[1]);
            }

            if (kCmds[0] == "newdir") {
                CreateDirectory(kCmds[1]);
            }

            if (kCmds[0] == "exec" || kCmds[0] == "execute") {
                ExecuteFile(kCmds[1]);
            }
        }

        if (kCmds[0] == "ls" || kCmds[0] == "dir") {
            ListCurrentWorkingDirectory(kLayers + 1);
        }

        if (kCmds[0] == "du" || kCmds[0] == "disk") {
            DuCommand(GetCurrentWorkingDirectory(), kLayers + 1);
        }

        if (kCmds[0] == "help") {
            help::main(kLayers + 1, std::vector<std::string> ({"help", "multife"}));
        }

        return 0;
    }

    /** 
        @fn inline int MultifeCommandCycle (const int kLayers)
        The function called each time the calculator asks for a command.

        @param[in] kLayers The amount of layers to print at.
        @param[out] exit_code The exit code.
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

    /**
        @fn inline int main(const int kLayers)
        The main function for multife.

        @param[in] kLayers The amount of layers to print at.
        @param[out] exit_code The exit code.
    */
    inline int main(const int kLayers) {
        std::cout << helper::AutoIndent(kLayers - 1 ? kLayers != 0 : kLayers) << "-MULTIFE-" << '\n';
        while (true) {
            if (MultifeCommandCycle(kLayers) == 1)
                break;
        }
        std::cout << helper::AutoIndent(kLayers - 1 ? kLayers != 0 : kLayers) << "-MULTIFE-" << '\n';
        return 0;
    }
}

#endif