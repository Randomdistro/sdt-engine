// ================================================================
// enrich_isotopes.cpp — Cross-reference element Atomicus data
//                        into isotope files
//
// Reads ionization energies and spectral data from element files,
// appends an "Electronic Structure" section to each isotope file.
//
// Data: empirical measurements only. 938 MeV is 938 MeV.
// ================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>
#include <iomanip>
#include <cmath>
#include <regex>
#include <algorithm>

namespace fs = std::filesystem;

struct IonLevel {
    int level;
    double energy_eV;
    double velocity;
    double k_factor;
    std::string description;
};

struct ElementData {
    int Z;
    std::string symbol;
    std::string name;
    double first_IE;       // eV
    double k_factor;       // c/v for first IE
    double atomic_radius;  // pm
    double electronegativity;
    std::vector<IonLevel> ionisation;
    std::string electron_config;
    // Spectral lines
    struct SpectralLine {
        std::string transition;
        std::string wavelength;
        std::string significance;
    };
    std::vector<SpectralLine> spectral;
};

// Hand-entered empirical data for elements Z=1-30 (richest Atomicus files)
// All values from measured sources
std::vector<ElementData> build_element_data() {
    std::vector<ElementData> elems;

    // Z=1 Hydrogen
    elems.push_back({1, "H", "Hydrogen", 13.598, 137.036, 53.0, 2.20, {
        {1, 13.598, 2.187e6, 137.036, "The Rydberg. Universal reference."}
    }, "1s1", {
        {"Lyman-alpha (1s-2p)", "121.6 nm (UV)", "Strongest emission line in the universe"},
        {"Balmer-alpha (2-3)", "656.3 nm (red)", "Hydrogen red — every nebula"},
        {"21-cm hyperfine", "21.1 cm (radio)", "Maps the universe"}
    }});

    // Z=2 Helium
    elems.push_back({2, "He", "Helium", 24.587, 101.9, 31.0, 0.0, {
        {1, 24.587, 2.940e6, 101.9, "The Fortress Wall. Counter-rotating dyad."},
        {2, 54.418, 4.373e6, 68.5, "Z-squared: 13.6x4 = 54.4 eV"}
    }, "1s2", {
        {"1s-2p", "58.4 nm (EUV)", "Extreme UV lithography"},
        {"D3 (3d-2p)", "587.6 nm (yellow)", "Discovered in the Sun before Earth"}
    }});

    // Z=3 Lithium
    elems.push_back({3, "Li", "Lithium", 5.392, 218.0, 152.0, 0.98, {
        {1, 5.392, 1.377e6, 218.0, "Barely bound 2s electron"},
        {2, 75.640, 5.156e6, 58.1, "Alpha core breach — 14x jump"}
    }, "[He]2s1", {
        {"2s-2p", "670.8 nm (red)", "Lithium red line — identifies brown dwarfs"}
    }});

    // Z=4 Beryllium
    elems.push_back({4, "Be", "Beryllium", 9.323, 155.6, 112.0, 1.57, {
        {1, 9.323, 1.811e6, 155.6, "2s dyad first electron"},
        {2, 18.211, 2.531e6, 111.3, "2s dyad second electron"},
        {3, 153.896, 7.356e6, 48.2, "Alpha core breach — 135.7 eV gap!"},
        {4, 217.718, 8.748e6, 40.5, "Z-squared: 13.6x16 = 217.7 eV (0.01% match)"}
    }, "[He]2s2", {}});

    // Z=5 Boron
    elems.push_back({5, "B", "Boron", 8.298, 165.0, 87.0, 2.04, {
        {1, 8.298, 1.708e6, 165.0, "Trigonal plane breach"},
        {2, 25.155, 2.973e6, 100.8, ""},
        {3, 37.930, 3.652e6, 82.0, ""},
        {4, 259.375, 9.545e6, 31.4, "Alpha core breach"},
        {5, 340.228, 10.93e6, 27.4, "Z-squared: 13.6x25 = 340 eV"}
    }, "[He]2s2 2p1", {}});

    // Z=6 Carbon
    elems.push_back({6, "C", "Carbon", 11.260, 150.6, 77.0, 2.55, {
        {1, 11.260, 1.990e6, 150.6, "The Lock. Tetrahedral geometry."},
        {2, 24.383, 2.929e6, 102.4, ""},
        {3, 47.888, 4.103e6, 73.1, ""},
        {4, 64.492, 4.762e6, 62.9, ""},
        {5, 392.090, 11.74e6, 25.5, "Alpha core breach — 392 eV!"},
        {6, 489.990, 13.12e6, 22.8, "Z-squared: 13.6x36 = 489.6 eV (0.08%)"}
    }, "[He]2s2 2p2", {
        {"2s2p-2s3s", "247.9 nm (UV)", "UV optical standard"},
        {"C IV", "154.8 nm", "Quasar beacon — AGN UV line"}
    }});

    // Z=7 Nitrogen
    elems.push_back({7, "N", "Nitrogen", 14.534, 157.0, 75.0, 3.04, {
        {1, 14.534, 2.261e6, 132.7, "Half-filled p-shell stability"},
        {2, 29.601, 3.228e6, 92.9, ""},
        {3, 47.449, 4.084e6, 73.4, ""}
    }, "[He]2s2 2p3", {}});

    // Z=8 Oxygen
    elems.push_back({8, "O", "Oxygen", 13.618, 137.0, 73.0, 3.44, {
        {1, 13.618, 2.189e6, 137.0, "Almost exactly hydrogen k. The mirror."},
        {2, 35.117, 3.514e6, 85.3, ""},
        {3, 54.936, 4.395e6, 68.3, ""}
    }, "[He]2s2 2p4", {
        {"O I", "777.4 nm", "Atmospheric aurora line"},
        {"O III", "500.7 nm (green)", "Planetary nebula green — 'nebulium'"}
    }});

    // Z=9 Fluorine
    elems.push_back({9, "F", "Fluorine", 17.423, 143.6, 71.0, 3.98, {
        {1, 17.423, 2.475e6, 121.1, "Cube minus one — maximum electron vacuum"}
    }, "[He]2s2 2p5", {}});

    // Z=10 Neon
    elems.push_back({10, "Ne", "Neon", 21.565, 108.9, 38.0, 0.0, {
        {1, 21.565, 2.754e6, 108.9, "The Wall. Cubic closure complete."},
        {2, 40.963, 3.794e6, 79.0, ""}
    }, "[He]2s2 2p6", {
        {"3s-2p", "632.8 nm (red)", "HeNe laser line"},
        {"Visible emission", "Red-orange", "Neon signs"}
    }});

    // Z=11 Sodium
    elems.push_back({11, "Na", "Sodium", 5.139, 223.0, 186.0, 0.93, {
        {1, 5.139, 1.345e6, 223.0, "The Loose Thread. Barely held 3s."},
        {2, 47.286, 4.078e6, 73.5, "Neon core breach — 9x jump!"}
    }, "[Ne]3s1", {
        {"D1 (3s-3p)", "589.6 nm (yellow)", "Street lighting — classic sodium glow"},
        {"D2 (3s-3p)", "589.0 nm (yellow)", "Guidestar lasers for telescope correction"}
    }});

    // Z=12 Magnesium
    elems.push_back({12, "Mg", "Magnesium", 7.646, 172.0, 160.0, 1.31, {
        {1, 7.646, 1.640e6, 172.0, "First 3s electron"},
        {2, 15.035, 2.300e6, 130.4, "Second 3s — spark flash"},
        {3, 80.144, 5.309e6, 56.5, "Neon core breach"}
    }, "[Ne]3s2", {
        {"Mg I", "285.2 nm (UV)", "Stellar atmosphere diagnostic"},
        {"Mg II h&k", "279.6/280.3 nm", "Chromosphere/ISM tracer"}
    }});

    // Z=13 Aluminium
    elems.push_back({13, "Al", "Aluminium", 5.986, 194.3, 143.0, 1.61, {
        {1, 5.986, 1.451e6, 194.3, "Boron echo — trigonal electron"},
        {2, 18.829, 2.573e6, 110.0, ""},
        {3, 28.448, 3.163e6, 94.8, "3s dyad breach"}
    }, "[Ne]3s2 3p1", {}});

    // Z=14 Silicon
    elems.push_back({14, "Si", "Silicon", 8.152, 166.6, 117.0, 1.90, {
        {1, 8.152, 1.693e6, 166.6, "Carbon echo — tetrahedral seed"},
        {2, 16.346, 2.397e6, 125.0, ""}
    }, "[Ne]3s2 3p2", {}});

    // Z=15 Phosphorus
    elems.push_back({15, "P", "Phosphorus", 10.487, 147.0, 110.0, 2.19, {
        {1, 10.487, 1.921e6, 147.0, "Nitrogen echo — half-shell stability"}
    }, "[Ne]3s2 3p3", {}});

    // Z=16 Sulfur
    elems.push_back({16, "S", "Sulfur", 10.360, 148.0, 104.0, 2.58, {
        {1, 10.360, 1.909e6, 148.0, "Oxygen echo — paired p-electron"}
    }, "[Ne]3s2 3p4", {}});

    // Z=17 Chlorine
    elems.push_back({17, "Cl", "Chlorine", 12.968, 132.2, 99.0, 3.16, {
        {1, 12.968, 2.135e6, 132.2, "Fluorine echo — cube minus one"}
    }, "[Ne]3s2 3p5", {}});

    // Z=18 Argon
    elems.push_back({18, "Ar", "Argon", 15.760, 120.0, 71.0, 0.0, {
        {1, 15.760, 2.354e6, 120.0, "Neon echo — cubic closure"}
    }, "[Ne]3s2 3p6", {}});

    // Z=26 Iron
    elems.push_back({26, "Fe", "Iron", 7.902, 179.8, 126.0, 1.83, {
        {1, 7.902, 1.667e6, 179.8, "The Rusting Step. 4s outer guard."},
        {2, 16.190, 2.386e6, 125.6, "Ferrous ion Fe2+"},
        {3, 30.650, 3.283e6, 91.3, "Ferric ion Fe3+ — rust"}
    }, "[Ar]3d6 4s2", {
        {"Fe I", "372.0 nm (UV)", "Stellar metallicity standard ruler"},
        {"Fe II", "260.0 nm (UV)", "Interstellar medium — most iron is Fe+"},
        {"K-alpha X-ray", "0.194 nm (6.4 keV)", "Black hole spin measurement — the Iron Line"}
    }});

    return elems;
}

// Find element data by Z
const ElementData* find_element(const std::vector<ElementData>& elems, int Z) {
    for (auto& e : elems)
        if (e.Z == Z) return &e;
    return nullptr;
}

// Check if isotope file already has enrichment
bool already_enriched(const std::string& path) {
    std::ifstream f(path);
    std::string line;
    while (std::getline(f, line)) {
        if (line.find("## Electronic Structure") != std::string::npos)
            return true;
        if (line.find("## Ionisation Series") != std::string::npos)
            return true;
    }
    return false;
}

void enrich_isotope(const std::string& path, const ElementData& elem, int A) {
    if (already_enriched(path)) {
        std::cout << "  SKIP (enriched): " << path << "\n";
        return;
    }

    // Read existing content
    std::ifstream in(path);
    std::string content((std::istreambuf_iterator<char>(in)),
                         std::istreambuf_iterator<char>());
    in.close();

    // Remove trailing closing epithet line to insert before it
    // Find the last line starting with '*'
    auto last_star = content.rfind("\n*");
    std::string closing;
    if (last_star != std::string::npos) {
        closing = content.substr(last_star);
        content = content.substr(0, last_star);
    }

    // Append enrichment
    std::ofstream out(path);
    out << content;

    out << "\n## Electronic Structure (from " << elem.name << " Atomicus)\n\n";
    out << "**Electron configuration**: " << elem.electron_config << "\n\n";

    // Ionisation series
    if (!elem.ionisation.empty()) {
        out << "### Ionisation Series\n\n";
        out << "| Level | Energy (eV) | k-factor | Description |\n";
        out << "|-------|-------------|----------|-------------|\n";
        for (auto& ion : elem.ionisation) {
            out << "| " << ion.level << " | " << std::fixed << std::setprecision(3)
                << ion.energy_eV << " | " << std::setprecision(1)
                << ion.k_factor << " | " << ion.description << " |\n";
        }
        out << "\n";
        if (elem.ionisation.size() >= 2) {
            double ratio = elem.ionisation[1].energy_eV / elem.ionisation[0].energy_eV;
            out << "**IE₂/IE₁ ratio**: " << std::setprecision(1) << ratio;
            if (ratio > 5.0)
                out << " — massive gap indicates core breach\n\n";
            else if (ratio > 2.0)
                out << " — moderate gap\n\n";
            else
                out << " — gradual stripping\n\n";
        }
    }

    // Spectral signatures
    if (!elem.spectral.empty()) {
        out << "### Spectral Signatures\n\n";
        out << "| Transition | Wavelength | Significance |\n";
        out << "|------------|-----------|-------------|\n";
        for (auto& s : elem.spectral) {
            out << "| " << s.transition << " | " << s.wavelength
                << " | " << s.significance << " |\n";
        }
        out << "\n";
    }

    // Kinematic ratio
    out << "### Kinematic Properties\n\n";
    out << "- **First ionisation**: " << std::setprecision(3) << elem.first_IE << " eV\n";
    out << "- **k-factor (χ = c/v)**: " << std::setprecision(1) << elem.k_factor << "\n";
    if (elem.atomic_radius > 0)
        out << "- **Atomic radius**: " << std::setprecision(0) << elem.atomic_radius << " pm\n";
    if (elem.electronegativity > 0)
        out << "- **Electronegativity**: " << std::setprecision(2) << elem.electronegativity << " (Pauling)\n";
    out << "- **Movement budget**: v²_circ + v² = c²  →  v_circ = c × √(1 − 1/χ²) ≈ c\n";
    out << "\n---\n";

    out << closing;
    out.close();

    std::cout << "  ENRICHED: " << path << "\n";
}

int main() {
    auto elems = build_element_data();
    std::string dir = "ATOMICUS/isotopes";

    std::cout << "# Isotope Enrichment Pass\n\n";
    std::cout << "Element data available for " << elems.size() << " elements\n\n";

    int enriched = 0, skipped = 0;

    for (auto& entry : fs::directory_iterator(dir)) {
        if (!entry.is_regular_file()) continue;
        std::string fname = entry.path().filename().string();
        if (fname.find("INVESTIGATION") != std::string::npos) continue;
        if (!fname.ends_with(".md")) continue;

        // Parse Z from filename: "026_Fe56.md" → Z=26
        int Z = 0;
        try {
            Z = std::stoi(fname.substr(0, 3));
        } catch (...) { continue; }

        auto* elem = find_element(elems, Z);
        if (!elem) {
            skipped++;
            continue;
        }

        // Parse A from filename
        int A = 0;
        auto under = fname.find('_', 4);
        if (under != std::string::npos) {
            // e.g. "Fe56.md" → extract 56
            std::string rest = fname.substr(under + 1);
            // Strip symbol letters, get number
            size_t num_start = 0;
            while (num_start < rest.size() && !std::isdigit(rest[num_start])) num_start++;
            size_t num_end = num_start;
            while (num_end < rest.size() && std::isdigit(rest[num_end])) num_end++;
            if (num_start < num_end) {
                try { A = std::stoi(rest.substr(num_start, num_end - num_start)); }
                catch (...) {}
            }
        }

        enrich_isotope(entry.path().string(), *elem, A);
        enriched++;
    }

    std::cout << "\n=== Summary ===\n";
    std::cout << "Enriched:  " << enriched << "\n";
    std::cout << "Skipped (no element data): " << skipped << "\n";

    return 0;
}
