// NP17 reset, instrument 1 (2026-10-10): the shared-electron seat ledger (H-SE) tested on native lists.
// Registration: PROMPT.md §5 (rewritten 2026-10-10). Record: NP17_RESET_ASSESSMENT_2026-10-10.md.
// Written afresh; constants from sdt::laws; AME2020 read from Datasets. Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
namespace M = sdt::laws::measured;

// attempt 2: masses carried in u (CODATA 2022 u_kg, u_MeV) so the engine kg masses and AME u masses share one conversion (attempt 1 G0: vintage mix)
static constexpr double u_kg = 1.66053906892e-27, u_MeV22 = 931.49410372;   // [MEASURED-INPUT] CODATA 2022
static double me_MeV() { return M::m_e / u_kg * u_MeV22; }
static double mp_MeV() { return M::m_p / u_kg * u_MeV22; }

// AME2020 mass.mas20: mass excess (keV) at columns 28..41 (0-based), Z at 9..13, A at 14..18.
static double ame_excess_keV(const char* path, int Z, int A) {
    std::ifstream f(path); std::string L;
    while (std::getline(f, L)) {
        if (L.size() < 42) continue;
        int z = std::atoi(L.substr(9, 5).c_str()), a = std::atoi(L.substr(14, 5).c_str());
        std::string ex = L.substr(28, 14);
        if (z == Z && a == A && ex.find_first_of("0123456789") != std::string::npos && ex.find('#') == std::string::npos
            && L.substr(4, 5).find_first_not_of(' ') != std::string::npos)
            return std::atof(ex.c_str());
    }
    std::printf("AME row Z=%d A=%d not found\n", Z, A); std::exit(2);
}

int main(int argc, char** argv) {
    const char* ame = argc > 1 ? argv[1] : "Datasets/nuclear/AME2020_mass_excess.txt";
    const double u_MeV = 931.49410242;                                    // [MEASURED-INPUT] AME2020 conversion
    const double ahc = M::alpha * M::hbar * M::c / M::MeV_to_J * 1e15;    // MeV fm
    const double Rp = M::R_p * 1e15, re = M::r_e * 1e15, a0fm = M::a_0 * 1e15;
    const double me = me_MeV(), mp = mp_MeV();
    std::printf("NP17 reset instrument 1 (2026-10-10)\n====================================\n\n");
    int bad = 0;
    { bool ok = std::fabs(ahc / 1.439964 - 1) < 1e-5; double r = 7 * Rp / 6, id = me * re / r; bool ok2 = std::fabs(id / (ahc / r) - 1) < 1e-8;   /* attempt 2: 1e-12 was below the engine vintage floor (m_e 2018, alpha 2022) */
      std::printf("[V1] alpha hbar c = %.6f MeV fm %s ; identity ahc/r = m_e c^2 r_e/r at 7Rp/6: %.12f vs %.12f -> %s\n", ahc, ok ? "met" : "NOT MET", ahc / r, id, ok2 ? "met" : "NOT MET"); bad += !ok + !ok2; }
    { double ry = 0.5 * M::m_e * std::pow(M::alpha * M::c, 2) / M::eV_to_J; bool ok = std::fabs(ry / M::Ry_eV - 1) < 1e-9;
      std::printf("[V2] 1/2 m_e (alpha c)^2 = %.9f eV vs engine Ry %.9f -> %s\n", ry, M::Ry_eV, ok ? "met" : "NOT MET"); bad += !ok; }
    auto Matom = [&](int Z, int A) { return (A + ame_excess_keV(ame, Z, A) / (u_MeV * 1e3)) * u_MeV22; };   // excess -> u with AME's own factor, then u -> MeV (2022)
    // native-list defect: B({A p, A e}) for the atom; nucleus list {A p, N e} equal to it up to the fielded-electron binding (<0.1 keV, A<=4)
    auto Bnat = [&](int Z, int A) { return A * (mp + me) - Matom(Z, A); };
    { double b = Bnat(1, 1) * 1e6; bool ok = std::fabs(b - 13.598) < 0.5;
      std::printf("[V3] AME: 1H defect against {p,e} = %.3f eV (measured 13.598) -> %s\n", b, ok ? "met" : "NOT MET"); bad += !ok; }
    { double eng = (2 * M::m_p + M::m_e - M::m_d) / u_kg * u_MeV22, am = Bnat(1, 2);
      bool ok = std::fabs(eng - am) < 1e-3; std::printf("[V4] deuteron against {2p,1e}: engine route %.6f MeV, AME route %.6f MeV (diff %.2e) -> %s\n\n", eng, am, eng - am, ok ? "met" : "NOT MET"); bad += !ok; }
    if (bad) { std::printf("VALIDATIONS NOT MET\n"); return 1; }
    std::printf("VALIDATIONS: met\n\n");

    const double unit = 0.5 * ahc / Rp;   // H-SE: one electron-proton seat at the boundary, 1/2 m_e v(R_p)^2
    std::printf("seat unit 1/2 ahc/R_p = 1/2 m_e v(R_p)^2 = %.6f MeV  (v(R_p) = %.5f c)\n\n", unit, std::sqrt(re / Rp));

    struct Nuc { const char* n; int Z, A; };
    const Nuc set[] = {{"2H (d)", 1, 2}, {"3H (t)", 1, 3}, {"3He (h)", 2, 3}, {"4He (a)", 2, 4}};
    std::printf("T1  H-SE ceiling B_max = N*A*(1/2 ahc/R_p) against the native-list defect\n");
    std::printf("   nucleus   N  A   B_meas{Ap,Ne} (MeV)   B_max (MeV)   B_meas/B_max   verdict\n");
    int over = 0;
    for (const auto& x : set) {
        int N = x.A - x.Z; double bm = Bnat(x.Z, x.A), cap = N * x.A * unit; bool ex = bm > cap;
        if (x.A >= 3) over += ex;
        std::printf("   %-8s %2d %2d   %14.6f      %10.6f     %8.4f      %s\n", x.n, N, x.A, bm, cap, bm / cap, ex ? "EXCEEDS ceiling" : "within ceiling");
    }
    std::printf("   A>=3 nuclei exceeding the ceiling: %d of 3 -> H-SE %s\n\n", over, over >= 2 ? "EXCLUDED (G1) for A>=3" : "admitted (G2 open)");

    { double Bd = Bnat(1, 2), pred = 2 * 0.5 * ahc / (7 * Rp / 6), rel = pred / Bd - 1;
      std::printf("T2  deuteron, NP30 contact geometry (electron at D/2 = 7R_p/6 from each proton): H-SE %.6f MeV vs %.6f {2p,1e}: %+.3f%% -> %s\n\n",
                  pred, Bd, 100 * rel, std::fabs(rel) <= 0.03 ? "within 3% (G3, post-seen, look-elsewhere 8)" : "outside 3% (G1 for this placement)"); }

    { double pred = 2 * 0.5 * (ahc / a0fm) * 1e6, meas = 131058.1219937 * 1.239841984e-4, rel = pred / meas - 1;   // [MEASURED-INPUT] arXiv:1804.11143; R_e = 2 a0, arXiv:1502.00291
      std::printf("T3  H2+ cross-scale, electron static at the midpoint of R_e = 2 a0: H-SE %.4f eV vs measured %.4f eV {p,p,e}: %+.2f%% -> %s\n\n",
                  pred, meas, 100 * rel, std::fabs(rel) <= 0.05 ? "scale-consistent" : "NOT one law across the ladder (static seat)"); }

    { double node = 0.5 * ahc / (Rp / 3), meas = (M::m_n - M::m_p - M::m_e) * M::c * M::c / M::MeV_to_J;
      std::printf("T4  neutron domain check: H-SE at the node R_p/3 predicts n LIGHTER than p+e by %.4f MeV; measured n HEAVIER by %.4f MeV (gap %.4f MeV)\n\n", node, meas, node + meas); }

    { double D = 7 * Rp / 3, old = 3 * ahc / D, Bd = Bnat(1, 2), nodeFull = ahc / (Rp / 3);
      std::printf("T5  old NP17 ledger 3 ahc/D = %.6f MeV (D = %.4f fm)\n", old, D);
      std::printf("    on its own list {p,p,e}: vs %.6f -> %+.2f%%\n", Bd, 100 * (old / Bd - 1));
      std::printf("    against {p,n} with the neutron's node term in the same bookkeeping: 3ahc/D - ahc/(R_p/3) = %.6f MeV (vs 2.2246 measured)\n\n", old - nodeFull); }

    std::printf("context (report only): native-list defects A=3: t - h = %.6f MeV (t has 2 stabled electrons, h has 1)\n", Bnat(1, 3) - Bnat(2, 3));
    return 0;
}
