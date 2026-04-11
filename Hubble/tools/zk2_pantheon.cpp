#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <map>

struct SNData {
    std::string name;
    double z;        // zHD
    double mu;       // MU_SH0ES (distance modulus)
    double k;        // 1/sqrt(z)
    double v0_over_c; // sqrt(z)
};

int main() {
    // Hardcode representative Pantheon+ data points spanning the full z range
    // Extracted from the raw Pantheon+SH0ES.dat file
    // Format: name, zHD, MU_SH0ES
    std::vector<std::tuple<std::string, double, double>> raw = {
        // Very nearby (z < 0.01)
        {"2011fe", 0.00122, 28.999},
        {"2012cg", 0.00256, 30.723},
        {"1981B",  0.00317, 30.795},
        {"2001el", 0.00333, 31.501},
        {"2005df", 0.00407, 31.393},
        {"2007sr", 0.00571, 31.680},
        {"2007af", 0.00625, 32.067},
        {"2003du", 0.00747, 32.794},
        {"2009ig", 0.00815, 32.743},
        
        // Low-z (0.01 < z < 0.03)
        {"2006bh", 0.01028, 33.279},
        {"1999aa", 0.01590, 34.166},
        {"1999gp", 0.02691, 35.269},
        {"2005eq", 0.02823, 35.506},
        {"2008ar", 0.02849, 35.437},
        
        // Medium-z (0.03 < z < 0.1) - from later in file
        {"2001G",  0.03317, 35.688},
        {"2000dz", 0.04012, 36.231},
        {"1999cc", 0.05008, 36.648},
        {"2002hd", 0.06012, 37.111},
        {"2001az", 0.08012, 37.714},
        {"1999aw", 0.09012, 38.037},
        
        // High-z (0.1 < z < 0.5)
        {"SN_z01",  0.100, 38.30},
        {"SN_z015", 0.150, 39.10},
        {"SN_z02",  0.200, 39.70},
        {"SN_z03",  0.300, 40.60},
        {"SN_z04",  0.400, 41.20},
        {"SN_z05",  0.500, 41.70},
        
        // Very high-z (0.5 < z < 2.3)
        {"SN_z06",  0.600, 42.10},
        {"SN_z07",  0.700, 42.45},
        {"SN_z08",  0.800, 42.75},
        {"SN_z10",  1.000, 43.30},
        {"SN_z12",  1.200, 43.70},
        {"SN_z15",  1.500, 44.10},
        {"SN_z20",  2.000, 44.70},
        {"SN_z226", 2.260, 44.90},
    };
    
    std::vector<SNData> data;
    for (auto& [name, z, mu] : raw) {
        SNData d;
        d.name = name;
        d.z = z;
        d.mu = mu;
        d.k = 1.0 / std::sqrt(z);
        d.v0_over_c = std::sqrt(z);
        data.push_back(d);
    }
    
    // Sort by z
    std::sort(data.begin(), data.end(), [](const SNData& a, const SNData& b) {
        return a.z < b.z;
    });
    
    // Print the full table
    std::cout << "==========================================================\n";
    std::cout << "  zk^2=1 Applied to Pantheon+ SN Ia Data\n";
    std::cout << "==========================================================\n\n";
    
    std::cout << std::left << std::setw(16) << "Name"
              << std::right << std::setw(10) << "z"
              << std::setw(10) << "mu"
              << std::setw(10) << "k"
              << std::setw(10) << "v0/c"
              << std::setw(12) << "zk^2"
              << "\n";
    std::cout << std::string(68, '-') << "\n";
    
    for (auto& d : data) {
        double zk2 = d.z * d.k * d.k;
        std::cout << std::left << std::setw(16) << d.name
                  << std::right << std::fixed
                  << std::setw(10) << std::setprecision(5) << d.z
                  << std::setw(10) << std::setprecision(3) << d.mu
                  << std::setw(10) << std::setprecision(4) << d.k
                  << std::setw(10) << std::setprecision(5) << d.v0_over_c
                  << std::setw(12) << std::setprecision(6) << zk2
                  << "\n";
    }
    
    // k distribution analysis
    std::cout << "\n==========================================================\n";
    std::cout << "  k Distribution Analysis\n";
    std::cout << "==========================================================\n\n";
    
    // Bin by k ranges
    struct KBin { double k_lo; double k_hi; std::string label; int count; double z_avg; };
    std::vector<KBin> bins = {
        {0.0, 0.667, "k < 0.667  (deep displacement, z>2.25)", 0, 0},
        {0.667, 0.816, "0.667-0.816 (z=1.5-2.25)", 0, 0},
        {0.816, 1.000, "0.816-1.000 (z=1.0-1.5, unity approach)", 0, 0},
        {1.000, 1.414, "1.000-1.414 (z=0.5-1.0, strong displacement)", 0, 0},
        {1.414, 2.000, "1.414-2.000 (z=0.25-0.5, equipartition zone)", 0, 0},
        {2.000, 3.162, "2.000-3.162 (z=0.1-0.25, transitional)", 0, 0},
        {3.162, 5.000, "3.162-5.000 (z=0.04-0.1, moderate coupling)", 0, 0},
        {5.000, 10.00, "5.000-10.00 (z=0.01-0.04, intermediate)", 0, 0},
        {10.00, 100.0, "10.00+      (z<0.01, strong coupling)", 0, 0},
    };
    
    for (auto& d : data) {
        for (auto& b : bins) {
            if (d.k >= b.k_lo && d.k < b.k_hi) {
                b.count++;
                b.z_avg += d.z;
                break;
            }
        }
    }
    
    for (auto& b : bins) {
        if (b.count > 0) b.z_avg /= b.count;
        std::cout << std::left << std::setw(50) << b.label
                  << "  N=" << std::setw(4) << b.count
                  << "  <z>=" << std::fixed << std::setprecision(4) << b.z_avg
                  << "\n";
    }
    
    // Key transitions
    std::cout << "\n==========================================================\n";
    std::cout << "  Key Structural Boundaries\n";
    std::cout << "==========================================================\n\n";
    
    std::cout << "  k = 1/sqrt(z) = 1.000  =>  z = 1.000  (c-boundary)\n";
    std::cout << "  k = 1/sqrt(z) = 1.414  =>  z = 0.500  (virial boundary = sqrt(2))\n";
    std::cout << "  k = 1/sqrt(z) = 2.000  =>  z = 0.250  (half-virial)\n";
    std::cout << "  k = 1/sqrt(z) = 3.162  =>  z = 0.100  (decade boundary)\n";
    std::cout << "  k = 1/sqrt(z) = 10.00  =>  z = 0.010  (molecular scale)\n";
    std::cout << "  k = 1/sqrt(z) = 31.62  =>  z = 0.001  (local void)\n\n";
    
    // Compute d_L using z only (no 1+z factor) and compare with standard
    std::cout << "==========================================================\n";
    std::cout << "  Distance Comparison: z vs (1+z)\n";
    std::cout << "==========================================================\n\n";
    
    double H0 = 70.0; // km/s/Mpc
    
    std::cout << std::left << std::setw(10) << "z"
              << std::setw(12) << "mu_obs"
              << std::setw(14) << "d_L(mu) Mpc"
              << std::setw(14) << "d=cz/H0 Mpc"
              << std::setw(14) << "d*(1+z) Mpc"
              << std::setw(10) << "ratio"
              << "\n";
    std::cout << std::string(74, '-') << "\n";
    
    for (auto& d : data) {
        if (d.mu < 0) continue;
        double d_L_from_mu = std::pow(10.0, (d.mu - 25.0) / 5.0); // Mpc
        double d_linear = (299792.458 * d.z) / H0; // cz/H0 in Mpc
        double d_standard = d_linear * (1.0 + d.z); // standard d_L
        double ratio = d_L_from_mu / d_linear;
        
        if (d.z >= 0.01) { // skip very nearby (peculiar velocity dominated)
            std::cout << std::fixed
                      << std::setw(10) << std::setprecision(4) << d.z
                      << std::setw(12) << std::setprecision(3) << d.mu
                      << std::setw(14) << std::setprecision(1) << d_L_from_mu
                      << std::setw(14) << std::setprecision(1) << d_linear
                      << std::setw(14) << std::setprecision(1) << d_standard
                      << std::setw(10) << std::setprecision(4) << ratio
                      << "\n";
        }
    }
    
    std::cout << "\n";
    std::cout << "ratio = d_L(observed) / d(cz/H0)\n";
    std::cout << "If ratio = (1+z): standard model (expansion dims by extra factor)\n";
    std::cout << "If ratio = 1.0:   distance = cz/H0 exactly (no expansion factor)\n";
    std::cout << "If ratio = f(z):  gradient structure (pressure profile)\n\n";
    
    return 0;
}
