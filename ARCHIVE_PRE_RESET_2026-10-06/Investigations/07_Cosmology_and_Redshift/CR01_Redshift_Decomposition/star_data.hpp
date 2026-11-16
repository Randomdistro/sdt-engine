// =============================================================================
// CR01 — Gravitational Redshift Decomposition
// star_data.hpp — Observational catalogue (NASA Exoplanet Archive + literature)
//
// All values are RAW OBSERVATIONAL inputs only:
//   - log_g     : spectroscopic surface gravity [log10(cm/s²)]
//   - T_eff     : effective temperature [K]         (spectral fit)
//   - R_star    : stellar radius [solar radii]      (interferometry or L+Teff)
//   - parallax  : [mas]                             (Gaia/HIPPARCOS)
//   - dist_pc   : distance [parsecs]                (1000/parallax)
//   - radv      : systemic radial velocity [km/s]   (spectroscopy)
//   - planets   : per-planet { period_days, rp_rs, t_transit_hrs, K_ms }
//
// NO G, NO M used anywhere in this file.
// All derived quantities computed in solvers from these inputs only.
// =============================================================================

#pragma once
#define _USE_MATH_DEFINES
#include <vector>
#include <string>
#include <cmath>
#ifndef M_PI
  static constexpr double M_PI = 3.14159265358979323846;
#endif


namespace cr01 {

constexpr double c_ms     = 299792458.0;    // speed of light [m/s]
constexpr double c_cms    = 2.99792458e10;  // speed of light [cm/s]
constexpr double R_sun_m  = 6.957e8;        // solar radius [m]
constexpr double sigma_sb = 5.670374419e-8; // Stefan-Boltzmann [W/m²/K⁴]
constexpr double L_sun_W  = 3.828e26;       // solar luminosity [W]
constexpr double AU_m     = 1.495978707e11; // 1 AU [m]
constexpr double pc_m     = 3.085677581e16; // 1 parsec [m]
constexpr double m_p_kg   = 1.67262192e-27; // proton mass [kg]
constexpr double H0_kms_Mpc = 70.0;         // Hubble constant [km/s/Mpc] — used only for z_cosmo estimate

struct Planet {
    std::string name;
    double period_days;   // orbital period [days]          — from transit timing
    double rp_rs;         // Rp/Rs ratio                    — from transit depth sqrt
    double t_transit_hrs; // transit duration [hours]        — from photometry
    double K_ms;          // RV semi-amplitude [m/s]         — from spectroscopy (0 if unknown)
    double eccentricity;  // orbital eccentricity e          — from RV or transit timing (0 = circular)
};

// SDT vis-viva: v²= c²Ϟ(2/r - 1/a)
// For circular orbit (e=0): r=a, reduces to v = c√(Ϟ/a)
// For eccentric orbit: use instantaneous r. At transit r ≈ a(1-e²)/(1+e·cos(ω))
// For period→Ϟ derivation always use semi-major axis a.
inline double sdt_visviva_v(double Koppa_m, double r_m, double a_m) {
    double v2 = c_ms * c_ms * Koppa_m * (2.0/r_m - 1.0/a_m);
    return (v2 > 0.0) ? sqrt(v2) : 0.0;
}

struct StarRecord {
    std::string name;
    double T_eff_K;       // effective temperature [K]
    double log_g;         // spectroscopic log g [log10(cm/s²)]
    double R_star_Rsun;   // stellar radius [R_sun]  (0 = derive from L and T_eff)
    double L_star_Lsun;   // luminosity [L_sun]      (0 = unknown)
    double parallax_mas;  // parallax [mas]
    double radv_kms;      // systemic RV [km/s]      (NaN = unknown)
    std::vector<Planet> planets;

    // Derived accessors — no G, no M
    double dist_pc()    const { return 1000.0 / parallax_mas; }
    double dist_m()     const { return dist_pc() * pc_m; }

    // g from spectroscopic log g [m/s²]
    double g_ms2()      const { return pow(10.0, log_g) * 1e-2; } // cm/s² → m/s²

    // R from angular diameter if available, else from L+Teff
    double R_m() const {
        if (R_star_Rsun > 0.0) return R_star_Rsun * R_sun_m;
        if (L_star_Lsun > 0.0 && T_eff_K > 0.0) {
            double L = L_star_Lsun * L_sun_W;
            double R2 = L / (4.0 * M_PI * sigma_sb * pow(T_eff_K, 4.0));
            return sqrt(R2);
        }
        return 0.0;
    }

    // Ϟ_star = g R² / c²  [m]
    double Koppa_m() const {
        double R = R_m();
        double g = g_ms2();
        return g * R * R / (c_ms * c_ms);
    }

    // z_grav = Ϟ/R
    double z_grav() const {
        double R = R_m();
        if (R <= 0.0) return 0.0;
        return Koppa_m() / R;
    }
};

// =============================================================================
// CATALOGUE
// Sources: NASA Exoplanet Archive pscomppars + stellarhosts (fetched 2026-05-09)
//          Literature values for nearest stars and well-characterised systems.
// =============================================================================

inline std::vector<StarRecord> load_catalogue() {
    return {

    // -------------------------------------------------------------------------
    // NEAREST STARS (< 6 pc)
    // -------------------------------------------------------------------------

    { "Proxima Centauri",
      2992.0, 5.20,   // T_eff, log_g
      0.1019, 0.00155, // R [Rsun], L [Lsun]
      768.50, 0.0,      // parallax [mas], RV [km/s]
      {{ "Proxima b", 11.186, 0.0, 0.0, 1.38 }}  // RV only, no transit
    },

    { "Alpha Centauri A",
      5790.0, 4.32,
      1.232, 1.519,
      742.12, -21.4,
      {} // no confirmed planets
    },

    { "Alpha Centauri B",
      5178.0, 4.52,
      0.880, 0.500,
      742.12, -21.4,
      {} // no confirmed planets
    },

    { "Barnard's Star",
      3259.0, 5.076,
      0.194, 0.0,
      547.45, -110.6,
      {} // Barnard b is disputed
    },

    { "GJ 411 (Lalande 21185)",
      3720.0, 4.895,
      0.369, 0.0,
      392.40, -84.7,
      {}
    },

    { "Epsilon Eridani",
      5065.0, 4.611,
      0.755, 0.339,
      312.22, 15.5,
      {} // known RV planet, no transit
    },

    // -------------------------------------------------------------------------
    // VERY NEARBY MULTI-PLANET SYSTEMS (< 15 pc)
    // -------------------------------------------------------------------------

    { "GJ 1214",  // 14.6 pc — water world
      3101.0, 5.029,
      0.216, 0.0,
      68.265, 20.91,
      {{ "GJ 1214 b", 1.5804, 0.1160, 0.870, 14.38 }}
    },

    { "GJ 436",  // 9.75 pc — warm Neptune
      3500.0, 4.843,
      0.455, 0.0,
      102.501, 9.6,
      {{ "GJ 436 b", 2.6439, 0.0822, 1.005, 17.09 }}
    },

    { "HD 219134",  // 6.53 pc — rocky multi-planet
      4699.0, 4.567,
      0.778, 0.0,
      153.081, -18.42,
      {
        { "HD 219134 b",  3.0929, 0.0190, 0.945, 2.381 },
        { "HD 219134 c",  6.7646, 0.0178, 1.660, 1.697 }
      }
    },

    { "GJ 876",  // 4.68 pc — resonant multi-planet
      3272.0, 4.875,
      0.367, 0.0,
      213.867, -1.6,
      {} // no transits confirmed
    },

    { "GJ 3470",  // 29.4 pc — sub-Neptune
      3600.0, 4.695,
      0.547, 0.0,
      33.960, 26.5,
      {{ "GJ 3470 b", 3.3366, 0.0773, 1.898, 13.40 }}
    },

    { "55 Cancri",  // 12.6 pc — 5 planets
      5250.0, 4.43,
      0.943, 0.574,
      79.427, 27.41,
      {
        { "55 Cnc e", 0.7365, 0.0196, 1.544, 6.02 },  // transiting super-Earth
        // b,c,d,f are RV-only
      }
    },

    { "GJ 9827",  // 29.7 pc — 3 planets
      4236.0, 4.719,
      0.580, 0.0,
      33.686, 31.95,
      {
        { "GJ 9827 b",  1.2090, 0.0766, 1.260, 3.53 },
        { "GJ 9827 c",  3.6481, 0.0602, 1.826, 1.06 },
        { "GJ 9827 d",  6.2018, 0.0980, 1.226, 1.44 }
      }
    },

    { "HD 136352",  // 14.7 pc — 3 planets
      5664.0, 4.390,
      1.058, 0.838,
      68.082, -69.0,
      {
        { "HD 136352 b", 11.578, 0.0144, 3.935, 1.46 },
        { "HD 136352 c", 27.592, 0.0253, 3.251, 2.61 },
        { "HD 136352 d",107.245, 0.0222, 8.870, 1.30 }
      }
    },

    { "HD 3167",  // 47.3 pc — 2 planets (one transiting)
      5261.0, 4.530,
      0.880, 0.0,
      21.118, 19.53,
      {
        { "HD 3167 b",  0.9596, 0.0171, 1.609, 3.56 },
        { "HD 3167 c", 29.845, 0.0307, 4.869, 2.58 }
      }
    },

    { "GJ 1132",  // 12.6 pc — rocky planet
      3090.0, 5.070,
      0.207, 0.0,
      79.254, 35.08,
      {{ "GJ 1132 b", 1.6289, 0.0476, 0.766, 2.75 }}
    },

    { "GJ 1252",  // 20.4 pc — ultra-short period
      3458.0, 4.830,
      0.391, 0.0,
      49.056, 7.48,
      {{ "GJ 1252 b", 0.5182, 0.0289, 0.724, 2.00 }}
    },

    { "LTT 1445 A",  // 6.87 pc — rocky
      3337.0, 4.967,
      0.276, 0.0,
      145.547, -5.43,
      {}
    },

    { "GJ 486",  // 8.07 pc — rocky super-Earth
      3317.0, 4.911,
      0.324, 0.0,
      123.821, 19.11,
      {{ "GJ 486 b", 1.4671, 0.0373, 1.016, 3.39 }}
    },

    // -------------------------------------------------------------------------
    // WELL-CHARACTERISED TRANSITING SYSTEMS (best data quality)
    // -------------------------------------------------------------------------

    { "HD 209458",  // 48.3 pc — first transiting exoplanet "Osiris"
      6091.0, 4.450,
      1.190, 1.600,
      20.675, -14.74,
      {{ "HD 209458 b", 3.52475, 0.12084, 3.067, 84.67 }}
    },

    { "HD 189733",  // 19.8 pc — best atmospheric characterisation
      5023.0, 4.582,
      0.776, 0.338,
      50.569, -2.20,
      {{ "HD 189733 b", 2.21858, 0.1555, 1.823, 205.0 }}
    },

    { "TRAPPIST-1",  // 12.1 pc — 7 Earth-sized planets
      2566.0, 5.227,
      0.1192, 0.000553,
      82.58, 0.0,
      {
        { "TRAPPIST-1 b",  1.51087,  0.08491, 0.0, 0.0 },
        { "TRAPPIST-1 c",  2.42179,  0.08249, 0.0, 0.0 },
        { "TRAPPIST-1 d",  4.04961,  0.03526, 0.0, 0.0 },
        { "TRAPPIST-1 e",  6.10108,  0.06839, 0.0, 0.0 },
        { "TRAPPIST-1 f",  9.20690,  0.08330, 0.0, 0.0 },
        { "TRAPPIST-1 g", 12.35294,  0.09191, 0.0, 0.0 },
        { "TRAPPIST-1 h", 18.76700,  0.05605, 0.0, 0.0 }
      }
    },

    { "Kepler-90",  // 870 pc — 8-planet system (KOI-351)
      6080.0, 4.400,
      1.200, 0.0,
      1.150, 0.0,
      {
        { "Kepler-90 b",   7.008,   0.0108, 3.99, 0.0 },
        { "Kepler-90 c",   8.719,   0.0127, 4.41, 0.0 },
        { "Kepler-90 d",  59.737,   0.0238, 8.40, 0.0 },
        { "Kepler-90 e",  91.939,   0.0220, 9.71, 0.0 },
        { "Kepler-90 f", 124.914,   0.0223,10.94, 0.0 },
        { "Kepler-90 g", 210.735,   0.0617,12.32, 2.28 },
        { "Kepler-90 h", 331.603,   0.0912,14.40,20.34 }
      }
    },

    { "51 Pegasi",  // 15.5 pc — first exoplanet around sun-like star (RV only)
      5787.0, 4.36,
      1.175, 0.0,
      64.649, 0.0,
      {{ "51 Peg b", 4.2308, 0.0, 0.0, 55.94 }}  // no transit
    },

    { "HD 149026",  // 75.9 pc — hot Saturn
      6179.0, 4.370,
      1.410, 1.580,
      13.153, -17.84,
      {{ "HD 149026 b", 2.8759, 0.0543, 3.14, 43.30 }}
    },

    { "HAT-P-11",  // 37.8 pc — hot Neptune
      4653.0, 4.663,
      0.683, 0.250,
      26.451, -63.24,
      {{ "HAT-P-11 b", 4.8880, 0.0576, 2.356, 10.42 }}
    },

    { "GJ 3470",  // duplicate — keep for multi-system coverage
      3600.0, 4.695,
      0.547, 0.0,
      33.960, 26.5,
      {{ "GJ 3470 b", 3.3366, 0.0773, 1.898, 13.40 }}
    },

    { "HD 106315",  // 109 pc — 2 transiting planets
      6327.0, 4.252,
      1.296, 2.480,
      9.116, -3.34,
      {
        { "HD 106315 b",  9.552, 0.0188, 3.775, 3.63 },
        { "HD 106315 c", 21.057, 0.0317, 4.638, 3.43 }
      }
    },

    { "HD 191939",  // 53.6 pc — 3 transiting planets
      5348.0, 4.300,
      0.940, 0.450,
      18.625, -9.5,
      {
        { "HD 191939 b",  8.880, 0.0352, 2.939, 3.56 },
        { "HD 191939 c", 28.580, 0.0329, 4.162, 1.93 },
        { "HD 191939 d", 38.353, 0.0321, 5.360, 0.61 }
      }
    },

    { "K2-138",  // 202 pc — 6-planet resonant chain
      5356.0, 4.540,
      0.863, 0.520,
      4.908, 0.64,
      {
        { "K2-138 d",  5.405, 0.0289, 2.70, 3.03 },
        { "K2-138 e",  8.261, 0.0366, 2.97, 4.31 },
        { "K2-138 f", 12.758, 0.0292, 3.20, 0.47 },
        { "K2-138 g", 41.968, 0.0290, 4.75, 0.83 }
      }
    },

    { "K2-32",  // 157 pc — 4 planets
      5271.0, 4.490,
      0.860, 0.420,
      6.314, -2.20,
      {
        { "K2-32 e",  4.349, 0.0160, 2.671, 0.92 },
        { "K2-32 b",  8.992, 0.0617, 3.488, 5.22 },
        { "K2-32 c", 20.661, 0.0367, 4.350, 2.15 },
        { "K2-32 d", 31.717, 0.0395, 4.888, 1.53 }
      }
    },

    { "pi Mensae",  // 18.3 pc — transiting super-Earth
      5998.0, 4.430,
      1.170, 1.550,
      54.705, 10.71,
      {{ "pi Men c", 6.268, 0.0164, 2.952, 1.185 }}
    },

    { "HD 15337",  // 44.8 pc — 2 transiting planets
      5131.0, 4.480,
      0.855, 0.310,
      22.285, -3.80,
      {
        { "HD 15337 b",  4.756, 0.0186, 2.554, 2.82 },
        { "HD 15337 c", 17.181, 0.0275, 2.232, 1.92 }
      }
    },

    { "HD 108236",  // 64.6 pc — 5 planets
      5660.0, 4.490,
      0.877, 0.640,
      15.452, 16.30,
      {
        { "HD 108236 b",  3.796, 0.0169, 2.384, 0.0 },
        { "HD 108236 c",  6.203, 0.0217, 2.860, 0.0 },
        { "HD 108236 d", 14.176, 0.0266, 3.850, 0.0 },
        { "HD 108236 e", 19.590, 0.0322, 4.200, 0.0 },
        { "HD 108236 f", 29.541, 0.0211, 3.270, 0.0 }
      }
    },

    { "K2-285",  // 155 pc — 4 planets
      4975.0, 4.400,
      0.787, 0.380,
      6.425, 15.88,
      {
        { "K2-285 b",  3.472, 0.0311, 2.180, 4.62 },
        { "K2-285 c",  7.138, 0.0458, 2.520, 5.90 },
        { "K2-285 d", 10.456, 0.0316, 2.504, 0.68 },
        { "K2-285 e", 14.763, 0.0261, 2.300, 1.69 }
      }
    },

    { "HD 260655",  // 10.0 pc — 2 rocky planets (very nearby!)
      3803.0, 5.200,
      0.439, 0.0,
      99.916, -58.75,
      {
        { "HD 260655 b", 2.770, 0.0843, 1.150, 1.69 },
        { "HD 260655 c", 5.706, 0.0906, 0.980, 1.92 }
      }
    },

    { "HD 23472",  // 39.0 pc — 5 planets
      4684.0, 4.530,
      0.710, 0.270,
      25.590, 34.55,
      {
        { "HD 23472 d",  3.977, 0.0119, 1.990, 0.29 },
        { "HD 23472 e",  7.908, 0.0146, 2.480, 0.30 },
        { "HD 23472 f", 12.162, 0.0163, 2.820, 0.29 },
        { "HD 23472 b", 17.667, 0.0275, 2.670, 2.68 },
        { "HD 23472 c", 29.797, 0.0248, 2.940, 0.92 }
      }
    },

    { "GJ 9827",  // already above but with full data
      4236.0, 4.719,
      0.580, 0.0,
      33.686, 31.95,
      {
        { "GJ 9827 b",  1.209, 0.0766, 1.260, 3.53 },
        { "GJ 9827 c",  3.648, 0.0602, 1.826, 1.06 },
        { "GJ 9827 d",  6.202, 0.0980, 1.226, 1.44 }
      }
    },

    { "HD 39091 (pi Men)",  // 18.3 pc
      5998.0, 4.430,
      1.170, 1.550,
      54.705, 10.71,
      {{ "pi Men c", 6.268, 0.0164, 2.952, 1.185 }}
    },

    { "Tau Ceti",  // 3.60 pc — nearest solar analogue with planet candidates
      5310.0, 4.440,
      0.793, 0.490,
      277.516, 0.0,
      {} // planets from RV only, no transits
    },

    { "Epsilon Indi A",  // 3.64 pc
      4754.0, 4.450,
      0.0, 0.255,
      274.805, 0.0,
      {}
    },

    { "61 Virginis",  // 8.50 pc — 3 RV planets
      5577.0, 4.510,
      0.980, 0.825,
      117.573, 0.0,
      {} // RV only
    },

    }; // end return
} // end load_catalogue

} // namespace cr01
