// GOM_DAT4 multi-day decode (2026-10-12). Registration: GOM_DAT4_RESET_ASSESSMENT_2026-10-12.md sections 0-2 (written before this file existed).
// Eight CORS_0021 ODFs (K252 and XMMMV0, days 157-160): per-file sizes, rows, format ID, types, stations, time windows against the labels.
// Author: J. C. Harvey, Melbourne.
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iterator>
#include <map>
#include <set>
#include <string>
#include <vector>
static uint32_t be32(const uint8_t* p) { return (uint32_t(p[0]) << 24) | (uint32_t(p[1]) << 16) | (uint32_t(p[2]) << 8) | p[3]; }
static uint64_t bits(const uint8_t* p, int start1, int n) { uint64_t v = 0; for (int i = 0; i < n; ++i) { int b = start1 - 1 + i; v = (v << 1) | ((p[b / 8] >> (7 - b % 8)) & 1); } return v; }
struct F { int fmt, rx, tx, type, valid; double t; };
static F decode(const uint8_t* p) { const uint8_t* q = p + 16; F f; f.t = double(be32(p)) + double(bits(p + 4, 1, 10)) / 1000.0; f.fmt = int(bits(q, 1, 3)); f.rx = int(bits(q, 4, 7)); f.tx = int(bits(q, 11, 7)); f.type = int(bits(q, 20, 6)); f.valid = int(bits(q, 32, 1)); return f; }
static std::string readTxt(const std::string& p) { std::ifstream f(p, std::ios::binary); return std::string((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>()); }
static std::string lblStr(const std::string& L, const std::string& key) { size_t p = L.find("\n" + key); if (p == std::string::npos) return ""; p = L.find('=', p); size_t e = L.find('\n', p); std::string v = L.substr(p + 1, e - p - 1); while (!v.empty() && (v[0] == ' ')) v.erase(0, 1); while (!v.empty() && (v.back() == '\r' || v.back() == ' ')) v.pop_back(); return v; }
static long labelRows(const std::string& L) { size_t p = L.find("= ODF3C_TABLE"); p = L.find("ROWS", p); p = L.find('=', p); return std::stol(L.substr(p + 1)); }
static double labelSec(const std::string& s) { // "2002-157T20:41:30" -> seconds since 1950-01-01
    int y = std::stoi(s.substr(0, 4)), d = std::stoi(s.substr(5, 3)), hh = std::stoi(s.substr(9, 2)), mm = std::stoi(s.substr(12, 2)), ss = std::stoi(s.substr(15, 2)); int leap = 0; for (int yy = 1950; yy < y; ++yy) if ((yy % 4 == 0 && yy % 100 != 0) || yy % 400 == 0) ++leap; return ((double)(y - 1950) * 365.0 + leap + (d - 1)) * 86400.0 + hh * 3600.0 + mm * 60.0 + ss; }
static void setbits(uint8_t* r, int byte0, int start1, int n, uint64_t v) { for (int i = 0; i < n; ++i) { int b = byte0 * 8 + start1 - 1 + i; if ((v >> (n - 1 - i)) & 1) r[b / 8] |= uint8_t(0x80 >> (b % 8)); } }
struct Res { std::string name; long rows; double wmin, wmax, tmin, tmax; bool ok; };
int main() {
    std::printf("GOM_DAT4 multi-day decode (registered in GOM_DAT4_RESET_ASSESSMENT_2026-10-12.md)\n=======================================================================\n\n");
    const std::string RAW = "Datasets/solar_propagation_2026-08/raw/cassini_sce1/cors_0021/";
    int fails = 0;
    { uint8_t r[36] = {0}; uint32_t sec = 1654548090u; r[0] = uint8_t(sec >> 24); r[1] = uint8_t(sec >> 16); r[2] = uint8_t(sec >> 8); r[3] = uint8_t(sec); setbits(r, 4, 1, 10, 500); setbits(r, 16, 1, 3, 2); setbits(r, 16, 4, 7, 25); setbits(r, 16, 11, 7, 25); setbits(r, 16, 20, 6, 12); F f = decode(r); bool ok = f.fmt == 2 && f.rx == 25 && f.tx == 25 && f.type == 12 && f.t == 1654548090.5; std::printf("[VA] synthetic round trip: %s\n", ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    std::vector<Res> all[2]; const char* fam[2] = {"k252v0", "xmmmv0"};
    for (int fi = 0; fi < 2; ++fi) for (int day = 157; day <= 160; ++day) {
        char pb[300]; std::snprintf(pb, sizeof pb, "%ssce1_%d/odf/c32easc2002_%d_0000%s", RAW.c_str(), day, day, fam[fi]); std::string odf = std::string(pb) + ".odf", lbl = std::string(pb) + ".lbl";
        std::ifstream f(odf, std::ios::binary); if (!f) { std::printf("%s day %d: odf MISSING\n", fam[fi], day); ++fails; continue; } std::vector<uint8_t> b((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>()); std::string L = readTxt(lbl);
        long recBytes = std::stol(lblStr(L, "RECORD_BYTES")), fileRecords = std::stol(lblStr(L, "FILE_RECORDS")), rowsLbl = labelRows(L); double w0 = labelSec(lblStr(L, "START_TIME")), w1 = labelSec(lblStr(L, "STOP_TIME")); std::string stations = lblStr(L, "DSN_STATION_NUMBER");
        bool sizeOk = (long)b.size() == recBytes * fileRecords; long nrec = (long)(b.size() / 36);
        // headers by scanning declared keys
        long h109 = -1, hnext = -1; for (long i = 0; i < nrec; ++i) { int32_t w = (int32_t)be32(b.data() + 36 * i); if (w == 109 && h109 < 0) h109 = i; else if (h109 >= 0 && (w == 2030 || w == 105 || w == -1) && hnext < 0 && i > h109) { hnext = i; break; } }
        long rowsFound = hnext - h109 - 1; std::map<int, int> hf, ht; std::map<std::pair<int, int>, int> hs; double tmin = 1e30, tmax = -1e30, prev = 0; int nonmono = 0;
        for (long r = h109 + 1; r < hnext; ++r) { F x = decode(b.data() + 36 * r); ++hf[x.fmt]; ++ht[x.type]; ++hs[{x.rx, x.tx}]; if (x.t < tmin) tmin = x.t; if (x.t > tmax) tmax = x.t; if (x.t < prev) ++nonmono; prev = x.t; }
        std::set<int> allowed; { size_t p = stations.find('{'); size_t e = stations.find('}'); std::string s = stations.substr(p + 1, e - p - 1); size_t i = 0; while (i < s.size()) { size_t c = s.find(',', i); if (c == std::string::npos) c = s.size(); allowed.insert(std::stoi(s.substr(i, c - i))); i = c + 1; } }
        bool stOk = true; for (auto& kv : hs) for (int s : {kv.first.first, kv.first.second}) if (s != 0 && !allowed.count(s)) stOk = false;
        bool fmtOk = hf.size() == 1 && hf.count(2), rowsOk = rowsFound == rowsLbl, tOk = std::fabs(tmin - w0) <= 1.0 + 1e-9 && std::fabs(tmax - w1) <= 1.0 + 1e-9, dayOk = tmin >= w0 - 86400 && tmax <= w1 + 86400;
        std::printf("%s day %d: size %zu = %ld x %ld %s ; records %ld ; orbit header at record %ld, next header at %ld ; rows found %ld, label ROWS %ld %s ; format ID %s ; types:", fam[fi], day, b.size(), recBytes, fileRecords, sizeOk ? "ok" : "MISMATCH", nrec, h109 + 1, hnext + 1, rowsFound, rowsLbl, rowsOk ? "ok" : "MISMATCH", fmtOk ? "2 on all rows" : "NOT 2 everywhere"); for (auto& kv : ht) std::printf(" %d:%d", kv.first, kv.second);
        std::printf(" ; stations %s %s ; tags %.3f..%.3f against label %.0f..%.0f (offsets %+.3f, %+.3f s; inside 1 s: %s; inside 1 day: %s) ; non-monotone steps %d\n", stations.c_str(), stOk ? "ok" : "OUTSIDE", tmin, tmax, w0, w1, tmin - w0, tmax - w1, tOk ? "yes" : "NO", dayOk ? "yes" : "NO", nonmono);
        if (!sizeOk || !rowsOk || !fmtOk || !stOk || !dayOk || nonmono) ++fails; all[fi].push_back({std::string(fam[fi]) + " " + std::to_string(day), rowsFound, w0, w1, tmin, tmax, tOk}); }
    for (int fi = 0; fi < 2; ++fi) { std::printf("\nWINDOWS %s (label START..STOP, seconds since 1950; gap to the next day):\n", fam[fi]); bool asc = true; for (size_t i = 0; i < all[fi].size(); ++i) { double gap = i + 1 < all[fi].size() ? all[fi][i + 1].wmin - all[fi][i].wmax : 0; if (i + 1 < all[fi].size() && gap <= 0) asc = false; std::printf("  %s : %.0f .. %.0f (span %.0f s)%s\n", all[fi][i].name.c_str(), all[fi][i].wmin, all[fi][i].wmax, all[fi][i].wmax - all[fi][i].wmin, i + 1 < all[fi].size() ? (" ; gap to next " + std::to_string((long long)gap) + " s").c_str() : ""); } std::printf("  ascending and non-overlapping: %s\n", asc ? "yes" : "NO"); if (!asc) ++fails; }
    std::printf("\n%s\n", fails ? "SOME CHECKS NOT MET" : "ALL CHECKS MET (VERIFICATION)");
    return fails ? 1 : 0; }
