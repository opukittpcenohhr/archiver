#pragma once

#include <fstream>

class Writer {
public:
    void WriteChar(uint16_t c) const;
    void WriteBit(bool b);
    void WriteBits(uint16_t c, size_t bits_count);
    void FlushBuffer();

    Writer(std::ostream& _out) : out_(_out), buffer_(0), buffer_size_(0) {
    }

    ~Writer() {
        FlushBuffer();
    }

    int BufferSize() {
        return buffer_size_;
    }

private:
    std::ostream& out_;
    uint16_t buffer_;
    size_t buffer_size_;

    void FlipChar(unsigned char &b) const;
};
