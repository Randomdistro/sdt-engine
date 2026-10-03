#!/usr/bin/env python3
"""Fails (exit 1) while any live file still states a superseded input status.
Source of truth: derivelist/OBSERVABLE_DERIVATION_ASSESSMENT.md + observable_derivations_results.txt.
Scope: everything outside _archive/, docs/ (mirror), Release/ (mirror), .git/.
Run from repo root: python3 derivelist/check_input_status.py"""
import re, sys, pathlib
STALE = [
 (r"l_P.{0,40}(Axiom R1|irreducible (dimensional )?seed)|(Axiom R1|irreducible (dimensional )?seed).{0,40}l_P", "l_P stated as irreducible seed / Axiom R1"),
 (r"ℓ_P.{0,40}(Axiom R1|irreducible (dimensional )?seed)|(Axiom R1|irreducible (dimensional )?seed).{0,40}ℓ_P", "ℓ_P stated as irreducible seed / Axiom R1"),
 (r"currently \*\*Axiom R1\*\*", "spation size stated as Axiom R1 (FLM06 header)"),
 (r"terminal input set becomes: \$?\\?ell_P|terminal input set becomes: ℓ_P", "ℓ_P kept in the terminal input set"),
 (r"measured`\s*[—-]\s*the ONLY external inputs", "namespace described as an admission list (derivelist: 'not an admission list')"),
 (r"remains on the input list\s+by count", "α kept on the input list by count"),
]
SKIP = {"HUNTER_SCOUR_2026-07-02", "_archive", "docs", "Release", ".git", "Audits"}
hits = []
for p in pathlib.Path(".").rglob("*"):
    if not p.is_file() or SKIP & set(p.parts) or p.suffix not in {".md", ".hpp", ".cpp", ".py", ".html", ".js"}: continue
    if p.name in {"check_input_status.py", "OBSERVABLE_DERIVATION_ASSESSMENT.md", "OBSERVABLE_DERIVATION_PREREG.md"}: continue
    try: t = p.read_text(encoding="utf8", errors="ignore")
    except Exception: continue
    for rx, why in STALE:
        for m in re.finditer(rx, t, re.S):
            hits.append((str(p), t.count("\n", 0, m.start()) + 1, why))
for f, ln, why in sorted(set(hits)): print(f"{f}:{ln}: {why}")
print(f"{len(set(hits))} stale statement(s)")
sys.exit(1 if hits else 0)
