// GD03 blank-slate run 1 (2026-10-10). Registration: GD03_RESET_ASSESSMENT_2026-10-10.md sections 0-2 (written before this file existed).
// Zone table (engine-defined and labelled-observed rows), zk^2, the GOM25 domain gate 0 <= z < 1, tau = 1/d, and a banner computed from the gate results.
// Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>
#include <string>
#include <vector>
using namespace sdt::laws;
namespace M = sdt::laws::measured;

int main() {
    std::printf("GD03 blank-slate run 1 (registered in GD03_RESET_ASSESSMENT_2026-10-10.md sections 0-2)\n=======================================================================\n\n");
    const double c = M::c; int fails = 0;
    // V1
    { double w = 0; for (double f = 1e-8; f <= 1.8; f *= 10) { double v = f * c, k = c / v, z = (v / c) * (v / c); w = std::fmax(w, std::fabs(z * k * k - 1)); } double v = 1.8 * c, k = c / v, z = (v / c) * (v / c); w = std::fmax(w, std::fabs(z * k * k - 1)); bool ok = w < 1e-12; std::printf("[V1] zk^2 - 1, worst over v = 1e-8 c ... 1.8 c: %.2e -> %s\n", w, ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    { bool ok = std::fabs(bridge::k_hydrogen * M::alpha - 1) < 1e-12 && std::fabs(bridge::koppa_hydrogen / (M::alpha * M::alpha * M::a_0) - 1) < 1e-12; std::printf("[V2] k_hydrogen = 1/alpha and koppa_hydrogen = alpha^2 a_0 in laws.hpp -> %s\n\n", ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    if (fails) { std::printf("VALIDATIONS NOT MET -> G0\n"); return 1; } std::printf("VALIDATIONS: met\n\n");
    struct Z { const char* nm; const char* src; double v, R; } zs[6] = {
        {"hydrogen ground state", "engine", M::alpha * c, M::a_0},
        {"proton surface", "engine", c / bridge::k_proton_surface, M::R_p},
        {"Earth surface", "engine", bridge::v_Earth, bridge::R_Earth},
        {"Sun surface", "engine", c / bridge::k_Sun, M::R_Sun},
        {"Milky Way solar circle", "OBSERVED (IAU 220 km/s, 8 kpc)", 220e3, 8.0 * 3.0856775814913673e19},
        {"S2 at periapsis", "OBSERVED (~7650 km/s, ~120 AU)", 7.65e6, 120.0 * 1.495978707e11}};
    int inDomain = 0; std::printf("%-26s %-34s %-12s %-12s %-12s %-14s %-16s %s\n", "zone boundary", "source", "v/c", "k", "z", "koppa [m]", "zk^2", "0<=z<1");
    for (auto& z : zs) { double k = c / z.v, zz = (z.v / c) * (z.v / c), kop = z.v * z.v * z.R / (c * c); bool dom = zz >= 0 && zz < 1; if (dom) ++inDomain; std::printf("%-26s %-34s %-12.6e %-12.6e %-12.6e %-14.6e %-16.12f %s\n", z.nm, z.src, z.v / c, k, zz, kop, zz * k * k, dom ? "yes" : "NO (rejected)"); }
    std::printf("\nrows inside the domain 0 <= z < 1: %d of 6\n", inDomain);
    std::printf("tau = 1/d: d = 1, 2, 3 -> %.6f %.6f %.6f (arithmetic; the 3-d value is 1/3 = %.12f)\n\n", 1.0, 0.5, 1.0 / 3.0, 1.0 / 3.0);
    // banner from gates
    bool L1 = true; for (auto& z : zs) { double k = c / z.v, zz = (z.v / c) * (z.v / c); if (std::fabs(zz * k * k - 1) > 1e-12) L1 = false; }
    bool L2 = false, L3 = false, L4 = false, domainAll = (inDomain == 6);
    std::printf("BANNER (computed from the gate results):\n  Level 1 (zk^2 = 1): %s (identity by construction, not a test)\n  Level 2 (probe-distance invariance): PENDING (observed orbits not local; the local ephemeris is a model output)\n  Level 3 (parent invariance, >= 3 independent probes, sigma/mu < 1%%): PENDING (planetary elements, S-star orbits with distance, Milky Way rotation curve, Laniakea probes)\n  Level 4 (predictive closure, drag coefficient from lattice geometry): OWED (no derivation to run)\n  Condition A: %s ; B (tau = 1/3): arithmetic ; C (bonding overlap): not defined in the portion read ; D (one formula, z continuous): %s\n", L1 ? "met (identity)" : "NOT MET", L1 ? "met (identity)" : "NOT MET", domainAll ? "met" : "the single formula z = (v/c)^2 gives z > 1 at the proton surface; the (1 - z)^2 profile domain rule rejects it (tension)");
    (void)L2; (void)L3; (void)L4;
    return 0;
}
