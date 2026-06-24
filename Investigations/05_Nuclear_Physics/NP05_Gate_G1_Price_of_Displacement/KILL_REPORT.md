# CQ-32 · KILL REPORT (Deliverable D5)

**The linear energy functional `E = price × geometric-deficit` is FALSIFIED at the nuclear scale.**
Both declared forms fail their gates; the protocol's Stage-4 HALT condition is met. Per R4, the clean kill —
with the failure pattern sorted and the successor named — is the result. Author: Claude (Opus 4.8), executing
CQ-32 (Tyndall / Fable). Reaction set, sealed answers, and run log frozen in this folder.

---

## 1. What was tested (the three declared candidates + the declared fallback)

| Candidate | V_disp definition | Verdict |
|-----------|-------------------|---------|
| **A** tube volume | `2π²Ra²` per tube, summed | **NULL** — ΔV_free = 0 for all 8 reactions (nucleon-conserving). Predicts zero binding. |
| **C** packed-lattice | excluded spation sites `N·ℓ_P³` | **≡ A (NULL)** — counts the same displaced *tube* volume → conserved. (Not run; reduces to A by conservation.) |
| **B** conscription overlap | union of c-boundary spheres (r_c=2.818 fm) at contact `s=2R` | **G1 FAIL** (spread 45×). |
| **Stage 4** B + surface | `E = −(P·ΔV + σ·ΔA)`, calibrate R1–R4, predict R5–R8 | **G4 FAIL** (predictions +158% … +1099%; σ<0). |

Binding lives only in the conscription-overlap channel (B); that channel fails, and adding the one declared
surface term (the SDT analogue of the liquid-drop volume+surface model) does not rescue it. **Two failures of
the deficit form. HALT.**

## 2. The failure pattern, sorted (Stage 3.4 diagnostic)

Candidate B price `P = Q/(−ΔV)` (MeV/fm³), grammar-faithful (v2):

```
TIGHT CORE (converge):  R1 dd→a 0.293 · R2 tp→a 0.297 · R3 hn→a 0.309 · R5 dd→tp 0.272 · R6 dd→hn 0.220
OUTLIER (α + ejected nucleon):  R4 dt→a+n 0.798   (2.7×)
LOOSE CLUSTERS:  R7 α+d→Li6 0.022 · R8 2α+n→Be9 0.018   (~13–16× low)
```

Residuals sort cleanly by **two structural features**:
1. **Loose-cluster over-binding (R7, R8):** ⁶Li's α–d bond is only **1.47 MeV**, but pushing the deuteron to
   contact-`s` creates a 67 fm³ overlap → the model predicts large binding. Real ⁶Li/⁹Be sit at α–d / α–α
   separations of ~3.5–4 fm, **≫ s**. A *single* contact separation is wrong for loosely-bound clusters.
2. **Free-nucleon ejection (R4):** the ejected neutron's conscription sphere re-enters the product union →
   tiny |ΔV| against a large Q.

**Root cause (the decisive number):** per-nucleus `BE / deficit` is **not constant** — it climbs
`0.050 (d) → 0.082 (t) → 0.166 (α) → 0.135 (Be9)`. The union-deficit does not scale with binding. There is
**no single price** because binding is not a static geometric volume at all: α is anomalously over-bound for
its geometry, the deuteron anomalously under-bound. (This is the real nuclear fact — α doubly-closed, d barely
bound — that no single volume-price can carry.)

## 3. What this does and does NOT kill

**Killed:** the hypothesis that *nuclear binding = one universal price × a geometric deficit* (volume, or
volume+surface), computed from conscription-sphere / contact-`s` geometry. Falsified by G1 and G4.

**NOT touched:**
- The *fundamental* functional `E = (Φ/3ℓ_P³)·V_disp` as **Law IV** — with V_disp **from mass** it is the
  identity `E = mc²` (verified: P*·V_disp_p = 938.272 MeV). What failed is the *geometric route* to V_disp for
  binding *differences*, not E=mc².
- The **G1-M Machian "Eddington" reading** was already dead at Stage 0 (the "15.35 MeV/fm³ = 2.459×10⁴⁸ Pa"
  equivalence is a 10¹⁵ unit slip; 15.35 MeV/fm³ = 2.459×10³³ Pa, nowhere in the corpus).
- A genuine **partial signal**: 5 of 6 tight-bound rearrangements share one overlap-price ≈ 0.28 MeV/fm³ to
  within ±20%. Something real lives in the tight-bound core; it simply does not generalise to loose clusters
  or to α-anomalous channels.

## 4. The successor hypothesis (named, with acceptance test) — the five locks re-route here

The static-geometry failure points where SDT's own mechanism always pointed: **rotation, not volume.** The
gear theorems already say binding is a *mesh-frequency* quantity, not a displaced-volume one —
T-J (mesh `r_eΩ_e = a₀ω₁ = αc`), T-I (rim quantisation `RΩ = (W+1)c`), T-K (gear ratio).

> **SUCCESSOR: `E_bind = ℏ · Δω`** — binding = the change in the **meshed-circulation frequency** when
> structures lock, not the change in displaced volume.

- **Acceptance test (declared now, so it can't be invented to fit):** the **H₂ frequency-pull** — compute the
  shift in the two protons' meshed rotation frequency at the bond, predict 4.52 eV. If a *frequency* price is
  universal where a *volume* price was not, the successor lives.
- **Why it should fix the failures:** a frequency model is *bond-local* (mesh contacts), naturally handling
  the α-anomaly (closed mesh = many locked contacts) and loose clusters (few/soft contacts → small Δω) without
  a universal separation — exactly the two things that broke the volume form.
- **The five locks it re-routes:** nuclear binding, the scission constant `12·ε_d`, chemical bond energies,
  Postulate B, the Axis-Alignment Lemma — all were waiting on a price; they now wait on the frequency-pull.

## 5. Bearing on the north-star

The volume form failed *because the geometry is not forced* — the separation is binding-dependent, which is the
same "more than one way to be" the programme must collapse. The successor (mesh-frequency) is also the path to
**choosable scission**: if binding is the lock-frequency of the mesh, then *where the mesh unlocks* under a
given input is the fission channel — predictable, then selectable. Killing the volume form did not cost the
goal; it pointed the goal at the right mechanism.

**Status:** CQ-32 closed as a kill. Next investigation = the gear-frequency functional `E = ℏΔω`, opening on
the H₂ frequency-pull. The geometry engine (`stage2b/stage4`, two-stream verified to 0.08%) is reusable for
the mesh-contact graph the successor needs.
