// GOM_DAT8 blank-slate run 1, Phase A (2026-10-10): decode of the Cassini SCE1 ODF 157 and structure checks against values the PDS label states.
// Registration: GOM_DAT8_RESET_ASSESSMENT_2026-10-10.md sections 0-2 (written before this file existed). Phase A makes no comparison with the Horizons geometry beyond VA5 (geometry sanity).
//  VA1 size = 36 x 7616; VA2 record 1 key = 101, data rows 6..7452, record 7453 secondary key 0; VA3 format ID 2, allowed data types/bands/validity;
//  VA4 time tags non-decreasing and within 120 s of the label START/STOP; VA5 Horizons deldot = finite difference of delta to 1%; VA6 reference frequency of the selection in 1e9..4e10 Hz.
// Author: J. C. Harvey, Melbourne.
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iterator>
#include <map>
#include <set>
#include <string>
#include <tuple>
#include <vector>

static const char* ODF = "Datasets/solar_propagation_2026-08/raw/cassini_sce1_157_odf.odf";
static const char* HZN = "Datasets/solar_propagation_2026-08/raw/jpl_horizons_cassini_dss25_rr_2002_157.csv";
static uint32_t be32(const uint8_t* p) { return (uint32_t(p[0]) << 24) | (uint32_t(p[1]) << 16) | (uint32_t(p[2]) << 8) | p[3]; }
static uint64_t bits(const uint8_t* p, int start1, int n) { uint64_t v = 0; for (int i = 0; i < n; ++i) { int b = start1 - 1 + i; v = (v << 1) | ((p[b / 8] >> (7 - b % 8)) & 1); } return v; }
static long long days_from_civil(int y, int m, int d) { y -= m <= 2; long long era = (y >= 0 ? y : y - 399) / 400; unsigned yoe = unsigned(y - era * 400); unsigned doy = (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1; unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy; return era * 146097 + (long long)doe - 719468; }
static double sec1950(int y, int m, int d, int hh, int mm, double ss) { return double(days_from_civil(y, m, d) + 7305) * 86400.0 + hh * 3600.0 + mm * 60.0 + ss; }

struct Rec { double t; double obs; int fmt, rx, tx, net, type, dl, ul, ex, valid, sc; double ref; double comp; };

int main() {
    std::printf("GOM_DAT8 blank-slate run 1, Phase A (registered in GOM_DAT8_RESET_ASSESSMENT_2026-10-10.md sections 0-2)\n====================================================================================\n\n");
    int fails = 0;
    std::ifstream f(ODF, std::ios::binary); std::vector<uint8_t> buf((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
    // VA1
    { bool ok = buf.size() == 36u * 7616u; std::printf("[VA1] file size %zu bytes, 36 x 7616 = %u -> %s\n", buf.size(), 36u * 7616u, ok ? "met" : "NOT MET"); if (!ok) { ++fails; return 1; } }
    auto R = [&](int rec1) { return buf.data() + 36 * (rec1 - 1); };
    // VA2
    // Amendment 1 (2026-10-10, after attempt 1 was seen): the registered check "record 7453 secondary key = 0" was an assumption of mine, not a statement of the label (attempt 1: G0, output kept).
    // The label names the headers ODF4A25, ODF4A45, ODF4A54 at records 7453, 7455, 7456 (DSN_STATION_NUMBER = {25,45,54}); the corrected check is: secondary keys at those records are 25, 45, 54.
    // 25 was seen in attempt 1; 45 and 54 are checks not seen before.
    { bool k1 = be32(R(1)) == 101, s7453 = be32(R(7453) + 4) == 25 && be32(R(7455) + 4) == 45 && be32(R(7456) + 4) == 54; std::printf("[VA2] record 1 primary key = %u (label: 101); secondary keys at records 7453, 7455, 7456 = %u, %u, %u (label names: stations 25, 45, 54); primary keys of records 3, 5, 7453-7460:", be32(R(1)), be32(R(7453) + 4), be32(R(7455) + 4), be32(R(7456) + 4));
      for (int r : {3, 5, 7453, 7454, 7455, 7456, 7457, 7458, 7459, 7460}) std::printf(" %d:%u", r, be32(R(r))); bool ok = k1 && s7453; std::printf(" -> %s\n", ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    // decode rows 6..7452
    std::vector<Rec> rows;
    for (int r = 6; r <= 7452; ++r) { const uint8_t* p = R(r); Rec x{};
        double ti = double(be32(p)); uint64_t b2 = bits(p + 4, 1, 32); double ms = double(bits(p + 4, 1, 10)); (void)b2; x.t = ti + ms / 1000.0;
        int32_t oi = int32_t(be32(p + 8)), of = int32_t(be32(p + 12)); x.obs = double(oi) + double(of) / 1e9;
        const uint8_t* q = p + 16; x.fmt = int(bits(q, 1, 3)); x.rx = int(bits(q, 4, 7)); x.tx = int(bits(q, 11, 7)); x.net = int(bits(q, 18, 2)); x.type = int(bits(q, 20, 6)); x.dl = int(bits(q, 26, 2)); x.ul = int(bits(q, 28, 2)); x.ex = int(bits(q, 30, 2)); x.valid = int(bits(q, 32, 1)); x.sc = int(bits(q, 40, 10));
        uint64_t hi = bits(q, 51, 22), lo = bits(q, 73, 24); x.ref = (double(hi) * 16777216.0 + double(lo)) / 1000.0;
        x.comp = double(bits(p + 28, 21, 22)) / 100.0; rows.push_back(x); }
    std::printf("decoded %zu orbit-data rows\n", rows.size());
    // VA3
    { std::set<int> allowed = {1, 2, 3, 4, 5, 6, 11, 12, 13, 21, 22, 23, 36, 37, 41, 51, 52, 53, 54, 55, 56, 57, 58}; bool ok = true; for (auto& x : rows) { if (x.fmt != 2 || !allowed.count(x.type) || x.dl < 1 || x.dl > 3 || x.valid > 1) ok = false; }
      std::printf("[VA3] format ID = 2, data type in the label's list, downlink band in 1..3, validity in {0,1} for all rows -> %s\n", ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    // VA4
    { bool mono = true; for (size_t i = 1; i < rows.size(); ++i) if (rows[i].t < rows[i - 1].t) mono = false; double t0 = sec1950(2002, 1, 1, 20, 41, 30) + 156 * 86400.0, t1 = sec1950(2002, 1, 1, 22, 45, 36) + 156 * 86400.0;
      bool ok = mono && std::fabs(rows.front().t - t0) <= 120 && std::fabs(rows.back().t - t1) <= 120; std::printf("[VA4] time tags non-decreasing: %s ; first %.3f (label start %.0f, diff %+.1f s), last %.3f (label stop %.0f, diff %+.1f s) -> %s\n", mono ? "yes" : "NO", rows.front().t, t0, rows.front().t - t0, rows.back().t, t1, rows.back().t - t1, ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    // VA5
    std::vector<double> hd, hdd;
    { std::ifstream h(HZN); std::string ln; bool in = false; while (std::getline(h, ln)) { if (ln.find("$$SOE") != std::string::npos) { in = true; continue; } if (ln.find("$$EOE") != std::string::npos) break; if (!in) continue; std::vector<std::string> t; size_t p = 0; while (true) { size_t q = ln.find(',', p); if (q == std::string::npos) break; t.push_back(ln.substr(p, q - p)); p = q + 1; } if (t.size() >= 5) { hd.push_back(std::stod(t[3])); hdd.push_back(std::stod(t[4])); } }
      double worst = 0; for (size_t i = 1; i + 1 < hd.size(); ++i) { double fd = (hd[i + 1] - hd[i - 1]) / 600.0 * 149597870.7; worst = std::max(worst, std::fabs(fd / hdd[i] - 1)); }
      bool ok = hd.size() == 31 && worst < 0.01; std::printf("[VA5] Horizons rows %zu ; deldot vs finite difference of delta: worst relative difference %.2e -> %s\n", hd.size(), worst, ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    // selection
    std::vector<Rec> sel; for (auto& x : rows) if (x.type == 12 && x.valid == 0 && x.rx == 25 && x.tx == 25) sel.push_back(x);
    // VA6
    { bool ok = !sel.empty(); std::set<double> refs; for (auto& x : sel) { if (x.ref < 1e9 || x.ref > 4e10) ok = false; refs.insert(x.ref); } std::printf("[VA6] selection (type 12, valid, rx 25, tx 25): %zu records ; reference frequency in 1e9..4e10 Hz: %s ; distinct values %zu -> %s\n", sel.size(), ok ? "yes" : "NO", refs.size(), ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    std::printf("\nPHASE A VALIDATIONS: %s\n\n", fails == 0 ? "met" : "NOT MET -> G0");
    // report
    std::map<std::tuple<int, int, int, int, int, int, int>, int> cnt; for (auto& x : rows) ++cnt[{x.type, x.rx, x.tx, x.dl, x.ul, x.ex, x.valid}];
    std::printf("Counts by (data type, rx, tx, downlink band, uplink band, exciter band, validity):\n"); for (auto& kv : cnt) std::printf("  type %2d rx %2d tx %2d dl %d ul %d ex %d valid %d : %d\n", std::get<0>(kv.first), std::get<1>(kv.first), std::get<2>(kv.first), std::get<3>(kv.first), std::get<4>(kv.first), std::get<5>(kv.first), std::get<6>(kv.first), kv.second);
    if (!sel.empty()) {
        std::printf("\nSelection: %zu records, time tags %.3f to %.3f s (span %.1f s)\n", sel.size(), sel.front().t, sel.back().t, sel.back().t - sel.front().t);
        double omin = 1e99, omax = -1e99; for (auto& x : sel) { omin = std::min(omin, x.obs); omax = std::max(omax, x.obs); } std::printf("  observable range %.4f to %.4f Hz\n", omin, omax);
        std::map<double, int> refc, compc; for (auto& x : sel) { ++refc[x.ref]; ++compc[x.comp]; } std::printf("  reference frequency values (Hz: count):"); int k = 0; for (auto& kv : refc) { if (k++ < 6) std::printf(" %.3f:%d", kv.first, kv.second); } std::printf(" ... (%zu distinct; min %.3f max %.3f)\n", refc.size(), refc.begin()->first, refc.rbegin()->first);
        std::printf("  compression time (s: count):"); for (auto& kv : compc) std::printf(" %.2f:%d", kv.first, kv.second); std::printf("\n  spacecraft ID values:"); std::set<int> scs; for (auto& x : sel) scs.insert(x.sc); for (int s : scs) std::printf(" %d", s);
        std::printf("\n  first 3 and last 2 selected records:\n"); for (size_t i : {size_t(0), size_t(1), size_t(2), sel.size() - 2, sel.size() - 1}) std::printf("    t = %.3f  obs = %.6f Hz  ref = %.3f Hz  comp = %.2f s  sc = %d\n", sel[i].t, sel[i].obs, sel[i].ref, sel[i].comp, sel[i].sc); }
    return 0;
}
