#include "Reader.h"

bool Reader::IsEof() const {
    return in_.eof();
}

uint16_t Reader::ReadChar() {
    unsigned char result;
    result = in_.get();
    return static_cast<uint16_t>(result);
}

bool Reader::ReadBit() {
    if (IsEof()) {
        throw std::runtime_error("Incorrect archive!");
    }
    if (buffer_size_ == 0) {
        buffer_ = ReadChar();
        buffer_size_ = 8;
    }
    bool result = (buffer_ & 1);
    buffer_size_--;
    buffer_ >>= 1;
    return result;
}

uint16_t Reader::ReadBits(size_t bits_count) {
    uint16_t res = 0;
    for (size_t i = 0; i < bits_count; i++) {
        if (ReadBit()) {
            res |= (1 << (bits_count - i - 1));
        }
    }
    return res;
}
