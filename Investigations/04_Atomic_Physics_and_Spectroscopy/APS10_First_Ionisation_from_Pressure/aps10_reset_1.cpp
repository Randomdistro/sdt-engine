// APS10 reset, instrument 1 (2026-10-10): engine first-ionisation closure Z=2-10 against measured IE1. Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>
using namespace sdt::laws;
namespace D = sdt::laws::atomic::dodecardinal;
int main() {
    std::printf("APS10 reset instrument 1 (2026-10-10)\n=====================================\n\n");
    const double Ry = 13.605693122994;  // eV, CODATA
    auto h1 = D::solve_state(1, 1), h2 = D::solve_state(2, 1);
    bool v = h1.converged && h2.converged && std::fabs(h1.energy_eV / (-Ry) - 1) < 1e-6 && std::fabs(h2.energy_eV / (-4 * Ry) - 1) < 1e-6;
    std::printf("[V] solve_state(1,1) = %.6f eV (-Ry %.6f), solve_state(2,1) = %.6f eV (-4Ry %.6f), converged %d %d -> %s\n", h1.energy_eV, -Ry, h2.energy_eV, -4 * Ry, h1.converged, h2.converged, v ? "met" : "NOT MET");
    const double meas[11] = {0, 13.59844, 24.58738, 5.39171, 9.32269, 8.29803, 11.2603, 14.53414, 13.61806, 17.42282, 21.5646};  // [MEASURED-INPUT, Datasets/nuclear/ionisation_energies.json]
    double maxres = 0; std::vector<double> err; double pred[11] = {};
    std::printf("\n Z  IE1_pred (eV)  IE1_meas (eV)   error\n");
    for (int Z = 2; Z <= 10; ++Z) { auto a = D::solve_state(Z, Z), b = D::solve_state(Z, Z - 1); maxres = std::max({maxres, a.force_residual, b.force_residual}); pred[Z] = b.energy_eV - a.energy_eV;
        double e = (pred[Z] - meas[Z]) / meas[Z]; err.push_back(std::fabs(e)); std::printf("%2d  %12.4f  %12.4f  %+7.2f%%\n", Z, pred[Z], meas[Z], 100 * e); }
    std::printf("max force residual over scored states: %.2e -> %s\n\n", maxres, maxres < 1e-8 ? "met" : "NOT MET");
    std::vector<double> s = err; std::sort(s.begin(), s.end()); double med = s[s.size() / 2], mx = s.back();
    int signs = 0; std::printf("pair signs (pred vs meas):"); for (int Z = 2; Z < 10; ++Z) { bool ok = ((pred[Z + 1] - pred[Z]) > 0) == ((meas[Z + 1] - meas[Z]) > 0); signs += ok; std::printf(" %d-%d:%s", Z, Z + 1, ok ? "ok" : "X"); } std::printf("\n");
    std::printf("\nmedian |error| %.2f%% (gate <= 15%%), max %.2f%% (gate <= 40%%), signs %d/8 consecutive pairs... (registered: all pairs Z=2..10)\n", 100 * med, 100 * mx, signs);
    bool pass = med <= 0.15 && mx <= 0.40 && signs == 8;
    std::printf("opening gate -> %s ; suite 5%% destination: median %s, max %s\n", pass ? "MET" : "NOT MET", med <= 0.05 ? "within" : "outside", mx <= 0.05 ? "within" : "outside");
    return 0;
}
