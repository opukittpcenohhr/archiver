#pragma once

#include "Reader.h"
#include "Writer.h"
#include "Trie.h"

#include <map>
#include <vector>

class UnArchiver {
public:
    void UnArchiveFiles(const std::string& archive_name);

private:
    Trie trie_;

    std::vector<std::vector<bool>> canonical_codes_;
    std::vector<uint16_t> canonical_codes_symbols_;

    uint16_t UnArchiveChar(Reader &reader);
    void ReadTechnicalInfo(Reader &reader);
    bool UnArchiveFile(Reader &reader);
    void IncrementVector(std::vector<bool> &cur);
};
