#include <sdt/materials.hpp>

#include <algorithm>
#include <cmath>
#include <cstdio>

namespace {

constexpr double lithium_density = 534.0;
constexpr double uranium_density = 19'100.0;
constexpr double lithium_A = 7.0;
constexpr double uranium_A = 238.0;

[[nodiscard]] auto relative_error(double value, double expected) -> double {
    return std::abs(value / expected - 1.0);
}

void gate(
    const char* id,
    const char* name,
    double value,
    double expected,
    double tolerance,
    bool& all_passed
) {
    const double error = relative_error(value, expected);
    const bool passed = error <= tolerance;
    std::printf(
        "%s  %-37s value=% .9e  expected=% .9e  rel=% .3e  %s\n",
        id,
        name,
        value,
        expected,
        error,
        passed ? "PASS" : "FAIL"
    );
    all_passed = all_passed && passed;
}

} // namespace

int main()
{
    using namespace sdt::materials;

    constexpr double tolerance = 1.0e-12;
    constexpr double equal_resistance_kg = 1.0;
    constexpr double equal_radius_m = 0.05;
    constexpr double observation_m = 10.0;
    constexpr double angular_rate = 1.0;

    bool all_passed = true;
    const double density_ratio = uranium_density / lithium_density;

    const auto li_equal_mass =
        state_from_total_resistance(equal_resistance_kg, lithium_density);
    const auto u_equal_mass =
        state_from_total_resistance(equal_resistance_kg, uranium_density);
    const auto li_equal_size =
        state_from_bulk_density(lithium_density, equal_radius_m);
    const auto u_equal_size =
        state_from_bulk_density(uranium_density, equal_radius_m);

    std::puts("CM08 — Material Koppa Density, Helical Wake and Flux Controls");
    std::puts("COMPUTED CONTROLS · densities are measured investigation inputs\n");

    std::puts("Equal total resistance: 1.000 kg");
    std::printf(
        "  Li  radius=%.9e m  n_b=%.9e m^-3  koppa=%.9e m  "
        "a_surface=%.9e m/s^2  a_10m=%.9e m/s^2\n",
        li_equal_mass.radius_m,
        li_equal_mass.baryon_density_m3,
        li_equal_mass.koppa_total_m,
        surface_acceleration(li_equal_mass),
        far_acceleration(li_equal_mass, observation_m)
    );
    std::printf(
        "  U   radius=%.9e m  n_b=%.9e m^-3  koppa=%.9e m  "
        "a_surface=%.9e m/s^2  a_10m=%.9e m/s^2\n\n",
        u_equal_mass.radius_m,
        u_equal_mass.baryon_density_m3,
        u_equal_mass.koppa_total_m,
        surface_acceleration(u_equal_mass),
        far_acceleration(u_equal_mass, observation_m)
    );

    gate(
        "C0a",
        "equal-mass total koppa ratio",
        u_equal_mass.koppa_total_m / li_equal_mass.koppa_total_m,
        1.0,
        tolerance,
        all_passed
    );
    gate(
        "C0b",
        "equal-mass far acceleration ratio",
        far_acceleration(u_equal_mass, observation_m)
            / far_acceleration(li_equal_mass, observation_m),
        1.0,
        tolerance,
        all_passed
    );
    gate(
        "C1",
        "equal-mass baryon-density ratio",
        u_equal_mass.baryon_density_m3
            / li_equal_mass.baryon_density_m3,
        density_ratio,
        tolerance,
        all_passed
    );

    std::puts("\nEqual radius: 0.050 m");
    std::printf(
        "  Li  resistance=%.9e kg  baryons=%.9e  koppa=%.9e m  "
        "a_10m=%.9e m/s^2\n",
        lithium_density * li_equal_size.volume_m3,
        li_equal_size.baryon_count,
        li_equal_size.koppa_total_m,
        far_acceleration(li_equal_size, observation_m)
    );
    std::printf(
        "  U   resistance=%.9e kg  baryons=%.9e  koppa=%.9e m  "
        "a_10m=%.9e m/s^2\n\n",
        uranium_density * u_equal_size.volume_m3,
        u_equal_size.baryon_count,
        u_equal_size.koppa_total_m,
        far_acceleration(u_equal_size, observation_m)
    );

    gate(
        "C2a",
        "equal-size total koppa ratio",
        u_equal_size.koppa_total_m / li_equal_size.koppa_total_m,
        density_ratio,
        tolerance,
        all_passed
    );
    gate(
        "C2b",
        "equal-size far acceleration ratio",
        far_acceleration(u_equal_size, observation_m)
            / far_acceleration(li_equal_size, observation_m),
        density_ratio,
        tolerance,
        all_passed
    );

    const double expected_surface_ratio =
        li_equal_mass.radius_m * li_equal_mass.radius_m
        / (u_equal_mass.radius_m * u_equal_mass.radius_m);
    gate(
        "C3",
        "equal-mass surface response ratio",
        surface_acceleration(u_equal_mass)
            / surface_acceleration(li_equal_mass),
        expected_surface_ratio,
        tolerance,
        all_passed
    );

    const auto wake_near = normalised_helical_wake(
        u_equal_size,
        1.0,
        0.4,
        0.2,
        0.1,
        0.5,
        angular_rate,
        3,
        1.0
    );
    const auto wake_far = normalised_helical_wake(
        u_equal_size,
        2.0,
        0.4,
        0.2,
        0.1,
        0.5,
        angular_rate,
        3,
        1.0
    );
    gate(
        "C4",
        "r^-3 wake ratio A(r)/A(2r)",
        wake_near.magnitude_ms2 / wake_far.magnitude_ms2,
        8.0,
        tolerance,
        all_passed
    );

    const double li_flux_mass = atom_loop_flux_control(
        li_equal_mass,
        lithium_A,
        1.0,
        1.0,
        angular_rate
    );
    const double u_flux_mass = atom_loop_flux_control(
        u_equal_mass,
        uranium_A,
        1.0,
        1.0,
        angular_rate
    );
    const double li_flux_size = atom_loop_flux_control(
        li_equal_size,
        lithium_A,
        1.0,
        1.0,
        angular_rate
    );
    const double u_flux_size = atom_loop_flux_control(
        u_equal_size,
        uranium_A,
        1.0,
        1.0,
        angular_rate
    );
    const double expected_equal_mass_flux_ratio =
        (lithium_A / uranium_A)
        * (u_equal_mass.radius_m / li_equal_mass.radius_m);
    const double expected_equal_size_flux_ratio =
        (
            u_equal_size.baryon_count / uranium_A
        ) / (
            li_equal_size.baryon_count / lithium_A
        );
    gate(
        "C5a",
        "equal-mass loop-flux control ratio",
        u_flux_mass / li_flux_mass,
        expected_equal_mass_flux_ratio,
        tolerance,
        all_passed
    );
    gate(
        "C5b",
        "equal-size loop-flux control ratio",
        u_flux_size / li_flux_size,
        expected_equal_size_flux_ratio,
        tolerance,
        all_passed
    );

    const auto zero_wake = normalised_helical_wake(
        u_equal_size,
        1.0,
        0.4,
        0.2,
        0.1,
        0.5,
        angular_rate,
        3,
        0.0
    );
    const double zero_flux = atom_loop_flux_control(
        u_equal_size,
        uranium_A,
        1.0,
        0.0,
        angular_rate
    );
    const bool c6 =
        zero_wake.magnitude_ms2 == 0.0
        && zero_flux == 0.0
        && u_equal_size.koppa_total_m > 0.0
        && u_equal_size.baryon_density_m3 > 0.0
        && far_acceleration(u_equal_size, observation_m) > 0.0;
    std::printf(
        "C6   %-37s wake=%g  flux=%g  monopole=%g  %s\n",
        "zero-alignment ledger separation",
        zero_wake.magnitude_ms2,
        zero_flux,
        far_acceleration(u_equal_size, observation_m),
        c6 ? "PASS" : "FAIL"
    );
    all_passed = all_passed && c6;

    std::printf(
        "\nFlux controls at omega=1 rad/s, full declared alignment:\n"
        "  equal mass  Li=% .9e Wb  U=% .9e Wb\n"
        "  equal size  Li=% .9e Wb  U=% .9e Wb\n",
        li_flux_mass,
        u_flux_mass,
        li_flux_size,
        u_flux_size
    );
    std::puts(
        "These flux values are count controls, not predictions of bulk "
        "lithium or uranium magnetism."
    );

    std::printf(
        "\nASSESSMENT: %s\n",
        all_passed ? "VALIDATED MATERIAL LEDGER" : "REJECTED"
    );
    return all_passed ? 0 : 1;
}
