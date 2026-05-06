#pragma once

/**
 * @file adversarial.hpp
 * @brief Stage 8 — Adversarial validation pass (10-point hostile check)
 *
 * Runs every derivation through hostile checks. Generates objections,
 * classifies severity, recommends fixes.
 *
 * @author SDT Theory Compiler — James Tyndall, Melbourne, Australia
 * @date May 2026
 */

#include <sdt/compiler/types.hpp>
#include <sdt/compiler/symbol_registry.hpp>
#include <sdt/compiler/kernel_manager.hpp>
#include <sdt/compiler/dimension_engine.hpp>
#include <sdt/compiler/derivation_graph.hpp>
#include <sdt/compiler/drift_detector.hpp>
#include <sdt/compiler/bridge_scanner.hpp>

#include <string>
#include <vector>

namespace sdt::compiler {

class AdversarialExaminer {
public:
    AdversarialExaminer(const SymbolRegistry& symbols,
                        const KernelManager& kernel,
                        const DimensionEngine& dimensions,
                        const DerivationGraphBuilder& derivations,
                        const DriftDetector& drift,
                        const BridgeScanner& bridges)
        : symbols_(symbols), kernel_(kernel), dimensions_(dimensions),
          derivations_(derivations), drift_(drift), bridges_(bridges) {}

    // Run all 10 adversarial checks
    [[nodiscard]] auto examine() const -> ValidationReport {
        ValidationReport report;

        check_1_symbols_defined(report);
        check_2_dimensions_valid(report);
        check_3_silent_redefinition(report);
        check_4_analogy_as_proof(report);
        check_5_empirical_smuggling(report);
        check_6_circular_assumption(report);
        check_7_hidden_standard_physics(report);
        check_8_forbidden_reintroduction(report);
        check_9_reproducibility(report);
        check_10_validation_level(report);

        return report;
    }

private:
    const SymbolRegistry&        symbols_;
    const KernelManager&         kernel_;
    const DimensionEngine&       dimensions_;
    const DerivationGraphBuilder& derivations_;
    const DriftDetector&         drift_;
    const BridgeScanner&         bridges_;

    // 1. Are all symbols defined before use?
    void check_1_symbols_defined(ValidationReport& report) const {
        for (auto& sym : symbols_.all_symbols()) {
            if (sym.status == SymbolStatus::UNRESOLVED) {
                report.failures.push_back({
                    FailureCategory::UNDEFINED_SYMBOL, Severity::HIGH,
                    sym.symbol,
                    "Symbol '" + sym.symbol + "' used but never defined.",
                    "", "", sym.source_location
                });
            }
        }
    }

    // 2. Are equations dimensionally valid?
    void check_2_dimensions_valid(ValidationReport& report) const {
        for (auto& step : derivations_.all_steps()) {
            if (!step.output_equation.empty()) {
                auto record = dimensions_.validate_equation(step.output_equation);
                if (record.status == EqStatus::FAIL) {
                    report.failures.push_back({
                        FailureCategory::DIMENSION_FAIL, Severity::HIGH,
                        "", record.failure_reason,
                        record.lhs_dimension, record.rhs_dimension,
                        step.location
                    });
                } else if (record.status == EqStatus::PASS) {
                    report.passes.push_back("Dimension check PASS: " + step.output_equation);
                }
            }
        }
    }

    // 3. Is any term redefined silently?
    void check_3_silent_redefinition(ValidationReport& report) const {
        auto drifts = drift_.detect_all();
        for (auto& d : drifts) {
            auto sev = d.severity;
            CompilationFailure f{
                FailureCategory::SYMBOL_DRIFT, sev,
                d.term, d.recommended_fix,
                d.original_definition, d.later_usage,
                d.location
            };
            if (sev == Severity::FATAL) report.fatal_errors.push_back(f);
            else report.failures.push_back(f);

            report.semantic_drift.push_back(d);
        }
    }

    // 4. Is any analogy treated as proof?
    void check_4_analogy_as_proof(ValidationReport& report) const {
        for (auto& step : derivations_.all_steps()) {
            auto lower = step.justification;
            for (auto& c : lower) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));

            if (lower.find("analogous") != std::string::npos ||
                lower.find("similar to") != std::string::npos ||
                lower.find("by analogy") != std::string::npos ||
                lower.find("just as") != std::string::npos) {

                if (step.validation_status >= ValidationLevel::DERIVATION_LINKED) {
                    report.failures.push_back({
                        FailureCategory::ANALOGY_AS_PROOF, Severity::HIGH,
                        step.step_id,
                        "Step '" + step.step_id + "' uses analogy as justification "
                        "but claims derivation-level validation.",
                        "", step.justification, step.location
                    });
                }
            }
        }
    }

    // 5. Is any empirical input smuggled in?
    void check_5_empirical_smuggling(ValidationReport& report) const {
        auto empirical_points = derivations_.find_empirical_entry_points();
        for (auto& step_id : empirical_points) {
            auto* step = derivations_.step(step_id);
            if (step && step->validation_status >= ValidationLevel::REPRODUCIBLE) {
                report.warnings.push_back({
                    FailureCategory::EMPIRICAL_SMUGGLING, Severity::MEDIUM,
                    step_id,
                    "Step '" + step_id + "' contains empirical data but claims "
                    "reproducible status. Empirical inputs must be documented.",
                    "", "", step->location
                });
            }
        }
    }

    // 6. Is the conclusion already assumed?
    void check_6_circular_assumption(ValidationReport& report) const {
        auto cycles = derivations_.find_circular_derivations();
        for (auto& cycle : cycles) {
            std::string cycle_str;
            for (auto& id : cycle) {
                if (!cycle_str.empty()) cycle_str += " -> ";
                cycle_str += id;
            }
            report.fatal_errors.push_back({
                FailureCategory::CIRCULAR_DERIVATION, Severity::FATAL,
                "",
                "Circular derivation detected: " + cycle_str,
                "", "", {}
            });
        }
    }

    // 7. Does the derivation depend on hidden standard-physics?
    void check_7_hidden_standard_physics(ValidationReport& report) const {
        static const std::vector<std::string> forbidden_concepts = {
            "dark matter", "dark energy", "quark", "gluon",
            "virtual particle", "wavefunction collapse",
            "wave-particle duality", "vacuum fluctuation"
        };

        for (auto& step : derivations_.all_steps()) {
            auto lower = step.justification + " " + step.output_equation;
            for (auto& c : lower) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));

            for (auto& forbidden : forbidden_concepts) {
                if (lower.find(forbidden) != std::string::npos) {
                    report.failures.push_back({
                        FailureCategory::HIDDEN_ASSUMPTION, Severity::HIGH,
                        step.step_id,
                        "Step '" + step.step_id + "' references forbidden concept '" +
                        forbidden + "'.",
                        "", "", step.location
                    });
                }
            }
        }
    }

    // 8. Does the theory reject a concept but later reuse it?
    void check_8_forbidden_reintroduction(ValidationReport& report) const {
        auto& kernel = kernel_.kernel();
        for (auto& step : derivations_.all_steps()) {
            for (auto& forbidden : kernel.forbidden_terms) {
                auto lower_just = step.justification;
                for (auto& c : lower_just) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
                auto lower_forb = forbidden;
                for (auto& c : lower_forb) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));

                if (lower_just.find(lower_forb) != std::string::npos) {
                    report.fatal_errors.push_back({
                        FailureCategory::FORBIDDEN_CONCEPT_REINTRODUCTION, Severity::FATAL,
                        step.step_id,
                        "Step '" + step.step_id + "' reintroduces forbidden term '" +
                        forbidden + "' which the kernel explicitly prohibits.",
                        "", "", step.location
                    });
                }
            }
        }

        // Also check missing bridges
        auto missing = bridges_.scan(derivations_);
        for (auto& bridge : missing) {
            report.missing_bridges.push_back(bridge);
        }
    }

    // 9. Can the result be reproduced from the kernel alone?
    void check_9_reproducibility(ValidationReport& report) const {
        for (auto& step : derivations_.all_steps()) {
            if (step.validation_status >= ValidationLevel::REPRODUCIBLE) {
                if (!derivations_.is_reproducible(step.step_id)) {
                    report.failures.push_back({
                        FailureCategory::NON_REPRODUCIBLE_RESULT, Severity::HIGH,
                        step.step_id,
                        "Step '" + step.step_id + "' claims reproducible status but "
                        "cannot be regenerated from the kernel + derivation graph alone.",
                        "", "", step.location
                    });
                }
            }
        }
    }

    // 10. Does any claim exceed its validation level?
    void check_10_validation_level(ValidationReport& report) const {
        for (auto& step : derivations_.all_steps()) {
            // Check if validation level is justified
            if (step.validation_status >= ValidationLevel::REPRODUCIBLE) {
                if (!derivations_.is_reproducible(step.step_id)) {
                    report.warnings.push_back({
                        FailureCategory::CLAIM_EXCEEDS_VALIDATION_LEVEL, Severity::MEDIUM,
                        step.step_id,
                        "Step '" + step.step_id + "' claims validation level " +
                        validation_level_str(step.validation_status) +
                        " but evidence is insufficient.",
                        "", "", step.location
                    });
                    report.unsupported_claims.push_back(step.step_id);
                }
            }
        }
    }
};

} // namespace sdt::compiler
