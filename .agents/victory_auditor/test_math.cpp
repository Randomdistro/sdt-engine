#include <iostream>
#include <cmath>
#include <iomanip>

int main() {
    constexpr double a = 5.790905e10; 
    constexpr double e = 0.205630;    
    constexpr double delta_phi = 5.0186e-7; 
    constexpr double v_sun = 436824.28; 
    
    double r_sun = 6.957e8; // sdt::laws::measured::R_Sun
    double actual_c = 299792458.0; // sdt::laws::measured::c
    
    constexpr double pi = 3.14159265358979323846;
    double numerator = 6.0 * pi * r_sun;
    double denominator = delta_phi * a * (1.0 - (e * e));
    
    double derived_c = v_sun * std::sqrt(numerator / denominator);
    double error_percent = std::abs(derived_c - actual_c) / actual_c * 100.0;
    
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Derived speed of light (c) from Mercury's precession: " << derived_c << " m/s\n";
    std::cout << "Standard speed of light (c): " << actual_c << " m/s\n";
    std::cout << "Percentage error: " << error_percent << " %\n";
    return 0;
}
