# GOM19 — Assessment, P0/P2/P3 partial (2026-10-05)

**Classification:** `GOM19_NUCLEAR_COLUMN_COMPUTED__P1_NOT_DERIVED__ASTAR_FORK_OPEN`<br>
**Run class:** direct. Locks and scope in `RUN_LOG.md` before the AME2020 file was parsed. Tool `gom19_nuclear_column.py`; output `gom19_results.txt`. **Canon edits:** none. **Fitted parameters:** 0. Data: `Datasets/nuclear/AME2020_mass_excess.txt` (cached; 3558 nuclides; n, ¹H, ⁴He mass excess spot checks pass). No GWTC table opened.

## P3 nuclear column (OBSERVED-ANCHOR from AME2020)
All six §2 anchors reproduce to ≤ 0.06% relative: p+n→d 0.1184%, p+d→³He 0.1952%, p+t→⁴He 0.5286%, d+d→⁴He 0.6355%, d+t→⁴He+n 0.3754%, n+³He→⁴He 0.5489%. Additional registered pairs: p+⁶Li→⁷Be 0.0857%, n+⁶Li→⁷Li 0.1108%, d+⁴He→⁶Li 0.0263%, t+⁴He→⁷Li 0.0377%, ³He+⁴He→⁷Be 0.0243%.

## Gates
- **F4 (flat residual in composition at fixed q) does not fire.** At q = 1, p+n (0.1184%) and d+d (0.6355%) differ by 5.37×; at q = 3, p+t 0.5286% vs n+³He 0.5489%; at q = 6, p+⁶Li 0.0857% vs n+⁶Li 0.1108%. Composition dependence at fixed mass ratio is present in the measured column. The PROMPT's NP24-A guard stands: this is a fixed-q observation, not yet a residual against a ledger f(q) (needs P1c), and not yet validated out of sample (needs P4).
- **P2 (f within a factor 2 of the BH value):** the locked target 1/16 = 6.25% is 1.29× the NR 4.83% and 1.36× the GW150914 4.6%, inside the gate. This evaluates the locked target against declared anchors only; the target is not earned (P1c not run), so the status is VIABLE-CONDITIONAL, not PASS. RIVAL-COMPUTED and OBSERVED anchors are theory-laden (§0.2) and used as comparison columns only.
- **F1 fires by default:** no P1a mechanism for the remnant-spin attractor exists in the repo, so the a* fork stays OPEN and no catalog comparison is made. A comparison line printed in run 1 is void (`RUN_LOG.md`).

## Not run
P1a–d (mechanism hunt, a*(q), f(q) law, surface choice); P4 residual and out-of-sample validation; P5. A derivation of f(q) from the ledger contact-binding is the make-or-break step the PROMPT names; nothing in this run substitutes for it.

## Next
P1c as a paper derivation locked in the log before any further data: f(q) at contact for the budget surfaces, then P4 with the A ≤ 4 events as the fit set and p+⁶Li, n+⁶Li, t+⁴He, ³He+⁴He as the held-out set (the A = 5–7 captures). GWTC event table (MUST-FETCH F10) is needed only for P2's stacked a* and f columns.

## P1c / P2 round (2026-10-05) — f(q) = η/4 against the GWTC table
Locks written before the event table was opened (RUN_LOG "P1c lock"). Data `Datasets/gw/GWTC_eventapi_2026-10-05.json` (GWOSC event API, sha256 prefix 9802865cc8b41508; 391 unique events, 279 with source-frame m₁, m₂ and final mass, 276 with f > 0). Tool `gom19_gwtc_fq.py`; output `gom19_gwtc_results.txt`. Final masses in the catalogue are NR-calibrated (RIVAL-COMPUTED, PROMPT §0.2), so f_obs here is the NR-based radiated fraction, not an independent measurement.

| q bin | n | median f_obs | f_ledger = η/4 | ratio |
|---|---|---|---|---|
| 1.0–1.5 | 152 | 4.54% | 6.11% | 0.74 |
| 1.5–2.0 | 96 | 3.99% | 5.89% | 0.68 |
| 2–3 | 14 | 3.05% | 5.36% | 0.57 |
| 3–5 | 11 | 2.58% | 4.20% | 0.61 |
| ≥ 5 | 3 | 0.77% | 2.26% | 0.34 |

- **G-A (level, q < 1.5): met** — ratio 0.74, inside a factor 2 (F2 not fired).
- **G-B (shape): not met.** Theil–Sen slope of ln f against ln η is 2.49 (bootstrap 95% interval 2.01–3.26) for all 276 events and 3.23 (2.43–4.27) for the 231 with |χ_eff| < 0.2. The ledger slope 1 lies outside both intervals; the leading NR slope 2 lies at or just outside the lower edge. The pre-registered consequence stands: the ledger shape f = η/4 fails against the catalogue.
- Assessment: the contact-binding law reproduces the level near equal mass (observed 4.5% against 6.1%, within the factor 2 gate) but not the mass-ratio dependence; the ratio falls from 0.74 to 0.34 as q grows, a steeper dependence than η¹. The locked derivation (Newtonian circular binding at the budget-point contact separation) is therefore falsified as a law for f(q); its q = 1 value is not.
- Limits: bootstrap over events only (parameter-estimation errors not propagated); catalogue selection thins q > 3 (14 + 11 + 3 events); catalogue final masses come from NR fits, so a pass or fail here is a comparison with NR's functional form; spin enters f and is not in the ledger (the |χ_eff| < 0.2 run changes the slope upward, not toward 1).
- Next (propose-only, to be derived and locked before any rerun): a radiated fraction equal to binding at contact times a q-dependent efficiency (the binding is η/4 but only part is radiated before merger); this needs a derivation from the ledger (no efficiency form exists in the repo) and is not supplied here. P1a (a* mechanism) remains undone.
