// GOM38 blank-slate run 1 (2026-10-11), Stage 1: census of the XMMMV0 ODFs (days 157-160) and the type-37 range rows.
// Registration: GOM38_RESET_ASSESSMENT_2026-10-11.md sections 0-2 (written before this file existed).
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
#include <vector>

static const std::string RAW = "Datasets/solar_propagation_2026-08/raw/";
static uint32_t be32(const uint8_t* p) { return (uint32_t(p[0]) << 24) | (uint32_t(p[1]) << 16) | (uint32_t(p[2]) << 8) | p[3]; }
static uint64_t bits(const uint8_t* p, int start1, int n) { uint64_t v = 0; for (int i = 0; i < n; ++i) { int b = start1 - 1 + i; v = (v << 1) | ((p[b / 8] >> (7 - b % 8)) & 1); } return v; }
static int labelRows(const std::string& lbl) { std::ifstream f(lbl); std::string ln; bool in = false; while (std::getline(f, ln)) { if (ln.find("= ODF3C_TABLE") != std::string::npos && ln.find("OBJECT") != std::string::npos) in = true; if (in && ln.find("ROWS") != std::string::npos) { size_t p = ln.find('='); return std::stoi(ln.substr(p + 1)); } } return -1; }

int main() {
    std::printf("GOM38 blank-slate run 1, Stage 1 census (registered in GOM38_RESET_ASSESSMENT_2026-10-11.md sections 0-2)\n=======================================================================\n\n");
    int totalUsed = 0; bool allFinite = true;
    for (int day = 157; day <= 160; ++day) {
        char b1[256], b2[256]; std::snprintf(b1, sizeof b1, "cassini_sce1/cors_0021/sce1_%d/odf/c32easc2002_%d_0000xmmmv0.odf", day, day); std::snprintf(b2, sizeof b2, "cassini_sce1/cors_0021/sce1_%d/odf/c32easc2002_%d_0000xmmmv0.lbl", day, day);
        std::ifstream f(RAW + b1, std::ios::binary); if (!f) { std::printf("day %d: file missing\n", day); continue; }
        std::vector<uint8_t> b((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>()); int rows = labelRows(RAW + b2);
        std::map<int, int> byType; std::map<std::string, int> r37; std::map<int, std::set<long long>> items; std::vector<double> obs; std::set<int> uplink, exc, dl; int valid37 = 0, invalid37 = 0; double tmin = 1e30, tmax = -1e30, t12 = 0; int n12 = 0, n12v = 0;
        for (int r = 6; r <= 5 + rows; ++r) { const uint8_t* p = b.data() + 36 * (r - 1); const uint8_t* q = p + 16; double t = double(be32(p)) + double(bits(p + 4, 1, 10)) / 1000.0;
            int type = int(bits(q, 20, 6)), rx = int(bits(q, 4, 7)), tx = int(bits(q, 11, 7)), valid = int(bits(q, 32, 1)); ++byType[type];
            if (type == 12) { ++n12; if (!valid) ++n12v; }
            if (type != 37) continue; if (valid) { ++invalid37; continue; } ++valid37;
            double o = double(int32_t(be32(p + 8))) + double(int32_t(be32(p + 12))) / 1e9; if (!std::isfinite(o)) allFinite = false; obs.push_back(o); tmin = std::min(tmin, t); tmax = std::max(tmax, t);
            int dband = int(bits(q, 26, 2)), uband = int(bits(q, 28, 2)), eband = int(bits(q, 30, 2)); dl.insert(dband); uplink.insert(uband); exc.insert(eband);
            char key[64]; std::snprintf(key, sizeof key, "rx%d tx%d", rx, tx); ++r37[key];
            items[15].insert((long long)bits(q, 33, 7)); items[16].insert((long long)bits(q, 40, 10)); items[17].insert((long long)bits(q, 50, 1)); items[18].insert((long long)bits(q, 51, 22)); items[19].insert((long long)bits(q, 73, 24)); items[20].insert((long long)bits(p + 28, 1, 20)); items[21].insert((long long)bits(p + 28, 21, 22)); items[22].insert((long long)bits(p + 28, 43, 22)); }
        std::printf("day %d: label ROWS %d, type-12 rows %d (valid %d); row counts by data type:", day, rows, n12, n12v); for (auto& kv : byType) std::printf(" %d:%d", kv.first, kv.second); std::printf("\n");
        std::printf("  type-37: valid %d, invalid %d; stations:", valid37, invalid37); for (auto& kv : r37) std::printf(" [%s]=%d", kv.first.c_str(), kv.second); std::printf("; downlink band ids:"); for (int v : dl) std::printf(" %d", v); std::printf("; uplink:"); for (int v : uplink) std::printf(" %d", v); std::printf("; exciter:"); for (int v : exc) std::printf(" %d", v); std::printf("\n");
        if (!obs.empty()) { std::vector<double> s = obs; std::sort(s.begin(), s.end()); std::printf("  type-37 observable (decoded int32 + frac/1e9): min %.3f, median %.3f, max %.3f ; span %.1f s\n", s.front(), s[s.size() / 2], s.back(), tmax - tmin); }
        for (auto& kv : items) { std::printf("  type-37 Item %d: %zu distinct values:", kv.first, kv.second.size()); int c = 0; for (long long v : kv.second) { if (c++ >= 8) break; std::printf(" %lld", v); } std::printf("\n"); }
        totalUsed += valid37; }
    std::printf("\nC1: used type-37 rows (validity 0) over days 157-160 = %d -> %s\nC2: every used row decodes finite: %s\n", totalUsed, totalUsed > 0 ? "met" : "NOT MET", allFinite ? "yes" : "NO");
    return 0;
}
