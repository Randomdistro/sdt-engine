// Build with C++20 and /I Engine/include (or a packaged sdt include directory).
#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>

int main() {
    using namespace sdt::laws;
    // Measured boundary 0.8414 fm / four trefoil seats = 0.21035 fm.
    // This gate distinguishes the measured wake from the old Compton substitution.
    if (std::abs(bridge::proton_wake / 2.1035e-16 - 1.0) > 1e-14) return 1;
    if constexpr (!(bridge::koppa_per_baryon > 1.24187e-54
          && bridge::koppa_per_baryon < 1.24188e-54)) return 2;
    const double recovered = std::sqrt(
        bridge::koppa_per_baryon * bridge::proton_wake);
    if (std::abs(recovered / measured::l_P - 1.0) > 1e-14) return 3;
    // The downstream census must use the repaired quantum.
    if (std::abs(bridge::N_baryons(7.0 * bridge::koppa_per_baryon) - 7.0)
        > 1e-13) return 4;
    std::printf("PASS: wake=%.12e m; baryon koppa=%.12e m; closure=%.12e m\n",
        bridge::proton_wake, bridge::koppa_per_baryon, recovered);
}
