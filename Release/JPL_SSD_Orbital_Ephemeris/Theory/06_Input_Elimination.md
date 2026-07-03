# 06 — Input Elimination: Standing on Shoulders, Then Flying Away

> **Author:** James Christopher Harvey, Melbourne. 2026-06-17.
> **Purpose:** retire the permitted-inputs whitelist `{ℓ_P, c, ℏ, k_B, T_CMB, α, m_e, m_p}`
> one entry at a time — showing what each is *derived from* inside SDT, and what minimal,
> **acyclic** seed set actually remains. This discharges the "input/derivation circularity"
> tension named in `PARADOX_CENSUS.md` §8.2(3).

---

## The principle (why the whitelist is not cheating, and why it must still go)

The whitelist is **not a list of fabrications.** It is three to four centuries of measurement —
Planck's quantum of action, Maxwell–Einstein's invariant speed, Boltzmann's energy–temperature
bridge, Sommerfeld's fine structure, the spectroscopic masses. Standing on those is not a sin;
it is **scientific custom**. Newton stood on Kepler and Galileo. Einstein stood on Lorentz,
Riemann, and Mach. Quantum mechanics stood on Balmer and Rydberg. *Every* theory bootstraps from
measured numbers and only later derives some of them from its own structure.

SDT's claim is the second half: having stood on the giants, it **flies away** — it turns inputs
into outputs until only an irreducible seed remains. The honest goal is therefore not "zero
numbers" (the seed theorem, CQ42, forbids that — at least one dimensional seed is unavoidable).
The goal is an **acyclic dependency graph**: a tiny set of declared seeds, with everything else
*derived* and nothing both assumed and derived. This document is that graph.

Labels used: **[UNIT]** convention, not a parameter · **[DERIVED]** from SDT structure ·
**[BOUNDARY]** a measured epoch/state condition · **[SEED]** genuinely irreducible ·
**[PARTIAL]** derivation begun, not closed.

---

## The eliminations, one by one

### c — the relay speed — **[UNIT]**
c is the rate the lattice relays one spation per tick: a conversion between the lattice's
space-step and time-step. Set c = 1 and it vanishes as a *number*; it is a choice of units, not
a free parameter. SDT flies away from "universal constant" to **local relay rate**: c is local,
c_local = c(1−z), and the absolute ceiling c_∞ is a derived quantity, not an input.
*Stood on:* Maxwell, Einstein. *Eliminated as a parameter.*

### k_B — Boltzmann's constant — **[UNIT]**
k_B only converts temperature to energy. In SDT temperature *is* lattice agitation energy
directly; set k_B = 1 and it disappears. *Stood on:* Boltzmann. *Eliminated as a parameter.*

### m_p — the proton mass — **[OPEN]**
[CORRECTED 2026-07-03: previously classed [DERIVED] — 6π⁵ is a privileged, unexplained 19-ppm
match (ROOTSIM verdict), not a derivation.]
The proton/electron mass ratio matches the trefoil topological signature **6π⁵ = 1836.118**
(measured 1836.153, 0.002%). Until a mechanism produces 6π⁵ from the (2,3) trefoil, m_p stays
an input. *Stood on:* the measured ratio. (Honest: the 0.002% residual and the
1.830c-vs-6π⁵ "shared digits" caveat stand — see `Papers/Depth_Closure_Theorem` §9.)

### α — the fine-structure constant — **[DERIVED, PARTIAL]**
α is koppa at the hydrogen ground state: the depth-ladder rung k_H = 1/α = 137, with
ϟ_H = α²a₀ = r_e exactly. α is therefore a *position on the ladder*, not a magic number — it
moves from input to output. **Residual [PARTIAL]:** fully retiring α requires the *integer* 137
to come from the winding/topology rather than being read back from a measurement of α. Until the
trefoil/winding origin of 137 is derived from scratch, α is "reframed as derived" but not yet
seed-free. This is the one place the dependency graph is not yet provably acyclic, and it is
flagged, not hidden.

### ℏ — the quantum of action — **[SEED, collapses with ℓ_P]**
ℏ is the lattice's action quantum: one relay tick carries one unit of action. By the seed
theorem (CQ42) exactly *one* of {length, action, mass} is dimensionally unavoidable, and ℏ, ℓ_P,
and c are not independent — given c [UNIT], an action and a length are interconvertible. So ℏ does
not survive as a *separate* seed; it collapses into the single length–action seed below.
*Stood on:* Planck. *Reduced to one shared seed.*

### ℓ_P — the spation closure length — **[SEED, PARTIAL elimination]**
The size of the spation. In koppa form ℓ_P = √(ϟ·ƛ) — the geometric mean of a koppa and a wake —
which is **mass-independent** and reduces the seed from Planck's two borrowed constants (ℏ, G) to
*one measured SDT length*. **Candidate full elimination:** deriving the spation size from
recombination-epoch hydrogen geometry (the ~3000 K decoupling surface), the route the redshift
investigations are pursuing. *Honest status [PARTIAL]:* CQ42's clean construction fell short (the
count N reached only ~z_rec≈10³ against a target ~6×10⁶¹); the recombination-geometry seed is the
live path, not a closed result. **ℓ_P (≡ the length–action seed) is therefore the first of the two
irreducible seeds** until that route closes. *Stood on:* Planck.

### T_CMB — the CMB temperature — **[BOUNDARY]**
In SDT the CMB is not an inflationary relic but the **convergence influx itself** — the monopole,
the ambient lattice pressure (the foundational ontology: influx directs, pressure holds). Its
*value* is a measured **epoch/state condition** (what the influx is *now*), analogous to
specifying the current cosmic time, and is a candidate output of the Law I relay-throughput
cosmology rather than a fundamental constant. Classed [BOUNDARY]: a measured state, not a tuned
parameter. *Flew away:* from "blackbody relic" to "the influx pressure of the lattice."

### m_e — the electron mass / charge e — **[SEED]**
The electron is the W = 1 lepton; its mass is a Law IV throughput-reorganisation cost. The
programme's own note (CQ10/CQ37) is that **charge e is the single irreducible input** and that
elementary charge quantisation is *derived* (integer windings → integer charge — itself a win
over the Standard Model, which has no reason for it). So the second seed is the **mass/charge
seed**, expressible as m_e or equivalently e, with the other derivable through the topology.
*Stood on:* Millikan, the spectroscopic electron mass. *Reduced to one seed.*

---

## The graph that remains (acyclic)

```
   SEEDS (irreducible)                 DERIVED / CONVENTION
   ──────────────────                  ────────────────────
   ① length–action seed   ─┬─► ℏ        c     [unit]
      (ℓ_P, koppa form)    │            k_B   [unit]
                           ├─► (spation size, scales, depths)
                           │
   ② mass–charge seed     ─┬─► e, charge quantisation (CQ37)
      (m_e ≡ e)            ├─► m_p = m_e · 6π⁵           [OPEN — unexplained match]
                           └─► (Law IV masses)
                                                         α = 1/k_H rung  [derived, 137 PARTIAL]
   BOUNDARY:  T_CMB  (measured epoch state; candidate Law I output)
```

**Tally: 8 whitelist entries → 2 irreducible seeds + 1 boundary**, with two pure unit
conventions (c, k_B) removed from the input column. [CORRECTED 2026-07-03: previously counted
"three genuine derivations (m_p, α, charge quantisation)" — m_p is [OPEN], not derived: 6π⁵ is
a privileged, unexplained 19-ppm match (ROOTSIM verdict), not a derivation; α remains [PARTIAL].]
Compare the Standard Model's ~19–26 fitted parameters. No number is both assumed
and derived **except** the flagged 137-origin [PARTIAL], which is the single remaining cycle to
break.

## Honest residuals (the unpaid corners)

1. **α's integer 137** must be derived from winding topology to fully cut the last cycle.
   Currently reframed-as-derived, not derived-from-scratch.
2. **The length–action seed** is only *reduced* (koppa form), not *eliminated*; the
   recombination-geometry route (≈3000 K hydrogen) is open, and CQ42's first attempt fell short.
3. **T_CMB** is classed boundary, not yet shown to fall out of Law I.
4. The **seed theorem guarantees ≥1 seed survives** — "zero inputs" is not the target and is not
   claimed. The target, an acyclic two-seed graph, is reached modulo residual (1).

---

*Companion to `PARADOX_CENSUS.md` §8.2(3) and `Theory/05_Provenance_and_Correspondence.md`.
Every "[DERIVED]" here carries its certification label in the engine and its CQ provenance.*
