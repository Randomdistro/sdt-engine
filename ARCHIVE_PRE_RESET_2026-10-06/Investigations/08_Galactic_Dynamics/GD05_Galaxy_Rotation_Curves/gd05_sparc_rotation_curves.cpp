// =====================================================================
//  GD05: Galaxy Rotation Curves from Eclipse Saturation
//  ---------------------------------------------------------------------
//  Drives the REAL SPARC sample (Lelli, McGaugh & Schombert 2016,
//  AJ 152, 157) through the canonical SDT 3D volumetric eclipse-
//  saturation model (GOM03 / galactic.hpp::predicted_velocity_3d).
//
//  This supersedes the earlier circular test, which generated its
//  "measured" velocities with the very SDT formula it then verified
//  (generate_mock_sparc.py) and called the deprecated 2D functions.
//  Here the velocities come from published HI/Halpha rotation curves;
//  only the baryonic geometry (M_bar, h_R) is fed to the model.
//
//  Data file (default): sparc_175.csv  [name,M_bar_Msun,h_R_kpc,
//  v_flat_kms,quality], produced by parse_sparc_mrt.py from the
//  Vizier mirror of the SPARC master table.
//
//  Certification: the gravitational coupling (koppa_per_baryon =
//  l_P^2 c m_p / hbar) is DERIVED. The occlusion cross-section
//  kappa_area_per_baryon = 9.1e-29 m^2 in galactic.hpp is CALIBRATED
//  (tuned to the historical 175 M_sun/pc^2 threshold). This driver
//  therefore reports a CALIBRATED headline plus a first-principles
//  ablation so the dependence on that one knob is explicit. Note the
//  exact degeneracy: the model depends on kappa_area and h_z only
//  through the product kappa_area * (h_R/h_z).
//
//  Author: SDT Canonical Engine — James Christopher Tyndall, Melbourne
// =====================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <set>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <sdt/galactic.hpp>

namespace meas = sdt::laws::measured;
namespace B    = sdt::laws::bridge;
using sdt::galactic::Galaxy3DProfile;
using sdt::galactic::VolumetricEclipseResult;
using sdt::galactic::predicted_velocity_3d;
using sdt::galactic::horizontal_column_density;

static constexpr double kpc_to_m = 3.085677581e19;
static constexpr double km_s     = 1000.0;
static constexpr double M_Sun    = 1.98847e30;        // matches galactic.hpp
static constexpr double PI       = 3.14159265358979323846;

// Reference cross-sections for the ablation:
static constexpr double KAPPA_CALIBRATED = 9.1e-29;   // galactic.hpp value (CALIBRATED to 175 M_sun/pc^2)
static constexpr double SIGMA_THOMSON    = 6.6524587e-29; // QED Thomson cross-section (first principles)

// Disk axial ratio. The kappa_area calibration in galactic.hpp assumes
// h_R/h_z = 10, so we adopt that as the baseline (and sweep it below).
// Empirically, edge-on disks give h_R/h_z ~ 7.3 (Kregel+2002).
static constexpr double HR_OVER_HZ_BASELINE = 10.0;

struct Galaxy {
    std::string name;
    double M_bar_Msun;
    double h_R_kpc;
    double v_flat_kms;
    int    quality;
};

std::vector<Galaxy> parse_csv(const std::string& filename) {
    std::vector<Galaxy> galaxies;
    std::set<std::string> seen;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: could not open " << filename << "\n";
        return galaxies;
    }
    std::string line;
    std::getline(file, line); // header
    int skipped_novflat = 0, skipped_dup = 0;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string tok;
        Galaxy g{};
        std::getline(ss, g.name, ',');
        std::getline(ss, tok, ','); g.M_bar_Msun = std::stod(tok);
        std::getline(ss, tok, ','); g.h_R_kpc    = std::stod(tok);
        std::getline(ss, tok, ','); g.v_flat_kms = std::stod(tok);
        std::getline(ss, tok, ','); g.quality    = tok.empty() ? 0 : std::stoi(tok);

        if (g.v_flat_kms <= 0.0 || g.h_R_kpc <= 0.0) { ++skipped_novflat; continue; }
        if (seen.count(g.name)) { ++skipped_dup; continue; }
        seen.insert(g.name);
        galaxies.push_back(g);
    }
    std::cerr << "  (parsed " << galaxies.size() << " usable galaxies; skipped "
              << skipped_novflat << " with no measured V_flat, "
              << skipped_dup << " duplicates)\n";
    return galaxies;
}

// ---------------------------------------------------------------------
// Parameterized re-implementation of galactic.hpp::predicted_velocity_3d,
// exposing kappa_area so we can run the first-principles ablation.
// Verified below to reproduce the committed engine bit-for-bit at
// kappa = KAPPA_CALIBRATED.
// ---------------------------------------------------------------------
double predict_v_peak(double M_bar_kg, double h_R_m, double h_z_m, double kappa_area) {
    if (h_R_m <= 0.0 || h_z_m <= 0.0) return 0.0;
    const double N_baryons = M_bar_kg / meas::m_p;
    const double kg_m = B::koppa_per_baryon * N_baryons;   // = G M / c^2 (DERIVED)
    double max_v = 0.0;
    const int steps = 100;
    for (int i = 1; i <= steps; ++i) {
        const double r = i * (5.0 * h_R_m) / steps;
        const double col = horizontal_column_density(r, M_bar_kg, h_R_m, h_z_m); // Lambda(r)
        const double tau = kappa_area * (col / meas::m_p);
        const double f_occ = 0.5 * (1.0 - std::exp(-tau));
        const double v_lim_sq = meas::c * meas::c * kg_m / (2.0 * r);
        const double v_lim = std::sqrt(std::max(0.0, v_lim_sq));
        const double v_test = v_lim * std::sqrt(2.0 * f_occ);
        if (v_test > max_v) max_v = v_test;
    }
    return max_v; // m/s
}

struct Stats { double rms, mean, med_abs; int n; };

Stats residual_stats(const std::vector<double>& res /* percent */) {
    Stats s{0,0,0,(int)res.size()};
    if (res.empty()) return s;
    double sumsq = 0, sum = 0;
    std::vector<double> abs_res;
    for (double r : res) { sumsq += r*r; sum += r; abs_res.push_back(std::fabs(r)); }
    s.rms = std::sqrt(sumsq / res.size());
    s.mean = sum / res.size();
    std::sort(abs_res.begin(), abs_res.end());
    s.med_abs = abs_res[abs_res.size()/2];
    return s;
}

// OLS slope of y on x  ->  returns d(logM)/d(logV) for BTFR when called (logV, logM)
double ols_slope(const std::vector<double>& x, const std::vector<double>& y) {
    double sx=0, sy=0, sxy=0, sxx=0; size_t n=x.size();
    for (size_t i=0;i<n;++i){ sx+=x[i]; sy+=y[i]; sxy+=x[i]*y[i]; sxx+=x[i]*x[i]; }
    double denom = n*sxx - sx*sx;
    return (denom!=0.0) ? (n*sxy - sx*sy)/denom : 0.0;
}

int main(int argc, char** argv) {
    std::cout << "================================================================\n";
    std::cout << " GD05: Galaxy Rotation Curves from Eclipse Saturation\n";
    std::cout << " Real SPARC sample  x  SDT 3D volumetric model (GOM03)\n";
    std::cout << "================================================================\n\n";

    std::string filename = (argc > 1) ? argv[1] : "sparc_175.csv";
    auto galaxies = parse_csv(filename);
    if (galaxies.empty()) { std::cout << "No galaxies. Exiting.\n"; return 1; }

    // ---- Self-check: local predictor must match the committed engine ----
    {
        const Galaxy& g = galaxies.front();
        double M_kg = g.M_bar_Msun * M_Sun;
        double hR = g.h_R_kpc * kpc_to_m;
        double hz = hR / HR_OVER_HZ_BASELINE;
        Galaxy3DProfile prof{M_kg, hR, hz, 0.0, PI/2.0};
        double v_engine = predicted_velocity_3d(3.0*hR, prof).predicted_velocity_m_s;
        double v_local  = predict_v_peak(M_kg, hR, hz, KAPPA_CALIBRATED);
        double drift = std::fabs(v_engine - v_local) / std::max(1.0, v_engine);
        std::cout << "[self-check] engine vs local predictor on " << g.name
                  << ": " << v_engine/km_s << " vs " << v_local/km_s
                  << " km/s  (drift " << drift*100 << "%)\n\n";
    }

    std::cout << "Loaded " << galaxies.size() << " real SPARC galaxies from "
              << filename << "\n";
    std::cout << "h_z prescription: h_z = h_R / " << HR_OVER_HZ_BASELINE
              << " (matches kappa_area calibration)\n\n";

    // ---- Headline run: committed engine, calibrated kappa ----
    std::vector<double> res_pct;
    std::vector<double> logV_obs, logM, logV_sdt;
    std::vector<Galaxy> sample = galaxies;

    std::cout << std::left << std::setw(16) << "Galaxy"
              << std::right << std::setw(13) << "M_bar(Msun)"
              << std::setw(10) << "V_obs" << std::setw(10) << "V_SDT"
              << std::setw(11) << "Resid(%)" << std::setw(4) << "Q" << "\n";
    std::cout << std::string(64,'-') << "\n";

    int shown = 0;
    for (const auto& g : sample) {
        double M_kg = g.M_bar_Msun * M_Sun;
        double hR   = g.h_R_kpc * kpc_to_m;
        double hz   = hR / HR_OVER_HZ_BASELINE;
        Galaxy3DProfile prof{M_kg, hR, hz, 0.0, PI/2.0};
        double v_sdt = predicted_velocity_3d(3.0*hR, prof).predicted_velocity_m_s / km_s;

        double resid = (g.v_flat_kms - v_sdt) / g.v_flat_kms * 100.0;
        res_pct.push_back(resid);

        if (v_sdt > 0) {
            logV_obs.push_back(std::log10(g.v_flat_kms));
            logM.push_back(std::log10(g.M_bar_Msun));
            logV_sdt.push_back(std::log10(v_sdt));
        }

        if (shown < 8 || shown >= (int)sample.size()-4) {
            std::cout << std::left << std::setw(16) << g.name
                      << std::right << std::setw(13) << std::scientific << std::setprecision(2) << g.M_bar_Msun
                      << std::setw(10) << std::fixed << std::setprecision(1) << g.v_flat_kms
                      << std::setw(10) << v_sdt
                      << std::setw(10) << std::showpos << std::setprecision(1) << resid << std::noshowpos << "%"
                      << std::setw(4) << g.quality << "\n";
        } else if (shown == 8) {
            std::cout << "   ... (" << sample.size()-12 << " more) ...\n";
        }
        ++shown;
    }
    std::cout << std::string(64,'-') << "\n\n";

    Stats s = residual_stats(res_pct);
    std::cout << "=== HEADLINE RESULT (committed engine, CALIBRATED kappa = "
              << std::scientific << std::setprecision(2) << KAPPA_CALIBRATED << " m^2) ===\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Galaxies analysed:        " << s.n << "\n";
    std::cout << "RMS residual:             " << s.rms << " %\n";
    std::cout << "Mean residual (bias):     " << std::showpos << s.mean << std::noshowpos << " %\n";
    std::cout << "Median |residual|:        " << s.med_abs << " %\n\n";

    double btfr_obs = ols_slope(logV_obs, logM);   // d(logM)/d(logV)
    double btfr_sdt = ols_slope(logV_sdt, logM);
    std::cout << "=== BARYONIC TULLY-FISHER  (M_bar ~ v^alpha) ===\n";
    std::cout << "Observed slope (data):    " << btfr_obs << "\n";
    std::cout << "SDT-predicted slope:      " << btfr_sdt << "\n";
    std::cout << "Literature expectation:   ~3.5 - 4.0\n\n";

    // ---- Per-quality breakdown ----
    std::cout << "=== RMS by SPARC quality flag ===\n";
    for (int q = 1; q <= 3; ++q) {
        std::vector<double> r;
        for (size_t i=0;i<sample.size();++i) if (sample[i].quality==q) r.push_back(res_pct[i]);
        if (!r.empty()) {
            Stats sq = residual_stats(r);
            std::cout << "  Q" << q << " (n=" << sq.n << "):  RMS "
                      << sq.rms << " %,  bias " << std::showpos << sq.mean << std::noshowpos << " %\n";
        }
    }
    std::cout << "\n";

    // ---- Ablation 1: cross-section choice (first-principles vs calibrated) ----
    std::cout << "=== ABLATION: occlusion cross-section kappa_area ===\n";
    std::cout << std::left << std::setw(34) << "kappa_area [m^2]"
              << std::right << std::setw(12) << "RMS(%)"
              << std::setw(14) << "BTFR slope" << "\n";
    struct KOpt { const char* label; double kappa; };
    KOpt kopts[] = {
        {"0.50 x Thomson",            0.5*SIGMA_THOMSON},
        {"Thomson sigma_T (1st-prin)", SIGMA_THOMSON},
        {"calibrated 9.1e-29",         KAPPA_CALIBRATED},
        {"2x calibrated",              2.0*KAPPA_CALIBRATED},
        {"10x calibrated",             10.0*KAPPA_CALIBRATED},
    };
    for (auto& ko : kopts) {
        std::vector<double> r, lV, lM;
        for (const auto& g : sample) {
            double M_kg=g.M_bar_Msun*M_Sun, hR=g.h_R_kpc*kpc_to_m, hz=hR/HR_OVER_HZ_BASELINE;
            double v=predict_v_peak(M_kg,hR,hz,ko.kappa)/km_s;
            r.push_back((g.v_flat_kms-v)/g.v_flat_kms*100.0);
            if (v>0){ lV.push_back(std::log10(v)); lM.push_back(std::log10(g.M_bar_Msun)); }
        }
        Stats sk=residual_stats(r);
        std::cout << std::left << std::setw(34) << ko.label
                  << std::right << std::setw(12) << std::fixed << std::setprecision(1) << sk.rms
                  << std::setw(14) << std::setprecision(2) << ols_slope(lV,lM) << "\n";
    }
    std::cout << "\n";

    // ---- Ablation 2: disk thickness h_R/h_z (shows kappa<->h_z degeneracy) ----
    std::cout << "=== ABLATION: disk axial ratio h_R/h_z (calibrated kappa) ===\n";
    std::cout << std::left << std::setw(34) << "h_R/h_z"
              << std::right << std::setw(12) << "RMS(%)" << std::setw(14) << "BTFR slope" << "\n";
    for (double q : {5.0, 7.3, 10.0, 20.0}) {
        std::vector<double> r, lV, lM;
        for (const auto& g : sample) {
            double M_kg=g.M_bar_Msun*M_Sun, hR=g.h_R_kpc*kpc_to_m, hz=hR/q;
            double v=predict_v_peak(M_kg,hR,hz,KAPPA_CALIBRATED)/km_s;
            r.push_back((g.v_flat_kms-v)/g.v_flat_kms*100.0);
            if (v>0){ lV.push_back(std::log10(v)); lM.push_back(std::log10(g.M_bar_Msun)); }
        }
        Stats sk=residual_stats(r);
        std::ostringstream lab; lab<<q;
        std::cout << std::left << std::setw(34) << lab.str()
                  << std::right << std::setw(12) << std::fixed << std::setprecision(1) << sk.rms
                  << std::setw(14) << std::setprecision(2) << ols_slope(lV,lM) << "\n";
    }
    std::cout << "\n";

    // ---- Verdict ----
    std::cout << "=== VERDICT ===\n";
    bool pass_rms  = s.rms < 20.0;
    bool pass_btfr = std::fabs(btfr_sdt - 4.0) < 1.0;
    std::cout << "[" << (pass_rms?"PASS":"FAIL") << "] RMS residual < 20% target  (got "
              << std::setprecision(1) << s.rms << "%)\n";
    std::cout << "[" << (pass_btfr?"PASS":"FAIL") << "] BTFR slope ~ 4  (got "
              << std::setprecision(2) << btfr_sdt << ")\n";
    std::cout << "\nCertification: CALIBRATED (1 fitted parameter: kappa_area, tuned to\n"
              << "175 M_sun/pc^2). Gravitational coupling koppa_per_baryon is DERIVED.\n"
              << "Zero-parameter status is NOT yet achieved for galaxy rotation.\n";
    return 0;
}
