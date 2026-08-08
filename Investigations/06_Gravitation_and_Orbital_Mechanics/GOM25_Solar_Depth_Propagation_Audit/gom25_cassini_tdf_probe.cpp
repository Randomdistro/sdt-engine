// GOM25 D4 readiness — structural probe of frozen Cassini ATDF against PDS label.
// Does NOT produce a Shapiro residual. Does NOT decode Doppler/range observables.
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

namespace {

constexpr std::size_t kLogical = 288;
constexpr std::size_t kPhysical = 8064; // 28 * 288

[[nodiscard]] auto read_u32_be_from_bits(const std::uint8_t* rec,
                                         int start_bit_1based,
                                         int nbits) -> std::uint32_t
{
    // Bit numbering in PDS label is 1-based within the record's bit stream,
    // MSB-first. We extract by walking bits.
    std::uint32_t val = 0;
    for (int i = 0; i < nbits; ++i) {
        const int bit_index = start_bit_1based - 1 + i; // 0-based
        const int byte_i = bit_index / 8;
        const int bit_in_byte = 7 - (bit_index % 8); // MSB first within byte
        const int bit = (rec[byte_i] >> bit_in_byte) & 1;
        val = (val << 1) | static_cast<std::uint32_t>(bit);
    }
    return val;
}

// File Identification record (type 10): fields from cassini_sce1_157_tdf.lbl
// RECORD FORMAT at bits 5..36 (32 bits), RECORD TYPE at bits 41..72 (32 bits)
// within the first 9-byte MSB_BIT_STRING column — but label bit numbering is
// within that column object. Safer path used below: scan logical records for
// type word patterns documented as record type 10 / 11 / 0-padded.

struct RecSummary {
    int type_guess = -1;
    int year_mod = 0;
    int doy = 0;
    int hour = 0;
    int minute = 0;
    int second = 0;
    int scid = 0;
};

[[nodiscard]] auto probe_file_id(const std::uint8_t* rec) -> RecSummary {
    RecSummary s;
    // Per tdf_unpack.pdf Table 0 / PDS label: packed bit fields from start of record.
    // Using Markwardt/PDS description: first fields are record format + type as
    // 36-bit words with 4 spare + 32 value. Extract via bit walker on whole record.
    const auto rec_format = static_cast<int>(read_u32_be_from_bits(rec, 5, 32));
    const auto rec_type = static_cast<int>(read_u32_be_from_bits(rec, 41, 32));
    s.type_guess = rec_type;
    s.year_mod = static_cast<int>(read_u32_be_from_bits(rec, 73, 12));
    s.doy = static_cast<int>(read_u32_be_from_bits(rec, 85, 16));
    s.hour = static_cast<int>(read_u32_be_from_bits(rec, 101, 8));
    s.minute = static_cast<int>(read_u32_be_from_bits(rec, 109, 12));
    s.second = static_cast<int>(read_u32_be_from_bits(rec, 121, 8));
    s.scid = static_cast<int>(read_u32_be_from_bits(rec, 141, 16));
    (void)rec_format;
    return s;
}

} // namespace

int main(int argc, char** argv)
{
    const std::string path =
        (argc > 1) ? argv[1]
                   : "Datasets/solar_propagation_2026-08/raw/cassini_sce1_157_tdf.tdf";

    std::puts("================================================================");
    std::puts("GOM25 D4 — Cassini ATDF structural probe (no residual fit)");
    std::puts("================================================================\n");

    std::ifstream in(path, std::ios::binary);
    if (!in) {
        std::fprintf(stderr, "FAIL open %s\n", path.c_str());
        return 2;
    }
    in.seekg(0, std::ios::end);
    const auto nbytes = static_cast<std::size_t>(in.tellg());
    in.seekg(0, std::ios::beg);

    std::printf("FILE\n  path=%s\n  bytes=%zu\n", path.c_str(), nbytes);
    const bool size_ok = (nbytes % kPhysical == 0) && (nbytes % kLogical == 0);
    std::printf("  multiple of 8064-byte physical blocks: %s\n", size_ok ? "PASS" : "FAIL");
    std::printf("  logical records (288 B): %zu\n", nbytes / kLogical);
    std::printf("  physical blocks (8064 B): %zu\n\n", nbytes / kPhysical);

    if (!size_ok || nbytes < kLogical) {
        std::puts("STRUCTURAL VALIDATION FAILED");
        return 3;
    }

    std::vector<std::uint8_t> buf(nbytes);
    in.read(reinterpret_cast<char*>(buf.data()), static_cast<std::streamsize>(nbytes));

    // Count non-zero logical records and classify first few types
    std::size_t nonzero = 0;
    std::size_t zero_pad = 0;
    int type10 = 0, type11 = 0, other = 0;
    RecSummary id{};
    bool have_id = false;

    const std::size_t nrec = nbytes / kLogical;
    for (std::size_t i = 0; i < nrec; ++i) {
        const std::uint8_t* rec = buf.data() + i * kLogical;
        bool all0 = true;
        for (std::size_t b = 0; b < kLogical; ++b) {
            if (rec[b] != 0) { all0 = false; break; }
        }
        if (all0) { ++zero_pad; continue; }
        ++nonzero;
        auto s = probe_file_id(rec);
        if (s.type_guess == 10) {
            ++type10;
            if (!have_id) { id = s; have_id = true; }
        } else if (s.type_guess == 11) {
            ++type11; // transponder table type in some docs
        } else {
            ++other;
        }
    }

    std::printf("RECORD CENSUS\n");
    std::printf("  nonzero logical records: %zu\n", nonzero);
    std::printf("  zero-pad logical records: %zu\n", zero_pad);
    std::printf("  type==10 (file ID guess): %d\n", type10);
    std::printf("  type==11 (transponder guess): %d\n", type11);
    std::printf("  other type values: %d\n\n", other);

    if (have_id) {
        std::printf("FILE ID (first type-10 record, bit-extract)\n");
        std::printf("  year = 1900+%d = %d\n", id.year_mod, 1900 + id.year_mod);
        std::printf("  DOY=%d  %02d:%02d:%02d\n", id.doy, id.hour, id.minute, id.second);
        std::printf("  spacecraft ID field=%d\n", id.scid);
        // Label PRODUCT_CREATION_TIME = 2002-166T02:25:37
        const bool time_ok = (1900 + id.year_mod == 2002) && (id.doy == 166);
        std::printf("  matches label creation DOY 2002-166: %s\n\n",
                    time_ok ? "PASS" : "CHECK (bit-layout may need TRK-2-25 table)");
    } else {
        std::puts("FILE ID type-10 not found by bit guess — layout needs full TRK-2-25 table\n");
    }

    std::puts("MISSING FOR ADMISSIBLE DELAY RESIDUAL (from CORS0021 index)");
    std::puts("  - full conjunction time series of TDF/ODF (only one sample day frozen)");
    std::puts("  - SPK spacecraft/planetary ephemeris");
    std::puts("  - station coordinates + clock/EOP/ION/TRO calibrations");
    std::puts("  - PD1/PD2 path-delay products OR independent reconstruction");
    std::puts("  - validated TRK-2-25 observable extractor (Doppler/range)");
    std::puts("  - pre-registered geometry + hold-out of PPN amplitude fits");
    std::puts("\nSTATUS: PENDING_DATA — structural sample validated; residual fit blocked");
    std::puts("================================================================");
    return 0;
}
