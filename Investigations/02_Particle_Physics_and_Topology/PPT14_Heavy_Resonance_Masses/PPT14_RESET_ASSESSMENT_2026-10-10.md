# PPT14 — Heavy resonance masses: reset record, scoped audit (2026-10-10)

**Protocol:** `Investigations/RESET_2026-10-06/PROTOCOL.md`. Claimed by session sdt-engine-e0; sdt-engine-14 was notified.

**Read before registration:**
- `PROMPT.md`
- `laws.hpp` law_I (P_conv), law_VI (winding, topology)
- `graph_v2.json`

No old record exists in the folder.

## 1. Dependency map
- **Graph:** layer 0, no suppliers, no dependents (reach 0).
- **The prompt names:** PPT01 (quantisation), PPT09 (stability), the Law VI winding spectrum.

## 2. Specification audit
- **The prompt states no ladder rule.** It names no rung formula, no width rule and no tolerance. The 2026-10-05 audit already records this as owed.
- **The engine carries no excitation ladder.** law_VI holds the (p,q) torus-knot classification (PPT09: classification only; barrier, lifetime and spectrum open) and the Law V velocity partition v_T = c√(p/(p+q)). Neither gives resonance masses.
- **Running anyway would be a search, and is not done.** Choosing a ladder (powers, knot invariants, sequences) to land on 80.4, 91.2, 125.3 and 173 GeV would be a census over candidate forms. The 2026-10-07 method rule excludes that: native mechanism first, then one comparison.
- **Premise (P1).** "W/Z/Higgs/top" is the prevailing account's bookkeeping. The measured masses and widths are admissible anchors. The prompt's own reading, "shortest-lived winding excitations before unwinding", is the native framing, so no imported particle concept is needed.

## 3. The one computable claim, pre-registered

**Claim.** The SDT mass unit M₀ = [π²ℏ³P_conv√3/(2c⁵)]^¼ lands at about 1 TeV with no tuning.

**Check.**
- Compute M₀ by two routes:
  - the engine's P_conv;
  - P_conv rebuilt as N·u_CMB = (R_CMB/ℓ_P)·aT⁴.
- Both must agree to 1e-12.
- **Confirmed** if M₀c² lies in 0.5–2 TeV.
- Report the input dependence (exponents) and the sensitivity to R_CMB.

**Validation:** the dimensional reduction of ℏ³P_conv/c⁵ to kg⁴, checked numerically by unit scaling.

## 4. Run and results
Instrument: `ppt14_reset_1.cpp`; output in `ppt14_reset_1_results.txt`.

(see section 5)

## 5. Results
Single pass; validation met (M₀ scales as mass^1.000000000000).

**M₀ = 1.786524e-24 kg, so M₀c² = 1.0022 TeV.** The two routes agree to 0 at double precision.
- **Claim confirmed:** the value lies in the registered 0.5–2 TeV band.
- M₀/m_p = 1068.10.

**Provenance and input dependence.**
- M₀ = [π²√3/2]^¼ ℏ^¾ c^(−5/4) (R_CMB/ℓ_P)^¼ a^¼ T_CMB.
- It carries the observed R_CMB to the ¼ power (a factor 2 in R_CMB moves M₀ by ×1.189) and T_CMB linearly.
- "No tuning" holds: no parameter was fitted. The value is conditioned on the observed R_CMB (law_I, class B / E).
- **Grade: G3, shared-input.** contaminating input: R_CMB — observed cosmological scale (measured::R_CMB) — enters at laws.hpp:249–276 through N and P_conv. The ~1 TeV figure is computed, not a prediction independent of the cosmological boundary.

**The resonance ladder: not run (G2, open).** No native rung rule exists in the prompt or in canon. Running one now would be a census.

**What would open it:** a native excitation rule, stated in advance:
- winding-excitation energies of the (p,q) modes below M₀, from the PPT01 mode equations and a barrier (PPT09's open item);
- an unwinding rate for the widths.

Then one comparison with the four measured masses and widths, at the ratio level first.

**Downstream:** none in the graph.

## 6. Comparison with the archived record
None exists.
