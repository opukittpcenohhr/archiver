#include "UnArchiver.h"
#include "Constants.h"

void UnArchiver::IncrementVector(std::vector<bool>& cur) {
    assert(!cur.empty());
    for (size_t i = cur.size() - 1; i >= 0; --i) {
        cur[i] = !cur[i];
        if (cur[i] == 1) {
            return;
        }
        if (i == 0) {
            return;
        }
    }
}

void UnArchiver::ReadTechnicalInfo(Reader& reader) {
    canonical_codes_.clear();
    canonical_codes_symbols_.clear();
    trie_ = Trie();
    size_t symbols_count = reader.ReadBits(SYMBOL_BIT_COUNT);
    canonical_codes_symbols_.resize(symbols_count);
    for (auto& symbol : canonical_codes_symbols_) {
        symbol = reader.ReadBits(SYMBOL_BIT_COUNT);
    }
    size_t current_symbols_count = 0;
    std::vector<size_t> count_code_size = {0};
    while (current_symbols_count < symbols_count) {
        size_t current_count = reader.ReadBits(SYMBOL_BIT_COUNT);
        count_code_size.push_back(current_count);
        current_symbols_count += current_count;
    }
    size_t max_symbol_code_size = count_code_size.size() - 1;
    std::vector<bool> current_code;
    for (size_t i = 0; i <= max_symbol_code_size; ++i) {
        while (current_code.size() < i) {
            current_code.push_back(0);
        }
        for (size_t j = 0; j < count_code_size[i]; ++j) {
            canonical_codes_.push_back(current_code);
            IncrementVector(current_code);
        }
    }
    for (size_t i = 0; i < canonical_codes_.size(); ++i) {
        trie_.Add(canonical_codes_[i], canonical_codes_symbols_[i]);
    }
}

uint16_t UnArchiver::UnArchiveChar(Reader& reader) {
    std::vector<bool> current_code;
    trie_.MovePointerToRoot();
    while (!trie_.IsTerminal()) {
        bool new_bit = reader.ReadBit();
        current_code.push_back(new_bit);
        trie_.MovePointer(new_bit);
    }
    return trie_.GetCurrentChar();
}

bool UnArchiver::UnArchiveFile(Reader& reader) {
    ReadTechnicalInfo(reader);
    std::string file_name;
    while (true) {
        uint16_t new_char = UnArchiveChar(reader);
        if (new_char == FILENAME_END) {
            break;
        } else {
            file_name.push_back(static_cast<char>(new_char));
        }
    }
    std::ofstream out(file_name, std::ostream::out);
    Writer writer(out);
    while (true) {
        uint16_t new_char = UnArchiveChar(reader);
        if (new_char == ONE_MORE_FILE || new_char == ARCHIVE_END) {
            return new_char == ONE_MORE_FILE;
        } else {
            writer.WriteChar(new_char);
        }
    }
}

void UnArchiver::UnArchiveFiles(const std::string& archive_name) {
    std::ifstream in(archive_name, std::istream::in);
    Reader reader(in);
    while (true) {
        bool is_another_files = UnArchiveFile(reader);
        if (!is_another_files) {
            return;
        }
    }
}
