// =====================================================================
//  GD09b : baryon allotment per object — Sgr A*, S stars, NSC/NSD, bulge, bar, each spiral arm, unallocated.
//  Rule (Operator): arms are objects; no smooth disc carries an allotment. Every baryon is assigned to a named
//  object or reported as unallocated. N = M/M_Sun x N_Sun (engine census, no kilograms).
//  Pre-registration: PROMPT.md Addendum 1. Build: cl /std:c++20 /EHsc /O2 /openmp /I Engine/include gd09b_object_allotment.cpp
//  Run from this folder. Writes: object_allotment.csv
//
//  Author: SDT Canonical Engine — J. C. Harvey, Melbourne
// =====================================================================

#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cmath>
#include <numbers>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>
#include <sdt/laws.hpp>

namespace {

using namespace sdt::laws;
constexpr double PI = std::numbers::pi;
const double N_SUN = bridge::N_baryons(bridge::koppa_Sun);
constexpr double K_ARM = 1.32;

std::string slurp(const std::string& fn) { std::ifstream f(fn, std::ios::binary); std::stringstream ss; ss << f.rdbuf(); return ss.str(); }
struct Node { double x, y, sin, sz; int tier; int arm; double R; };
struct Arm { std::string name; std::vector<Node> nodes; };
std::vector<Arm> read_arms(const std::string& fn) {
    std::string s = slurp(fn); std::vector<Arm> arms; size_t pos = 0;
    while ((pos = s.find("{name:\"", pos)) != std::string::npos) {
        pos += 7; size_t e = s.find('"', pos); Arm a; a.name = s.substr(pos, e - pos);
        size_t p = s.find("pts:[", e) + 5;
        while (s[p] != ']') {
            if (s[p] == ',') { ++p; continue; }
            ++p; char* end; double v[5];
            for (int i = 0; i < 5; ++i) { v[i] = std::strtod(s.c_str() + p, &end); p = end - s.c_str(); if (s[p] == ',') ++p; }
            ++p; a.nodes.push_back({v[0], v[1], v[2], v[3], (int)std::lround(v[4]), (int)arms.size(), std::hypot(v[0], v[1])});
        }
        arms.push_back(a); pos = p;
    }
    return arms;
}
double read_n(const std::string& js, const std::string& id, int which) {      // which: 0 lo, 1 central, 2 hi
    size_t p = js.find("{id:\"" + id + "\"");
    if (p == std::string::npos) { std::printf("missing row %s\n", id.c_str()); std::exit(2); }
    p = js.find("n:[", p) + 3; char* end; double v[3];
    for (int i = 0; i < 3; ++i) { v[i] = std::strtod(js.c_str() + p, &end); p = end - js.c_str() + 1; }
    return v[which];
}
struct Rng { std::mt19937_64 g; explicit Rng(uint64_t s) : g(s) {} double u() { return ((g() >> 11) + 0.5) * (1.0 / 9007199254740992.0); } double expo(double m) { return -m * std::log(u()); } };
double erl_frac(double Rd, double a, double b) { return (1 + a / Rd) * std::exp(-a / Rd) - (1 + b / Rd) * std::exp(-b / Rd); }
int g_fail = 0;
void check(const char* id, const char* what, bool ok, double v) { std::printf("  [%s] %s : %s  (%.3e)\n", ok ? "PASS" : "FAIL", id, what, v); if (!ok) ++g_fail; }

} // namespace

int main(int argc, char** argv) {
    const bool measured_only = argc > 1 && std::string(argv[1]) == "measured";   // variant: tier-1 (measured azimuth) ridge only
    std::printf("=================================================================\n");
    std::printf(" GD09b BARYON ALLOTMENT PER OBJECT  (arms are objects; no smooth disc carries an allotment)\n");
    std::printf("=================================================================\n");
    auto arms = read_arms("../GD08_Milky_Way_Arm_Topology/mw_arms_data.js");
    std::string js = slurp("mw_baryons.js");
    if (arms.empty() || js.empty()) { std::printf("input files missing\n"); return 1; }
    const double Nt = read_n(js, "disc_thin", 1), Nk = read_n(js, "disc_thick", 1), Ng = read_n(js, "gas_disc_He", 1);
    const double Nsgr = read_n(js, "smbh", 1), Nbul = read_n(js, "bulge_stellar", 1) + read_n(js, "gas_bulge", 1);
    const double Nbar = read_n(js, "bar_thin", 1) + read_n(js, "bar_superthin", 1), Nnsc = read_n(js, "nsc", 1), Nnsd = read_n(js, "nsd", 1);
    const double Ngal = Nsgr + Nbul + Nk + Nt + Ng;
    std::printf("N_Sun = %.4e baryons per M_Sun ; Galaxy partition total (Sgr A* + bulge region + thick + thin + gas) = %.4e\n\n", N_SUN, Ngal);

    // ---------------- grid route ----------------
    const double half = 20.0, h = 0.05; const int n = (int)std::lround(2 * half / h) + 1; const int NA = (int)arms.size();
    std::vector<const Node*> nodes; for (auto& a : arms) for (auto& nd : a.nodes) if (measured_only ? nd.tier == 1 : nd.tier <= 1) nodes.push_back(&nd);
    std::vector<float> best((size_t)n * n, 0.f); std::vector<unsigned char> aid((size_t)n * n, 255);
#pragma omp parallel for schedule(static)
    for (long j = 0; j < n; ++j) for (int i = 0; i < n; ++i) {
        double x = -half + h * i, y = -half + h * j, b = 0; int id = 255;
        for (auto* nd : nodes) { double dx = x - nd->x, dy = y - nd->y, d2 = dx * dx + dy * dy; if (d2 < 9 * nd->sin * nd->sin) { double w = std::exp(-d2 / (2 * nd->sin * nd->sin)); if (w > b) { b = w; id = nd->arm; } } }
        best[(size_t)j * n + i] = (float)b; aid[(size_t)j * n + i] = (unsigned char)id;
    }
    const double Ft = erl_frac(2.6, 0, 20), Fg = erl_frac(5.2, 2, 19), Fk = erl_frac(2.0, 0, 20);
    auto St = [&](double R) { return R <= 20.0 ? Nt * std::exp(-R / 2.6) / (Ft * 2 * PI * 2.6 * 2.6) : 0.0; };
    auto Sg = [&](double R) { return (R >= 2.0 && R <= 19.0) ? Ng * std::exp(-R / 5.2) / (Fg * 2 * PI * 5.2 * 5.2) : 0.0; };
    auto Sk = [&](double R) { return R <= 20.0 ? Nk * std::exp(-R / 2.0) / (Fk * 2 * PI * 2.0 * 2.0) : 0.0; };
    double I0t = 0, I0g = 0, I0k = 0, Imt = 0, Img = 0;
    for (int j = 0; j < n; ++j) for (int i = 0; i < n; ++i) {
        double x = -half + h * i, y = -half + h * j, R = std::hypot(x, y), b = best[(size_t)j * n + i], m = 1 + (K_ARM - 1) * b;
        I0t += St(R) * h * h; I0g += Sg(R) * h * h; I0k += Sk(R) * h * h; Imt += St(R) * m * h * h; Img += Sg(R) * m * h * h;
    }
    const double ft = I0t / Imt, fg = I0g / Img;
    std::printf("== VALIDATION ==\n");
    check("V1", "surface-density grid integrates to N (thin 1e-3)", std::fabs(I0t / Nt - 1) < 1e-3, I0t / Nt - 1);
    check("V1", "surface-density grid integrates to N (gas 1e-3)", std::fabs(I0g / Ng - 1) < 1e-3, I0g / Ng - 1);
    check("V1", "surface-density grid integrates to N (thick 1e-3)", std::fabs(I0k / Nk - 1) < 1e-3, I0k / Nk - 1);
    {   double Tt = 0, Tg = 0;
        for (int j = 0; j < n; ++j) for (int i = 0; i < n; ++i) { double x = -half + h * i, y = -half + h * j, R = std::hypot(x, y), m = 1 + (K_ARM - 1) * best[(size_t)j * n + i]; Tt += ft * St(R) * m * h * h; Tg += fg * Sg(R) * m * h * h; }
        check("V2", "thin total conserved with overdensity + renormalisation (1e-6)", std::fabs(Tt / I0t - 1) < 1e-6, Tt / I0t - 1);
        check("V2", "gas total conserved with overdensity + renormalisation (1e-6)", std::fabs(Tg / I0g - 1) < 1e-6, Tg / I0g - 1); }

    struct Acc { double E = 0, Et = 0, F1 = 0, F2 = 0, B1 = 0, B2 = 0; };
    std::vector<Acc> A(NA);
    const float t1 = (float)std::exp(-0.5), t2 = (float)std::exp(-2.0);
    for (int j = 0; j < n; ++j) for (int i = 0; i < n; ++i) {
        size_t c = (size_t)j * n + i; int id = aid[c]; if (id == 255) continue;
        double x = -half + h * i, y = -half + h * j, R = std::hypot(x, y), b = best[c], m = 1 + (K_ARM - 1) * b;
        double base = (St(R) + Sg(R)) * h * h, mod = (ft * St(R) + fg * Sg(R)) * h * h;
        A[id].E += mod * (K_ARM - 1) * b;
        A[id].Et += ft * St(R) * h * h * (K_ARM - 1) * b;
        if (b >= t1) { A[id].F1 += mod * m; A[id].B1 += base; }
        if (b >= t2) { A[id].F2 += mod * m; A[id].B2 += base; }
    }

    // ---------------- Monte-Carlo route (two-route check) ----------------
    std::vector<double> mcF1(NA, 0), mcF2(NA, 0);
    {
        const int Npt = 600000, Npg = 150000; Rng r(4242);
        std::vector<double> x, y, w; x.reserve(Npt + Npg); y.reserve(Npt + Npg); w.reserve(Npt + Npg);
        for (int i = 0; i < Npt; ++i) { double R; do { R = r.expo(2.6) + r.expo(2.6); } while (R > 20.0); double ph = 2 * PI * r.u(); x.push_back(R * std::cos(ph)); y.push_back(R * std::sin(ph)); w.push_back(Nt / Npt); }
        for (int i = 0; i < Npg; ++i) { double R; do { R = r.expo(5.2) + r.expo(5.2); } while (R < 2.0 || R > 19.0); double ph = 2 * PI * r.u(); x.push_back(R * std::cos(ph)); y.push_back(R * std::sin(ph)); w.push_back(Ng / Npg); }
        std::vector<double> m(x.size()); std::vector<unsigned char> id(x.size(), 255);
#pragma omp parallel for schedule(static)
        for (long i = 0; i < (long)x.size(); ++i) {
            double b = 0; int ai = 255;
            for (auto* nd : nodes) { double dx = x[i] - nd->x, dy = y[i] - nd->y, d2 = dx * dx + dy * dy; if (d2 < 9 * nd->sin * nd->sin) { double ww = std::exp(-d2 / (2 * nd->sin * nd->sin)); if (ww > b) { b = ww; ai = nd->arm; } } }
            m[i] = 1 + (K_ARM - 1) * b; id[i] = (unsigned char)ai; m[i] = m[i];
            (void)ai;
        }
        // best weight needed again for footprint thresholds
        std::vector<double> bw(x.size(), 0.0);
#pragma omp parallel for schedule(static)
        for (long i = 0; i < (long)x.size(); ++i) bw[i] = (m[i] - 1) / (K_ARM - 1);
        double sa = 0, sm = 0; for (size_t i = 0; i < x.size(); ++i) { sa += w[i]; sm += w[i] * m[i]; }
        for (size_t i = 0; i < x.size(); ++i) { if (id[i] == 255) continue; double ww = w[i] * m[i] * sa / sm; if (bw[i] >= t1) mcF1[id[i]] += ww; if (bw[i] >= t2) mcF2[id[i]] += ww; }
    }
    {   double worst = 0; for (int a = 0; a < NA; ++a) { if (A[a].F2 > 1e-3 * Ngal) worst = std::fmax(worst, std::fabs(mcF2[a] / A[a].F2 - 1)); }
        double worst1 = 0; for (int a = 0; a < NA; ++a) { if (A[a].F1 > 1e-3 * Ngal) worst1 = std::fmax(worst1, std::fabs(mcF1[a] / A[a].F1 - 1)); }
        check("V3", "per-arm +-2 sigma footprint: grid vs Monte-Carlo (3%)", worst < 3e-2, worst);
        check("V3", "per-arm +-1 sigma footprint: grid vs Monte-Carlo (3%)", worst1 < 3e-2, worst1); }
    if (g_fail) { std::printf("validation failed — allotment not recorded.\n"); return 1; }

    // ---------------- table ----------------
    std::printf("\n== ALLOTMENT PER OBJECT (N = M/M_Sun x N_Sun) ==\n");
    FILE* f = std::fopen(measured_only ? "object_allotment_measured.csv" : "object_allotment.csv", "w");
    std::fprintf(f, "object,group,N,share_of_galaxy,relation,source\n");
    auto row = [&](const char* name, const char* grp, double N, const char* rel, const char* src) {
        std::printf("%-44s %-10s %11.3e  %8.4f%%  %-22s %s\n", name, grp, N, 100.0 * N / Ngal, rel, src);
        std::fprintf(f, "\"%s\",%s,%.6e,%.6e,%s,\"%s\"\n", name, grp, N, N / Ngal, rel, src);
    };
    std::printf("%-44s %-10s %11s  %9s  %-22s %s\n", "object", "group", "N baryons", "share", "relation", "source");
    row("Sgr A* (4.2e6 Msun, mass-equivalent)", "nucleus", Nsgr, "additive", "BH&G 2016 via GD09");
    row("Sgr A* (4.28e6 Msun, Gillessen+2017)", "nucleus", 4.28e6 * N_SUN, "alternative", "Gillessen+2017 combined fit");
    // S stars (Habibi+2017 Table 2)
    const char* sn[8] = {"S1", "S2", "S4", "S6", "S7", "S8", "S9", "S12"}; const double sm[8] = {12.4, 13.6, 12.2, 9.2, 8.4, 13.2, 8.2, 7.6};
    double ssum = 0; for (int i = 0; i < 8; ++i) { ssum += sm[i]; char nm[64]; std::snprintf(nm, sizeof nm, "S star %s (%.1f Msun)", sn[i], sm[i]); row(nm, "S stars", sm[i] * N_SUN, "nested in NSC region", "Habibi+2017 Table 2"); }
    row("S stars, eight with measured masses (84.8 Msun)", "S stars", ssum * N_SUN, "nested in NSC region", "Habibi+2017 Table 2");
    row("S/orbit sample, 40 stars, upper bound 14 Msun each", "S stars", (ssum + 32 * 14.0) * N_SUN, "bound, nested", "Gillessen+2017 count; masses of 32 not measured");
    row("Nuclear star cluster", "nucleus", Nnsc, "nested in bulge region", "BH&G 2016 via GD09");
    row("Nuclear stellar disc", "nucleus", Nnsd, "nested in bulge region", "BH&G 2016 via GD09");
    row("Bulge region (stellar + gas)", "bulge", Nbul, "additive", "Portail+2015 via GD09");
    row("Long bar (thin + super-thin)", "bar", Nbar, "nested in thin-disc pool", "Wegg+2015 via GD09");
    double sumF1 = 0, sumF2 = 0, sumE = 0;
    for (int a = 0; a < NA; ++a) {
        char nm[96];
        std::snprintf(nm, sizeof nm, "%s, +-2 sigma footprint", arms[a].name.c_str()); row(nm, "arm", A[a].F2, "nested in thin+gas pool", "GD08 ridge, GD09 profiles, K = 1.32");
        std::snprintf(nm, sizeof nm, "%s, +-1 sigma footprint", arms[a].name.c_str()); row(nm, "arm", A[a].F1, "within the above", "same");
        std::snprintf(nm, sizeof nm, "%s, overdensity excess", arms[a].name.c_str()); row(nm, "arm", A[a].E, "within the above", "same");
        sumF1 += A[a].F1; sumF2 += A[a].F2; sumE += A[a].E;
    }
    row("All arms, +-2 sigma footprints", "arm", sumF2, "nested in thin+gas pool", "sum of the arm rows");
    row("All arms, +-1 sigma footprints", "arm", sumF1, "nested in thin+gas pool", "sum of the arm rows");
    row("All arms, overdensity excess", "arm", sumE, "nested in thin+gas pool", "sum of the arm rows");
    {   double sumEt = 0; for (int a = 0; a < NA; ++a) sumEt += A[a].Et;
        const double Nstel = Nt + Nk;                                         // stellar disc baryons (K light is stellar)
        row("All arms, overdensity excess, thin disc (stellar) only", "arm", sumEt, "within the excess above", "same, thin share");
        row("All arms, K-band luminosity route, 7% of stellar disc", "arm", 0.07 * Nstel, "independent route, upper bound (equal M/L)", "Drimmel & Spergel 2001: arms = 7% of K luminosity");
        row("All arms, K-band luminosity route, 10% of stellar disc", "arm", 0.10 * Nstel, "independent route, upper bound (equal M/L)", "Drimmel & Spergel 2001: 10% if complete over 3/4 of the Galaxy");
        std::printf("   ratio model stellar excess / luminosity route: %.2f (7%%) , %.2f (10%%)\n", sumEt / (0.07 * Nstel), sumEt / (0.10 * Nstel)); }
    row("UNALLOCATED thin + gas, outside every +-2 sigma arm footprint", "unalloc.", Nt + Ng - sumF2, "additive", "pool minus arms; not assigned to any object");
    row("UNALLOCATED thin + gas, outside every +-1 sigma arm footprint", "unalloc.", Nt + Ng - sumF1, "alternative", "pool minus arms; not assigned to any object");
    row("Thick disc (not an arm member)", "unalloc.", Nk, "additive", "BH&G 2016 via GD09");
    std::fclose(f);

    // per-arm geometry
    std::printf("\nper-arm geometry (measured + near-extended ridge): length, mean sigma_in, baryons per kpc of ridge (2 sigma), excess share of the footprint\n");
    for (int a = 0; a < NA; ++a) {
        double len = 0, lm = 0, sw = 0; int c = 0; const Arm& ar = arms[a];
        for (size_t i = 1; i < ar.nodes.size(); ++i) if (measured_only ? (ar.nodes[i].tier == 1 && ar.nodes[i - 1].tier == 1) : (ar.nodes[i].tier <= 1 && ar.nodes[i - 1].tier <= 1)) { double d = std::hypot(ar.nodes[i].x - ar.nodes[i - 1].x, ar.nodes[i].y - ar.nodes[i - 1].y); len += d; if (ar.nodes[i].tier == 1) lm += d; sw += ar.nodes[i].sin; ++c; }
        std::printf("  %-9s length %6.2f kpc (measured %5.2f) ; mean sigma_in %.3f kpc ; %.3e baryons per kpc ; excess/footprint(2s) = %.3f%%\n", ar.name.c_str(), len, lm, c ? sw / c : 0, len > 0 ? A[a].F2 / len : 0, A[a].F2 > 0 ? 100.0 * A[a].E / A[a].F2 : 0);
    }
    std::printf("\nthin+gas pool %.4e ; arms +-2s %.4e (%.2f%% of pool) ; arms +-1s %.4e (%.2f%%) ; excess %.4e (%.3f%% of pool)\n", Nt + Ng, sumF2, 100 * sumF2 / (Nt + Ng), sumF1, 100 * sumF1 / (Nt + Ng), sumE, 100 * sumE / (Nt + Ng));
    std::printf("\nwrote %s\n", measured_only ? "object_allotment_measured.csv" : "object_allotment.csv");
    return 0;
}
