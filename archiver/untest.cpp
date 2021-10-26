#include "ArgumentParser.h"
#include "UnArchiver.h"

int main(int argc, char** argv) {
    ArgumentParser argument_parser(argc, argv);

    if (argument_parser.Contains("-c")) {

        return 0;
    } else {
        std::string archive_name = argument_parser.GetResultName();
        UnArchiver unarc;
        unarc.UnArchiveFiles(archive_name);
        return 0;
    }
}
