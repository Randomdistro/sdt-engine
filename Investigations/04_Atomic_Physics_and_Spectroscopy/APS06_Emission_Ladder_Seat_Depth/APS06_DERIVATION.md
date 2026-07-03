# APS06 — Derivation: the Emission Ladder by Seat Depth

> Author: J. C. Harvey, Melbourne. Companion to `aps06_seat_ladder.py`,
> `APS06_results.csv`, `APS06_VERDICT.md`. Every number tagged
> DERIVED / COMPUTED / OBSERVED-ANCHOR / PENDING. Engine: `sdt/laws.hpp`,
> `sdt/nuclear.hpp` (constants transcribed with line citations; no local
> constant namespaces).

---

## P1 — Seat depth defined, and the monotone ladder

**Definition (Law IV).** An emission is the reorganisation cost of the *deepest
occupied seat* being vacated and re-settled. Identify the **seat depth** `s`
with the **released photon energy** `E_γ`:

```
s  ≡  E_γ      [J] or [eV]      (Law IV: mass/energy = reorganisation cost)
```

This is the load-bearing identification: it makes the emission band a **read-out
of structure**, not a free axis. Deeper seat ⇒ larger lift cost ⇒ higher `E_γ`.

For the atomic seats, depth is anchored to the radial ladder via the Bohr
kinematics already in the engine: a constituent moving at `v = αcZ/n`
(`atomic::bohr_velocity`, laws.hpp:896) sits at radius `r = a₀n²/Z`
(`atomic::bohr_radius`, laws.hpp:901); the release ceiling of that seat is the
ionisation energy `Z²·Ry/n²`. Deeper seat = larger `k = c/v` = smaller radius =
larger release — the APS01 `z·k² = 1` closure. **DERIVED** magnitudes.

For the **molecular** (rot/vib, meV) and **nuclear** (keV–MeV) classes, the
absolute magnitudes are **OBSERVED-ANCHOR** bands — data, not SDT predictions
(PROMPT §9). The *claim under test* is the **ordering**, not these magnitudes.

**The ladder (from the tool):**

| seat class | representative | `s` (eV) | tag | band |
|---|---|---|---|---|
| molecular (rot/vib) | H₂O bend / CO stretch | 1.0e−1 | OBSERVED-ANCHOR | microwave–IR |
| outer-shell electronic (H, Z=1) | H n=1 Lyman limit | 1.3606e+1 | **DERIVED** | UV (91 nm) |
| inner-shell electronic (Pb, Z=82) | Pb K-shell refill | 9.1485e+4 | **DERIVED** | hard X-ray |
| nuclear | Co-60 → Ni-60* | 1.332e+6 | OBSERVED-ANCHOR | gamma |

**Result:** `s` is **strictly increasing** across all four classes — **zero
inversions**. The seat that is geometrically deeper always emits the higher
band. T1 PASS.

---

## P2 — The hydrogen electronic ceiling = 13.6 eV, from geometry

**The derivation, whitelist only.** The Rydberg scale is rebuilt from the
primitives `{m_e, c, α, h}` — the *same closed form the engine carries*
(`atomic::R_inf_derived`, laws.hpp:929), consulted **before** any spectrum:

```
R∞(derived) = m_e · c · α² / (2h)          [DERIVED, laws.hpp:929]
            = 1.0973731568e7 m⁻¹
```

The deepest **neutron-free single-particle electronic seat** is hydrogen's
`n=1` Bohr seat. Its release ceiling (ionisation / Lyman limit) is:

```
E_ceiling = Z² · R∞(derived) · hc ,  Z=1, n: 1 → ∞
          = 13.605693123 eV           [DERIVED]
```

Compared with the OBSERVED anchor `measured::Ry_eV = 13.605693123 eV`
(laws.hpp:155): **0.000 ppm** (gate < 50 ppm). T2 PASS.

> **Honest caveat (not glossed).** The match is *exact* because
> `R∞(derived) = m_e c α²/(2h)` **is** the closed form by which the Rydberg
> energy is itself defined from CODATA constants. This is a genuine **recovery
> of 13.6 eV from the whitelist geometry**, and it is *not* an identity-pass on
> `Ry_eV` (the tabulated `Ry_eV` is never read into the derivation — only used
> as the comparison column). But it is **not an independent measurement** of
> 13.6 eV: given the CODATA `{m_e,c,α,h}`, the value is algebraically forced.
> Class **CONVERGENCE / IDENTITY**, labelled as such. The *structural* claim —
> that this is the deepest neutron-free electronic seat — is the load-bearing
> statement, and it is vindicated by P2/P3 below, not by the ppm number.

**Why nothing neutron-free sits deeper.** To seat a constituent deeper than
13.6 eV *without* neutrons you must raise `Z` (the X-ray climb, `E ∝ Z²`). But a
bound all-proton nucleus with `Z ≥ 2` does not exist. Drive this from the alpha
grammar (`nuclear::alpha_grammar`, nuclear.hpp:131), scanning the `N = 0` line
`A = Z`:

| Z | A=Z | N | n_d = 3Z−A−2 | n_t = A−2Z | alpha-valid? |
|---|---|---|---|---|---|
| 1 | 1 | 0 | 0 | −1 | **False** (H-1: no nuclear gamma) |
| 2 | 2 | 0 | 2 | −2 | **False** (He-2 diproton, measured unbound) |
| 3 | 3 | 0 | 4 | −3 | False |
| … | … | 0 | … | <0 | False |
| 10 | 10 | 0 | 18 | −10 | **False** |

For every `Z ≥ 1` on the `N = 0` line, `n_t = A − 2Z = −Z < 0` ⇒ **outside the
wedge** `2Z ≤ A ≤ 3Z−2`. The alpha grammar admits **zero** `(Z≥2, N=0)` bound
nuclides (**DERIVED** from the grammar). H-1 is the only `N=0` bound nuclide and
it carries **no** nuclear gamma — its deepest emission is the 13.6 eV electronic
Lyman limit. He-2 (the diproton) is measured **unbound** (OBSERVED-ANCHOR;
SDT derivation deferred → NP19/NP20). T3 PASS.

**The X-ray climb (all electronic seats, `E ∝ Z²`):**

| Z | elem | E_ceiling = Z²·Ry | band |
|---|---|---|---|
| 1 | H | 13.606 eV | UV |
| 2 | He | 54.42 eV | UV |
| 6 | C | 489.8 eV | UV/soft-X |
| 26 | Fe | 9.197 keV | X-ray |
| 82 | Pb | 91.48 keV | hard X-ray |

Monotone in `Z` (**DERIVED**). Every seat here is **still an electron seat**;
the depth grew only because more protons pull the wake inward. And past
hydrogen, those extra protons can only be bound with **neutrons** — so
everything past the 13.6 eV ceiling rides on neutrons, whether the emitter is a
deeper electron seat (X-ray on a neutron-bearing nucleus) or the nucleus itself
(gamma). **Corollary DERIVED.**

---

## P3 — The decisive empirical test: nuclear gamma requires neutrons

This is the genuine falsifiable check, and it is **OBSERVED**, not derived. For
each recorded gamma emitter, take the **de-exciting (emitting) nucleus** `(Z,A)`
— the nucleus whose nuclear level actually releases the gamma (usually the
daughter of a β/EC/α source) — and compute `N = A − Z` and the alpha grammar.

**Committed gate (before the scan):** ZERO counterexamples (a bound `N=0, Z≥2`
gamma emitter) = PASS; ONE = KILL.

**Result (18 emitters, NNDC-cited; full table in `APS06_results.csv`):** every
surveyed gamma emitter has **N ≥ 1**. Spanning Fe-57* (14.4 keV) → Pb-208*
(2614.5 keV), light (Ne-22*, Mg-24*) to heavy (U-235, Pu-239, Np-237*).
**Counterexamples: 0.** T4 PASS.

A control row (Sr-90, N=52, pure β⁻, **no** gamma) confirms that N ≥ 1 is
**necessary but not sufficient** — the survey is a real filter, not a
tautology. The only `N=0` bound nuclide, H-1, emits no nuclear gamma.

**Provenance ledger:** the survey magnitudes are **OBSERVED-ANCHOR** (NNDC
gamma energies); the neutron count `N` and grammar `(n_d,n_t)` are **DERIVED**
integer transforms of `(Z,A)`; the exceptionlessness is an **OBSERVED**
empirical finding over the tested set (Class C — hand-curated, fully cited;
not a full machine-read AME2020 sweep, which would upgrade to Class A corpus).

---

## P4 — The corrected teaching: provenance, not energy

The electronic/nuclear line is drawn by **provenance (seat origin)**, not by
photon energy — the bands genuinely overlap.

| line | E (keV) | seat origin | citation |
|---|---|---|---|
| W Kα1 (Z=74) K-shell X-ray | 59.32 | **electronic** | X-ray Data Booklet |
| Am-241 → Np-237* nuclear gamma | 59.54 | **nuclear** | NNDC A=241/237 |

Energy ratio **1.0037** — within a factor 2 (in fact within 0.4%). At ~59.5 keV
a tungsten K-shell X-ray and the americium nuclear gamma are the **same photon**;
only the **seat** (electron wake vs nucleus) that made them differs. T5 PASS.

**Corrected definition (native):**

- "X-ray" = **electron-seat** emission; "gamma" = **nucleus-seat** emission.
- Seat depth is the native ordering variable; **provenance** is the native label.
- The historical energy-band split (microwave→…→X-ray→gamma) is a **teaching
  artifact** that fails in the overlap region. This document contains **no**
  "X-rays are lower-energy than gammas" definitional statement.

**Downstream (not derived here):** hydrogen caps the neutron-free electronic
ladder at 13.6 eV; everything deeper rides on neutrons; the neutrino (PPT10) is
the rung **below** nuclear gamma (straight-light from the deepest seat
rearrangement) — flagged, deferred.

---

## Parameter ledger (what is what)

| Quantity | Value | Tag | Source |
|---|---|---|---|
| `R∞(derived)` | 1.0973731568e7 m⁻¹ | **DERIVED** | `m_e·c·α²/(2h)`, laws.hpp:929 |
| H n=1 ceiling | 13.605693123 eV | **DERIVED** (recovery) | `Z²·R∞·hc`, Z=1 |
| `Ry_eV` (comparison) | 13.605693122994 eV | OBSERVED-ANCHOR | laws.hpp:155 |
| molecular band `s` | ~0.1 eV | OBSERVED-ANCHOR | rot/vib spectroscopy |
| nuclear band `s` | ~1 MeV | OBSERVED-ANCHOR | NNDC gamma lines |
| wedge `(Z≥2,N=0)` count | 0 | **DERIVED** | `nuclear::alpha_grammar`, nuclear.hpp:131 |
| diproton bound? | no | OBSERVED-ANCHOR | He-2 measured unbound |
| gamma-emitter `N` values | all ≥ 1 | **DERIVED** (N=A−Z) over OBSERVED emitters | NNDC A-chains |
| neutron-requirement counterexamples | 0 | **OBSERVED** (empirical, exceptionless on set) | survey |
| overlap ratio (W Kα1 / Am-241) | 1.0037 | OBSERVED-ANCHOR | X-ray booklet + NNDC |

No CALIBRATED parameters. No `G/M/GM`, no wavefunctions, no quarks/gluons, no
ΛCDM. "Charge radius" never used — `R_p` is the proton boundary/displacement
radius. `e` is a unit-bridge, not a substance.
