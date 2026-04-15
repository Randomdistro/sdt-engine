// ================================================================
// generate_isotopes.cpp — Complete Naturally Occurring Isotope
//                          File Generator (SDT Framework)
//
// Generates one markdown file per naturally occurring isotope
// using the SDT nuclear construction grammar:
//   - 1 alpha core (for Z >= 2)
//   - n_deu deuterons: n_deu = 3Z - A - 2
//   - n_tri tritons:   n_tri = A - 2Z
//   - Verification: A = 4 + 2*n_deu + 3*n_tri
//   -                Z = 2 + n_deu + n_tri
//
// Framework: Spatial Displacement Theory v6.0
// Prohibitions: No G, No M, No GM, No QM, No quarks, No wave-particle duality.
//
// All binding = convergent boundary pressure (CMB occlusion)
// All mass = throughput reorganisation cost
// All stability = topological protection
// All neutrons = compressed hydrogen atoms
// ================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>
#include <iomanip>
#include <cmath>
#include <algorithm>

namespace fs = std::filesystem;

struct Isotope {
    int Z;
    int A;
    const char* symbol;
    const char* element;
    double abundance;        // percent (0 = trace/synthetic)
    double binding_MeV;      // total binding energy in MeV
    const char* spin_parity; // e.g. "0+", "1/2-", "3/2+"
    const char* halflife;    // "stable" or value
    double mass_u;           // atomic mass in u
    bool skip;               // true if file already exists
};

// ================================================================
// COMPLETE NATURALLY OCCURRING ISOTOPE TABLE
// Sources: NUBASE2020, IAEA, NNDC
// Every stable + primordially long-lived isotope, Z=1 to Z=92
// ================================================================
std::vector<Isotope> build_isotope_table() {
    return {
        // ── Z=1 HYDROGEN ──
        {1, 1, "H", "Hydrogen", 99.9885, 0.0, "1/2+", "stable", 1.00783, true},       // H-1 exists
        {1, 2, "H", "Hydrogen", 0.0115, 2.224, "1+", "stable", 2.01410, true},          // H-2 exists

        // ── Z=2 HELIUM ──
        {2, 3, "He", "Helium", 0.000134, 7.718, "1/2+", "stable", 3.01603, false},
        {2, 4, "He", "Helium", 99.999866, 28.296, "0+", "stable", 4.00260, true},       // He-4 exists

        // ── Z=3 LITHIUM ──
        {3, 6, "Li", "Lithium", 7.59, 31.994, "1+", "stable", 6.01512, true},           // Li-6 exists
        {3, 7, "Li", "Lithium", 92.41, 39.245, "3/2-", "stable", 7.01600, true},        // Li-7 exists

        // ── Z=4 BERYLLIUM ──
        {4, 9, "Be", "Beryllium", 100.0, 58.165, "3/2-", "stable", 9.01218, true},      // Be-9 exists

        // ── Z=5 BORON ──
        {5, 10, "B", "Boron", 19.9, 64.751, "3+", "stable", 10.01294, false},
        {5, 11, "B", "Boron", 80.1, 76.205, "3/2-", "stable", 11.00931, false},

        // ── Z=6 CARBON ──
        {6, 12, "C", "Carbon", 98.93, 92.162, "0+", "stable", 12.00000, true},          // C-12 exists
        {6, 13, "C", "Carbon", 1.07, 97.108, "1/2-", "stable", 13.00335, false},

        // ── Z=7 NITROGEN ──
        {7, 14, "N", "Nitrogen", 99.632, 104.659, "1+", "stable", 14.00307, false},
        {7, 15, "N", "Nitrogen", 0.368, 115.492, "1/2-", "stable", 15.00011, false},

        // ── Z=8 OXYGEN ──
        {8, 16, "O", "Oxygen", 99.757, 127.619, "0+", "stable", 15.99491, true},        // O-16 exists
        {8, 17, "O", "Oxygen", 0.038, 131.763, "5/2+", "stable", 16.99913, false},
        {8, 18, "O", "Oxygen", 0.205, 139.808, "0+", "stable", 17.99916, false},

        // ── Z=9 FLUORINE ──
        {9, 19, "F", "Fluorine", 100.0, 147.801, "1/2+", "stable", 18.99840, false},

        // ── Z=10 NEON ──
        {10, 20, "Ne", "Neon", 90.48, 160.645, "0+", "stable", 19.99244, true},         // Ne-20 exists
        {10, 21, "Ne", "Neon", 0.27, 167.406, "3/2+", "stable", 20.99385, false},
        {10, 22, "Ne", "Neon", 9.25, 177.770, "0+", "stable", 21.99138, false},

        // ── Z=11 SODIUM ──
        {11, 23, "Na", "Sodium", 100.0, 186.564, "3/2+", "stable", 22.98977, false},

        // ── Z=12 MAGNESIUM ──
        {12, 24, "Mg", "Magnesium", 78.99, 198.257, "0+", "stable", 23.98504, false},
        {12, 25, "Mg", "Magnesium", 10.00, 205.588, "5/2+", "stable", 24.98584, false},
        {12, 26, "Mg", "Magnesium", 11.01, 216.681, "0+", "stable", 25.98259, false},

        // ── Z=13 ALUMINIUM ──
        {13, 27, "Al", "Aluminium", 100.0, 224.952, "5/2+", "stable", 26.98154, false},

        // ── Z=14 SILICON ──
        {14, 28, "Si", "Silicon", 92.223, 236.537, "0+", "stable", 27.97693, false},
        {14, 29, "Si", "Silicon", 4.685, 245.011, "1/2+", "stable", 28.97649, false},
        {14, 30, "Si", "Silicon", 3.092, 255.620, "0+", "stable", 29.97377, false},

        // ── Z=15 PHOSPHORUS ──
        {15, 31, "P", "Phosphorus", 100.0, 262.917, "1/2+", "stable", 30.97376, false},

        // ── Z=16 SULFUR ──
        {16, 32, "S", "Sulfur", 94.99, 271.780, "0+", "stable", 31.97207, false},
        {16, 33, "S", "Sulfur", 0.75, 280.422, "3/2+", "stable", 32.97146, false},
        {16, 34, "S", "Sulfur", 4.25, 291.839, "0+", "stable", 33.96787, false},
        {16, 36, "S", "Sulfur", 0.01, 308.714, "0+", "stable", 35.96708, false},

        // ── Z=17 CHLORINE ──
        {17, 35, "Cl", "Chlorine", 75.76, 298.210, "3/2+", "stable", 34.96885, false},
        {17, 37, "Cl", "Chlorine", 24.24, 317.100, "3/2+", "stable", 36.96590, false},

        // ── Z=18 ARGON ──
        {18, 36, "Ar", "Argon", 0.3336, 306.716, "0+", "stable", 35.96755, false},
        {18, 38, "Ar", "Argon", 0.0629, 327.343, "0+", "stable", 37.96273, false},
        {18, 40, "Ar", "Argon", 99.6035, 343.810, "0+", "stable", 39.96238, false},

        // ── Z=19 POTASSIUM ──
        {19, 39, "K", "Potassium", 93.2581, 333.724, "3/2+", "stable", 38.96371, false},
        {19, 40, "K", "Potassium", 0.0117, 341.523, "4-", "1.25e9 y", 39.96400, false},
        {19, 41, "K", "Potassium", 6.7302, 351.618, "3/2+", "stable", 40.96183, false},

        // ── Z=20 CALCIUM ──
        {20, 40, "Ca", "Calcium", 96.941, 342.052, "0+", "stable", 39.96259, false},
        {20, 42, "Ca", "Calcium", 0.647, 361.895, "0+", "stable", 41.95862, false},
        {20, 43, "Ca", "Calcium", 0.135, 369.829, "7/2-", "stable", 42.95877, false},
        {20, 44, "Ca", "Calcium", 2.086, 380.960, "0+", "stable", 43.95548, false},
        {20, 46, "Ca", "Calcium", 0.004, 398.769, "0+", "stable", 45.95369, false},
        {20, 48, "Ca", "Calcium", 0.187, 415.991, "0+", "4.3e19 y", 47.95253, false},

        // ── Z=21 SCANDIUM ──
        {21, 45, "Sc", "Scandium", 100.0, 387.849, "7/2-", "stable", 44.95591, false},

        // ── Z=22 TITANIUM ──
        {22, 46, "Ti", "Titanium", 8.25, 398.195, "0+", "stable", 45.95263, false},
        {22, 47, "Ti", "Titanium", 7.44, 407.072, "5/2-", "stable", 46.95176, false},
        {22, 48, "Ti", "Titanium", 73.72, 418.699, "0+", "stable", 47.94795, false},
        {22, 49, "Ti", "Titanium", 5.41, 426.842, "7/2-", "stable", 48.94787, false},
        {22, 50, "Ti", "Titanium", 5.18, 437.781, "0+", "stable", 49.94479, false},

        // ── Z=23 VANADIUM ──
        {23, 50, "V", "Vanadium", 0.250, 434.794, "6+", "1.4e17 y", 49.94716, false},
        {23, 51, "V", "Vanadium", 99.750, 445.841, "7/2-", "stable", 50.94396, false},

        // ── Z=24 CHROMIUM ──
        {24, 50, "Cr", "Chromium", 4.345, 435.049, "0+", "stable", 49.94604, false},
        {24, 52, "Cr", "Chromium", 83.789, 456.345, "0+", "stable", 51.94051, false},
        {24, 53, "Cr", "Chromium", 9.501, 464.286, "3/2-", "stable", 52.94065, false},
        {24, 54, "Cr", "Chromium", 2.365, 474.009, "0+", "stable", 53.93888, false},

        // ── Z=25 MANGANESE ──
        {25, 55, "Mn", "Manganese", 100.0, 482.071, "5/2-", "stable", 54.93804, false},

        // ── Z=26 IRON ──
        {26, 54, "Fe", "Iron", 5.845, 471.764, "0+", "stable", 53.93961, false},
        {26, 56, "Fe", "Iron", 91.754, 492.258, "0+", "stable", 55.93494, false},
        {26, 57, "Fe", "Iron", 2.119, 499.905, "1/2-", "stable", 56.93540, false},
        {26, 58, "Fe", "Iron", 0.282, 509.946, "0+", "stable", 57.93328, false},

        // ── Z=27 COBALT ──
        {27, 59, "Co", "Cobalt", 100.0, 517.309, "7/2-", "stable", 58.93320, false},

        // ── Z=28 NICKEL ──
        {28, 58, "Ni", "Nickel", 68.077, 506.454, "0+", "stable", 57.93535, false},
        {28, 60, "Ni", "Nickel", 26.223, 526.842, "0+", "stable", 59.93079, false},
        {28, 61, "Ni", "Nickel", 1.140, 534.662, "3/2-", "stable", 60.93106, false},
        {28, 62, "Ni", "Nickel", 3.634, 545.259, "0+", "stable", 61.92835, false},
        {28, 64, "Ni", "Nickel", 0.926, 561.756, "0+", "stable", 63.92797, false},

        // ── Z=29 COPPER ──
        {29, 63, "Cu", "Copper", 69.15, 551.385, "3/2-", "stable", 62.92960, false},
        {29, 65, "Cu", "Copper", 30.85, 569.208, "3/2-", "stable", 64.92779, false},

        // ── Z=30 ZINC ──
        {30, 64, "Zn", "Zinc", 49.17, 559.094, "0+", "stable", 63.92914, false},
        {30, 66, "Zn", "Zinc", 27.73, 578.135, "0+", "stable", 65.92603, false},
        {30, 67, "Zn", "Zinc", 4.04, 585.185, "5/2-", "stable", 66.92713, false},
        {30, 68, "Zn", "Zinc", 18.45, 595.387, "0+", "stable", 67.92484, false},
        {30, 70, "Zn", "Zinc", 0.61, 611.085, "0+", "stable", 69.92532, false},

        // ── Z=31 GALLIUM ──
        {31, 69, "Ga", "Gallium", 60.108, 601.996, "3/2-", "stable", 68.92558, false},
        {31, 71, "Ga", "Gallium", 39.892, 618.948, "3/2-", "stable", 70.92470, false},

        // ── Z=32 GERMANIUM ──
        {32, 70, "Ge", "Germanium", 20.57, 610.518, "0+", "stable", 69.92425, false},
        {32, 72, "Ge", "Germanium", 27.45, 628.686, "0+", "stable", 71.92208, false},
        {32, 73, "Ge", "Germanium", 7.75, 635.467, "9/2+", "stable", 72.92346, false},
        {32, 74, "Ge", "Germanium", 36.50, 645.665, "0+", "stable", 73.92118, false},
        {32, 76, "Ge", "Germanium", 7.73, 661.598, "0+", "1.9e21 y", 75.92140, false},

        // ── Z=33 ARSENIC ──
        {33, 75, "As", "Arsenic", 100.0, 652.564, "3/2-", "stable", 74.92160, false},

        // ── Z=34 SELENIUM ──
        {34, 74, "Se", "Selenium", 0.89, 642.889, "0+", "stable", 73.92248, false},
        {34, 76, "Se", "Selenium", 9.37, 662.071, "0+", "stable", 75.91921, false},
        {34, 77, "Se", "Selenium", 7.63, 669.494, "1/2-", "stable", 76.91991, false},
        {34, 78, "Se", "Selenium", 23.77, 679.989, "0+", "stable", 77.91731, false},
        {34, 80, "Se", "Selenium", 49.61, 696.865, "0+", "stable", 79.91652, false},
        {34, 82, "Se", "Selenium", 8.73, 712.845, "0+", "1.0e20 y", 81.91670, false},

        // ── Z=35 BROMINE ──
        {35, 79, "Br", "Bromine", 50.69, 686.322, "3/2-", "stable", 78.91834, false},
        {35, 81, "Br", "Bromine", 49.31, 704.369, "3/2-", "stable", 80.91629, false},

        // ── Z=36 KRYPTON ──
        {36, 78, "Kr", "Krypton", 0.355, 675.565, "0+", "stable", 77.92040, false},
        {36, 80, "Kr", "Krypton", 2.286, 695.434, "0+", "stable", 79.91638, false},
        {36, 82, "Kr", "Krypton", 11.593, 714.273, "0+", "stable", 81.91348, false},
        {36, 83, "Kr", "Krypton", 11.500, 721.237, "9/2+", "stable", 82.91414, false},
        {36, 84, "Kr", "Krypton", 56.987, 732.260, "0+", "stable", 83.91150, false},
        {36, 86, "Kr", "Krypton", 17.279, 749.235, "0+", "stable", 85.91062, false},

        // ── Z=37 RUBIDIUM ──
        {37, 85, "Rb", "Rubidium", 72.17, 739.285, "5/2-", "stable", 84.91179, false},
        {37, 87, "Rb", "Rubidium", 27.83, 757.854, "3/2-", "4.9e10 y", 86.90918, false},

        // ── Z=38 STRONTIUM ──
        {38, 84, "Sr", "Strontium", 0.56, 728.907, "0+", "stable", 83.91343, false},
        {38, 86, "Sr", "Strontium", 9.86, 748.926, "0+", "stable", 85.90926, false},
        {38, 87, "Sr", "Strontium", 7.00, 757.354, "9/2+", "stable", 86.90888, false},
        {38, 88, "Sr", "Strontium", 82.58, 768.468, "0+", "stable", 87.90561, false},

        // ── Z=39 YTTRIUM ──
        {39, 89, "Y", "Yttrium", 100.0, 775.538, "1/2-", "stable", 88.90585, false},

        // ── Z=40 ZIRCONIUM ──
        {40, 90, "Zr", "Zirconium", 51.45, 783.893, "0+", "stable", 89.90470, false},
        {40, 91, "Zr", "Zirconium", 11.22, 791.087, "5/2+", "stable", 90.90564, false},
        {40, 92, "Zr", "Zirconium", 17.15, 799.722, "0+", "stable", 91.90504, false},
        {40, 94, "Zr", "Zirconium", 17.38, 814.677, "0+", "stable", 93.90632, false},
        {40, 96, "Zr", "Zirconium", 2.80, 828.995, "0+", "2.0e19 y", 95.90828, false},

        // ── Z=41 NIOBIUM ──
        {41, 93, "Nb", "Niobium", 100.0, 805.766, "9/2+", "stable", 92.90638, false},

        // ── Z=42 MOLYBDENUM ──
        {42, 92, "Mo", "Molybdenum", 14.53, 796.510, "0+", "stable", 91.90681, false},
        {42, 94, "Mo", "Molybdenum", 9.15, 814.256, "0+", "stable", 93.90509, false},
        {42, 95, "Mo", "Molybdenum", 15.84, 821.625, "5/2+", "stable", 94.90584, false},
        {42, 96, "Mo", "Molybdenum", 16.67, 830.779, "0+", "stable", 95.90468, false},
        {42, 97, "Mo", "Molybdenum", 9.60, 837.600, "5/2+", "stable", 96.90602, false},
        {42, 98, "Mo", "Molybdenum", 24.39, 846.243, "0+", "stable", 97.90541, false},
        {42, 100, "Mo", "Molybdenum", 9.82, 860.457, "0+", "7.1e18 y", 99.90748, false},

        // ── Z=44 RUTHENIUM ──
        {44, 96, "Ru", "Ruthenium", 5.54, 826.495, "0+", "stable", 95.90760, false},
        {44, 98, "Ru", "Ruthenium", 1.87, 843.774, "0+", "stable", 97.90529, false},
        {44, 99, "Ru", "Ruthenium", 12.76, 852.166, "5/2+", "stable", 98.90594, false},
        {44, 100, "Ru", "Ruthenium", 12.60, 861.928, "0+", "stable", 99.90422, false},
        {44, 101, "Ru", "Ruthenium", 17.06, 868.724, "5/2+", "stable", 100.90558, false},
        {44, 102, "Ru", "Ruthenium", 31.55, 878.135, "0+", "stable", 101.90435, false},
        {44, 104, "Ru", "Ruthenium", 18.62, 893.091, "0+", "stable", 103.90543, false},

        // ── Z=45 RHODIUM ──
        {45, 103, "Rh", "Rhodium", 100.0, 884.164, "1/2-", "stable", 102.90550, false},

        // ── Z=46 PALLADIUM ──
        {46, 102, "Pd", "Palladium", 1.02, 875.211, "0+", "stable", 101.90561, false},
        {46, 104, "Pd", "Palladium", 11.14, 892.819, "0+", "stable", 103.90404, false},
        {46, 105, "Pd", "Palladium", 22.33, 899.927, "5/2+", "stable", 104.90508, false},
        {46, 106, "Pd", "Palladium", 27.33, 909.476, "0+", "stable", 105.90348, false},
        {46, 108, "Pd", "Palladium", 26.46, 925.240, "0+", "stable", 107.90389, false},
        {46, 110, "Pd", "Palladium", 11.72, 940.208, "0+", "stable", 109.90517, false},

        // ── Z=47 SILVER ──
        {47, 107, "Ag", "Silver", 51.839, 915.266, "1/2-", "stable", 106.90509, false},
        {47, 109, "Ag", "Silver", 48.161, 931.721, "1/2-", "stable", 108.90476, false},

        // ── Z=48 CADMIUM ──
        {48, 106, "Cd", "Cadmium", 1.25, 905.140, "0+", "stable", 105.90646, false},
        {48, 108, "Cd", "Cadmium", 0.89, 923.400, "0+", "stable", 107.90418, false},
        {48, 110, "Cd", "Cadmium", 12.49, 940.647, "0+", "stable", 109.90301, false},
        {48, 111, "Cd", "Cadmium", 12.80, 947.620, "1/2+", "stable", 110.90418, false},
        {48, 112, "Cd", "Cadmium", 24.13, 957.016, "0+", "stable", 111.90276, false},
        {48, 113, "Cd", "Cadmium", 12.22, 963.557, "1/2+", "7.7e15 y", 112.90440, false},
        {48, 114, "Cd", "Cadmium", 28.73, 972.599, "0+", "stable", 113.90337, false},
        {48, 116, "Cd", "Cadmium", 7.49, 988.454, "0+", "2.9e19 y", 115.90476, false},

        // ── Z=49 INDIUM ──
        {49, 113, "In", "Indium", 4.29, 963.084, "9/2+", "stable", 112.90406, false},
        {49, 115, "In", "Indium", 95.71, 979.425, "9/2+", "4.4e14 y", 114.90388, false},

        // ── Z=50 TIN ──
        {50, 112, "Sn", "Tin", 0.97, 953.530, "0+", "stable", 111.90482, false},
        {50, 114, "Sn", "Tin", 0.66, 971.574, "0+", "stable", 113.90278, false},
        {50, 115, "Sn", "Tin", 0.34, 979.119, "1/2+", "stable", 114.90334, false},
        {50, 116, "Sn", "Tin", 14.54, 988.684, "0+", "stable", 115.90174, false},
        {50, 117, "Sn", "Tin", 7.68, 995.626, "1/2+", "stable", 116.90295, false},
        {50, 118, "Sn", "Tin", 24.22, 1004.955, "0+", "stable", 117.90161, false},
        {50, 119, "Sn", "Tin", 8.59, 1011.438, "1/2+", "stable", 118.90331, false},
        {50, 120, "Sn", "Tin", 32.58, 1020.546, "0+", "stable", 119.90220, false},
        {50, 122, "Sn", "Tin", 4.63, 1035.528, "0+", "stable", 121.90344, false},
        {50, 124, "Sn", "Tin", 5.79, 1049.963, "0+", "stable", 123.90527, false},

        // ── Z=51 ANTIMONY ──
        {51, 121, "Sb", "Antimony", 57.21, 1026.321, "5/2+", "stable", 120.90382, false},
        {51, 123, "Sb", "Antimony", 42.79, 1042.471, "7/2+", "stable", 122.90421, false},

        // ── Z=52 TELLURIUM ──
        {52, 120, "Te", "Tellurium", 0.09, 1017.283, "0+", "stable", 119.90406, false},
        {52, 122, "Te", "Tellurium", 2.55, 1034.330, "0+", "stable", 121.90304, false},
        {52, 123, "Te", "Tellurium", 0.89, 1041.260, "1/2+", "stable", 122.90427, false},
        {52, 124, "Te", "Tellurium", 4.74, 1050.681, "0+", "stable", 123.90282, false},
        {52, 125, "Te", "Tellurium", 7.07, 1057.257, "1/2+", "stable", 124.90443, false},
        {52, 126, "Te", "Tellurium", 18.84, 1066.370, "0+", "stable", 125.90331, false},
        {52, 128, "Te", "Tellurium", 31.74, 1081.438, "0+", "2.2e24 y", 127.90446, false},
        {52, 130, "Te", "Tellurium", 34.08, 1095.942, "0+", "8.2e20 y", 129.90622, false},

        // ── Z=53 IODINE ──
        {53, 127, "I", "Iodine", 100.0, 1072.580, "5/2+", "stable", 126.90447, false},

        // ── Z=54 XENON ──
        {54, 124, "Xe", "Xenon", 0.0952, 1046.256, "0+", "1.8e22 y", 123.90589, false},
        {54, 126, "Xe", "Xenon", 0.0890, 1063.914, "0+", "stable", 125.90427, false},
        {54, 128, "Xe", "Xenon", 1.9102, 1080.740, "0+", "stable", 127.90353, false},
        {54, 129, "Xe", "Xenon", 26.4006, 1087.648, "1/2+", "stable", 128.90478, false},
        {54, 130, "Xe", "Xenon", 4.0710, 1096.907, "0+", "stable", 129.90351, false},
        {54, 131, "Xe", "Xenon", 21.2324, 1103.514, "3/2+", "stable", 130.90508, false},
        {54, 132, "Xe", "Xenon", 26.9086, 1112.449, "0+", "stable", 131.90415, false},
        {54, 134, "Xe", "Xenon", 10.4357, 1127.439, "0+", "stable", 133.90539, false},
        {54, 136, "Xe", "Xenon", 8.8573, 1141.882, "0+", "2.2e21 y", 135.90722, false},

        // ── Z=55 CESIUM ──
        {55, 133, "Cs", "Cesium", 100.0, 1118.528, "7/2+", "stable", 132.90545, false},

        // ── Z=56 BARIUM ──
        {56, 130, "Ba", "Barium", 0.106, 1092.729, "0+", "stable", 129.90632, false},
        {56, 132, "Ba", "Barium", 0.101, 1110.037, "0+", "stable", 131.90506, false},
        {56, 134, "Ba", "Barium", 2.417, 1126.700, "0+", "stable", 133.90451, false},
        {56, 135, "Ba", "Barium", 6.592, 1133.683, "3/2+", "stable", 134.90569, false},
        {56, 136, "Ba", "Barium", 7.854, 1142.780, "0+", "stable", 135.90457, false},
        {56, 137, "Ba", "Barium", 11.232, 1149.686, "3/2+", "stable", 136.90583, false},
        {56, 138, "Ba", "Barium", 71.698, 1158.296, "0+", "stable", 137.90524, false},

        // ── Z=57 LANTHANUM ──
        {57, 138, "La", "Lanthanum", 0.0888, 1155.262, "5+", "1.02e11 y", 137.90711, false},
        {57, 139, "La", "Lanthanum", 99.9119, 1164.555, "7/2+", "stable", 138.90636, false},

        // ── Z=58 CERIUM ──
        {58, 136, "Ce", "Cerium", 0.185, 1138.722, "0+", "stable", 135.90714, false},
        {58, 138, "Ce", "Cerium", 0.251, 1153.695, "0+", "stable", 137.90599, false},
        {58, 140, "Ce", "Cerium", 88.450, 1172.689, "0+", "stable", 139.90544, false},
        {58, 142, "Ce", "Cerium", 11.114, 1185.286, "0+", "5.0e16 y", 141.90924, false},

        // ── Z=59 PRASEODYMIUM ──
        {59, 141, "Pr", "Praseodymium", 100.0, 1177.918, "5/2+", "stable", 140.90766, false},

        // ── Z=60 NEODYMIUM ──
        {60, 142, "Nd", "Neodymium", 27.152, 1185.145, "0+", "stable", 141.90773, false},
        {60, 143, "Nd", "Neodymium", 12.174, 1191.272, "7/2-", "stable", 142.90982, false},
        {60, 144, "Nd", "Neodymium", 23.798, 1199.083, "0+", "2.3e15 y", 143.91009, false},
        {60, 145, "Nd", "Neodymium", 8.293, 1205.634, "7/2-", "stable", 144.91258, false},
        {60, 146, "Nd", "Neodymium", 17.189, 1214.182, "0+", "stable", 145.91312, false},
        {60, 148, "Nd", "Neodymium", 5.756, 1227.570, "0+", "stable", 147.91690, false},
        {60, 150, "Nd", "Neodymium", 5.638, 1239.983, "0+", "6.7e18 y", 149.92090, false},

        // ── Z=62 SAMARIUM ──
        {62, 144, "Sm", "Samarium", 3.07, 1195.740, "0+", "stable", 143.91200, false},
        {62, 147, "Sm", "Samarium", 14.99, 1217.251, "7/2-", "1.06e11 y", 146.91490, false},
        {62, 148, "Sm", "Samarium", 11.24, 1225.393, "0+", "7.0e15 y", 147.91483, false},
        {62, 149, "Sm", "Samarium", 13.82, 1233.296, "7/2-", "stable", 148.91718, false},
        {62, 150, "Sm", "Samarium", 7.38, 1239.253, "0+", "stable", 149.91728, false},
        {62, 152, "Sm", "Samarium", 26.75, 1253.104, "0+", "stable", 151.91973, false},
        {62, 154, "Sm", "Samarium", 22.75, 1266.936, "0+", "stable", 153.92221, false},

        // ── Z=63 EUROPIUM ──
        {63, 151, "Eu", "Europium", 47.81, 1244.141, "5/2+", "stable", 150.91986, false},
        {63, 153, "Eu", "Europium", 52.19, 1258.998, "5/2+", "stable", 152.92124, false},

        // ── Z=64 GADOLINIUM ──
        {64, 152, "Gd", "Gadolinium", 0.20, 1251.483, "0+", "1.1e14 y", 151.91980, false},
        {64, 154, "Gd", "Gadolinium", 2.18, 1266.606, "0+", "stable", 153.92087, false},
        {64, 155, "Gd", "Gadolinium", 14.80, 1274.106, "3/2-", "stable", 154.92263, false},
        {64, 156, "Gd", "Gadolinium", 20.47, 1282.419, "0+", "stable", 155.92213, false},
        {64, 157, "Gd", "Gadolinium", 15.65, 1289.146, "3/2-", "stable", 156.92397, false},
        {64, 158, "Gd", "Gadolinium", 24.84, 1297.452, "0+", "stable", 157.92411, false},
        {64, 160, "Gd", "Gadolinium", 21.86, 1311.368, "0+", "stable", 159.92706, false},

        // ── Z=65 TERBIUM ──
        {65, 159, "Tb", "Terbium", 100.0, 1303.554, "3/2+", "stable", 158.92535, false},

        // ── Z=66 DYSPROSIUM ──
        {66, 156, "Dy", "Dysprosium", 0.056, 1281.431, "0+", "stable", 155.92428, false},
        {66, 158, "Dy", "Dysprosium", 0.095, 1296.878, "0+", "stable", 157.92441, false},
        {66, 160, "Dy", "Dysprosium", 2.329, 1312.427, "0+", "stable", 159.92520, false},
        {66, 161, "Dy", "Dysprosium", 18.889, 1318.982, "5/2+", "stable", 160.92694, false},
        {66, 162, "Dy", "Dysprosium", 25.475, 1327.820, "0+", "stable", 161.92680, false},
        {66, 163, "Dy", "Dysprosium", 24.896, 1333.828, "5/2-", "stable", 162.92874, false},
        {66, 164, "Dy", "Dysprosium", 28.260, 1342.402, "0+", "stable", 163.92918, false},

        // ── Z=67 HOLMIUM ──
        {67, 165, "Ho", "Holmium", 100.0, 1349.270, "7/2-", "stable", 164.93033, false},

        // ── Z=68 ERBIUM ──
        {68, 162, "Er", "Erbium", 0.139, 1326.410, "0+", "stable", 161.92879, false},
        {68, 164, "Er", "Erbium", 1.601, 1341.503, "0+", "stable", 163.92920, false},
        {68, 166, "Er", "Erbium", 33.503, 1358.170, "0+", "stable", 165.93030, false},
        {68, 167, "Er", "Erbium", 22.869, 1363.925, "7/2+", "stable", 166.93205, false},
        {68, 168, "Er", "Erbium", 26.978, 1372.630, "0+", "stable", 167.93238, false},
        {68, 170, "Er", "Erbium", 14.910, 1385.029, "0+", "stable", 169.93547, false},

        // ── Z=69 THULIUM ──
        {69, 169, "Tm", "Thulium", 100.0, 1378.390, "1/2+", "stable", 168.93422, false},

        // ── Z=70 YTTERBIUM ──
        {70, 168, "Yb", "Ytterbium", 0.123, 1369.230, "0+", "stable", 167.93389, false},
        {70, 170, "Yb", "Ytterbium", 2.982, 1385.980, "0+", "stable", 169.93477, false},
        {70, 171, "Yb", "Ytterbium", 14.09, 1392.160, "1/2-", "stable", 170.93633, false},
        {70, 172, "Yb", "Ytterbium", 21.68, 1400.440, "0+", "stable", 171.93639, false},
        {70, 173, "Yb", "Ytterbium", 16.103, 1406.430, "5/2-", "stable", 172.93822, false},
        {70, 174, "Yb", "Ytterbium", 32.026, 1414.560, "0+", "stable", 173.93887, false},
        {70, 176, "Yb", "Ytterbium", 12.996, 1427.080, "0+", "stable", 175.94257, false},

        // ── Z=71 LUTETIUM ──
        {71, 175, "Lu", "Lutetium", 97.401, 1421.220, "7/2+", "stable", 174.94078, false},
        {71, 176, "Lu", "Lutetium", 2.599, 1427.050, "7-", "3.76e10 y", 175.94269, false},

        // ── Z=72 HAFNIUM ──
        {72, 174, "Hf", "Hafnium", 0.16, 1412.830, "0+", "2.0e15 y", 173.94005, false},
        {72, 176, "Hf", "Hafnium", 5.26, 1428.380, "0+", "stable", 175.94142, false},
        {72, 177, "Hf", "Hafnium", 18.60, 1434.900, "7/2-", "stable", 176.94323, false},
        {72, 178, "Hf", "Hafnium", 27.28, 1443.230, "0+", "stable", 177.94371, false},
        {72, 179, "Hf", "Hafnium", 13.62, 1449.620, "9/2+", "stable", 178.94582, false},
        {72, 180, "Hf", "Hafnium", 35.08, 1457.540, "0+", "stable", 179.94656, false},

        // ── Z=73 TANTALUM ──
        {73, 180, "Ta", "Tantalum", 0.01201, 1454.360, "9-", "stable", 179.94747, false},
        {73, 181, "Ta", "Tantalum", 99.98799, 1462.420, "7/2+", "stable", 180.94800, false},

        // ── Z=74 TUNGSTEN ──
        {74, 180, "W", "Tungsten", 0.12, 1450.760, "0+", "1.8e18 y", 179.94671, false},
        {74, 182, "W", "Tungsten", 26.50, 1468.340, "0+", "stable", 181.94820, false},
        {74, 183, "W", "Tungsten", 14.31, 1474.490, "1/2-", "stable", 182.95022, false},
        {74, 184, "W", "Tungsten", 30.64, 1482.720, "0+", "stable", 183.95093, false},
        {74, 186, "W", "Tungsten", 28.43, 1496.380, "0+", "stable", 185.95436, false},

        // ── Z=75 RHENIUM ──
        {75, 185, "Re", "Rhenium", 37.40, 1490.220, "5/2+", "stable", 184.95296, false},
        {75, 187, "Re", "Rhenium", 62.60, 1504.700, "5/2+", "4.12e10 y", 186.95575, false},

        // ── Z=76 OSMIUM ──
        {76, 184, "Os", "Osmium", 0.02, 1480.980, "0+", "stable", 183.95249, false},
        {76, 186, "Os", "Osmium", 1.59, 1497.810, "0+", "2.0e15 y", 185.95384, false},
        {76, 187, "Os", "Osmium", 1.96, 1504.530, "1/2-", "stable", 186.95575, false},
        {76, 188, "Os", "Osmium", 13.24, 1513.120, "0+", "stable", 187.95586, false},
        {76, 189, "Os", "Osmium", 16.15, 1519.460, "3/2-", "stable", 188.95814, false},
        {76, 190, "Os", "Osmium", 26.26, 1527.640, "0+", "stable", 189.95844, false},
        {76, 192, "Os", "Osmium", 40.78, 1541.510, "0+", "stable", 191.96148, false},

        // ── Z=77 IRIDIUM ──
        {77, 191, "Ir", "Iridium", 37.3, 1535.260, "3/2+", "stable", 190.96059, false},
        {77, 193, "Ir", "Iridium", 62.7, 1549.990, "3/2+", "stable", 192.96292, false},

        // ── Z=78 PLATINUM ──
        {78, 190, "Pt", "Platinum", 0.012, 1526.900, "0+", "6.5e11 y", 189.95995, false},
        {78, 192, "Pt", "Platinum", 0.782, 1543.000, "0+", "stable", 191.96104, false},
        {78, 194, "Pt", "Platinum", 32.864, 1558.460, "0+", "stable", 193.96268, false},
        {78, 195, "Pt", "Platinum", 33.775, 1564.580, "1/2-", "stable", 194.96479, false},
        {78, 196, "Pt", "Platinum", 25.211, 1573.000, "0+", "stable", 195.96495, false},
        {78, 198, "Pt", "Platinum", 7.356, 1586.490, "0+", "stable", 197.96789, false},

        // ── Z=79 GOLD ── (THE GOLDEN BOUNDARY)
        {79, 197, "Au", "Gold", 100.0, 1579.290, "3/2+", "stable", 196.96657, false},

        // ── Z=80 MERCURY ──
        {80, 196, "Hg", "Mercury", 0.15, 1569.640, "0+", "stable", 195.96583, false},
        {80, 198, "Hg", "Mercury", 9.97, 1585.490, "0+", "stable", 197.96676, false},
        {80, 199, "Hg", "Mercury", 16.87, 1592.240, "1/2-", "stable", 198.96828, false},
        {80, 200, "Hg", "Mercury", 23.10, 1600.330, "0+", "stable", 199.96833, false},
        {80, 201, "Hg", "Mercury", 13.18, 1606.560, "3/2-", "stable", 200.97030, false},
        {80, 202, "Hg", "Mercury", 29.86, 1614.530, "0+", "stable", 201.97064, false},
        {80, 204, "Hg", "Mercury", 6.87, 1627.680, "0+", "stable", 203.97349, false},

        // ── Z=81 THALLIUM ──
        {81, 203, "Tl", "Thallium", 29.52, 1622.330, "1/2+", "stable", 202.97234, false},
        {81, 205, "Tl", "Thallium", 70.48, 1637.090, "1/2+", "stable", 204.97443, false},

        // ── Z=82 LEAD ──
        {82, 204, "Pb", "Lead", 1.4, 1627.840, "0+", "stable", 203.97302, false},
        {82, 206, "Pb", "Lead", 24.1, 1643.010, "0+", "stable", 205.97447, false},
        {82, 207, "Pb", "Lead", 22.1, 1649.350, "1/2-", "stable", 206.97589, false},
        {82, 208, "Pb", "Lead", 52.4, 1636.430, "0+", "stable", 207.97665, false},

        // ── Z=83 BISMUTH ── (last "stable")
        {83, 209, "Bi", "Bismuth", 100.0, 1640.240, "9/2-", "2.01e19 y", 208.98040, false},

        // ── Z=90 THORIUM ── (primordial)
        {90, 232, "Th", "Thorium", 100.0, 1766.690, "0+", "1.405e10 y", 232.03806, false},

        // ── Z=92 URANIUM ── (primordial)
        {92, 234, "U", "Uranium", 0.0054, 1778.572, "0+", "2.455e5 y", 234.04095, false},
        {92, 235, "U", "Uranium", 0.7204, 1783.871, "7/2-", "7.04e8 y", 235.04393, false},
        {92, 238, "U", "Uranium", 99.2742, 1801.695, "0+", "4.468e9 y", 238.05079, false},
    };
}

// Compute SDT construction grammar
struct Grammar {
    int n_alpha;  // always 1 for Z>=2
    int n_deu;
    int n_tri;
    bool valid;
    double sym_score;  // 0-100
    double tri_frac;   // triton fraction
};

Grammar compute_grammar(int Z, int A) {
    Grammar g{};
    if (Z < 2) {
        // H isotopes: special
        g.n_alpha = 0; g.n_deu = 0; g.n_tri = 0;
        g.valid = false;
        g.sym_score = 0; g.tri_frac = 0;
        return g;
    }
    g.n_alpha = 1;
    g.n_tri = A - 2 * Z;
    g.n_deu = 3 * Z - A - 2;
    int A_check = 4 + 2 * g.n_deu + 3 * g.n_tri;
    int Z_check = 2 + g.n_deu + g.n_tri;
    g.valid = (A_check == A && Z_check == Z && g.n_deu >= 0 && g.n_tri >= 0);

    int total_blocks = g.n_deu + g.n_tri;
    if (total_blocks == 0) {
        g.sym_score = 100.0;  // alpha only
        g.tri_frac = 0.0;
    } else {
        g.tri_frac = static_cast<double>(g.n_tri) / total_blocks;
        // Symmetry: pure deu = 100, even tri > odd tri
        if (g.n_tri == 0) g.sym_score = 100.0;
        else if (g.n_tri % 2 == 0) g.sym_score = 78.0 - 2.0 * g.n_tri;
        else g.sym_score = 59.0 - 2.0 * g.n_tri;
    }
    if (g.sym_score < 0) g.sym_score = 0;
    return g;
}

std::string spin_description(const char* sp) {
    std::string s(sp);
    if (s == "0+") return "All angular momenta cancel by geometric symmetry — serene.";
    if (s == "1+") return "Net angular momentum from unpaired structures.";
    if (s == "1/2+" || s == "1/2-") return "Single unpaired component creates half-integer spin.";
    if (s == "3/2+" || s == "3/2-") return "Coupled angular momentum from asymmetric arrangement.";
    if (s == "5/2+" || s == "5/2-") return "Complex coupling from multiple asymmetric components.";
    if (s == "7/2+" || s == "7/2-") return "High angular momentum from extended nuclear geometry.";
    if (s == "9/2+" || s == "9/2-") return "High coupling from multiple triton asymmetries.";
    return "Angular momentum from geometric coupling of nuclear construction.";
}

std::string tri_regime(double frac) {
    if (frac < 0.001) return "Pure deuteron — maximum geometric symmetry";
    if (frac <= 0.12) return "Deuteron-dominated — highly stable";
    if (frac <= 0.20) return "Near equilibrium — approaching peak throughput reorganisation cost per nucleon";
    if (frac <= 0.35) return "Moderate triton loading — stable but increasingly strained";
    if (frac <= 0.50) return "Heavy triton loading — geometrically stressed";
    return "Triton-overloaded — topological protection failing → radioactive decay";
}

void generate_file(const Isotope& iso, const std::string& dir) {
    Grammar g = compute_grammar(iso.Z, iso.A);
    int N = iso.A - iso.Z;
    double be_per_nucleon = iso.binding_MeV / iso.A;

    std::string filename = dir + "/" +
        (iso.Z < 10 ? "00" : (iso.Z < 100 ? "0" : "")) +
        std::to_string(iso.Z) + "_" +
        iso.symbol + std::to_string(iso.A) + ".md";

    // Check if file already exists
    if (fs::exists(filename)) {
        std::cout << "  SKIP (exists): " << filename << "\n";
        return;
    }

    std::ofstream out(filename);
    if (!out.is_open()) {
        std::cerr << "  ERROR: Cannot write " << filename << "\n";
        return;
    }

    // ── HEADER ──
    out << "# " << iso.element << "-" << iso.A << " — ";
    // Unicode superscript for mass number
    out << "^" << iso.A << iso.symbol << "\n\n";

    // Epithet
    if (g.n_tri == 0 && g.valid)
        out << "**Pure deuteron construction. Maximum geometric symmetry.**\n\n";
    else if (g.n_tri > 0 && g.n_tri % 2 == 0 && g.valid)
        out << "**Even-triton construction. Partially restored symmetry.**\n\n";
    else if (g.n_tri > 0 && g.n_tri % 2 != 0 && g.valid)
        out << "**Odd-triton construction. Broken symmetry.**\n\n";
    else if (!g.valid && iso.Z >= 2)
        out << "**Special construction — grammar edge case.**\n\n";
    else
        out << "**Primordial hydrogen isotope.**\n\n";

    out << "- **Z**: " << iso.Z << " (" << iso.Z << " protons)\n";
    out << "- **A**: " << iso.A << " (" << iso.A << " nucleons)\n";
    out << "- **N**: " << N << " (" << N << " neutrons)\n";
    out << "- **Abundance**: " << std::fixed << std::setprecision(4) << iso.abundance << "% of all " << iso.element << "\n";
    out << "- **Stability**: " << iso.halflife << "\n";
    out << "- **Binding Energy**: " << std::setprecision(3) << iso.binding_MeV
        << " MeV (" << std::setprecision(3) << be_per_nucleon << " MeV/nucleon)\n";
    out << "- **Spin/Parity**: " << iso.spin_parity << "\n";
    out << "- **Atomic Mass**: " << std::setprecision(5) << iso.mass_u << " u\n";
    out << "\n---\n\n";

    // ── NUCLEAR CONSTRUCTION GRAMMAR ──
    out << "## Nuclear Construction Grammar\n\n";

    if (iso.Z == 1) {
        // Hydrogen isotopes — special
        if (iso.A == 1) {
            out << "H-1 is the proton itself — a single W=3 trefoil vortex.\n";
            out << "No alpha core. No deuterons. No tritons. The irreducible charged building block.\n\n";
        } else if (iso.A == 2) {
            out << "H-2 (deuterium) is the **deuteron** — the fundamental nuclear mortar.\n";
            out << "One proton + one neutron (compressed hydrogen atom), bound by convergent boundary pressure.\n\n";
        }
        out << "| Component | Count |\n|-----------|-------|\n";
        out << "| Alpha core | 0 |\n| Deuterons | " << (iso.A == 2 ? 1 : 0) << " |\n| Tritons | 0 |\n\n";
    } else if (iso.Z == 2 && iso.A == 3) {
        // He-3: special — proto-alpha
        out << "He-3 is a **proto-alpha** — an incomplete tetrahedral assembly missing one neutron.\n\n";
        out << "| Component | Count |\n|-----------|-------|\n";
        out << "| Alpha core | 0 (incomplete) |\n| Deuterons | 0 |\n| Tritons | 0 |\n\n";
        out << "He-3 consists of 2 protons and 1 neutron. It cannot be decomposed into the standard α+d+t grammar because it IS the incomplete version of the alpha core. The missing neutron (4th vertex of the tetrahedron) leaves one face exposed — giving He-3 its non-zero spin (1/2+) and magnetic moment, unlike the serene alpha.\n\n";
        out << "This is the ONLY stable nucleus that defies the construction grammar.\n\n";
    } else if (g.valid) {
        out << "| Component | Count |\n|-----------|-------|\n";
        out << "| Alpha core | " << g.n_alpha << " |\n";
        out << "| Deuterons | " << g.n_deu << " |\n";
        out << "| Tritons | " << g.n_tri << " |\n\n";

        out << "$$A = 4 + 2(" << g.n_deu << ") + 3(" << g.n_tri << ") = "
            << iso.A << " \\quad Z = 2 + " << g.n_deu << " + " << g.n_tri
            << " = " << iso.Z << " \\checkmark$$\n\n";

        int total_blocks = g.n_deu + g.n_tri;
        if (g.n_tri == 0) {
            out << iso.element << "-" << iso.A << " is alpha + " << g.n_deu
                << " deuterons, zero tritons. Pure deuteron construction — "
                << "all positions around the alpha core occupied by symmetric d-blocks.\n\n";
        } else if (g.n_tri % 2 == 0) {
            out << iso.element << "-" << iso.A << " is alpha + " << g.n_deu
                << " deuterons + " << g.n_tri << " tritons. The " << g.n_tri
                << " tritons can occupy opposing positions around the alpha core, "
                << "partially restoring the symmetry broken by substitution.\n\n";
        } else {
            out << iso.element << "-" << iso.A << " is alpha + " << g.n_deu
                << " deuterons + " << g.n_tri << " triton" << (g.n_tri > 1 ? "s" : "")
                << ". The odd triton count breaks geometric symmetry — "
                << "one face of the arrangement has no opposing partner.\n\n";
        }

        out << "**Symmetry score**: " << std::setprecision(0) << g.sym_score << "\n\n";
        out << "**Triton fraction**: " << std::setprecision(1) << g.tri_frac * 100
            << "% — " << tri_regime(g.tri_frac) << "\n\n";
    } else {
        out << "Grammar decomposition yields n_deu = " << g.n_deu
            << ", n_tri = " << g.n_tri << " — edge case requiring further analysis.\n\n";
    }

    out << "---\n\n";

    // ── SPIN/PARITY ──
    out << "## Spin and Angular Momentum\n\n";
    out << "- **Spin/Parity**: " << iso.spin_parity << "\n";
    out << "- **Interpretation**: " << spin_description(iso.spin_parity) << "\n\n";
    if (g.valid && g.n_tri == 0 && std::string(iso.spin_parity) == "0+") {
        out << "Zero spin with pure deuteron construction: every angular momentum contribution is geometrically cancelled by its opposing partner. This is the fingerprint of maximum structural serenity.\n\n";
    }
    out << "---\n\n";

    // ── THROUGHPUT ANALYSIS ──
    out << "## Throughput Reorganisation Cost\n\n";
    out << "- **Total binding**: " << std::setprecision(3) << iso.binding_MeV << " MeV\n";
    out << "- **Per nucleon**: " << std::setprecision(3) << be_per_nucleon << " MeV/nucleon\n";
    if (be_per_nucleon > 8.7)
        out << "- **Assessment**: Near peak throughput reorganisation density. This construction is at or near the geometric optimum for the convergent boundary pressure field.\n\n";
    else if (be_per_nucleon > 8.0)
        out << "- **Assessment**: High throughput reorganisation density. Efficient geometric packing.\n\n";
    else if (be_per_nucleon > 7.0)
        out << "- **Assessment**: Moderate throughput reorganisation density. Stable construction.\n\n";
    else
        out << "- **Assessment**: Below equilibrium throughput density. Light nucleus with surface effects dominating.\n\n";

    out << "---\n\n";

    // ── FAMILY CONTEXT ──
    out << "## Family Context\n\n";
    if (iso.abundance > 90.0) {
        out << iso.element << "-" << iso.A << " is the **dominant isotope** of " << iso.element
            << " at " << std::setprecision(4) << iso.abundance << "% abundance.\n\n";
    } else if (iso.abundance > 20.0) {
        out << iso.element << "-" << iso.A << " is a **major isotope** of " << iso.element
            << " at " << std::setprecision(4) << iso.abundance << "% abundance.\n\n";
    } else if (iso.abundance > 1.0) {
        out << iso.element << "-" << iso.A << " is a **minor isotope** of " << iso.element
            << " at " << std::setprecision(4) << iso.abundance << "% abundance.\n\n";
    } else {
        out << iso.element << "-" << iso.A << " is a **trace isotope** of " << iso.element
            << " at " << std::setprecision(4) << iso.abundance << "% abundance.\n\n";
    }

    std::string hl(iso.halflife);
    if (hl != "stable") {
        out << "**Primordially long-lived**: Half-life " << iso.halflife
            << ". Present since the Clearing era, slowly decaying but far from depleted.\n\n";
    }

    // ── CONSTRUCTION CHAINS ──
    out << "## Construction Chains\n\n";
    out << "### Parents\n\n";
    if (iso.Z >= 3 && g.valid) {
        int parent_Z = iso.Z - 1;
        int parent_A_d = iso.A - 2;  // if built by deuteron addition
        int parent_A_t = iso.A - 3;  // if built by triton addition
        auto parent_sym = [](int z) -> const char* {
            static const char* syms[] = {"H","He","Li","Be","B","C","N","O","F","Ne",
                "Na","Mg","Al","Si","P","S","Cl","Ar","K","Ca","Sc","Ti","V","Cr",
                "Mn","Fe","Co","Ni","Cu","Zn","Ga","Ge","As","Se","Br","Kr","Rb",
                "Sr","Y","Zr","Nb","Mo","Tc","Ru","Rh","Pd","Ag","Cd","In","Sn",
                "Sb","Te","I","Xe","Cs","Ba","La","Ce","Pr","Nd","Pm","Sm","Eu",
                "Gd","Tb","Dy","Ho","Er","Tm","Yb","Lu","Hf","Ta","W","Re","Os",
                "Ir","Pt","Au","Hg","Tl","Pb","Bi","Po","At","Rn","Fr","Ra","Ac",
                "Th","Pa","U"};
            if (z >= 1 && z <= 92) return syms[z-1];
            return "?";
        };
        out << "- " << parent_sym(parent_Z) << "-" << parent_A_d << " + d → "
            << iso.symbol << "-" << iso.A << " (deuteron addition)\n";
        out << "- " << parent_sym(parent_Z) << "-" << parent_A_t << " + t → "
            << iso.symbol << "-" << iso.A << " (triton addition)\n\n";
    } else if (iso.Z == 2 && iso.A == 4) {
        out << "- 2 deuterons → He-4 (primordial alpha formation)\n";
        out << "- pp chain: 4H-1 → He-4 + 2e⁺ + 2ν_e + 26.7 MeV\n\n";
    } else {
        out << "- Primordial production from the Clearing era.\n\n";
    }

    out << "### Children\n\n";
    if (iso.Z < 92 && g.valid) {
        auto child_sym = [](int z) -> const char* {
            static const char* syms[] = {"H","He","Li","Be","B","C","N","O","F","Ne",
                "Na","Mg","Al","Si","P","S","Cl","Ar","K","Ca","Sc","Ti","V","Cr",
                "Mn","Fe","Co","Ni","Cu","Zn","Ga","Ge","As","Se","Br","Kr","Rb",
                "Sr","Y","Zr","Nb","Mo","Tc","Ru","Rh","Pd","Ag","Cd","In","Sn",
                "Sb","Te","I","Xe","Cs","Ba","La","Ce","Pr","Nd","Pm","Sm","Eu",
                "Gd","Tb","Dy","Ho","Er","Tm","Yb","Lu","Hf","Ta","W","Re","Os",
                "Ir","Pt","Au","Hg","Tl","Pb","Bi","Po","At","Rn","Fr","Ra","Ac",
                "Th","Pa","U"};
            if (z >= 1 && z <= 92) return syms[z-1];
            return "?";
        };
        out << "- " << iso.symbol << "-" << iso.A << " + d → "
            << child_sym(iso.Z + 1) << "-" << iso.A + 2 << " (deuteron capture)\n";
        out << "- " << iso.symbol << "-" << iso.A << " + t → "
            << child_sym(iso.Z + 1) << "-" << iso.A + 3 << " (triton capture)\n\n";
    } else {
        out << "- End of the stable construction chain.\n\n";
    }

    out << "---\n\n";

    // ── GOLDEN BOUNDARY CHECK ──
    if (iso.Z >= 79 && g.valid) {
        out << "## Golden Boundary Analysis\n\n";
        if (g.n_deu > g.n_tri) {
            out << "Deuterons (" << g.n_deu << ") > Tritons (" << g.n_tri
                << "): **Below the Golden Boundary.** The deuteron skeleton still bears the weight.\n\n";
        } else if (g.n_deu == g.n_tri) {
            out << "Deuterons (" << g.n_deu << ") = Tritons (" << g.n_tri
                << "): **AT the Golden Boundary.** The geometric skeleton is at equilibrium.\n\n";
        } else {
            out << "Deuterons (" << g.n_deu << ") < Tritons (" << g.n_tri
                << "): **BEYOND the Golden Boundary.** Triton-dominant — the geometric skeleton can no longer bear its own weight. Topological protection is failing.\n\n";
        }
        out << "---\n\n";
    }

    // ── CLOSING ──
    out << "*" << iso.element << "-" << iso.A << ": ";
    if (g.valid && g.n_tri == 0) {
        out << g.n_deu << " deuterons around one alpha. Pure geometry. Maximum symmetry.*\n";
    } else if (g.valid) {
        out << g.n_deu << " deuterons + " << g.n_tri << " triton"
            << (g.n_tri != 1 ? "s" : "") << " around one alpha. "
            << std::setprecision(1) << g.tri_frac * 100 << "% triton fraction.*\n";
    } else if (iso.Z == 1) {
        out << "The primordial seed.*\n";
    } else {
        out << "A unique construction.*\n";
    }

    out.close();
    std::cout << "  WROTE: " << filename << "\n";
}

int main() {
    auto isotopes = build_isotope_table();
    std::string dir = "ATOMICUS/isotopes";

    // Ensure dir exists
    fs::create_directories(dir);

    std::cout << "# SDT Isotope File Generator\n\n";
    std::cout << "Total isotopes in table: " << isotopes.size() << "\n\n";

    int written = 0, skipped_flag = 0, skipped_exist = 0;

    for (auto& iso : isotopes) {
        if (iso.skip) {
            std::cout << "  SKIP (flag): " << iso.symbol << "-" << iso.A << "\n";
            skipped_flag++;
            continue;
        }
        generate_file(iso, dir);
        written++;
    }

    std::cout << "\n=== Summary ===\n";
    std::cout << "Written:        " << written << "\n";
    std::cout << "Skipped (flag): " << skipped_flag << "\n";
    std::cout << "Total:          " << isotopes.size() << "\n";

    // Verify grammar for all
    std::cout << "\n=== Grammar Verification ===\n";
    int pass = 0, fail = 0, special = 0;
    for (auto& iso : isotopes) {
        Grammar g = compute_grammar(iso.Z, iso.A);
        if (iso.Z == 1 || (iso.Z == 2 && iso.A == 3)) {
            special++;
            continue;
        }
        if (g.valid) {
            pass++;
        } else {
            fail++;
            std::cout << "  FAIL: " << iso.symbol << "-" << iso.A
                      << " (n_deu=" << g.n_deu << ", n_tri=" << g.n_tri << ")\n";
        }
    }
    std::cout << "Pass: " << pass << ", Fail: " << fail << ", Special: " << special << "\n";

    return 0;
}
