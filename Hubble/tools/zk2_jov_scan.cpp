#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <iomanip>

int main() {
    double c = 2.99792458e8;
    double R = 6.9911e7;  // Jupiter vol mean
    double GM = 1.26687e17;
    double z = GM / (R * c * c);
    double k = 1.0 / std::sqrt(z);
    double v = c / k;
    double T = 2.0 * M_PI * R / v;  // T_surface in SI seconds
    double Jd = 35730.0;             // Jupiter sidereal day in SI seconds

    std::cout << "T_surf(Jup) = " << std::fixed << std::setprecision(4) << T << " SI s\n";
    std::cout << "J_day       = " << Jd << " SI s\n";
    std::cout << "k           = " << std::setprecision(2) << k << "\n";
    std::cout << "z           = " << std::scientific << std::setprecision(6) << z << "\n\n";

    // What N makes T = N^2 ticks where tick = Jday/D for integer D?
    std::cout << "Scanning: what division D of Jupiter's day gives T = N^2 ticks?\n";
    std::cout << "tick = J_day / D,  T_in_ticks = T / tick = T * D / J_day\n\n";

    std::cout << std::left << std::setw(8) << "D"
              << std::right << std::setw(14) << "T_in_ticks"
              << std::setw(10) << "sqrt"
              << std::setw(12) << "nearest_N"
              << std::setw(10) << "err%"
              << std::setw(14) << "tick(SI_s)"
              << "\n";
    std::cout << std::string(68, '-') << "\n";

    // Try every D from 1000 to 100000
    for (int D = 1000; D <= 100000; D++) {
        double ticks = T * D / Jd;
        double sq = std::sqrt(ticks);
        int N = (int)std::round(sq);
        double pred = (double)N * N;
        double err = std::abs(ticks - pred) / pred * 100.0;
        if (err < 0.01) {  // within 0.01%
            double tick_si = Jd / D;
            std::cout << std::left << std::setw(8) << D
                      << std::right << std::fixed << std::setprecision(2) << std::setw(14) << ticks
                      << std::setprecision(4) << std::setw(10) << sq
                      << std::setw(12) << N
                      << std::setprecision(4) << std::setw(10) << err
                      << std::setprecision(6) << std::setw(14) << tick_si
                      << "\n";
        }
    }

    return 0;
}
