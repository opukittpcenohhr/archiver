#include "Archiver.h"
#include "Constants.h"

#include <queue>

namespace {
    struct CmpVectors {
        bool operator()(const std::vector<bool>& a, const std::vector<bool>& b) const {
            if (a.size() != b.size()) {
                return a.size() < b.size();
            } else {
                for (size_t i = 0; i < a.size(); ++i) {
                    if (a[i] != b[i]) {
                        return a[i] < b[i];
                    }
                }
                return false;
            }
        }
    };

    struct CmpPairVectors {
        bool operator()(const std::pair<uint16_t, std::vector<bool>>& a,
                        const std::pair<uint16_t, std::vector<bool>>& b) const {
            return CmpVectors()(a.second, b.second);
        }
    };
}

void Archiver::ClearCodes() {
    std::fill(count_symbols_, count_symbols_ + (1 << SYMBOL_BIT_COUNT), 0);
    TrieRoot_ = nullptr;
    huffman_codes_.clear();
    canonical_huffman_codes_.clear();
    canonical_codes_.clear();
    canonical_codes_symbols_.clear();
}

void Archiver::PrintTechnicalInfo(Writer& writer) {
    size_t symbols_count = huffman_codes_.size();
    if (symbols_count == 0) {
        throw std::exception();
    }
    size_t max_symbol_code_size = 0;
    for (auto v : canonical_codes_) {
        max_symbol_code_size = std::max(max_symbol_code_size, v.size());
    }
    std::vector<size_t> count_code_size(max_symbol_code_size + 1);
    for (auto v : canonical_codes_) {
        count_code_size[v.size()]++;
    }
    writer.WriteBits(symbols_count, SYMBOL_BIT_COUNT);
    for (auto symbol : canonical_codes_symbols_) {
        writer.WriteBits(symbol, SYMBOL_BIT_COUNT);
    }
    for (size_t i = 1; i <= max_symbol_code_size; ++i) {
        writer.WriteBits(count_code_size[i], SYMBOL_BIT_COUNT);
    }
}

void Archiver::InitFile(const std::string& filename) {
    ClearCodes();
    ProcessSymbol(ONE_MORE_FILE);
    ProcessSymbol(FILENAME_END);
    ProcessSymbol(ARCHIVE_END);
    for (const auto& c : filename) {
        ProcessSymbol(c);
    }
    std::ifstream in(filename, std::istream::in);
    ProcessStream(in);
}

void Archiver::ArchiveFiles(const std::vector<std::string>& filenames, const std::string& resultname) {
    std::ofstream out(resultname, std::ostream::out);
    Writer writer(out);
    for (const auto& filename : filenames) {
        InitFile(filename);
        MakeTrie();
        TransformToCanonicalForm();

        PrintTechnicalInfo(writer);
        for (const auto& c : filename) {
            ArchiveSymbol(c, writer);
        }
        ArchiveSymbol(FILENAME_END, writer);
        std::ifstream in(filename, std::istream::in);
        ArchiveStream(in, writer);
        if (filename != filenames.back()) {
           ArchiveSymbol(ONE_MORE_FILE, writer);
        } else {
            ArchiveSymbol(ARCHIVE_END, writer);
        }
    }
}

Archiver::Archiver() {
    count_symbols_ = new int[1 << SYMBOL_BIT_COUNT]();
}

Archiver::~Archiver() {
    delete[] count_symbols_;
}

void Archiver::ProcessSymbol(uint16_t c) {
    count_symbols_[c]++;
}

void Archiver::ProcessStream(std::istream& in) {
    Reader reader(in);
    while (!reader.IsEof()) {
        auto new_char = reader.ReadChar();
        if (reader.IsEof()) break;
        ProcessSymbol(new_char);
    }
}

void Archiver::ArchiveSymbol(uint16_t c, Writer& writer) {
    for (auto bit : canonical_huffman_codes_[c]) {
        writer.WriteBit(bit);
    }
}

void Archiver::ArchiveStream(std::istream& in, Writer& writer) {
    Reader reader(in);
    while (!reader.IsEof()) {
        ArchiveSymbol(reader.ReadChar(), writer);
    }
}

void Archiver::IncrementVector(std::vector<bool>& cur) {
    assert(!cur.empty());
    for (size_t i = cur.size() - 1; i >= 0; --i) {
        cur[i] = !cur[i];
        if (cur[i] == 1) {
            return;
        }
    }
}

void Archiver::TransformToCanonicalForm() {
    std::vector<std::pair<uint16_t, std::vector<bool>>> code_pairs;
    for (const auto& [c, code] : huffman_codes_) {
        code_pairs.push_back(make_pair(c, code));
    }
    sort(code_pairs.begin(), code_pairs.end(), CmpPairVectors());
    std::vector<bool> current_code;
    for (size_t i = 0; i < code_pairs.size(); ++i) {
        while (current_code.size() < code_pairs[i].second.size()) {
            current_code.push_back(0);
        }
        canonical_huffman_codes_[code_pairs[i].first] = current_code;
        canonical_codes_.push_back(current_code);
        canonical_codes_symbols_.push_back(code_pairs[i].first);
        if (i + 1 < code_pairs.size()) {
            IncrementVector(current_code);
        }
    }
}

void Archiver::MakeTrie() {
    std::priority_queue<TrieNode*, std::vector<TrieNode*>, TrieNodeCmp> symbols;
    for (size_t i = 0; i < (1 << SYMBOL_BIT_COUNT); ++i) {
        if (count_symbols_[i] > 0) {
            TrieNode* tmp = new TrieNode(true, i, count_symbols_[i]);
            symbols.push(tmp);
        }
    }
    while (symbols.size() > 1) {
        auto F = symbols.top();
        symbols.pop();
        auto S = symbols.top();
        symbols.pop();
        size_t new_priority = F->priority + S->priority;
        TrieNode* new_node = new TrieNode(false, 0, new_priority, F, S);
        symbols.push(new_node);
    }
    TrieRoot_ = symbols.top();
    std::vector<bool> path;
    dfs(TrieRoot_, path, huffman_codes_);
}
