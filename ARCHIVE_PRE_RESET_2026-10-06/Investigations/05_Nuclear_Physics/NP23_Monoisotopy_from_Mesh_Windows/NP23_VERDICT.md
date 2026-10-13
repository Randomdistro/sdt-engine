# NP23 — VERDICT: Monoisotopy from Mesh Windows

> **Author:** J. C. Harvey, Melbourne. **Run:** 2026-07-06.
> Tool: `np23_mesh_windows.py` (Python, exit 0) → `np23_results.txt` (teed stdout).
> Question (Harvey, 2026-07-06, verbatim intent): *"if we are correct, then the reason for the
> natural single isotope should naturally just jump out."*
> All commitments in `RUN_LOG.md`, written before the tool; zero ADJ taken; nothing altered
> after first execution.

## Dual verdict header

| Axis | Grade | One-line |
|------|-------|----------|
| **Prompt completion** | **A** | Both phases executed exactly as committed; G0 and G1 scored against pre-committed gates; no knob, no widening, no post-hoc variant. |
| **Physics class** | **CONVERGENCE / CALIBRATED (data-interpolated), capped as declared** — plus one structural EARNED point (the NP08 even-Z pinch) and four leads | The grammar map makes the singles jump out as width-1 windows with a shared signature; the committed WHICH-A rule scores 24/26 with zero per-element freedom; the *mechanism* of the window (why the mesh closes only there) remains the NP17-lock/FLM14 debt. |

## Key numbers

| Quantity | Value | Label |
|---|---|---|
| Stable nuclides mapped (C1: no observed decay), Z=1..83 | 252 (31 naturally-occurring excluded rows listed as leads) | OBSERVED (declared anchor, typed NUBASE2020-class) |
| Window width, odd-Z mean / even-Z mean | 1.36 / 4.85 (odd-Z widths ∈ {1,2} only) | OBSERVED → CONVERGENCE (Mattauch/pairing in grammar coordinates; declared rival cap) |
| Monoisotopic (width-1) elements from the table | exactly the declared 26; the ONLY even-Z single = Be | OBSERVED (G0 integrity PASS) |
| Signature of the 25 odd-Z singles | all (n_d even, n_t odd); Be-9 = the lone (odd,odd) single (1,1) | OBSERVED / CONVERGENCE |
| **Phase B gate G1 (committed rule V1)** | **24/26 correct stable-A picks; Be row = A 9 via GX → PASS** | **CONVERGENCE / CALIBRATED (data-interpolated), post-diction-exposed (declared)** |
| Misses | La-139 (predicted 137), Ho-165 (predicted 163) — both t-RICH of the valley (+1.75, +1.25) | OPEN (owed) |
| Tie rows (In, Pr, Re) under committed LOW (deuteron-rich) tie-break | 3/3 correct — including In-113, the rival's "anomalous" minor-abundance stable | LEAD (n=3, weak but directional) |
| Be-9 (Z=4) | GX: n_t=0 (Be-8) excluded by NP08 ledger (α+2d loses to 2α by −0.092 MeV) → A=9 | IDENTITY ledger, structural use EARNED |
| Bi-209 (unscored, near-stable) | extrapolated t̂=43.00 → A=209 HIT | LEAD (unscored) |
| Scans (cannot PASS, look-elsewhere) | V0 valley power-law 16/26; V2 quadratic 14/26; V1-HIGH 21/26; V1+2β-restored 22/26 | SCAN (committed cell V1/LOW/C1 was best; exposure declared) |

## The answer to Harvey's question (as far as this run earns it)

**It does jump out — in two halves, one per parity:**

1. **Odd Z (25 of the 26 singles):** the grammar forces stable odd-Z windows onto the odd-n_t
   comb (every odd-Z stable nuclide above Z=7 has n_d even, n_t odd — zero exceptions in the
   table; Ta-180m is an isomer footnote). The window is therefore a set of isolated points
   spaced 2 apart in n_t, and its width is 1 or 2, never more. Whether a given odd-Z element
   is a single or a double is set by how the valley position falls on that comb —
   **rival-convergent** (this IS Mattauch/pairing restated as n_t = N−Z; declared, capped).
2. **Even Z (Be, the only even-Z single):** the grammar permits a dense window, so a width-1
   even-Z window needs a *killer*, and the grammar names it: **whole-alpha reassembly, which
   is grammatically possible only at even Z.** The repo already carried the ledger (NP08):
   at Z=4 the α+2d configuration loses to 2α by 0.092 MeV — the ONLY place the competition
   flips sign (at Z=6, α+4d beats 3α by +7.275 MeV). **The unique even-Z monoisotopic element
   is exactly the Z where the packing competition kills a window point. That is the
   convergence the question predicted, and it was already on the record before the question
   was asked.**

**WHICH A (Phase B):** one committed rule with zero per-element freedom — neighbour-median
interpolation of the triton load + the odd-n_t comb + the NP08 exclusion + a deuteron-rich
tie-break (ATOMICUS §6 motivation: tritons are the strain units) — picks the stable A for
24/26, including all 7 radioactive-sibling cases (V-51 not V-50, Rb-85 not Rb-87, **In-113 not
In-115**, Eu-153 not Eu-151, Lu-175 not Lu-176, Re-185 not Re-187, La missed) and Bi-209
unscored. Class honestly capped: the valley is rival-known, the rule was designed with the
public table in view (post-diction-exposed, declared pre-run), and t̂(Z) is *interpolated from
data, not derived from the mesh* — so this is CONVERGENCE with structure, not NATIVE.

## What is earned vs owed

**Earned:**
1. **The even-Z pinch mechanism as a structural theorem of the grammar:** packing competition
   against alpha reassembly exists only at even Z (odd Z is not a sum of alphas); the single
   even-Z monoisotopic element (Be) is the single sign-flip of the NP08 ledger. Grammar +
   ledger, no new number invented.
2. **The window atlas:** every stable nuclide Z=1..83 mapped to (n_d, n_t); widths, positions,
   n_t ranges — the reusable Phase A table for successors (NP17/FLM14 lineage).
3. **Phase B PASS at its declared cap:** 24/26 zero-per-element-freedom picks; gate ≥20/26 met
   without widening; the mandatory Be-9 row landed via the committed general exclusion, not a
   special case.
4. **Leads:** (i) D/T crossover is a BAND (first t>d stable: Li-7 trivially, heavy band from
   ~Sm-154; last d>t stable: Hg-198) — ATOMICUS rules §8 "Golden Boundary at Au" does not
   survive the constitutional formulas (Au-197 itself is n_d=38 < n_t=39): **propose-and-wait
   canon correction, no edit made**; (ii) n_d plateaus (30 at Rh/I/Cs, 34 at Pr/Tb/Ho, 38 at
   Au-region) — unexplained; (iii) deuteron-rich tie-break went 3/3 (In/Pr/Re) — weak-n
   directional support for §6's strain reading; (iv) both misses (La, Ho) sit t-RICH of the
   interpolated valley — localized, named, where the rival parks a shell closure (N=82 under
   La-139); SDT owes its own account of that ridge.

**Owed (cascade roots):**
- **The window MECHANISM.** Phase A/B locate windows; nothing here derives WHY the mesh
  closes only inside them. That is the NP17-lock / FLM14 residence-energy debt (NP10 run 2's
  (Z−1)! candidate is the live route). Until paid, monoisotopy is mapped, not explained.
- **t̂(Z), the triton ramp.** V1 interpolates it from neighbours; a native derivation (why the
  triton load grows — occlusion surplus vs mesh saving) would promote Phase B toward NATIVE.
- **Odd-Z width discriminator.** V1 picks the window POSITION, not its WIDTH; why 13 odd-Z
  elements keep doubles while 25 pinch to singles has no grammar-native rule yet (rival:
  isobar energetics). Declared not-surfaced in Phase A; not scored.
- **La-139 / Ho-165.** The two misses, both +1.2 to +1.8 t-rich of the valley.

## Stress-test self-audit

1. **Identity/circularity:** n_t = N−Z is a relabeling and was declared IDENTITY; everything
   scored is a *pick against measured stability*, not a re-quote of it. The NP08 rows consume
   measured BEs (IDENTITY) — only their even-Z-only *applicability* is used as structure.
2. **Fished factors:** zero fitted constants in the gated rule; 12-cell design space declared
   with the gated cell chosen pre-run; scans and sensitivity cells reported, none promoted;
   design-time hand-estimates disclosed in RUN_LOG (the reason for the CONVERGENCE cap).
3. **Dimensions:** counts are dimensionless; MeV appears only in the cited NP08 ledger. No
   borrowed units.
4. **GATE-CONTRABAND check:** the gate is a measured anchor (which A is stable); no pairing
   term, shell magic number, or SEMF coefficient sits in any gate or enters the chain — the
   rival's account is cited in the rival column only. The C5 parity constraint is a verified
   regularity of the anchor table (re-checked in-run: zero violations), not an imported axiom.
5. **§G MIRROR:** what was accepted on faith — (a) the typed anchor table (mitigated by G0
   integrity gate + the 31-row exclusion ledger printed for audit); (b) convention C1 ("no
   observed decay"), whose flip was run as sensitivity (22/26 — gate-robust); (c) ATOMICUS §6
   strain reading behind the LOW tie-break (3/3 here, n too small to lean on).

## Success criteria scoring (PROMPT)

- [x] Phase A mapping + window-width/position/signature report — done, leads only, no gate
- [x] RIVAL DECLARATION applied — odd/even skeleton graded CONVERGENCE, nothing scored on it
- [x] Phase B declarable rule surfaced → declared in RUN_LOG before scoring, with
      look-elsewhere ledger (12 cells; V0/V2/sensitivity reported)
- [x] G1: 24/26 ≥ 20/26 **AND** Be row = 9 — **PASS at declared cap**
- [x] Be-9/NP08 convergence stated with the ledger on record

---

> **Prompt completion A · Physics class CONVERGENCE / CALIBRATED (data-interpolated, post-diction-exposed; cap declared pre-run) · G1 PASS 24/26 + Be-9 via NP08 complement · EARNED: even-Z pinch = packing competition is grammatically even-Z-only and its unique sign-flip is the unique even-Z single · Misses La-139/Ho-165 named OPEN · Cascade root: window MECHANISM = NP17-lock / FLM14 residence energy**

*NP23 · executed 2026-07-06 · the singles jump out as width-1 mesh windows — mapped and
pick-able with zero per-element freedom; the closing mechanism is still the lock debt.*
