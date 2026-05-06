#pragma once

/**
 * @file types.hpp
 * @brief Core data structures and enumerations for the Theory Compiler
 *
 * Every module in the compiler pipeline shares these types.
 * No module may define its own classification or status enums.
 *
 * @author SDT Theory Compiler — James Tyndall, Melbourne, Australia
 * @date May 2026
 */

#include <cstdint>
#include <string>
#include <vector>
#include <optional>
#include <unordered_map>
#include <array>
#include <variant>

namespace sdt::compiler {

// ═══════════════════════════════════════════════════════════════════════
//  INPUT CLASSIFICATION
// ═══════════════════════════════════════════════════════════════════════

enum class InputClass : uint8_t {
    AXIOM,
    DEFINITION,
    EQUATION,
    CLAIM,
    DERIVATION_STEP,
    EMPIRICAL_ANCHOR,
    ASSUMPTION,
    CONJECTURE,
    ANALOGY,
    METAPHOR,
    TERMINOLOGY,
    INVALID_OR_AMBIGUOUS,
    COUNT_
};

[[nodiscard]] inline auto input_class_str(InputClass c) noexcept -> const char* {
    switch (c) {
        case InputClass::AXIOM:                return "AXIOM";
        case InputClass::DEFINITION:           return "DEFINITION";
        case InputClass::EQUATION:             return "EQUATION";
        case InputClass::CLAIM:                return "CLAIM";
        case InputClass::DERIVATION_STEP:      return "DERIVATION_STEP";
        case InputClass::EMPIRICAL_ANCHOR:     return "EMPIRICAL_ANCHOR";
        case InputClass::ASSUMPTION:           return "ASSUMPTION";
        case InputClass::CONJECTURE:           return "CONJECTURE";
        case InputClass::ANALOGY:              return "ANALOGY";
        case InputClass::METAPHOR:             return "METAPHOR";
        case InputClass::TERMINOLOGY:          return "TERMINOLOGY";
        case InputClass::INVALID_OR_AMBIGUOUS: return "INVALID_OR_AMBIGUOUS";
        default:                               return "UNKNOWN";
    }
}

// ═══════════════════════════════════════════════════════════════════════
//  VALIDATION LEVELS (0–8)
// ═══════════════════════════════════════════════════════════════════════

enum class ValidationLevel : uint8_t {
    UNPARSED           = 0,   // Text exists, not structured
    PARSED             = 1,   // Symbols and claims identified
    DEFINED            = 2,   // All terms defined
    DIMENSIONALLY_VALID = 3,  // Equation passes unit/dimension check
    DERIVATION_LINKED  = 4,   // Claim traces to prior definitions/equations
    REPRODUCIBLE       = 5,   // System can regenerate from kernel
    EMPIRICALLY_ANCHORED = 6, // Matches measured data
    PREDICTIVE         = 7,   // Produces result not used as input
    FALSIFIABLE        = 8,   // Clear failure condition exists
};

[[nodiscard]] inline auto validation_level_str(ValidationLevel v) noexcept -> const char* {
    switch (v) {
        case ValidationLevel::UNPARSED:            return "UNPARSED";
        case ValidationLevel::PARSED:              return "PARSED";
        case ValidationLevel::DEFINED:             return "DEFINED";
        case ValidationLevel::DIMENSIONALLY_VALID: return "DIMENSIONALLY_VALID";
        case ValidationLevel::DERIVATION_LINKED:   return "DERIVATION_LINKED";
        case ValidationLevel::REPRODUCIBLE:        return "REPRODUCIBLE";
        case ValidationLevel::EMPIRICALLY_ANCHORED:return "EMPIRICALLY_ANCHORED";
        case ValidationLevel::PREDICTIVE:          return "PREDICTIVE";
        case ValidationLevel::FALSIFIABLE:         return "FALSIFIABLE";
        default:                                   return "UNKNOWN";
    }
}

// ═══════════════════════════════════════════════════════════════════════
//  SYMBOL STATUS
// ═══════════════════════════════════════════════════════════════════════

enum class SymbolStatus : uint8_t {
    UNLOCKED,
    LOCKED,
    DERIVED,
    UNRESOLVED,
};

[[nodiscard]] inline auto symbol_status_str(SymbolStatus s) noexcept -> const char* {
    switch (s) {
        case SymbolStatus::UNLOCKED:   return "unlocked";
        case SymbolStatus::LOCKED:     return "locked";
        case SymbolStatus::DERIVED:    return "derived";
        case SymbolStatus::UNRESOLVED: return "unresolved";
        default:                       return "unknown";
    }
}

// ═══════════════════════════════════════════════════════════════════════
//  FAILURE CATEGORIES
// ═══════════════════════════════════════════════════════════════════════

enum class FailureCategory : uint8_t {
    UNDEFINED_SYMBOL,
    SYMBOL_DRIFT,
    DIMENSION_FAIL,
    HIDDEN_ASSUMPTION,
    CIRCULAR_DERIVATION,
    MISSING_BRIDGE_INVARIANT,
    EMPIRICAL_SMUGGLING,
    ANALOGY_AS_PROOF,
    FORBIDDEN_CONCEPT_REINTRODUCTION,
    NON_REPRODUCIBLE_RESULT,
    CLAIM_EXCEEDS_VALIDATION_LEVEL,
    VERSION_MUTATION_ERROR,
    COUNT_
};

[[nodiscard]] inline auto failure_category_str(FailureCategory f) noexcept -> const char* {
    switch (f) {
        case FailureCategory::UNDEFINED_SYMBOL:                  return "UNDEFINED_SYMBOL";
        case FailureCategory::SYMBOL_DRIFT:                      return "SYMBOL_DRIFT";
        case FailureCategory::DIMENSION_FAIL:                    return "DIMENSION_FAIL";
        case FailureCategory::HIDDEN_ASSUMPTION:                 return "HIDDEN_ASSUMPTION";
        case FailureCategory::CIRCULAR_DERIVATION:               return "CIRCULAR_DERIVATION";
        case FailureCategory::MISSING_BRIDGE_INVARIANT:          return "MISSING_BRIDGE_INVARIANT";
        case FailureCategory::EMPIRICAL_SMUGGLING:               return "EMPIRICAL_SMUGGLING";
        case FailureCategory::ANALOGY_AS_PROOF:                  return "ANALOGY_AS_PROOF";
        case FailureCategory::FORBIDDEN_CONCEPT_REINTRODUCTION:  return "FORBIDDEN_CONCEPT_REINTRODUCTION";
        case FailureCategory::NON_REPRODUCIBLE_RESULT:           return "NON_REPRODUCIBLE_RESULT";
        case FailureCategory::CLAIM_EXCEEDS_VALIDATION_LEVEL:    return "CLAIM_EXCEEDS_VALIDATION_LEVEL";
        case FailureCategory::VERSION_MUTATION_ERROR:             return "VERSION_MUTATION_ERROR";
        default:                                                  return "UNKNOWN";
    }
}

// ═══════════════════════════════════════════════════════════════════════
//  SEVERITY
// ═══════════════════════════════════════════════════════════════════════

enum class Severity : uint8_t {
    LOW,
    MEDIUM,
    HIGH,
    FATAL,
};

[[nodiscard]] inline auto severity_str(Severity s) noexcept -> const char* {
    switch (s) {
        case Severity::LOW:    return "low";
        case Severity::MEDIUM: return "medium";
        case Severity::HIGH:   return "high";
        case Severity::FATAL:  return "fatal";
        default:               return "unknown";
    }
}

// ═══════════════════════════════════════════════════════════════════════
//  EQUATION VALIDATION STATUS
// ═══════════════════════════════════════════════════════════════════════

enum class EqStatus : uint8_t {
    PASS,
    FAIL,
    UNRESOLVED,
};

[[nodiscard]] inline auto eq_status_str(EqStatus s) noexcept -> const char* {
    switch (s) {
        case EqStatus::PASS:       return "pass";
        case EqStatus::FAIL:       return "fail";
        case EqStatus::UNRESOLVED: return "unresolved";
        default:                   return "unknown";
    }
}

// ═══════════════════════════════════════════════════════════════════════
//  BRIDGE STATUS
// ═══════════════════════════════════════════════════════════════════════

enum class BridgeStatus : uint8_t {
    VALIDATED,
    CONJECTURAL,
    MISSING,
};

[[nodiscard]] inline auto bridge_status_str(BridgeStatus s) noexcept -> const char* {
    switch (s) {
        case BridgeStatus::VALIDATED:   return "validated";
        case BridgeStatus::CONJECTURAL: return "conjectural";
        case BridgeStatus::MISSING:     return "missing";
        default:                        return "unknown";
    }
}

// ═══════════════════════════════════════════════════════════════════════
//  TRANSFORMATION TYPES
// ═══════════════════════════════════════════════════════════════════════

enum class TransformKind : uint8_t {
    ALGEBRAIC_REARRANGEMENT,
    SUBSTITUTION,
    DIMENSIONAL_REDUCTION,
    LIMIT_OPERATION,
    GEOMETRIC_PROJECTION,
    RATIO_CONVERSION,
    LOGARITHMIC_TRANSFORM,
    NUMERICAL_EVALUATION,
    EMPIRICAL_CALIBRATION,
    APPROXIMATION,
    COUNT_
};

[[nodiscard]] inline auto transform_kind_str(TransformKind t) noexcept -> const char* {
    switch (t) {
        case TransformKind::ALGEBRAIC_REARRANGEMENT: return "algebraic_rearrangement";
        case TransformKind::SUBSTITUTION:            return "substitution";
        case TransformKind::DIMENSIONAL_REDUCTION:   return "dimensional_reduction";
        case TransformKind::LIMIT_OPERATION:         return "limit_operation";
        case TransformKind::GEOMETRIC_PROJECTION:    return "geometric_projection";
        case TransformKind::RATIO_CONVERSION:        return "ratio_conversion";
        case TransformKind::LOGARITHMIC_TRANSFORM:   return "logarithmic_transform";
        case TransformKind::NUMERICAL_EVALUATION:    return "numerical_evaluation";
        case TransformKind::EMPIRICAL_CALIBRATION:   return "empirical_calibration";
        case TransformKind::APPROXIMATION:           return "approximation";
        default:                                     return "unknown";
    }
}

// ═══════════════════════════════════════════════════════════════════════
//  STATE28D — 28-Dimensional Aspect Model
//  Reference: Engine/include/sdt/state28d.hpp (canonical)
//
//  7 hierarchical levels: 1+2+3+4+5+6+7 = 28 aspects
//  Every physical object in SDT lives in this manifold.
// ═══════════════════════════════════════════════════════════════════════

enum class State28DLevel : uint8_t {
    ZERO_POINT  = 1,   // Existence                    (1 aspect)
    LINE        = 2,   // Position + Velocity           (2 aspects)
    PLANE       = 3,   // Boundaries + Rotation         (3 aspects)
    SPHERE      = 4,   // Volume + Orientation          (4 aspects)
    TORUS       = 5,   // Matter Structure (Topology)   (5 aspects)
    DYNAMISM    = 6,   // Time Evolution (Dynamics)     (6 aspects)
    ENERGY      = 7,   // Force Manifestation (Physics) (7 aspects)
};

[[nodiscard]] inline auto state28d_level_str(State28DLevel l) noexcept -> const char* {
    switch (l) {
        case State28DLevel::ZERO_POINT: return "Zero-Point (Existence)";
        case State28DLevel::LINE:       return "Line (Position + Velocity)";
        case State28DLevel::PLANE:      return "Plane (Boundaries + Rotation)";
        case State28DLevel::SPHERE:     return "Sphere (Volume + Orientation)";
        case State28DLevel::TORUS:      return "Torus (Matter Structure)";
        case State28DLevel::DYNAMISM:   return "Dynamism (Time Evolution)";
        case State28DLevel::ENERGY:     return "Energy (Force Manifestation)";
        default:                        return "UNKNOWN";
    }
}

struct State28DAspect {
    int             index;          // 0-27
    State28DLevel   level;
    std::string     field_name;     // C++ field name from state28d.hpp
    std::string     symbol;         // LaTeX-cleaned symbol
    std::string     name;           // Human description
    std::string     dimension_str;  // SI dimension string
    std::string     unit_hint;      // Expected unit
};

// The canonical 28 aspects, mirroring Engine/include/sdt/state28d.hpp
inline auto state28d_aspects() -> const std::vector<State28DAspect>& {
    static const std::vector<State28DAspect> aspects = {
        // ── Level 1: Zero-Point (1 aspect) ──
        { 0, State28DLevel::ZERO_POINT, "xi_0", "xi_0", "Existence — baseline presence in spation medium", "1", "dimensionless"},

        // ── Level 2: Line (2 aspects) ──
        { 1, State28DLevel::LINE, "xi_10", "xi_10", "Location — position along axis", "L", "m"},
        { 2, State28DLevel::LINE, "xi_11", "xi_11", "Relocation — linear velocity",   "L T^-1", "m/s"},

        // ── Level 3: Plane (3 aspects) ──
        { 3, State28DLevel::PLANE, "xi_p0", "xi_p0", "Internal existence — planar boundary (within/without)", "1", "dimensionless"},
        { 4, State28DLevel::PLANE, "xi_p1", "xi_p1", "Planar relocation — position within plane",             "L^2", "m^2"},
        { 5, State28DLevel::PLANE, "xi_p2", "xi_p2", "Planar rotation — orientation in plane",                "1", "rad"},

        // ── Level 4: Sphere (4 aspects) ──
        { 6, State28DLevel::SPHERE, "xi_s0", "xi_s0", "Shell existence — volumetric presence",   "L^3", "m^3"},
        { 7, State28DLevel::SPHERE, "xi_s1", "xi_s1", "Shell relocation — motion within volume", "L^3 T^-1", "m^3/s"},
        { 8, State28DLevel::SPHERE, "xi_s2", "xi_s2", "Shell rotation — rotational state",       "T^-1", "rad/s"},
        { 9, State28DLevel::SPHERE, "xi_s3", "xi_s3", "Orientation — axis direction",             "1", "unit vector"},

        // ── Level 5: Torus (5 aspects) — MATTER STRUCTURE ──
        {10, State28DLevel::TORUS, "T_1", "T_1", "Central ring — constriction line, max compression",         "L", "m"},
        {11, State28DLevel::TORUS, "T_2", "T_2", "Tube diameter — vortex thickness",                          "L", "m"},
        {12, State28DLevel::TORUS, "T_3", "T_3", "Topological surface — 2D boundary",                         "L^2", "m^2"},
        {13, State28DLevel::TORUS, "T_4", "T_4", "Polarised volume — central aperture + pressure gradient",   "M L^-1 T^-2 L^3", "m^3 Pa"},
        {14, State28DLevel::TORUS, "T_5", "T_5", "Aspect gradation — internal pressure/density gradient",     "M L^-2 T^-2", "Pa/m"},

        // ── Level 6: Dynamism (6 aspects) — TIME EVOLUTION ──
        {15, State28DLevel::DYNAMISM, "Phi_0", "Phi_0", "Omnidirectionality — all surface vectors",                         "1", "sr"},
        {16, State28DLevel::DYNAMISM, "Phi_1", "Phi_1", "Dynamic translocation — higher-order rates",                       "L T^-2", "m/s^2"},
        {17, State28DLevel::DYNAMISM, "Phi_2", "Phi_2", "Oscillation — periodic reversal/precession",                       "T^-1", "Hz"},
        {18, State28DLevel::DYNAMISM, "Phi_3", "Phi_3", "Inversion/chirality — handedness",                                 "1", "±1"},
        {19, State28DLevel::DYNAMISM, "Phi_4", "Phi_4", "State trajectory variance — potential from external influence",     "1", "dimensionless"},
        {20, State28DLevel::DYNAMISM, "Phi_5", "Phi_5", "Phase transition — potential for structural change",                "M L^2 T^-2", "J"},

        // ── Level 7: Energy (7 aspects) — FORCE MANIFESTATION ──
        {21, State28DLevel::ENERGY, "eps_0", "eps_0", "Potential — energy of position/configuration",     "M L^2 T^-2", "J"},
        {22, State28DLevel::ENERGY, "eps_1", "eps_1", "Kinetic — energy of bulk motion",                  "M L^2 T^-2", "J"},
        {23, State28DLevel::ENERGY, "eps_2", "eps_2", "Rotational — energy of unencumbered motion",       "M L^2 T^-2", "J"},
        {24, State28DLevel::ENERGY, "eps_3", "eps_3", "Field — energy in pressure-occlusion field",       "M L^2 T^-2", "J"},
        {25, State28DLevel::ENERGY, "eps_b", "eps_b", "Binding energy — energy to decohere structure",    "M L^2 T^-2", "J"},
        {26, State28DLevel::ENERGY, "eps_4", "eps_4", "Flux — rate of energy transfer",                   "M L^2 T^-3", "W"},
        {27, State28DLevel::ENERGY, "eps_5", "eps_5", "Transmission — mechanical transfer",               "M L^2 T^-2", "J"},
    };
    return aspects;
}

// ── Theory Symbol → State28D Aspect Mapping ──
// The theory files use physics symbol names, not raw field names.
// This map bridges: theory symbol → State28D aspect index.
// Multiple theory symbols may exercise the same aspect.

struct State28DMapping {
    std::string theory_symbol;
    int         aspect_index;
    std::string rationale;
};

inline auto state28d_mappings() -> const std::vector<State28DMapping>& {
    static const std::vector<State28DMapping> mappings = {
        // Level 1: Existence
        {"N",            0, "Shell count N exercises the existence aspect — without N shells, no medium"},

        // Level 2: Line
        {"R",            1, "Radial distance is the primary location observable"},
        {"r",            1, "Orbital radius is a location"},
        {"c",            2, "Speed of light is the fundamental relocation rate"},
        {"v",            2, "Bulk velocity is relocation"},
        {"v_circ",       2, "Circulation velocity"},

        // Level 3: Plane
        {"R_charge",     3, "Charge radius defines the planar boundary of the charge region"},
        {"r_e",          4, "Electron radius defines a planar area scale"},
        {"theta",        5, "Angular measure is planar rotation"},

        // Level 4: Sphere
        {"V_disp",       6, "Displacement volume is the spherical presence"},
        {"V_disp_e",     6, "Electron displacement volume"},
        {"V_disp_p",     6, "Proton displacement volume"},
        {"xi_s2",        8, "Shell rotation"},

        // Level 5: Torus (matter structure)
        {"R_p",         10, "Proton radius maps to the central ring (T_1)"},
        {"a",           11, "Torus minor radius is tube diameter (T_2)"},
        {"W",           10, "Winding number characterises the torus topology"},
        {"C_TP",        14, "Toroidal-poloidal coupling is aspect gradation"},

        // Level 6: Dynamism (time evolution)
        {"v_T",         15, "Toroidal velocity — omnidirectional surface component"},
        {"v_P",         15, "Poloidal velocity — surface circulation component"},
        {"v_C",         15, "Compression velocity — surface component"},
        {"omega",       17, "Oscillation frequency"},
        {"Phi_3",       18, "Chirality"},
        {"alpha",       19, "Fine structure constant — state trajectory ratio"},

        // Level 7: Energy (force manifestation)
        {"epsilon",     21, "Deformation content is potential energy per spation"},
        {"E",           21, "Energy"},
        {"E_0",         21, "Rest energy mc^2"},
        {"Phi",         21, "Throughput burden is cumulative energy"},
        {"epsilon_d",   22, "Direct (kinetic) fraction of deformation energy"},
        {"epsilon_a",   23, "Rotational fraction of deformation energy"},
        {"P_conv",      24, "Convergent pressure is the field energy density"},
        {"P_eff",       24, "Effective pressure is the force-scale field"},
        {"F",           24, "Force is field-mediated"},
        {"eps_b",       25, "Binding energy"},
        {"epsilon_t",   26, "Tangential (flux) fraction"},
        {"sigma_n",     24, "Normal stress is field energy density"},
    };
    return mappings;
}

// Resolve which aspects are exercised by the theory's symbol table
inline auto resolve_28d_coverage(const std::vector<std::string>& symbol_names)
    -> std::array<bool, 28>
{
    std::array<bool, 28> covered = {};
    auto& mappings = state28d_mappings();
    for (auto& sym : symbol_names) {
        for (auto& m : mappings) {
            if (m.theory_symbol == sym) {
                covered[m.aspect_index] = true;
            }
        }
    }
    return covered;
}

// ═══════════════════════════════════════════════════════════════════════
//  SOURCE LOCATION
// ═══════════════════════════════════════════════════════════════════════

struct SourceLocation {
    std::string file;
    int         line      = 0;
    int         column    = 0;
    std::string section;        // Current heading context

    [[nodiscard]] auto to_string() const -> std::string {
        std::string s = file;
        if (line > 0) { s += ":" + std::to_string(line); }
        if (column > 0) { s += ":" + std::to_string(column); }
        if (!section.empty()) { s += " [" + section + "]"; }
        return s;
    }
};

// ═══════════════════════════════════════════════════════════════════════
//  VERSION
// ═══════════════════════════════════════════════════════════════════════

struct Version {
    int major = 0;
    int minor = 0;
    int patch = 1;

    [[nodiscard]] auto to_string() const -> std::string {
        return std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(patch);
    }

    auto operator<=>(const Version&) const = default;
};

// ═══════════════════════════════════════════════════════════════════════
//  SYMBOL ENTRY
// ═══════════════════════════════════════════════════════════════════════

struct SymbolEntry {
    std::string              symbol;
    std::string              name;
    std::string              type;               // "constant", "variable", "operator", "function", "unit"
    std::string              definition;          // Human-readable definition text
    std::string              dimensional_signature; // e.g. "M L^-1 T^-2"
    std::string              domain;             // e.g. "cosmological", "atomic", "nuclear"
    std::string              allowed_values;      // e.g. "> 0", "integer", "[0, c]"
    SourceLocation           source_location;
    SymbolStatus             status   = SymbolStatus::UNLOCKED;
    std::vector<std::string> aliases;
    std::vector<std::string> forbidden_aliases;
    std::vector<std::string> dependencies;       // Other symbols this depends on
    Version                  version  = {0, 0, 1};
    uint64_t                 id       = 0;        // Stable unique ID assigned by registry
};

// ═══════════════════════════════════════════════════════════════════════
//  CLASSIFIED ITEM (Parser output)
// ═══════════════════════════════════════════════════════════════════════

struct ClassifiedItem {
    InputClass      classification = InputClass::INVALID_OR_AMBIGUOUS;
    std::string     raw_text;
    std::string     normalised;         // Cleaned/stripped version
    SourceLocation  location;
    ValidationLevel level = ValidationLevel::UNPARSED;
    double          confidence = 0.0;   // Classification confidence [0,1]
};

// ═══════════════════════════════════════════════════════════════════════
//  EQUATION RECORD
// ═══════════════════════════════════════════════════════════════════════

struct EquationRecord {
    std::string equation;
    std::string lhs_expression;
    std::string rhs_expression;
    std::string lhs_dimension;
    std::string rhs_dimension;
    EqStatus    status = EqStatus::UNRESOLVED;
    std::string failure_reason;
    SourceLocation location;
    uint64_t    id = 0;
};

// ═══════════════════════════════════════════════════════════════════════
//  DERIVATION STEP
// ═══════════════════════════════════════════════════════════════════════

struct DerivationStep {
    std::string              step_id;
    std::vector<std::string> input_equations;
    std::vector<std::string> input_definitions;
    TransformKind            operation = TransformKind::ALGEBRAIC_REARRANGEMENT;
    std::string              operation_detail;     // Free-form description of the operation
    std::string              output_equation;
    std::string              justification;
    ValidationLevel          validation_status = ValidationLevel::UNPARSED;
    std::vector<std::string> dependencies;         // step_ids this depends on
    std::vector<std::string> failure_modes;        // FailureCategory strings
    SourceLocation           location;
};

// ═══════════════════════════════════════════════════════════════════════
//  DRIFT REPORT
// ═══════════════════════════════════════════════════════════════════════

struct DriftReport {
    std::string    term;
    std::string    original_definition;
    std::string    later_usage;
    SourceLocation location;
    Severity       severity = Severity::LOW;
    std::string    recommended_fix;
};

// ═══════════════════════════════════════════════════════════════════════
//  BRIDGE RECORD
// ═══════════════════════════════════════════════════════════════════════

struct BridgeRecord {
    std::string              bridge_id;
    std::string              from_domain;
    std::string              to_domain;
    std::string              invariant;
    std::vector<std::string> equations;
    BridgeStatus             status = BridgeStatus::MISSING;
    std::string              notes;
};

// ═══════════════════════════════════════════════════════════════════════
//  COMPILATION FAILURE
// ═══════════════════════════════════════════════════════════════════════

struct CompilationFailure {
    FailureCategory category;
    Severity        severity = Severity::HIGH;
    std::string     symbol;
    std::string     message;
    std::string     original_definition;
    std::string     later_definition;
    SourceLocation  location;
};

// ═══════════════════════════════════════════════════════════════════════
//  PARSED THEORY (Parser output aggregate)
// ═══════════════════════════════════════════════════════════════════════

struct ParsedTheory {
    std::vector<ClassifiedItem> definitions;
    std::vector<ClassifiedItem> equations;
    std::vector<ClassifiedItem> claims;
    std::vector<ClassifiedItem> assumptions;
    std::vector<ClassifiedItem> conjectures;
    std::vector<ClassifiedItem> ambiguous_items;
    std::vector<ClassifiedItem> all_items;       // In source order

    [[nodiscard]] auto total_items() const noexcept -> size_t {
        return all_items.size();
    }

    [[nodiscard]] auto count_by_class(InputClass c) const noexcept -> size_t {
        size_t n = 0;
        for (auto& item : all_items) {
            if (item.classification == c) ++n;
        }
        return n;
    }

    // Merge another ParsedTheory into this one
    void merge(const ParsedTheory& other) {
        auto append = [](auto& dst, const auto& src) {
            dst.insert(dst.end(), src.begin(), src.end());
        };
        append(definitions, other.definitions);
        append(equations, other.equations);
        append(claims, other.claims);
        append(assumptions, other.assumptions);
        append(conjectures, other.conjectures);
        append(ambiguous_items, other.ambiguous_items);
        append(all_items, other.all_items);
    }
};

// ═══════════════════════════════════════════════════════════════════════
//  THEORY KERNEL
// ═══════════════════════════════════════════════════════════════════════

struct TheoryKernel {
    std::string              kernel_id;
    std::string              theory_name;
    Version                  version = {0, 0, 1};
    std::vector<SymbolEntry> locked_primitives;
    std::vector<std::string> locked_definitions;
    std::vector<std::string> locked_equations;
    std::vector<std::string> dimension_basis;
    std::vector<std::string> forbidden_terms;
    std::vector<std::string> allowed_transformations;
    std::string              hash;                // SHA-256
    std::string              mutation_policy = "reject unless versioned";
    bool                     is_locked = false;
};

// ═══════════════════════════════════════════════════════════════════════
//  VALIDATION REPORT
// ═══════════════════════════════════════════════════════════════════════

struct ValidationReport {
    std::vector<std::string>        passes;
    std::vector<CompilationFailure> warnings;
    std::vector<CompilationFailure> failures;
    std::vector<CompilationFailure> fatal_errors;
    std::vector<BridgeRecord>       missing_bridges;
    std::vector<DriftReport>        semantic_drift;
    std::vector<std::string>        unsupported_claims;

    [[nodiscard]] auto has_fatal() const noexcept -> bool {
        return !fatal_errors.empty();
    }

    [[nodiscard]] auto total_issues() const noexcept -> size_t {
        return warnings.size() + failures.size() + fatal_errors.size();
    }
};

// ═══════════════════════════════════════════════════════════════════════
//  COMPILATION RESULT (Full pipeline output)
// ═══════════════════════════════════════════════════════════════════════

struct CompilationResult {
    ParsedTheory                    parsed;
    std::vector<SymbolEntry>        symbol_table;
    TheoryKernel                    kernel;
    std::vector<DerivationStep>     derivation_steps;
    std::vector<EquationRecord>     equation_records;
    ValidationReport                report;
    bool                            success = false;
};

} // namespace sdt::compiler
