#pragma once

#include <fstream>

class Reader {
public:
    bool IsEof() const;
    uint16_t ReadChar();
    bool ReadBit();
    uint16_t ReadBits(size_t bits_count);

    Reader(std::istream& _in) : in_(_in), buffer_(0), buffer_size_(0) {
    }

private:
    std::istream& in_;
    uint16_t buffer_;
    size_t buffer_size_;
};
