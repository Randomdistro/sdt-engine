// GOM_DAT2 fresh one-file decode (2026-10-12). Registration: GOM_DAT2_RESET_ASSESSMENT_2026-10-12.md sections 0-2 (written before this file existed).
// Author: J. C. Harvey, Melbourne.
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iterator>
#include <map>
#include <vector>
static uint32_t be32(const uint8_t* p) { return (uint32_t(p[0]) << 24) | (uint32_t(p[1]) << 16) | (uint32_t(p[2]) << 8) | p[3]; }
static uint64_t bits(const uint8_t* p, int start1, int n) { uint64_t v = 0; for (int i = 0; i < n; ++i) { int b = start1 - 1 + i; v = (v << 1) | ((p[b / 8] >> (7 - b % 8)) & 1); } return v; }
struct F { int fmt, rx, tx, type, valid; double t; };
static F decode(const uint8_t* p) { const uint8_t* q = p + 16; F f; f.t = double(be32(p)) + double(bits(p + 4, 1, 10)) / 1000.0; f.fmt = int(bits(q, 1, 3)); f.rx = int(bits(q, 4, 7)); f.tx = int(bits(q, 11, 7)); f.type = int(bits(q, 20, 6)); f.valid = int(bits(q, 32, 1)); return f; }
static void setbits(uint8_t* r, int byte0, int start1, int n, uint64_t v) { for (int i = 0; i < n; ++i) { int b = byte0 * 8 + start1 - 1 + i; int bit = int((v >> (n - 1 - i)) & 1); if (bit) r[b / 8] |= uint8_t(0x80 >> (b % 8)); } }
int main() {
    std::printf("GOM_DAT2 fresh one-file decode (registered in GOM_DAT2_RESET_ASSESSMENT_2026-10-12.md)\n=======================================================================\n\n");
    int fails = 0;
    { uint8_t r[36] = {0}; uint32_t sec = 1654548090u; r[0] = uint8_t(sec >> 24); r[1] = uint8_t(sec >> 16); r[2] = uint8_t(sec >> 8); r[3] = uint8_t(sec);
      setbits(r, 4, 1, 10, 500); setbits(r, 16, 1, 3, 2); setbits(r, 16, 4, 7, 25); setbits(r, 16, 11, 7, 25); setbits(r, 16, 20, 6, 12);
      F f = decode(r); bool ok = f.fmt == 2 && f.rx == 25 && f.tx == 25 && f.type == 12 && f.valid == 0 && f.t == 1654548090.5; std::printf("[VA] synthetic record round trip: format %d, rx %d, tx %d, type %d, time %.3f -> %s\n", f.fmt, f.rx, f.tx, f.type, f.t, ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    std::ifstream fi("Datasets/solar_propagation_2026-08/raw/cassini_sce1_157_odf.odf", std::ios::binary); std::vector<uint8_t> b((std::istreambuf_iterator<char>(fi)), std::istreambuf_iterator<char>());
    { int k5 = (int32_t)be32(b.data() + 36 * 4), k7453 = (int32_t)be32(b.data() + 36 * 7452); bool ok = k5 == 109 && k7453 == 2030; std::printf("[VB] record 5 key %d (expected 109), record 7453 key %d (the next header, 2030) -> %s\n", k5, k7453, ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    if (fails) { std::printf("VALIDATIONS NOT MET\n"); return 1; }
    std::map<int, int> hf, ht, hv; std::map<std::pair<int, int>, int> hs; double tmin = 1e30, tmax = -1e30; int nonmono = 0; double prev = 0; int rows = 0;
    for (int r = 6; r <= 7452; ++r) { F f = decode(b.data() + 36 * (r - 1)); ++rows; ++hf[f.fmt]; ++ht[f.type]; ++hv[f.valid]; ++hs[{f.rx, f.tx}]; if (f.t < tmin) tmin = f.t; if (f.t > tmax) tmax = f.t; if (f.t < prev) ++nonmono; prev = f.t; }
    std::printf("rows decoded: %d\nFORMAT ID histogram:", rows); for (auto& kv : hf) std::printf(" %d:%d", kv.first, kv.second);
    std::printf("\nDATA TYPE ID histogram:"); for (auto& kv : ht) std::printf(" %d:%d", kv.first, kv.second);
    std::printf("\nvalidity histogram (0 good, 1 bad):"); for (auto& kv : hv) std::printf(" %d:%d", kv.first, kv.second);
    std::printf("\n(receive, transmit) station pairs:"); for (auto& kv : hs) std::printf(" (%d,%d):%d", kv.first.first, kv.first.second, kv.second);
    // label window 2002-157T20:41:30 .. 22:45:36 in seconds since 1950-01-01: days = 52*365 + 13 leap days (1952..2000) + 156
    const double d0 = (52.0 * 365.0 + 13.0 + 156.0) * 86400.0, t0 = d0 + 20 * 3600 + 41 * 60 + 30, t1 = d0 + 22 * 3600 + 45 * 60 + 36;
    std::printf("\nlabel window = %.0f .. %.0f s since 1950 ; decoded tags %.3f .. %.3f ; offsets from the window: start %+.3f s, stop %+.3f s ; non-monotone steps %d\n", t0, t1, tmin, tmax, tmin - t0, tmax - t1, nonmono);
    bool c1 = hf.size() == 1 && hf.count(2), c2 = tmin >= t0 - 86400 && tmax <= t1 + 86400 && nonmono == 0, c4 = true; for (auto& kv : hs) for (int s : {kv.first.first, kv.first.second}) if (s != 0 && s != 25 && s != 45 && s != 54) c4 = false;
    std::printf("[C1] format ID = 2 for all rows: %s\n[C2] time tags non-decreasing and inside the window (prompt tolerance +-1 day): %s ; inside to +-1 s: %s\n[C3] data-type histogram above; Doppler types (11-13) present: %s ; range types (36, 37) present: %s\n[C4] non-zero station IDs within the label set {25, 45, 54}: %s\n[C5] no SDT residual computed.\n", c1 ? "met" : "NOT MET", c2 ? "met" : "NOT MET", (std::fabs(tmin - t0) <= 1.0 && std::fabs(tmax - t1) <= 1.0) ? "yes" : "no", (ht.count(11) || ht.count(12) || ht.count(13)) ? "yes" : "no", (ht.count(36) || ht.count(37)) ? "yes" : "no", c4 ? "met" : "NOT MET");
    return 0; }
