// GOM20 reset, instrument 1 (2026-10-10): the GPS clock ledger from one koppa (depth + Law V budget).
// Record: GOM20_RESET_ASSESSMENT_2026-10-10.md. Written afresh. Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>
#include <numbers>
using namespace sdt::laws;
namespace M = sdt::laws::measured;
int main() {
    std::printf("GOM20 reset instrument 1 (2026-10-10)\n=====================================\n\n");
    const double c = M::c, R = bridge::R_Earth, v = bridge::v_Earth, P = 86164.0905 / 2, day = 86400.0, PI = std::numbers::pi;  // [MEASURED-INPUT] sidereal day
    const double Om = v * v * R / (c * c), r = std::cbrt(Om * c * c * P * P / (4 * PI * PI)), vs = c * std::sqrt(Om / r);
    int bad = 0;
    { bool ok = std::fabs(Om / bridge::koppa_Earth - 1) < 1e-12; std::printf("[V1] Om_E = %.6e m against engine koppa_Earth %.6e m -> %s\n", Om, bridge::koppa_Earth, ok ? "met" : "NOT MET"); bad += !ok; }
    { double P2 = 2 * PI * std::sqrt(r * r * r / (Om * c * c)); bool ok = std::fabs(P2 / P - 1) < 1e-12; std::printf("[V2] Kepler round trip: P = %.6f s (registered %.6f) -> %s\n", P2, P, ok ? "met" : "NOT MET"); bad += !ok; }
    { double exact = (vs * vs / (c * c)) / (1 + law_V::v_circ(vs) / c), first = vs * vs / (2 * c * c); bool ok = std::fabs(exact / first - 1) < 1e-9; std::printf("[V3] Law V loss at GPS speed: exact %.6e, first order %.6e (rel %.1e) -> %s\n\n", exact, first, exact / first - 1, ok ? "met" : "NOT MET"); bad += !ok; }
    if (bad) { std::printf("VALIDATIONS NOT MET\n"); return 1; }
    std::printf("VALIDATIONS: met\n\n");
    const double dep = (Om / R - Om / r), spd = (vs * vs / (c * c)) / (1 + law_V::v_circ(vs) / c),   /* attempt 2: stable form of 1 - v_circ/c (attempt 1 G0: cancellation) */ net = dep - spd;
    std::printf("Om_E = %.6e m ; r_GPS = %.1f km (altitude %.1f km) ; v_GPS = %.2f m/s\n", Om, r / 1e3, (r - R) / 1e3, vs);
    std::printf("depth term  +%.4f us/day (fractional %.4e) ; anchor +45.9\n", dep * day * 1e6, dep);
    std::printf("speed term  -%.4f us/day (fractional %.4e) ; anchor -7.2\n", spd * day * 1e6, spd);
    std::printf("net         +%.4f us/day (fractional %.5e)\n\n", net * day * 1e6, net);
    const double anchor = (10.23e6 - 10.22999999543e6) / 10.23e6;    // [MEASURED-INPUT, IS-GPS-200 factory offset; recalled, tagged B]
    double d = (net - anchor) * day * 1e6;
    std::printf("primary anchor: engineered offset %.5e = %.4f us/day ; net - anchor = %+.4f us/day -> gate (+/-0.1) %s\n", anchor, anchor * day * 1e6, d, std::fabs(d) <= 0.1 ? "MET (G4)" : "NOT MET");
    { double vrot = 2 * PI * R / 86164.0905, rot = vrot * vrot / (2 * c * c) * day * 1e6; std::printf("context (not in the registered ledger): ground-clock rotation at the equator, v = %.1f m/s, would shift the net by +%.4f us/day\n", vrot, rot); }
    return 0;
}

