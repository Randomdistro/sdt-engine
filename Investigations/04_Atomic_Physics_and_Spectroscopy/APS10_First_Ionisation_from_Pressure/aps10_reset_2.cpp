// APS10 next round (2026-10-14): higher sequential ionisations Z = 2-10 from the engine's dodecardinal solver.
// Registration: APS10_RESET_ASSESSMENT_2026-10-14.md sections 0-2 (written before this file existed).
// Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <vector>
using namespace sdt::laws;
namespace D = sdt::laws::atomic::dodecardinal;
static std::map<int, std::vector<double>> loadIE(const char* path) {   // minimal reader for {"Z": [v1, v2, ...], ...}
    std::ifstream f(path, std::ios::binary); std::string s((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>()); std::map<int, std::vector<double>> m; size_t p = 0;
    while ((p = s.find('"', p)) != std::string::npos) { size_t q = s.find('"', p + 1); int z = std::stoi(s.substr(p + 1, q - p - 1)); size_t a = s.find('[', q), b = s.find(']', a); std::stringstream ss(s.substr(a + 1, b - a - 1)); std::string tok; std::vector<double> v; while (std::getline(ss, tok, ',')) if (tok.find_first_of("0123456789") != std::string::npos) v.push_back(std::stod(tok)); m[z] = v; p = b; }
    return m; }
static double med(std::vector<double> v) { std::sort(v.begin(), v.end()); size_t n = v.size(); return n ? (n % 2 ? v[n / 2] : 0.5 * (v[n / 2 - 1] + v[n / 2])) : 0; }
struct R { int Z, s; double pred, meas, err; bool hyd, first; };
int main() {
    std::printf("APS10 next round: higher sequential ionisations (registered in APS10_RESET_ASSESSMENT_2026-10-14.md)\n=======================================================================\n\n");
    const double Ry = 13.605693122994; int fails = 0;
    auto h1 = D::solve_state(1, 1), h2 = D::solve_state(2, 1);
    bool v = h1.converged && h2.converged && std::fabs(h1.energy_eV / (-Ry) - 1) < 1e-6 && std::fabs(h2.energy_eV / (-4 * Ry) - 1) < 1e-6;
    std::printf("[V] solve_state(1,1) = %.6f eV, solve_state(2,1) = %.6f eV -> %s\n", h1.energy_eV, h2.energy_eV, v ? "met" : "NOT MET"); if (!v) ++fails;
    auto ie = loadIE("Datasets/nuclear/ionisation_energies.json");
    std::vector<R> rs; int nonconv = 0; double maxres = 0;
    for (int Z = 2; Z <= 10; ++Z) {
        std::vector<double> E(Z + 1, 0.0);
        for (int N = 1; N <= Z; ++N) { auto st = D::solve_state(Z, N); if (!st.converged || !(st.force_residual < 1e-8)) ++nonconv; maxres = std::max(maxres, st.force_residual); E[N] = st.energy_eV; }
        E[0] = 0.0;
        for (int s = 1; s <= Z; ++s) { double pred = E[Z - s] - E[Z - s + 1]; double meas = ie.at(Z).at(s - 1); rs.push_back({Z, s, pred, meas, (pred - meas) / meas, s == Z, s == 1}); }
    }
    std::printf("states solved: non-converged or residual >= 1e-8: %d ; max force residual %.2e\n\n Z  s   IE_pred (eV)   IE_meas (eV)    error\n", nonconv, maxres);
    for (auto& r : rs) std::printf("%2d %2d  %12.4f  %12.4f  %+8.2f%%%s\n", r.Z, r.s, r.pred, r.meas, 100 * r.err, r.hyd ? "  (hydrogenic)" : "");
    auto stat = [&](const char* nm, auto pick) { std::vector<double> e; for (auto& r : rs) if (pick(r)) e.push_back(std::fabs(r.err)); double md = med(e), mx = *std::max_element(e.begin(), e.end()); std::printf("%-34s n %2zu  median %6.2f%%  max %6.2f%%\n", nm, e.size(), 100 * md, 100 * mx); return std::make_pair(md, mx); };
    std::printf("\n");
    stat("all 54", [](const R&) { return true; });
    stat("first ionisations (opening set)", [](const R& r) { return r.first; });
    auto h = stat("higher stages (the 45)", [](const R& r) { return !r.first; });
    stat("many-electron higher (the 36)", [](const R& r) { return !r.first && !r.hyd; });
    stat("hydrogenic last stage (the 9)", [](const R& r) { return r.hyd; });
    int mono = 0, monoN = 0;
    for (int Z = 2; Z <= 10; ++Z) for (int s = 1; s < Z; ++s) { double p0 = 0, p1 = 0, m0 = 0, m1 = 0; for (auto& r : rs) if (r.Z == Z) { if (r.s == s) { p0 = r.pred; m0 = r.meas; } if (r.s == s + 1) { p1 = r.pred; m1 = r.meas; } } ++monoN; mono += ((p1 > p0) == (m1 > m0)); }
    std::printf("\nmonotone pairs (predicted ordering equals measured ordering): %d of %d\n", mono, monoN);
    bool opening = h.first <= 0.15 && h.second <= 0.40, dest = h.first <= 0.05 && h.second <= 0.15, allmono = mono == monoN;
    std::printf("opening gate on the 45 (median <= 15%%, max <= 40%%): %s ; monotone: %s ; destination (median <= 5%%, max <= 15%%): %s\n", opening ? "MET" : "NOT MET", allmono ? "MET" : "NOT MET", dest ? "reached" : "not reached");
    std::printf("cascade band: %s\n", (opening && allmono && dest && !fails && !nonconv) ? "G4 (COMPUTED, good)" : (opening && allmono) ? "G3" : "see gates");
    return 0;
}
