#include "ArgumentParser.h"
#include "Archiver.h"
#include "Constants.h"
#include "UnArchiver.h"

#include <iostream>

bool CheckArguments(const ArgumentParser& argument_parser) {
    if (argument_parser.NoArgs()) {
        std::cout << "Error: no arguments\n";
        std::cout << "You can use archiver " << HELP_TOKEN << " to see help\n";
        std::cout << std::endl;
        return 0;
    }
    if (argument_parser.Contains(HELP_TOKEN)) {
        std::cout << "Usage:\n\n";
        std::cout << "archiver " << ARCHIVE_TOKEN << " archive_name file1 file2 ... -- archive file_1, file_2, ... to archive archive_name\n\n";
        std::cout << "archiver " << UNARCHIVE_TOKEN << " archive_name -- unarchive archive_name\n\n";
        std::cout << std::endl;
        return 0;
    }
    if (argument_parser.Contains(ARCHIVE_TOKEN) && argument_parser.Contains(UNARCHIVE_TOKEN)) {
        std::cout << "Error: invalid arguments" << std::endl;
        return 0;
    }
    return 1;
}

int main(int argc, char** argv) {
    ArgumentParser argument_parser(argc, argv);
    if (!CheckArguments(argument_parser)) {
        return 0;
    }
    if (argument_parser.Contains(ARCHIVE_TOKEN)) {
        std::string result_name = argument_parser.GetResultName();
        std::vector<std::string> filenames = argument_parser.GetFilenames();
        Archiver archiver;
        archiver.ArchiveFiles(filenames, result_name);
        return 0;
    }
    if (argument_parser.Contains(UNARCHIVE_TOKEN)) {
        std::string archive_name = argument_parser.GetResultName();
        UnArchiver unarc;
        unarc.UnArchiveFiles(archive_name);
        return 0;
    }
}
