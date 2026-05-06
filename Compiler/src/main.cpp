/**
 * @file main.cpp
 * @brief CLI entry point for the SDT Theory Compiler
 *
 * Usage:
 *   sdt-compile <input.md|dir> [--name <theory>] [--output <dir>]
 *                              [--lock] [--validate-only] [--prohibitions]
 *
 * If <input> is a directory, all .md files within it are compiled together.
 *
 * @author SDT Theory Compiler — James Tyndall, Melbourne, Australia
 * @date May 2026
 */

#include <sdt/compiler/compiler.hpp>
#include <sdt/compiler/exporter.hpp>

#include <cstdio>
#include <string>
#include <vector>
#include <filesystem>

static void print_usage() {
    std::printf(
        "SDT Theory Compiler v1.0\n"
        "========================\n\n"
        "Usage: sdt-compile <input.md|dir> [options]\n\n"
        "  If <input> is a directory, all .md files are compiled together.\n\n"
        "Options:\n"
        "  --name <theory>    Theory name (default: derived from input)\n"
        "  --output <dir>     Output directory (default: ./output)\n"
        "  --lock             Lock kernel after parse (default: on)\n"
        "  --validate-only    Run validation, don't export\n"
        "  --prohibitions     Apply SDT standard prohibitions (default: on)\n"
        "  --no-prohibitions  Disable SDT standard prohibitions\n"
        "  --help             Show this help\n\n"
        "Outputs:\n"
        "  kernel.json        Locked invariant kernel\n"
        "  derivations.json   Derivation dependency graph\n"
        "  report.json        Validation report\n"
        "  report.md          Human-readable compilation report\n"
    );
}

struct CLIArgs {
    std::string input_path;
    std::string theory_name;
    std::string output_dir = "output";
    bool lock = true;
    bool validate_only = false;
    bool prohibitions = true;
};

static auto parse_args(int argc, char** argv) -> CLIArgs {
    CLIArgs args;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--help" || arg == "-h") {
            print_usage();
            std::exit(0);
        } else if (arg == "--name" && i + 1 < argc) {
            args.theory_name = argv[++i];
        } else if (arg == "--output" && i + 1 < argc) {
            args.output_dir = argv[++i];
        } else if (arg == "--lock") {
            args.lock = true;
        } else if (arg == "--validate-only") {
            args.validate_only = true;
        } else if (arg == "--prohibitions") {
            args.prohibitions = true;
        } else if (arg == "--no-prohibitions") {
            args.prohibitions = false;
        } else if (arg[0] != '-') {
            args.input_path = arg;
        }
    }

    return args;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        print_usage();
        return 1;
    }

    auto args = parse_args(argc, argv);

    if (args.input_path.empty()) {
        std::fprintf(stderr, "Error: No input file or directory specified.\n");
        return 1;
    }

    std::filesystem::path input_path(args.input_path);
    if (!std::filesystem::exists(input_path)) {
        std::fprintf(stderr, "Error: Input '%s' not found.\n", args.input_path.c_str());
        return 1;
    }

    bool is_directory = std::filesystem::is_directory(input_path);

    // Derive theory name from filename/dirname if not specified
    if (args.theory_name.empty()) {
        if (is_directory)
            args.theory_name = input_path.filename().string();
        else
            args.theory_name = input_path.stem().string();
    }

    std::printf("═══════════════════════════════════════════════\n");
    std::printf("  SDT THEORY COMPILER v1.0\n");
    std::printf("═══════════════════════════════════════════════\n\n");
    std::printf("  Input:  %s%s\n", args.input_path.c_str(), is_directory ? " (directory)" : "");
    std::printf("  Theory: %s\n", args.theory_name.c_str());
    std::printf("  Output: %s\n\n", args.output_dir.c_str());

    // ─── Compile ───

    sdt::compiler::TheoryCompiler compiler;
    compiler.set_theory_name(args.theory_name);

    if (args.prohibitions) {
        compiler.set_sdt_prohibitions();
        std::printf("[STAGE 0] SDT prohibitions loaded\n");
    }

    // Parse — single file or directory
    sdt::compiler::ParsedTheory parsed;

    if (is_directory) {
        std::printf("[STAGE 0] Scanning directory: %s\n", args.input_path.c_str());
        parsed = compiler.load_directory(input_path);

        std::printf("          Files loaded:\n");
        for (auto& f : compiler.source_files()) {
            std::printf("            • %s\n", f.c_str());
        }
    } else {
        std::printf("[STAGE 0] Parsing: %s\n", args.input_path.c_str());
        parsed = compiler.load_file(input_path);
    }

    std::printf("\n          ┌─────────────────────────────────────┐\n");
    std::printf("          │  PARSE SUMMARY                      │\n");
    std::printf("          ├─────────────────────────────────────┤\n");
    std::printf("          │  Total items:    %6zu              │\n", parsed.total_items());
    std::printf("          │  Definitions:    %6zu              │\n", parsed.definitions.size());
    std::printf("          │  Equations:      %6zu              │\n", parsed.equations.size());
    std::printf("          │  Claims:         %6zu              │\n", parsed.claims.size());
    std::printf("          │  Assumptions:    %6zu              │\n", parsed.assumptions.size());
    std::printf("          │  Conjectures:    %6zu              │\n", parsed.conjectures.size());
    std::printf("          │  Ambiguous:      %6zu              │\n", parsed.ambiguous_items.size());
    std::printf("          └─────────────────────────────────────┘\n\n");

    std::printf("[STAGE 1] Extracting symbols...\n");
    auto sym_failures = compiler.extract_symbols();
    auto& registry = compiler.symbol_registry();
    std::printf("          %zu symbols registered", registry.size());
    if (!sym_failures.empty()) {
        std::printf(", %zu conflicts", sym_failures.size());
    }
    std::printf("\n");

    std::printf("[STAGE 2] Building kernel...\n");
    compiler.build_kernel();
    if (args.lock) {
        auto hash = compiler.lock_kernel();
        std::printf("          Kernel LOCKED — hash: %.16s...\n", hash.c_str());
    }

    std::printf("[STAGE 3] Validating dimensions...\n");
    auto eq_records = compiler.validate_dimensions();
    int pass_count = 0, fail_count = 0, unresolved_count = 0;
    for (auto& r : eq_records) {
        if (r.status == sdt::compiler::EqStatus::PASS) ++pass_count;
        else if (r.status == sdt::compiler::EqStatus::FAIL) ++fail_count;
        else ++unresolved_count;
    }
    std::printf("          %d pass, %d fail, %d unresolved", pass_count, fail_count, unresolved_count);
    if (compiler.propagated_dimensions() > 0)
        std::printf(", %d inferred by propagation", compiler.propagated_dimensions());
    std::printf("\n");

    std::printf("[STAGE 4] Building derivation graph...\n");
    compiler.build_derivation_graph();

    // ─── State28D Manifold Report ───
    {
        std::printf("\n  ┌─────────────────────────────────────────────────────────────────┐\n");
        std::printf("  │  STATE28D MANIFOLD COVERAGE                                    │\n");
        std::printf("  ├─────────────────────────────────────────────────────────────────┤\n");

        // Collect all registered symbol names
        auto& all_syms = compiler.symbol_registry().all_symbols();
        std::vector<std::string> sym_names;
        sym_names.reserve(all_syms.size());
        for (auto& s : all_syms) sym_names.push_back(s.symbol);

        // Resolve which of the 28 aspects are covered
        auto covered = sdt::compiler::resolve_28d_coverage(sym_names);
        auto& aspects = sdt::compiler::state28d_aspects();

        const char* level_names[] = {
            "", "L1  Zero-Point ", "L2  Line       ", "L3  Plane      ",
            "L4  Sphere     ", "L5  Torus      ", "L6  Dynamism   ", "L7  Energy     "
        };
        int level_sizes[] = {0, 1, 2, 3, 4, 5, 6, 7};

        int total_found = 0;
        for (int lv = 1; lv <= 7; ++lv) {
            int count = 0;
            // Count covered aspects in this level
            for (auto& a : aspects) {
                if (static_cast<int>(a.level) == lv && covered[a.index]) ++count;
            }
            total_found += count;

            char bar[32] = {};
            int filled = (count * 20) / level_sizes[lv];
            for (int b = 0; b < 20; ++b) bar[b] = (b < filled) ? '=' : '.';
            std::printf("  │  %s [%s] %d/%d          │\n",
                        level_names[lv], bar, count, level_sizes[lv]);
        }
        std::printf("  ├─────────────────────────────────────────────────────────────────┤\n");
        std::printf("  │  Total: %d/28 aspects exercised by theory equations             │\n",
                    total_found);
        std::printf("  └─────────────────────────────────────────────────────────────────┘\n\n");

        // Show which aspects are NOT covered
        bool has_gaps = false;
        for (int i = 0; i < 28; ++i) {
            if (!covered[i]) {
                if (!has_gaps) {
                    std::printf("  28D gaps (aspects not yet exercised by theory):\n");
                    has_gaps = true;
                }
                std::printf("    ○ [%d] %s — %s\n", aspects[i].index, aspects[i].field_name.c_str(),
                            aspects[i].name.c_str());
            }
        }
        if (has_gaps) std::printf("\n");
    }

    std::printf("[STAGE 5-8] Adversarial validation...\n");
    auto report = compiler.run_adversarial();

    // ─── Results ───

    std::printf("\n═══════════════════════════════════════════════\n");
    if (report.has_fatal()) {
        std::printf("  COMPILATION FAILED\n");
    } else {
        std::printf("  COMPILATION SUCCEEDED\n");
    }
    std::printf("═══════════════════════════════════════════════\n\n");

    std::printf("  ┌─────────────────────────────────────┐\n");
    std::printf("  │  VALIDATION SUMMARY                 │\n");
    std::printf("  ├─────────────────────────────────────┤\n");
    std::printf("  │  Passes:        %6zu              │\n", report.passes.size());
    std::printf("  │  Warnings:      %6zu              │\n", report.warnings.size());
    std::printf("  │  Failures:      %6zu              │\n", report.failures.size());
    std::printf("  │  Fatal errors:  %6zu              │\n", report.fatal_errors.size());
    if (!report.missing_bridges.empty())
    std::printf("  │  Missing bridges: %4zu              │\n", report.missing_bridges.size());
    if (!report.semantic_drift.empty())
    std::printf("  │  Semantic drift:  %4zu              │\n", report.semantic_drift.size());
    std::printf("  └─────────────────────────────────────┘\n\n");

    // Print fatal errors
    if (!report.fatal_errors.empty()) {
        std::printf("  ── FATAL ERRORS ──\n\n");
        for (auto& f : report.fatal_errors) {
            std::printf("  ✘ [%s]", sdt::compiler::failure_category_str(f.category));
            if (!f.symbol.empty()) std::printf(" %s", f.symbol.c_str());
            std::printf("\n    %s\n", f.message.c_str());
            if (!f.location.file.empty())
                std::printf("    at %s\n", f.location.to_string().c_str());
            std::printf("\n");
        }
    }

    // Print failures (non-fatal)
    if (!report.failures.empty()) {
        std::printf("  ── FAILURES ──\n\n");
        int shown = 0;
        for (auto& f : report.failures) {
            std::printf("  ⚠ [%s]", sdt::compiler::failure_category_str(f.category));
            if (!f.symbol.empty()) std::printf(" %s", f.symbol.c_str());
            std::printf("\n    %s\n\n", f.message.c_str());
            if (++shown >= 25) {
                auto remaining = report.failures.size() - shown;
                if (remaining > 0)
                    std::printf("  ... and %zu more failures (see report.md)\n\n", remaining);
                break;
            }
        }
    }

    // Print dimension passes
    if (pass_count > 0) {
        std::printf("  ── DIMENSION PASSES ──\n\n");
        for (auto& r : eq_records) {
            if (r.status == sdt::compiler::EqStatus::PASS) {
                std::printf("  ✓ %s  [%s = %s]\n", r.equation.c_str(),
                            r.lhs_dimension.c_str(), r.rhs_dimension.c_str());
            }
        }
        std::printf("\n");
    }

    // ─── Export ───

    if (!args.validate_only) {
        std::printf("[EXPORT] Writing artefacts to %s/\n", args.output_dir.c_str());

        sdt::compiler::CompilationResult result;
        result.parsed = parsed;
        result.symbol_table = registry.all_symbols();
        result.kernel = compiler.kernel_manager().kernel();
        result.equation_records = eq_records;
        result.report = report;
        result.success = !report.has_fatal();

        compiler.export_all(result, args.output_dir);

        std::printf("         kernel.json      ✓\n");
        std::printf("         derivations.json  ✓\n");
        std::printf("         report.json       ✓\n");
        std::printf("         report.md         ✓\n");
    }

    std::printf("\nDone.\n");
    return report.has_fatal() ? 2 : 0;
}
