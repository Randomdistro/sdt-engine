// Shadow analysis round 2: zk^2 = 1 for white dwarfs from spectra (Om_spec = (v_gr/c) R) against orbits (Om_orbit = (M_dyn/M_Sun) Om_Sun).
// Pre-registration: ../SHADOW_ANALYSIS_ROUND2_2026-10-09_PRE_REGISTRATION.md. Om = R/k^2 (older files: koppa).
// Om_Sun from the engine's Mercury route; M_dyn/M_Sun from Kepler III in AU and years (no G).
// Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>
using namespace sdt::laws;
namespace M = sdt::laws::measured;

int main() {
    std::printf("Shadow analysis round 2: zk^2 = 1 for white dwarfs (2026-10-09)\n================================================================\n\n");
    const double c = M::c, OmS = bridge::koppa_Sun_from_precession, RS = M::R_Sun;
    // [V] instrument check on the Sun: Om_spec built from z = Om_Sun/R_Sun and R = R_Sun, M = 1 must return zk^2 = 1
    { double v = c * OmS / RS, zk2 = (v / c) * RS / (1.0 * OmS); bool ok = std::fabs(zk2 - 1) < 1e-14;
      std::printf("[V] Sun built from its own Om: zk^2 - 1 = %.1e -> %s\n\n", zk2 - 1, ok ? "met" : "NOT MET"); if (!ok) return 1; }
    struct Row { const char* star; const char* src; double v, sv, Rf, sRf, Md, sMd; };
    const Row rows[] = {   // [MEASURED-INPUT] v_gr km/s; R in R_Sun (flux + parallax); M_dyn in M_Sun (visual-binary orbit)
        {"Sirius B", "Greenstein et al. 1971",      89.0, 16.0,  0.00803, 0.00011, 1.018, 0.011},
        {"Sirius B", "Barstow et al. 2005",         80.42, 4.83, 0.00803, 0.00011, 1.018, 0.011},
        {"Sirius B", "Joyce et al. 2018",           80.65, 0.77, 0.00803, 0.00011, 1.018, 0.011},
        {"40 Eri B", "Koester & Weidemann 1991",    26.5,  1.5,  0.01308, 0.00020, 0.573, 0.018},
        {"40 Eri B", "Reid 1996",                   25.8,  1.4,  0.01308, 0.00020, 0.573, 0.018},
    };
    std::printf("Om_Sun = %.4f m (engine, Mercury route); R_Sun = %.4e m\n\n", OmS, RS);
    std::printf("%-9s %-26s %10s %10s %12s %16s %8s %s\n", "star", "redshift source", "z", "Om_spec m", "Om_orbit m", "zk^2", "dev", "result");
    int in2 = 0, n = 0;
    for (auto& r : rows) {
        double z = r.v * 1e3 / c, R = r.Rf * RS, Osp = z * R, Oor = r.Md * OmS, q = Osp / Oor;
        double sq = q * std::sqrt(std::pow(r.sv / r.v, 2) + std::pow(r.sRf / r.Rf, 2) + std::pow(r.sMd / r.Md, 2)), dev = (q - 1) / sq;
        bool ok = std::fabs(dev) <= 2; in2 += ok; ++n;
        std::printf("%-9s %-26s %10.4e %10.2f %12.2f %8.4f +/- %.4f %+7.2fs %s\n", r.star, r.src, z, Osp, Oor, q, sq, dev, ok ? "confirmed" : "rejected");
    }
    std::printf("\nwithin 2 sigma: %d of %d (expectation ~95%%)\n", in2, n);
    std::printf("excluded by the registered criteria: Procyon B (no measured gravitational redshift: no detectable H-alpha; Bond et al. 2015 predict 30.46 +/- 0.85 km/s)\n");
    return 0;
}
