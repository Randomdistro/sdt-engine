#pragma once

/**
 * @file symbol_registry.hpp
 * @brief Stage 1 — Global symbol table with conflict detection
 *
 * Maintains the symbol table, detects duplicates, conflicts,
 * undefined references, circular definitions, and manages symbol locking.
 *
 * @author SDT Theory Compiler — James Tyndall, Melbourne, Australia
 * @date May 2026
 */

#include <sdt/compiler/types.hpp>

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <optional>
#include <algorithm>

namespace sdt::compiler {

class SymbolRegistry {
public:
    // ─── Registration ───

    struct RegisterResult {
        bool     success = false;
        uint64_t id = 0;
        std::string error;
        FailureCategory failure = FailureCategory::UNDEFINED_SYMBOL;
    };

    [[nodiscard]] auto register_symbol(SymbolEntry entry) -> RegisterResult {
        // Check for duplicates with conflicting definitions
        auto it = by_name_.find(entry.symbol);
        if (it != by_name_.end()) {
            auto& existing = symbols_[it->second];
            if (existing.definition != entry.definition && !existing.definition.empty()) {
                return {false, 0,
                    "Symbol '" + entry.symbol + "' already defined as '" +
                    existing.definition + "', conflicting definition: '" +
                    entry.definition + "'",
                    FailureCategory::SYMBOL_DRIFT};
            }
            // Same definition — update metadata if needed
            if (entry.definition.empty()) entry.definition = existing.definition;
            entry.id = existing.id;
            symbols_[it->second] = entry;
            return {true, entry.id, ""};
        }

        // Check forbidden aliases
        for (auto& [name, idx] : by_name_) {
            auto& sym = symbols_[idx];
            for (auto& forbidden : sym.forbidden_aliases) {
                if (forbidden == entry.symbol) {
                    return {false, 0,
                        "Symbol '" + entry.symbol + "' is a forbidden alias of '" + sym.symbol + "'",
                        FailureCategory::SYMBOL_DRIFT};
                }
            }
        }

        entry.id = next_id_++;
        size_t idx = symbols_.size();
        symbols_.push_back(entry);
        by_name_[entry.symbol] = idx;

        // Register aliases
        for (auto& alias : entry.aliases) {
            alias_map_[alias] = idx;
        }

        return {true, entry.id, ""};
    }

    // ─── Lookup ───

    [[nodiscard]] auto find(const std::string& name) const -> std::optional<SymbolEntry> {
        auto it = by_name_.find(name);
        if (it != by_name_.end()) return symbols_[it->second];
        // Check aliases
        auto ait = alias_map_.find(name);
        if (ait != alias_map_.end()) return symbols_[ait->second];
        return std::nullopt;
    }

    [[nodiscard]] auto find_by_id(uint64_t id) const -> std::optional<SymbolEntry> {
        for (auto& sym : symbols_) {
            if (sym.id == id) return sym;
        }
        return std::nullopt;
    }

    [[nodiscard]] auto contains(const std::string& name) const -> bool {
        return by_name_.count(name) > 0 || alias_map_.count(name) > 0;
    }

    // ─── Locking ───

    auto lock_symbol(const std::string& name) -> bool {
        auto it = by_name_.find(name);
        if (it == by_name_.end()) return false;
        symbols_[it->second].status = SymbolStatus::LOCKED;
        return true;
    }

    auto lock_all() -> void {
        for (auto& sym : symbols_) sym.status = SymbolStatus::LOCKED;
    }

    // ─── Validation ───

    // Find all symbols referenced in a set of expressions but not defined
    [[nodiscard]] auto find_undefined(const std::vector<std::string>& referenced) const
        -> std::vector<std::string>
    {
        std::vector<std::string> undefined;
        for (auto& name : referenced) {
            if (!contains(name)) {
                if (std::find(undefined.begin(), undefined.end(), name) == undefined.end()) {
                    undefined.push_back(name);
                }
            }
        }
        return undefined;
    }

    // Detect circular definitions (A depends on B, B depends on A)
    [[nodiscard]] auto find_circular_definitions() const -> std::vector<std::vector<std::string>> {
        std::vector<std::vector<std::string>> cycles;
        std::unordered_set<std::string> visited;
        std::unordered_set<std::string> in_stack;
        std::vector<std::string> path;

        for (auto& sym : symbols_) {
            if (visited.count(sym.symbol) == 0) {
                dfs_cycle(sym.symbol, visited, in_stack, path, cycles);
            }
        }
        return cycles;
    }

    // Check for symbol drift: same symbol used with different definition later
    [[nodiscard]] auto check_drift(const std::string& name, const std::string& new_definition,
                                    const SourceLocation& location) const
        -> std::optional<DriftReport>
    {
        auto it = by_name_.find(name);
        if (it == by_name_.end()) return std::nullopt;

        auto& existing = symbols_[it->second];
        if (existing.status == SymbolStatus::LOCKED &&
            !existing.definition.empty() &&
            existing.definition != new_definition) {
            return DriftReport{
                name,
                existing.definition,
                new_definition,
                location,
                Severity::FATAL,
                "Symbol '" + name + "' previously defined as '" + existing.definition +
                "'. Later used as '" + new_definition + "'. This reverses the quantity."
            };
        }
        return std::nullopt;
    }

    // ─── Accessors ───

    [[nodiscard]] auto all_symbols() const -> const std::vector<SymbolEntry>& { return symbols_; }
    [[nodiscard]] auto size() const noexcept -> size_t { return symbols_.size(); }

    // Get all locked symbol names
    [[nodiscard]] auto locked_symbols() const -> std::vector<std::string> {
        std::vector<std::string> result;
        for (auto& sym : symbols_) {
            if (sym.status == SymbolStatus::LOCKED) result.push_back(sym.symbol);
        }
        return result;
    }

    // ─── Bulk extraction from parsed items ───

    auto extract_from_parsed(const ParsedTheory& parsed) -> std::vector<CompilationFailure> {
        std::vector<CompilationFailure> failures;

        for (auto& item : parsed.definitions) {
            auto extracted = extract_symbol_from_text(item.raw_text, item.location);
            for (auto& entry : extracted) {
                auto result = register_symbol(entry);
                if (!result.success) {
                    failures.push_back({
                        result.failure, Severity::HIGH,
                        entry.symbol, result.error,
                        "", "", item.location
                    });
                }
            }
        }

        // Extract from equations (symbols used in equations)
        for (auto& item : parsed.equations) {
            auto syms = extract_symbols_from_equation(item.normalised);
            for (auto& name : syms) {
                if (!contains(name)) {
                    // Register as unresolved (used but not yet defined)
                    SymbolEntry entry;
                    entry.symbol = name;
                    entry.status = SymbolStatus::UNRESOLVED;
                    entry.source_location = item.location;
                    register_symbol(entry);
                }
            }
        }

        return failures;
    }

private:
    std::vector<SymbolEntry>                    symbols_;
    std::unordered_map<std::string, size_t>     by_name_;
    std::unordered_map<std::string, size_t>     alias_map_;
    uint64_t                                    next_id_ = 1;

    void dfs_cycle(const std::string& node,
                   std::unordered_set<std::string>& visited,
                   std::unordered_set<std::string>& in_stack,
                   std::vector<std::string>& path,
                   std::vector<std::vector<std::string>>& cycles) const
    {
        visited.insert(node);
        in_stack.insert(node);
        path.push_back(node);

        auto it = by_name_.find(node);
        if (it != by_name_.end()) {
            auto& sym = symbols_[it->second];
            for (auto& dep : sym.dependencies) {
                if (in_stack.count(dep) > 0) {
                    // Found cycle — extract it
                    std::vector<std::string> cycle;
                    auto start = std::find(path.begin(), path.end(), dep);
                    for (auto ci = start; ci != path.end(); ++ci) cycle.push_back(*ci);
                    cycle.push_back(dep);
                    cycles.push_back(cycle);
                } else if (visited.count(dep) == 0) {
                    dfs_cycle(dep, visited, in_stack, path, cycles);
                }
            }
        }

        path.pop_back();
        in_stack.erase(node);
    }

    // Extract symbol definitions from text like "Let k = c/v" or table rows
    [[nodiscard]] auto extract_symbol_from_text(const std::string& text,
                                                 const SourceLocation& loc) const
        -> std::vector<SymbolEntry>
    {
        std::vector<SymbolEntry> result;
        auto lower = detail::to_lower(text);

        // Pattern: "Let X = ..."
        for (auto& prefix : {"let ", "define "}) {
            size_t pos = lower.find(prefix);
            if (pos != std::string::npos) {
                pos += std::string(prefix).size();
                while (pos < text.size() && std::isspace(static_cast<unsigned char>(text[pos]))) ++pos;
                size_t sym_start = pos;
                while (pos < text.size() && (std::isalnum(static_cast<unsigned char>(text[pos])) ||
                       text[pos] == '_' || static_cast<unsigned char>(text[pos]) > 127)) ++pos;
                if (pos > sym_start) {
                    std::string sym_name = text.substr(sym_start, pos - sym_start);
                    if (!is_stopword(sym_name)) {
                        SymbolEntry entry;
                        entry.symbol = sym_name;
                        while (pos < text.size() && std::isspace(static_cast<unsigned char>(text[pos]))) ++pos;
                        if (pos < text.size() && text[pos] == '=') {
                            entry.definition = detail::trim(text.substr(pos + 1));
                            auto rhs_syms = extract_symbols_from_equation(entry.definition);
                            entry.dependencies = rhs_syms;
                        }
                        entry.source_location = loc;
                        entry.type = "variable";
                        result.push_back(entry);
                    }
                }
            }
        }

        // Pattern: table row with LaTeX symbols "| $\ell_P$ | Spation scale | ... | m |"
        if (!text.empty() && text[0] == '|') {
            auto cells = split_table_row(text);
            if (cells.size() >= 3) {
                std::string raw_sym = detail::trim(cells[0]);
                // Extract LaTeX symbol if present: $\ell_P$ -> l_P
                std::string sym_name = extract_latex_symbol(raw_sym);
                if (sym_name.empty()) sym_name = raw_sym;

                // Skip header rows and non-symbol entries
                if (!sym_name.empty() && !is_stopword(sym_name) &&
                    sym_name[0] != '#' && sym_name.find("---") == std::string::npos &&
                    sym_name.find("Symbol") == std::string::npos) {

                    SymbolEntry entry;
                    entry.symbol = sym_name;
                    if (cells.size() >= 2) entry.name = detail::trim(cells[1]);
                    if (cells.size() >= 3) {
                        std::string def_raw = detail::trim(cells[2]);
                        // Clean LaTeX from definition too
                        std::string def_clean = extract_latex_symbol(def_raw);
                        entry.definition = def_clean.empty() ? def_raw : def_clean;
                    }
                    if (cells.size() >= 4) entry.dimensional_signature = detail::trim(cells[3]);
                    entry.source_location = loc;
                    entry.type = "constant";
                    result.push_back(entry);
                }
            }
        }

        return result;
    }

    // Extract LaTeX symbol name from $...$
    [[nodiscard]] static auto extract_latex_symbol(const std::string& text) -> std::string {
        size_t start = text.find('$');
        if (start == std::string::npos) return "";
        size_t end = text.find('$', start + 1);
        if (end == std::string::npos) return "";
        std::string latex = text.substr(start + 1, end - start - 1);
        return EquationExtractor::clean_latex(latex);
    }

    [[nodiscard]] auto extract_symbols_from_equation(const std::string& eq) const
        -> std::vector<std::string>
    {
        std::vector<std::string> syms;
        size_t i = 0;
        while (i < eq.size()) {
            if (std::isalpha(static_cast<unsigned char>(eq[i])) ||
                static_cast<unsigned char>(eq[i]) > 127) {
                size_t start = i;
                while (i < eq.size() && (std::isalnum(static_cast<unsigned char>(eq[i])) ||
                       eq[i] == '_' || eq[i] == '\'' ||
                       static_cast<unsigned char>(eq[i]) > 127)) ++i;
                std::string name = eq.substr(start, i - start);
                if (!is_stopword(name) && !is_latex_command(name) && !is_function(name)) {
                    if (std::find(syms.begin(), syms.end(), name) == syms.end()) {
                        syms.push_back(name);
                    }
                }
            } else {
                ++i;
            }
        }
        return syms;
    }

    [[nodiscard]] static auto is_function(const std::string& name) -> bool {
        static const std::unordered_set<std::string> funcs = {
            "sqrt", "log", "ln", "exp", "sin", "cos", "tan",
            "asin", "acos", "atan", "sinh", "cosh", "tanh",
            "abs", "min", "max", "mod", "tr"
        };
        return funcs.count(name) > 0;
    }

    [[nodiscard]] static auto is_latex_command(const std::string& name) -> bool {
        static const std::unordered_set<std::string> cmds = {
            "text", "mathrm", "mathbf", "mathcal", "frac", "left", "right",
            "hat", "vec", "bar", "dot", "ddot", "tilde", "overline",
            "begin", "end", "quad", "qquad", "operatorname",
            "sum", "prod", "int", "oint", "partial", "nabla",
            "lim", "inf", "sup", "det",
            "propto", "equiv", "approx", "sim", "neq", "leq", "geq",
            "Rightarrow", "rightarrow", "leftarrow", "Leftrightarrow",
            "cdot", "times", "circ", "otimes", "oplus",
        };
        return cmds.count(name) > 0;
    }

    [[nodiscard]] static auto is_stopword(const std::string& name) -> bool {
        // Single characters that are valid symbols
        static const std::unordered_set<std::string> valid_single = {
            "c", "e", "f", "k", "m", "r", "v", "z", "E", "F", "G", "H",
            "L", "M", "N", "P", "R", "T", "V", "W", "a", "d", "g", "i",
            "n", "p", "q", "t", "u", "x", "y",
        };

        if (name.size() == 1) {
            return valid_single.count(name) == 0;
        }

        // Contains underscore → probably a subscripted symbol, always valid
        if (name.find('_') != std::string::npos) return false;

        // Known SDT symbols — always accept
        static const std::unordered_set<std::string> sdt_symbols = {
            "Phi", "phi", "tau", "alpha", "beta", "gamma", "delta", "epsilon",
            "sigma", "rho", "omega", "theta", "lambda", "mu", "nu", "pi",
            "hbar", "beth", "nabla", "Delta", "Gamma", "Omega", "Sigma",
            "inf", "Re", "Im",
            // SDT-specific compound symbols
            "W_wake", "n_hat",
        };
        if (sdt_symbols.count(name) > 0) return false;

        // English stopwords — reject
        static const std::unordered_set<std::string> stops = {
            // Articles, prepositions, conjunctions
            "the", "The", "is", "Is", "in", "In", "of", "Of", "at", "At",
            "an", "An", "on", "On", "to", "To", "by", "By", "or", "Or",
            "as", "As", "if", "If", "it", "It", "be", "Be", "do", "Do",
            "no", "No", "so", "So", "up", "Up", "we", "We", "he", "He",
            // Common English words that appear in theory prose
            "not", "has", "are", "was", "for", "but", "and", "nor", "yet",
            "all", "any", "its", "our", "his", "her", "the", "can", "may",
            "will", "that", "this", "with", "from", "they", "been", "have",
            "each", "only", "also", "more", "than", "then", "when", "what",
            "which", "where", "their", "there", "these", "those", "would",
            "could", "should", "shall", "same", "such", "just", "both",
            "does", "here", "into", "like", "must", "much", "some", "very",
            "over", "down", "even", "most", "many", "well", "back", "been",
            "will", "your", "them", "after", "about", "above", "below",
            "other", "every", "under", "again", "being", "first", "never",
            "still", "while", "since", "until", "whose", "might",
            // Theory-specific English words that aren't symbols
            "The", "This", "Derived", "locally", "from", "normal", "projection",
            "isotropic", "stress", "tensor", "equals", "geometry", "tuning",
            "Multipole", "expansion", "electric", "magnetic", "structure",
            "Nearest", "neighbour", "Transmission", "nearest", "only", "rate",
            "Shell", "lattice", "radial", "shells", "Budget", "total",
            "velocity", "always", "Convergent", "throughput", "Occlusion",
            "force", "Inertial", "mass", "Equivalence", "principle",
            "Traction", "Charge", "quantisation", "charge", "Coulomb",
            "identity", "Movement", "budget", "Time", "dilation",
            "Length", "contraction", "Rest", "energy", "Energy", "momentum",
            "Photon", "limit", "Gravitational", "boundary", "where",
            "orbital", "speed", "anisotropic", "residue", "non", "traction",
            // Additional common words
            "one", "two", "three", "four", "five", "six", "new", "old",
            "get", "set", "use", "see", "let", "say", "way", "day",
            "per", "via", "how", "why", "now", "too", "out", "own",
            "between", "through", "during", "before", "within", "without",
            "against", "because", "however", "therefore", "although",
            "whether", "either", "neither", "already", "always",
            "another", "certain", "current", "further", "general",
            "instead", "itself", "nothing", "number", "perhaps",
            "possible", "present", "problem", "result", "second",
            "several", "special", "strong", "enough", "called",
            "given", "known", "later", "makes", "means", "never",
            "point", "quite", "right", "small", "still", "taken",
            "value", "whole", "inner", "outer", "lower", "upper",
            "cancel", "next", "last", "left", "full", "free",
            "high", "long", "near", "open", "real", "true", "weak",
            "bold", "text", "else", "work", "type", "show", "form",
            "case", "need", "part", "role", "rule", "test", "unit",
            "name", "mode", "line", "kind", "fact", "data", "body",
            "area", "base",
        };

        // Check lowercase version
        auto lower = detail::to_lower(name);
        return stops.count(name) > 0 || stops.count(lower) > 0;
    }

    [[nodiscard]] static auto split_table_row(const std::string& row) -> std::vector<std::string> {
        std::vector<std::string> cells;
        size_t i = 0;
        if (!row.empty() && row[0] == '|') ++i;
        while (i < row.size()) {
            size_t end = row.find('|', i);
            if (end == std::string::npos) {
                cells.push_back(row.substr(i));
                break;
            }
            cells.push_back(row.substr(i, end - i));
            i = end + 1;
        }
        return cells;
    }
};

} // namespace sdt::compiler
