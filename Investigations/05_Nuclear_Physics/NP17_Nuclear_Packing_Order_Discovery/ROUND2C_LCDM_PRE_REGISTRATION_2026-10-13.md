# NP17 round 2-C: ΛCDM-style calibrated run of the proton-ladder map (pre-registration, 2026-10-13)

**Direction (Harvey, 2026-10-13):** "there are no proton proton contacts, or at least, no proton to proton contacts that don't result in EC … let's do a lambda CDM and fit those controls to known measurements, and run it again."

## Ruling recorded
- Nuclear contacts are **proton–neutron** only. Any proton–proton contact ends in electron capture.
- **Checked against the live sequencer before registering** (2026-10-13): every contact in ⁴He, ⁶Li, ¹²C, ¹⁶O, ⁴⁰Ca and ⁵⁶Fe is p–n (kinds alpha, dock, internal). There are no p–p contacts. The run counts p–p contacts in every nuclide and reports any found.

## Method (ΛCDM-style)
Fit a small set of free controls to a calibration set of measurements; label the fit **CALIBRATED(n)**; then predict held-out measurements the fit never saw. The calibration fit is not evidence. Only the held-out cascade counts.

**Model (the PPT18 stage-3 map applied to the built geometry).** Each p–n contact at centre distance d releases the movement of a proton-ladder mover settling to depth Ѻ_p/d:
- E_contact = κ · m_p c² · Ѻ_p / d.
- Only the product **K ≡ κ·Ѻ_p (fm)** is identifiable, because energy depends on κ and Ѻ_p together.

Then:
- **B(A,Z) = K · m_p c² · Σ_contacts 1/d_ij + L · N_loops**

where:
- d_ij = the live sequencer's centre distance × its contraction scale, in fm;
- N_loops = the cycle rank of the contact graph.

**Controls fitted: K and L. CALIBRATED(2).**

**Data.**
- Native-list defects B(A, Z) on {A p, A e} from AME2020 (primary). The {Z p, N n} list is reported secondarily.
- Universe: the 250 zero-fit stable nuclides of the 2026-10-11 cascade (A ≥ 4; seeds ²H, ³H, ³He excluded, because their engine positions are fitted to their own bindings).

**Calibration set** (fixed now): ⁴He, ¹²C, ¹⁶O, ⁴⁰Ca, ⁵⁶Fe, ¹²⁰Sn, ²⁰⁸Pb (7 nuclides). Least squares on relative residuals.

**Held-out set:** the other 243 nuclides.

**Outputs.**
- K and L, with K converted back to the map's controls: κ = K/Ѻ_p at the stage-2b-r fill value Ѻ_p = 0.155 fm. For reference the forms give: proton F κ = 1, proton H κ = ½, loop F κ = ¼, loop H κ = ⅛. That κ is **read off, not tested**.
- Held-out cascade: bands B1–B7 per nuclide, median ρ, the ratio's coefficient of variation, the trend by A-quintile.
- Isotope-step sign check: the fraction of steps where predicted binding falls when a neutron is added.

**Gate (held-out, registered now).** Median ρ ≤ 3% (B3) means "the calibrated map carries binding". Median ρ > 10% is excluded. In between is B4.

**Null.** A one-parameter model B = c·A fitted on the same calibration set and scored on the same held-out set. The map must beat it to be worth anything; the shape of binding per nucleon is the discriminator.

**Exposure.** The engine's zero-fit ledger levels and trend were seen on 2026-10-11 (ratio 0.37–0.67). Measured bindings are general knowledge. The calibration set was chosen as landmark nuclides, not by residual.
