#pragma once

/**
 * @file kernel_manager.hpp
 * @brief Stage 2 — Invariant kernel lock, versioning, hashing, persistence
 *
 * Stores the locked theory kernel. Once locked, primitives, symbols,
 * dimensional basis, and foundational equations cannot mutate without
 * creating a versioned branch.
 *
 * @author SDT Theory Compiler — James Tyndall, Melbourne, Australia
 * @date May 2026
 */

#include <sdt/compiler/types.hpp>
#include <sdt/compiler/symbol_registry.hpp>
#include <sdt/compiler/sha256.hpp>
#include <sdt/compiler/json_writer.hpp>

#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <sstream>

namespace sdt::compiler {

class KernelManager {
public:
    // ─── Kernel Construction ───

    void set_theory_name(const std::string& name) { kernel_.theory_name = name; }
    void set_kernel_id(const std::string& id)      { kernel_.kernel_id = id; }
    void set_version(Version v)                     { kernel_.version = v; }

    void add_primitive(const SymbolEntry& entry) {
        if (kernel_.is_locked) return; // Cannot modify locked kernel
        kernel_.locked_primitives.push_back(entry);
    }

    void add_definition(const std::string& def) {
        if (kernel_.is_locked) return;
        kernel_.locked_definitions.push_back(def);
    }

    void add_equation(const std::string& eq) {
        if (kernel_.is_locked) return;
        kernel_.locked_equations.push_back(eq);
    }

    void add_dimension(const std::string& dim) {
        if (kernel_.is_locked) return;
        kernel_.dimension_basis.push_back(dim);
    }

    void add_forbidden_term(const std::string& term) {
        if (kernel_.is_locked) return;
        kernel_.forbidden_terms.push_back(term);
    }

    void add_allowed_transformation(const std::string& transform) {
        if (kernel_.is_locked) return;
        kernel_.allowed_transformations.push_back(transform);
    }

    // ─── Build from parsed theory + symbol registry ───

    void build_from(const ParsedTheory& parsed, const SymbolRegistry& registry) {
        if (kernel_.is_locked) return;

        // Import locked symbols as primitives
        for (auto& sym : registry.all_symbols()) {
            if (sym.status == SymbolStatus::LOCKED) {
                kernel_.locked_primitives.push_back(sym);
            }
        }

        // Import axioms as definitions
        for (auto& item : parsed.assumptions) {
            if (item.classification == InputClass::AXIOM) {
                kernel_.locked_definitions.push_back(item.normalised);
            }
        }

        // Import equations
        for (auto& item : parsed.equations) {
            kernel_.locked_equations.push_back(item.normalised);
        }
    }

    // ─── Locking ───

    auto lock() -> std::string {
        kernel_.is_locked = true;
        kernel_.hash = compute_hash();
        return kernel_.hash;
    }

    [[nodiscard]] auto is_locked() const noexcept -> bool { return kernel_.is_locked; }

    // ─── Mutation Detection ───

    struct MutationCheck {
        bool   mutated = false;
        std::string detail;
        FailureCategory failure = FailureCategory::VERSION_MUTATION_ERROR;
    };

    [[nodiscard]] auto check_mutation(const std::string& symbol_name,
                                       const std::string& new_definition) const -> MutationCheck
    {
        if (!kernel_.is_locked) return {false, ""};

        for (auto& prim : kernel_.locked_primitives) {
            if (prim.symbol == symbol_name) {
                if (!prim.definition.empty() && prim.definition != new_definition) {
                    return {true,
                        "Symbol '" + symbol_name + "' previously defined as '" +
                        prim.definition + "'. Attempted redefinition as '" +
                        new_definition + "'. Compilation halted.",
                        FailureCategory::VERSION_MUTATION_ERROR};
                }
            }
        }

        // Check forbidden terms
        for (auto& forbidden : kernel_.forbidden_terms) {
            if (symbol_name == forbidden || new_definition.find(forbidden) != std::string::npos) {
                return {true,
                    "Forbidden term '" + forbidden + "' detected in definition of '" + symbol_name + "'.",
                    FailureCategory::FORBIDDEN_CONCEPT_REINTRODUCTION};
            }
        }

        return {false, ""};
    }

    // ─── Versioning ───

    auto branch(const std::string& reason) -> TheoryKernel {
        TheoryKernel branched = kernel_;
        branched.version.major += 1;
        branched.version.minor = 0;
        branched.version.patch = 0;
        branched.is_locked = false;
        branched.hash.clear();
        branched.kernel_id += "_branch_" + std::to_string(branched.version.major);
        return branched;
    }

    void bump_patch() { kernel_.version.patch += 1; }
    void bump_minor() { kernel_.version.minor += 1; kernel_.version.patch = 0; }
    void bump_major() { kernel_.version.major += 1; kernel_.version.minor = 0; kernel_.version.patch = 0; }

    // ─── Hash Verification ───

    [[nodiscard]] auto verify_integrity() const -> bool {
        if (!kernel_.is_locked) return true;
        return compute_hash() == kernel_.hash;
    }

    // ─── Export ───

    [[nodiscard]] auto to_json() const -> std::string {
        JsonWriter jw;
        jw.begin_object();
        jw.key("kernel_id").value(kernel_.kernel_id);
        jw.key("theory_name").value(kernel_.theory_name);
        jw.key("version").value(kernel_.version.to_string());
        jw.key("is_locked").value(kernel_.is_locked);
        jw.key("hash").value(kernel_.hash);
        jw.key("mutation_policy").value(kernel_.mutation_policy);

        // Locked symbols
        jw.key("locked_symbols").begin_array();
        for (auto& prim : kernel_.locked_primitives) {
            jw.value(prim.symbol);
        }
        jw.end_array();

        jw.key("locked_definitions").string_array(kernel_.locked_definitions);
        jw.key("locked_equations").string_array(kernel_.locked_equations);
        jw.key("dimension_basis").string_array(kernel_.dimension_basis);
        jw.key("forbidden_terms").string_array(kernel_.forbidden_terms);
        jw.key("allowed_transformations").string_array(kernel_.allowed_transformations);

        // Full primitive details
        jw.key("locked_primitives").begin_array();
        for (auto& prim : kernel_.locked_primitives) {
            jw.begin_object();
            jw.key("symbol").value(prim.symbol);
            jw.key("name").value(prim.name);
            jw.key("type").value(prim.type);
            jw.key("definition").value(prim.definition);
            jw.key("dimensional_signature").value(prim.dimensional_signature);
            jw.key("domain").value(prim.domain);
            jw.key("status").value(symbol_status_str(prim.status));
            jw.key("version").value(prim.version.to_string());
            jw.end_object();
        }
        jw.end_array();

        jw.end_object();
        return jw.str();
    }

    auto save(const std::filesystem::path& path) const -> bool {
        std::ofstream f(path);
        if (!f.is_open()) return false;
        f << to_json();
        return true;
    }

    // ─── Accessors ───

    [[nodiscard]] auto kernel() const -> const TheoryKernel& { return kernel_; }
    [[nodiscard]] auto kernel() -> TheoryKernel& { return kernel_; }

private:
    TheoryKernel kernel_;

    [[nodiscard]] auto compute_hash() const -> std::string {
        // Hash: theory_name + all primitives + all definitions + all equations
        std::string content = kernel_.theory_name + "|";
        for (auto& prim : kernel_.locked_primitives) {
            content += prim.symbol + "=" + prim.definition + ";";
        }
        content += "|";
        for (auto& def : kernel_.locked_definitions) {
            content += def + ";";
        }
        content += "|";
        for (auto& eq : kernel_.locked_equations) {
            content += eq + ";";
        }
        return SHA256::hash(content);
    }
};

} // namespace sdt::compiler
