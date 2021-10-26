#pragma once

#include <vector>
#include <string>

class ArgumentParser {
public:
    ArgumentParser(int argc, char** argv);
    bool Contains(const std::string& key) const;
    bool NoArgs() const;
    std::vector<std::string> GetFilenames() const;
    std::string GetResultName() const;

private:
    std::vector<std::string> keys_;
    std::vector<std::string> filenames_;
};
