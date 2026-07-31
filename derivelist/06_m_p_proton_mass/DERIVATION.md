# m_p — proton mass (occlusion formula + boundary route)

> **J. C. Harvey, Melbourne — 2026-07-30.** Measured anchor: 1.67262192369×10⁻²⁷ kg
> (NIST). Whitelist entry: `laws.hpp:148`. Primary records: Law IV
> (`laws.hpp:434-482`), B18/B24/B26 (benchmarks), PPT07 ROOT-SIM
> (`Investigations/02_Particle_Physics_and_Topology/PPT07_Proton_Electron_Mass_Ratio/ROOTSIM_VERDICT.md`).
> Re-run: `../derivelist_results.txt` §[6].

## Role in the framework

The proton is the W=3 (2,3)-trefoil. It is substantive — it occludes: hard,
dense, present (5.9×10⁵⁹ spations at the boundary), never a hole or deficit.
Its mass is the throughput reorganisation cost of the volume it excludes.

## Derivation routes on record

**1. The occlusion formula (Law IV).**

```
m_p = Φ·V_disp,p/(3ℓ_P³c²)          (laws.hpp:452-461; /3 = angular-averaging share, T10)
V_disp,p = 1.834×10⁻⁵⁸ m³            round trip exact (re-run)
V_p/V_e = m_p/m_e                    identity (B24)
```

This is the occlusion account of what proton mass *is* — the exclusion cost
against the convergent influx. Role, exact by construction.

**2. The boundary route (W+1 conjecture, tallied B18).** The measured proton
boundary radius (muonic hydrogen, 0.8414 fm — the literature's "charge radius";
no charge substance) returns the mass:

```
m_p = 4ℏ/(R_p·c) = 1.6722951935e-27 kg   (dev −0.0195%)   [DERIVED from measured R_p]
```

**3. The topological ratio (B26; PPT07 ROOT-SIM corrected verdict).**

```
m_p = 6π⁵·m_e = 1.6725904374e-27 kg      (dev −0.0019%, 19 ppm)
```

Status on the record: **OPEN — privileged, unexplained, high-precision match.**
6π⁵ is the ONLY simple a·πᵇ form within 0.1% of 1836.15267 (a≤30, b≤6), zero
parameters, nothing to delete-test. The bare topological invariants (winding
W²=9, ropelength 2.6) are O(10) — they do not produce it; the π⁵ lives in the
wake phase-space integral (angular integrations), never yet computed. Factor
homes on the table: 6 = 2·3 (trefoil), π⁵ = 3·A(S³)·A(S⁵).

**4. The ℏ-free pure-ratio statement (FLM13 P3).**

```
m_p/m_e = (4/α)·(r_e/R_p) = 1835.79      (dev −0.0195% — the same single residual
                                          as route 2, seen from the other end)
```

## Scope / Limitations / Residuals

- Route 2's −0.0195% residual is the muonic R_p measurement vs exact W+1=4;
  routes 2 and 4 share it (one consistency fact, not two — FLM13 record).
- The absolute magnitude shares the one mass/action seat with ℏ and m_e; the
  earned content here is the ratio structure and the boundary closure.
- The 6π⁵ mechanism (wake integral run blind) is the named open problem; if a
  different clean number falls out, that becomes the prediction.

## Status

**Line drawn — occlusion role exact, boundary route earned at 0.02%.** m_p is
not an independent mystery: it is the W=3 exclusion cost, pinned to the
measured boundary radius through W+1 and to m_e through the (4/α)(r_e/R_p)
ratio. Open remainder: the 6π⁵ wake integral and the seat magnitude.
