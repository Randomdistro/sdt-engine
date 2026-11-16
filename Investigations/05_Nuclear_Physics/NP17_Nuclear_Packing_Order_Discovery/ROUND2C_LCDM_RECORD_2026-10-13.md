# NP17 round 2-C: ΛCDM-style calibrated run, record (2026-10-13)

**Registration:** `ROUND2C_LCDM_PRE_REGISTRATION_2026-10-13.md`, written before both instruments. Geometry `np17_round2c_dump.js` → `np17_round2c_geometry.csv`; fit and hold-out `np17_round2c_fit.py` → `np17_round2c_results.txt`. Single pass; validations met.

## Ruling check
- 250 stable nuclides built: **0 p–p contacts and 0 n–n contacts.** Every contact is p–n.
- **The live construction is consistent with Harvey's ruling** (no p–p contacts outside electron capture).

## Fit: CALIBRATED(2), on ⁴He, ¹²C, ¹⁶O, ⁴⁰Ca, ⁵⁶Fe, ¹²⁰Sn, ²⁰⁸Pb
| list | K = κ·Ѻ_p | L (per loop) | null c (per nucleon) |
|---|---|---|---|
| native {A p, A e} | 0.01461 fm | −5.53 MeV | 7.566 MeV |
| {Z p, N n} | 0.01542 fm | −5.80 MeV | 7.984 MeV |

**Read-off (not tested).** κ = K/0.155 fm ≈ **0.094**. It is **none of the map's forms** (proton full 1, half ½; loop full ¼, half ⅛).

Read the other way: with κ = ½ the fit would need Ѻ_p ≈ 0.029 fm; with κ = ⅛, 0.117 fm. The fill-limit Ѻ_p (0.155 fm) does not sit with any registered form.

**L < 0.** Every A ≥ 4 graph has exactly one loop, so L acts as a constant offset. Its negative sign does not support a cooperative closure bonus on these graphs.

## Held-out (243 nuclides)
| list | model | median ρ | ratio CV | ratio, first → last A-quintile | bands | verdict |
|---|---|---|---|---|---|---|
| native | **map (2 params)** | **5.14%** | 7.0% | 0.981 → 1.091 | B1 4, B2 21, B3 37, B4 161, B5 18, B6 2 | **B4** |
| native | null c·A (1 param) | 5.82% | 7.1% | 0.990 → 1.006 | B1 3, B2 21, B3 50, B4 164, B5 3, B6 2 | B4 |
| {p,n} | map | 4.95% | 6.5% | 0.982 → 1.084 | — | B4 |
| {p,n} | null | 5.82% | 6.7% | 0.990 → 1.000 | — | B4 |

**Isotope steps where the map's binding falls: 0 of 171.** The wrong-sign defect of the engine's own ledger is absent here, because Σ1/d always grows with each added contact.

## Reading
1. **Calibrated with two controls, the map is order-correct (B4: 5% median), and no better.** It beats "constant binding per nucleon" by only 0.7–0.9 percentage points.
   - The sequencer's contact geometry contributes little beyond counting contacts, since E = A for every A ≥ 4.
   - The map **over-binds the heaviest nuclei** (²⁰⁸Pb +13%; last quintile 1.09). The constant-per-nucleon null does not.
2. **The fitted coefficient corresponds to no registered mover or form.** The map's physical reading (which mover, which form, the fill-limit Ѻ_p) is **not supported** by the calibration.
3. **No closure bonus.** The fitted loop term is negative.
4. **What would lift it above B4.** Not more fitted controls; a native shape term.
   - The measured B/A rises through the light nuclei and saturates in the heavy ones. Neither the contact count nor Σ1/d on the built geometry carries that.
   - The built geometry is itself excluded on size (NP12f round 2: +27%). A shape term computed on correct geometry is the next step: the close-pack radius law with triton contraction (NP12 round 2), feeding contact distances.

**Grades.**
- CALIBRATED(2) map on held-out data: **B4**, beats the null marginally.
- Physical read-off: **not supported**.
- Ruling consistency (p–n only): **confirmed** in the construction.
