#pragma once

/**
 * @file bridge_scanner.hpp
 * @brief Stage 7 — Bridge invariant detection
 *
 * Detects domain transitions in derivations and demands explicit
 * bridge invariants for each crossing.
 *
 * @author SDT Theory Compiler — James Tyndall, Melbourne, Australia
 * @date May 2026
 */

#include <sdt/compiler/types.hpp>
#include <sdt/compiler/derivation_graph.hpp>

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

namespace sdt::compiler {

class BridgeScanner {
public:
    BridgeScanner() { register_default_domains(); }

    // ─── Domain Registration ───

    void register_domain(const std::string& domain) {
        domains_.insert(domain);
    }

    void tag_step_domain(const std::string& step_id, const std::string& domain) {
        step_domains_[step_id].insert(domain);
    }

    // ─── Bridge Registration ───

    void register_bridge(const BridgeRecord& bridge) {
        bridges_.push_back(bridge);
        auto key = bridge.from_domain + "->" + bridge.to_domain;
        bridge_index_[key] = bridges_.size() - 1;
    }

    // ─── Auto-tag domains from keywords ───

    void auto_tag_step(const std::string& step_id, const std::string& content) {
        auto lower = content;
        for (auto& c : lower) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));

        static const std::vector<std::pair<std::string, std::vector<std::string>>> domain_keywords = {
            {"geometry",          {"radius", "sphere", "torus", "genus", "topology", "winding", "angle"}},
            {"motion",            {"velocity", "speed", "orbit", "rotation", "circulation"}},
            {"energy",            {"energy", "joule", "rest energy", "kinetic"}},
            {"pressure",          {"pressure", "pascal", "convergent", "occlusion"}},
            {"quantisation",      {"quantum", "quantis", "discrete", "shell", "orbital"}},
            {"lattice_structure", {"lattice", "spation", "relay", "nearest-neighbour"}},
            {"atomic_spectra",    {"spectrum", "emission", "rydberg", "wavelength", "balmer"}},
            {"gravitation",       {"gravity", "gravitational", "koppa", "c-boundary"}},
            {"electromagnetism",  {"coulomb", "electric", "magnetic", "charge", "dipole"}},
            {"atomic_structure",  {"atom", "electron", "proton", "neutron", "nuclear"}},
            {"chemistry",         {"molecule", "bond", "chemical", "reaction"}},
            {"cosmology",         {"cmb", "hubble", "redshift", "universe", "clearing"}},
        };

        for (auto& [domain, keywords] : domain_keywords) {
            for (auto& kw : keywords) {
                if (lower.find(kw) != std::string::npos) {
                    step_domains_[step_id].insert(domain);
                    break;
                }
            }
        }
    }

    // ─── Scan for Missing Bridges ───

    [[nodiscard]] auto scan(const DerivationGraphBuilder& deriv_graph) const
        -> std::vector<BridgeRecord>
    {
        std::vector<BridgeRecord> missing;
        auto& graph = deriv_graph.graph();

        for (auto& node : graph.nodes()) {
            auto succs = graph.successors(node);
            auto node_domains = get_domains(node);

            for (auto& succ : succs) {
                auto succ_domains = get_domains(succ);

                // Find domain transitions
                for (auto& from : node_domains) {
                    for (auto& to : succ_domains) {
                        if (from != to && !has_bridge(from, to)) {
                            BridgeRecord rec;
                            rec.bridge_id = "MISSING_" + from + "_to_" + to;
                            rec.from_domain = from;
                            rec.to_domain = to;
                            rec.status = BridgeStatus::MISSING;
                            rec.notes = "Derivation step " + node + " -> " + succ +
                                        " crosses from '" + from + "' to '" + to +
                                        "' without a registered bridge invariant.";

                            // Avoid duplicates
                            bool dup = false;
                            for (auto& m : missing) {
                                if (m.from_domain == from && m.to_domain == to) { dup = true; break; }
                            }
                            if (!dup) missing.push_back(rec);
                        }
                    }
                }
            }
        }
        return missing;
    }

    // ─── Accessors ───

    [[nodiscard]] auto bridges() const -> const std::vector<BridgeRecord>& { return bridges_; }

private:
    std::unordered_set<std::string>                              domains_;
    std::unordered_map<std::string, std::unordered_set<std::string>> step_domains_;
    std::vector<BridgeRecord>                                    bridges_;
    std::unordered_map<std::string, size_t>                      bridge_index_;

    void register_default_domains() {
        for (auto& d : {"geometry", "motion", "energy", "pressure", "quantisation",
                        "lattice_structure", "atomic_spectra", "occlusion", "gravitation",
                        "electromagnetism", "atomic_structure", "chemistry",
                        "material_properties", "cosmology"}) {
            domains_.insert(d);
        }
    }

    [[nodiscard]] auto get_domains(const std::string& step_id) const
        -> std::unordered_set<std::string>
    {
        auto it = step_domains_.find(step_id);
        if (it != step_domains_.end()) return it->second;
        return {};
    }

    [[nodiscard]] auto has_bridge(const std::string& from, const std::string& to) const -> bool {
        auto key1 = from + "->" + to;
        auto key2 = to + "->" + from; // Bidirectional check
        return bridge_index_.count(key1) || bridge_index_.count(key2);
    }
};

} // namespace sdt::compiler
