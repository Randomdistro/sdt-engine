#pragma once

/**
 * @file compiler.hpp
 * @brief Top-level Theory Compiler pipeline orchestrator
 *
 * Chains all stages: parse → symbols → kernel → dimensions →
 * derivation graph → drift → bridges → adversarial → export
 *
 * @author SDT Theory Compiler — James Tyndall, Melbourne, Australia
 * @date May 2026
 */

#include <sdt/compiler/types.hpp>
#include <sdt/compiler/parser.hpp>
#include <sdt/compiler/symbol_registry.hpp>
#include <sdt/compiler/kernel_manager.hpp>
#include <sdt/compiler/dimension_engine.hpp>
#include <sdt/compiler/derivation_graph.hpp>
#include <sdt/compiler/drift_detector.hpp>
#include <sdt/compiler/bridge_scanner.hpp>
#include <sdt/compiler/adversarial.hpp>
#include <sdt/compiler/exporter.hpp>

#include <string>
#include <vector>
#include <filesystem>

namespace sdt::compiler {

class TheoryCompiler {
public:
    TheoryCompiler() {
        dim_engine_.register_sdt_defaults();
    }

    // ─── Configuration ───

    void set_theory_name(const std::string& name) {
        kernel_mgr_.set_theory_name(name);
        kernel_mgr_.set_kernel_id(name + "_KERNEL_001");
    }

    void add_forbidden_term(const std::string& term) {
        kernel_mgr_.add_forbidden_term(term);
    }

    void set_sdt_prohibitions() {
        add_forbidden_term("quark");
        add_forbidden_term("gluon");
        add_forbidden_term("virtual particle");
        add_forbidden_term("dark matter");
        add_forbidden_term("dark energy");
        add_forbidden_term("wavefunction collapse");
        add_forbidden_term("wave-particle duality");
    }

    // ─── Stage 0: Load & Parse ───

    auto load_file(const std::filesystem::path& path) -> ParsedTheory {
        parsed_ = parser_.parse_file(path);
        source_files_.push_back(path.string());
        return parsed_;
    }

    auto load_string(const std::string& text, const std::string& source = "<input>") -> ParsedTheory {
        parsed_ = parser_.parse_string(text, source);
        return parsed_;
    }

    // Load multiple files and merge into a single ParsedTheory
    auto load_files(const std::vector<std::filesystem::path>& paths) -> ParsedTheory {
        parsed_ = {};
        for (auto& path : paths) {
            auto single = parser_.parse_file(path);
            parsed_.merge(single);
            source_files_.push_back(path.string());
        }
        return parsed_;
    }

    // Load all .md files from a directory (sorted by name)
    auto load_directory(const std::filesystem::path& dir) -> ParsedTheory {
        std::vector<std::filesystem::path> md_files;
        for (auto& entry : std::filesystem::directory_iterator(dir)) {
            if (entry.is_regular_file() && entry.path().extension() == ".md") {
                md_files.push_back(entry.path());
            }
        }
        std::sort(md_files.begin(), md_files.end());
        return load_files(md_files);
    }

    // ─── Stage 1: Symbol Extraction ───

    auto extract_symbols() -> std::vector<CompilationFailure> {
        return symbols_.extract_from_parsed(parsed_);
    }

    // ─── Stage 2: Kernel Lock ───

    auto build_kernel() -> void {
        kernel_mgr_.build_from(parsed_, symbols_);
    }

    auto lock_kernel() -> std::string {
        symbols_.lock_all();
        return kernel_mgr_.lock();
    }

    // ─── Stage 3: Dimension Validation ───

    auto validate_dimensions() -> std::vector<EquationRecord> {
        // First pass: validate with known dimensions
        eq_records_ = dim_engine_.validate_all(parsed_);

        // Propagation: iteratively infer unknown dimensions from equations
        int propagated = dim_engine_.propagate_from_equations(eq_records_);
        if (propagated > 0) {
            // Re-validate with newly inferred dimensions
            eq_records_ = dim_engine_.validate_all(parsed_);
        }
        propagated_count_ = propagated;

        return eq_records_;
    }

    [[nodiscard]] auto propagated_dimensions() const -> int { return propagated_count_; }

    // ─── Stage 4: Derivation Graph ───

    auto build_derivation_graph() -> void {
        // Add axioms and definitions as root nodes
        int axiom_count = 0;
        for (auto& item : parsed_.assumptions) {
            if (item.classification == InputClass::AXIOM) {
                std::string id = "AX" + std::to_string(++axiom_count);
                deriv_graph_.add_axiom_node(id, item.normalised);
            }
        }

        int def_count = 0;
        for (auto& item : parsed_.definitions) {
            std::string id = "DEF" + std::to_string(++def_count);
            deriv_graph_.add_definition_node(id, item.normalised);
        }

        // Add derivation steps from claims
        int step_count = 0;
        for (auto& item : parsed_.claims) {
            if (item.classification == InputClass::DERIVATION_STEP) {
                DerivationStep step;
                step.step_id = "D" + std::to_string(++step_count);
                step.output_equation = item.normalised;
                step.justification = item.raw_text;
                step.location = item.location;
                step.validation_status = ValidationLevel::PARSED;
                deriv_graph_.add_step(step);

                // Auto-tag domains
                bridge_scanner_.auto_tag_step(step.step_id, item.raw_text);
            }
        }
    }

    // ─── Stage 5–8: Adversarial Validation ───

    auto run_adversarial() -> ValidationReport {
        DriftDetector drift(symbols_);
        drift.set_forbidden_terms(kernel_mgr_.kernel().forbidden_terms);
        drift.record_from_parsed(parsed_);

        AdversarialExaminer examiner(
            symbols_, kernel_mgr_, dim_engine_,
            deriv_graph_, drift, bridge_scanner_
        );

        report_ = examiner.examine();
        return report_;
    }

    // ─── Full Pipeline ───

    auto compile() -> CompilationResult {
        CompilationResult result;

        // Stage 0: Parse
        // (already done via load_file/load_string)

        // Stage 1: Symbols
        auto symbol_failures = extract_symbols();

        // Stage 2: Kernel
        build_kernel();
        lock_kernel();

        // Stage 3: Dimensions
        validate_dimensions();

        // Stage 4: Derivation graph
        build_derivation_graph();

        // Stages 5–8: Adversarial
        run_adversarial();

        // Add symbol failures to report
        for (auto& f : symbol_failures) {
            if (f.severity == Severity::FATAL) report_.fatal_errors.push_back(f);
            else report_.failures.push_back(f);
        }

        // Assemble result
        result.parsed = parsed_;
        result.symbol_table = symbols_.all_symbols();
        result.kernel = kernel_mgr_.kernel();
        result.derivation_steps = deriv_graph_.all_steps();
        result.equation_records = eq_records_;
        result.report = report_;
        result.success = !report_.has_fatal();

        return result;
    }

    // ─── Export ───

    void export_all(const CompilationResult& result, const std::filesystem::path& output_dir) {
        Exporter::export_all(result, output_dir);
    }

    // ─── Accessors ───

    [[nodiscard]] auto symbol_registry() const -> const SymbolRegistry& { return symbols_; }
    [[nodiscard]] auto kernel_manager() const -> const KernelManager& { return kernel_mgr_; }
    [[nodiscard]] auto parsed() const -> const ParsedTheory& { return parsed_; }
    [[nodiscard]] auto source_files() const -> const std::vector<std::string>& { return source_files_; }

private:
    TheoryParser            parser_;
    SymbolRegistry          symbols_;
    KernelManager           kernel_mgr_;
    DimensionEngine         dim_engine_;
    DerivationGraphBuilder  deriv_graph_;
    BridgeScanner           bridge_scanner_;
    ValidationReport        report_;
    ParsedTheory            parsed_;
    std::vector<EquationRecord> eq_records_;
    std::vector<std::string>    source_files_;
    int                         propagated_count_ = 0;
};

} // namespace sdt::compiler
