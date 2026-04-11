#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>

constexpr double c_mps = 2.99792458e8; // m/s — the only constant

// Format scientific notation for markdown
std::string sci(double v, int prec = 4) {
    std::ostringstream ss;
    ss << std::scientific << std::setprecision(prec) << v;
    return ss.str();
}

std::string fix(double v, int prec = 2) {
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(prec) << v;
    return ss.str();
}

struct Body {
    std::string name;
    double R_m;
    double z;
};

int main() {
    // ================================================================
    // OUTPUT MARKDOWN DIRECTLY
    // ================================================================

    std::cout << "# Epsilon Eridani - zk^2=1 System Map (Clean Formulation)\n\n";
    std::cout << "> **Three relations, no G:**\n";
    std::cout << "> - `v = c/k` -- surface coupling velocity\n";
    std::cout << "> - `r_cb = R/k^2 = Rz` -- c-boundary (= 1/2 Schwarzschild)\n";
    std::cout << "> - `k = 1 -> v = c, r_cb = R` -- event horizon condition\n\n";
    std::cout << "---\n\n";

    // ---- FORMULATION ----
    std::cout << "## The Formulation\n\n";
    std::cout << "```\n";
    std::cout << "z       = measured (spectral shift)\n";
    std::cout << "k       = 1/sqrt(z)\n";
    std::cout << "v       = c/k = c*sqrt(z)           (surface coupling velocity)\n";
    std::cout << "kappa   = R*z                        (c-orbit anchor, metres)\n";
    std::cout << "r_cb    = R/k^2 = Rz                 (c-boundary)\n";
    std::cout << "v(r)    = (c/k)*sqrt(R/r)            (orbital velocity at distance r)\n\n";
    std::cout << "At k=1:  v = c,  r_cb = R            (event horizon)\n\n";
    std::cout << "Three inputs: z (measured), R (measured), c (defined).\n";
    std::cout << "Everything else follows.\n";
    std::cout << "```\n\n";
    std::cout << "---\n\n";

    // ---- BODIES TABLE ----
    std::cout << "## Bodies Through zk^2=1\n\n";

    std::vector<Body> bodies = {
        {"Earth",         6.371e6,   6.9536e-10},
        {"Jupiter",       7.149e7,   1.4838e-8},
        {"Aegir (b)",     8.937e7,   1.5773e-8},
        {"Eps Eri",       5.113e8,   2.3686e-6},
        {"Sun",           6.957e8,   2.1226e-6},
        {"Neutron star",  1.0e4,     0.15},
    };

    std::cout << "| Body | R (m) | z | k | v (m/s) | r_cb (m) | r_s (m) | zk^2 |\n";
    std::cout << "|------|-------|---|---|---------|----------|---------|------|\n";

    for (auto& b : bodies) {
        double k      = 1.0 / std::sqrt(b.z);
        double v_surf = c_mps / k;
        double r_cb   = b.R_m / (k * k);
        double r_s    = 2.0 * r_cb;
        double zk2    = b.z * k * k;

        std::cout << "| " << b.name
                  << " | " << sci(b.R_m, 3)
                  << " | " << sci(b.z)
                  << " | " << fix(k, 1)
                  << " | " << fix(v_surf, 1)
                  << " | " << sci(r_cb, 3)
                  << " | " << sci(r_s, 3)
                  << " | " << fix(zk2, 6)
                  << " |\n";
    }

    std::cout << "\nRead the columns:\n";
    std::cout << "- **v**: Earth surface = 7.9 km/s (orbital velocity). ";
    std::cout << "Neutron star = 0.39c. At k=1, v=c. That's the horizon.\n";
    std::cout << "- **r_cb**: Earth's c-boundary is 4.4 mm. ";
    std::cout << "The Sun's is 1,477 m. Half the Schwarzschild radius in every case.\n\n";
    std::cout << "---\n\n";

    // ---- EPSILON ERIDANI SYSTEM ----
    std::cout << "## Epsilon Eridani System\n\n";

    double z_s = 2.3686e-6;
    double R_s = 5.113e8;
    double k_s = 1.0 / std::sqrt(z_s);
    double v_s = c_mps / k_s;
    double rcb_s = R_s / (k_s * k_s);
    double rs_s = 2.0 * rcb_s;

    std::cout << "### Star (Ran)\n\n";
    std::cout << "```\n";
    std::cout << "R = " << sci(R_s) << " m    (measured: interferometry + parallax)\n";
    std::cout << "z = " << sci(z_s) << "    (measured: spectral lines)\n";
    std::cout << "k = " << fix(k_s, 1) << "\n";
    std::cout << "v = c/" << fix(k_s, 1) << " = " << fix(v_s/1000.0) << " km/s\n";
    std::cout << "r_cb = R/k^2 = " << fix(rcb_s, 1) << " m\n";
    std::cout << "r_s  = " << fix(rs_s, 1) << " m\n";
    std::cout << "```\n\n";

    double z_p = 1.5773e-8;
    double R_p = 8.937e7;
    double k_p = 1.0 / std::sqrt(z_p);
    double v_p = c_mps / k_p;
    double rcb_p = R_p / (k_p * k_p);
    double rs_p = 2.0 * rcb_p;

    std::cout << "### Planet b (Aegir)\n\n";
    std::cout << "```\n";
    std::cout << "R = " << sci(R_p) << " m    (derived from k-ratio)\n";
    std::cout << "z = " << sci(z_p) << "    (derived from k-ratio)\n";
    std::cout << "k = " << fix(k_p, 1) << "\n";
    std::cout << "v = c/" << fix(k_p, 1) << " = " << fix(v_p/1000.0) << " km/s\n";
    std::cout << "r_cb = R/k^2 = " << fix(rcb_p, 3) << " m\n";
    std::cout << "r_s  = " << fix(rs_p, 3) << " m\n";
    std::cout << "```\n\n";

    // k-ratio
    double k_ratio = k_p / k_s;
    std::cout << "### k-Ratio\n\n";
    std::cout << "```\n";
    std::cout << "k_b / k_star = " << fix(k_p, 1) << " / " << fix(k_s, 1) << " = " << fix(k_ratio, 4) << "\n";
    std::cout << "(k_b / k_star)^2 = " << fix(k_ratio * k_ratio, 1) << "\n\n";
    std::cout << "This IS the M/R encoding:\n";
    std::cout << "  k_b/k_star = sqrt((M_star*R_b)/(M_b*R_star))\n";
    std::cout << "  Know any 3 -> get the 4th.\n";
    std::cout << "```\n\n";
    std::cout << "---\n\n";

    // ---- ORBITAL MAP ----
    std::cout << "## Orbital Map\n\n";
    std::cout << "Every orbit has a z, a k, and a velocity -- derived from the\n";
    std::cout << "star's z and R alone:\n\n";
    std::cout << "```\n";
    std::cout << "z(r) = z_star * (R_star/r)\n";
    std::cout << "k(r) = k_star * sqrt(r/R_star)\n";
    std::cout << "v(r) = c/k(r)\n";
    std::cout << "```\n\n";

    double AU = 1.496e11;
    struct Orbit { std::string name; double r_AU; };
    std::vector<Orbit> orbits = {
        {"Inner belt",      3.0},
        {"Planet b",        3.53},
        {"Gap edge",        8.0},
        {"Secondary belt", 20.0},
        {"Main belt inner",60.0},
        {"Main belt peak", 69.0},
        {"Main belt outer",90.0},
    };

    double v_at_b = c_mps / (k_s * std::sqrt(3.53 * AU / R_s));

    std::cout << "| Feature | r (AU) | z(r) | k(r) | v (km/s) | v/v_b |\n";
    std::cout << "|---------|--------|------|------|----------|-------|\n";

    for (auto& o : orbits) {
        double r = o.r_AU * AU;
        double z_r = z_s * (R_s / r);
        double k_r = k_s * std::sqrt(r / R_s);
        double v_r = c_mps / k_r;

        std::cout << "| " << o.name
                  << " | " << fix(o.r_AU)
                  << " | " << sci(z_r)
                  << " | " << fix(k_r, 0)
                  << " | " << fix(v_r / 1000.0)
                  << " | " << fix(v_r / v_at_b, 4)
                  << " |\n";
    }

    std::cout << "\nPlanet b orbits at k = 20,882. The gap it clears spans\n";
    std::cout << "k = 19,251 to k = 31,436. The main belt peaks at k = 92,000\n";
    std::cout << "where orbital velocity has dropped to 23% of the planet's.\n\n";
    std::cout << "---\n\n";

    // ---- THE POINT ----
    std::cout << "## The Point\n\n";
    std::cout << "```\n";
    std::cout << "Traditional: needs G, M, R, c\n";
    std::cout << "  G is measured to 22 ppm. Worst constant in physics.\n\n";
    std::cout << "zk^2=1: needs z, R, c\n";
    std::cout << "  z < 1 ppm. R < 10 ppm. c = exact.\n\n";
    std::cout << "v = c/k\n";
    std::cout << "r_cb = R/k^2  = 1/2 Schwarzschild\n";
    std::cout << "k = 1 => event horizon\n\n";
    std::cout << "G = zRc^2/M\n";
    std::cout << "G is a conversion factor. Not a law.\n";
    std::cout << "```\n\n";

    std::cout << "JWST pointed a $10B telescope at this system and got a\n";
    std::cout << "diffraction artifact. The entire architecture -- star,\n";
    std::cout << "planet, debris belts, clearing zones -- is encoded in\n";
    std::cout << "three symbols: z, k, R. Measured from the spectral lines.\n\n";
    std::cout << "The number was always in the light.\n";

    return 0;
}
