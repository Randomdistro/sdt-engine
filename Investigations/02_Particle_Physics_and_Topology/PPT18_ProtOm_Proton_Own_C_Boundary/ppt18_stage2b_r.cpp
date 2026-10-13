// PPT18 stage 2b (2026-10-12): Harvey's construction — conserve 1836 electron closure-tube volumes into a four-loop
// twined bundle inside the 1.68 fm envelope, one poloidal traversal per loop. Registration: PROMPT.md addendum (b).
// Round r (2026-10-12): Harvey ruling — the 720-degree closure is a flip connection made within ONE tour;
// the electron tube is one Bohr orbit long (2 pi a0), half of canon PPT17's 4 pi a0. Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>
#include <numbers>
using namespace sdt::laws;
namespace M = sdt::laws::measured;
static const double PI = std::numbers::pi, S2 = std::numbers::sqrt2;
static double Rp_fm() { return law_III::R_p_lock * 1e15; }
static double strand_len(double b) { double a = S2 * b, R = Rp_fm() - a - b; return 4 * std::sqrt(std::pow(2 * PI * R, 2) + std::pow(2 * PI * a, 2)); }
static double vol(double b) { return PI * b * b * strand_len(b); }          // fm^3
static bool ring(double b) { double a = S2 * b, R = Rp_fm() - a - b; return R > a && a > 0; }
static double bmax_ring() { return Rp_fm() / (2 * S2 + 1); }               // R = a  <=>  Rp - a - b = a, a = sqrt2 b
static double solve(double V) {                                            // smallest b with vol(b) = V on the ring branch
    double lo = 1e-9, hi = bmax_ring();
    if (vol(hi) < V) return -1;                                            // does not fit (vol rises then falls? checked below)
    for (int i = 0; i < 200; ++i) { double m = 0.5 * (lo + hi); (vol(m) < V ? lo : hi) = m; }
    return 0.5 * (lo + hi);
}
int main() {
    std::printf("PPT18 stage 2b-r (2026-10-12): four-loop construction, one-orbit electron tube\n===================================================================\n");
    const double a0 = M::a_0, be_canon = law_VI::winding::r_electron_body_open, ratio = M::m_p / M::m_e;
    auto Ve_fm3 = [&](double be) { return PI * be * be * 2 * PI * a0 * 1e45; };   // one orbit (ruling)
    { double v = Ve_fm3(be_canon) * 1e-45, e = 0.5 * law_VI::mass_ratio::electron_orbit_tube_volume(be_canon); bool ok = std::fabs(v / e - 1) < 1e-12;   // half of canon 720-degree tube
      std::printf("[V1] V_e(b_e) = %.6e m^3 vs canon %.6e -> %s\n", v, e, ok ? "met" : "NOT MET"); if (!ok) return 1; }
    { double bt = 0.1, b = solve(vol(bt)); bool ok = std::fabs(b / bt - 1) < 1e-9; std::printf("[V2] planted b = 0.1 fm recovered %.10f -> %s\n", b, ok ? "met" : "NOT MET"); if (!ok) return 1; }
    // monotonicity of vol on the ring branch (so bisection is valid)
    { bool mono = true; double prev = 0; for (int i = 1; i <= 1000; ++i) { double b = bmax_ring() * i / 1000.0, v = vol(b); if (v < prev) mono = false; prev = v; }
      std::printf("[V3a] vol(b) monotone on the ring branch: %s ; ring branch b < %.5f fm ; max bundle volume %.5f fm^3\n", mono ? "yes" : "NO", bmax_ring(), vol(bmax_ring())); }
    const double Rp = Rp_fm();
    std::printf("\nEnvelope: outer radius R_p_lock = %.5f fm (diameter %.4f fm). Proton sphere volume %.4f fm^3.\n", Rp, 2 * Rp, 4.0 / 3 * PI * Rp * Rp * Rp);
    std::printf("Packing count: m_p/m_e = %.5f (canon 6pi^5 = %.5f)\n\n", ratio, law_VI::mass_ratio::six_pi_5);
    std::printf("   b_e (m)      V_e (fm^3)     V_p = 1836 V_e (fm^3)   fits?   b (fm)    a (fm)    R (fm)    v_P/c     Om_p (fm)  z_p@2R_p\n");
    const double bes[] = {1e-21, 3e-21, 1e-20, 2e-20, 2.5e-20, be_canon, 5e-20, 1e-19};
    for (double be : bes) {
        double Vp = ratio * Ve_fm3(be), b = solve(Vp);
        if (b < 0) { std::printf("   %.2e   %.4e     %.4e             NO (exceeds max %.4f)\n", be, Ve_fm3(be), Vp, vol(bmax_ring())); continue; }
        double a = S2 * b, R = Rp - a - b, vP = 2 * PI * a / std::sqrt(std::pow(2 * PI * R, 2) + std::pow(2 * PI * a, 2)), O = a * vP * vP;
        bool okR = std::fabs((R + a + b) / Rp - 1) < 1e-12;
        std::printf("   %.2e   %.4e     %.4e             yes     %.5f   %.5f   %.5f   %.5f   %.6f   %.6f %s%s\n", be, Ve_fm3(be), Vp, b, a, R, vP, O, O / (2 * Rp), okR ? "" : "[V3 NOT MET]", be == be_canon ? "  <- canon b_e" : "");
    }
    double be_max = be_canon * std::sqrt(vol(bmax_ring()) / (ratio * Ve_fm3(be_canon)));
    std::printf("\nLargest b_e whose 1836 V_e fits the four-loop bundle as a ring inside R_p: %.4e m (canon b_e = %.1e m is %.2fx that)\n", be_max, be_canon, be_canon / be_max);
    return 0;
}
