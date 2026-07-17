# NP23 — Monoisotopy from Mesh Windows

> **Author:** J. C. Harvey, Melbourne. **Status:** ACTIVE (Harvey question, 2026-07-06, verbatim
> intent: *"if we are correct, then the reason for the natural single isotope should naturally
> just jump out."*).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · HUNTER §G
> + MIRROR · FARMER refinements (2026-07-03/06).
> **Tool language:** Python (pure integer/count analysis; no engine constants consumed — the
> only MeV numbers are the NP08 ledger rows, cited from the repo record with s.f. noted).
> **Committed BEFORE any tool code exists.** RUN_LOG.md carries the pre-commitments.

## ⓪ The five answers

1. **What don't we know?** Whether the ATOMICUS construction grammar (α core + n_d deuterons +
   n_t tritons; n_t = A−2Z, n_d = 3Z−A−2) makes the ~26 single-stable-isotope elements *jump
   out* — a shared grammar/mesh signature — and whether a zero-per-element-freedom rule picks
   WHICH A is the stable one for each.
2. **Why does it matter?** It is Harvey's stated falsification posture: if the mesh/packing
   picture is right, monoisotopy should be a structural consequence, not a fitted afterthought.
   NP08 already carries the even-Z half of the claim at Z=4 (Be-8 metastable against 2α by
   0.092 MeV — the packing competition), and Be is the ONLY even-Z single. The question
   predicts that convergence; this run tests whether the rest of the map converges too.
3. **How will we find out?** Phase A (leads only, NO gates): map every stable isotope Z=1..83
   into (n_d, n_t); tabulate per-Z window width and position; test and REPORT the structural
   correlations. Phase B (scored ONLY if Phase A surfaces a declarable rule): a
   zero-per-element-freedom rule predicting the stable A for each of the 26 monoisotopic
   elements, declared in RUN_LOG before scoring, gate ≥ 20/26 plus the mandatory Be-9 row.
4. **What would prove us wrong?** Phase B rule < 20/26; or the Be row missing A=9 even with the
   NP08 packing-competition complement; or Phase A showing the singles share NO grammar
   signature beyond what the rival's pairing/Mattauch account already fixes.
5. **How will we know we're done?** Dual verdict: prompt completion + physics class, with the
   RIVAL DECLARATION cap applied honestly (see §3), earned-vs-owed ledger, canonical line.

## 1. Executive summary

~26 elements are naturally single-stable-isotope. The rival explains the odd-even skeleton of
this (pairing term + Mattauch isobar rule). SDT's grammar restates A, Z as construction counts
(n_d, n_t) around one alpha core. This run asks: (A) do the stability WINDOWS (which A are
stable per Z, how many, where in (n_d, n_t) space) carry a grammar-native structure, and do the
singles share a signature; (B) can one committed rule with zero per-element freedom pick the
stable A of every monoisotopic element — including Be-9, where the NP08 packing competition
(α+2d loses to 2α by 0.092 MeV at A=8) is the repo's existing width-1 mechanism.

## 2. Physical context (SDT chain)

- **Grammar (constitutional):** every Z ≥ 2 nucleus = 1 alpha core + n_d deuterons + n_t
  tritons; n_t = A−2Z, n_d = 3Z−A−2; free neutrons forbidden. EC isotopes use the alternate
  grammar (He-3 core): n_t = A−2Z+1, n_d = 3Z−A−3 — noted; the standard grammar is used for
  the window map (declared; the alternate grammar is not needed to *count* windows).
- **Mesh/roll (FARMER §8, refinement 2 + 8):** contact ANGLE is the scarce resource (limited
  poloidal rim); cadence-locked rotations MESH (bond), desynchronised ones ROLL (repulsion). A
  stability window = the set of block loadings (n_d, n_t) whose mesh closes; monoisotopy = a
  window pinched to width 1.
- **Packing competition (NP08):** at even Z the grammar configuration competes against
  whole-alpha reassembly (Z=4: α+2d vs 2α → −0.092 MeV, metastable; Z=6: α+4d beats 3α by
  +7.275 MeV). At odd Z the pure-alpha competitor is grammatically impossible (Z odd cannot be
  a sum of alphas) — the competition can only pinch EVEN-Z windows.
- **Triton strain (ATOMICUS rules §6):** tritons are the strain/weight units; triton overload
  is the decay side. The stable side of an ambiguous window is the deuteron-rich side.

## 3. RIVAL DECLARATION (mandatory, written before any result)

**The odd-even window-width split and one-stable-isotope-per-odd-Z is ALSO the rival's
pairing/Mattauch physics** (pairing energy term; Mattauch isobar rule: no two stable isobars at
adjacent Z). Re-deriving that skeleton in grammar coordinates earns **CONVERGENCE at most** —
it is a relabeling (n_t = N−Z is the neutron excess). The run must go BEYOND it to earn
anything: (i) the WHICH-A rule of Phase B with zero per-element freedom; (ii) the even-Z
pinch mechanism (NP08 packing competition — grammatically even-Z-only — landing exactly on the
unique even-Z single, Be); (iii) any grammar signature of the singles the pairing account does
not fix. **GATE-CONTRABAND check:** all Phase B kill/pass conditions are measured anchors
(which A is stable — NUBASE-class data); no rival axiom (pairing term, shell magic numbers,
SEMF coefficients) sits in any gate, and none of that machinery is imported into the SDT
chain — it is cited in the rival column only.

## 4. Phase A — leads / mapping (NO gates scored)

1. Map every stable isotope of Z=1..83 to (n_d, n_t) (standard grammar; H pre-grammar and
   He-3 non-decomposable — flagged, excluded from grammar statistics; both declared).
2. Tabulate per-Z window width (number of stable A) and position (n_t range).
3. Test and REPORT (not gate):
   - odd-Z vs even-Z window width distributions;
   - where in (n_d, n_t) space the windows sit (valley position; n_d plateaus; D/T crossover);
   - whether the monoisotopic Z's share a grammar signature (n_t parity; window pinched
     between packing competitors; position relative to the interpolated valley).
4. Examine candidate WHICH-A rules as leads and log EVERY variant (look-elsewhere ledger) —
   the Phase B rule must come from this set, declared before scoring.

## 5. Phase B — the committed gate (scored ONLY if Phase A surfaces a declarable rule)

- **Rule requirement:** zero-per-element-freedom grammar/mesh rule predicting, for each
  monoisotopic Z, WHICH A is stable. Declared in RUN_LOG BEFORE scoring, with the full
  look-elsewhere ledger of every variant examined in Phase A.
- **Gate G1:** ≥ 20/26 correct A picks over the declared 26-element monoisotopic list, AND
  the Be-9 row: the rule (or its packing-competition complement per NP08) must pick A=9 for
  Z=4. Gates never widened.
- **Class cap (declared now):** even at PASS, the result is capped at **CONVERGENCE /
  CALIBRATED (data-interpolated)** — the valley of stability is rival-known physics, and the
  rule variants were designed with sight of the (centuries-old, public) stable table.
  NATIVE would require the window mechanics derived from the mesh (NP17-lock lineage) — not
  attempted here; owed.

## 6. Measured anchors (declared)

- **Stable-nuclide table, Z=1..83** — NUBASE2020-class classification, typed into the tool by
  element. **Convention C1 (committed):** "stable" = no experimentally observed decay.
  Nuclides with measured 2β/2EC (Ca-48, Ge-76, Se-82, Kr-78, Zr-96, Mo-100, Cd-116, Te-128,
  Te-130, Xe-124, Xe-136, Ba-130, Nd-150), measured α (Nd-144, Sm-147, Sm-148, Eu-151, Gd-152,
  Hf-174, W-180, Os-186, Pt-190, Bi-209), and primordial β/EC (K-40, V-50, Rb-87, Cd-113,
  In-115, La-138, Lu-176, Re-187) are EXCLUDED from windows and listed separately as
  naturally-occurring leads. Ta-180m: observationally stable isomer, kept with flag.
  **s.f.:** A, Z are exact integers; half-life notes are 2 s.f. context only.
- **Monoisotopic list (declared, with the honest distinction):** the **26 monoisotopic**
  elements (exactly one stable isotope) = 19 that are also mononuclidic (Be, F, Na, Al, P,
  Sc, Mn, Co, As, Y, Nb, Rh, I, Cs, Pr, Tb, Ho, Tm, Au) + 7 with a naturally-occurring
  radioactive sibling (V, Rb, In, La, Eu, Lu, Re). **Why this list:** "which A is THE stable
  one" is well-posed for all 26 (the 7 sibling cases are the sharper test — the rule must
  reject the radioactive sibling). Bi-209 (mononuclidic, α measured 2003, t½ 2.0×10¹⁹ yr) is
  reported as an UNSCORED near-stable 27th row; Th/Pa (mononuclidic, no stable isotope) are
  out of scope. Tc, Pm (no stable isotope) get unscored lead-only rows.
- **NP08 ledger rows (repo record):** B(α) = 28.296 MeV, B(Be-8) = 56.500 MeV, Be-8 vs 2α =
  −0.092 MeV (5 s.f.; IDENTITY — consumes measured BEs).

## 7. Mandatory clauses

- **Disqualified-data-as-leads (Harvey fallback):** if any anchor row is later found
  defective, every result touching it demotes to LEAD — no silent regrade.
- **ADJ-before-code:** any adjustment to commitments is logged in RUN_LOG with an ADJ number
  BEFORE the tool is edited.
- **§D on FAIL:** any gate failure gets the seven questions (HUNTER_PROTOCOL).
- **GATE-CONTRABAND:** pairing/shell-model/SEMF machinery = rival column only; cite, never
  import; no rival axiom in any kill condition (checked in §3).
- **No borrowed units:** counts are dimensionless; the only dimensioned numbers are the NP08
  MeV ledger rows (measured anchors).
- **Tool hygiene:** teed stdout, exit 0, `PYTHONIOENCODING=utf-8`.

## 8. Outputs

1. `RUN_LOG.md` — pre-commitments (BEFORE the tool; rule variants, tie-breaks, conventions,
   design-time exposure disclosure, forbidden retro list).
2. `np23_mesh_windows.py` — standalone Python tool.
3. `np23_results.txt` — teed stdout.
4. `NP23_VERDICT.md` — dual verdict, earned-vs-owed, §D if anything fails, canonical line.

## 9. Dependencies & references

- **Upstream:** ATOMICUS rules (constitutional grammar, §6 triton spectrum); NP08 verdict
  (packing competition + 2026-07-06 re-open); NP10 run 2 ((Z−1)! lock — context for why
  windows exist energetically; NOT consumed here); FARMER_PASS §8 (mesh/roll, angle premium).
- **Downstream:** NP17-lock lineage owes the window MECHANISM (why the mesh closes only inside
  the window); FLM14 owes the residence/tour energy that would make Phase B NATIVE.

## ⑩ Adaptive execution protocol

| Trigger (numeric) | First response (PIVOT) | If pivot fails | Forbidden response |
|-------------------|------------------------|----------------|--------------------|
| G0 data-integrity mismatch (width-1 set ≠ declared 26) | Fix typed table against the declared source; log as numerics fix | Report tool defect, no verdict | Grade with a broken anchor table |
| Phase A surfaces NO declarable rule | Phase B NOT scored; verdict reports leads only (Harvey fallback) | — | Inventing a rule after peeking at per-element scores |
| G1 < 20/26 | §D seven questions; cascade root named (valley position underived) | — | Widening the gate; swapping rule variant post-hoc; per-element patches |
| Be row misses A=9 | §D on the row; NP08 convergence claim retracted | — | Special-casing Z=4 beyond the declared general exclusion |

**Allowed:** typing-error fixes to the anchor table (logged), formatting, extra REPORTED
diagnostics. **Disallowed:** RETRO-PASS, rule edits after results, tie-break flips after
results, convention flips after results, promoting scan variants (V0/V2) to PASS.

---

*NP23 · spec 2026-07-06 · Harvey's monoisotopy question · J. C. Harvey, Melbourne.*
