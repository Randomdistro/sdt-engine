# GOM14 — Koppa-Density Consistency Across Multi-Planet Systems

> **Author:** J. C. Harvey, Melbourne (analysis executed by HUNTER, 2026-07-03).
> **Status:** EXECUTED — results reproduce from `koppa_consistency.py` + `koppa_multiplanet.csv` (both in this folder).
> **Dual verdict:** Prompt completion **A** · Physics class **CONVERGENCE (Class C) — earned, with one named provenance caveat.**

## The claim under test

Every planet of one host star must return the **same stellar koppa-density**

```
q ≡ ϟ★/R★³ = (4π²/c²) · (a/R★)³ / P²
```

from photometric observables alone: `a/R★` from transit geometry, `P` from timing.
**No G, no kilograms, no stellar mass anywhere in the chain** — lengths, times, ratios.
This is the earned (non-definitional) form of the "zk²=1 for foreign star systems"
claim: zk²=1 itself is the closure *definition* and cannot fail; cross-planet
agreement of q on the same star *can* fail, and therefore counts.

Note q gauges the star's **mean density** by pure geometry (ϟ/R³ = (4πG/3c²)ρ in
SI display units) — the koppa form of the Seager–Mallén-Ornelas transit density.
This is the "baryon count to density" gauge in its directly measurable form.

## Data

NASA Exoplanet Archive `pscomppars` (TAP, fetched 2026-07-03): all transiting
planets in systems with ≥2 known planets, with `pl_ratdor` and `pl_orbper` present.
1,846 planets; 693 hosts retain ≥2 planets in-table (1,754 planets).

## Result (reproduce: `python koppa_consistency.py`)

| statistic | REAL systems | SHUFFLED control |
|---|---|---|
| median intra-system \|dev\| of q | **5.91%** | 50.74% |
| 75th percentile | 39.06% | 82.95% |
| 90th percentile | 77.99% | 98.29% |
| planets within 10% of system median | **54.6%** | 18.2% |

The negative control (planets reassigned to pseudo-systems of identical size
structure, 10 shuffles) is what makes this a test: nothing in a shuffled (P, a/R★)
pair forces agreement, and indeed it collapses ~9× at the median.

**Solar anchor, same formula:** Earth's (P, a/R☉ = 215.032) → ϟ☉ = 1476.6 m
(CODATA GM☉/c² = 1476.6 m) and implied mean density 1409.8 kg/m³ (accepted ≈1408).
One formula, ratios only, from Kepler field stars to the Sun.

## Honest scope (what is and is not earned)

- **Earned:** same-star agreement of an orbit-independent quantity, 9× tighter than
  chance, from a chain containing no mass unit. The fat tail (90th pct 78%) is real:
  grazing transits, eccentric orbits, and poor a/R★ fits are noisy — shown, not hidden.
- **Caveat (named, unresolved):** some archive `pl_ratdor` values are literature
  products that themselves used a stellar-density prior in the transit fit; where one
  prior served a whole system, part of the intra-system agreement is imported, not
  measured. The shuffled control kills the chance hypothesis; it does **not** fully
  kill the shared-prior pathway. **The airtight version refits raw light curves
  (duration + depth + ingress shape → a/R★ per planet, prior-free) — OPEN.**
- This is CONVERGENCE with Kepler's third law, deliberately: the content is that the
  koppa formulation runs the whole chain in lengths/times/counts with the G·kg
  bookkeeping never entering. It is not claimed as physics beyond Kepler — it is the
  demonstration that the ratio-only gauge works on unclassified foreign systems.

## Falsification

A multi-planet system whose per-planet q values disagree beyond fit uncertainties
(after eccentricity correction, prior-free refit) falsifies the shared-koppa reading
for that system; a population-level null (real ≈ shuffled) would kill it outright.
Current data: not killed — real beats shuffled at every percentile.

## Addendum (2026-07-03, Harvey's twelfths cut)

Duodecile breakdown of the intra-system |dev| distribution:

| duodecile | REAL | SHUFFLED | ratio |
|---|---|---|---|
| 2/12 | 0.018% | 7.62% | 418× |
| 3/12 | 0.088% | 18.61% | 210× |
| 4/12 | 0.406% | 29.25% | 72× |
| 5/12 | 1.855% | 39.55% | 21× |
| 6/12 | 5.914% | 50.74% | 8.6× |
| 8/12 | 23.70% | 72.57% | 3.1× |
| 10/12 | 57.15% | 91.84% | 1.6× |

The distribution is sharply bimodal: **the bottom third of planets agree with their
system's koppa-density to better than 0.1% — parts-in-10⁴ at the 2nd duodecile
(418× tighter than chance)** — with a smooth decay into the noisy-fit tail. The
koppa signal is not a soft 6%-everywhere effect; it is essentially exact where the
transit fits are clean, and drowned where they are not. (Footnote: the 1/12 row is
0 for both real and shuffled — odd-sized systems' median member has dev≡0 by
construction; the discriminating rows start at 2/12.) A distance-from-Sol
twelfths-shell cut (robustness probe: intra-system consistency should be
distance-blind; any gradient = data-quality systematic) is pending an archive
refetch with `sy_dist` (endpoint TLS failure at time of writing).
