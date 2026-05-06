#pragma once

/**
 * @file derivation_graph.hpp
 * @brief Stage 4 — Derivation dependency graph builder
 *
 * Stores derivations as dependency graphs, not prose.
 * Traces conclusions to axioms. Detects circular reasoning,
 * unsupported jumps, missing bridges.
 *
 * @author SDT Theory Compiler — James Tyndall, Melbourne, Australia
 * @date May 2026
 */

#include <sdt/compiler/types.hpp>
#include <sdt/compiler/graph.hpp>

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

namespace sdt::compiler {

class DerivationGraphBuilder {
public:
    // ─── Step Management ───

    void add_step(const DerivationStep& step) {
        steps_[step.step_id] = step;
        graph_.add_node(step.step_id);
        for (auto& dep : step.dependencies) {
            graph_.add_edge(dep, step.step_id);
        }
    }

    void add_axiom_node(const std::string& id, const std::string& content) {
        DerivationStep axiom_step;
        axiom_step.step_id = id;
        axiom_step.output_equation = content;
        axiom_step.justification = "AXIOM";
        axiom_step.validation_status = ValidationLevel::DEFINED;
        steps_[id] = axiom_step;
        graph_.add_node(id);
        axiom_ids_.insert(id);
    }

    void add_definition_node(const std::string& id, const std::string& content) {
        DerivationStep def_step;
        def_step.step_id = id;
        def_step.output_equation = content;
        def_step.justification = "DEFINITION";
        def_step.validation_status = ValidationLevel::DEFINED;
        steps_[id] = def_step;
        graph_.add_node(id);
        definition_ids_.insert(id);
    }

    // ─── Validation ───

    // Detect circular reasoning
    [[nodiscard]] auto find_circular_derivations() const -> std::vector<std::vector<std::string>> {
        return graph_.find_cycles();
    }

    // Detect steps with missing dependencies
    [[nodiscard]] auto find_unsupported_jumps() const -> std::vector<std::string> {
        std::vector<std::string> unsupported;
        for (auto& [id, step] : steps_) {
            for (auto& dep : step.dependencies) {
                if (!graph_.has_node(dep)) {
                    unsupported.push_back(id + " depends on undefined step " + dep);
                }
            }
        }
        return unsupported;
    }

    // Trace a conclusion back to its root axioms/definitions
    [[nodiscard]] auto trace_to_axioms(const std::string& step_id) const -> std::vector<std::string> {
        auto ancestors = graph_.ancestors_of(step_id);
        std::vector<std::string> axiom_roots;
        for (auto& anc : ancestors) {
            if (axiom_ids_.count(anc) || definition_ids_.count(anc)) {
                axiom_roots.push_back(anc);
            }
        }
        // Also check roots of the graph
        auto roots = graph_.roots();
        for (auto& r : roots) {
            if (graph_.can_reach(r, step_id)) {
                if (std::find(axiom_roots.begin(), axiom_roots.end(), r) == axiom_roots.end()) {
                    axiom_roots.push_back(r);
                }
            }
        }
        return axiom_roots;
    }

    // Identify where empirical values enter
    [[nodiscard]] auto find_empirical_entry_points() const -> std::vector<std::string> {
        std::vector<std::string> empirical;
        for (auto& [id, step] : steps_) {
            auto lower = step.justification;
            for (auto& c : lower) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
            if (lower.find("empirical") != std::string::npos ||
                lower.find("measured") != std::string::npos ||
                lower.find("codata") != std::string::npos ||
                lower.find("calibrated") != std::string::npos) {
                empirical.push_back(id);
            }
        }
        return empirical;
    }

    // Identify conjectural transitions
    [[nodiscard]] auto find_conjectural_steps() const -> std::vector<std::string> {
        std::vector<std::string> conjectural;
        for (auto& [id, step] : steps_) {
            auto lower = step.justification;
            for (auto& c : lower) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
            if (lower.find("conjecture") != std::string::npos ||
                lower.find("hypothesis") != std::string::npos) {
                conjectural.push_back(id);
            }
        }
        return conjectural;
    }

    // Get execution order (topological sort)
    [[nodiscard]] auto execution_order() const -> std::vector<std::string> {
        auto order = graph_.topological_sort();
        return order.value_or(std::vector<std::string>{});
    }

    // ─── Reproducibility ───

    // Check if a step can be reproduced from the graph alone
    [[nodiscard]] auto is_reproducible(const std::string& step_id) const -> bool {
        auto it = steps_.find(step_id);
        if (it == steps_.end()) return false;

        auto& step = it->second;
        // Must have all dependencies present
        for (auto& dep : step.dependencies) {
            if (steps_.find(dep) == steps_.end()) return false;
        }
        // Must trace back to axioms/definitions (no dangling roots)
        auto roots = trace_to_axioms(step_id);
        if (roots.empty() && !axiom_ids_.count(step_id) && !definition_ids_.count(step_id)) {
            return false;
        }
        // Must not be in a cycle
        auto cycles = graph_.find_cycles();
        for (auto& cycle : cycles) {
            if (std::find(cycle.begin(), cycle.end(), step_id) != cycle.end()) return false;
        }
        return true;
    }

    // ─── Accessors ───

    [[nodiscard]] auto step(const std::string& id) const -> const DerivationStep* {
        auto it = steps_.find(id);
        return it != steps_.end() ? &it->second : nullptr;
    }

    [[nodiscard]] auto all_steps() const -> std::vector<DerivationStep> {
        std::vector<DerivationStep> result;
        for (auto& [id, step] : steps_) result.push_back(step);
        return result;
    }

    [[nodiscard]] auto graph() const -> const DirectedGraph<std::string>& { return graph_; }
    [[nodiscard]] auto step_count() const -> size_t { return steps_.size(); }

private:
    std::unordered_map<std::string, DerivationStep> steps_;
    DirectedGraph<std::string>                      graph_;
    std::unordered_set<std::string>                 axiom_ids_;
    std::unordered_set<std::string>                 definition_ids_;
};

} // namespace sdt::compiler
