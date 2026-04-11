#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

// ==============================================================
// THE ONLY PHYSICAL CONSTANT
// ==============================================================
constexpr double c = 2.99792458e8;  // m/s — defined exactly
constexpr double pi = 3.14159265358979;

// ==============================================================
// STEP 0: zk²=1 is the first value
// z is MEASURED from spectral lines 
// z is the measured redshift caused by spatial displacement, λ_observed/λ_emitted 
// k = 1/√z
// Everything else derives from z.  
// ==============================================================

// z = λ_observed/λ_emitted

struct Star {
    std::string name;
    double z;           // MEASURED: spatial displacement redshift
    double R_m;         // MEASURED: stellar radius in metres
    double k;           // = 1/√z
    double kappa_m;     // = R/k² = R*z  (c-orbit anchor)
    double v_surface;   // = c/k
};

Star make_star(const std::string& name, double z, double R_m) {
    Star s;
    s.name = name;
    s.z = z;
    s.R_m = R_m;
    s.k = 1.0 / std::sqrt(z);
    s.kappa_m = R_m / (s.k * s.k);
    s.v_surface = c / s.k;
    return s;
}

struct Planet {
    std::string name;
    double P_s;         // MEASURED: orbital period in seconds
    double K_mps;       // MEASURED: star wobble semi-amplitude in m/s
};

std::string sci(double v, int p = 4) {
    std::ostringstream s; s << std::scientific << std::setprecision(p) << v; return s.str();
}
std::string fix(double v, int p = 2) {
    std::ostringstream s; s << std::fixed << std::setprecision(p) << v; return s.str();
}

// Kepler from kappa: a = (κ * c² * P² / (4π²))^(1/3)
double get_a(double kappa_m, double P_s) {
    return std::cbrt(kappa_m * c * c * P_s * P_s / (4.0 * pi * pi));
}

void print_usage() {
    std::cerr << "zk2_mapper — zk^2=1 system calculator\n\n";
    std::cerr << "Usage:\n";
    std::cerr << "  zk2_mapper star <name> <z> <R_km>\n";
    std::cerr << "  zk2_mapper orbit <star_z> <star_R_km> <planet_name> <P_days> <K_m/s>\n";
    std::cerr << "  zk2_mapper system <star_name> <star_z> <star_R_km> [planet_name P_days K_m/s] ...\n\n";
    std::cerr << "All inputs are measured quantities. \n";
    std::cerr << "  z     = spatial displacement redshift (lambda_obs/lambda_emit)\n";
    std::cerr << "  R_km  = stellar radius in km\n";
    std::cerr << "  P     = orbital period in days\n";
    std::cerr << "  K     = star wobble semi-amplitude in m/s\n";
}

void print_star(const Star& s) {
    std::cout << "Star: " << s.name << "\n";
    std::cout << "  z         = " << sci(s.z) << "  (measured)\n";
    std::cout << "  R         = " << fix(s.R_m / 1e3, 1) << " km\n";
    std::cout << "  k         = " << fix(s.k, 2) << "\n";
    std::cout << "  v         = c/k = " << fix(s.v_surface / 1e3, 2) << " km/s\n";
    std::cout << "  kappa     = R/k^2 = " << fix(s.kappa_m, 4) << " m\n";
    std::cout << "  r_s       = 2*kappa = " << fix(2.0 * s.kappa_m, 4) << " m\n";
    std::cout << "  zk^2      = " << fix(s.z * s.k * s.k, 6) << "\n";
}

void print_orbit(const Star& s, const Planet& p) {
    double a = get_a(s.kappa_m, p.P_s);
    double k_orb = std::sqrt(a / s.kappa_m);
    double v_orb = c / k_orb;
    double z_orb = 1.0 / (k_orb * k_orb);  // = kappa/a
    double mu = (p.K_mps / c) * k_orb;
    double dz_wobble = p.K_mps / c;         // wobble as z
    double dz_ratio = dz_wobble / s.z;      // wobble / star surface z

    std::cout << "Planet: " << p.name << "\n";
    std::cout << "  P         = " << fix(p.P_s / 86400.0, 4) << " days\n";
    std::cout << "  K         = " << fix(p.K_mps, 4) << " m/s  (wobble)\n";
    std::cout << "  a         = " << sci(a) << " m  (" << fix(a / 1.496e11, 4) << " AU)\n";
    std::cout << "  k_orb     = " << fix(k_orb, 2) << "\n";
    std::cout << "  v_orb     = c/k_orb = " << fix(v_orb / 1e3, 4) << " km/s\n";
    std::cout << "  z_orb     = 1/k_orb^2 = " << sci(z_orb) << "\n";
    std::cout << "  zk^2      = " << fix(z_orb * k_orb * k_orb, 6) << "\n";
    std::cout << "  mu        = K*k_orb/c = " << sci(mu) << "\n";
    std::cout << "  dz_wobble = K/c = " << sci(dz_wobble) << "\n";
    std::cout << "  dz/z_star = " << fix(dz_ratio * 100.0, 4) << " %\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        print_usage();
        return 1;
    }

    std::string mode = argv[1];

    // ---- STAR MODE: just compute star properties ----
    if (mode == "star") {
        if (argc < 5) {
            std::cerr << "Usage: zk2_mapper star <name> <z> <R_km>\n";
            return 1;
        }
        Star s = make_star(argv[2], std::stod(argv[3]), std::stod(argv[4]) * 1e3);
        print_star(s);
        return 0;
    }

    // ---- ORBIT MODE: single planet ----
    if (mode == "orbit") {
        if (argc < 8) {
            std::cerr << "Usage: zk2_mapper orbit <star_z> <star_R_km> <planet_name> <P_days> <K_m/s>\n";
            return 1;
        }
        Star s = make_star("host", std::stod(argv[2]), std::stod(argv[3]) * 1e3);
        Planet p = {argv[4], std::stod(argv[5]) * 86400.0, std::stod(argv[6])};
        print_star(s);
        std::cout << "\n";
        print_orbit(s, p);
        return 0;
    }

    // ---- SYSTEM MODE: star + multiple planets ----
    if (mode == "system") {
        if (argc < 5) {
            std::cerr << "Usage: zk2_mapper system <star_name> <star_z> <star_R_km> [planet_name P_days K_m/s] ...\n";
            return 1;
        }
        Star s = make_star(argv[2], std::stod(argv[3]), std::stod(argv[4]) * 1e3);
        print_star(s);
        std::cout << "\n";

        // Parse planets: groups of 3 args (name, P_days, K_mps)
        std::vector<Planet> planets;
        for (int i = 5; i + 2 < argc; i += 3) {
            planets.push_back({argv[i], std::stod(argv[i+1]) * 86400.0, std::stod(argv[i+2])});
        }

        if (planets.empty()) {
            std::cout << "No planets specified.\n";
            return 0;
        }

        std::cout << "| Planet | P (days) | K (m/s) | a (AU) | k_orb | v_orb (km/s) | z_orb | mu | dz/z_star |\n";
        std::cout << "|--------|----------|---------|--------|-------|-------------|-------|------|----------|\n";

        for (auto& p : planets) {
            double a = get_a(s.kappa_m, p.P_s);
            double k_orb = std::sqrt(a / s.kappa_m);
            double v_orb = c / k_orb;
            double z_orb = 1.0 / (k_orb * k_orb);
            double mu = (p.K_mps / c) * k_orb;
            double dz_ratio = (p.K_mps / c) / s.z;

            std::cout << "| " << p.name
                      << " | " << fix(p.P_s / 86400.0, 2)
                      << " | " << fix(p.K_mps, 3)
                      << " | " << fix(a / 1.496e11, 4)
                      << " | " << fix(k_orb, 0)
                      << " | " << fix(v_orb / 1e3, 4)
                      << " | " << sci(z_orb, 3)
                      << " | " << sci(mu, 3)
                      << " | " << fix(dz_ratio * 100.0, 4) << "%"
                      << " |\n";
        }
    }

    return 0;
}
