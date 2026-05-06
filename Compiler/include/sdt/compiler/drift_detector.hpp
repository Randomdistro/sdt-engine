#pragma once

/**
 * @file drift_detector.hpp
 * @brief Stage 6 — Semantic drift detection
 *
 * Compares term usage across the document to detect when prose
 * silently changes the theory. Detects redefinitions, metaphor-to-mechanism
 * contamination, and forbidden concept reintroduction.
 *
 * @author SDT Theory Compiler — James Tyndall, Melbourne, Australia
 * @date May 2026
 */

#include <sdt/compiler/types.hpp>
#include <sdt/compiler/symbol_registry.hpp>

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

namespace sdt::compiler {

class DriftDetector {
public:
    explicit DriftDetector(const SymbolRegistry& registry)
        : registry_(registry) {}

    // ─── Configuration ───

    void add_forbidden_term(const std::string& term) {
        forbidden_terms_.push_back(term);
    }

    void set_forbidden_terms(const std::vector<std::string>& terms) {
        forbidden_terms_ = terms;
    }

    // ─── Term Usage Recording ───

    // Record how a term is used at a given location
    void record_usage(const std::string& term, const std::string& usage_context,
                      const SourceLocation& location) {
        usages_[term].push_back({usage_context, location});
    }

    // Record all term usages from a parsed theory
    void record_from_parsed(const ParsedTheory& parsed) {
        for (auto& item : parsed.all_items) {
            // Extract terms used in this item
            auto terms = extract_terms(item.raw_text);
            for (auto& term : terms) {
                record_usage(term, item.raw_text, item.location);
            }
        }
    }

    // ─── Drift Analysis ───

    [[nodiscard]] auto detect_all() const -> std::vector<DriftReport> {
        std::vector<DriftReport> reports;

        // 1. Symbol drift: same symbol, different definition
        detect_symbol_drift(reports);

        // 2. Forbidden concept reintroduction
        detect_forbidden_reintroduction(reports);

        // 3. Metaphor-to-mechanism contamination
        detect_metaphor_contamination(reports);

        return reports;
    }

    // Check a specific term for drift against the locked definition
    [[nodiscard]] auto check_term(const std::string& term, const std::string& new_usage,
                                   const SourceLocation& location) const
        -> std::optional<DriftReport>
    {
        auto sym = registry_.find(term);
        if (!sym) return std::nullopt;

        // Only check locked symbols
        if (sym->status != SymbolStatus::LOCKED) return std::nullopt;

        // Check if new usage conflicts with definition
        if (!sym->definition.empty() && is_conflicting_usage(sym->definition, new_usage)) {
            DriftReport report;
            report.term = term;
            report.original_definition = sym->definition;
            report.later_usage = new_usage;
            report.location = location;
            report.severity = Severity::FATAL;
            report.recommended_fix = "Restore usage of '" + term + "' to match its locked definition: '" +
                                     sym->definition + "'. If the new meaning is intended, create a version branch.";
            return report;
        }

        return std::nullopt;
    }

    // ─── Specific Drift Checks (from spec example) ───

    // Detects "k = c/v" later used as "k = v/c"
    [[nodiscard]] auto check_inversion_drift(const std::string& symbol,
                                              const std::string& original_def,
                                              const std::string& later_def) const
        -> std::optional<DriftReport>
    {
        // Simple inversion detection: if one def is "A/B" and other is "B/A"
        auto parse_ratio = [](const std::string& def) -> std::pair<std::string, std::string> {
            auto pos = def.find('/');
            if (pos == std::string::npos) return {"", ""};
            auto lhs = def.substr(0, pos);
            auto rhs = def.substr(pos + 1);
            // Trim
            while (!lhs.empty() && lhs.back() == ' ') lhs.pop_back();
            while (!rhs.empty() && rhs.front() == ' ') rhs.erase(rhs.begin());
            return {lhs, rhs};
        };

        auto [orig_num, orig_den] = parse_ratio(original_def);
        auto [later_num, later_den] = parse_ratio(later_def);

        if (!orig_num.empty() && !orig_den.empty() &&
            orig_num == later_den && orig_den == later_num) {
            DriftReport report;
            report.term = symbol;
            report.original_definition = symbol + " = " + original_def;
            report.later_usage = symbol + " = " + later_def;
            report.location = {};
            report.severity = Severity::FATAL;
            report.recommended_fix = "Symbol " + symbol + " inverted without version branch.";
            return report;
        }

        return std::nullopt;
    }

private:
    const SymbolRegistry& registry_;
    std::vector<std::string> forbidden_terms_;

    struct UsageRecord {
        std::string    context;
        SourceLocation location;
    };

    std::unordered_map<std::string, std::vector<UsageRecord>> usages_;

    void detect_symbol_drift(std::vector<DriftReport>& reports) const {
        for (auto& [term, uses] : usages_) {
            if (uses.size() < 2) continue;

            auto sym = registry_.find(term);
            if (!sym || sym->status != SymbolStatus::LOCKED) continue;

            // Check each usage against the original definition
            for (size_t i = 1; i < uses.size(); ++i) {
                if (is_conflicting_usage(sym->definition, uses[i].context)) {
                    reports.push_back({
                        term,
                        sym->definition,
                        uses[i].context,
                        uses[i].location,
                        Severity::HIGH,
                        "Term '" + term + "' usage at " + uses[i].location.to_string() +
                        " may conflict with locked definition."
                    });
                }
            }
        }
    }

    void detect_forbidden_reintroduction(std::vector<DriftReport>& reports) const {
        auto lower_str = [](const std::string& s) {
            std::string r = s;
            for (auto& c : r) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
            return r;
        };

        // Negation/prohibition context markers — if the sentence containing
        // the forbidden term ALSO contains one of these, it's a prohibition
        // declaration, not a reintroduction.
        static const std::vector<std::string> negation_markers = {
            "not permitted", "prohibited", "rejected", "forbidden",
            "not allowed", "not used", "never", "must not",
            "cannot", "shall not", "are not", "is not",
            "no ", "non-", "without", "absent", "eliminated",
            "replaced", "instead of", "replaces", "dispensed",
            "not invoked", "not required", "not employ",
            "prohibit", "ruleset", "prohibition",
        };

        // Track which forbidden terms we've already reported to deduplicate
        std::unordered_set<std::string> reported_terms;

        for (auto& [term, uses] : usages_) {
            for (auto& forbidden : forbidden_terms_) {
                if (reported_terms.count(forbidden)) continue; // Already reported

                auto lf = lower_str(forbidden);
                for (auto& use : uses) {
                    auto lc = lower_str(use.context);
                    if (lc.find(lf) == std::string::npos) continue;

                    // Check if this is a prohibition declaration (negation context)
                    bool is_prohibition_declaration = false;
                    for (auto& neg : negation_markers) {
                        if (lc.find(neg) != std::string::npos) {
                            is_prohibition_declaration = true;
                            break;
                        }
                    }

                    // Also check if the section heading indicates a prohibitions section
                    auto section_lower = lower_str(use.location.section);
                    if (section_lower.find("prohibit") != std::string::npos ||
                        section_lower.find("forbidden") != std::string::npos ||
                        section_lower.find("ruleset") != std::string::npos ||
                        section_lower.find("constitution") != std::string::npos) {
                        is_prohibition_declaration = true;
                    }

                    if (is_prohibition_declaration) continue; // Skip — this is a rule defining the ban

                    reports.push_back({
                        forbidden,
                        "FORBIDDEN",
                        use.context,
                        use.location,
                        Severity::FATAL,
                        "Forbidden term '" + forbidden + "' reintroduced. "
                        "This concept is prohibited by the theory kernel."
                    });
                    reported_terms.insert(forbidden); // Deduplicate
                    break; // One report per forbidden term is enough
                }
            }
        }
    }

    void detect_metaphor_contamination(std::vector<DriftReport>& reports) const {
        // Track terms that appear in both definitional and metaphorical contexts
        static const std::vector<std::string> metaphor_markers = {
            "like", "as if", "think of", "picture", "imagine",
            "metaphor", "analogy", "similar to", "reminiscent"
        };

        for (auto& [term, uses] : usages_) {
            bool used_mechanically = false;
            bool used_metaphorically = false;
            UsageRecord mech_use, meta_use;

            for (auto& use : uses) {
                auto lower_ctx = detail::to_lower(use.context);
                bool is_metaphorical = false;
                for (auto& marker : metaphor_markers) {
                    if (lower_ctx.find(marker) != std::string::npos) {
                        is_metaphorical = true;
                        break;
                    }
                }

                if (is_metaphorical) {
                    used_metaphorically = true;
                    meta_use = use;
                } else {
                    auto sym = registry_.find(term);
                    if (sym && !sym->definition.empty()) {
                        used_mechanically = true;
                        mech_use = use;
                    }
                }
            }

            if (used_mechanically && used_metaphorically) {
                reports.push_back({
                    term,
                    "Mechanical: " + mech_use.context,
                    "Metaphorical: " + meta_use.context,
                    meta_use.location,
                    Severity::MEDIUM,
                    "Term '" + term + "' used mechanically in one section and "
                    "metaphorically in another. Distinguish uses or clarify intent."
                });
            }
        }
    }

    [[nodiscard]] static auto is_conflicting_usage(const std::string& definition,
                                                     const std::string& usage) -> bool {
        // Basic conflict detection: if usage contains a different equation
        // for the same symbol
        // This is a heuristic — the full version uses the expression tree
        if (definition.empty() || usage.empty()) return false;

        // If usage explicitly redefines with a different equation
        auto def_lower = detail::to_lower(definition);
        auto use_lower = detail::to_lower(usage);

        // Check for explicit redefinition patterns
        if (use_lower.find("redefine") != std::string::npos ||
            use_lower.find("now means") != std::string::npos ||
            use_lower.find("instead") != std::string::npos) {
            return true;
        }

        return false;
    }

    [[nodiscard]] static auto extract_terms(const std::string& text) -> std::vector<std::string> {
        std::vector<std::string> terms;
        size_t i = 0;
        while (i < text.size()) {
            if (std::isalpha(static_cast<unsigned char>(text[i])) ||
                static_cast<unsigned char>(text[i]) > 127) {
                size_t start = i;
                while (i < text.size() &&
                       (std::isalnum(static_cast<unsigned char>(text[i])) ||
                        text[i] == '_' ||
                        static_cast<unsigned char>(text[i]) > 127)) ++i;
                std::string term = text.substr(start, i - start);
                if (term.size() >= 1 && std::find(terms.begin(), terms.end(), term) == terms.end()) {
                    terms.push_back(term);
                }
            } else {
                ++i;
            }
        }
        return terms;
    }
};

} // namespace sdt::compiler
