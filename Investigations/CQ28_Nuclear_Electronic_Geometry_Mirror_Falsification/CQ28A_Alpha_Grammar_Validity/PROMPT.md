# CQ28A — Alpha-Grammar Validity *(Claim 1: arithmetic only — proves NO geometry)*

**Purpose.** Certify, electron-free, that every isotope maps cleanly to `1α + n_d·d + n_t·t`. This is the clean foundation; it must never be used to justify geometry (that is CQ28E).

**Inputs.** Full isotope table `(Z, A)` (stable + unstable). **No electron data.**
**Outputs.** Per isotope: `(n_d, n_t)`, validity, and the four decay-transition vectors.

**Formulations (frozen, `nuclear.hpp`):**
```
n_t = A − 2Z ,  n_d = 3Z − A − 2 ;  inverse  Z = 2 + n_d + n_t ,  A = 4 + 2n_d + 3n_t
decay vectors in (n_d,n_t):  α:(−2,0)  β⁻:(+3,−2)  EC:(−3,+2)  n:(+1,−1)
```

**Fixed metrics.** (i) fraction of isotopes with `n_d,n_t ≥ 0` satisfying the inverse exactly; (ii) decay-vector closure (every transition lands on a valid lattice point); (iii) the 7 `nuclear.hpp` aggregate `static_assert`s pass.

**Null / negative control.** Random `(n_d,n_t)` assignment must **fail** the inverse map (`Z=2+n_d+n_t, A=4+2n_d+3n_t`) for ≥ almost all isotopes — proving the map carries information.

**Failure criteria.** Any stable isotope failing the inverse; any decay vector breaking charge/baryon conservation; aggregate asserts fail.

**Status.** Largely DONE — `nuclear.hpp` static_asserts + `CQ25` already certify this. CQ28A re-runs it as the electron-blind foundation and emits the decay-vector table for CQ28E's count/closure metric.

**Reuses.** `nuclear.hpp`, `CQ25`. **Provenance:** class **C**.
