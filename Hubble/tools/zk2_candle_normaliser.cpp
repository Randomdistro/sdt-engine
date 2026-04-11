// ==============================================================
// zk²=1 STANDARD CANDLE NORMALISER
//
// Program:
//   For each host galaxy with a SN Ia AND multiple calibrators:
//   1. Record RAW measured spectral z for each phenomenon
//      (SN Ia, Cepheid, TRGB, JAGB, Mira)
//   2. DO NOT prenormalise
//   3. Normalise all five using each as calibrator in turn
//   4. Check for anomalies
//
// z is z. λ_observed / λ_emitted. Measured from lines.
// No distances. No derived values. Just light.
//
// The only constant is c.
// ==============================================================

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <numeric>

constexpr double c = 2.99792458e8;

// ==============================================================
// A calibrator measurement in a galaxy
// ==============================================================
struct Calibrator {
    std::string type;       // "SN_Ia", "Cepheid", "TRGB", "JAGB", "Mira"
    std::string id;         // specific object ID
    double z_raw;           // RAW measured z from spectral lines (heliocentric)
    double lambda_obs;      // representative observed wavelength (Angstrom)
    double lambda_lab;      // lab rest wavelength (Angstrom)
    double mu;              // distance modulus (observed, not derived)
    bool present;           // is this calibrator available in this galaxy?
};

// ==============================================================
// A host galaxy with multiple calibrators
// ==============================================================
struct Galaxy {
    std::string name;
    double z_helio;         // heliocentric z of the galaxy (from NED)
    std::string sn_name;    // SN Ia name
    std::vector<Calibrator> calibrators;
};

std::string sci(double v, int p = 4) {
    std::ostringstream s; s << std::scientific << std::setprecision(p) << v; return s.str();
}
std::string fix(double v, int p = 4) {
    std::ostringstream s; s << std::fixed << std::setprecision(p) << v; return s.str();
}

// ==============================================================
// KEY SPECTRAL LINES USED FOR EACH CALIBRATOR TYPE
//
// SN Ia:    Si II 6355 A (primary), Ca II H&K 3934/3969 A
// Cepheid:  H-alpha 6563 A, Ca II triplet 8498/8542/8662 A
// TRGB:     Ca II triplet, Fe I lines, TiO bands
// JAGB:     C₂ Swan bands (5165 A), CN bands (4215 A)
// Mira:     TiO bands (7050 A), VO bands (7400 A)
// ==============================================================

// Representative line for each type (used for normalisation)
double lab_line(const std::string& type) {
    if (type == "SN_Ia")   return 6355.0;  // Si II
    if (type == "Cepheid") return 6563.0;  // H-alpha
    if (type == "TRGB")    return 8542.0;  // Ca II triplet
    if (type == "JAGB")    return 5165.0;  // C₂ Swan band
    if (type == "Mira")    return 7050.0;  // TiO band
    return 0.0;
}

Calibrator make_cal(const std::string& type, const std::string& id,
                    double z_galaxy, bool present) {
    Calibrator cal;
    cal.type = type;
    cal.id = id;
    cal.present = present;
    cal.lambda_lab = lab_line(type);
    // RAW: observed wavelength = lab * (1 + z)
    // z_raw IS the galaxy z (measured from this line or the galaxy's lines)
    // We DO NOT prenormalise — this is the raw measurement
    cal.z_raw = z_galaxy;
    cal.lambda_obs = cal.lambda_lab * (1.0 + z_galaxy);
    cal.mu = 0.0;  // filled in if available
    return cal;
}

int main() {
    // ==============================================================
    // HOST GALAXIES WITH MULTIPLE CALIBRATORS
    //
    // z_helio: from NED (heliocentric, spectroscopic)
    // Each galaxy has: SN Ia + subset of {Cepheid, TRGB, JAGB, Mira}
    //
    // Galaxies chosen: those with the MOST calibrator overlap
    // SH0ES anchor + Freedman CCHP + Madore JAGB overlap
    // ==============================================================

    std::vector<Galaxy> galaxies;

    // --- NGC 4258 (Maser anchor galaxy, Cepheid + TRGB + JAGB) ---
    // No SN Ia in this galaxy, but it's the geometric anchor
    {
        Galaxy g;
        g.name = "NGC 4258";
        g.z_helio = 0.001494;
        g.sn_name = "(anchor)";
        g.calibrators.push_back(make_cal("SN_Ia",   "none",       g.z_helio, false));
        g.calibrators.push_back(make_cal("Cepheid", "Ceph-N4258", g.z_helio, true));
        g.calibrators.push_back(make_cal("TRGB",    "TRGB-N4258", g.z_helio, true));
        g.calibrators.push_back(make_cal("JAGB",    "JAGB-N4258", g.z_helio, true));
        g.calibrators.push_back(make_cal("Mira",    "none",       g.z_helio, false));
        galaxies.push_back(g);
    }

    // --- NGC 1365 (SN 2012fr, Cepheid + TRGB) ---
    {
        Galaxy g;
        g.name = "NGC 1365";
        g.z_helio = 0.005457;
        g.sn_name = "SN 2012fr";
        g.calibrators.push_back(make_cal("SN_Ia",   "2012fr",       g.z_helio, true));
        g.calibrators.push_back(make_cal("Cepheid", "Ceph-N1365",   g.z_helio, true));
        g.calibrators.push_back(make_cal("TRGB",    "TRGB-N1365",   g.z_helio, true));
        g.calibrators.push_back(make_cal("JAGB",    "JAGB-N1365",   g.z_helio, true));
        g.calibrators.push_back(make_cal("Mira",    "none",         g.z_helio, false));
        galaxies.push_back(g);
    }

    // --- NGC 5584 (SN 2007af, Cepheid + TRGB) ---
    {
        Galaxy g;
        g.name = "NGC 5584";
        g.z_helio = 0.005464;
        g.sn_name = "SN 2007af";
        g.calibrators.push_back(make_cal("SN_Ia",   "2007af",       g.z_helio, true));
        g.calibrators.push_back(make_cal("Cepheid", "Ceph-N5584",   g.z_helio, true));
        g.calibrators.push_back(make_cal("TRGB",    "TRGB-N5584",   g.z_helio, true));
        g.calibrators.push_back(make_cal("JAGB",    "none",         g.z_helio, false));
        g.calibrators.push_back(make_cal("Mira",    "none",         g.z_helio, false));
        galaxies.push_back(g);
    }

    // --- NGC 1309 (SN 2002fk, Cepheid + TRGB) ---
    {
        Galaxy g;
        g.name = "NGC 1309";
        g.z_helio = 0.007125;
        g.sn_name = "SN 2002fk";
        g.calibrators.push_back(make_cal("SN_Ia",   "2002fk",       g.z_helio, true));
        g.calibrators.push_back(make_cal("Cepheid", "Ceph-N1309",   g.z_helio, true));
        g.calibrators.push_back(make_cal("TRGB",    "TRGB-N1309",   g.z_helio, true));
        g.calibrators.push_back(make_cal("JAGB",    "none",         g.z_helio, false));
        g.calibrators.push_back(make_cal("Mira",    "none",         g.z_helio, false));
        galaxies.push_back(g);
    }

    // --- NGC 3370 (SN 1994ae, Cepheid + TRGB) ---
    {
        Galaxy g;
        g.name = "NGC 3370";
        g.z_helio = 0.004266;
        g.sn_name = "SN 1994ae";
        g.calibrators.push_back(make_cal("SN_Ia",   "1994ae",       g.z_helio, true));
        g.calibrators.push_back(make_cal("Cepheid", "Ceph-N3370",   g.z_helio, true));
        g.calibrators.push_back(make_cal("TRGB",    "TRGB-N3370",   g.z_helio, true));
        g.calibrators.push_back(make_cal("JAGB",    "none",         g.z_helio, false));
        g.calibrators.push_back(make_cal("Mira",    "none",         g.z_helio, false));
        galaxies.push_back(g);
    }

    // --- NGC 4536 (SN 1981B, Cepheid + TRGB) ---
    {
        Galaxy g;
        g.name = "NGC 4536";
        g.z_helio = 0.006031;
        g.sn_name = "SN 1981B";
        g.calibrators.push_back(make_cal("SN_Ia",   "1981B",        g.z_helio, true));
        g.calibrators.push_back(make_cal("Cepheid", "Ceph-N4536",   g.z_helio, true));
        g.calibrators.push_back(make_cal("TRGB",    "TRGB-N4536",   g.z_helio, true));
        g.calibrators.push_back(make_cal("JAGB",    "none",         g.z_helio, false));
        g.calibrators.push_back(make_cal("Mira",    "none",         g.z_helio, false));
        galaxies.push_back(g);
    }

    // --- NGC 4639 (SN 1990N, Cepheid + TRGB) ---
    {
        Galaxy g;
        g.name = "NGC 4639";
        g.z_helio = 0.003395;
        g.sn_name = "SN 1990N";
        g.calibrators.push_back(make_cal("SN_Ia",   "1990N",        g.z_helio, true));
        g.calibrators.push_back(make_cal("Cepheid", "Ceph-N4639",   g.z_helio, true));
        g.calibrators.push_back(make_cal("TRGB",    "TRGB-N4639",   g.z_helio, true));
        g.calibrators.push_back(make_cal("JAGB",    "none",         g.z_helio, false));
        g.calibrators.push_back(make_cal("Mira",    "none",         g.z_helio, false));
        galaxies.push_back(g);
    }

    // --- M101 (SN 2011fe, Cepheid + TRGB + JAGB — richest overlap) ---
    {
        Galaxy g;
        g.name = "M101";
        g.z_helio = 0.000804;
        g.sn_name = "SN 2011fe";
        g.calibrators.push_back(make_cal("SN_Ia",   "2011fe",       g.z_helio, true));
        g.calibrators.push_back(make_cal("Cepheid", "Ceph-M101",    g.z_helio, true));
        g.calibrators.push_back(make_cal("TRGB",    "TRGB-M101",    g.z_helio, true));
        g.calibrators.push_back(make_cal("JAGB",    "JAGB-M101",    g.z_helio, true));
        g.calibrators.push_back(make_cal("Mira",    "none",         g.z_helio, false));
        galaxies.push_back(g);
    }

    // --- NGC 1448 (SN 2001el + SN 2021pit, Cepheid + TRGB + Mira) ---
    {
        Galaxy g;
        g.name = "NGC 1448";
        g.z_helio = 0.003897;
        g.sn_name = "SN 2001el";
        g.calibrators.push_back(make_cal("SN_Ia",   "2001el",       g.z_helio, true));
        g.calibrators.push_back(make_cal("Cepheid", "Ceph-N1448",   g.z_helio, true));
        g.calibrators.push_back(make_cal("TRGB",    "TRGB-N1448",   g.z_helio, true));
        g.calibrators.push_back(make_cal("JAGB",    "none",         g.z_helio, false));
        g.calibrators.push_back(make_cal("Mira",    "Mira-N1448",   g.z_helio, true));
        galaxies.push_back(g);
    }

    // ==============================================================
    // SECTION 1: RAW FLOOR MEASUREMENT
    // ==============================================================

    std::cout << "================================================================================\n";
    std::cout << "  STANDARD CANDLE NORMALISER — RAW FLOOR MEASUREMENT\n";
    std::cout << "================================================================================\n\n";

    std::cout << "  z = lambda_observed / lambda_emitted - 1  (from spectral lines)\n";
    std::cout << "  k = 1/sqrt(z)\n";
    std::cout << "  zk^2 = 1 (always)\n";
    std::cout << "  NO prenormalisation. These are the raw numbers.\n\n";

    for (auto& g : galaxies) {
        double k_gal = 1.0 / std::sqrt(g.z_helio);

        std::cout << "--- " << g.name << " (SN: " << g.sn_name
                  << ") z_helio = " << fix(g.z_helio, 6)
                  << "  k = " << fix(k_gal, 2)
                  << "  zk^2 = " << fix(g.z_helio * k_gal * k_gal, 6) << " ---\n";

        std::cout << std::left
                  << std::setw(10) << "  Type"
                  << std::setw(16) << "ID"
                  << std::right
                  << std::setw(10) << "lam_lab"
                  << std::setw(12) << "lam_obs"
                  << std::setw(14) << "z_raw"
                  << std::setw(12) << "k"
                  << std::setw(10) << "zk^2"
                  << "\n";

        for (auto& cal : g.calibrators) {
            if (!cal.present) continue;
            double k = 1.0 / std::sqrt(cal.z_raw);
            std::cout << std::left
                      << "  " << std::setw(8) << cal.type
                      << std::setw(16) << cal.id
                      << std::right
                      << std::setw(10) << fix(cal.lambda_lab, 1)
                      << std::setw(12) << fix(cal.lambda_obs, 1)
                      << std::setw(14) << sci(cal.z_raw)
                      << std::setw(12) << fix(k, 2)
                      << std::setw(10) << fix(cal.z_raw * k * k, 6)
                      << "\n";
        }
        std::cout << "\n";
    }

    // ==============================================================
    // SECTION 2: NORMALISATION — CALIBRATE TO EACH PHENOMENON
    //
    // For each calibrator type C:
    //   z_norm(X) = z_raw(X) - z_raw(C)
    //   = how much does phenomenon X differ from calibrator C
    //     within the SAME galaxy
    //
    // If all phenomena share the same z (same spatial displacement):
    //   z_norm → 0 for all X
    //
    // If there are anomalies:
    //   z_norm ≠ 0 → that phenomenon has EXTRA or MISSING displacement
    // ==============================================================

    std::cout << "================================================================================\n";
    std::cout << "  NORMALISATION — CALIBRATE TO EACH PHENOMENON IN TURN\n";
    std::cout << "================================================================================\n\n";

    std::cout << "  z_residual = z_raw(X) - z_raw(calibrator)\n";
    std::cout << "  If all calibrators share the same spatial displacement,\n";
    std::cout << "  residuals should be ZERO.\n\n";
    std::cout << "  Non-zero residual = anomaly = extra displacement at that source.\n\n";

    // Calibrator types to use as reference
    std::vector<std::string> cal_types = {"Cepheid", "TRGB", "JAGB", "SN_Ia"};

    for (auto& ref_type : cal_types) {
        std::cout << "--- CALIBRATOR: " << ref_type << " ---\n";
        std::cout << std::left
                  << std::setw(12) << "  Galaxy"
                  << std::right
                  << std::setw(14) << "z_" + ref_type;

        // Other types as columns
        std::vector<std::string> other_types;
        for (auto& t : std::vector<std::string>{"SN_Ia", "Cepheid", "TRGB", "JAGB", "Mira"}) {
            if (t != ref_type) {
                other_types.push_back(t);
                std::cout << std::setw(14) << "dz_" + t;
            }
        }
        std::cout << "\n";

        for (auto& g : galaxies) {
            // Find the reference calibrator
            double z_ref = -1;
            for (auto& cal : g.calibrators) {
                if (cal.type == ref_type && cal.present) {
                    z_ref = cal.z_raw;
                    break;
                }
            }
            if (z_ref < 0) continue; // ref not present in this galaxy

            std::cout << std::left << "  " << std::setw(10) << g.name
                      << std::right << std::setw(14) << sci(z_ref);

            for (auto& otype : other_types) {
                bool found = false;
                for (auto& cal : g.calibrators) {
                    if (cal.type == otype && cal.present) {
                        double dz = cal.z_raw - z_ref;
                        std::cout << std::setw(14) << sci(dz);
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    std::cout << std::setw(14) << "---";
                }
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    // ==============================================================
    // SECTION 3: BLUESHIFT NORMALISATION — REST FRAME RECOVERY
    //
    // For each SN Ia: compute lambda_rest = lambda_obs / (1 + z)
    // Compare recovered rest-frame lines across all galaxies
    // ==============================================================

    std::cout << "================================================================================\n";
    std::cout << "  BLUESHIFT NORMALISATION — WHAT DID THE SN Ia ACTUALLY LOOK LIKE?\n";
    std::cout << "================================================================================\n\n";

    std::cout << "  lambda_rest = lambda_obs / (1 + z_galaxy)\n";
    std::cout << "  If SN Ia are truly standard, recovered lambda_rest should\n";
    std::cout << "  match lab Si II 6355 A in every case.\n\n";

    // Key SN Ia lines
    struct Line { std::string name; double lab; };
    std::vector<Line> sn_lines = {
        {"Si II",     6355.0},
        {"Ca II H",   3934.0},
        {"Ca II K",   3969.0},
        {"S II",      5454.0},
        {"S II",      5640.0},
        {"Fe II",     4555.0},
    };

    std::cout << std::left << std::setw(12) << "  Galaxy"
              << std::setw(14) << "z_helio";
    for (auto& l : sn_lines) {
        std::cout << std::setw(12) << l.name + "_obs"
                  << std::setw(12) << l.name + "_rest";
    }
    std::cout << std::setw(10) << "MATCH?" << "\n";
    std::cout << std::string(12 + 14 + sn_lines.size() * 24 + 10, '-') << "\n";

    for (auto& g : galaxies) {
        bool has_sn = false;
        for (auto& cal : g.calibrators) {
            if (cal.type == "SN_Ia" && cal.present) { has_sn = true; break; }
        }
        if (!has_sn) continue;

        std::cout << std::left << "  " << std::setw(10) << g.name
                  << std::right << std::setw(14) << fix(g.z_helio, 6);

        bool all_match = true;
        for (auto& l : sn_lines) {
            double obs = l.lab * (1.0 + g.z_helio);
            double rest = obs / (1.0 + g.z_helio);
            double error = std::abs(rest - l.lab);
            if (error > 0.01) all_match = false;

            std::cout << std::setw(12) << fix(obs, 1)
                      << std::setw(12) << fix(rest, 1);
        }
        std::cout << std::setw(10) << (all_match ? "YES" : "ANOMALY") << "\n";
    }

    // ==============================================================
    // SECTION 4: CROSS-GALAXY COMPARISON
    // ==============================================================

    std::cout << "\n================================================================================\n";
    std::cout << "  CROSS-GALAXY COMPARISON — ARE STANDARD CANDLES STANDARD?\n";
    std::cout << "================================================================================\n\n";

    std::cout << "  For EACH calibrator type, compute the spread in z across galaxies.\n";
    std::cout << "  z_galaxy is the same for all calibrators in one galaxy (by assumption).\n";
    std::cout << "  The test is: does the NORMALISED luminosity/period change with z?\n\n";

    std::cout << "  KEY QUESTION:\n";
    std::cout << "  If a Cepheid at z=0.001 and a Cepheid at z=0.007 are both\n";
    std::cout << "  blueshifted to rest frame, do their periods and luminosities match?\n";
    std::cout << "  If YES: standard candle holds.\n";
    std::cout << "  If NO:  something changes with z — and THAT is the anomaly.\n\n";

    // Sort galaxies by z
    auto sorted = galaxies;
    std::sort(sorted.begin(), sorted.end(),
              [](const Galaxy& a, const Galaxy& b) { return a.z_helio < b.z_helio; });

    std::cout << std::left << std::setw(12) << "  Galaxy"
              << std::right
              << std::setw(12) << "z_helio"
              << std::setw(10) << "k"
              << std::setw(10) << "zk^2"
              << std::setw(8) << "SN_Ia"
              << std::setw(8) << "Ceph"
              << std::setw(8) << "TRGB"
              << std::setw(8) << "JAGB"
              << std::setw(8) << "Mira"
              << std::setw(8) << "N_cal"
              << "\n";
    std::cout << std::string(92, '-') << "\n";

    for (auto& g : sorted) {
        double k = 1.0 / std::sqrt(g.z_helio);
        int n_cal = 0;

        std::cout << std::left << "  " << std::setw(10) << g.name
                  << std::right
                  << std::setw(12) << fix(g.z_helio, 6)
                  << std::setw(10) << fix(k, 2)
                  << std::setw(10) << fix(g.z_helio * k * k, 6);

        for (auto& cal : g.calibrators) {
            std::cout << std::setw(8) << (cal.present ? "YES" : "---");
            if (cal.present) n_cal++;
        }
        std::cout << std::setw(8) << n_cal << "\n";
    }

    std::cout << "\n================================================================================\n";
    std::cout << "  RESULT\n";
    std::cout << "================================================================================\n\n";

    std::cout << "  In this initial run, z_raw is the same for all calibrators\n";
    std::cout << "  in a single galaxy (= galaxy's heliocentric z from NED).\n";
    std::cout << "  Therefore all residuals are zero by construction.\n\n";

    std::cout << "  TO REVEAL REAL ANOMALIES, the next step requires:\n";
    std::cout << "  1. Individual spectroscopic z per calibrator object\n";
    std::cout << "     (not just the galaxy z, but each Cepheid's own lines)\n";
    std::cout << "  2. Time-dilation check: SN Ia light curves stretch by (1+z)\n";
    std::cout << "     in standard model. Does zk^2=1 predict this?\n";
    std::cout << "  3. Approaching vs receding halves of each galaxy\n";
    std::cout << "     (rotation curve → z gradient across the disk)\n\n";

    std::cout << "  The framework is ready. The data needs to be per-object.\n";
    std::cout << "  z is z. The light will tell us.\n\n";

    return 0;
}
