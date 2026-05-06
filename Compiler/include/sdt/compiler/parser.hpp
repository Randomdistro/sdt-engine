#pragma once

/**
 * @file parser.hpp
 * @brief Stage 0 — Input intake, classification, and equation extraction
 *
 * Parses raw Markdown/text theory input. Splits into classified items:
 * definitions, equations, claims, assumptions, conjectures, etc.
 * Detects LaTeX equations, symbol declarations, and structural elements.
 *
 * Understands SDT document conventions:
 *   - ### (N) Title  → Operator/definition heading
 *   - | # | Name | Statement/Result | → Axiom/Theorem table rows
 *   - $$ ... $$  → Display equations
 *   - $ ... $    → Inline equations
 *   - ## Prohibitions → Section context for forbidden terms
 *
 * @author SDT Theory Compiler — James Tyndall, Melbourne, Australia
 * @date May 2026
 */

#include <sdt/compiler/types.hpp>
#include <sdt/compiler/expression.hpp>

#include <string>
#include <string_view>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cctype>
#include <filesystem>
#include <regex>

namespace sdt::compiler {

// ═══════════════════════════════════════════════════════════════════════
//  STRING UTILITIES
// ═══════════════════════════════════════════════════════════════════════

namespace detail {

inline auto trim(std::string_view sv) -> std::string {
    while (!sv.empty() && std::isspace(static_cast<unsigned char>(sv.front()))) sv.remove_prefix(1);
    while (!sv.empty() && std::isspace(static_cast<unsigned char>(sv.back()))) sv.remove_suffix(1);
    return std::string(sv);
}

inline auto to_lower(std::string s) -> std::string {
    for (auto& c : s) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    return s;
}

inline auto contains_any(const std::string& haystack, const std::vector<std::string>& needles) -> bool {
    auto lower = to_lower(haystack);
    for (auto& n : needles) {
        if (lower.find(n) != std::string::npos) return true;
    }
    return false;
}

inline auto starts_with(std::string_view sv, std::string_view prefix) -> bool {
    return sv.size() >= prefix.size() && sv.substr(0, prefix.size()) == prefix;
}

inline auto strip_markdown(const std::string& s) -> std::string {
    std::string out;
    out.reserve(s.size());
    size_t i = 0;
    while (i < s.size()) {
        if (s[i] == '`') { ++i; continue; }
        if (s[i] == '*' || s[i] == '_') { ++i; continue; }
        out += s[i++];
    }
    return out;
}

} // namespace detail

// ═══════════════════════════════════════════════════════════════════════
//  EQUATION EXTRACTOR
// ═══════════════════════════════════════════════════════════════════════

struct ExtractedEquation {
    std::string raw_latex;
    std::string cleaned;
    int         line = 0;
    bool        is_display = false;
};

class EquationExtractor {
public:
    [[nodiscard]] auto extract(const std::string& text) const -> std::vector<ExtractedEquation> {
        std::vector<ExtractedEquation> results;
        int line = 1;
        size_t i = 0;

        while (i < text.size()) {
            if (text[i] == '\n') { ++line; ++i; continue; }

            // Display math: $$ ... $$
            if (i + 1 < text.size() && text[i] == '$' && text[i + 1] == '$') {
                size_t content_start = i + 2;
                auto eq = extract_delimited(text, content_start, "$$", line);
                if (eq) {
                    eq->is_display = true;
                    results.push_back(std::move(*eq));
                    i = content_start;
                } else {
                    i += 2;
                }
                continue;
            }

            // Display math: \[ ... \]
            if (i + 1 < text.size() && text[i] == '\\' && text[i + 1] == '[') {
                size_t content_start = i + 2;
                auto eq = extract_delimited(text, content_start, "\\]", line);
                if (eq) {
                    eq->is_display = true;
                    results.push_back(std::move(*eq));
                    i = content_start;
                } else {
                    i += 2;
                }
                continue;
            }

            // Inline math: $ ... $ (not $$)
            if (text[i] == '$' && (i + 1 >= text.size() || text[i + 1] != '$')) {
                size_t content_start = i + 1;
                auto eq = extract_delimited(text, content_start, "$", line);
                if (eq) {
                    eq->is_display = false;
                    results.push_back(std::move(*eq));
                    i = content_start;
                } else {
                    i += 1;
                }
                continue;
            }

            ++i;
        }
        return results;
    }

    [[nodiscard]] static auto clean_latex(const std::string& latex) -> std::string {
        std::string s = latex;
        auto remove_cmd = [&](const std::string& cmd) {
            size_t pos;
            while ((pos = s.find(cmd)) != std::string::npos) {
                s.erase(pos, cmd.size());
            }
        };
        remove_cmd("\\left");
        remove_cmd("\\right");
        remove_cmd("\\cdot");
        remove_cmd("\\times");
        remove_cmd("\\text{");
        remove_cmd("\\mathrm{");
        remove_cmd("\\mathbf{");

        // Replace \frac{A}{B} with (A)/(B)
        size_t pos = 0;
        while ((pos = s.find("\\frac", pos)) != std::string::npos) {
            s.erase(pos, 5);
            if (pos < s.size() && s[pos] == '{') {
                auto [num, end1] = extract_braced(s, pos);
                s.erase(pos, end1 - pos);
                s.insert(pos, "(" + num + ")/");
                pos += num.size() + 3;
                if (pos < s.size() && s[pos] == '{') {
                    auto [den, end2] = extract_braced(s, pos);
                    s.erase(pos, end2 - pos);
                    s.insert(pos, "(" + den + ")");
                    pos += den.size() + 2;
                }
            }
        }

        // Replace \sqrt{X} with sqrt(X)
        pos = 0;
        while ((pos = s.find("\\sqrt", pos)) != std::string::npos) {
            s.erase(pos, 5);
            if (pos < s.size() && s[pos] == '{') {
                auto [content, end] = extract_braced(s, pos);
                s.erase(pos, end - pos);
                s.insert(pos, "sqrt(" + content + ")");
                pos += content.size() + 6;
            }
        }

        // Handle ^{exponent}
        pos = 0;
        while ((pos = s.find('^', pos)) != std::string::npos) {
            if (pos + 1 < s.size() && s[pos + 1] == '{') {
                auto [exp_content, end] = extract_braced(s, pos + 1);
                s.erase(pos + 1, end - pos - 1);
                s.insert(pos + 1, exp_content);
            }
            ++pos;
        }

        // Remove remaining { and }
        s.erase(std::remove(s.begin(), s.end(), '{'), s.end());
        s.erase(std::remove(s.begin(), s.end(), '}'), s.end());

        // Replace Greek with ASCII
        auto replace_all = [&](const std::string& from, const std::string& to) {
            size_t p = 0;
            while ((p = s.find(from, p)) != std::string::npos) {
                s.replace(p, from.size(), to);
                p += to.size();
            }
        };
        replace_all("\\alpha",      "alpha");
        replace_all("\\beta",       "beta");
        replace_all("\\gamma",      "gamma");
        replace_all("\\delta",      "delta");
        replace_all("\\epsilon",    "epsilon");
        replace_all("\\varepsilon", "epsilon");
        replace_all("\\Phi",        "Phi");
        replace_all("\\phi",        "phi");
        replace_all("\\pi",         "pi");
        replace_all("\\tau",        "tau");
        replace_all("\\sigma",      "sigma");
        replace_all("\\rho",        "rho");
        replace_all("\\omega",      "omega");
        replace_all("\\hbar",       "hbar");
        replace_all("\\ell",        "l");
        replace_all("\\infty",      "inf");
        replace_all("\\leq",        "<=");
        replace_all("\\geq",        ">=");
        replace_all("\\neq",        "!=");
        replace_all("\\approx",     "~=");
        replace_all("\\equiv",      "==");
        replace_all("\\Rightarrow", "=>");
        replace_all("\\rightarrow", "->");
        replace_all("\\hat{n}",     "n_hat");
        replace_all("\\hat",        "");
        replace_all("\\mathcal{W}", "W_wake");
        replace_all("\\mathcal",    "");
        replace_all("\\beth",       "beth");
        replace_all("\\nabla",      "nabla");
        replace_all("\\Delta",      "Delta");
        replace_all("\\propto",     "propto");
        replace_all("\\qquad",      " ");
        replace_all("\\quad",       " ");
        replace_all("\\,",          " ");
        replace_all("\\;",          " ");

        return detail::trim(s);
    }

private:
    auto extract_delimited(const std::string& text, size_t& start, const std::string& end_delim,
                           int& line) const -> std::optional<ExtractedEquation> {
        size_t end = text.find(end_delim, start);
        if (end == std::string::npos) return std::nullopt;

        ExtractedEquation eq;
        eq.raw_latex = text.substr(start, end - start);
        eq.cleaned = clean_latex(eq.raw_latex);
        eq.line = line;

        for (size_t j = start; j < end + end_delim.size(); ++j) {
            if (text[j] == '\n') ++line;
        }
        start = end + end_delim.size();
        return eq;
    }

    static auto extract_braced(const std::string& s, size_t pos) -> std::pair<std::string, size_t> {
        if (pos >= s.size() || s[pos] != '{') return {"", pos};
        int depth = 0;
        size_t start = pos + 1;
        size_t i = pos;
        while (i < s.size()) {
            if (s[i] == '{') ++depth;
            else if (s[i] == '}') { --depth; if (depth == 0) return {s.substr(start, i - start), i + 1}; }
            ++i;
        }
        return {s.substr(start), s.size()};
    }
};

// ═══════════════════════════════════════════════════════════════════════
//  CLASSIFIER — SDT-aware document structure recognition
// ═══════════════════════════════════════════════════════════════════════

class ItemClassifier {
public:
    [[nodiscard]] auto classify(const std::string& text, const std::string& section) const
        -> std::pair<InputClass, double>
    {
        auto lower = detail::to_lower(text);
        auto section_lower = detail::to_lower(section);

        // ── Section-context-aware classification ──

        // Items under "Axiom" sections are axioms
        if (section_lower.find("axiom") != std::string::npos) {
            if (text[0] == '|') return {InputClass::AXIOM, 0.95};
            return {InputClass::AXIOM, 0.85};
        }

        // Items under "Theorem" sections are derivation steps
        if (section_lower.find("theorem") != std::string::npos) {
            if (text[0] == '|') return {InputClass::DERIVATION_STEP, 0.95};
            return {InputClass::DERIVATION_STEP, 0.85};
        }

        // Items under "Prohibition" sections are terminology declarations
        if (section_lower.find("prohibit") != std::string::npos ||
            section_lower.find("forbidden") != std::string::npos) {
            return {InputClass::TERMINOLOGY, 0.9};
        }

        // Items under "Notation" or "Primary Symbols" are definitions
        if (section_lower.find("notation") != std::string::npos ||
            section_lower.find("symbol") != std::string::npos ||
            section_lower.find("primary") != std::string::npos) {
            if (text[0] == '|') return {InputClass::DEFINITION, 0.95};
            return {InputClass::DEFINITION, 0.85};
        }

        // Items under "Certification" are terminology
        if (section_lower.find("certification") != std::string::npos ||
            section_lower.find("label") != std::string::npos) {
            return {InputClass::TERMINOLOGY, 0.85};
        }

        // Items under "Independent Inputs" / "Measured" are empirical anchors
        if (section_lower.find("input") != std::string::npos ||
            section_lower.find("measured") != std::string::npos) {
            if (text[0] == '|') return {InputClass::EMPIRICAL_ANCHOR, 0.9};
            return {InputClass::EMPIRICAL_ANCHOR, 0.8};
        }

        // Items under "Derived Quantities" / "Stage" are derivation steps
        if (section_lower.find("derived") != std::string::npos ||
            section_lower.find("stage") != std::string::npos) {
            if (text[0] == '|') return {InputClass::DERIVATION_STEP, 0.9};
            return {InputClass::DERIVATION_STEP, 0.8};
        }

        // Items under "Open Problems" are conjectures
        if (section_lower.find("open problem") != std::string::npos ||
            section_lower.find("conjecture") != std::string::npos) {
            return {InputClass::CONJECTURE, 0.85};
        }

        // Items under "Falsifiable" / "Prediction" are claims
        if (section_lower.find("falsif") != std::string::npos ||
            section_lower.find("prediction") != std::string::npos) {
            return {InputClass::CLAIM, 0.9};
        }

        // Items under "Closure" are derivation steps
        if (section_lower.find("closure") != std::string::npos) {
            return {InputClass::DERIVATION_STEP, 0.85};
        }

        // Items under "Wake" / "Modal" / "Topology" / "Coulomb" are derivation steps
        if (section_lower.find("wake") != std::string::npos ||
            section_lower.find("modal") != std::string::npos ||
            section_lower.find("topology") != std::string::npos ||
            section_lower.find("coulomb") != std::string::npos ||
            section_lower.find("radius") != std::string::npos) {
            return {InputClass::DERIVATION_STEP, 0.8};
        }

        // Items under "Bridge" are bridge invariants
        if (section_lower.find("bridge") != std::string::npos) {
            return {InputClass::EQUATION, 0.85};
        }

        // Items under "State28D" / "Levels" are definitions
        if (section_lower.find("state") != std::string::npos ||
            section_lower.find("level") != std::string::npos) {
            return {InputClass::DEFINITION, 0.8};
        }

        // ── Content-based classification (fallback) ──

        // Numbered subsection headings like "### (1) ..." are operator definitions
        if (lower.find("irreducible") != std::string::npos ||
            lower.find("operator") != std::string::npos) {
            return {InputClass::AXIOM, 0.9};
        }

        // Axiom indicators
        if (detail::contains_any(lower, {"axiom", "postulate", "we assume", "fundamental assumption"})) {
            return {InputClass::AXIOM, 0.9};
        }

        // Definition indicators
        if (detail::contains_any(lower, {"is defined as", "we define", "let ", "define ", ":="})) {
            return {InputClass::DEFINITION, 0.85};
        }

        // Equation (pure math)
        if (text.find('=') != std::string::npos) {
            int alpha_count = 0, op_count = 0;
            for (char c : text) {
                if (std::isalpha(static_cast<unsigned char>(c))) ++alpha_count;
                if (c == '=' || c == '+' || c == '-' || c == '*' || c == '/' || c == '^') ++op_count;
            }
            if (op_count > 0 && alpha_count < static_cast<int>(text.size()) * 0.7) {
                return {InputClass::EQUATION, 0.8};
            }
        }

        // Derivation step indicators
        if (detail::contains_any(lower, {"therefore", "thus", "hence", "it follows", "we get",
                                         "substituting", "rearranging", "from above",
                                         "consequence", "from the", "derived", "collapses"})) {
            return {InputClass::DERIVATION_STEP, 0.75};
        }

        // Empirical anchor
        if (detail::contains_any(lower, {"measured", "codata", "nist", "observed", "experimental",
                                         "measurement", "firas", "iau", "agreement"})) {
            return {InputClass::EMPIRICAL_ANCHOR, 0.8};
        }

        // Conjecture
        if (detail::contains_any(lower, {"conjecture", "hypothesis", "speculate",
                                         "might", "could be", "possibly", "if correct"})) {
            return {InputClass::CONJECTURE, 0.7};
        }

        // Assumption
        if (detail::contains_any(lower, {"assume", "assumption", "suppose", "given that",
                                         "if we take", "taking"})) {
            return {InputClass::ASSUMPTION, 0.7};
        }

        // Claim
        if (detail::contains_any(lower, {"this shows", "this proves", "we conclude", "this implies",
                                         "predicts", "prediction", "result:", "falsification"})) {
            return {InputClass::CLAIM, 0.7};
        }

        // Analogy
        if (detail::contains_any(lower, {"analogous to", "similar to", "just as",
                                         "reminiscent of", "in the same way"})) {
            return {InputClass::ANALOGY, 0.65};
        }

        // Metaphor
        if (detail::contains_any(lower, {"metaphor", "think of it as", "picture", "imagine",
                                         "as if"})) {
            return {InputClass::METAPHOR, 0.6};
        }

        // Terminology
        if (detail::contains_any(lower, {"terminology", "we call", "referred to as", "known as",
                                         "denoted by", "the term"})) {
            return {InputClass::TERMINOLOGY, 0.7};
        }

        return {InputClass::INVALID_OR_AMBIGUOUS, 0.3};
    }
};

// ═══════════════════════════════════════════════════════════════════════
//  THEORY PARSER — SDT-aware document structure
// ═══════════════════════════════════════════════════════════════════════

class TheoryParser {
public:
    [[nodiscard]] auto parse_file(const std::filesystem::path& path) -> ParsedTheory {
        std::ifstream f(path);
        if (!f.is_open()) return {};
        std::ostringstream ss;
        ss << f.rdbuf();
        return parse_string(ss.str(), path.string());
    }

    [[nodiscard]] auto parse_string(const std::string& text,
                                     const std::string& source_file = "<input>") -> ParsedTheory
    {
        ParsedTheory result;
        std::string current_section;
        std::string current_subsection;
        int line_num = 0;

        std::istringstream stream(text);
        std::string line;
        std::string pending_block;
        bool in_code_block = false;

        while (std::getline(stream, line)) {
            ++line_num;
            auto trimmed = detail::trim(line);

            // Track code blocks (skip them)
            if (detail::starts_with(trimmed, "```")) {
                in_code_block = !in_code_block;
                continue;
            }
            if (in_code_block) continue;

            // Track section headings — build hierarchical context
            if (!trimmed.empty() && trimmed[0] == '#') {
                // Flush pending
                if (!pending_block.empty()) {
                    flush_block(pending_block, source_file, line_num - 1, current_section, result);
                    pending_block.clear();
                }

                int level = 0;
                while (level < static_cast<int>(trimmed.size()) && trimmed[level] == '#') ++level;
                auto heading = detail::trim(trimmed.substr(level));

                if (level <= 2) {
                    current_section = heading;
                    current_subsection.clear();
                } else {
                    current_subsection = heading;
                    // Subsection headings like "### (1) Continuous throughput" are definitions
                    // Check for numbered operator pattern
                    if (heading.find('(') != std::string::npos && heading.find(')') != std::string::npos) {
                        // This is an operator definition heading — the next $$ block is its equation
                        ClassifiedItem item;
                        item.classification = InputClass::DEFINITION;
                        item.raw_text = heading;
                        item.normalised = detail::strip_markdown(heading);
                        item.location = {source_file, line_num, 0, current_section};
                        item.level = ValidationLevel::PARSED;
                        item.confidence = 0.9;
                        result.definitions.push_back(item);
                        result.all_items.push_back(item);
                    }
                }
                continue;
            }

            // Horizontal rules
            if (trimmed == "---" || trimmed == "***" || trimmed == "___") {
                if (!pending_block.empty()) {
                    flush_block(pending_block, source_file, line_num - 1, current_section, result);
                    pending_block.clear();
                }
                continue;
            }

            // Empty lines flush
            if (trimmed.empty()) {
                if (!pending_block.empty()) {
                    flush_block(pending_block, source_file, line_num - 1, current_section, result);
                    pending_block.clear();
                }
                continue;
            }

            // Table rows: | ... | ... |
            if (trimmed[0] == '|') {
                if (!pending_block.empty()) {
                    flush_block(pending_block, source_file, line_num - 1, current_section, result);
                    pending_block.clear();
                }
                // Skip separator rows
                if (trimmed.find("---") != std::string::npos) continue;
                // Skip header rows (first row after section heading)
                if (trimmed.find("Symbol") != std::string::npos ||
                    trimmed.find("Axiom") != std::string::npos ||
                    trimmed.find("Theorem") != std::string::npos ||
                    trimmed.find("Constant") != std::string::npos ||
                    trimmed.find("Quantity") != std::string::npos ||
                    trimmed.find("Label") != std::string::npos ||
                    trimmed.find("Meaning") != std::string::npos ||
                    trimmed.find("Genus") != std::string::npos ||
                    trimmed.find("Components") != std::string::npos ||
                    trimmed.find("Level") != std::string::npos ||
                    trimmed.find("Prediction") != std::string::npos) continue;

                // Classify the table row using section context
                classify_and_add(trimmed, source_file, line_num, current_section, result);
                continue;
            }

            // Bullet list items
            if (trimmed[0] == '-' || trimmed[0] == '*') {
                if (!pending_block.empty()) {
                    flush_block(pending_block, source_file, line_num - 1, current_section, result);
                    pending_block.clear();
                }
                auto bullet_text = detail::trim(trimmed.substr(1));
                classify_and_add(bullet_text, source_file, line_num, current_section, result);
                continue;
            }

            // Accumulate paragraph text
            if (!pending_block.empty()) pending_block += " ";
            pending_block += trimmed;
        }

        // Flush final block
        if (!pending_block.empty()) {
            flush_block(pending_block, source_file, line_num, current_section, result);
        }

        // Extract equations from full text (LaTeX)
        EquationExtractor eq_ext;
        auto equations = eq_ext.extract(text);
        for (auto& eq : equations) {
            ClassifiedItem item;
            item.classification = InputClass::EQUATION;
            item.raw_text = eq.raw_latex;
            item.normalised = eq.cleaned;
            item.location = {source_file, eq.line, 0, ""};
            item.level = ValidationLevel::PARSED;
            item.confidence = 0.9;
            result.equations.push_back(item);
            result.all_items.push_back(item);
        }

        return result;
    }

private:
    ItemClassifier classifier_;

    void flush_block(const std::string& block, const std::string& file,
                     int line, const std::string& section, ParsedTheory& result) {
        classify_and_add(block, file, line, section, result);
    }

    void classify_and_add(const std::string& text, const std::string& file,
                          int line, const std::string& section, ParsedTheory& result) {
        if (text.empty()) return;

        ClassifiedItem item;
        item.raw_text = text;
        item.normalised = detail::strip_markdown(text);
        item.location = {file, line, 0, section};
        item.level = ValidationLevel::PARSED;

        auto [cls, conf] = classifier_.classify(text, section);
        item.classification = cls;
        item.confidence = conf;

        // Route to appropriate bucket
        switch (cls) {
            case InputClass::DEFINITION:      result.definitions.push_back(item); break;
            case InputClass::EQUATION:        result.equations.push_back(item); break;
            case InputClass::CLAIM:
            case InputClass::DERIVATION_STEP: result.claims.push_back(item); break;
            case InputClass::ASSUMPTION:
            case InputClass::AXIOM:           result.assumptions.push_back(item); break;
            case InputClass::CONJECTURE:      result.conjectures.push_back(item); break;
            case InputClass::EMPIRICAL_ANCHOR: result.assumptions.push_back(item); break;
            default:                          result.ambiguous_items.push_back(item); break;
        }

        result.all_items.push_back(item);
    }
};

} // namespace sdt::compiler
