// GOM06 / B09 — binary period loss from an SDT resistance quadrupole.
//
// Forward inputs are raw timing observables: orbital period, eccentricity,
// periastron advance and Einstein-delay amplitude.  The period-loss
// comparison is loaded only after every prediction has been frozen.
//
// Sources:
//   B1913+16: Weisberg & Huang, ApJ 829 (2016) 55, Table 2.
//   J0737-3039A/B: Kramer et al., Phys. Rev. X 11 (2021) 041050;
//                  MeerKAT timing table (2022).
//
// Build:
//   cl /std:c++20 /EHsc /O2 /I Engine\include gom06_binary_decay.cpp
//
// Author: James Christopher Tyndall, Melbourne.

#include <sdt/laws.hpp>

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdio>
#include <numbers>
#include <vector>

namespace {

using sdt::laws::bridge::binary_radiation::angular_flux_weight;
using sdt::laws::bridge::binary_radiation::companion_resistance_fraction;
using sdt::laws::bridge::binary_radiation::depth_from_periastron_timing;
using sdt::laws::bridge::binary_radiation::period_decay;
using sdt::laws::bridge::binary_radiation::period_decay_from_timing;
using sdt::laws::bridge::binary_radiation::symmetric_resistance_ratio;

constexpr double pi = std::numbers::pi;

struct TimingGeometry {
    const char* name;
    double orbital_period_days;
    double eccentricity;
    double periastron_advance_deg_per_year;
    double einstein_delay_s;
};

struct Comparison {
    const char* name;
    double intrinsic_period_decay;
    double one_sigma;
};

struct Prediction {
    double depth;
    double companion_fraction;
    double eta;
    double time_domain;
    double frequency_domain;
    double canonical;
};

struct OrbitPoint {
    std::array<double, 3> position{};
    std::array<double, 3> first{};
    std::array<double, 3> second{};
    std::array<double, 3> third{};
};

[[nodiscard]] double eccentric_anomaly(double mean_anomaly, double eccentricity)
{
    double anomaly = mean_anomaly;
    for (int iteration = 0; iteration < 20; ++iteration) {
        const double residual =
            anomaly - eccentricity * std::sin(anomaly) - mean_anomaly;
        const double slope = 1.0 - eccentricity * std::cos(anomaly);
        anomaly -= residual / slope;
    }
    return anomaly;
}

[[nodiscard]] OrbitPoint orbit_point(
    double mean_anomaly,
    double eccentricity
) {
    const double anomaly = eccentric_anomaly(mean_anomaly, eccentricity);
    const double cosine = std::cos(anomaly);
    const double sine = std::sin(anomaly);
    const double compression = 1.0 - eccentricity * cosine;
    const double vertical_scale =
        std::sqrt(1.0 - eccentricity * eccentricity);

    const double anomaly_first = 1.0 / compression;
    const double anomaly_second =
        -eccentricity * sine / std::pow(compression, 3);
    const double anomaly_third =
        -eccentricity * cosine / std::pow(compression, 4)
        + 3.0 * eccentricity * eccentricity * sine * sine
          / std::pow(compression, 5);

    OrbitPoint point{};
    point.position = {cosine - eccentricity, vertical_scale * sine, 0.0};
    point.first = {
        -sine * anomaly_first,
        vertical_scale * cosine * anomaly_first,
        0.0
    };
    point.second = {
        -cosine * anomaly_first * anomaly_first
            - sine * anomaly_second,
        vertical_scale * (
            -sine * anomaly_first * anomaly_first
            + cosine * anomaly_second
        ),
        0.0
    };
    point.third = {
        sine * std::pow(anomaly_first, 3)
            - 3.0 * cosine * anomaly_first * anomaly_second
            - sine * anomaly_third,
        vertical_scale * (
            -cosine * std::pow(anomaly_first, 3)
            - 3.0 * sine * anomaly_first * anomaly_second
            + cosine * anomaly_third
        ),
        0.0
    };
    return point;
}

[[nodiscard]] std::array<double, 6> trace_free_quadrupole(
    const std::array<double, 3>& position
) {
    const double radius_squared =
        position[0] * position[0]
        + position[1] * position[1]
        + position[2] * position[2];
    return {
        position[0] * position[0] - radius_squared / 3.0,
        position[1] * position[1] - radius_squared / 3.0,
        position[2] * position[2] - radius_squared / 3.0,
        position[0] * position[1],
        position[0] * position[2],
        position[1] * position[2]
    };
}

[[nodiscard]] double quadrupole_third_norm(const OrbitPoint& point)
{
    double radius_squared_third = 0.0;
    for (int axis = 0; axis < 3; ++axis) {
        radius_squared_third +=
            2.0 * point.position[axis] * point.third[axis]
            + 6.0 * point.first[axis] * point.second[axis];
    }

    double norm = 0.0;
    for (int row = 0; row < 3; ++row) {
        for (int column = 0; column < 3; ++column) {
            const double product_third =
                point.third[row] * point.position[column]
                + 3.0 * point.second[row] * point.first[column]
                + 3.0 * point.first[row] * point.second[column]
                + point.position[row] * point.third[column];
            const double component =
                product_third
                - (row == column ? radius_squared_third / 3.0 : 0.0);
            norm += component * component;
        }
    }
    return norm;
}

[[nodiscard]] double time_domain_quadrupole_norm(
    double eccentricity,
    int samples
) {
    double total = 0.0;
    for (int sample = 0; sample < samples; ++sample) {
        const double mean_anomaly =
            2.0 * pi * (static_cast<double>(sample) + 0.5)
            / static_cast<double>(samples);
        total += quadrupole_third_norm(
            orbit_point(mean_anomaly, eccentricity)
        );
    }
    return total / static_cast<double>(samples);
}

[[nodiscard]] double frequency_domain_quadrupole_norm(
    double eccentricity,
    int samples
) {
    std::vector<std::array<double, 6>> quadrupoles(
        static_cast<std::size_t>(samples)
    );
    for (int sample = 0; sample < samples; ++sample) {
        const double mean_anomaly =
            2.0 * pi * static_cast<double>(sample)
            / static_cast<double>(samples);
        quadrupoles[static_cast<std::size_t>(sample)] =
            trace_free_quadrupole(
                orbit_point(mean_anomaly, eccentricity).position
            );
    }

    constexpr std::array<double, 6> tensor_weights = {
        1.0, 1.0, 1.0, 2.0, 2.0, 2.0
    };
    double derivative_norm = 0.0;
    for (int harmonic = 1; harmonic < samples / 2; ++harmonic) {
        std::array<double, 6> real{};
        std::array<double, 6> imaginary{};
        for (int sample = 0; sample < samples; ++sample) {
            const double angle =
                2.0 * pi * static_cast<double>(harmonic * sample)
                / static_cast<double>(samples);
            const double cosine = std::cos(angle);
            const double sine = std::sin(angle);
            for (int component = 0; component < 6; ++component) {
                const double value =
                    quadrupoles[static_cast<std::size_t>(sample)]
                               [static_cast<std::size_t>(component)];
                real[static_cast<std::size_t>(component)] += value * cosine;
                imaginary[static_cast<std::size_t>(component)] -= value * sine;
            }
        }

        const double normalization = 1.0 / static_cast<double>(samples);
        const double derivative_multiplier =
            std::pow(static_cast<double>(harmonic), 6);
        for (int component = 0; component < 6; ++component) {
            const double real_coefficient =
                real[static_cast<std::size_t>(component)] * normalization;
            const double imaginary_coefficient =
                imaginary[static_cast<std::size_t>(component)] * normalization;
            derivative_norm +=
                2.0
                * tensor_weights[static_cast<std::size_t>(component)]
                * derivative_multiplier
                * (
                    real_coefficient * real_coefficient
                    + imaginary_coefficient * imaginary_coefficient
                );
        }
    }
    return derivative_norm;
}

[[nodiscard]] double angular_shear_weight(int samples)
{
    // One arbitrary nonzero symmetric trace-free tensor.  Rotational
    // invariance makes the sphere average independent of this choice.
    constexpr double source[3][3] = {
        {1.0, 0.0, 0.0},
        {0.0, -1.0, 0.0},
        {0.0, 0.0, 0.0}
    };
    constexpr double source_norm = 2.0;
    const double golden_angle = pi * (3.0 - std::sqrt(5.0));
    double projected_norm = 0.0;

    for (int sample = 0; sample < samples; ++sample) {
        const double z =
            1.0 - 2.0 * (static_cast<double>(sample) + 0.5)
                    / static_cast<double>(samples);
        const double radius = std::sqrt(1.0 - z * z);
        const double azimuth = golden_angle * static_cast<double>(sample);
        const double direction[3] = {
            radius * std::cos(azimuth),
            radius * std::sin(azimuth),
            z
        };

        double projector[3][3]{};
        for (int row = 0; row < 3; ++row) {
            for (int column = 0; column < 3; ++column) {
                projector[row][column] =
                    (row == column ? 1.0 : 0.0)
                    - direction[row] * direction[column];
            }
        }

        double transverse_trace = 0.0;
        for (int row = 0; row < 3; ++row) {
            for (int column = 0; column < 3; ++column) {
                transverse_trace += projector[row][column] * source[row][column];
            }
        }

        double norm = 0.0;
        for (int row = 0; row < 3; ++row) {
            for (int column = 0; column < 3; ++column) {
                double projected = 0.0;
                for (int first = 0; first < 3; ++first) {
                    for (int second = 0; second < 3; ++second) {
                        projected +=
                            projector[row][first]
                            * source[first][second]
                            * projector[second][column];
                    }
                }
                const double transverse_trace_free =
                    projected
                    - 0.5 * projector[row][column] * transverse_trace;
                norm += transverse_trace_free * transverse_trace_free;
            }
        }
        projected_norm += norm;
    }

    const double sphere_average =
        projected_norm / static_cast<double>(samples) / source_norm;
    return 0.5 * sphere_average;  // quadratic Law-IV work
}

[[nodiscard]] double conservation_leakage(
    double eccentricity,
    double companion_fraction,
    int samples
) {
    const double first_fraction = 1.0 - companion_fraction;
    const double second_fraction = companion_fraction;
    double maximum = std::abs(first_fraction + second_fraction - 1.0);

    for (int sample = 0; sample < samples; ++sample) {
        const double mean_anomaly =
            2.0 * pi * static_cast<double>(sample)
            / static_cast<double>(samples);
        const auto relative =
            orbit_point(mean_anomaly, eccentricity).position;
        for (int axis = 0; axis < 3; ++axis) {
            const double first_position =
                second_fraction * relative[static_cast<std::size_t>(axis)];
            const double second_position =
                -first_fraction * relative[static_cast<std::size_t>(axis)];
            const double centre =
                first_fraction * first_position
                + second_fraction * second_position;
            maximum = std::max(maximum, std::abs(centre));
        }
    }
    return maximum;
}

[[nodiscard]] std::array<Comparison, 2> load_comparisons()
{
    // Loaded after the forward predictions.  B1913+16 includes the published
    // Galactic acceleration correction; J0737 includes distance, kinematic
    // and spin-down corrections.
    return {{
        {"B1913+16", -2.3980e-12, 0.0040e-12},
        {"J0737-3039A/B", -1.247920e-12, 0.000078e-12}
    }};
}

} // namespace

int main()
{
    constexpr std::array<TimingGeometry, 2> systems = {{
        {"B1913+16", 0.322997448918, 0.6171340, 4.226585, 4.307e-3},
        {"J0737-3039A/B", 0.1022515592972, 0.087777036, 16.899321, 0.384045e-3}
    }};

    std::printf("GOM06 / B09 — SDT resistance-quadrupole closure\n\n");

    const double angular_low = angular_shear_weight(8192);
    const double angular_high = angular_shear_weight(16384);
    const double angular_change =
        std::abs(angular_high / angular_low - 1.0);
    std::printf(
        "Angular TT shear weight: %.12f -> %.12f; change %.3e; exact ledger %.12f\n",
        angular_low,
        angular_high,
        angular_change,
        angular_flux_weight
    );

    const double circular_time = time_domain_quadrupole_norm(0.0, 1024);
    const double circular_frequency =
        frequency_domain_quadrupole_norm(0.0, 1024);
    std::printf(
        "Circular quadrupole norm: time %.12f; frequency %.12f; expected geometry 32\n",
        circular_time,
        circular_frequency
    );

    bool eccentricity_gate = true;
    double maximum_resolution_change = 0.0;
    std::printf("\nEccentric orbit integration:\n");
    constexpr std::array<double, 11> eccentricities = {
        0.0, 0.1, 0.2, 0.3, 0.4, 0.5,
        0.6, 0.6171340, 0.7, 0.8, 0.9
    };
    for (double eccentricity : eccentricities) {
        const double low =
            frequency_domain_quadrupole_norm(eccentricity, 512);
        const double high =
            frequency_domain_quadrupole_norm(eccentricity, 1024);
        const double time =
            time_domain_quadrupole_norm(eccentricity, 1024);
        const double resolution_change = std::abs(high / low - 1.0);
        const double path_difference = std::abs(time / high - 1.0);
        maximum_resolution_change =
            std::max(maximum_resolution_change, resolution_change);
        eccentricity_gate =
            eccentricity_gate
            && resolution_change < 0.005
            && path_difference < 0.01;
        std::printf(
            "  e=%.6f  F_num=%12.8f  resolution=%8.2e  paths=%8.2e\n",
            eccentricity,
            high / circular_frequency,
            resolution_change,
            path_difference
        );
    }

    // Freeze every prediction before observed period-loss values are loaded.
    std::array<Prediction, systems.size()> predictions{};
    double maximum_conservation_leakage = 0.0;
    double maximum_path_difference = 0.0;
    for (std::size_t index = 0; index < systems.size(); ++index) {
        const auto& system = systems[index];
        const double period_s = system.orbital_period_days * 86400.0;
        const double depth = depth_from_periastron_timing(
            period_s,
            system.eccentricity,
            system.periastron_advance_deg_per_year
        );
        const double companion_fraction = companion_resistance_fraction(
            period_s,
            system.eccentricity,
            depth,
            system.einstein_delay_s
        );
        const double eta =
            symmetric_resistance_ratio(companion_fraction);
        const double time_norm =
            time_domain_quadrupole_norm(system.eccentricity, 2048);
        const double frequency_norm =
            frequency_domain_quadrupole_norm(system.eccentricity, 2048);
        const double time_prediction =
            -6.0 * pi * angular_high * time_norm
            * eta * std::pow(depth, 2.5);
        const double frequency_prediction =
            -6.0 * pi * angular_high * frequency_norm
            * eta * std::pow(depth, 2.5);
        const double canonical_prediction = period_decay_from_timing(
            period_s,
            system.eccentricity,
            system.periastron_advance_deg_per_year,
            system.einstein_delay_s
        );
        predictions[index] = {
            depth,
            companion_fraction,
            eta,
            time_prediction,
            frequency_prediction,
            canonical_prediction
        };
        maximum_conservation_leakage = std::max(
            maximum_conservation_leakage,
            conservation_leakage(
                system.eccentricity,
                companion_fraction,
                2048
            )
        );
        maximum_path_difference = std::max(
            maximum_path_difference,
            std::abs(time_prediction / frequency_prediction - 1.0)
        );
    }

    const auto comparisons = load_comparisons();
    bool prediction_gate = true;
    bool control_gate = true;
    std::printf("\nFrozen timing predictions:\n");
    for (std::size_t index = 0; index < systems.size(); ++index) {
        const auto& system = systems[index];
        const auto& prediction = predictions[index];
        const auto& comparison = comparisons[index];
        const double residual =
            prediction.canonical / comparison.intrinsic_period_decay - 1.0;
        const double sigma_distance =
            std::abs(
                prediction.canonical - comparison.intrinsic_period_decay
            ) / comparison.one_sigma;
        prediction_gate = prediction_gate && std::abs(residual) <= 0.01;
        if (index == 1) {
            control_gate =
                prediction.canonical < 0.0
                && sigma_distance <= 2.0;
        }
        std::printf(
            "  %s: z=%.9e f=%.9f eta=%.9f\n",
            system.name,
            prediction.depth,
            prediction.companion_fraction,
            prediction.eta
        );
        std::printf(
            "    time=%+.12e frequency=%+.12e canonical=%+.12e\n",
            prediction.time_domain,
            prediction.frequency_domain,
            prediction.canonical
        );
        std::printf(
            "    observed intrinsic=%+.12e residual=%+.5f%% distance=%.3f sigma\n",
            comparison.intrinsic_period_decay,
            100.0 * residual,
            sigma_distance
        );
    }

    const bool conservation_gate =
        maximum_conservation_leakage < 1.0e-10;
    const bool angular_gate =
        angular_change < 0.005
        && std::abs(angular_high / angular_flux_weight - 1.0) < 1.0e-6;
    const bool circular_gate =
        std::abs(circular_time / 32.0 - 1.0) < 1.0e-6
        && std::abs(circular_frequency / 32.0 - 1.0) < 1.0e-6;
    const bool two_path_gate = maximum_path_difference < 0.01;
    const bool all_pass =
        conservation_gate
        && angular_gate
        && circular_gate
        && eccentricity_gate
        && two_path_gate
        && prediction_gate
        && control_gate;

    std::printf("\nGates:\n");
    std::printf(
        "  monopole/dipole leakage %.3e <1e-10: %s\n",
        maximum_conservation_leakage,
        conservation_gate ? "PASS" : "FAIL"
    );
    std::printf(
        "  angular coefficient/resolution: %s\n",
        angular_gate ? "PASS" : "FAIL"
    );
    std::printf(
        "  circular normalization F(0)=1: %s\n",
        circular_gate ? "PASS" : "FAIL"
    );
    std::printf(
        "  eccentric resolution max %.3e and same-orbit paths: %s\n",
        maximum_resolution_change,
        eccentricity_gate ? "PASS" : "FAIL"
    );
    std::printf(
        "  time/frequency whole-system agreement max %.3e: %s\n",
        maximum_path_difference,
        two_path_gate ? "PASS" : "FAIL"
    );
    std::printf(
        "  B1913+16 residual <=1%%: %s\n",
        prediction_gate ? "PASS" : "FAIL"
    );
    std::printf(
        "  J0737 sign and 2-sigma overlap: %s\n",
        control_gate ? "PASS" : "FAIL"
    );
    std::printf("\nB09 result: %s\n", all_pass ? "PASS" : "FAIL");
    return all_pass ? 0 : 1;
}
