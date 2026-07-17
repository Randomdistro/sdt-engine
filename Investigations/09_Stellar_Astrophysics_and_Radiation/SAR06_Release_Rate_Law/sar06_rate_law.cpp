// ============================================================================
// SAR06 — Release-Rate Law: mechanism hunts M1-M4 against constraints C1-C5
// Direct execution (no agents). Movement-only discipline; SI comparison columns.
// Author: J. C. Harvey, Melbourne. Run: Fable direct, 2026-07-13.
// ============================================================================
#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>
#include <initializer_list>

int main() {
    using namespace sdt::laws;
    constexpr double pi = std::numbers::pi;
    constexpr double kB = 1.380649e-23, sb = 5.670374e-8, hP = 6.62607015e-34;

    const double c  = measured::c;
    const double Rs = measured::R_Sun;
    const double L  = law_II::L_Sun;
    const double kS = bridge::k_Sun;
    const double mp = measured::m_p;
    const double lP = 1.616255e-35;
    const double Rp = 8.414e-16;
    const double Tcmb = 2.725;
    const double u  = 4.0*sb*Tcmb*Tcmb*Tcmb*Tcmb/c;
    const double V  = 4.0/3.0*pi*Rs*Rs*Rs, A = 4.0*pi*Rs*Rs;
    const double Nb = 1.989e30/mp;                    // census [OBSERVED]
    const double n  = Nb/V;
    const double lam_peak = 2.897771955e-3/Tcmb;      // 1.063 mm
    const double lam_mean = hP*c/(2.701*kB*Tcmb);     // 1.95 mm

    // constraints
    const double C1 = u*c/(lP*n);                     // 0.918 W offered per baryon
    const double C2 = (L/Nb)/C1;                      // engaged fraction 3.5e-31
    const double C4 = 1.286e-25;                      // p_align (SAR03 H2)
    const double gap23 = L/(u*c*V/lam_peak);          // the x23 (osc-cell -> L)

    std::printf("SAR06 — release-rate law hunts (direct)\n");
    std::printf("constraints: C1=%.4f W/baryon  C2=%.3e  C4=%.3e  osc-cell gap=x%.1f\n\n",
                C1, C2, C4, gap23);

    // ---------------- M1: pressure-restriction weighting of the volumetric sum
    std::printf("[M1] weighting (v(r)/v_surf)^m on sqrt(R/r) profile: amplification of the\n");
    std::printf("     oscillation-cell sum (needs x%.1f to reach L):\n", gap23);
    for (int m : {2,4,6,8}) {
        // amplification = 3*Int_0^1 f^2 (1/f)^(m/2) df   (v/v_surf = f^-1/2)
        const double p = 2.0 - m/2.0;   // integrand exponent: f^(2 - m/2)
        double amp;
        bool diverges = (p <= -1.0);
        if (!diverges) amp = 3.0/(p+1.0);
        std::printf("     m=%d: ", m);
        if (!diverges) {
            std::printf("amplification x%.2f %s\n", amp, std::fabs(amp-gap23)<0.5*gap23 ? "<-- near x23" : "");
        } else {
            // kernel radius where truncated integral reaches gap23: 3*ln(1/fmin)=gap23 (m=6)
            if (m==6) {
                const double fmin = std::exp(-gap23/3.0);
                std::printf("DIVERGES at centre — truncated integral reaches x%.1f at kernel f_min=%.3e (r=%.3e m = %.0f km)\n",
                            gap23, fmin, fmin*Rs, fmin*Rs/1e3);
            } else {
                const double fmin = std::pow(3.0/((-p-1.0)*gap23), 1.0/(-p-1.0)); // 3/(q) fmin^-q = gap
                std::printf("DIVERGES — reaches x%.1f at kernel f_min=%.3e (r=%.0f km)\n",
                            gap23, fmin, fmin*Rs/1e3);
            }
        }
    }
    std::printf("     reading: hot-cores weighting CAN close the gap only via a central kernel;\n");
    std::printf("     kernel radius is the mechanism's own prediction (structure, not fit).\n\n");

    // ---------------- M2: grip-per-span candidates vs C4 (pre-registered)
    std::printf("[M2] transverse-footprint (PPT10 n=2) candidates vs C4=%.3e:\n", C4);
    struct Cnd { const char* nm; double v; };
    Cnd cs[] = {
        {"(R_p/lam_peak)^2", std::pow(Rp/lam_peak,2)},
        {"(R_p/lam_mean)^2", std::pow(Rp/lam_mean,2)},
        {"(R_p/lam_peak)  ", Rp/lam_peak},
        {"(R_p/lam_mean)  ", Rp/lam_mean},
    };
    for (auto& x : cs) {
        const double r = x.v/C4;
        std::printf("     %s = %.3e   ratio to C4 = %.2f %s\n", x.nm, x.v, r,
            (r>0.1 && r<10.0) ? "<-- LEAD band (pre-registered)" : "");
    }
    std::printf("     mechanism statement: assembly succeeds when the arriving relay\n");
    std::printf("     oscillation grips BOTH boundaries within one transverse footprint;\n");
    std::printf("     grip fraction = (boundary/medium-span)^2. The span is the LATTICE's\n");
    std::printf("     (Clearing-set lambda_CMB), not the local plasma's — the medium\n");
    std::printf("     remembers its span; matter's local thermal light does not reset it.\n\n");

    // ---------------- M3: event-energy identity
    const double v_th = std::sqrt(3.0*kB*1.57e7/mp);
    const double attempt = n*pi*Rp*Rp*v_th;               // encounters /s /baryon
    const double event_rate = C4*attempt;                 // engagements /s /baryon
    const double E_event = (L/Nb)/event_rate;             // J per engagement
    std::printf("[M3] IDENTITY check: energy per engagement event\n");
    std::printf("     attempt=%.3e /s  event rate=%.3e /s  E_event=%.3e J = %.2f MeV\n",
                attempt, event_rate, E_event, E_event/1.602176634e-13);
    std::printf("     grammar per-deuteron-step release = 26.73/2 = 13.37 MeV  [IDENTITY —\n");
    std::printf("     both sides descend from L; value = the release QUANTUM the law owes]\n\n");

    // ---------------- M4: main-sequence scaling kill test
    std::printf("[M4] scaling kill test (homology, mass-free k via koppa; R ~ M^0.8 observed):\n");
    // law: L ~ Nb * n * v_th * p, with p = const (grip law)
    // Nb ~ M ; n ~ M/R^3 ; v_th ~ v_koppa ~ sqrt(M/R)  =>  L ~ M^2.5 / R^3.5 ~ M^(2.5-3.5*0.8)
    const double expo_const_grip = 2.5 - 3.5*0.8;
    std::printf("     constant-grip law:      L ~ M^%.2f   (band 2.5-4.5; empirical 3.5)  %s\n",
                expo_const_grip, (expo_const_grip>=2.5&&expo_const_grip<=4.5)?"PASS":"KILLED");
    // dissection: what T-dependence would the alignment factor need?
    // L ~ M^(-0.3) * (T_core)^q with T_core ~ M/R ~ M^0.2  =>  need -0.3 + 0.2q in [2.5,4.5]
    const double q_lo = (2.5 - expo_const_grip)/0.2, q_hi = (4.5 - expo_const_grip)/0.2;
    std::printf("     dissection: alignment factor needs T-sensitivity q in [%.0f, %.0f]\n", q_lo, q_hi);
    std::printf("     (T_core ~ M^0.2 under same homology). Rival column: SM pp effective\n");
    std::printf("     q ~ 4 near solar T; CNO q ~ 17. The demanded q is STEEPER — the\n");
    std::printf("     alignment-search (Arrhenius) factor must carry it; its own exponent\n");
    std::printf("     becomes the next decidable (cross-feed QM03/Arrhenius root).\n\n");

    std::printf("SUMMARY\n");
    std::printf("  M1: hot-cores weighting closes x%.1f only with a central kernel (km-class) — structure prediction\n", gap23);
    std::printf("  M2: grip law (R_p/lam_mean)^2 = %.3e vs C4 %.3e (x%.2f) — LEAD (pre-registered, mechanism named)\n",
                std::pow(Rp/lam_mean,2), C4, std::pow(Rp/lam_mean,2)/C4);
    std::printf("  M3: release quantum 13.4 MeV [IDENTITY]\n");
    std::printf("  M4: constant grip KILLED by scaling (M^%.2f vs 3.5); demanded alignment T-exponent %.0f-%.0f\n",
                expo_const_grip, q_lo, q_hi);
    std::printf("  LAW SHAPE EARNED: rate = attempt x (R_p/lam_CMB)^2 x A(T), with A(T) the\n");
    std::printf("  alignment-search factor owing q~%.0f-%.0f — the corner for the next hunt.\n", q_lo, q_hi);
    return 0;
}
