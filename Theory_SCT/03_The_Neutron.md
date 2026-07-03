# The Neutron — the Canonical Metastable Structure (SCT Regime II)

> The neutron is the structure that *forced* the two-regime refinement
> ([04](04_Two_Regime_Persistence.md)): the **same object** lives ~880 s free and is **eternal**
> bound. That is impossible for a single `d_min`; it is natural for a **metastable ledge** whose
> retaining barrier changes with context. With the SDT composite `n = p⁺ + e⁻_internal` (NP17),
> every part of the neutron — its decay, its free/bound split, its mass, its moment — reads off
> **one seat geometry** (the 1.83c counter-rotating internal electron). **Author:** J. C. Harvey,
> Melbourne. Solid claims and owed claims are kept apart throughout.

---

## 1. What the neutron is

`n = p⁺ + e⁻_internal`: a proton with one internal electron nestled (counter-rotating) at the
trefoil's 1.83c seat. No fundamental neutron exists. The mass bookkeeping is exact, with **three
numbers that must never be conflated** (mass-defect ontology):

| quantity | value | what it is |
|---|---|---|
| `m_n − m_p` | 1.2934 MeV | the **resistance difference** — neutron form vs proton form |
| `m_e` (the toll) | 0.5110 MeV | the cost of *manufacturing* the released electron |
| `Q_β = m_n − m_p − m_e` | **0.7824 MeV** | the **exhaust** — what's left over, released as movement |

`Q_β = m_n − m_p − m_e = 0.782 MeV` to the digit, parameter-free. β-decay `n → p + e⁻ + ν̄` is not
a particle disintegrating — it is the composite **relaxing to a lower-resistance form and shedding
its internal electron**, venting the 0.782 MeV drop as the kinetic movement of the products.

**Critical distinction (the heart of the model):** the **0.782 MeV is the DROP** (how far downhill
`p+e` sits), **not the BARRIER** (how hard it is to start). The barrier is a separate quantity,
`B` (§3), and it is what actually sets the 880 s.

---

## 2. Two regimes: why the proton is eternal and the neutron is not

The proton and neutron share the *same* `(2,3)` trefoil core — same `~10³⁹` topological barrier to
unknotting. They differ in **one thing**: whether a lower-resistance valid form is reachable.

| | lower form reachable? | regime | persistence law | result |
|---|---|---|---|---|
| **proton** | **no** (nothing below the trefoil floor) | I | `τ ~ (1/λ)·2^{d_min}`, `d_min~10³⁹` | eternal |
| **free neutron** | **yes** (`p+e`, 0.782 MeV down) | II | `τ ~ (1/λ)·e^{B}`, `B~61` | 880 s |

The proton has **no opponent** — there is nowhere downhill to fall, so its repair (A5) wins by
walkover. The neutron has a **real opponent** — the medium's path of least resistance pulls toward
`p+e` — so it is a **tug-of-war**, and the neutron loses it after ~880 s.

---

## 3. What the "89" actually is — a well depth, not a count

My first draft called it "89 reconnections." That was wrong, and the arithmetic proves it:

```
τ_free · λ = 3.13×10²⁶
  in bits (log₂) = 88
  in nats (ln)   = 61      ← same well, two rulers
```

A **count cannot be base-dependent.** `89`/`61` is the **depth of the metastable well in
fluctuation units** — the log of the first-passage odds — *not* a tally of physical reconnections.
This is the clean diagnostic separating the regimes: the proton's `10³⁹` **is** a count (base-free,
a literal number of simultaneous strand-cuts); the neutron's `61` **is** a log (base-dependent,
a barrier height). The neutron was never in the `d_min` regime; it was always on a ledge.

---

## 4. The tug-of-war, mechanically

Decay is a **biased first-passage** over a barrier — two forces, continuously:

- **Hold** = A5 / **Law IV soliton-repair**: the convergent throughput continuously restores the
  high-resistance neutron *form*, pinning the internal electron in its 1.83c counter-seat.
- **Pull** = the **resistance gradient**: the medium presses toward the lower-resistance `p+e`
  form (path of least resistance — the form, *unheld*, relaxes).

The hold is strong (it keeps the form for ~10²⁶ ticks), but the pull is relentless and one-way, so
eventually a fluctuation crosses the barrier and the form lets go, venting `Q_β`. This is why decay
needs **no trigger and no external feed**: it is downhill relaxation, gated only by the barrier.
"Energy released" is the wrong frame — *a high-resistance form falling to a low-resistance one* is
the right one (mass-defect ontology §2.3).

So Harvey's three options resolve cleanly: **not** (a) 89 reconnections; the *spirit* of (b)
"unrepaired interruptions" (it is a first-passage, repair losing over time); and exactly (c) **a
tug-of-war the proton wins and the neutron loses.**

---

## 5. Free vs bound = the sign of the resistance gradient (β-stability)

The single hardest fact about the neutron — 880 s free, forever bound — is **one ledge whose
downhill side opens or closes with context:**

- **Free:** `p+e` is 0.782 MeV downhill → the pull is on → Regime II → `τ ≈ 880 s`.
- **Bound in a β-stable nucleus:** turning `n → p` would be **uphill** (it breaks the shared
  Coulomb-well bond of NP17 and/or violates the ATOMICUS grammar's stability triangle) → **no
  downhill neighbour** → Regime I → **eternal**.
- **Bound in a β-emitter:** `n → p` *is* downhill in *this* nucleus → back to Regime II → a
  **finite, isotope-specific half-life**, set by that nucleus's barrier `B`.

So **β-stability is the sign of the local resistance gradient**, and the grammar's decay vectors
(`β⁻ = (+3,−2)`, `EC = (−3,+2)`) are the moves along the landscape. The neutron is simply the
`Z=0` end of this map, where the downhill direction is always open.

---

## 6. One seat, two numbers — the 1.83c closure

The strongest available closure (distillation Tier-3): a *single* seat geometry — the 1.83c
counter-rotating internal electron — should generate **both** the mass defect **and** the magnetic
moment. (Caution, retained: these are **not** an independent cross-check — they are one defect read
by two instruments, mass-spectrometer and magnetometer. The legitimate question is whether *one
geometry* yields *both numbers*.)

**The moment, from the counter-seat.** `μ_n = μ_p + μ_internal`, so the internal electron must
contribute `μ_internal = μ_n − μ_p = −4.706 μ_N`. A counter-rotating electron at the seat gives
(point current loop, using `R_p/λ_{C,p} = W+1 = 4`):

```
μ_internal / μ_N = −(v/c)·(r/λ_{C,p})
   r = R_p        → −7.32 μ_N
   r = R_p/3      → −2.44 μ_N
   r = 0.64 R_p   → −4.69 μ_N   (matches −4.706)
```

- **Sign: exact** — counter-rotation against the proton's circulation makes the composite moment
  *negative*, which is *why* `μ_n < 0` (a fact a "deepest-seat = zero moment" picture gets wrong).
- **Order: right** — a few `μ_N`, landing on `−4.706` at `r_eff ≈ 0.64 R_p` (between the surface
  and the node).
- **The same 1.83c** that the trefoil proton engine uses to reproduce `μ_p` *exactly* is the seat
  that produces this. So "one geometry, two numbers" is **structurally in place**; the *exact*
  `−1.913` (and the `0.782 MeV` as the seat-binding energy) await the proton engine **extended to
  carry the internal electron** — a concrete, bounded next computation, not a hand-wave.

---

## 7. Solid vs owed

**Solid:**
- `n = p⁺ + e⁻`, `Q_β = m_n − m_p − m_e = 0.782 MeV` — exact, parameter-free.
- The **two-regime resolution**: proton = Regime-I floor (eternal), free neutron = Regime-II ledge
  (880 s), bound neutron = Regime-I or II by the gradient sign (β-stability). One landscape, two
  laws — resolves the free/bound puzzle with no new entity.
- The "89" is a **barrier depth**, not a reconnection count (base-dependence proves it).
- The neutron moment's **sign and order** fall out of the 1.83c counter-seat; the same seat fixes
  `μ_p`.

**Owed (named, not hidden):**
- **What sets `B ≈ 61`.** Back-solved from 880 s; *predicting* it requires SDT's transition rate
  for releasing the counter-seated electron over the barrier — the framework's analog of the weak
  coupling `G_F` (the distillation's central wager that `G_F` is a re-description of a medium-
  grounding event). **This is the deep open problem; it is not faked.**
- **The exact `−1.913 μ_N` and `0.782 MeV` from one geometry** — needs the proton engine extended
  with the internal electron (the `r_eff ≈ 0.64 R_p` should *emerge*, not be fitted).
- **Per-isotope β half-lives** — the Regime-II barrier `B` per nucleus, from the grammar landscape
  (NP04/NP17 continuation).

**Net:** the neutron is the SCT's sharpest confirmation *and* its sharpest open challenge. The
*architecture* — one composite, one seat, one landscape, two regimes — is clean and parameter-free
at the level of `Q_β`, the free/bound dichotomy, and the moment's sign+order. The *arithmetic* of
the barrier (the 880 s as a prediction, the exact moment) is the bounded next work, and it routes
through the one genuinely deep question SDT has left: **what is the rate at which the medium lets a
seated electron go** — i.e., what `G_F` really is.

---

### Cross-references
- **[04](04_Two_Regime_Persistence.md)** — the two-regime framework this is the canonical case of.
- **NP17** — `n = p⁺ + e⁻`, shared-electron Coulomb-well binding (the bond that locks the bound neutron).
- **NP04A** — neutron decay ledger, `Q_n = 0.782 MeV`, antineutrino as winding receipt; tritium keystone.
- **trefoil_proton_engine.cpp** — the 1.83c seat that fixes `μ_p`; extend it with the internal electron to close §6.
- **SCT 01/02** — the audit (A5–A7) and the proton's `10³⁹` Regime-I persistence.
