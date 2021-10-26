#include "ArgumentParser.h"
#include "Constants.h"

#include <algorithm>

ArgumentParser::ArgumentParser(int argc, char** argv) {
    for (size_t i = 1; i < argc; ++i) {
        keys_.push_back(argv[i]);
    }
    for (const auto& key : keys_) {
        if (key == HELP_TOKEN || key == ARCHIVE_TOKEN || key == UNARCHIVE_TOKEN) {
            continue;
        } else {
            filenames_.push_back(key);
        }
    }
}

bool ArgumentParser::Contains(const std::string& key) const {
    return std::find(keys_.begin(), keys_.end(), key) != keys_.end();
}

bool ArgumentParser::NoArgs() const {
    return keys_.empty();
}

std::vector<std::string> ArgumentParser::GetFilenames() const {
    std::vector<std::string> result = filenames_;
    result.erase(result.begin());
    return result;
}

std::string ArgumentParser::GetResultName() const {
    return filenames_[0];
}
