#pragma once

/**
 * @file exporter.hpp
 * @brief Output: JSON / Markdown / HTML artefact export
 *
 * Generates the four required outputs: Kernel File, Derivation Graph,
 * Validation Report, and Human-Readable Document.
 *
 * @author SDT Theory Compiler — James Tyndall, Melbourne, Australia
 * @date May 2026
 */

#include <sdt/compiler/types.hpp>
#include <sdt/compiler/json_writer.hpp>

#include <string>
#include <fstream>
#include <filesystem>

namespace sdt::compiler {

class Exporter {
public:
    // ─── Output A: Kernel File (JSON) ───

    [[nodiscard]] static auto kernel_json(const TheoryKernel& kernel) -> std::string {
        JsonWriter jw;
        jw.begin_object();
        jw.key("theory_name").value(kernel.theory_name);
        jw.key("version").value(kernel.version.to_string());
        jw.key("kernel_id").value(kernel.kernel_id);
        jw.key("hash").value(kernel.hash);
        jw.key("is_locked").value(kernel.is_locked);

        jw.key("locked_primitives").begin_array();
        for (auto& p : kernel.locked_primitives) {
            jw.begin_object();
            jw.key("symbol").value(p.symbol);
            jw.key("name").value(p.name);
            jw.key("definition").value(p.definition);
            jw.key("dimensional_signature").value(p.dimensional_signature);
            jw.key("status").value(symbol_status_str(p.status));
            jw.end_object();
        }
        jw.end_array();

        jw.key("locked_definitions").string_array(kernel.locked_definitions);
        jw.key("locked_equations").string_array(kernel.locked_equations);
        jw.key("dimension_basis").string_array(kernel.dimension_basis);
        jw.key("forbidden_terms").string_array(kernel.forbidden_terms);
        jw.key("allowed_transformations").string_array(kernel.allowed_transformations);
        jw.end_object();
        return jw.str();
    }

    // ─── Output B: Derivation Graph (JSON) ───

    [[nodiscard]] static auto derivation_json(const std::vector<DerivationStep>& steps) -> std::string {
        JsonWriter jw;
        jw.begin_object();
        jw.key("derivations").begin_array();
        for (auto& step : steps) {
            jw.begin_object();
            jw.key("id").value(step.step_id);
            jw.key("operation").value(transform_kind_str(step.operation));
            jw.key("output_equation").value(step.output_equation);
            jw.key("justification").value(step.justification);
            jw.key("validation_status").value(validation_level_str(step.validation_status));
            jw.key("input_equations").string_array(step.input_equations);
            jw.key("input_definitions").string_array(step.input_definitions);
            jw.key("dependencies").string_array(step.dependencies);
            jw.key("failure_modes").string_array(step.failure_modes);
            jw.end_object();
        }
        jw.end_array();
        jw.end_object();
        return jw.str();
    }

    // ─── Output C: Validation Report (JSON) ───

    [[nodiscard]] static auto report_json(const ValidationReport& report) -> std::string {
        JsonWriter jw;
        jw.begin_object();

        jw.key("passes").string_array(report.passes);

        auto write_failures = [&](const char* key, const std::vector<CompilationFailure>& failures) {
            jw.key(key).begin_array();
            for (auto& f : failures) {
                jw.begin_object();
                jw.key("type").value(failure_category_str(f.category));
                jw.key("severity").value(severity_str(f.severity));
                jw.key("symbol").value(f.symbol);
                jw.key("message").value(f.message);
                if (!f.original_definition.empty())
                    jw.key("original_definition").value(f.original_definition);
                if (!f.later_definition.empty())
                    jw.key("later_definition").value(f.later_definition);
                if (!f.location.file.empty())
                    jw.key("location").value(f.location.to_string());
                jw.end_object();
            }
            jw.end_array();
        };

        write_failures("warnings", report.warnings);
        write_failures("failures", report.failures);
        write_failures("fatal_errors", report.fatal_errors);

        jw.key("missing_bridges").begin_array();
        for (auto& b : report.missing_bridges) {
            jw.begin_object();
            jw.key("bridge_id").value(b.bridge_id);
            jw.key("from_domain").value(b.from_domain);
            jw.key("to_domain").value(b.to_domain);
            jw.key("status").value(bridge_status_str(b.status));
            jw.key("notes").value(b.notes);
            jw.end_object();
        }
        jw.end_array();

        jw.key("semantic_drift").begin_array();
        for (auto& d : report.semantic_drift) {
            jw.begin_object();
            jw.key("term").value(d.term);
            jw.key("original_definition").value(d.original_definition);
            jw.key("later_usage").value(d.later_usage);
            jw.key("severity").value(severity_str(d.severity));
            jw.key("recommended_fix").value(d.recommended_fix);
            jw.end_object();
        }
        jw.end_array();

        jw.key("unsupported_claims").string_array(report.unsupported_claims);

        jw.end_object();
        return jw.str();
    }

    // ─── Output D: Human-Readable Markdown ───

    [[nodiscard]] static auto report_markdown(const CompilationResult& result) -> std::string {
        std::string md;
        md += "# Theory Compilation Report\n\n";
        md += "**Theory:** " + result.kernel.theory_name + "\n";
        md += "**Version:** " + result.kernel.version.to_string() + "\n";
        md += "**Status:** " + std::string(result.success ? "COMPILED" : "FAILED") + "\n";
        md += "**Kernel Hash:** `" + result.kernel.hash + "`\n\n";

        // Summary
        md += "## Summary\n\n";
        md += "| Metric | Count |\n|--------|-------|\n";
        md += "| Total items parsed | " + std::to_string(result.parsed.total_items()) + " |\n";
        md += "| Symbols registered | " + std::to_string(result.symbol_table.size()) + " |\n";
        md += "| Equations validated | " + std::to_string(result.equation_records.size()) + " |\n";
        md += "| Derivation steps | " + std::to_string(result.derivation_steps.size()) + " |\n";
        md += "| Passes | " + std::to_string(result.report.passes.size()) + " |\n";
        md += "| Warnings | " + std::to_string(result.report.warnings.size()) + " |\n";
        md += "| Failures | " + std::to_string(result.report.failures.size()) + " |\n";
        md += "| Fatal errors | " + std::to_string(result.report.fatal_errors.size()) + " |\n\n";

        // Fatal errors
        if (!result.report.fatal_errors.empty()) {
            md += "## ❌ Fatal Errors\n\n";
            for (auto& f : result.report.fatal_errors) {
                md += "- **" + std::string(failure_category_str(f.category)) + "**";
                if (!f.symbol.empty()) md += " (`" + f.symbol + "`)";
                md += ": " + f.message + "\n";
            }
            md += "\n";
        }

        // Failures
        if (!result.report.failures.empty()) {
            md += "## ⚠️ Failures\n\n";
            for (auto& f : result.report.failures) {
                md += "- **" + std::string(failure_category_str(f.category)) + "**";
                if (!f.symbol.empty()) md += " (`" + f.symbol + "`)";
                md += ": " + f.message + "\n";
            }
            md += "\n";
        }

        // Symbol table
        md += "## Symbol Table\n\n";
        md += "| Symbol | Name | Definition | Status |\n";
        md += "|--------|------|------------|--------|\n";
        for (auto& sym : result.symbol_table) {
            md += "| `" + sym.symbol + "` | " + sym.name + " | " + sym.definition +
                  " | " + symbol_status_str(sym.status) + " |\n";
        }
        md += "\n";

        // Equations
        if (!result.equation_records.empty()) {
            md += "## Equation Validation\n\n";
            md += "| Equation | LHS Dim | RHS Dim | Status |\n";
            md += "|----------|---------|---------|--------|\n";
            for (auto& eq : result.equation_records) {
                std::string badge = eq.status == EqStatus::PASS ? "✅" :
                                    eq.status == EqStatus::FAIL ? "❌" : "⏳";
                md += "| `" + eq.equation + "` | " + eq.lhs_dimension + " | " +
                      eq.rhs_dimension + " | " + badge + " |\n";
            }
            md += "\n";
        }

        // Passes
        if (!result.report.passes.empty()) {
            md += "## ✅ Passes\n\n";
            for (auto& p : result.report.passes) {
                md += "- " + p + "\n";
            }
            md += "\n";
        }

        // State28D Manifold Coverage
        md += "## State28D Manifold\n\n";
        md += "The 28-dimensional state manifold Ξ ∈ ℝ²⁸ organises every physical locus.\n\n";
        md += "| # | Level | Field | Description | Dimension | Registered |\n";
        md += "|---|-------|-------|-------------|-----------|------------|\n";
        for (auto& a : state28d_aspects()) {
            bool found = false;
            for (auto& sym : result.symbol_table) {
                if (sym.symbol == a.symbol) { found = true; break; }
            }
            md += "| " + std::to_string(a.index) +
                  " | L" + std::to_string(static_cast<int>(a.level)) +
                  " | `" + a.symbol +
                  "` | " + a.name +
                  " | " + a.dimension_str +
                  " | " + (found ? "✅" : "—") + " |\n";
        }
        md += "\n";

        return md;
    }

    // ─── File Output ───

    static auto save(const std::filesystem::path& path, const std::string& content) -> bool {
        auto parent = path.parent_path();
        if (!parent.empty()) std::filesystem::create_directories(parent);
        std::ofstream f(path);
        if (!f.is_open()) return false;
        f << content;
        return true;
    }

    static void export_all(const CompilationResult& result, const std::filesystem::path& output_dir) {
        std::filesystem::create_directories(output_dir);
        save(output_dir / "kernel.json",     kernel_json(result.kernel));
        save(output_dir / "derivations.json", derivation_json(result.derivation_steps));
        save(output_dir / "report.json",     report_json(result.report));
        save(output_dir / "report.md",       report_markdown(result));
    }
};

} // namespace sdt::compiler
