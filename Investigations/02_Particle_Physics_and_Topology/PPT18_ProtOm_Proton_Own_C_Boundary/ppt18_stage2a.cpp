// PPT18 stage 2a (2026-10-12): canon-consistent windings (aspect law + filament envelope R+a = R_p_lock) and Om_p.
// Registration: PROMPT.md addendum 2026-10-12. Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>
using namespace sdt::laws;
namespace M = sdt::laws::measured;
int main() {
    const double fm = 1e-15, Rp = law_III::R_p_lock / fm, lbar = M::hbar / (M::m_p * M::c) / fm, re = M::r_e / fm;
    std::printf("PPT18 stage 2a (2026-10-12)\n===========================\n");
    { bool ok = std::fabs(law_VI::topology::aspect_ratio(2, 3) - std::sqrt(1.5)) < 1e-15 && std::fabs(law_VI::topology::v_poloidal(2, 3) / M::c - std::sqrt(0.6)) < 1e-15;
      std::printf("[V1] canon aspect/v_P for (2,3) reproduced -> %s\n", ok ? "met" : "NOT MET"); if (!ok) return 1; }
    { double k = law_VI::topology::aspect_ratio(4, 5), a = Rp / (1 + k), R = k * a; bool ok = std::fabs((R + a) / Rp - 1) < 1e-15 && std::fabs(R / a - k) < 1e-14;
      std::printf("[V2] envelope construction closes (R+a = R_p_lock, R/a = aspect) -> %s\n\n", ok ? "met" : "NOT MET"); if (!ok) return 1; }
    std::printf("R_p_lock = %.5f fm ; lbar_p = %.5f fm (D3) ; z_H at contact = r_e/(2R_p_lock) = %.4f\n\n", Rp, lbar, re / (2 * Rp));
    std::printf("  (p,q)   R/a      R (fm)    a (fm)   C1 ring?   v_P (c)   Om_p = a vP^2 (fm)   Om_p/R_p   Om_p/R   z_p at contact   C2 p=4?\n");
    for (auto [p, q] : {std::pair{2, 3}, std::pair{4, 5}, std::pair{4, 3}}) {
        double k = law_VI::topology::aspect_ratio(p, q), a = Rp / (1 + k), R = k * a, v = law_VI::topology::v_poloidal(p, q) / M::c, O = a * v * v;
        std::printf("  (%d,%d)  %.4f   %.4f    %.4f    %-9s  %.4f    %.5f              %.4f     %.4f   %.4f           %s\n",
                    p, q, k, R, a, R > a ? "yes" : "NO (R<=a)", v, O, O / Rp, O / R, O / (2 * Rp), p == 4 ? "yes" : "no (flag)");
    }
    return 0;
}
