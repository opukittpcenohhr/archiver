#pragma once

#include "Reader.h"
#include "Writer.h"
#include "TrieNode.h"

#include <vector>

class Archiver {
public:
    void ArchiveFiles(const std::vector<std::string>& filenames, const std::string& resultname);

    Archiver();
    ~Archiver();

private:
    int* count_symbols_;
    TrieNode* TrieRoot_;
    std::map<uint16_t, std::vector<bool>> huffman_codes_;
    std::map<uint16_t, std::vector<bool>> canonical_huffman_codes_;

    std::vector<std::vector<bool> > canonical_codes_;
    std::vector<uint16_t> canonical_codes_symbols_;

    void ClearCodes();

    void InitFile(const std::string& filename);

    void ProcessSymbol(uint16_t c);
    void ProcessStream(std::istream& in);

    void ArchiveSymbol(uint16_t c, Writer& writer);
    void ArchiveStream(std::istream& in, Writer& writer);

    void MakeTrie();
    void TransformToCanonicalForm();
    void PrintTechnicalInfo(Writer& writer);

    void IncrementVector(std::vector<bool> &cur);
};
