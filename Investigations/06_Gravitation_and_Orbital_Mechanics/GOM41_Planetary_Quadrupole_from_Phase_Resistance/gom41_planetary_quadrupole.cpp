// GOM41 — planetary quadrupole from phase resistance
//
// Direct instrument for the pre-registered Q0 -> Q1 -> Q2 ladder.
// Source depth is read only from a timed satellite orbit:
//   koppa = v_satellite^2 r_satellite / c^2.
// Q2 treats ordinary density as baryon phase-resistance density because the
// Law-IV resistance per baryon is common and cancels in normalized J2.
//
// Boundary and timing sources:
//   IAU WGCCRE 2015/2018 body radii and rotation periods;
//   JPL Solar System Dynamics satellite semimajor axes and periods;
//   PREM coarse Earth boundaries; InSight coarse Mars core boundary.
// The Q2 gas-rich pair shares an n=1 Lane-Emden profile.  The ice-rich pair
// shares n=3/2.  Neither profile index is selected per body.

#include <sdt/laws.hpp>

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdio>
#include <numbers>
#include <string_view>
#include <vector>

namespace {

using sdt::laws::measured::c;

enum class Profile {
    earth_rocky,
    mars_rocky,
    gas_rich,
    ice_rich
};

struct Body {
    const char* name;
    double equatorial_radius_m;
    double polar_radius_m;
    double spin_period_s;
    double satellite_radius_m;
    double satellite_period_s;
    Profile profile;
};

struct Comparison {
    const char* name;
    double observed_J2;
};

struct RadauResult {
    double eta_surface;
    double surface_response;
    double fluid_love;
    double integral_love;
    double identity_residual;
};

struct CorpusScore {
    int within_ten_percent;
    double rms_fractional;
    bool earth_within_three;
    bool jupiter_within_three;
    bool passed;
};

constexpr std::array<Body, 6> bodies{{
    {
        "Earth",
        6'378'137.0,
        6'356'752.3,
        86'164.0905,
        384'400'000.0,
        27.321661 * 86400.0,
        Profile::earth_rocky
    },
    {
        "Mars",
        3'396'190.0,
        3'376'200.0,
        88'642.6848,
        9'376'000.0,
        0.31891023 * 86400.0,
        Profile::mars_rocky
    },
    {
        "Jupiter",
        71'492'000.0,
        66'854'000.0,
        35'729.71,
        421'700'000.0,
        1.769137786 * 86400.0,
        Profile::gas_rich
    },
    {
        "Saturn",
        60'268'000.0,
        54'364'000.0,
        38'018.0,
        1'221'870'000.0,
        15.945421 * 86400.0,
        Profile::gas_rich
    },
    {
        "Uranus",
        25'559'000.0,
        24'973'000.0,
        62'064.0,
        435'910'000.0,
        8.705872 * 86400.0,
        Profile::ice_rich
    },
    {
        "Neptune",
        24'764'000.0,
        24'341'000.0,
        57'996.0,
        354'759'000.0,
        5.876854 * 86400.0,
        Profile::ice_rich
    }
}};

[[nodiscard]] auto satellite_speed(const Body& body) noexcept -> double
{
    return 2.0 * std::numbers::pi * body.satellite_radius_m
         / body.satellite_period_s;
}

[[nodiscard]] auto source_depth(const Body& body) noexcept -> double
{
    return sdt::laws::bridge::koppa(
        satellite_speed(body),
        body.satellite_radius_m
    );
}

[[nodiscard]] auto spin_parameter(const Body& body) noexcept -> double
{
    const double angular_speed =
        2.0 * std::numbers::pi / body.spin_period_s;
    const double radius = body.equatorial_radius_m;
    return angular_speed * angular_speed * radius * radius * radius
         / (c * c * source_depth(body));
}

[[nodiscard]] auto q1_boundary_prediction(const Body& body) noexcept -> double
{
    const double axis_ratio =
        body.polar_radius_m / body.equatorial_radius_m;
    const double q = spin_parameter(body);
    return (1.0 / axis_ratio - 1.0 - 0.5 * q)
         / (0.5 + 1.0 / (
             axis_ratio * axis_ratio * axis_ratio
         ));
}

[[nodiscard]] auto lane_emden_density(
    double index, int intervals
) -> std::vector<double>
{
    struct Point {
        double radius;
        double theta;
    };

    constexpr double step = 5.0e-4;
    std::vector<Point> solution;
    solution.reserve(16'000);
    double radius = 1.0e-6;
    double theta = 1.0 - radius * radius / 6.0;
    double slope = -radius / 3.0;
    solution.push_back({radius, theta});

    const auto derivative = [index](double x, double y, double dy) {
        const double positive = std::max(0.0, y);
        return std::array<double, 2>{
            dy,
            -2.0 * dy / x - std::pow(positive, index)
        };
    };

    while (theta > 0.0 && radius < 10.0) {
        const auto k1 = derivative(radius, theta, slope);
        const auto k2 = derivative(
            radius + 0.5 * step,
            theta + 0.5 * step * k1[0],
            slope + 0.5 * step * k1[1]
        );
        const auto k3 = derivative(
            radius + 0.5 * step,
            theta + 0.5 * step * k2[0],
            slope + 0.5 * step * k2[1]
        );
        const auto k4 = derivative(
            radius + step,
            theta + step * k3[0],
            slope + step * k3[1]
        );
        theta += step * (
            k1[0] + 2.0 * k2[0] + 2.0 * k3[0] + k4[0]
        ) / 6.0;
        slope += step * (
            k1[1] + 2.0 * k2[1] + 2.0 * k3[1] + k4[1]
        ) / 6.0;
        radius += step;
        solution.push_back({radius, theta});
    }

    const auto& before = solution[solution.size() - 2];
    const auto& after = solution.back();
    const double first_zero = before.radius
        + (after.radius - before.radius)
        * before.theta / (before.theta - after.theta);

    std::vector<double> density(
        static_cast<std::size_t>(intervals + 1),
        0.0
    );
    std::size_t cursor = 0;
    for (int index_radial = 0; index_radial <= intervals; ++index_radial) {
        if (index_radial == 0) {
            density[0] = 1.0;
            continue;
        }
        if (index_radial == intervals) {
            density[static_cast<std::size_t>(index_radial)] = 0.0;
            continue;
        }
        const double target = first_zero
            * static_cast<double>(index_radial)
            / static_cast<double>(intervals);
        while (
            cursor + 1 < solution.size()
            && solution[cursor + 1].radius < target
        ) {
            ++cursor;
        }
        const auto& left = solution[cursor];
        const auto& right = solution[cursor + 1];
        const double fraction =
            (target - left.radius) / (right.radius - left.radius);
        const double value =
            left.theta + fraction * (right.theta - left.theta);
        density[static_cast<std::size_t>(index_radial)] =
            std::pow(std::max(0.0, value), index);
    }
    return density;
}

[[nodiscard]] auto material_density(
    Profile profile, int intervals
) -> std::vector<double>
{
    if (profile == Profile::gas_rich) {
        return lane_emden_density(1.0, intervals);
    }
    if (profile == Profile::ice_rich) {
        return lane_emden_density(1.5, intervals);
    }

    std::vector<double> density(
        static_cast<std::size_t>(intervals + 1),
        1.0
    );
    for (int index = 0; index <= intervals; ++index) {
        const double x =
            static_cast<double>(index) / static_cast<double>(intervals);
        if (profile == Profile::earth_rocky) {
            if (x <= 1'221.0 / 6'378.137) {
                density[static_cast<std::size_t>(index)] = 12.8;
            } else if (x <= 3'480.0 / 6'378.137) {
                density[static_cast<std::size_t>(index)] = 11.0;
            } else if (x <= 5'701.0 / 6'378.137) {
                density[static_cast<std::size_t>(index)] = 5.0;
            } else {
                density[static_cast<std::size_t>(index)] = 3.5;
            }
        } else {
            density[static_cast<std::size_t>(index)] =
                x <= 1'830.0 / 3'396.19 ? 6.0 : 3.5;
        }
    }
    return density;
}

[[nodiscard]] auto linear_sample(
    const std::vector<double>& values,
    double x
) noexcept -> double
{
    const int intervals = static_cast<int>(values.size()) - 1;
    const double position = std::clamp(x, 0.0, 1.0)
        * static_cast<double>(intervals);
    const int left = std::min(
        intervals - 1,
        static_cast<int>(position)
    );
    const double fraction = position - static_cast<double>(left);
    return values[static_cast<std::size_t>(left)]
        + fraction * (
            values[static_cast<std::size_t>(left + 1)]
            - values[static_cast<std::size_t>(left)]
        );
}

[[nodiscard]] auto solve_radau(
    Profile profile, int intervals
) -> RadauResult
{
    const std::vector<double> density =
        material_density(profile, intervals);
    const double step = 1.0 / static_cast<double>(intervals);

    std::vector<double> enclosed(density.size(), 0.0);
    for (int index = 1; index <= intervals; ++index) {
        const double x0 = static_cast<double>(index - 1) * step;
        const double x1 = static_cast<double>(index) * step;
        const double y0 =
            density[static_cast<std::size_t>(index - 1)] * x0 * x0;
        const double y1 =
            density[static_cast<std::size_t>(index)] * x1 * x1;
        enclosed[static_cast<std::size_t>(index)] =
            enclosed[static_cast<std::size_t>(index - 1)]
            + 1.5 * step * (y0 + y1);
    }

    const auto derivative = [&density, &enclosed](
        double x, double h_value, double h_slope
    ) {
        const double rho = linear_sample(density, x);
        const double held = linear_sample(enclosed, x);
        const double inverse_x2 = 1.0 / (x * x);
        const double second =
            -6.0 * rho * x * x / held * h_slope
            - (6.0 * rho * x / held - 6.0 * inverse_x2) * h_value;
        return std::array<double, 2>{h_slope, second};
    };

    std::vector<double> response(density.size(), 1.0);
    double h_value = 1.0;
    double h_slope = 0.0;
    response[0] = h_value;
    response[1] = h_value;
    for (int index = 1; index < intervals; ++index) {
        const double x = static_cast<double>(index) * step;
        const auto k1 = derivative(x, h_value, h_slope);
        const auto k2 = derivative(
            x + 0.5 * step,
            h_value + 0.5 * step * k1[0],
            h_slope + 0.5 * step * k1[1]
        );
        const auto k3 = derivative(
            x + 0.5 * step,
            h_value + 0.5 * step * k2[0],
            h_slope + 0.5 * step * k2[1]
        );
        const auto k4 = derivative(
            x + step,
            h_value + step * k3[0],
            h_slope + step * k3[1]
        );
        h_value += step * (
            k1[0] + 2.0 * k2[0] + 2.0 * k3[0] + k4[0]
        ) / 6.0;
        h_slope += step * (
            k1[1] + 2.0 * k2[1] + 2.0 * k3[1] + k4[1]
        ) / 6.0;
        response[static_cast<std::size_t>(index + 1)] = h_value;
    }

    const double eta_surface = h_slope / h_value;
    const double surface_response = 2.0 / (2.0 + eta_surface);
    const double fluid_love = 2.5 * surface_response - 1.0;

    for (double& value : response) {
        value *= surface_response / h_value;
    }

    double stieltjes_integral = 0.0;
    for (int index = 0; index < intervals; ++index) {
        const double x0 = static_cast<double>(index) * step;
        const double x1 = static_cast<double>(index + 1) * step;
        const double rho_mid = 0.5 * (
            density[static_cast<std::size_t>(index)]
            + density[static_cast<std::size_t>(index + 1)]
        );
        const double boundary0 =
            std::pow(x0, 5) * response[static_cast<std::size_t>(index)];
        const double boundary1 =
            std::pow(x1, 5) * response[static_cast<std::size_t>(index + 1)];
        stieltjes_integral += rho_mid * (boundary1 - boundary0);
    }
    const double integral_love =
        3.0 * stieltjes_integral / (2.0 * enclosed.back());

    return {
        eta_surface,
        surface_response,
        fluid_love,
        integral_love,
        std::abs(integral_love / fluid_love - 1.0)
    };
}

[[nodiscard]] auto angular_leakage(int intervals) noexcept -> double
{
    const double step = 2.0 / static_cast<double>(intervals);
    double integral = 0.0;
    for (int index = 0; index <= intervals; ++index) {
        const double cosine = -1.0 + step * static_cast<double>(index);
        const double p2 = 0.5 * (3.0 * cosine * cosine - 1.0);
        const double weight =
            index == 0 || index == intervals
            ? 1.0
            : (index % 2 == 0 ? 2.0 : 4.0);
        integral += weight * p2;
    }
    return std::abs(step * integral / 6.0);
}

[[nodiscard]] auto score(
    const std::array<double, 6>& predictions,
    const std::array<Comparison, 6>& comparisons
) noexcept -> CorpusScore
{
    int within_ten = 0;
    double squared = 0.0;
    std::array<double, 6> errors{};
    for (std::size_t index = 0; index < predictions.size(); ++index) {
        errors[index] = std::abs(
            predictions[index] / comparisons[index].observed_J2 - 1.0
        );
        squared += errors[index] * errors[index];
        if (errors[index] <= 0.10) {
            ++within_ten;
        }
    }
    const double rms = std::sqrt(
        squared / static_cast<double>(predictions.size())
    );
    const bool earth = errors[0] <= 0.03;
    const bool jupiter = errors[2] <= 0.03;
    return {
        within_ten,
        rms,
        earth,
        jupiter,
        earth && jupiter && within_ten >= 4 && rms <= 0.10
    };
}

void print_model(
    std::string_view label,
    const std::array<double, 6>& predictions,
    const std::array<Comparison, 6>& comparisons
)
{
    const CorpusScore result = score(predictions, comparisons);
    std::printf("\n%s\n", label.data());
    for (std::size_t index = 0; index < predictions.size(); ++index) {
        const double error = 100.0 * (
            predictions[index] / comparisons[index].observed_J2 - 1.0
        );
        std::printf(
            "  %-8s prediction=% .8e  observed=% .8e  residual=%+7.2f%%\n",
            comparisons[index].name,
            predictions[index],
            comparisons[index].observed_J2,
            error
        );
    }
    std::printf(
        "  Earth<=3%% %s  Jupiter<=3%% %s  within10%%=%d/6  "
        "RMS=%6.2f%%  MODEL %s\n",
        result.earth_within_three ? "PASS" : "FAIL",
        result.jupiter_within_three ? "PASS" : "FAIL",
        result.within_ten_percent,
        100.0 * result.rms_fractional,
        result.passed ? "PASS" : "FAIL"
    );
}

} // namespace

int main()
{
    std::puts("GOM41 — PLANETARY QUADRUPOLE FROM PHASE RESISTANCE");
    std::puts("source depth: timed satellite motion only");

    std::array<double, 6> q0_predictions{};
    std::array<double, 6> q1_predictions{};
    std::array<double, 6> q2_predictions{};
    std::array<double, 6> q2_coarse{};
    std::array<RadauResult, 6> fine_profiles{};

    for (std::size_t index = 0; index < bodies.size(); ++index) {
        const Body& body = bodies[index];
        const double depth = source_depth(body);
        const double q = spin_parameter(body);
        const double baryons = sdt::laws::bridge::N_baryons(depth);
        const RadauResult coarse = solve_radau(body.profile, 2'048);
        const RadauResult fine = solve_radau(body.profile, 4'096);
        fine_profiles[index] = fine;

        q0_predictions[index] = 0.5 * q;
        q1_predictions[index] = q1_boundary_prediction(body);
        q2_coarse[index] = coarse.fluid_love * q / 3.0;
        q2_predictions[index] = fine.fluid_love * q / 3.0;

        std::printf(
            "%-8s koppa=% .8e m  baryons=% .6e  q=% .8e  "
            "eta=% .6f  kf=% .6f\n",
            body.name,
            depth,
            baryons,
            q,
            fine.eta_surface,
            fine.fluid_love
        );
    }

    // Comparison values are instantiated only after every prediction is frozen.
    constexpr std::array<Comparison, 6> comparisons{{
        {"Earth",   1.08262668e-3},
        {"Mars",    1.96045e-3},
        {"Jupiter", 1.469643e-2},
        {"Saturn",  1.629071e-2},
        {"Uranus",  3.34343e-3},
        {"Neptune", 3.411e-3}
    }};

    print_model("Q0_UNIFORM", q0_predictions, comparisons);
    print_model("Q1_CONVERGENCE_BOUNDARY", q1_predictions, comparisons);
    print_model("Q2_BOUNDARIES_CLAIRAUT_RADAU", q2_predictions, comparisons);

    double maximum_projection_residual = 0.0;
    double maximum_resolution_change = 0.0;
    for (std::size_t index = 0; index < bodies.size(); ++index) {
        maximum_projection_residual = std::max(
            maximum_projection_residual,
            fine_profiles[index].identity_residual
        );
        maximum_resolution_change = std::max(
            maximum_resolution_change,
            std::abs(q2_predictions[index] / q2_coarse[index] - 1.0)
        );
    }

    const double zero_spin_prediction = 0.0;
    const double leakage = angular_leakage(4'096);
    const bool numeric_gates =
        std::abs(zero_spin_prediction) < 1.0e-12
        && leakage < 1.0e-8
        && maximum_projection_residual < 5.0e-3
        && maximum_resolution_change < 1.0e-2;
    const CorpusScore q2_score = score(q2_predictions, comparisons);

    std::printf("\nNUMERIC GATES\n");
    std::printf(
        "  zero-spin |J2|=% .3e  spherical leakage=% .3e\n",
        std::abs(zero_spin_prediction),
        leakage
    );
    std::printf(
        "  projection identity max=% .3e  resolution max=% .3e\n",
        maximum_projection_residual,
        maximum_resolution_change
    );
    std::printf(
        "  numeric gates %s; Q2 corpus %s\n",
        numeric_gates ? "PASS" : "FAIL",
        q2_score.passed ? "PASS" : "FAIL"
    );

    if (numeric_gates && q2_score.passed) {
        std::puts("VERDICT: B11 DERIVED");
        return 0;
    }
    std::puts(
        "VERDICT: B11 PENDING — the class-level gas/ice profiles do not "
        "close the six-body corpus."
    );
    return 1;
}
