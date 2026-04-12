#pragma once
// ═══════════════════════════════════════════════════════════════════════
// CRUMPILER — Bitstream Reader/Writer
// ═══════════════════════════════════════════════════════════════════════
// Variable-width bit-level I/O for frequency-ranked token encoding.
// Rank 1 → "1" (1 bit), Rank 2 → "10" (2 bits), Rank 3 → "11", etc.
// Self-delimiting via Elias gamma coding: unary length prefix + payload.
// ═══════════════════════════════════════════════════════════════════════

#include <cstdint>
#include <cstring>
#include <vector>

namespace crumpiler {

// ── Elias Gamma Encoding ───────────────────────────────────────────────
// Encodes rank N (1-based) as:
//   1. Number of bits in binary(N) minus 1, written as that many 0s
//   2. Then binary(N) itself
//
// Rank 1 →  1          (1 bit)
// Rank 2 →  010        (3 bits)
// Rank 3 →  011        (3 bits)
// Rank 4 →  00100      (5 bits)
// Rank 5 →  00101      (5 bits)
// Rank 6 →  00110      (5 bits)
// Rank 7 →  00111      (5 bits)
// Rank 8 →  0001000    (7 bits)
//
// Prefix-free. Self-delimiting. No ambiguity.
// Higher ranks cost more bits — exactly what we want.

[[nodiscard]] constexpr auto gamma_bit_cost(uint32_t rank) noexcept -> uint8_t {
    if (rank == 0) return 0;
    uint8_t bits = 0;
    uint32_t v = rank;
    while (v > 0) { ++bits; v >>= 1; }
    // Elias gamma: (bits - 1) zeros + bits data = 2*bits - 1
    return static_cast<uint8_t>(2 * bits - 1);
}

// ── BitWriter ──────────────────────────────────────────────────────────
// Packs bits into a byte buffer, MSB-first.
class BitWriter {
public:
    BitWriter() { buffer_.reserve(4096); }

    void write_bit(bool bit) noexcept {
        if (bit_pos_ == 0) {
            buffer_.push_back(0);
        }
        if (bit) {
            buffer_.back() |= (0x80u >> bit_pos_);
        }
        bit_pos_ = (bit_pos_ + 1) & 7;
        ++total_bits_;
    }

    void write_bits(uint64_t value, uint8_t count) noexcept {
        for (int i = count - 1; i >= 0; --i) {
            write_bit((value >> i) & 1);
        }
    }

    // Write a frequency rank using Elias gamma coding.
    void write_gamma(uint32_t rank) noexcept {
        if (rank == 0) return;

        // Count bits in binary representation
        uint8_t bits = 0;
        uint32_t v = rank;
        while (v > 0) { ++bits; v >>= 1; }

        // Write (bits - 1) zeros as length prefix
        for (uint8_t i = 0; i < bits - 1; ++i) {
            write_bit(false);
        }

        // Write the binary value itself (bits wide)
        write_bits(rank, bits);
    }

    // Write raw bytes (for headers, etc.)
    void write_bytes(const void* data, size_t count) noexcept {
        flush_byte();
        auto* bytes = static_cast<const uint8_t*>(data);
        for (size_t i = 0; i < count; ++i) {
            buffer_.push_back(bytes[i]);
        }
        total_bits_ += count * 8;
    }

    void write_u8(uint8_t v) noexcept { write_bytes(&v, 1); }
    void write_u16(uint16_t v) noexcept { write_bytes(&v, 2); }
    void write_u32(uint32_t v) noexcept { write_bytes(&v, 4); }
    void write_u64(uint64_t v) noexcept { write_bytes(&v, 8); }

    void flush_byte() noexcept {
        if (bit_pos_ != 0) {
            bit_pos_ = 0;
        }
    }

    [[nodiscard]] auto data() const noexcept -> const uint8_t* { return buffer_.data(); }
    [[nodiscard]] auto size() const noexcept -> size_t { return buffer_.size(); }
    [[nodiscard]] auto total_bits() const noexcept -> uint64_t { return total_bits_; }
    [[nodiscard]] auto raw_buffer() noexcept -> std::vector<uint8_t>& { return buffer_; }

private:
    std::vector<uint8_t> buffer_;
    uint8_t bit_pos_   = 0;      // Next bit position within current byte (0-7)
    uint64_t total_bits_ = 0;
};

// ── BitReader ──────────────────────────────────────────────────────────
// Unpacks bits from a byte buffer, MSB-first.
class BitReader {
public:
    BitReader(const uint8_t* data, size_t size) noexcept
        : data_(data), size_(size) {}

    [[nodiscard]] bool read_bit() noexcept {
        if (byte_pos_ >= size_) return false;
        bool bit = (data_[byte_pos_] >> (7 - bit_pos_)) & 1;
        bit_pos_ = (bit_pos_ + 1) & 7;
        if (bit_pos_ == 0) ++byte_pos_;
        ++total_bits_read_;
        return bit;
    }

    [[nodiscard]] uint64_t read_bits(uint8_t count) noexcept {
        uint64_t value = 0;
        for (uint8_t i = 0; i < count; ++i) {
            value = (value << 1) | (read_bit() ? 1 : 0);
        }
        return value;
    }

    // Read an Elias gamma-coded rank.
    [[nodiscard]] uint32_t read_gamma() noexcept {
        // Count leading zeros to determine bit width
        uint8_t zeros = 0;
        while (!read_bit()) {
            ++zeros;
            if (zeros > 31) return 0; // safety
        }
        // We've consumed the leading '1'. Read remaining 'zeros' bits.
        uint32_t value = 1;
        for (uint8_t i = 0; i < zeros; ++i) {
            value = (value << 1) | (read_bit() ? 1 : 0);
        }
        return value;
    }

    void read_bytes(void* out, size_t count) noexcept {
        align_byte();
        auto* bytes = static_cast<uint8_t*>(out);
        for (size_t i = 0; i < count && byte_pos_ < size_; ++i) {
            bytes[i] = data_[byte_pos_++];
        }
        total_bits_read_ += count * 8;
    }

    [[nodiscard]] uint8_t  read_u8()  noexcept { uint8_t  v = 0; read_bytes(&v, 1); return v; }
    [[nodiscard]] uint16_t read_u16() noexcept { uint16_t v = 0; read_bytes(&v, 2); return v; }
    [[nodiscard]] uint32_t read_u32() noexcept { uint32_t v = 0; read_bytes(&v, 4); return v; }
    [[nodiscard]] uint64_t read_u64() noexcept { uint64_t v = 0; read_bytes(&v, 8); return v; }

    void align_byte() noexcept {
        if (bit_pos_ != 0) {
            bit_pos_ = 0;
            ++byte_pos_;
        }
    }

    [[nodiscard]] bool eof() const noexcept { return byte_pos_ >= size_; }
    [[nodiscard]] auto total_bits_read() const noexcept -> uint64_t { return total_bits_read_; }

private:
    const uint8_t* data_;
    size_t size_;
    size_t byte_pos_     = 0;
    uint8_t bit_pos_     = 0;
    uint64_t total_bits_read_ = 0;
};

} // namespace crumpiler
