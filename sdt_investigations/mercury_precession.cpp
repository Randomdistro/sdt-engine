#include <iostream>
#include <cmath>
#include <iomanip>
#include <numbers>
#include <sdt/laws.hpp>

int main() {
    // Standard parameters for Mercury and the Sun
    constexpr double a = 5.790905e10; // Semi-major axis in meters
    constexpr double e = 0.205630;    // Eccentricity
    constexpr double delta_phi = 5.0186e-7; // Anomalous precession in rad/orbit
    
    // The surface orbital velocity (v) is related to escape velocity (v_esc = sqrt(2)*v).
    // The Sun's escape velocity is ~617.7 km/s, so v_Sun is ~436,824 m/s.
    constexpr double v_sun = 436824.28; // Sun's surface orbital velocity in m/s
    
    // Sun's radius from SDT observables
    double r_sun = sdt::laws::measured::R_Sun;
    
    // Standard speed of light from SDT observables
    double actual_c = sdt::laws::measured::c;
    
    // Formula calculation: c = v_Sun * sqrt((6 * pi * R_Sun) / (delta_phi * a * (1 - e^2)))
    double pi = std::numbers::pi;
    double numerator = 6.0 * pi * r_sun;
    double denominator = delta_phi * a * (1.0 - (e * e));
    
    double derived_c = v_sun * std::sqrt(numerator / denominator);
    
    // Percentage error calculation
    double error_percent = std::abs(derived_c - actual_c) / actual_c * 100.0;
    
    // Output results
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Derived speed of light (c) from Mercury's precession: " << derived_c << " m/s\n";
    std::cout << "Standard speed of light (c): " << actual_c << " m/s\n";
    std::cout << "Percentage error: " << error_percent << " %\n";
    
    return 0;
}
