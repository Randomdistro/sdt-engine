// ═══════════════════════════════════════════════════════════════════════
// CRUMPILER — CLI
// ═══════════════════════════════════════════════════════════════════════
// crumpiler encode   <source> -o <output.crm> -k <output.crk>
// crumpiler decode   <input.crm> -k <input.crk> -o <output.cpp>
// crumpiler crumple  <anyfile> [-o <output.crb>] [-p <max_passes>]
// crumpiler uncrumple <input.crb> -o <output> -p <passes_used>
// crumpiler stats    <source>
// ═══════════════════════════════════════════════════════════════════════

#include "encoder/encoder.hpp"
#include "encoder/binary_crumpler.hpp"
#include "encoder/image_crumpler.hpp"
#include "encoder/spiral_scanner.hpp"
#include "decoder/decoder.hpp"
#include "core/rings.hpp"
#include <cstdio>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

static auto read_file(const std::string& path) -> std::string {
    std::ifstream in(path, std::ios::binary | std::ios::ate);
    if (!in.is_open()) return "";
    auto size = in.tellg();
    in.seekg(0);
    std::string content(static_cast<size_t>(size), '\0');
    in.read(content.data(), size);
    return content;
}

static void print_banner() {
    std::printf("\n");
    std::printf("  ╔═══════════════════════════════════════════════╗\n");
    std::printf("  ║           CRUMPILER v0.1.0                    ║\n");
    std::printf("  ║     Frequency-Ranked Source Compression       ║\n");
    std::printf("  ╚═══════════════════════════════════════════════╝\n");
    std::printf("\n");
}

static void print_usage() {
    print_banner();
    std::printf("  Usage:\n");
    std::printf("    crumpiler encode <source> -o <output.crm> -k <output.crk>\n");
    std::printf("    crumpiler decode <input.crm> -k <input.crk> -o <output>\n");
    std::printf("    crumpiler stats  <source>\n");
    std::printf("\n");
    std::printf("  Universal ring tokens: %u (sub-10 bits)\n",
        crumpiler::rings::TOTAL_RING_TOKENS);
    std::printf("  Rings defined: %u\n",
        static_cast<unsigned>(crumpiler::rings::RING_COUNT));
    std::printf("\n");
}

static auto find_arg(int argc, char** argv, const char* flag) -> const char* {
    for (int i = 0; i < argc - 1; ++i) {
        if (std::strcmp(argv[i], flag) == 0) return argv[i + 1];
    }
    return nullptr;
}

static int cmd_encode(int argc, char** argv) {
    if (argc < 3) {
        std::printf("  Error: no source file specified.\n");
        return 1;
    }

    std::string source_path = argv[2];
    std::string crm_path = find_arg(argc, argv, "-o") ? find_arg(argc, argv, "-o")
        : (source_path + ".crm");
    std::string crk_path = find_arg(argc, argv, "-k") ? find_arg(argc, argv, "-k")
        : (source_path + ".crk");

    std::printf("  Encoding: %s\n", source_path.c_str());

    auto source = read_file(source_path);
    if (source.empty()) {
        std::printf("  Error: could not read source file.\n");
        return 1;
    }

    crumpiler::Encoder encoder;
    auto result = encoder.encode(source, crm_path, crk_path);

    std::printf("\n  ── Results ────────────────────────────────────\n");
    std::printf("  Original:          %10llu bytes\n", result.original_bytes);
    std::printf("  .crm (bitstream):  %10llu bytes\n", result.crm_bytes);
    std::printf("  .crk (legend):     %10llu bytes\n", result.crk_bytes);
    std::printf("  Total crumpled:    %10llu bytes\n", result.crm_bytes + result.crk_bytes);
    std::printf("  Compression:       %10.1f%% of original\n", result.compression_ratio);
    std::printf("  ──────────────────────────────────────────────\n");
    std::printf("  Tokens (raw):      %10llu total\n", result.total_tokens);
    std::printf("  Tokens (stream):   %10llu (after phrase collapse)\n", result.stream_tokens);
    std::printf("  Unique:            %10llu\n", result.unique_tokens);
    std::printf("  Ring tokens:       %10llu (%.1f%%)\n",
        result.ring_token_count,
        result.total_tokens > 0
            ? (static_cast<double>(result.ring_token_count) / result.total_tokens * 100.0) : 0);
    std::printf("  [ Local idents:    %10u unique\n", result.local_ident_count);
    std::printf("  Identifiers:       %10llu references\n", result.ident_count);
    std::printf("  Literals:          %10llu\n", result.literal_count);
    std::printf("  Phrases:           %10llu found, %llu replacements\n",
        result.phrase_count, result.phrase_replacements);
    std::printf("\n  Output: %s\n", crm_path.c_str());
    std::printf("  Legend: %s\n", crk_path.c_str());
    std::printf("\n");

    return 0;
}

static int cmd_decode(int argc, char** argv) {
    if (argc < 3) {
        std::printf("  Error: no .crm file specified.\n");
        return 1;
    }

    std::string crm_path = argv[2];
    const char* k = find_arg(argc, argv, "-k");
    std::string crk_path = k ? k : (crm_path.substr(0, crm_path.rfind('.')) + ".crk");
    const char* o = find_arg(argc, argv, "-o");
    std::string out_path = o ? o : (crm_path + ".decoded");

    std::printf("  Decoding: %s\n", crm_path.c_str());
    std::printf("  Legend:   %s\n", crk_path.c_str());

    crumpiler::Decoder decoder;
    if (!decoder.load_key(crk_path)) {
        std::printf("  Error: could not load legend file.\n");
        return 1;
    }

    auto result = decoder.decode(crm_path);
    if (result.empty()) {
        std::printf("  Error: decoding failed.\n");
        return 1;
    }

    std::ofstream out(out_path, std::ios::binary);
    out.write(result.c_str(), result.size());

    std::printf("  Output: %s (%zu bytes)\n\n", out_path.c_str(), result.size());
    return 0;
}

static int cmd_stats(int argc, char** argv) {
    if (argc < 3) {
        std::printf("  Error: no source file specified.\n");
        return 1;
    }

    std::string source_path = argv[2];
    auto source = read_file(source_path);
    if (source.empty()) {
        std::printf("  Error: could not read source file.\n");
        return 1;
    }

    std::printf("  Analyzing: %s (%zu bytes)\n\n", source_path.c_str(), source.size());

    crumpiler::Lexer lexer;
    auto tokens = lexer.tokenize(source);

    uint64_t ring_count = 0, ident_count = 0, literal_count = 0;
    crumpiler::FrequencyTable freq;

    for (auto const& tok : tokens) {
        if (tok.channel == crumpiler::Channel::Ring) {
            ring_count++;
            freq.record(crumpiler::Channel::Ring,
                crumpiler::ring_global_id(tok.ring_id, tok.ring_pos));
        } else if (tok.channel == crumpiler::Channel::Ident) {
            ident_count++;
            // Use simple hash for stats
            uint32_t hash = 0;
            for (char c : tok.text) hash = hash * 31 + c;
            freq.record(crumpiler::Channel::Ident, hash);
        } else {
            literal_count++;
            freq.record(crumpiler::Channel::Literal, 0);
        }
    }

    freq.finalize();

    std::printf("  ── Token Analysis ─────────────────────────────\n");
    std::printf("  Total tokens:      %10zu\n", tokens.size());
    std::printf("  Unique tokens:     %10zu\n", freq.size());
    std::printf("  Repetition ratio:  %10.1fx\n",
        freq.size() > 0 ? static_cast<double>(tokens.size()) / freq.size() : 0);
    std::printf("  Ring tokens:       %10llu  (%.1f%%)\n",
        ring_count, tokens.size() > 0
            ? static_cast<double>(ring_count) / tokens.size() * 100.0 : 0);
    std::printf("  Identifiers:       %10llu  (%.1f%%)\n",
        ident_count, tokens.size() > 0
            ? static_cast<double>(ident_count) / tokens.size() * 100.0 : 0);
    std::printf("  Literals:          %10llu  (%.1f%%)\n",
        literal_count, tokens.size() > 0
            ? static_cast<double>(literal_count) / tokens.size() * 100.0 : 0);
    std::printf("  ──────────────────────────────────────────────\n");
    std::printf("  Freq-ranked bits:  %10llu bits (%.1f KB)\n",
        freq.total_bits(), freq.total_bits() / 8.0 / 1024.0);
    std::printf("  Original size:     %10zu bytes (%.1f KB)\n",
        source.size(), source.size() / 1024.0);
    std::printf("  Estimated ratio:   %10.1f%% of original\n",
        source.size() > 0
            ? (freq.total_bits() / 8.0) / source.size() * 100.0 : 0);
    std::printf("\n");

    // Show ring usage
    std::printf("  ── Ring Usage ─────────────────────────────────\n");
    std::printf("  Universal rings: %u   Total ring tokens: %u\n",
        static_cast<unsigned>(crumpiler::rings::RING_COUNT),
        crumpiler::rings::TOTAL_RING_TOKENS);
    std::printf("\n");

    // Top 20 tokens by frequency
    std::printf("  ── Top 20 Tokens (by frequency rank) ─────────\n");
    auto const& entries = freq.entries();
    for (uint32_t i = 0; i < std::min(static_cast<size_t>(20), entries.size()); ++i) {
        auto const& e = entries[i];
        std::printf("    Rank %2u  %7u×  %2u bits  ", i + 1, e.count, e.bit_cost);

        if (e.key.channel == crumpiler::Channel::Ring) {
            uint16_t rid = static_cast<uint16_t>(e.key.id / crumpiler::MAX_RING_SIZE);
            uint16_t rpos = static_cast<uint16_t>(e.key.id % crumpiler::MAX_RING_SIZE);
            if (rid < crumpiler::rings::RING_COUNT &&
                rpos < crumpiler::rings::RING_TABLE[rid].token_count) {
                std::printf("[%s] %s",
                    crumpiler::rings::RING_TABLE[rid].name,
                    crumpiler::rings::RING_TABLE[rid].tokens[rpos]);
            }
        } else if (e.key.channel == crumpiler::Channel::Ident) {
            std::printf("[IDENT] #%u", e.key.id);
        } else {
            std::printf("[LITERAL]");
        }
        std::printf("\n");
    }
    std::printf("\n");

    return 0;
}

static int cmd_crumple(int argc, char** argv) {
    if (argc < 3) {
        std::printf("  Error: no input file specified.\n");
        return 1;
    }

    std::string input_path = argv[2];
    const char* o = find_arg(argc, argv, "-o");
    std::string out_path = o ? o : (input_path + ".crb");
    const char* p = find_arg(argc, argv, "-p");
    uint32_t max_passes = p ? static_cast<uint32_t>(std::atoi(p)) : 5;

    std::printf("  Crumpling (binary): %s\n", input_path.c_str());
    std::printf("  Max passes: %u\n\n", max_passes);

    // Read entire file
    std::ifstream in(input_path, std::ios::binary | std::ios::ate);
    if (!in.is_open()) {
        std::printf("  Error: could not read file.\n");
        return 1;
    }
    size_t file_size = in.tellg();
    in.seekg(0);
    std::vector<uint8_t> data(file_size);
    in.read(reinterpret_cast<char*>(data.data()), file_size);
    in.close();

    crumpiler::BinaryCrumpler bc;
    std::vector<uint8_t> output;
    auto passes = bc.crumple_recursive(data.data(), data.size(),
                                       output, max_passes);

    std::printf("  ── Binary Crumple Results ──────────────────────\n");
    for (auto const& pass : passes) {
        std::printf("  binary^%u:  %10llu → %10llu bytes  (%.1f%%)  "
                    "phrases: %u\n",
            pass.pass_number,
            static_cast<unsigned long long>(pass.input_bytes),
            static_cast<unsigned long long>(pass.output_bytes),
            pass.ratio, pass.phrases_found);
    }
    std::printf("  ──────────────────────────────────────────────\n");
    std::printf("  Original:   %10zu bytes\n", file_size);
    std::printf("  Crumpled:   %10zu bytes\n", output.size());
    std::printf("  Ratio:      %10.1f%%\n",
        file_size > 0
        ? static_cast<double>(output.size()) / file_size * 100.0 : 0);
    std::printf("  Passes:     %10zu\n", passes.size());

    // Write output
    // Prepend a recursive header: pass count so uncrumple knows how many layers
    {
        std::ofstream out_f(out_path, std::ios::binary);
        uint32_t magic = crumpiler::CRBR_MAGIC;
        uint32_t pass_count = static_cast<uint32_t>(passes.size());
        out_f.write(reinterpret_cast<const char*>(&magic), 4);
        out_f.write(reinterpret_cast<const char*>(&pass_count), 4);
        out_f.write(reinterpret_cast<const char*>(output.data()), output.size());
    }

    std::printf("\n  Output: %s\n\n", out_path.c_str());
    return 0;
}

static int cmd_uncrumple(int argc, char** argv) {
    if (argc < 3) {
        std::printf("  Error: no .crb file specified.\n");
        return 1;
    }

    std::string input_path = argv[2];
    const char* o = find_arg(argc, argv, "-o");
    std::string out_path = o ? o : (input_path + ".restored");

    std::printf("  Uncrumpling: %s\n", input_path.c_str());

    std::ifstream in(input_path, std::ios::binary | std::ios::ate);
    if (!in.is_open()) {
        std::printf("  Error: could not read file.\n");
        return 1;
    }
    size_t file_size = in.tellg();
    in.seekg(0);
    std::vector<uint8_t> data(file_size);
    in.read(reinterpret_cast<char*>(data.data()), file_size);
    in.close();

    // Read recursive header
    if (file_size < 8) {
        std::printf("  Error: file too small.\n");
        return 1;
    }
    uint32_t magic = 0;
    std::memcpy(&magic, data.data(), 4);
    if (magic != crumpiler::CRBR_MAGIC) {
        std::printf("  Error: not a .crb file.\n");
        return 1;
    }
    uint32_t pass_count = 0;
    std::memcpy(&pass_count, data.data() + 4, 4);

    std::printf("  Passes to undo: %u\n", pass_count);

    crumpiler::BinaryCrumpler bc;
    std::vector<uint8_t> output;
    bool ok = bc.decrumple_recursive(
        data.data() + 8, file_size - 8,
        output, pass_count);

    if (!ok) {
        std::printf("  Error: decrumple failed.\n");
        return 1;
    }

    std::ofstream out_f(out_path, std::ios::binary);
    out_f.write(reinterpret_cast<const char*>(output.data()), output.size());

    std::printf("  Restored: %s (%zu bytes)\n\n", out_path.c_str(), output.size());
    return 0;
}

static int cmd_crumple_image(int argc, char** argv) {
    if (argc < 3) {
        std::printf("  Error: no BMP file specified.\n");
        return 1;
    }

    std::string input_path = argv[2];
    const char* o = find_arg(argc, argv, "-o");
    std::string out_path = o ? o : (input_path + ".crmpg");
    const char* t = find_arg(argc, argv, "-t");
    uint8_t tolerance = t ? static_cast<uint8_t>(std::atoi(t)) : 8;

    std::printf("  Crumpling image: %s\n", input_path.c_str());
    std::printf("  Tolerance: +/-%u per channel (fuzzy match)\n", tolerance);

    uint32_t width = 0, height = 0;
    auto pixels = crumpiler::ImageCrumpler::load_bmp(input_path, width, height);
    if (pixels.empty()) {
        std::printf("  Error: could not load BMP (24-bit uncompressed only).\n");
        return 1;
    }

    std::printf("  Dimensions: %ux%u (%zu bytes raw RGB)\n\n",
        width, height, pixels.size());

    crumpiler::ImageCrumpler ic;
    std::vector<uint8_t> output;
    auto result = ic.crumple(pixels.data(), width, height, 3, tolerance, output);

    std::printf("  -- Image Crossword Results --\n");
    std::printf("  Pixels:         %10llu\n",
        static_cast<unsigned long long>(result.pixel_count));
    std::printf("  Scans (px*8):   %10u\n", result.total_scans);
    std::printf("  Phrases found:  %10u\n", result.phrases_found);
    std::printf("  Replacements:   %10u\n", result.replacements);
    std::printf("  Covered:        %10u pixels (%.1f%%)\n",
        result.pixels_covered,
        result.pixel_count > 0
            ? static_cast<double>(result.pixels_covered) / result.pixel_count * 100.0 : 0);
    std::printf("  Uncovered:      %10u pixels\n", result.pixels_uncovered);
    std::printf("  ------------------------------\n");
    std::printf("  Input (raw):    %10llu bytes\n",
        static_cast<unsigned long long>(result.input_bytes));
    std::printf("  Output:         %10llu bytes\n",
        static_cast<unsigned long long>(result.output_bytes));
    std::printf("  Ratio:          %10.1f%%\n", result.ratio);

    {
        std::ofstream out_f(out_path, std::ios::binary);
        out_f.write(reinterpret_cast<const char*>(output.data()), output.size());
    }

    std::printf("\n  Output: %s\n\n", out_path.c_str());
    return 0;
}

static int cmd_spiral_scan(int argc, char** argv) {
    if (argc < 3) {
        std::printf("  Error: no BMP file specified.\n");
        return 1;
    }

    std::string input_path = argv[2];
    const char* t = find_arg(argc, argv, "-t");
    uint8_t tolerance = t ? static_cast<uint8_t>(std::atoi(t)) : 0;

    std::printf("  Torah Column Spiral Scan: %s\n", input_path.c_str());
    std::printf("  Tolerance: +/-%u per channel\n", tolerance);

    uint32_t img_w = 0, img_h = 0;
    auto pixels = crumpiler::ImageCrumpler::load_bmp(input_path, img_w, img_h);
    if (pixels.empty()) {
        std::printf("  Error: could not load BMP.\n");
        return 1;
    }

    uint32_t total_pixels = img_w * img_h;
    uint64_t raw_size = static_cast<uint64_t>(total_pixels) * 3;
    std::printf("  Image: %ux%u = %u pixels (%llu bytes)\n",
        img_w, img_h, total_pixels,
        static_cast<unsigned long long>(raw_size));
    std::printf("  Testing EVERY width from 2 to %u...\n\n", total_pixels / 2);

    crumpiler::SpiralScanner ss;
    auto hits = ss.scan_all_widths(pixels.data(), total_pixels, 3,
        tolerance, 0.5, true);

    std::printf("\n  -- Results: %zu widths with >50%% column match --\n\n",
        hits.size());

    // Show top 20 hits
    uint32_t show = std::min(static_cast<uint32_t>(hits.size()), 20u);
    for (uint32_t i = 0; i < show; ++i) {
        auto const& h = hits[i];
        int offset = static_cast<int>(h.width) - static_cast<int>(img_w);
        const char* interp = "";
        if (h.width == img_w) interp = " [= image width, vertical]";
        else if (std::abs(offset) <= 5) interp = " [near image width, diagonal]";
        else if (h.width < img_w) interp = " [sub-tile]";

        auto est = ss.estimate_size(h, 3, tolerance, total_pixels);
        double ratio = raw_size > 0
            ? static_cast<double>(est) / raw_size * 100.0 : 100.0;

        std::printf("  #%2u  w=%-6u  %u/%u cols (%.0f%%)  %u rows  score=%.1f  est=%.1f%%%s\n",
            i + 1, h.width, h.matching_cols, h.width,
            h.match_rate * 100.0, h.rows, h.score,
            ratio, interp);
    }

    // Encode the best hit
    if (!hits.empty()) {
        auto const& best = hits[0];
        auto est = ss.estimate_size(best, 3, tolerance, total_pixels);

        std::printf("\n  -- Best Width --\n");
        std::printf("  Width:          %u\n", best.width);
        std::printf("  Rows:           %u\n", best.rows);
        std::printf("  Match rate:     %.1f%%\n", best.match_rate * 100.0);
        std::printf("  Estimated:      %llu bytes (%.1f%% of raw)\n",
            static_cast<unsigned long long>(est),
            raw_size > 0 ? static_cast<double>(est) / raw_size * 100.0 : 100.0);

        if (est < raw_size) {
            auto enc = ss.encode(pixels.data(), total_pixels, 3, tolerance, best);
            auto blob = ss.serialize(enc);
            std::string out_path = input_path + ".sprl";
            std::ofstream out_f(out_path, std::ios::binary);
            out_f.write(reinterpret_cast<const char*>(blob.data()), blob.size());
            std::printf("  Actual output:  %zu bytes (%.1f%%)\n",
                blob.size(),
                raw_size > 0 ? static_cast<double>(blob.size()) / raw_size * 100.0 : 100.0);
            std::printf("\n  Output: %s\n", out_path.c_str());
        } else {
            std::printf("  Not profitable.\n");
        }
    } else {
        std::printf("\n  No periodic structure found at any width.\n");
    }

    return 0;
}

int main(int argc, char** argv) {
    print_banner();

    if (argc < 2) {
        print_usage();
        return 0;
    }

    std::string cmd = argv[1];

    if (cmd == "encode")         return cmd_encode(argc, argv);
    if (cmd == "decode")         return cmd_decode(argc, argv);
    if (cmd == "crumple")        return cmd_crumple(argc, argv);
    if (cmd == "uncrumple")      return cmd_uncrumple(argc, argv);
    if (cmd == "crumple-image")  return cmd_crumple_image(argc, argv);
    if (cmd == "spiral-scan")    return cmd_spiral_scan(argc, argv);
    if (cmd == "stats")          return cmd_stats(argc, argv);

    std::printf("  Unknown command: %s\n", cmd.c_str());
    print_usage();
    return 1;
}
