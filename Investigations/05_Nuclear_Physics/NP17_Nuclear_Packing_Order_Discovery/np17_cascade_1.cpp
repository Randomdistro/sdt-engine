// NP17/NP09/NP10 tolerance-cascade run C1 (2026-10-11). Registration: CASCADE_PRE_REGISTRATION_2026-10-11.md.
// Same native-list ledger as np17_reset_1 (attempt 2 conventions: masses in u, CODATA 2022 u). Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
namespace M = sdt::laws::measured;
static constexpr double u_kg = 1.66053906892e-27, u_MeV22 = 931.49410372, u_MeV_ame = 931.49410242;   // [MEASURED-INPUT]

static const char* band(double rho) {
    if (!std::isfinite(rho)) return "B7";
    return rho <= 1e-3 ? "B1" : rho <= 1e-2 ? "B2" : rho <= 3e-2 ? "B3" : rho <= 0.10 ? "B4" : rho <= 0.30 ? "B5" : rho <= 2.0 ? "B6" : "B7";
}
static double ame_excess_keV(const char* path, int Z, int A) {
    std::ifstream f(path); std::string L;
    while (std::getline(f, L)) {
        if (L.size() < 42) continue;
        int z = std::atoi(L.substr(9, 5).c_str()), a = std::atoi(L.substr(14, 5).c_str());
        std::string ex = L.substr(28, 14);
        if (z == Z && a == A && ex.find_first_of("0123456789") != std::string::npos && ex.find('#') == std::string::npos
            && L.substr(4, 5).find_first_not_of(' ') != std::string::npos) return std::atof(ex.c_str());
    }
    std::printf("AME row Z=%d A=%d not found\n", Z, A); std::exit(2);
}
static void row(const char* id, const char* what, double pred, double meas, const char* mod, bool wrongSign = false) {
    double rho = std::fabs(pred / meas - 1);
    std::printf("%-12s %-58s pred %12.6f  meas %12.6f  rho %8.3f%%  %s  [%s]\n", id, what, pred, meas, 100 * rho, wrongSign ? "B7 (wrong sign)" : band(rho), mod);
}
int main(int argc, char** argv) {
    const char* ame = argc > 1 ? argv[1] : "Datasets/nuclear/AME2020_mass_excess.txt";
    const double ahc = M::alpha * M::hbar * M::c / M::MeV_to_J * 1e15, Rp = M::R_p * 1e15, a0 = M::a_0 * 1e15;
    const double me = M::m_e / u_kg * u_MeV22, mp = M::m_p / u_kg * u_MeV22;
    auto Bnat = [&](int Z, int A) { return A * (mp + me) - (A + ame_excess_keV(ame, Z, A) / (u_MeV_ame * 1e3)) * u_MeV22; };
    std::printf("NP17/NP09/NP10 cascade C1 (2026-10-11)\n======================================\n");
    // validations carried from np17_reset_1 (attempt 2)
    double h1 = Bnat(1, 1) * 1e6; bool v3 = std::fabs(h1 - 13.598) < 0.5;
    double ry = 0.5 * M::m_e * std::pow(M::alpha * M::c, 2) / M::eV_to_J; bool v2 = std::fabs(ry / M::Ry_eV - 1) < 1e-9;
    std::printf("[V2] %.9f eV vs Ry %s ; [V3] 1H defect %.3f eV %s\n\n", ry, v2 ? "met" : "NOT MET", h1, v3 ? "met" : "NOT MET");
    if (!v2 || !v3) return 1;
    const double unit = 0.5 * ahc / Rp, D = 7 * Rp / 3;
    std::printf("id           check                                                      (MeV unless stated)\n");
    row("NP17-T1-t", "H-SE ceiling N*A*unit vs 3H {3p,2e} (ceiling BELOW meas)", 2 * 3 * unit, Bnat(1, 3), "post-seen");
    row("NP17-T1-h", "H-SE ceiling vs 3He {3p,1e} (ceiling BELOW meas)", 1 * 3 * unit, Bnat(2, 3), "post-seen");
    row("NP17-T1-a", "H-SE ceiling vs 4He {4p,2e} (ceiling BELOW meas)", 2 * 4 * unit, Bnat(2, 4), "post-seen");
    row("NP17-T2", "H-SE deuteron, electron at 7Rp/6, vs {2p,1e}  (= NP09-C1a)", ahc / (7 * Rp / 6), Bnat(1, 2), "post-seen");
    row("NP17-T3", "H2+ static seat at R_e=2a0 (eV) vs {p,p,e}", (ahc / a0) * 1e6, 131058.1219937 * 1.239841984e-4, "post-seen");
    { double meas = (M::m_n - M::m_p - M::m_e) * M::c * M::c / M::MeV_to_J;
      row("NP17-T4", "H-SE node: n - (p+e) predicted -unit*... vs measured", -0.5 * ahc / (Rp / 3), meas, "wrong-sign", true); }
    row("NP17-T5", "old ledger 3ahc/D on its own list {2p,1e} (= NP09-C1b)", 3 * ahc / D, Bnat(1, 2), "post-seen");
    row("NP09-C1c", "old ledger 3ahc/D vs {p,n} 2.224571 (the old claim)", 3 * ahc / D, (M::m_p + M::m_n - M::m_d) * M::c * M::c / M::MeV_to_J, "post-seen; list mismatch");
    row("NP10-C4", "2 R_p_lock vs R_He (fm)", 2 * sdt::laws::law_III::R_p_lock * 1e15, M::R_He * 1e15, "post-seen");
    return 0;
}
