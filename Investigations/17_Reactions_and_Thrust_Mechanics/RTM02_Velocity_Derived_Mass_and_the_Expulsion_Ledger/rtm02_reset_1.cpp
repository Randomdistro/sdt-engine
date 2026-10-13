// RTM02 reset, instrument 1 (2026-10-10): Law V gearing, expulsion ledgers, hover-price sweep. Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>
using namespace sdt::laws; namespace M = sdt::laws::measured;
int main() {
    const double c = M::c, g = bridge::v_Earth * bridge::v_Earth / bridge::R_Earth, day = 86400.0;
    std::printf("RTM02 reset instrument 1 (2026-10-10)\n=====================================\ng = v_E^2/R_E = %.4f m/s^2 (native, no G)\n\n", g);
    double w = 0; for (int i = 1; i < 1000; ++i) { double v = c * i / 1000.0, gear = c / law_V::v_circ(v); w = std::max(w, std::fabs(gear * std::sqrt(1 - (v / c) * (v / c)) - 1)); }
    std::printf("P1a gearing c/v_circ vs 1/sqrt(1-v^2/c^2): worst %.1e [CONSTRUCTION]\n", w);
    { double v = 1e-3; std::printf("P1b classical limit at v = 1 mm/s: gear - 1 = %.1e [CONSTRUCTION]\n", c / law_V::v_circ(v) - 1); }
    { double v = 0.6 * c, dm = c / law_V::v_circ(v) - 1, Ek = (1 / std::sqrt(1 - 0.36) - 1); std::printf("P1c dm/m_rest = %.12f vs E_k/(m c^2) = %.12f [CONSTRUCTION]\n\n", dm, Ek); }
    auto open_exp = [&](double vex) { double vc = law_V::v_circ(vex); return g * day * vc / (c * vex) / std::log(10.0); };   // log10 mass ratio per day
    auto closed_exp = [&](double vex) { (void)vex; return 0.0; };
    double e45 = open_exp(4500.0);
    std::printf("P2 open ledger at v_ex = 4.5 km/s: hover price 10^%.3f per day (RTM01 anchor 10^81.9) -> %s\n", e45, std::fabs(e45 - 81.9) <= 0.1 ? "consistent within 0.1" : "NOT within 0.1");
    { double vex = 0.5 * c, gear = c / law_V::v_circ(vex), mom_per_rest = gear * vex, mom_per_total = mom_per_rest / gear; std::printf("P2 closed ledger at 0.5c: momentum per unit total expended mass = %.6f c (= v_ex/c %.6f) [CONSTRUCTION: gearing cancels]\n", mom_per_total / c, vex / c); }
    std::printf("   price floor (closed ledger, photon rocket): 10^%.6f per day = exp(g t / c)\n\n", g * day / c / std::log(10.0));
    std::printf("P3 sweep (log10 hover mass ratio per day):\n   v_ex            open ledger    closed ledger (momentum per total mass = v_ex)\n");
    for (double vex : {4500.0, 5.0e4, 1.0e6, 0.01 * c, 0.1 * c, 0.5 * c, 0.9 * c, 0.999999 * c}) { double cl = g * day / vex / std::log(10.0); std::printf("   %-12.4e   %12.6e   %12.6e\n", vex, open_exp(vex), cl); }
    std::printf("   floor exp(g t/c): %.6e\n\n", g * day / c / std::log(10.0));
    double lo = 0.1, hi = 5.0; for (int i = 0; i < 200; ++i) { double x = 0.5 * (lo + hi), f = 2 * (1 - std::exp(-x)) - x; (f > 0 ? lo : hi) = x; } double x = 0.5 * (lo + hi);
    std::printf("P5 energy-optimal v_ex/dv = 1/x with 2(1-e^-x) = x: x = %.6f -> v_ex/dv = %.6f [computed; stationarity is CONSTRUCTION]\n", x, 1 / x);
    return 0;
}
