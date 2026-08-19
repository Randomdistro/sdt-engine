#!/usr/bin/env python3
"""One-time, reviewable migration of named public papers to the 2026 contract."""

from __future__ import annotations

import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SITE = ROOT / "Release" / "HTML_SDT_Website"

# domain, document status, theory steps, authority, dimensional audit,
# rejection criterion, limitation
META: dict[str, tuple[str, str, str, str, str, str, str]] = {
    "paper-glossary": (
        "nomenclature and certification", "NORMATIVE", "L0 L20",
        "Engine/include/sdt/laws.hpp",
        "Symbols retain the dimensions declared at their engine definitions; evidence labels alter provenance, not dimensions.",
        "A term is rejected if two active papers use it incompatibly or if its unit differs from the engine definition.",
        "This document introduces no mechanism; it fixes language and audit semantics.",
    ),
    "paper-engine": (
        "executable scientific infrastructure", "COMPUTED", "L0 L20",
        "Benchmarks/B01_B25/benchmarks_suite.cpp",
        "Exported values retain the SI dimensions of laws.hpp; normalized residuals are dimensionless.",
        "A duplicated constant, stale tally, or header/export mismatch invalidates the public numerical ledger.",
        "Numerical agreement cannot establish a mechanism absent from the engine.",
    ),
    "paper-experiments": (
        "falsification programme", "SPECIFICATION", "L20",
        "Experiments/README.md",
        "Every observable and tolerance carries a unit; normalized residuals and test statistics are dimensionless.",
        "A specification is incomplete unless its rejection class is physically reachable and its comparator uses the same observable.",
        "A registered experiment is not evidence until executed by a validated instrument on identified data.",
    ),
    "paper-medium": (
        "relay substrate", "AXIOM", "L0 L1 L2 L3",
        "Theory/00_Ruleset.md",
        "N is dimensionless, ε and Φ are energies, and Pconv = Φ/ℓP³ is pressure.",
        "The substrate account is ruled out if relay movement exceeds its bound or shell accounting fails unit closure.",
        "Microscopic moving-packing dynamics and non-circular elimination of the first length remain open.",
    ),
    "paper-01-foundations": (
        "foundational relay mechanics", "DERIVED", "L0 L1 L2 L3 L6",
        "Engine/include/sdt/laws.hpp",
        "N is dimensionless; Nε is energy; division by ℓP³ yields pascals.",
        "The chain is rejected if direct FLM12 gates fail or a claimed seed elimination depends on ℓP itself.",
        "ℓP remains the R1 seed; direct microscopic inertial dynamics remain open.",
    ),
    "paper-laws": (
        "Six-Law constitution", "NORMATIVE", "L3 L4 L5 L6 L7 L8",
        "Engine/include/sdt/laws.hpp",
        "Each operator is checked term by term against its SI output; dimensionless closures are identified as identities.",
        "A public law statement inconsistent with laws.hpp or a direct assessment is withdrawn.",
        "Law forms do not promote conjectural coefficients or unclosed microscopic mechanisms.",
    ),
    "paper-02-particle-topology": (
        "persistent matter topology", "CONJECTURE", "L5 L6",
        "Engine/include/sdt/laws.hpp",
        "W and knot invariants are dimensionless; ℏ/(mc) is a length.",
        "W+1 is ruled out if an independent boundary measurement yields a non-integer effective winding outside uncertainty.",
        "W+1 and the higher protected winding spectrum await native moving-packing dynamics.",
    ),
    "paper-topology": (
        "topology and wake geometry", "CONJECTURE", "L5 L12 L13",
        "Theory/00_Ruleset.md",
        "Topology labels are dimensionless; wake radii are lengths; circulation h/m has units of area per time.",
        "The wake taxonomy is rejected where a lobe count or circulation sense fails its registered symmetry test.",
        "A topology drawing is a mechanism proposal until direct substrate evolution reproduces it.",
    ),
    "paper-03-electromagnetism": (
        "directional occlusion", "CALIBRATED", "L4 L5 L12",
        "Engine/include/sdt/laws.hpp",
        "P R⁴/r² has units Pa·m² = N; coupling identities are dimensionally equivalent but not independent evidence.",
        "The mechanism is ruled out if one coefficient and declared geometry cannot reproduce both response senses without retuning.",
        "Inverse-square geometry is distinct from coefficient provenance; target-free Peff remains open.",
    ),
    "paper-04-atomic-spectroscopy": (
        "atomic seating and emission", "COMPUTED", "L9 L10 L11",
        "Engine/include/sdt/laws.hpp",
        "cα√(a0/r) is speed; 2L(c/v) is length; z and k are dimensionless.",
        "A spectral rule is excluded when it fails the complete registered series or requires line-by-line adjustment.",
        "Observed Lamb intervals remain comparator data; the withdrawn extraction is not reinstated.",
    ),
    "paper-05-nuclear": (
        "nuclear construction grammar", "COMPUTED", "L13 L14",
        "ATOMICUS/rules/On the Nature of Atomicus Rules.md",
        "nd and nt are integer counts; packing radii are lengths; binding requires an explicit energy map.",
        "The grammar is ruled out by a stable Z≥2 nuclide lacking its unique decomposition or a registered geometry failure.",
        "Grammar identities are not binding predictions; absolute binding, stability and decay rates remain open.",
    ),
    "paper-atomicus": (
        "nuclear geometry reference", "COMPUTED", "L13 L14",
        "ATOMICUS/rules/On the Nature of Atomicus Rules.md",
        "Grammar outputs are integer counts or lengths until an independently derived energy conversion is supplied.",
        "A tier or belt rule is excluded if a frozen census misses a declared closure without post-hoc branch selection.",
        "Visual placement and measured schedule naming remain distinct from derived geometry.",
    ),
    "paper-lab": (
        "nuclear instrument architecture", "COMPUTED", "L13 L14 L20",
        "ATOMICUS/tools",
        "Inputs and outputs declare units; physical lengths and normalized display coordinates are never interchanged.",
        "The instrument is invalid if known-answer grammar cases, round trips or mirrors disagree.",
        "The browser is an inspection surface; direct validators carry the numerical record.",
    ),
    "paper-06-gravitation": (
        "koppa celestial mechanics", "DERIVED", "L9 L17 L18",
        "Engine/include/sdt/dynamics.hpp",
        "c²ϟ/r² is acceleration; c√(ϟ/r) is speed; orbital invariants retain their standard dimensions.",
        "A celestial relation is rejected when fixed-input residuals exceed its registered gate or an identity is presented as prediction.",
        "Macroscopic koppa aggregation, extended multipoles and dissipative coefficients remain open.",
    ),
    "paper-07-cosmology": (
        "release-domain cosmology", "OPEN", "L3 L8 L19",
        "Engine/include/sdt/laws.hpp",
        "Redshift and octave count are dimensionless; pressure is measured in pascals; distance relations retain length.",
        "A route is excluded by a pre-registered whole-range comparison using the same data and nuisance ledger.",
        "The cyclic amplitude and discriminating distance-redshift law remain under test.",
    ),
    "paper-08-galactic": (
        "galactic dynamics", "OPEN", "L17 L18 L19",
        "Engine/include/sdt/laws.hpp",
        "cH0 is acceleration; velocities are compared in m/s with dimensionless normalized residuals.",
        "A galactic law is excluded when one fixed-input profile fails the complete registered set or imports a fitted profile shape.",
        "No native whole-range galaxy rotation law has passed; the negative ledger is retained.",
    ),
    "paper-09-stellar": (
        "stellar processing", "OPEN", "L8 L13 L15 L17 L19",
        "Engine/include/sdt/laws.hpp",
        "L/(4πr²) is flux; equating it to baseline flux yields a length after the square root.",
        "A stellar mechanism is rejected if independently derived luminosity, radius or spectrum misses the registered population.",
        "The solar luminosity mechanism remains open; measured luminosity cannot derive itself.",
    ),
    "paper-cosmology": (
        "cosmology reference ledger", "OPEN", "L8 L17 L18 L19 L20",
        "Theory/03_Open_Problems.md",
        "Redshift is dimensionless; every inferred scale carries its distance unit and conditioning inputs.",
        "The ledger changes only when a direct assessment promotes, excludes or withdraws a registered route.",
        "Cyclic reiteration is a working extension with open amplitude closure.",
    ),
    "paper-10-fluid": (
        "continuum relay mechanics", "COMPUTED", "L1 L7 L15",
        "Engine/include/sdt/laws.hpp",
        "Viscosity and h/m have units m²/s; Reynolds-like ratios are dimensionless.",
        "A continuum relation is excluded when one coefficient-free rule fails the complete range or uses a target-derived constant.",
        "The continuum limit does not derive microscopic relay collision dynamics.",
    ),
    "paper-11-thermodynamics": (
        "thermodynamic counting", "OPEN", "L1 L2 L8 L16",
        "Engine/include/sdt/laws.hpp",
        "Entropy has units J/K through kB lnΩ; temperature is kelvin; energy-sharing equations close in joules.",
        "A statistical derivation is rejected if its state measure is undefined or an asserted energy quantum is imported as result.",
        "The native origin of ε = hν and several radiation steps remains open.",
    ),
    "paper-12-condensed-matter": (
        "condensed-matter programme", "SPECIFICATION", "L14 L15 L20",
        "Engine/include/sdt/laws.hpp",
        "Mode frequencies are s⁻¹, circulation is m²/s, and transport coefficients retain measured SI dimensions.",
        "Each mechanism must predict a material series from independent structural inputs before receiving a computed label.",
        "This domain is principally a specification, not an established material theory.",
    ),
    "paper-13-quantum-foundations": (
        "deterministic measurement programme", "OPEN", "L1 L2 L5 L7 L20",
        "Theory/03_Open_Problems.md",
        "Residence density normalizes to unity; rates are s⁻¹; barrier exponents and correlations are dimensionless.",
        "The account is ruled out by a registered locality or residence experiment not reproducible by local relay histories.",
        "The correlation sector and a native residence law remain open.",
    ),
    "paper-14-plasma-magnetism": (
        "plasma circulation and magnetic response", "SPECIFICATION", "L5 L12 L15 L20",
        "Engine/include/sdt/laws.hpp",
        "Vorticity is s⁻¹, circulation is m²/s, and force expressions close in newtons without a primitive field.",
        "The programme is rejected if one circulation map fails registered sign, radial and material-dependence tests.",
        "Only the assessed subset is computed; PM02–PM07 remain specifications.",
    ),
    "paper-15-optics": (
        "optical propagation programme", "SPECIFICATION", "L1 L7 L11 L15 L20",
        "Engine/include/sdt/laws.hpp",
        "Refractive index and phase ratios are dimensionless; wavelength is length; group delay is time.",
        "A propagation law is excluded when one fixed dispersion surface fails the registered wavelength and path-length range.",
        "Solar-fold and extreme-energy cases are falsifiers, not completed demonstrations.",
    ),
    "paper-16-chemistry": (
        "molecular seating programme", "SPECIFICATION", "L10 L12 L14 L15 L20",
        "Engine/include/sdt/laws.hpp",
        "Forces are newtons, bond lengths are metres, and an energy surface integrates force over displacement to joules.",
        "A bonding rule is excluded if one fixed geometry fails the registered molecular set or fitted data return as inputs.",
        "The superseded H2 prototype is not evidence; native energies and general geometry remain open.",
    ),
}


def status_from(fragment: str, default: str) -> str:
    upper = re.sub(r"<[^>]+>", " ", fragment).upper()
    for token in (
        "WITHDRAWN", "EXCLUDED", "CALIBRATED", "IDENTITY", "OBSERVED",
        "PENDING", "OPEN", "CONJECTURE", "DERIVED", "COMPUTED",
    ):
        if token in upper:
            return token
    return default


def migrate(path: Path) -> None:
    key = path.stem
    domain, status, steps, source, dimensions, falsifier, limitation = META[key]
    text = path.read_text(encoding="utf-8")
    if 'data-paper-id="' in text:
        return

    text = re.sub(r"<style>.*?</style>\s*", "", text, flags=re.S)
    text = text.replace(
        '<link rel="stylesheet" href="sdt-shell.css">',
        '<link rel="stylesheet" href="sdt-shell.css">\n'
        '<link rel="stylesheet" href="paper.css">',
    )
    text = text.replace(
        '<script src="sdt-shell.js" defer></script>',
        '<script src="sdt-shell.js" defer></script>\n'
        '<script src="paper.js" defer></script>',
    )
    text = text.replace(
        "<main>",
        f'<main data-paper-id="{key}" data-domain="{domain}" '
        f'data-status="{status}" data-theory-steps="{steps}">',
        1,
    )
    text = text.replace("Prepared for Submission", "Scientific working paper · revised August 2026")

    replacements = {
        "R<sub>charge</sub>": "R<sub>×</sub>",
        "charge radius": "boundary radius",
        "Charge radius": "Boundary radius",
        "charged configurations": "persistent handed configurations",
        "charge sign": "circulation sense",
        "no charge substance": "no additional substance",
        "No charge substance": "No additional substance",
        "no charge invoked": "from movement geometry",
        "Handedness replaces charge": "Directional response follows circulation sense",
        "charge quantisation": "circulation-sign quantisation",
        "Electromagnetism_and_Charge": "Electromagnetism_and_Directional_Response",
        "nuclear charge": "nuclear boundary",
        "Charge": "Directional response",
        "charge": "directional sign",
    }
    for old, new in replacements.items():
        text = text.replace(old, new)

    affiliation = re.search(r'(<p class="affil">.*?</p>)', text, re.S)
    if affiliation:
        badge = (
            f'\n<ul class="paper-status"><li>{status}</li><li>{domain}</li>'
            f'<li>Dependencies: {steps.replace(" ", " · ")}</li></ul>'
        )
        text = text[: affiliation.end()] + badge + text[affiliation.end() :]

    first_heading = text.find("<h2>")
    introduction = (
        f'\n<section id="scope" class="scope"><span class="paper-kicker">'
        f'Scope and claim boundary</span><p>This paper treats {domain}. Its '
        f'mathematical authority is <a id="cite-engine" class="citation" '
        f'href="#ref-engine">[1]</a>; its constitutional restrictions are '
        f'applied from <a id="cite-rules" class="citation" href="#ref-rules">'
        f'[2]</a>. Definitions, identities, measured inputs, calibrations, '
        f'computations and open mechanisms are separated before conclusions.'
        f'</p></section>\n<section id="definitions"><h2>Definitions and '
        f'dependency surface</h2><dl class="definition-ledger"><dt><dfn '
        f'id="term-domain">Domain</dfn></dt><dd>{domain}.</dd><dt><dfn '
        f'id="term-authority">Authority</dfn></dt><dd>{source}; engine symbols '
        f'and direct assessments outrank narrative summaries.</dd><dt><dfn '
        f'id="term-status">Document status</dfn></dt><dd>{status}; this label '
        f'limits what the paper claims.</dd></dl></section>\n<section '
        f'id="derivation"><h2>Derivation protocol</h2><p>Each displayed '
        f'relation identifies its source. Identities carry no empirical weight; '
        f'measurements remain inputs; calibrations name their anchor; and '
        f'computations inherit every upstream dependency.</p>\n'
    )
    text = text[:first_heading] + introduction + text[first_heading:]

    equation_number = 0

    def equation(match: re.Match[str]) -> str:
        nonlocal equation_number
        equation_number += 1
        fragment = match.group(0)
        default = "SPECIFICATION" if status == "SPECIFICATION" else "COMPUTED"
        equation_status = status_from(fragment, default)
        return fragment.replace(
            '<div class="eq">',
            f'<div class="eq" id="eq-{equation_number}" '
            f'data-status="{equation_status}" data-source="{source}">',
            1,
        )

    text = re.sub(r'<div class="eq">.*?</div>', equation, text, flags=re.S)
    if equation_number == 0:
        relation = (
            '<div class="eq" id="eq-1" data-status="NORMATIVE" '
            'data-source="Theory/05_Provenance_and_Correspondence.md">'
            '<span>claim class = (provenance, correspondence, input dependence)'
            '</span><span class="no">(1)</span></div>'
        )
        marker = '<section id="derivation"><h2>Derivation protocol</h2>'
        position = text.find("</p>", text.find(marker)) + 4
        text = text[:position] + relation + text[position:]

    certification = re.search(
        r"<h2>(?:\d+\. )?Certification(?: summary)?</h2>|"
        r"<h2>4\. Certification of this document</h2>",
        text,
    )
    if not certification:
        raise RuntimeError(f"{path.name}: certification heading not found")
    insertion = (
        '</section>\n<section id="dimensional-analysis"><h2>Dimensional and '
        f'limiting-case audit</h2><p>{dimensions} Zero-source, '
        'infinite-separation, symmetry and boundary limits are stated wherever '
        'defined; a relation that fails unit closure is excluded before '
        'numerical comparison.</p></section>\n<section id="certification">'
    )
    text = text[: certification.start()] + insertion + text[certification.start() :]
    declaration = text.find('<div class="decl">', certification.start() + len(insertion))
    if declaration < 0:
        raise RuntimeError(f"{path.name}: methodological declaration not found")
    text = text[:declaration] + "</section>\n" + text[declaration:]

    start = text.find('<section id="certification">')
    finish = text.find("</section>", start)
    segment = text[start:finish]
    claim_number = 0

    def claim(match: re.Match[str]) -> str:
        nonlocal claim_number
        row = match.group(0)
        if "<th>" in row:
            return row
        claim_number += 1
        claim_status = status_from(
            row, status if status in {"NORMATIVE", "SPECIFICATION", "OPEN"} else "COMPUTED"
        )
        return row.replace(
            "<tr>",
            f'<tr data-claim="claim-{claim_number}" '
            f'data-status="{claim_status}" data-source="{source}">',
            1,
        )

    segment = re.sub(r"<tr>.*?</tr>", claim, segment, flags=re.S)
    text = text[:start] + segment + text[finish:]

    old_references = re.search(
        r'<h2 class="refs">References</h2>.*?</div>', text, re.S
    )
    if not old_references:
        raise RuntimeError(f"{path.name}: references block not found")
    references = (
        f'<section id="falsification" class="falsification"><span '
        f'class="paper-kicker">Falsification</span><p>{falsifier}</p></section>\n'
        f'<section id="limitations" class="limitations"><span '
        f'class="paper-kicker">Limitations and open problems</span><p>'
        f'{limitation}</p></section>\n<section id="references" class="refs">'
        f'<h2>References</h2><ol><li id="ref-engine" data-type="repo" '
        f'data-path="{source}"><code>{source}</code> — authority used for the '
        f'equations and status assignments in this paper.</li><li id="ref-rules" '
        f'data-type="repo" data-path="Theory/00_Ruleset.md"><code>'
        f'Theory/00_Ruleset.md</code> — axioms, prohibitions and theorem '
        f'vocabulary used to delimit the derivation.</li></ol></section>'
    )
    text = text[: old_references.start()] + references + text[old_references.end() :]
    path.write_text(text, encoding="utf-8", newline="\n")


def main(arguments: list[str]) -> int:
    if not arguments:
        raise SystemExit("Pass one or more paper stems.")
    for stem in arguments:
        if stem not in META:
            raise SystemExit(f"Unknown paper: {stem}")
        migrate(SITE / f"{stem}.html")
        print(f"migrated {stem}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
