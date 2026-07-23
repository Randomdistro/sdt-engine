# NP25 — Binary-fission geometry forced by the grammar

## Result

For a parent `(A,Z)` split into two daughters `(A1,Z1)` and `(A2,Z2)`, with
`A1+A2=A` and `Z1+Z2=Z`, the canonical grammar gives

```
n_t1 + n_t2 = n_t(parent)
n_d1 + n_d2 = n_d(parent) - 2
```

The `-2` is forced because the daughters contain **two alpha cores** while the
parent contains one.  The unique zero-remainder construction receipt is

```
2 d -> alpha
```

It conserves `A=4` and `Z=2`.  No neutron is emitted by formation of the second
core.

If `nu` prompt neutrons are stripped, the receipt becomes

```
nu(t -> d+n), plus 2d -> alpha
delta n_t = -nu
delta n_d = nu - 2
```

Thus prompt-neutron multiplicity is variable and independent of the mandatory
topological act that makes the second alpha core.  The earlier proposal
`2t -> 2d + 2n` for closure is not the binary-fission invariant and incorrectly
imposes a two-neutron minimum.

## Geometry class implied

The minimal admissible scission geometry is a **two-lobed body with an alpha
seed in each lobe**.  Before scission, one lobe contains the inherited alpha
core; the other must contain a contiguous pair of deuterons capable of locking
into the new alpha core.  A neck joins the lobes.  Tritons intersected in the
neck or traversal path may strip neutrons individually (`t -> d+n`), producing
the observed variable multiplicity.  EC/beta repair occurs after the primary
fragment identities are fixed.

This determines a topology, not unique coordinates.  Exact `(r,theta,phi)`
positions still require the missing heavy-nucleus trefoil mapping and must be
selected by measured joint yields `Y(A,Z,TKE,nu)`, not by average fragment
masses.

## Hard gates for a coordinate reconstruction

1. Every cut must leave one alpha seed in each connected component.
2. The grammar receipt above must close exactly for every event.
3. The same geometry must generate the full prompt-neutron multiplicity
   distribution; no fixed `nu` is permitted.
4. Reachable cuts must reproduce joint complementary mass and charge yields,
   not marginal averages.
5. Cut weights must be predicted from entry coordinate and trajectory; they
   may not be fitted to yields.

The check program `np25_fission_geometry.py` verifies representative U-236
complementary partitions and the general receipt.

---

## HUNTER verification (Fable direct, 2026-07-19)

**Algebra re-derived independently: CONFIRMS.** For any binary split conserving Z and A,
Σn_t = n_t(P) and Σn_d = n_d(P) − 2 follow from the per-nucleus core constant appearing
twice in the daughters; 2d→α is the unique zero-remainder source of the second core
(ΔA=4, ΔZ=2, zero neutrons). Script audited: computes all fragments from the formula,
no hardcoding; receipts pass. **Classification: grammar IDENTITY-THEOREM** — it holds
for every admissible binary split, so it cannot select which splits occur (that remains
Γ's job); its force is structural: every binary fission MUST manufacture a second alpha
core, and the 2t→2d+2n closure was not an identity and is correctly retired.

**The ν≥2 kill-gate (NP16 consolidated run, 2026-07-19) is RESOLVED, not patched:**
prompt multiplicity is carried entirely by the variable neck process t→d+n, so ν=0
events are pure-scission (no tritons stripped) — the measured P(0)≈3%, P(1)≈17% are
accommodated without retention mechanisms. The generator's first kill-gate closes.

**Energy line-items (new, computed from measured binding energies):**
- 2d→α releases **23.85 MeV** — a fixed per-event core-formation release. This IS the
  "23.8 MeV cross-gate" already queued in the decidables ledger: the fission energy
  budget must contain exactly one 23.85 MeV line-item per binary event.
- t→d+n costs **6.26 MeV** per stripped neutron; adding ~2 MeV neutron KE gives
  ~8.3 MeV per prompt neutron vs the empirical ~8.6 MeV (S_n + η) — same class, ~4%.
  [lit-memory values; VERIFY before certification]

**Supporting observation (convergence-class, lit-memory):** ternary fission is
overwhelmingly α-accompanied (~90% of third fragments are ⁴He). If scission's
mandatory act is core formation, the cheapest third fragment is a bare core — an
alpha — which is what is observed. A three-way split demands Σn_d = n_d(P) − 4
(three cores); a pure-α third fragment (n_d = n_t = 0) satisfies it minimally.

**Prose correction for the record:** the session message quoted Sr-98 as (12d,22t)
and Xe-138 as (24d,30t); correct values are **Sr-98 = (14d,22t), Xe-138 = (22d,30t)**
(totals were accidentally right). The repo files never contained the slip.

**Owed (unchanged):** Γ_U235/U238 positional ordering; event-resolved Y(A,Z,TKE,ν)
for coordinate reconstruction; gate 5 discipline (weights from trajectory, never
fitted to yields).
