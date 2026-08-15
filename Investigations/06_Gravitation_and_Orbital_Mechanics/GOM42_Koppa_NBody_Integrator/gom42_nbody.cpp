#include <sdt/dynamics.hpp>

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdio>
#include <numbers>
#include <vector>

namespace {

using sdt::dynamics::Body;
using sdt::dynamics::Invariants;
using sdt::dynamics::StepStatus;
using sdt::dynamics::Vec3;

struct Drift {
    double separation{};
    double energy{};
    double barycentre{};
    double momentum{};
    double angular_momentum{};
    bool advanced{true};
};

[[nodiscard]] auto relative_change(double value, double reference) -> double {
    return reference == 0.0
        ? std::abs(value)
        : std::abs(value / reference - 1.0);
}

[[nodiscard]] auto momentum_scale(const std::vector<Body>& bodies) -> double {
    double scale = 0.0;
    for (const auto& body : bodies) {
        scale += body.koppa_m * sdt::dynamics::norm(body.velocity);
    }
    return scale;
}

[[nodiscard]] auto angular_scale(const std::vector<Body>& bodies) -> double {
    double scale = 0.0;
    for (const auto& body : bodies) {
        scale += body.koppa_m * sdt::dynamics::norm(
            sdt::dynamics::cross(body.position, body.velocity)
        );
    }
    return scale;
}

[[nodiscard]] auto maximum_pair_error(
    const std::vector<Body>& bodies,
    double reference
) -> double {
    double result = 0.0;
    for (std::size_t i = 0; i < bodies.size(); ++i) {
        for (std::size_t j = i + 1; j < bodies.size(); ++j) {
            result = std::max(
                result,
                relative_change(
                    sdt::dynamics::norm(
                        bodies[j].position - bodies[i].position
                    ),
                    reference
                )
            );
        }
    }
    return result;
}

[[nodiscard]] auto run_fixed(
    std::vector<Body>& bodies,
    double dt,
    int steps,
    double reference_separation
) -> Drift {
    const Invariants initial = sdt::dynamics::invariants(bodies);
    const double p_scale = momentum_scale(bodies);
    const double l_scale = angular_scale(bodies);

    Drift drift{};
    for (int n = 0; n < steps; ++n) {
        if (sdt::dynamics::step(bodies, dt) != StepStatus::advanced) {
            drift.advanced = false;
            break;
        }
        const auto current = sdt::dynamics::invariants(bodies);
        drift.separation = std::max(
            drift.separation,
            maximum_pair_error(bodies, reference_separation)
        );
        drift.energy = std::max(
            drift.energy,
            relative_change(current.energy, initial.energy)
        );
        drift.barycentre = std::max(
            drift.barycentre,
            sdt::dynamics::norm(current.barycentre - initial.barycentre)
                / reference_separation
        );
        drift.momentum = std::max(
            drift.momentum,
            sdt::dynamics::norm(current.momentum - initial.momentum)
                / p_scale
        );
        drift.angular_momentum = std::max(
            drift.angular_momentum,
            sdt::dynamics::norm(
                current.angular_momentum - initial.angular_momentum
            ) / l_scale
        );
    }
    return drift;
}

[[nodiscard]] auto final_state_error(
    int steps,
    double period,
    double separation,
    double koppa_1,
    double koppa_2
) -> double {
    auto bodies =
        sdt::dynamics::circular_pair(koppa_1, koppa_2, separation);
    const auto initial = bodies;
    const double velocity_scale = std::max(
        sdt::dynamics::norm(initial[0].velocity),
        sdt::dynamics::norm(initial[1].velocity)
    );
    for (int i = 0; i < steps; ++i) {
        if (
            sdt::dynamics::step(bodies, period / steps)
            != StepStatus::advanced
        ) {
            return 1.0;
        }
    }

    double position_sum = 0.0;
    double velocity_sum = 0.0;
    for (std::size_t i = 0; i < bodies.size(); ++i) {
        const Vec3 dp = bodies[i].position - initial[i].position;
        const Vec3 dv = bodies[i].velocity - initial[i].velocity;
        position_sum += sdt::dynamics::dot(dp, dp);
        velocity_sum += sdt::dynamics::dot(dv, dv);
    }
    const double position_rms =
        std::sqrt(position_sum / bodies.size()) / separation;
    const double velocity_rms =
        std::sqrt(velocity_sum / bodies.size()) / velocity_scale;
    return std::hypot(position_rms, velocity_rms);
}

void print_gate(
    const char* id,
    const char* name,
    double value,
    const char* relation,
    double limit,
    bool passed
) {
    std::printf(
        "%s  %-34s value=% .9e  gate %s %.3e  %s\n",
        id,
        name,
        value,
        relation,
        limit,
        passed ? "PASS" : "FAIL"
    );
}

} // namespace

int main()
{
    using sdt::laws::measured::c;

    bool all_passed = true;
    double maximum_momentum_drift = 0.0;
    double maximum_angular_drift = 0.0;

    std::puts("GOM42 — Koppa N-Body Integrator");
    std::puts("VALIDATION · no G · no M · no GM · no softening\n");

    // V0 — pair symmetry and inverse-square scaling.
    std::vector<Body> pair{
        {{0.0, 0.0, 0.0}, {}, 2.0e-3, 0.0},
        {{1.0e9, 0.0, 0.0}, {}, 3.0e-3, 0.0}
    };
    std::vector<Vec3> acceleration;
    const auto pair_status = sdt::dynamics::accelerations(pair, acceleration);
    const Vec3 weighted_residual =
        acceleration[0] * pair[0].koppa_m
        + acceleration[1] * pair[1].koppa_m;
    const double symmetry_scale =
        pair[0].koppa_m * sdt::dynamics::norm(acceleration[0]);
    const double symmetry_error =
        sdt::dynamics::norm(weighted_residual) / symmetry_scale;

    pair[1].position.x = 2.0e9;
    std::vector<Vec3> acceleration_2r;
    const auto pair_2r_status =
        sdt::dynamics::accelerations(pair, acceleration_2r);
    const double inverse_square_error = std::abs(
        sdt::dynamics::norm(acceleration[0])
            / sdt::dynamics::norm(acceleration_2r[0])
        - 4.0
    );
    const bool v0 =
        pair_status == StepStatus::advanced
        && pair_2r_status == StepStatus::advanced
        && symmetry_error <= 1.0e-14
        && inverse_square_error <= 1.0e-14;
    print_gate("V0a", "pair weighted symmetry", symmetry_error, "<=", 1.0e-14, v0);
    print_gate(
        "V0b",
        "inverse-square residual",
        inverse_square_error,
        "<=",
        1.0e-14,
        v0
    );
    all_passed = all_passed && v0;

    // V1/V2 — circular two-body limit and timestep convergence.
    constexpr double separation = 1.0e9;
    constexpr double koppa_1 = 1.0e-3;
    constexpr double koppa_2 = 2.0e-3;
    const double period =
        2.0 * std::numbers::pi
        * std::sqrt(
            separation * separation * separation
            / (c * c * (koppa_1 + koppa_2))
        );
    auto circular =
        sdt::dynamics::circular_pair(koppa_1, koppa_2, separation);
    const Drift circular_drift = run_fixed(
        circular,
        period / 2000.0,
        100 * 2000,
        separation
    );
    const bool v1 =
        circular_drift.advanced
        && circular_drift.separation <= 5.0e-5
        && circular_drift.energy <= 5.0e-6;
    print_gate(
        "V1a",
        "two-body separation drift",
        circular_drift.separation,
        "<=",
        5.0e-5,
        v1
    );
    print_gate(
        "V1b",
        "two-body energy drift",
        circular_drift.energy,
        "<=",
        5.0e-6,
        v1
    );
    all_passed = all_passed && v1;

    const double coarse_error =
        final_state_error(500, period, separation, koppa_1, koppa_2);
    const double fine_error =
        final_state_error(1000, period, separation, koppa_1, koppa_2);
    const double convergence_ratio = coarse_error / fine_error;
    const bool v2 = convergence_ratio >= 3.5;
    print_gate(
        "V2",
        "Verlet convergence ratio",
        convergence_ratio,
        ">=",
        3.5,
        v2
    );
    all_passed = all_passed && v2;

    maximum_momentum_drift = std::max(
        maximum_momentum_drift,
        circular_drift.momentum
    );
    maximum_angular_drift = std::max(
        maximum_angular_drift,
        circular_drift.angular_momentum
    );

    // V3 — Lagrange equilateral solution.
    constexpr double triangle_side = 1.5e9;
    constexpr double triangle_koppa_1 = 2.5e-3;
    constexpr double triangle_koppa_2 = 2.5e-6;
    constexpr double triangle_koppa_3 = 2.5e-9;
    constexpr double triangle_total_koppa =
        triangle_koppa_1 + triangle_koppa_2 + triangle_koppa_3;
    const double triangle_omega =
        c * std::sqrt(
            triangle_total_koppa
            / (triangle_side * triangle_side * triangle_side)
        );
    const double triangle_period =
        2.0 * std::numbers::pi / triangle_omega;
    auto triangle = sdt::dynamics::equilateral_three(
        triangle_koppa_1,
        triangle_koppa_2,
        triangle_koppa_3,
        triangle_side
    );
    const Drift triangle_drift = run_fixed(
        triangle,
        triangle_period / 4000.0,
        20 * 4000,
        triangle_side
    );
    const bool v3 =
        triangle_drift.advanced
        && triangle_drift.separation <= 1.0e-4
        && triangle_drift.barycentre <= 1.0e-10;
    print_gate(
        "V3a",
        "equilateral side drift",
        triangle_drift.separation,
        "<=",
        1.0e-4,
        v3
    );
    print_gate(
        "V3b",
        "equilateral barycentre drift",
        triangle_drift.barycentre,
        "<=",
        1.0e-10,
        v3
    );
    all_passed = all_passed && v3;

    maximum_momentum_drift = std::max(
        maximum_momentum_drift,
        triangle_drift.momentum
    );
    maximum_angular_drift = std::max(
        maximum_angular_drift,
        triangle_drift.angular_momentum
    );

    // V4 — figure-eight choreography, Moore/Chenciner-Montgomery state.
    constexpr double length_scale = 1.0e9;
    constexpr double figure_koppa = 1.0e-3;
    const double time_scale =
        std::sqrt(
            length_scale * length_scale * length_scale
            / (c * c * figure_koppa)
        );
    const double velocity_scale = length_scale / time_scale;
    const double figure_period = 6.32591398 * time_scale;
    std::vector<Body> figure{
        {
            {-0.97000436 * length_scale, 0.24308753 * length_scale, 0.0},
            {0.466203685 * velocity_scale, 0.432365730 * velocity_scale, 0.0},
            figure_koppa,
            0.0
        },
        {
            {0.97000436 * length_scale, -0.24308753 * length_scale, 0.0},
            {0.466203685 * velocity_scale, 0.432365730 * velocity_scale, 0.0},
            figure_koppa,
            0.0
        },
        {
            {0.0, 0.0, 0.0},
            {-0.932407370 * velocity_scale, -0.864731460 * velocity_scale, 0.0},
            figure_koppa,
            0.0
        }
    };
    const auto figure_initial = figure;
    const Drift figure_drift = run_fixed(
        figure,
        figure_period / 50000.0,
        50000,
        length_scale
    );

    double figure_position_sum = 0.0;
    double figure_velocity_sum = 0.0;
    for (std::size_t i = 0; i < figure.size(); ++i) {
        const Vec3 dp = figure[i].position - figure_initial[i].position;
        const Vec3 dv = figure[i].velocity - figure_initial[i].velocity;
        figure_position_sum += sdt::dynamics::dot(dp, dp);
        figure_velocity_sum += sdt::dynamics::dot(dv, dv);
    }
    const double figure_position_error =
        std::sqrt(figure_position_sum / 3.0) / length_scale;
    const double figure_velocity_error =
        std::sqrt(figure_velocity_sum / 3.0) / velocity_scale;
    const bool v4 =
        figure_drift.advanced
        && figure_position_error <= 2.0e-5
        && figure_velocity_error <= 2.0e-5;
    print_gate(
        "V4a",
        "figure-eight position closure",
        figure_position_error,
        "<=",
        2.0e-5,
        v4
    );
    print_gate(
        "V4b",
        "figure-eight velocity closure",
        figure_velocity_error,
        "<=",
        2.0e-5,
        v4
    );
    all_passed = all_passed && v4;

    maximum_momentum_drift = std::max(
        maximum_momentum_drift,
        figure_drift.momentum
    );
    maximum_angular_drift = std::max(
        maximum_angular_drift,
        figure_drift.angular_momentum
    );

    const bool v5 =
        maximum_momentum_drift <= 1.0e-11
        && maximum_angular_drift <= 1.0e-10;
    print_gate(
        "V5a",
        "maximum momentum drift",
        maximum_momentum_drift,
        "<=",
        1.0e-11,
        v5
    );
    print_gate(
        "V5b",
        "maximum angular drift",
        maximum_angular_drift,
        "<=",
        1.0e-10,
        v5
    );
    all_passed = all_passed && v5;

    // V6 — collision boundary stops the step without committing overlap.
    std::vector<Body> collision{
        {{-1.0e6, 0.0, 0.0}, {1.0e4, 0.0, 0.0}, 1.0e-6, 1.0e5},
        {{ 1.0e6, 0.0, 0.0}, {-1.0e4, 0.0, 0.0}, 1.0e-6, 1.0e5}
    };
    StepStatus collision_status = StepStatus::advanced;
    for (int i = 0; i < 1000 && collision_status == StepStatus::advanced; ++i) {
        collision_status = sdt::dynamics::step(collision, 1.0);
    }
    const double stopped_separation =
        sdt::dynamics::norm(collision[1].position - collision[0].position);
    const double contact =
        collision[0].collision_radius_m + collision[1].collision_radius_m;
    const bool v6 =
        collision_status == StepStatus::collision
        && stopped_separation > contact;
    print_gate(
        "V6",
        "collision stop margin [m]",
        stopped_separation - contact,
        ">",
        0.0,
        v6
    );
    all_passed = all_passed && v6;

    std::printf(
        "\nASSESSMENT: %s — numerical initial-value instrument; "
        "not a closed-form general three-body solution.\n",
        all_passed ? "VALIDATED" : "REJECTED"
    );
    return all_passed ? 0 : 1;
}
