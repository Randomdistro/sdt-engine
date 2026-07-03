# HUNTER — REPAIR half · CANON PROPOSALS (2026-07-02)

> ┌─────────────────────────────────────────────────────────────────────────┐
> │  ⚠️  APPLY THESE YOURSELF — CANON, NOT TOUCHED BY HUNTER                  │
> │                                                                          │
> │  Every patch below lives in `Engine/include/sdt/*.hpp` or               │
> │  `Benchmarks/B01_B25/benchmarks_b01_b25.cpp`. Both are OFF-LIMITS to     │
> │  HUNTER (Harvey's standing rule: no edits to Engine/include/sdt or Laws  │
> │  without explicit OK). NOTHING here has been applied. These are          │
> │  PROPOSE-ONLY patches with before/after + justification for Harvey to    │
> │  apply by hand.                                                          │
> └─────────────────────────────────────────────────────────────────────────┘

**Author of proposals:** HUNTER (adversarial auditor) · **Method:** `Investigations/HUNTER_PROTOCOL.md`
**Sources verified read-only against current tree** (line numbers below are live as of this audit).
**Prime directive:** propose the HONEST fix, not the cosmetic one — remove fabrications and
identity-passes from the "62/73" so the headline reports only *earned* passes.

---

## 0. The mechanism this repair must respect (why relabel alone is NOT enough)

`report()` in `benchmarks_b01_b25.cpp:51-74` increments the pass counter purely on the
tolerance test:

```cpp
bool pass = err <= tol_pct;
...
g_total++;
if (pass) g_passed++; else g_failed++;
```

**The `Certification` label is printed but never counted.** Therefore relabelling a line
`DERIVED → OBSERVED` or `→ IDENTITY` does **not** remove it from the `62` headline — the
typed/definitional value still sits inside its tolerance and still increments `g_passed`.

**Consequence:** an honest headline requires one of two structural moves, not a cosmetic label swap:
- **(A) REMOVE** the line from the suite (delete the `report()` call — the fabricated/borrowed ones), or
- **(B) SEGREGATE** it into a separate "consistency identities" counter that is reported on its
  own line and **excluded from the headline `X/Y passed`**.

Both are given below. The proposals add a new `Certification::IDENTITY` enum value and a
parallel counter so identities are *shown* (not hidden) but *not tallied as predictions*.

---

## 1. Proposal table  `[file:line · current · proposed · why · Δtally]`

Δtally = effect on the headline earned-pass count (each `report()` call = one tally slot).

| # | File:line | Current | Proposed | Why | Δtally |
|---|-----------|---------|----------|-----|--------|
| **P1** | `laws.hpp:1340` | `inline constexpr double lamb_shift_native_MHz = 1051.8;` (bare literal; comment claims "(9/4)Φ₂(a₀) ⇒ 1051.8", but **no arithmetic evaluates Φ₂** — only the answer is typed) | **DELETE** the constant + its `measured` twin's benchmark use. Replace the block with an `OBSERVED-INPUT` note: keep `lamb_shift_measured_MHz = 1057.845` (a real RF resonance) but explicitly mark it **NOT SDT-derived**; add `// APS04 fished value retracted — PPT08 OPEN`. See §2 for exact text. | It is the laundered APS04 fabrication. The APS04 HUNTER audit already ruled it FABRICATED (non-compiling solver, hand-typed, formula-with-own-inputs gives 3145 MHz not 1051.8). A bare literal is not a derivation. | −1 (B04 removed) |
| **P2** | `benchmarks…cpp:183-185` (B04) | `double Lamb_MHz = law_VI::angular::lamb_shift_native_MHz;` → `report("B04", …, Lamb_MHz, …_measured_MHz, 1.0, Certification::COMPUTED);` | **DELETE the B04 `report()` call** (and the `B04_lamb_shift()` invocation at line 743), OR convert to an explicit `Certification::OBSERVED` **non-tallied** note stating the SDT Lamb amplitude is PPT08-OPEN. | The "PASS" compares a typed number to its target. No SDT quantity is computed. | −1 |
| **P3** | `benchmarks…cpp:297-298` (B09) | `double sdt_dPdt = -2.4029e-12;  // SDT gives the same as GR quadrupole` → `report("B09", …, DERIVED);` | Re-express as an **OBSERVED comparison column**: rename value `observed_dPdt = -2.4025e-12`, `gr_dPdt = -2.4029e-12`, and `report(..., Certification::OBSERVED)` **outside the pass tally**, OR delete. The typed `-2.4029e-12` is literally the GR quadrupole value. | BORROW-SMUGGLE (GR) + HAND-WRITTEN. Nothing SDT is computed; "SDT gives same as GR" is an assertion, and the number is the rival's. | −1 |
| **P4** | `benchmarks…cpp:560` (B21) | `double G_derived = 6.674e-11;  // NIST value (SDT derives same from k-hierarchy)` | **REMOVE** the hardcoded NIST `G` (and B21's `report`), OR mark the whole B21 `Certification::OBSERVED-INPUT` and exclude from tally. If the k-hierarchy derivation is real, **invoke it** (`G = c²R/(k²M)` from `bridge`) instead of typing NIST G. | BORROW-SMUGGLE (G) inside a suite whose banner says "No G". The k-hierarchy route is *asserted in the comment* but the NIST number is what enters the arithmetic. | −1 |
| **P5** | `benchmarks…cpp:596` (B23) | `report("B23", …, coulomb_identity::k_e_e2, …k_e_e2_codata, 0.001, Certification::DERIVED);` | Relabel `Certification::IDENTITY` and route to the **identities counter** (see §3), NOT `g_passed`. | `α ≡ k_e e²/(ℏc)`, so `k_e e² = αℏc` is a tautology. **`laws.hpp:1016-1021` itself flags this class F, "FAILS delete-test", "relabel from Derived — it is an identity."** The benchmark must match the engine's own honesty. | −1 |
| **P6** | `benchmarks…cpp:615` (B24) | `report("B24", "V_p/V_e = m_p/m_e", …, ratio, exp_ratio, 0.001, Certification::DERIVED);` | Relabel `Certification::IDENTITY` → identities counter. (The two `V_disp(e/p)` magnitude lines at 609-610 stay as COMPUTED passes — they check the *magnitude* against a target, not a definition.) | `V_disp = 3mℓ_P³c²/Φ`, so `V_p/V_e ≡ m_p/m_e` by construction — the common `3ℓ_P³c²/Φ` cancels. Output = an input ratio re-exposed. | −1 |
| **P6b** | `benchmarks…cpp:621` (B24) | `report("B24", "P_cf / (P_conv/3) = 1.0", …, stability_ratio, 1.0, 0.001, Certification::DERIVED);` | Relabel `Certification::IDENTITY` → identities counter. | `P_cf ≡ P_conv/3` by the marginal-stability *definition*; the ratio is 1.0 by construction. | −1 |
| **P7** | `benchmarks…cpp:165` (B03) | `report("B03", "Bohr v(1,1) = alpha*c [m/s]", …, v1, exp_v, 0.001, Certification::DERIVED);` | Relabel `Certification::IDENTITY` → identities counter. (The B03 fine-structure line at 160 is a **genuine derivation** — α²Ry/16 with the ½ j-structure factor — and STAYS a fair pass.) | `bohr_velocity(1,1)` returns `αc`; `exp_v = alpha*c`. This is `αc` vs `αc` — identity. | −1 |
| **P8** | `benchmarks…cpp:387` (B12) | 5× `report("B12", "<star> zk2", …, zk2, 1.0, 0.001, Certification::DERIVED);` (one per star) | Relabel all 5 `Certification::IDENTITY` → identities counter. | `zk² = 1` is the **closure definition** `z ≡ 1/k²` (`bridge::zk2_product`). Feeding any `v` and printing `z·k²` returns 1 by construction — the star list is decorative; nothing is predicted per-star. | −5 |
| **P9** | `benchmarks…cpp:534,540` (B20) | 2× `report("B20", …, zk2, 1.0, 0.001, Certification::DERIVED);` | Relabel both `Certification::IDENTITY` → identities counter. | Same `zk²≡1` definitional closure as B12, at the H and Earth points. | −2 |
| **P10** | `benchmarks…cpp:577,580` (B22) | 2× `report("B22", "P_eff…"/"f = P_eff/P_conv", …, Certification::COMPUTED);` | Relabel **`Certification::CALIBRATED`** (align to the engine). Keep in the tally *only if* CALIBRATED passes are counted separately from earned; recommended: move to identities/calibrated non-earned column. The `P_CMB` line (583, DERIVED) stays a fair pass. | **`laws.hpp:359-364` and 370-374 self-label BOTH class E, `calibrated`, "FAILS delete-test — hydrogen calibration fixes the scale", "load-bearing fitted pressure."** The benchmark stamping them COMPUTED is *softer than the engine's own honest label*. Restore the engine's truth. | −2 (as earned) |
| **P11** | `state28d.hpp:134` | `double gradation_screening = std::tanh(std::abs(T_5) / 1e10);  // Normalize to ~1e10 Pa/m scale` | **DO NOT DELETE.** Per the **Closure Principle** (`HUNTER_PROTOCOL §D`): either (a) **derive** the screening scale natively — candidate `S ~ P_conv/R` (convergence pressure over torus radius, both native) — and replace `1e10` with that expression + a `// DERIVED: S = P_conv/R_torus` cite; or (b) mark the term `// OPEN/PENDING — un-derived [Pa/m] screening scale (FLM01 closure debt); T_5=0 in both factories ⇒ dormant, LIVE only when magnetosphere sets T_5`. | It is an un-derived fitted scale. FLM01 confirms it is not uniquely derivable from Laws I–IV. Amputation would delete the *evidence of an open problem* (a fake correction). It is **dormant** (T_5=0 from both factories) but **live** where magnetosphere sets T_5. Not consumed by the B-suite, so **zero tally impact**. | 0 (not in suite) |
| **P12** | `state28d.hpp:159` | `double transition_factor = 1.0 + std::abs(Phi_5) / 1e-20;  // Normalize to ~1e-20 J scale` | **Candidate quarantine.** The enclosing function `accessible_phase_space_volume()` is **uncalled** anywhere in the tree. Mark `// OPEN/DEAD — un-derived [J] scale; enclosing fn uncalled → quarantine candidate (FLM01)`, or move the function to a `#if 0`/deprecated block until a caller + derivation exist. Do not silently delete (closure-debt record). | Un-derived `1e-20 J` scale in a dead function. FLM01: it sits 10⁶× below the binding-energy scale it was reached for — not uniquely determined. | 0 (not in suite; fn dead) |

---

## 2. Exact before/after for the CANON edits (P1 — the cascade root)

### `Engine/include/sdt/laws.hpp:1332-1341`

**BEFORE:**
```cpp
    /// Native Lamb-shift candidate (CLASS C; amplitude pending — see caveats)
    /// ΔE(2S–2P) ≈ (9/4) Φ₂(a₀) ⇒ 1051.8 MHz vs measured 1057.845 MHz (0.57%)
    // provenance_status:     SDT-derived
    // correspondence_status: known-match
    // input_dependency:      primitive-whitelist + measured radii (zero fitted params)
    // class:                 C
    // circularity_assertion: not tuned to the measured value (emergent)
    // risk_flag:             quadrupole amplitude awaits numerical (lattice) verification
    inline constexpr double lamb_shift_native_MHz   = 1051.8;
    inline constexpr double lamb_shift_measured_MHz = 1057.845;
```

**AFTER (proposed — Harvey to apply):**
```cpp
    /// Lamb shift (H 2S–2P). SDT amplitude is OPEN (PPT08).
    /// RETRACTION (HUNTER 2026-07-02): the former `lamb_shift_native_MHz = 1051.8`
    /// was a bare literal, NOT a derivation — the (9/4)Φ₂(a₀) evaluation is not in
    /// the code, only the answer was typed. It is the APS04 fished value (its own
    /// solver won't compile; the formula with its own inputs gives ~3145 MHz).
    /// Removed. PPT08 (SDT Lamb amplitude) is OPEN.
    // provenance_status:     OBSERVED-INPUT (measured RF resonance; NOT SDT-derived)
    // correspondence_status: measured
    // input_dependency:      measured-observable
    // class:                 OPEN (native amplitude unbuilt — see PPT08)
    inline constexpr double lamb_shift_measured_MHz = 1057.845;  // measured, not derived
    // (lamb_shift_native_MHz DELETED — was fabricated 1051.8; do not restore without a derivation)
```

> **Cascade payoff (per MASTER_LEDGER §Cascade root #1):** removing this single canon literal
> + marking PPT08 OPEN collapses **B04**, the De Rerum "19/0", and the compendium's Lamb claim
> back to honest **in one move**. Pay the root, clear the debts.

### `Benchmarks/B01_B25/benchmarks_b01_b25.cpp:173-186` (B04) — must change with P1

**BEFORE:** (reads the deleted constant, stamps COMPUTED, PASSes on the typed value)
```cpp
    double Lamb_MHz = law_VI::angular::lamb_shift_native_MHz;
    report("B04", "H 2S-2P Lamb shift [MHz]", "Atomic", Lamb_MHz,
           law_VI::angular::lamb_shift_measured_MHz, 1.0, Certification::COMPUTED);
```
**AFTER (proposed):** delete the two lines above and the `B04_lamb_shift();` call at line 743.
Optionally replace with a printed OPEN note (no `report()`, so no tally slot):
```cpp
    std::puts("  B04  H 2S-2P Lamb shift: SDT amplitude OPEN (PPT08) — no earned prediction. "
              "Measured 1057.845 MHz retained as OBSERVED-INPUT only.");
```

---

## 3. The structural fix that makes the headline honest (segregation, not hiding)

Add one enum value and one parallel counter so identities/borrows are **shown but not tallied
as predictions.** This is the APS06 template ("flag IDENTITY explicitly, then run a genuine survey").

**`benchmarks…cpp:34`**
```cpp
enum class Certification { DERIVED, COMPUTED, CALIBRATED, OBSERVED, PENDING, IDENTITY };
```

**`benchmarks…cpp:71-73`** — split the tally so IDENTITY/OBSERVED-INPUT do not inflate the headline:
```cpp
    g_total++;
    if (cert == Certification::IDENTITY) {           // definitional / borrowed-input: shown, not earned
        if (pass) g_identity_pass++;                 // separate consistency counter
    } else {
        if (pass) g_passed++; else g_failed++;
    }
```
And add to the summary a second line:
```cpp
    std::printf("║  + %d consistency identities (definitional; NOT counted as predictions) ║\n",
                g_identity_pass);
```

With this in place, applying P5–P10 (relabel to IDENTITY/CALIBRATED-non-earned) automatically
subtracts them from the headline **without deleting the check** — they still print, still show
PASS, but the "X/Y passed" reflects predictions only. P1–P4 (fabrications/borrows) are **deleted**,
not segregated, because they are not even honest identities — they are typed rival values.

---

## 4. Corrected honest benchmark headline (the subtraction, shown)

**Current run (verified):** `62 / 73 passed (84.9%)` · 0 genuine fail · 11 PENDING.

Every `report()` call is one tally slot. Removing/segregating the non-earned passes:

| Removed from earned (deleted) | slots |
|---|---|
| P2 B04 Lamb (typed 1051.8) | −1 |
| P3 B09 dP/dt (GR value) | −1 |
| P4 B21 EM/Grav ratio (hardcoded NIST G) | −1 |
| **subtotal DELETED (fabrication/borrow)** | **−3** |

| Segregated to "consistency identities" (relabel IDENTITY, still printed) | slots |
|---|---|
| P5 B23 k_e e²=αℏc (class F) | −1 |
| P6 B24 V_p/V_e=m_p/m_e | −1 |
| P6b B24 P_cf/(P_conv/3)=1 | −1 |
| P7 B03 Bohr v=αc | −1 |
| P8 B12 zk²=1 (×5 stars) | −5 |
| P9 B20 zk²=1 (×2) | −2 |
| **subtotal SEGREGATED (definitional identities)** | **−11** |

| Restored to engine's own CALIBRATED (class E; not an earned *prediction*) | slots |
|---|---|
| P10 B22 P_eff, f_transfer | −2 |
| **subtotal CALIBRATED-not-earned** | **−2** |

**Arithmetic:**

```
  62  current passes
−  3  deleted (B04, B09, B21 — fabricated / GR / NIST-G)
− 11  segregated (B03, B12×5, B20×2, B23, B24×2 — definitional identities)
−  2  reclassified CALIBRATED, not earned (B22 P_eff, f_transfer)
─────
= 46  EARNED, INDEPENDENT PASSES
```

> **Denominator note:** the total also shrinks — the 3 deleted lines leave the suite (73 → 70),
> and the 13 segregated/reclassified lines move to labelled non-prediction columns.
>
> **HONEST HEADLINE (proposed):**
> **`46 / 70 earned predictions` · + 11 consistency identities (definitional, not counted)
> · + 2 CALIBRATED (class E, documented) · 0 genuine fail · 11 PENDING (known-open).**

This is a floor, not a smear: the ~15 genuinely-independent derivations flagged in BENCH_ENGINE
(B01/B02 Rydberg, B07 Stefan-Boltzmann, B10 Mercury/deflection, B17 g-2, B18 R_p W+1, B19 β-Q,
B26 6π⁵, B27 c-from-precession, B28 depth) plus B05/B13/B14/B24-magnitude/B25-variational/B29 etc.
survive as earned. B15 (typed 147.0) and B16 (typed 0.5) and B25-exact (borrowed Pekeris −79.0052)
are **additional** hand-written literals (F7) — if Harvey also retires those 3, earned drops to **43**.
They were left out of the −3/−11/−2 tally above because the prompt scoped the six named clusters;
they are noted here so the count is not later mistaken for complete.

---

## 5. Verdict line

> **Prompt completion A** — every named fault verified against live source (line numbers current);
> exact before/after given for the one canon edit (P1) + all benchmark edits; tally subtraction shown. ·
> **Physics class of the repair: HONEST-RECLASSIFICATION** — no new physics claimed; the fix restores
> the engine's *own* honest labels (`laws.hpp` already flags B23 class F, B22 class E) to the benchmark
> wire, which currently rounds them up. ·
> **Recovery:** P1 RECOVERED-by-retraction (delete fabrication, mark PPT08 OPEN); P2–P4 delete;
> P5–P9 segregate to identities counter; P10 restore CALIBRATED; P11/P12 CLOSE-or-flag (do NOT amputate). ·
> **Cascade root:** the labelling gap between `laws.hpp` provenance blocks (rigorous) and the
> benchmark `Certification` enum (looser) — plus the counter that tallies on tolerance alone,
> ignoring the label. Fix the counter (§3) and the gap closes structurally, not per-line.

**Earned, honest: 46 / 70 (43 / 70 if B15/B16/B25-exact also retired). Everything else printed but not counted as a prediction.**

— HUNTER · REPAIR half · 2026-07-02 · PROPOSE-ONLY (canon untouched)
