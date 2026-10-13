// NP40 reset, instrument 1 (2026-10-10): EC accessibility (Q_EC) and the EC grammar test on NUBASE2020 ground states.
// Record: NP40_RESET_ASSESSMENT_2026-10-10.md. Written afresh. Author: J. C. Harvey, Melbourne.
#include <cmath>
#include <cstdio>
#include <fstream>
#include <map>
#include <regex>
#include <string>
#include <vector>
struct Nuc { int A, Z; double D; bool Dexp; std::string modes; };
static std::string trim(const std::string& s) { size_t a = s.find_first_not_of(' '), b = s.find_last_not_of(" \r"); return a == std::string::npos ? "" : s.substr(a, b - a + 1); }
static bool valid_ec(int A, int Z) { return (A - 2 * Z + 1) >= 0 && (3 * Z - A - 3) >= 0; }
int main(int argc, char** argv) {
    const char* path = argc > 1 ? argv[1] : "Datasets/nuclear/NUBASE2020.txt";
    std::printf("NP40 reset instrument 1 (2026-10-10)\n====================================\n\n");
    std::map<std::pair<int, int>, Nuc> g; std::ifstream f(path); std::string s; int lines = 0;
    while (std::getline(f, s)) { if (s.empty() || s[0] == '#' || s.size() < 31) continue; ++lines; if (s[7] != '0') continue;
        Nuc n; n.A = std::stoi(s.substr(0, 3)); n.Z = std::stoi(s.substr(4, 3)); std::string m = trim(s.substr(18, 13)); n.Dexp = m.find('#') == std::string::npos;
        try { n.D = std::stod(m.substr(0, m.find('#'))); } catch (...) { continue; } n.modes = s.size() > 119 ? trim(s.substr(119)) : ""; g[{n.Z, n.A}] = n; }
    std::printf("data lines %d ; ground states parsed %zu\n", lines, g.size());
    int bad = 0;
    { auto& b = g.at({4, 7}); bool ok = b.Dexp && std::fabs(b.D - 15769.00) < 1e-6 && b.modes.find("EC=100") != std::string::npos && g.count({11, 22}); std::printf("[V1] 7Be: Delta %.2f keV, modes '%s' ; 22Na present -> %s\n", b.D, b.modes.c_str(), ok ? "met" : "NOT MET"); bad += !ok; }
    { double q = g.at({4, 7}).D - g.at({3, 7}).D; bool ok = std::fabs(q - 861.89) < 0.02; std::printf("[V2] Q_EC(7Be) = %.3f keV (known 861.89) -> %s\n", q, ok ? "met" : "NOT MET"); bad += !ok; }
    { bool ok = valid_ec(7, 4) && (7 - 8 + 1) == 0 && (12 - 7 - 3) == 2; std::printf("[V3] 7Be EC grammar n_t = %d, n_d = %d, valid %s -> %s\n\n", 7 - 8 + 1, 12 - 7 - 3, valid_ec(7, 4) ? "yes" : "no", ok ? "met" : "NOT MET"); bad += !ok; }
    if (bad) { std::printf("VALIDATIONS NOT MET\n"); return 1; }
    std::printf("VALIDATIONS: met\n\n");
    std::regex prim("(EC|B\\+)[=~<>]"), any("(EC|B\\+)");
    // P0 accessibility
    int pairs = 0, qpos = 0, qpos_valid = 0, ecQknown = 0, ecQpos = 0;
    for (auto& [k, n] : g) { if (n.Z < 2) continue; auto it = g.find({n.Z - 1, n.A}); if (it == g.end() || !n.Dexp || !it->second.Dexp) continue; ++pairs; double q = n.D - it->second.D;
        if (q > 0) { ++qpos; if (valid_ec(n.A, n.Z)) ++qpos_valid; }
        if (std::regex_search(n.modes, prim)) { ++ecQknown; if (q > 0) ++ecQpos; } }
    std::printf("P0 accessibility: ground-state pairs (Z,A)->(Z-1,A) with experimental Delta: %d ; Q_EC > 0: %d ; of those grammar-valid parents: %d (%.1f%%)\n", pairs, qpos, qpos_valid, 100.0 * qpos_valid / qpos);
    std::printf("   known answer: primary EC nuclides with both Delta experimental: %d ; with Q_EC > 0: %d -> %s\n\n", ecQknown, ecQpos, ecQknown == ecQpos ? "met" : "NOT MET");
    // P1 grammar test
    auto test = [&](const char* name, auto sel) { int n = 0, v = 0, lo = 0, hi = 0; std::vector<std::string> ex;
        for (auto& [k, u] : g) { if (u.Z < 2 || !sel(u)) continue; ++n; int N = u.A - u.Z; if (valid_ec(u.A, u.Z)) ++v; else { if (N < u.Z - 1) ++lo; else ++hi; if (ex.size() < 8) ex.push_back(std::to_string(u.A) + "(Z=" + std::to_string(u.Z) + ",N=" + std::to_string(N) + ")"); } }
        std::printf("  %-34s n = %4d ; valid %4d (%.2f%%) ; invalid %4d (%.2f%%): N < Z-1: %d, N > 2Z-3: %d", name, n, v, 100.0 * v / n, n - v, 100.0 * (n - v) / n, lo, hi);
        if (!ex.empty()) { std::printf(" ; e.g."); for (auto& e : ex) std::printf(" %s", e.c_str()); } std::printf("\n"); return 100.0 * (n - v) / n; };
    std::printf("P1 EC grammar validity (Z-1 <= N <= 2Z-3):\n");
    double fprim = test("primary EC set (EC/B+ with value)", [&](const Nuc& u) { return std::regex_search(u.modes, prim); });
    test("secondary EC set (incl. '?')", [&](const Nuc& u) { return std::regex_search(u.modes, any); });
    test("null: all ground states Z >= 2", [](const Nuc&) { return true; });
    test("contrast: beta-minus emitters", [](const Nuc& u) { return u.modes.find("B-") != std::string::npos; });
    test("primary EC set, experimental Delta only", [&](const Nuc& u) { return u.Dexp && std::regex_search(u.modes, prim); });
    std::printf("\ngate (a): invalid fraction of primary EC set = %.2f%% -> %s (threshold 1%%)\n", fprim, fprim > 1.0 ? "MET: the EC grammar does not cover the EC nuclides" : "not met: grammar covers the EC set");
    return 0;
}
