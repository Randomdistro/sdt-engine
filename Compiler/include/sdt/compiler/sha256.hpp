#pragma once

/**
 * @file sha256.hpp
 * @brief Pure C++20 SHA-256 implementation for kernel hashing
 *
 * No external crypto library. Implements FIPS 180-4.
 *
 * @author SDT Theory Compiler — James Tyndall, Melbourne, Australia
 * @date May 2026
 */

#include <cstdint>
#include <cstring>
#include <string>
#include <array>
#include <vector>

namespace sdt::compiler {

class SHA256 {
public:
    static auto hash(const std::string& input) -> std::string {
        return hash(reinterpret_cast<const uint8_t*>(input.data()), input.size());
    }

    static auto hash(const uint8_t* data, size_t len) -> std::string {
        SHA256 ctx;
        ctx.update(data, len);
        return ctx.finalise();
    }

    void update(const uint8_t* data, size_t len) {
        for (size_t i = 0; i < len; ++i) {
            buf_[buf_len_++] = data[i];
            if (buf_len_ == 64) {
                process_block(buf_.data());
                total_bits_ += 512;
                buf_len_ = 0;
            }
        }
    }

    auto finalise() -> std::string {
        total_bits_ += buf_len_ * 8;

        // Padding
        buf_[buf_len_++] = 0x80;
        if (buf_len_ > 56) {
            while (buf_len_ < 64) buf_[buf_len_++] = 0;
            process_block(buf_.data());
            buf_len_ = 0;
        }
        while (buf_len_ < 56) buf_[buf_len_++] = 0;

        // Append length in bits (big-endian 64-bit)
        for (int i = 7; i >= 0; --i) {
            buf_[buf_len_++] = static_cast<uint8_t>((total_bits_ >> (i * 8)) & 0xFF);
        }
        process_block(buf_.data());

        // Convert state to hex string
        std::string result;
        result.reserve(64);
        for (int i = 0; i < 8; ++i) {
            for (int j = 28; j >= 0; j -= 4) {
                result += hex_char((state_[i] >> j) & 0xF);
            }
        }
        return result;
    }

private:
    std::array<uint32_t, 8>  state_ = {
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
        0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
    };
    std::array<uint8_t, 64>  buf_ = {};
    size_t                   buf_len_ = 0;
    uint64_t                 total_bits_ = 0;

    static constexpr std::array<uint32_t, 64> K = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
        0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
        0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
        0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
        0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
        0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
        0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
        0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
        0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
    };

    static constexpr auto rotr(uint32_t x, int n) -> uint32_t {
        return (x >> n) | (x << (32 - n));
    }

    static constexpr auto ch(uint32_t x, uint32_t y, uint32_t z) -> uint32_t {
        return (x & y) ^ (~x & z);
    }

    static constexpr auto maj(uint32_t x, uint32_t y, uint32_t z) -> uint32_t {
        return (x & y) ^ (x & z) ^ (y & z);
    }

    static constexpr auto sigma0(uint32_t x) -> uint32_t {
        return rotr(x, 2) ^ rotr(x, 13) ^ rotr(x, 22);
    }

    static constexpr auto sigma1(uint32_t x) -> uint32_t {
        return rotr(x, 6) ^ rotr(x, 11) ^ rotr(x, 25);
    }

    static constexpr auto gamma0(uint32_t x) -> uint32_t {
        return rotr(x, 7) ^ rotr(x, 18) ^ (x >> 3);
    }

    static constexpr auto gamma1(uint32_t x) -> uint32_t {
        return rotr(x, 17) ^ rotr(x, 19) ^ (x >> 10);
    }

    void process_block(const uint8_t* block) {
        std::array<uint32_t, 64> w;

        for (int i = 0; i < 16; ++i) {
            w[i] = (uint32_t(block[i * 4]) << 24) |
                   (uint32_t(block[i * 4 + 1]) << 16) |
                   (uint32_t(block[i * 4 + 2]) << 8) |
                   uint32_t(block[i * 4 + 3]);
        }
        for (int i = 16; i < 64; ++i) {
            w[i] = gamma1(w[i - 2]) + w[i - 7] + gamma0(w[i - 15]) + w[i - 16];
        }

        uint32_t a = state_[0], b = state_[1], c = state_[2], d = state_[3];
        uint32_t e = state_[4], f = state_[5], g = state_[6], h = state_[7];

        for (int i = 0; i < 64; ++i) {
            uint32_t t1 = h + sigma1(e) + ch(e, f, g) + K[i] + w[i];
            uint32_t t2 = sigma0(a) + maj(a, b, c);
            h = g; g = f; f = e; e = d + t1;
            d = c; c = b; b = a; a = t1 + t2;
        }

        state_[0] += a; state_[1] += b; state_[2] += c; state_[3] += d;
        state_[4] += e; state_[5] += f; state_[6] += g; state_[7] += h;
    }

    static auto hex_char(uint32_t v) -> char {
        return v < 10 ? static_cast<char>('0' + v) : static_cast<char>('a' + v - 10);
    }
};

} // namespace sdt::compiler
