#include "Writer.h"

void Writer::WriteChar(uint16_t c) const {
    out_ << static_cast<unsigned char>(c);
}

void Writer::WriteBit(bool b) {
    if (buffer_size_ == 8) {
        FlushBuffer();
    }
    if (b) {
        buffer_ |= (1 << (buffer_size_));
    }
    buffer_size_++;
}

void Writer::WriteBits(uint16_t c, size_t bits_count) {
    for (size_t i = 0; i < bits_count; i++) {
        WriteBit((c >> (bits_count - i - 1)) & 1);
    }
}

void Writer::FlushBuffer() {
    if (buffer_size_ > 0) {
        WriteChar(buffer_);
        buffer_ = 0;
        buffer_size_ = 0;
    }
}

void Writer::FlipChar(unsigned char &b) const {
    b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
    b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
    b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
}
