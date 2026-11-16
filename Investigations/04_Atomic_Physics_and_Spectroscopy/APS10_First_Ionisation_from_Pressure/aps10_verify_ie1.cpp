// APS10 — re-verification of the engine's APS14 dodecardinal closure against APS10's gates.
// Pre-registration: PROMPT.md, section "Pre-registration (2026-10-03)".
// Run from the repository root:
//   aps10_verify_ie1 Investigations/04_Atomic_Physics_and_Spectroscopy/APS14_Nuclear_Z_Celestial_Atom/data/ionisation.csv
// Build: cl /std:c++20 /EHsc /O2 /I Engine\include aps10_verify_ie1.cpp
#include <sdt/laws.hpp>

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

namespace dd = sdt::laws::atomic::dodecardinal;
using sdt::laws::measured::Ry_eV;

namespace {
bool near(double a, double b, double rel) { return std::fabs(a - b) <= rel * std::fabs(b); }

struct Row { std::string symbol; double ie_meas; };

std::map<int, Row> load_ie1(const char* path) {
    std::map<int, Row> out;
    std::ifstream f(path);
    std::string line;
    std::getline(f, line);  // header: Z,symbol,step,energy_eV,status,split,source
    while (std::getline(f, line)) {
        std::vector<std::string> cell;
        std::stringstream ss(line);
        std::string tok;
        while (std::getline(ss, tok, ',')) cell.push_back(tok);
        if (cell.size() < 5) continue;
        if (std::atoi(cell[2].c_str()) != 1) continue;
        out[std::atoi(cell[0].c_str())] = {cell[1], std::atof(cell[3].c_str())};
    }
    return out;
}

double median(std::vector<double> v) {
    std::sort(v.begin(), v.end());
    const size_t n = v.size();
    return n % 2 ? v[n / 2] : 0.5 * (v[n / 2 - 1] + v[n / 2]);
}
}  // namespace

int main(int argc, char** argv) {
    const char* path = argc > 1 ? argv[1]
        : "Investigations/04_Atomic_Physics_and_Spectroscopy/APS14_Nuclear_Z_Celestial_Atom/data/ionisation.csv";
    std::printf("APS10 verification of the APS14 closure (sdt::laws::atomic::dodecardinal)\n");
    std::printf("pre-registration: PROMPT.md (2026-10-03). Label ceiling: COMPUTED.\n\n");

    int fail = 0;
    auto check = [&](const char* what, bool ok) {
        std::printf("  [%s] %s\n", ok ? "ok" : "FAIL", what);
        if (!ok) ++fail;
    };
    std::printf("INSTRUMENT VALIDATION (closed-form one-electron limits; anchors not yet opened)\n");
    const dd::State h = dd::solve_state(1, 1);
    const dd::State heplus = dd::solve_state(2, 1);
    std::printf("  H   : %.6f eV vs -Ry = %.6f, converged=%d, residual=%.2e\n", h.energy_eV, -Ry_eV, h.converged, h.force_residual);
    std::printf("  He+ : %.6f eV vs -4Ry = %.6f, converged=%d, residual=%.2e\n", heplus.energy_eV, -4.0 * Ry_eV, heplus.converged, heplus.force_residual);
    check("H ground state = -Ry to 1e-6", h.converged && near(h.energy_eV, -Ry_eV, 1e-6));
    check("He+ ground state = -4 Ry to 1e-6", heplus.converged && near(heplus.energy_eV, -4.0 * Ry_eV, 1e-6));
    if (fail) {
        std::printf("\nVALIDATION FAILED: instrument fault, no result reported.\n");
        return 2;
    }
    std::printf("VALIDATION PASS\n\n");

    const auto meas = load_ie1(path);
    if (meas.empty()) {
        std::printf("anchor file not read: %s\n", path);
        return 3;
    }

    std::vector<double> err;
    std::map<int, double> pred;
    double worst_residual = 0.0;
    bool all_converged = true;
    std::printf("%-3s %-3s %10s %10s %9s %9s %10s\n", "Z", "sym", "IE1_pred", "IE1_meas", "err %", "converged", "residual");
    for (int Z = 2; Z <= 10; ++Z) {
        const auto it = meas.find(Z);
        if (it == meas.end()) { std::printf("Z=%d: no measured row\n", Z); return 3; }
        const dd::State neutral = dd::solve_state(Z, Z);
        const dd::State ion = dd::solve_state(Z, Z - 1);
        const double ie = ion.energy_eV - neutral.energy_eV;
        pred[Z] = ie;
        const double e = 100.0 * std::fabs(ie - it->second.ie_meas) / it->second.ie_meas;
        err.push_back(e);
        const bool conv = neutral.converged && ion.converged;
        all_converged = all_converged && conv;
        const double res = std::max(neutral.force_residual, ion.force_residual);
        worst_residual = std::max(worst_residual, res);
        std::printf("%-3d %-3s %10.4f %10.4f %9.3f %9s %10.2e\n", Z, it->second.symbol.c_str(), ie, it->second.ie_meas, e, conv ? "yes" : "NO", res);
    }

    const double med = median(err);
    const double mx = *std::max_element(err.begin(), err.end());

    std::printf("\nperiod trend (sign of IE1(Z+1) - IE1(Z), predicted vs measured):\n");
    int sign_fail = 0;
    for (int Z = 2; Z <= 9; ++Z) {
        const double dp = pred[Z + 1] - pred[Z];
        const double dm = meas.at(Z + 1).ie_meas - meas.at(Z).ie_meas;
        const bool ok = (dp > 0) == (dm > 0);
        if (!ok) ++sign_fail;
        std::printf("  %s->%s  pred %+8.3f  meas %+8.3f  %s\n", meas.at(Z).symbol.c_str(), meas.at(Z + 1).symbol.c_str(), dp, dm, ok ? "agree" : "DISAGREE");
    }

    std::printf("\nGATES (single pass, Z=2-10)\n");
    std::printf("  median error %.3f %% (opening gate <= 15 %%): %s\n", med, med <= 15.0 ? "inside" : "OUTSIDE");
    std::printf("  maximum error %.3f %% (opening gate <= 40 %%): %s\n", mx, mx <= 40.0 ? "inside" : "OUTSIDE");
    std::printf("  period-trend sign disagreements: %d of 8 (gate: 0)\n", sign_fail);
    std::printf("  all states converged: %s, maximum force residual %.2e (validation bound 1e-8)\n", all_converged ? "yes" : "NO", worst_residual);
    std::printf("  report-only, suite destination 5 %%: median %s, maximum %s\n", med <= 5.0 ? "inside" : "OUTSIDE", mx <= 5.0 ? "inside" : "OUTSIDE");
    const bool rejected = med > 15.0 || mx > 40.0 || sign_fail > 0;
    std::printf("\nrejection criterion: %s\n", rejected ? "MET" : "not met");
    std::printf("Z = 11-18: outside the closure domain (solve_state rejects more than 10 electrons); open per APS14.\n");
    return 0;
}
