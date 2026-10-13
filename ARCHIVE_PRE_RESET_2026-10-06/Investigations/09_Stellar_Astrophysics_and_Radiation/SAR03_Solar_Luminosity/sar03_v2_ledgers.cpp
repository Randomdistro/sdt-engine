// ============================================================================
// SAR03 v2 (§K rebuild) — Solar Luminosity: MECHANISM HUNTS H1-H4
//
// H1: interior rotation-map hunt (three un-tuned profiles -> T(r) via
//     pressure-restricted oscillation; open outcome)
// H2: assembly-bottleneck hunt (grammar rate demand -> p_align; candidate
//     geometric fractions ranked)
// H3: engagement-fraction hunt (four intake ledgers x combinatorial
//     zero-parameter gear-stack search; nulls reported)
// H4: pressure-domain check (open comparison)
//
// Movement discipline: movements (v/c) and spans first; SI comparison columns.
// No fits. Direct execution. Author: J.C. Harvey. Run: Fable direct, 2026-07-12.
// ============================================================================

#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>
#include <vector>
#include <string>

int main() {
    using namespace sdt::laws;
    constexpr double pi = std::numbers::pi;
    constexpr double AU = 1.495978707e11;
    constexpr double kB = 1.380649e-23;

    const double c  = measured::c;
    const double Rs = measured::R_Sun;
    const double L  = law_II::L_Sun;
    const double Fc = law_II::F_CMB;
    const double Pc = law_I::P_conv;
    const double kS = bridge::k_Sun;
    const double fT = law_III::f_transfer;
    const double mp = measured::m_p;
    const double me = measured::m_e;
    const double al = measured::alpha;
    const double Rp = 8.414e-16;              // proton boundary radius [m] (canon)
    const double SfG = 4.19e-9;               // GOM12 occlusion budget [imported COMPUTED]
    const double Msun_census = 1.989e30;      // kg — baryon CENSUS import [OBSERVED, flagged]
    const double Nb = Msun_census / mp;

    const double v_surf = c / kS;             // solar surface movement from the k-gear

    std::printf("SAR03 v2 — mechanism hunts (direct run)\n");
    std::printf("[engine] P_conv=%.4e Pa  F_CMB=%.4e W/m2  L=%.4e W  v_surf=c/k_Sun=%.4e m/s\n\n",
                Pc, Fc, L, v_surf);

    // ------------------------------------------------------------------ H1
    std::printf("[H1] interior rotation-map hunt: T(r) = m_p v(r)^2 / (3 kB), three profiles\n");
    std::printf("     %-6s %12s %12s %12s\n", "r/R", "sqrt(R/r)->T", "rotor(r/R)->T", "hybrid->T");
    const double fr[] = {0.02, 0.05, 0.10, 0.20, 0.25, 0.50, 0.75, 1.00};
    double bestT[3] = {0,0,0}; double bestFr[3] = {0,0,0};
    for (double f : fr) {
        const double vA = v_surf * std::sqrt(1.0/f);           // Keplerian-interior
        const double vB = v_surf * f;                          // solid rotor
        const double vC = v_surf * std::pow(1.0/f, 1.0/3.0);   // FLM03-hybrid (cube-root)
        const double TA = mp*vA*vA/(3*kB), TB = mp*vB*vB/(3*kB), TC = mp*vC*vC/(3*kB);
        std::printf("     %-6.2f %12.4e %12.4e %12.4e\n", f, TA, TB, TC);
        const double Ts[3] = {TA,TB,TC};
        for (int i=0;i<3;++i)
            if (std::fabs(std::log10(Ts[i]/1.57e7)) < std::fabs(std::log10((bestT[i]?bestT[i]:1e-30)/1.57e7)))
                { bestT[i]=Ts[i]; bestFr[i]=f; }
    }
    std::printf("     surface reading (r/R=1): sqrt: %.3e K  rotor: %.3e K  hybrid: %.3e K  (photosphere 5778 K rival col.)\n",
                mp*v_surf*v_surf/(3*kB), mp*v_surf*v_surf/(3*kB), mp*v_surf*v_surf/(3*kB));
    for (int i=0;i<3;++i) {
        const char* nm[3] = {"sqrt(R/r)","rotor","hybrid"};
        const double dist = std::fabs(std::log10(bestT[i]/1.57e7));
        std::printf("     closest to core scale [%s]: T=%.3e K at r/R=%.2f  (log-dist %.2f) %s\n",
            nm[i], bestT[i], bestFr[i], dist, dist<1.0 ? "<-- WITHIN x10: LEAD candidate" : "");
    }
    std::printf("\n");

    // ------------------------------------------------------------------ H2
    std::printf("[H2] assembly-bottleneck hunt (grammar rate demand)\n");
    const double E_alpha = 26.73e6 * 1.602176634e-19;  // J per He-4 assembly (4p->alpha ledger)
    const double rate_alpha = L / E_alpha;
    const double rate_pp = 2.0 * rate_alpha;           // two deuteron formations per alpha
    const double n_mean = Nb / (4.0/3.0*pi*Rs*Rs*Rs);
    // thermal movement at H1's best core-scale T (use the profile family's core-scale band):
    const double T_core_band = 1.57e7;                 // rival col. anchor for the attempt rate;
    const double v_th = std::sqrt(3*kB*T_core_band/mp);// movement v/c ~ 2e-3 (logged)
    const double attempt_per_baryon = n_mean * (pi*Rp*Rp) * v_th;   // encounters/s within footprint
    const double required_per_baryon = rate_pp / Nb;
    const double p_align = required_per_baryon / attempt_per_baryon;
    std::printf("     required alpha assemblies = %.3e /s ; deuteron formations = %.3e /s\n", rate_alpha, rate_pp);
    std::printf("     census: N_b=%.3e [OBSERVED import]  mean n=%.3e /m3\n", Nb, n_mean);
    std::printf("     attempt rate/baryon = n*(pi R_p^2)*v_th = %.3e /s  (v_th/c=%.3e)\n",
                attempt_per_baryon, v_th/c);
    std::printf("     required rate/baryon = %.3e /s\n", required_per_baryon);
    std::printf("     => demanded p_align = %.3e per encounter\n", p_align);
    std::printf("     candidate geometric fractions (ranked by |log10 ratio| to p_align):\n");
    struct Cand { const char* name; double val; };
    std::vector<Cand> cands = {
        {"alpha^10", std::pow(al,10)}, {"alpha^11", std::pow(al,11)}, {"alpha^12", std::pow(al,12)},
        {"(m_e/m_p)^3", std::pow(me/mp,3)}, {"(m_e/m_p)^4", std::pow(me/mp,4)},
        {"alpha^6*(m_e/m_p)^2", std::pow(al,6)*std::pow(me/mp,2)},
        {"1/k_Sun^8", std::pow(kS,-8.0)}, {"1/k_Sun^9", std::pow(kS,-9.0)},
        {"f_transfer*alpha^4", fT*std::pow(al,4)}, {"Sigma_f^3", std::pow(SfG,3)},
        {"alpha^8*(m_e/m_p)", std::pow(al,8)*(me/mp)},
    };
    for (auto& cd : cands) {
        const double d = std::fabs(std::log10(cd.val/p_align));
        if (d < 3.0)
            std::printf("       %-22s = %.3e  log-dist %.2f %s\n", cd.name, cd.val, d,
                        d<1.0 ? "<-- WITHIN x10: LEAD (mechanism required before claim)" : "");
    }
    std::printf("     rival column: SM pp bottleneck ~1e-25/encounter class (weak S-factor) — comparison only\n\n");

    // ------------------------------------------------------------------ H3
    std::printf("[H3] engagement-fraction hunt: four intake ledgers\n");
    struct Ledger { const char* name; double intake; };
    const std::vector<Ledger> Ls = {
        {"radiative F_CMB*piR^2", Fc*pi*Rs*Rs},
        {"full P_conv*c*piR^2  ", Pc*c*pi*Rs*Rs},
        {"electropause P_eff*c*piR^2", law_III::P_eff*c*pi*Rs*Rs},
        {"GOM12-weighted full  ", SfG*Pc*c*pi*Rs*Rs},
    };
    for (const auto& lg : Ls) {
        const double frac = L / lg.intake;
        std::printf("     %-28s intake=%.3e W  implied engagement=%.3e\n", lg.name, lg.intake, frac);
    }
    // combinatorial zero-parameter search over gear stack, exponents -3..3
    std::printf("     gear-stack search (exponents -3..+3; report hits within 1 order):\n");
    const double gears[] = {al, 1.0/kS, fT, SfG, Rp/Rs, me/mp};
    const char* gn[] = {"alpha","1/k_Sun","f_transfer","Sigma_f","R_p/R_Sun","m_e/m_p"};
    int hits = 0;
    for (const auto& lg : Ls) {
        const double target = std::log10(L/lg.intake);
        for (int a=-3;a<=3;++a) for(int b=-3;b<=3;++b) for(int cc=-3;cc<=3;++cc)
        for (int d=-3;d<=3;++d) for(int e=-3;e<=3;++e) for(int f=-3;f<=3;++f) {
            if (std::abs(a)+std::abs(b)+std::abs(cc)+std::abs(d)+std::abs(e)+std::abs(f) > 6) continue;
            const double lg10 = a*std::log10(gears[0])+b*std::log10(gears[1])+cc*std::log10(gears[2])
                              + d*std::log10(gears[3])+e*std::log10(gears[4])+f*std::log10(gears[5]);
            if (std::fabs(lg10-target) < 1.0) {
                if (hits < 12)
                    std::printf("       [%s] ~ %s^%d * %s^%d * %s^%d * %s^%d * %s^%d * %s^%d (log-dist %.2f)\n",
                        lg.name, gn[0], a, gn[1], b, gn[2], cc, gn[3], d, gn[4], e, gn[5], f,
                        std::fabs(lg10-target));
                ++hits;
            }
        }
    }
    std::printf("     total combinatorial hits within 1 order: %d %s\n\n", hits,
        hits==0 ? "(NULL — no zero-parameter decomposition in this gear set)" :
        "(NOTE: hit count >> 1 means the space is degenerate — hits are NOT results without mechanism)");

    // ------------------------------------------------------------------ H4
    const double rdom = law_II::pressure_domain(L);
    std::printf("[H4] pressure-domain check: r_domain = %.4e m = %.0f AU (Oort literature comparison open)\n",
                rdom, rdom/AU);
    return 0;
}
