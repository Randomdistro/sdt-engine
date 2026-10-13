// PPT18 stage 3 (2026-10-12): radiation map of the proton's own ladder (fill-limit Om_p), movers x forms x transitions.
// Registration: PROMPT.md addendum (d). No observed line is compared. Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>
#include <numbers>
#include <string>
using namespace sdt::laws;
namespace M = sdt::laws::measured;
static const char* band(double E_MeV) {
    double eV = E_MeV * 1e6;
    if (eV < 1.65) return "infrared"; if (eV < 3.3) return "visible"; if (eV < 124) return "UV/EUV"; if (eV < 1.0e5) return eV < 1e4 ? "soft X-ray" : "hard X-ray";
    if (eV < 1.0e7) return "nuclear gamma (0.1-10 MeV)"; if (eV < 1.0e8) return "high-energy gamma (10-100 MeV)"; return "very-high-energy gamma (>100 MeV)";
}
int main() {
    const double PI = std::numbers::pi, Rp = law_III::R_p_lock * 1e15, re = M::r_e * 1e15, a0 = M::a_0 * 1e15;
    const double Om = (Rp / (2 * std::numbers::sqrt2 + 1)) * std::numbers::sqrt2 / 2;   // fill limit: a = sqrt2 b, R = a, v_P^2 = c^2/2 -> Om_p = a/2
    const double a = 2 * Om;
    const double hc = M::h * M::c / M::MeV_to_J * 1e15;   // MeV fm
    const double me = M::m_e * M::c * M::c / M::MeV_to_J, mp = M::m_p * M::c * M::c / M::MeV_to_J;
    std::printf("PPT18 stage 3 (2026-10-12): radiation map of the proton's own ladder\n=====================================================================\n");
    { double ry = 0.5 * me * M::alpha * M::alpha * 1e6; bool ok = std::fabs(ry / M::Ry_eV - 1) < 1e-6; std::printf("[V1] 1/2 m_e c^2 alpha^2 = %.4f eV vs Ry %.4f -> %s\n", ry, M::Ry_eV, ok ? "met" : "NOT MET"); if (!ok) return 1; }
    { double z = 1e-6, Bf = 1 - std::sqrt(1 - z), Hf = 0.5 * z; bool ok = std::fabs(Bf / Hf - 1) < 1e-6; std::printf("[V2] budget/half at z=1e-6: %.9f -> %s\n", Bf / Hf, ok ? "met" : "NOT MET"); if (!ok) return 1; }
    { bool ok = std::fabs(hc / 1239.84198 - 1) < 1e-8; std::printf("[V3] hc = %.6f MeV fm -> %s\n\n", hc, ok ? "met" : "NOT MET"); if (!ok) return 1; }
    std::printf("Om_p = %.5f fm (fill limit, one-orbit tube) ; bundle/tour radius a = R = %.5f fm ; R_p = %.5f ; r_e = %.4f\n\n", Om, a, Rp, re);
    struct St { const char* n; double r; };
    const St S[] = {{"Om_p", Om}, {"node R_p/3", Rp / 3}, {"a=R", a}, {"R_p", Rp}, {"2R_p (contact)", 2 * Rp}, {"r_e", re}, {"a0", a0}, {"inf", INFINITY}};
    auto zp = [&](double r) { return std::isinf(r) ? 0.0 : Om / r; };
    auto zh = [&](double r) { return std::isinf(r) ? 0.0 : re / r; };
    std::printf("STATIONS: depth, speed and line shift\n  station          r (fm)      z_p (own)   v_p/c     z_H (hydrogen)  v_H/c     shift own   shift H     own+H     light speed (1-z_p)^2\n");
    for (auto& s : S) { double z = zp(s.r), h = zh(s.r);
        std::printf("  %-15s  %10.5f  %10.6f  %8.5f  %12.6f   %8.5f  %8.3f%%  %9.3f%%  %8.3f%%  %.5f c\n", s.n, s.r, z, std::sqrt(z), h, std::sqrt(h), 100 * z, 100 * h, 100 * (z + h), std::pow(1 - z, 2)); }
    struct Tr { int o, i; };   // indices into S (out -> in)
    const Tr T[] = {{7, 4}, {7, 3}, {4, 3}, {5, 3}, {3, 2}, {2, 0}, {3, 0}, {7, 0}, {3, 1}, {6, 3}};
    struct Mv { const char* n; double m; };
    const Mv MV[] = {{"electron m_e", me}, {"proton m_p", mp}, {"one loop m_p/4", mp / 4}};
    for (auto& mv : MV) {
        std::printf("\nMOVER: %s (%.6f MeV)\n  transition (out -> in)        dz_p        F full (MeV)   H half (MeV)   B budget (MeV)   lambda_F (fm)   lambda_H (fm)   lambda_B (fm)   band (H)                         L*_H (fm)   L*_H/(2 pi r_in)\n", mv.n, mv.m);
        for (auto& t : T) { double zo = zp(S[t.o].r), zi = zp(S[t.i].r), dz = zi - zo;
            double F = mv.m * dz, H = 0.5 * F, B = (zi <= 1 && zo <= 1) ? mv.m * (std::sqrt(1 - zo) - std::sqrt(1 - zi)) : NAN;
            double vin = std::sqrt(zi), Lh = (hc / H) * vin / 2;
            std::string tn = std::string(S[t.o].n) + " -> " + S[t.i].n;
            std::printf("  %-28s  %9.6f   %12.6g   %12.6g   %13.6g   %13.6g   %13.6g   %13.6g   %-31s  %10.4g   %10.4g\n", tn.c_str(), dz, F, H, B, hc / F, hc / H, hc / B, band(H), Lh, Lh / (2 * PI * S[t.i].r)); }
    }
    std::printf("\nHYDROGEN-LADDER COMPARISON (same stations, electron, z_H = r_e/r; B undefined for z_H > 1):\n  transition                    dz_H         F (MeV)        H (MeV)        band (H)\n");
    for (auto& t : T) { double dz = zh(S[t.i].r) - zh(S[t.o].r), F = me * dz; std::string tn = std::string(S[t.o].n) + " -> " + S[t.i].n;
        std::printf("  %-28s  %10.5f   %12.6g   %12.6g   %s\n", tn.c_str(), dz, F, 0.5 * F, band(0.5 * F)); }
    return 0;
}
