// GOM07 blank-slate pass (2026-10-13). Registration: GOM07_RESET_ASSESSMENT_2026-10-13.md sections 0-2 (written before this file existed).
// Reflection table, P2 cost-benefit numbers, and the stamp-versus-observer-term benchmark table. No G: depths from N_b x koppa_per_baryon.
// Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>
using namespace sdt::laws;
namespace M = sdt::laws::measured;
int main() {
    std::printf("GOM07 blank-slate pass (registered in GOM07_RESET_ASSESSMENT_2026-10-13.md)\n=======================================================================\n\n");
    const double c = M::c, kpb = bridge::koppa_per_baryon, mp = M::m_p;
    auto koppa = [&](double kg) { return kg / mp * kpb; };   // native census route: N_b x koppa per baryon
    const double kS = 1476.351201, kS_eng = bridge::koppa_Sun, AU = M::AU, RS = M::R_Sun;
    const double Mj = 1.898e27, Mv = 4.867e24, Me = 5.972e24, Mio = 8.932e22, Mca = 1.076e23;
    const double kJ = koppa(Mj), kV = koppa(Mv), kE = koppa(Me), kIo = koppa(Mio), kCa = koppa(Mca);
    const double RJ = 7.1492e7, RV = 6.0518e6, RE = 6.371e6, aIo = 4.217e8, aCa = 1.8827e9, RIo = 1.8216e6, RCa = 2.4103e6;   // census inputs typed from standard values (D3)
    std::printf("koppa_per_baryon = %.6e m ; koppa (m): Sun %.4f (GOM26) / %.4f (engine) ; Jupiter %.4f ; Venus %.5f ; Earth %.5f ; Io %.3e ; Callisto %.3e\n\n", kpb, kS, kS_eng, kJ, kV, kE, kIo, kCa);
    auto v = [&](double z) { return c * z; };
    std::printf("REFLECTION TABLE (m/s): flat stamp (Sun at its surface) %.3f ; naive-climb additions:\n", v(kS / RS));
    std::printf("  Venus  : +%.4f (own well) -> %.3f\n  Jupiter: +%.4f (own well) -> %.3f\n", v(kV / RV), v(kS / RS + kV / RV), v(kJ / RJ), v(kS / RS + kJ / RJ));
    const double io = v(kJ / aIo), ca = v(kJ / aCa); std::printf("  Io (jovian well at its orbit): +%.4f ; Callisto: +%.4f ; Io - Callisto = %.4f m/s (prompt known answer 0.78: %s)\n", io, ca, io - ca, std::fabs((io - ca) / 0.78 - 1) < 0.05 ? "met within 5%" : "NOT MET");
    std::printf("  with the moons' own wells added: Io %.4f, Callisto %.4f ; difference %.4f\n\n", io + v(kIo / RIo), ca + v(kCa / RCa), (io + v(kIo / RIo)) - (ca + v(kCa / RCa)));
    std::printf("P2: Jupiter naive-climb addition %.3f m/s = %.2f x the stated floor 1.5 m/s ; Io - Callisto %.3f m/s = %.2f x the +-0.2 m/s of a Galilean follow-up (%.1f sigma); Venus addition %.3f m/s\n\n", v(kJ / RJ), v(kJ / RJ) / 1.5, io - ca, (io - ca) / 0.2, (io - ca) / 0.2, v(kV / RV));
    // P3
    struct B { const char* nm; double zemit, zobs; };
    const double rE = AU, rJ = 5.2 * AU, rP = 0.046 * AU;
    const double zSun_E = kS / rE, zSun_J = kS / rJ, zSun_P = kS / rP, zE_own = kE / RE;
    B bs[3] = {{"B1 solar surface seen from Earth (1 AU)", kS / RS, zSun_E + zE_own}, {"B2 solar surface seen from 0.046 AU (Parker depth)", kS / RS, zSun_P}, {"B3 Jupiter ionosphere emission (R_J, 5.2 AU) seen from Earth", kJ / RJ + zSun_J, zSun_E + zE_own}};
    std::printf("P3 BENCHMARKS (m/s): stamp S = c z_emit ; observer-term O = c (z_emit - z_obs) ; observer term c z_obs ; S - O\n");
    for (auto& b : bs) std::printf("  %-62s S %9.3f  O %9.3f  c z_obs %8.3f  S-O %8.3f\n", b.nm, v(b.zemit), v(b.zemit - b.zobs), v(b.zobs), v(b.zobs));
    std::printf("\nConvergence test (F2): S and O differ by the observer term at every benchmark (%.3f, %.3f, %.3f m/s): the readings do not converge.\n", v(bs[0].zobs), v(bs[1].zobs), v(bs[2].zobs));
    std::printf("Solar reference from the engine: depth_closure::z_spectral_Sun c = %.3f m/s ; GOM26 invariant c z = %.3f m/s ; clock_rate(z_Sun) = 1 - %.4e\n", v(depth_closure::z_spectral_Sun), v(kS / RS), kS / RS);
    return 0;
}
