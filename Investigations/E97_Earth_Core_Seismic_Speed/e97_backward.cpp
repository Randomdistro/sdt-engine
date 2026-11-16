/**
 * @file e97_backward.cpp
 * @brief E97v5: Earth interior from KOPPA with smooth PREM polynomials
 *
 *     ϟ = v²R/c² = 4.43 mm
 *     g(r) = c²ϟ frac(r)/r²
 *
 * Density: PREM polynomial coefficients (Dziewonski & Anderson 1981)
 * Moduli:  smooth pressure-dependent K(P), G(P) with SDT K'=4
 *
 * Inputs: c, v_surf, R_E, PREM polynomials
 * NOT USED: G, M, GM
 */

#include <cstdio>
#include <cmath>
#include <numbers>

// ═══════════════════════════════════════════════════════════
//  PREM SMOOTH DENSITY (polynomials in x = r/R)
//  ρ in kg/m³, coefficients from Dziewonski & Anderson 1981
// ═══════════════════════════════════════════════════════════
constexpr double R_REF = 6.371e6;

inline double prem_rho(double r) {
    double x = r / R_REF;
    double rho_gcc;
    if      (r < 1221.5e3) rho_gcc = 13.0885 - 8.8381*x*x;
    else if (r < 3480.0e3) rho_gcc = 12.5815 - 1.2638*x - 3.6426*x*x - 5.5281*x*x*x;
    else if (r < 5701.0e3) rho_gcc = 7.9565 - 6.4761*x + 5.5283*x*x - 3.0807*x*x*x;
    else if (r < 5771.0e3) rho_gcc = 5.3197 - 1.4836*x;
    else if (r < 5971.0e3) rho_gcc = 11.2494 - 8.0298*x;
    else if (r < 6151.0e3) rho_gcc = 7.1089 - 3.8045*x;
    else if (r < 6346.6e3) rho_gcc = 2.6910 + 0.6924*x;
    else if (r < 6356.0e3) rho_gcc = 2.9;
    else                    rho_gcc = 2.6;
    return rho_gcc * 1000.0;  // → kg/m³
}

// PREM smooth Vp, Vs (km/s) for reference comparison
inline double prem_vp(double r) {
    double x = r / R_REF;
    if      (r < 1221.5e3) return 11.2622 - 6.3640*x*x;
    else if (r < 3480.0e3) return 11.0487 - 4.0362*x + 4.8023*x*x - 13.5732*x*x*x;
    else if (r < 3630.0e3) return 15.3891 - 5.3181*x;
    else if (r < 5600.0e3) return 24.952  - 40.4673*x + 51.4832*x*x - 26.6419*x*x*x;
    else if (r < 5701.0e3) return 29.2766 - 23.6027*x + 5.5242*x*x - 2.5514*x*x*x;
    else if (r < 5771.0e3) return 19.0957 - 9.8672*x;
    else if (r < 5971.0e3) return 39.7027 - 32.6166*x;
    else if (r < 6151.0e3) return 20.3926 - 12.2569*x;
    else if (r < 6346.6e3) return  4.1875 +  3.9382*x;
    else if (r < 6356.0e3) return  6.8;
    else                    return  5.8;
}

inline double prem_vs(double r) {
    double x = r / R_REF;
    if      (r < 1221.5e3) return 3.6678 - 4.4475*x*x;
    else if (r < 3480.0e3) return 0.0;  // liquid
    else if (r < 3630.0e3) return 6.9254 + 1.4672*x;
    else if (r < 5600.0e3) return 11.1671 - 13.7818*x + 17.4575*x*x - 9.2777*x*x*x;
    else if (r < 5701.0e3) return 22.3459 - 17.2473*x - 2.0834*x*x + 0.9783*x*x*x;
    else if (r < 5771.0e3) return  9.9839 - 4.9324*x;
    else if (r < 5971.0e3) return 22.3512 - 18.5856*x;
    else if (r < 6151.0e3) return  8.9496 - 4.4597*x;
    else if (r < 6346.6e3) return  2.1519 + 2.3481*x;
    else if (r < 6356.0e3) return  3.9;
    else                    return  3.2;
}

inline double prem_g(double r) {
    // PREM gravity polynomial (approximate, for comparison)
    double x = r / R_REF;
    if (x < 0.001) return 0.0;
    if      (r < 1221.5e3) return 4.4 * x / 0.1917;   // linear in core
    else if (r < 3480.0e3) return 10.68 - (10.68 - 4.40) * (3480e3 - r) / (3480e3 - 1221.5e3);
    else if (r < 5701.0e3) return 10.02 + (10.68 - 10.02) * (5701e3 - r) / (5701e3 - 3480e3);
    else                    return 9.81 + (10.02 - 9.81) * (R_REF - r) / (R_REF - 5701e3);
}

int main() {
    // ═══════════════════════════════════════════════════════════
    //  INPUTS
    // ═══════════════════════════════════════════════════════════
    constexpr double c      = 299'792'458.0;
    constexpr double v_surf = 7909.0;
    constexpr double R_E    = R_REF;

    // SDT derived
    constexpr double k      = c / v_surf;
    constexpr double z      = (v_surf * v_surf) / (c * c);
    constexpr double koppa  = R_E * z;
    constexpr double g_surf = v_surf * v_surf / R_E;

    // Planck (displacement analysis)
    constexpr double l_P   = 1.616'255e-35;
    constexpr double t_P   = 5.391'24e-44;
    constexpr double l_P3  = l_P * l_P * l_P;
    constexpr double a_rad = 7.565'7e-16;
    constexpr double T_CMB = 2.7255;
    constexpr double R_CMB = 9.527e26;
    constexpr double m_u   = 1.660'539'07e-27;
    constexpr double m_p   = 1.672'621'923'69e-27;
    constexpr double m_n   = 1.674'927'498'04e-27;
    constexpr double m_e   = 9.109'383'7015e-31;
    constexpr double u_CMB = a_rad * T_CMB * T_CMB * T_CMB * T_CMB;
    constexpr double eps   = u_CMB * l_P3;
    constexpr double N_sh  = R_CMB / l_P;
    constexpr double Phi   = N_sh * eps;
    constexpr double P_conv= Phi / l_P3;
    constexpr double V_dp  = 3.0 * m_p * l_P3 * c * c / Phi;
    constexpr double V_dn  = 3.0 * m_n * l_P3 * c * c / Phi;
    constexpr double V_de  = 3.0 * m_e * l_P3 * c * c / Phi;

    // ═══════════════════════════════════════════════════════════
    //  INTEGRATE with smooth PREM
    // ═══════════════════════════════════════════════════════════
    constexpr int NS = 5000;
    double dr = R_E / NS;

    // Pass 1: ∫ρ 4πr² dr (smooth)
    double rho_int[NS + 1];
    rho_int[0] = 0.0;
    for (int i = 1; i <= NS; ++i) {
        double rm = (i - 0.5) * dr;
        rho_int[i] = rho_int[i-1] + prem_rho(rm) * 4.0*std::numbers::pi*rm*rm*dr;
    }
    double total_rho_vol = rho_int[NS];

    // g(r) = v²R frac(r) / r²  =  c²ϟ frac(r) / r²
    auto g_at = [&](double r, int idx) -> double {
        if (r < dr) return 0.0;
        return g_surf * R_E * R_E * rho_int[idx] / (total_rho_vol * r * r);
    };

    // Pass 2: P from surface inward
    double P_pa[NS + 1];
    P_pa[NS] = 0.0;
    for (int i = NS-1; i >= 0; --i) {
        double rm = (i + 0.5) * dr;
        int idx = i + 1;
        double g = g_at(rm, idx);
        P_pa[i] = P_pa[i+1] + prem_rho(rm) * g * dr;
    }

    // Seismic: K(P) = K₀ + 4P, then v_p = √((K+4G/3)/ρ)
    struct KG { double K0, G0; };
    auto get_K0_G0 = [](double r) -> KG {
        double d = R_REF - r;
        if (d < 35e3)   return {40e9,  30e9};
        if (d < 410e3)  return {129e9, 80e9};
        if (d < 520e3)  return {174e9, 108e9};
        if (d < 670e3)  return {185e9, 117e9};
        if (d < 2891e3) return {253e9, 172e9};
        if (d < 5150e3) return {109e9, 0.0};
        return {165e9, 19.8e9};
    };

    // ═══════════════════════════════════════════════════════════
    //  DISPLACEMENT INVENTORY
    // ═══════════════════════════════════════════════════════════
    double n_baryons = total_rho_vol / m_u;
    double V_excl    = n_baryons * ((V_dp + V_dn)/2.0 + V_de);
    double V_Earth   = (4.0/3.0)*std::numbers::pi*R_E*R_E*R_E;
    double b         = V_excl / l_P3;
    double a_cells   = V_Earth / l_P3;

    // ═══════════════════════════════════════════════════════════
    //  OUTPUT
    // ═══════════════════════════════════════════════════════════
    std::printf("╔══════════════════════════════════════════════════════════════════════╗\n");
    std::printf("║  E97v5: SMOOTH PREM + KOPPA                                        ║\n");
    std::printf("║  ϟ = %.2f mm   g = v²/R = %.4f m/s²                              ║\n", koppa*1e3, g_surf);
    std::printf("╚══════════════════════════════════════════════════════════════════════╝\n\n");

    std::printf("  k = %.2f    z = %.6e    ϟ = %.6f mm\n", k, z, koppa*1e3);
    std::printf("  ∫ρdV = %.6e kg    baryons = %.6e\n", total_rho_vol, n_baryons);
    std::printf("  b = %.6e    a = %.6e    b/a = %.6e\n", b, a_cells, b/a_cells);
    std::printf("  V_excl = %.4f cm³    P_conv = %.6e Pa\n", V_excl*1e6, P_conv);
    std::printf("  Total F = %.6e N    Phase delay = %.3e s\n\n",
                b * Phi/l_P, (R_E/l_P)*(b/a_cells)*t_P);

    // Profile table
    std::printf("  depth   r/R     ρ(PREM)  g_SDT   g_PREM  err%%   P_SDT   P_PREM  Vp_SDT  Vp_PREM Vs_SDT  Vs_PREM\n");
    std::printf("  (km)            (kg/m³)  (m/s²)  (m/s²)         (GPa)   (GPa)   (km/s)  (km/s)  (km/s)  (km/s)\n");
    std::printf("  ─────────────────────────────────────────────────────────────────────────────────────────────────────\n");

    double depths[] = {0,25,100,200,400,600,670,1000,1500,2000,2500,2700,2891,
                       3000,3500,4000,4500,5000,5150,5500,5800,6000,6200,6371};
    int ND = sizeof(depths)/sizeof(depths[0]);

    double se_g=0,se_p=0,se_vp=0,se_vs=0;
    int ng=0,np_c=0,nvp=0,nvs=0;

    for (int q = 0; q < ND; ++q) {
        double d = depths[q];
        double r = (R_E - d*1e3);
        if (r < 0) r = 0;
        int idx = (int)(r / dr);
        if (idx < 0) idx = 0;
        if (idx > NS) idx = NS;

        double rho = prem_rho(r);
        double g_s = g_at(r, idx);
        double g_p = prem_g(r);
        double Ps  = P_pa[idx] / 1e9;

        // PREM reference pressure (approximate from their tables)
        double P_prem;
        {
            double x = d / 6371.0;
            if      (d < 670)  P_prem = d * 0.0355;
            else if (d < 2891) P_prem = 23.8 + (d-670)*0.0504;
            else if (d < 5150) P_prem = 135.8 + (d-2891)*0.0854;
            else               P_prem = 328.9 + (d-5150)*0.0287;
        }

        // Seismic velocities from SDT
        double Pp = P_pa[idx];
        KG kg = get_K0_G0(r);
        double K0 = kg.K0, G0 = kg.G0;
        double K = K0 + 4.0 * Pp;
        double Gs;
        if (G0 > 0) {
            double Psat = K0 * 3.0;
            Gs = G0 + 1.5 * Pp / (1.0 + Pp/Psat);
            if (d > 5150) {
                double Gmax = K * 0.12;
                if (Gs > Gmax) Gs = Gmax;
            }
        } else { Gs = 0; }

        double vp_s = std::sqrt((K + (4.0/3.0)*Gs) / rho) / 1e3;
        double vs_s = (Gs > 0) ? std::sqrt(Gs / rho) / 1e3 : 0.0;
        double vp_p = prem_vp(r);
        double vs_p = prem_vs(r);

        double ge = (g_p > 0.5) ? (g_s - g_p)/g_p * 100.0 : 0.0;

        std::printf("  %5.0f  %6.4f  %7.0f  %6.3f  %6.3f %+5.1f  %7.2f  %7.2f  %6.2f  %6.2f  %6.2f  %6.2f\n",
                    d, r/R_E, rho, g_s, g_p, ge, Ps, P_prem, vp_s, vp_p, vs_s, vs_p);

        // Accumulate errors
        if (g_p > 0.5 && d > 0) {
            double e = (g_s-g_p)/g_p; se_g += e*e; ng++;
        }
        if (P_prem > 1.0) {
            double e = (Ps-P_prem)/P_prem; se_p += e*e; np_c++;
        }
        if (vp_p > 1.0) {
            double e = (vp_s-vp_p)/vp_p; se_vp += e*e; nvp++;
        }
        if (vs_p > 0.5) {
            double e = (vs_s-vs_p)/vs_p; se_vs += e*e; nvs++;
        }
    }

    std::printf("\n══ RMS ERRORS (smooth PREM) ══\n");
    std::printf("  g(r)  : %5.2f%%  (%d points)\n", 100*std::sqrt(se_g/ng), ng);
    std::printf("  P(r)  : %5.2f%%  (%d points)\n", 100*std::sqrt(se_p/np_c), np_c);
    std::printf("  v_p(r): %5.2f%%  (%d points)\n", 100*std::sqrt(se_vp/nvp), nvp);
    std::printf("  v_s(r): %5.2f%%  (%d points)\n", 100*std::sqrt(se_vs/nvs), nvs);

    // Koppa table
    std::printf("\n══ KOPPA TABLE ══\n");
    std::printf("  Body       v(m/s)    R(m)           k        ϟ(mm)      g_calc    g_meas\n");
    std::printf("  ────────────────────────────────────────────────────────────────────────────\n");
    struct B { const char* n; double v,R,g; };
    B bs[] = {
        {"Earth",   7909,   6.371e6,  9.81},  {"Moon",    1680,   1.7374e6, 1.625},
        {"Mars",    3555,   3.3895e6, 3.721}, {"Venus",   7328,   6.0518e6, 8.87},
        {"Jupiter",42100,  69.911e6, 24.79},  {"Saturn", 25100,  58.232e6, 10.44},
        {"Sun",   437000,   6.957e8, 274.0},  {"Mercury", 3010,   2.4397e6, 3.70},
    };
    for (auto& b : bs) {
        double ki = c/b.v;
        double qi = b.R * b.v * b.v / (c*c);
        double gi = b.v * b.v / b.R;
        std::printf("  %-9s %6.0f  %12.4e  %8.1f  %10.3f  %7.3f   %6.3f\n",
                    b.n, b.v, b.R, ki, qi*1e3, gi, b.g);
    }

    std::printf("\n  g = v²/R. No G. No M. ϟ = v²R/c². Done.\n");
    return 0;
}
