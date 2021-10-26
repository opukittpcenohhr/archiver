#include "ArgumentParser.h"
#include "Reader.h"
#include "Writer.h"

#include <iostream>
#include <bitset>

using std::cerr;
using std::endl;

bool CheckArguments(const ArgumentParser &argument_parser) {
    if (argument_parser.NoArgs()) {
        std::cout << "Error: no arguments" << std::endl;
        return 0;
    }
    if (argument_parser.Contains("-h")) {
        std::cout << "Here is your help" << std::endl;
        return 0;
    }
    if (argument_parser.Contains("-c") && argument_parser.Contains("-d")) {
        std::cout << "Error: invalid arguments" << std::endl;
        return 0;
    }
    return 1;
}

int main(int argc, char** argv) {
    ArgumentParser argument_parser(argc, argv);

    // std::vector<std::string> files = argument_parser.GetFilenames();
    // std::cerr << "filenames are: " << std::endl;
    // for (auto filename : files) {
    //     std::cerr << filename << std::endl;
    // }
    // std::cerr << "inside: " << std::endl;
    // for (auto filename : files) {
    //     std::cerr << filename << std::endl;
    //     std::istream in(filename, std::istream::in);
    //     Reader reader(in);
    //     while (!reader.IsEof()) {
    //         std::cerr << reader.ReadBit();
    //     }
    //     std::cerr << std::endl;
    // }
    // cerr << "copying " << std::endl;
    // for (auto filename : files) {
    //     std::istream in(filename, std::istream::in);
    //     Reader reader(in);

    //     std::string filename_out = filename + "out";

    //     std::ostream out(filename_out, std::ostream::out);
    //     Writer writer(out);

    //     std::cerr << filename << " to " << filename_out << std::endl;

    //     while (!reader.IsEof()) {
    //         bool tmp = reader.ReadBit();
    //         // cerr << tmp;
    //         writer.WriteBit(tmp);
    //     }
    //     cerr << endl;
    //     writer.FlushBuffer();
    // }

    // std::ostream out("file_1", std::ostream::out);
    // Writer writer(out);

    // writer.WriteBit(1);
    // writer.WriteBit(0);
    // writer.WriteBit(0);
    // writer.WriteBit(1);
    // writer.WriteBit(0);
    // writer.FlushBuffer();

    // std::istream in("file_1", std::istream::in);
    // Reader reader(in);
    // cerr << reader.ReadBit() << endl;
    // cerr << reader.ReadBit() << endl;
    // cerr << reader.ReadBit() << endl;
    // cerr << reader.ReadBit() << endl;
    // cerr << reader.ReadBit() << endl;

}
