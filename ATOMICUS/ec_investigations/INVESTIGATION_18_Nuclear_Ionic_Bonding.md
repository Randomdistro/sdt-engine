# INVESTIGATION 18: Nuclear Ionic Bonding — He-8 as a Nuclear Anion

> Navigation: [Grammar Test](INVESTIGATION_01_Grammar_Test.md) ·
> [Be-7](INVESTIGATION_02_Be7_Deep_Dive.md) ·
> [Closures](INVESTIGATION_03_Subshell_Closure_Pattern.md) ·
> [Protection](INVESTIGATION_04_Protection_Factor.md) ·
> [Orthohelium](INVESTIGATION_05_Orthohelium_Connection.md) ·
> [Missing](INVESTIGATION_06_Missing_Elements.md) ·
> [Ratios](INVESTIGATION_07_Energy_Ratios.md) ·
> [Dual Defect](INVESTIGATION_08_Dual_Defect_Branching.md) ·
> [FINAL](FINAL_REPORT.md)
>
> Data: [Master Table](EC_data/01_All_EC_Isotopes_Master_Table.md)

---

## 1. Motivation: The Empty Slots

The stable isotope chart has exactly THREE structural vacancies:

| Slot | Location | What's missing | Why |
|------|----------|---------------|-----|
| **A = 5** | Bottom | No stable isobar at mass 5 | Grammar-forbidden (pairing impossible) |
| **A = 8** | Bottom | No stable isobar at mass 8 | Grammar-valid (Be-8) but energetically unbound |
| **A ≥ 210** | Top | No stable isobar above 209 | Triton overload cliff |

Investigation 06 established the **Tc/Pm pattern**: odd-Z elements blocked by
prolific even-Z neighbours at every mass number. This investigation asks the
inverse question: what makes a mass number ITSELF empty? And can anything
fill it?

---

## 2. The A = 5 Vacancy: Pairing Failure

At A = 5, only two elements can attempt construction:

| Candidate | Z | A | n_tri | n_deu | Grammar |
|-----------|---|---|-------|-------|---------|
| He-5 | 2 | 5 | 1 | **−1** | ❌ INVALID |
| Li-5 | 3 | 5 | **−1** | 2 | ❌ INVALID |

Both have exactly ONE unpaired defect:
- He-5: 1 bare neutron bolted to the alpha (no deuteron partner)
- Li-5: 1 bare proton bolted to the alpha (no triton partner, n_tri = −1)

Neither can pair. Both die in ~10⁻²² s. The slot is empty because
**pairing is impossible at A = 5**.

---

## 3. The A = 209/210 Vacancy: The Cliff Edge

| A | Stable occupants | Identity |
|---|-----------------|----------|
| 207 | 1 | Pb-207 (Z=82) |
| 208 | 1 | **Pb-208** (Z=82, N=126 — doubly magic) |
| 209 | 1* | Bi-209 (Z=83 — technically α-radioactive, t½ = 1.9×10¹⁹ y) |
| 210 | **0** | **EMPTY** |
| 211+ | **0** | **ALL EMPTY** |

Bi-209 is the last pretence of stability. Above it: nothing. The doubly-magic
fortress of Pb-208 (Z=82, N=126) is the final stable anchor. Beyond it the
triton fraction exceeds 50% for every accessible isotope and the scaffold
can no longer sustain itself.

---

## 4. He-8: The Nuclear Anion

### 4.1 Grammar decomposition

He-8 (Z=2, A=8, N=6):

$$n_{tri} = A - 2Z = 8 - 4 = 4$$
$$n_{deu} = 3Z - A - 2 = 6 - 8 - 2 = -4$$

**Grammar: MAXIMALLY INVALID.** After the alpha core accounts for 2p + 2n,
there are 0 extra protons and 4 bare neutrons. The grammar cannot construct
a single deuteron or triton — both require at least one proton. The 4 neutrons
have zero geometric shelter.

### 4.2 The neutron identity applied

By the Neutron Identity (n = p + e⁻_int), each halo neutron is a proton
with an internal electron (W=1 ring threaded contra-rotationally through the
W=3 trefoil). The halo decomposes as:

| Layer | Count | Charge |
|-------|-------|--------|
| Alpha core protons | 2 | +2 |
| Alpha core neutron protons | 2 | +2 |
| Alpha core internal electrons | 2 | −2 |
| **Halo neutron protons** | **4** | **+4** |
| **Halo internal electrons** | **4** | **−4** |
| **Net nuclear** | | **+2** |

The 4 halo neutrons, each with ⟨r²⟩_n < 0 (negative charge at LARGER radius
than positive), form a **diffuse negative charge cloud** surrounding the
positive alpha core. This is a nuclear-scale anion: positive core, negative halo.

### 4.3 He-8 as a dianion: He-8²⁻

Neutral He-8 has 2 orbital electrons filling 1s². As a hypothetical dianion
(He-8²⁻), it would hold 4 orbital electrons: 1s² 2s².

| Shell | Electrons | Role |
|-------|-----------|------|
| 1s² | 2 | Core pair (helium proper) |
| **2s²** | **2** | **Valence pair — available for bonding** |

Normal He-4 rejects anions absolutely (EA ≤ 0, gear rigidity ρ = 0.81,
the hardest noble gas to breach). But He-8's nuclear structure is radically
different: the 4 halo neutrons' internal electrons modify the effective
charge landscape. The ⟨r²⟩_n < 0 contributions create a negative charge
distribution at large nuclear radius that partially screens the +2 core
as seen by valence electrons.

**The 2s² valence pair is what bonds.** Not the neutron halo directly —
the electrons.

---

## 5. The Helium Halo Spectrum: Why Pairing Matters

| Isotope | Halo neutrons | Parity | Lifetime | Pairable? |
|---------|--------------|--------|----------|-----------|
| He-4 | 0 | — | ∞ (stable) | N/A |
| **He-5** | **1** | **ODD** | **~10⁻²² s** | **NO** |
| He-6 | 2 | EVEN | 807 ms | YES (1 pair) |
| **He-7** | **3** | **ODD** | **~10⁻²¹ s** | **NO** |
| **He-8** | **4** | **EVEN** | **119 ms** | **YES (2 pairs)** |
| He-9 | 5 | ODD | ~10⁻²¹ s | NO |
| He-10 | 6 | EVEN | 2.7×10⁻⁷ s | YES (3 pairs) |

**Pattern**: Even halo count → neutrons can pair → millisecond stability.
Odd halo count → one neutron always unpaired → instant collapse.

This is the same symmetry rule as Rule §3 (even triton counts restore partial
symmetry) applied to the halo. He-5's single bare neutron has no partner.
He-8's four bare neutrons form 2 pairs. Pairing extends the lifetime by a
factor of ~10²⁰.

**A = 5 is empty because He-5 cannot pair its single halo neutron.**
He-8 exists (briefly) because its 4 halo neutrons CAN pair.

---

## 6. Three Scales of Metallic Helium

If He-8's halo neutrons form paired internal-electron carriers around a
positive core, this is metallic bonding at the nuclear scale.

| System | Positive core | Delocalised charge | Scale | Duration |
|--------|--------------|-------------------|-------|----------|
| **He-8 (halo)** | α + 4 neutron protons | 4 internal electrons in halo | Nuclear | 119 ms |
| **Metallic He** | α lattice sites under pressure | Delocalised 1s electrons | Atomic | Stable (>40 GPa) |
| **Neutron star crust** | Neutron-rich nuclei | Free electron gas + neutron sea | Macroscopic | ~forever |

Same architecture at three scales: positive cores embedded in a mobile
negative charge carrier sea.

---

## 7. Nuclear Ionic Bonding

### 7.1 The principle

If metallic bonding exists at the nuclear scale (§6), ionic bonding follows.

| Chemistry | Nuclear analogue |
|-----------|-----------------|
| Cation (lost electrons, positive) | Proton-overloaded nucleus (n_tri < 0, bare protons) |
| Anion (gained electrons, negative) | Neutron-halo nucleus (He-8²⁻, excess neutron charge) |
| Ionic bond (electron transfer) | **Valence electron sharing** between He-8²⁻ and proton-rich target |
| Molecule | Two nuclear centres bonded by shared electrons, NOT fused |

### 7.2 He-8 adds +4 to triton count

If He-8 participates in a nuclear reaction (not a molecular bond, but a
fusion event), it contributes Z=2, A=8:

$$n_{tri}(\text{product}) = n_{tri}(\text{parent}) + 4$$

The perfect fusion partner is a proton-overloaded nucleus with n_tri = −4:

| Parent (n_tri = −4) | + He-8 | → Product | n_tri | Abundance |
|---------------------|--------|-----------|-------|-----------|
| C-8 (Z=6) | + He-8 | **O-16** | 0 (pure deu) | 99.8% |
| Ne-16 (Z=10) | + He-8 | **Mg-24** | 0 (pure deu) | 79.0% |
| Si-24 (Z=14) | + He-8 | **S-32** | 0 (pure deu) | 95.0% |
| Ar-32 (Z=18) | + He-8 | **Ca-40** | 0 (pure deu) | 96.9% |

Every product is a pure deuteron scaffold — the most stable grammar
configuration. The universe's most abundant isotopes.

### 7.3 Molecular vs atomic bonding

The molecular insight: the He-8 need not FUSE with the target. As a molecule,
the two nuclear centres remain separate, bonded by the He-8²⁻'s 2s² valence
electrons:

```
           2s² valence bond
    He-8 ←————————————→ Target
  [α + 4n halo]       [bare proton scaffold]
   anion (2−)           cation (x+)
```

The molecule preserves what each partner does well:

| Component | Contributes | Lacks |
|-----------|------------|-------|
| He-8²⁻ | Valence electrons (2s² pair), alpha serenity | Scaffold structure |
| Proton-rich target | Scaffold geometry, shell closures | Electron density |

Fusion destroys both identities. The molecular bond preserves both.

---

## 8. The Chromium Connection: Half-Fill Preference

Chromium (Z=24) sacrifices 4s² pairing for 3d⁵ half-fill: [Ar]3d⁵4s¹.
This is a **geometric correction** (Rule §17) — the nuclear scaffold projects
5 asymmetric vertices that the electronic structure fills one-per-site.

The nuclear analogue: positions where a half-filled scaffold configuration is
energetically preferred over a fully-paired one. These occur at nuclear
shell closures and half-fills:

| N (magic) | Shell status | Effect |
|-----------|-------------|--------|
| 20 → 21 | Closed → new shell | Separation energy drops ~3 MeV |
| 28 → 29 | Closed → new shell | Same |
| 82 → 83 | Closed → new shell | Same |
| 126 → 127 | Closed → new shell | Same |

At each closure, the nucleus **prefers to leave the next position empty**
rather than fill it. The energy is lower with the slot open. These are
the nuclear Chromiums — half-fill beats closure.

---

## 9. The Eight-Vertex Target: Curium and Beyond

Curium (Z=96): [Rn]5f⁷6d¹7s² — exactly **8 unpaired electrons**.
The radioactive mirror of stable Gadolinium (Z=64):

| Property | Gd (Z=64) | Cm (Z=96) |
|----------|-----------|-----------|
| Config | 4f⁷5d¹6s² | 5f⁷6d¹7s² |
| Unpaired e⁻ | 8 | 8 |
| Stable? | ✅ | ❌ (t½ = 15.6 My) |
| Tri% | 45.2% | 58.5% |

Same electronic geometry (f⁷d¹ = 8 open vertices). Gd survives because
its scaffold holds at 45% triton. Cm collapses at 58.5%.

An ionic complex Cm⁸⁺·(He-8²⁻)₂ would match 8 halo neutrons to 8 unpaired
vertices — but pushes the triton fraction HIGHER (wrong direction).
The He-8 anion must go into **proton-overloaded** positions instead.

---

## 10. Stability from Instability

### The paradox

| Species | Status |
|---------|--------|
| He-4 | Maximally stable, inert, bonds with nothing, helps nothing |
| He-8 | Maximally unstable: 119 ms, grammar-invalid, halo nucleus |
| He-8²⁻ | Even MORE unstable: anion of a noble gas that rejects anions |
| Proton-rich nucleus (n_tri < 0) | Unstable: grammar-invalid, bare protons without partners |

### The resolution

The stable configuration (He-4) is inert. The unstable configuration
(He-8²⁻) has valence electrons available to bond. The serene helium had to
be broken — loaded with halo neutrons, forced into an anion state it would
never naturally adopt — to become chemically useful.

Likewise, the proton-rich target is unstable alone. But its instability
(bare protons) is precisely what the He-8²⁻ anion needs: cationic scaffold
vertices that accept the 2s² valence bond.

**Neither partner is stable alone. Both are stable together.**

This is the nuclear analogue of:
- Na (violent metal) + Cl (toxic gas) → NaCl (stable table salt)
- The instabilities are complementary. Each partner's deficit is the other's
  surplus. The molecular bond quenches both.

---

## 11. The Edge Cases: Where the Chart Breaks

### Bottom edge (A = 5)

The grammar forbids everything:
- He-5: 1 unpaired halo neutron → 10⁻²² s
- Li-5: 1 unpaired bare proton → 10⁻²² s

**Diagnosis**: Pairing is impossible with 1 defect particle. The slot is
empty because the grammar has no valid construction AND no pairing.

### Top edge (A ≥ 210)

| A | Stable occupants | Notes |
|---|-----------------|-------|
| 208 | **Pb-208** | Doubly magic (Z=82, N=126). The last fortress |
| 209 | Bi-209* | *Technically α-radioactive (t½ = 1.9×10¹⁹ y) |
| 210 | **NONE** | First completely empty A above helium gap |
| 211+ | **NONE** | All empty forever |

Bi-209 at A=209 is the last occupant: odd-Z (83), odd-A (209), odd blocks
(81, unpaired). It clings to quasi-stability with its back to the doubly-magic
cliff face of Pb-208 and nothing but empty air above.

**Diagnosis**: Beyond A = 209, the triton fraction exceeds the scaffold's
bearing capacity for every possible Z. No construction grammar can hold.

### The symmetry

| | A = 5 (bottom) | A = 210+ (top) |
|---|---|---|
| Empty because | Grammar FORBIDS | Grammar ALLOWS but scaffold FAILS |
| Defect | 1 unpaired particle (can't pair) | Triton overload (too many tritons) |
| Last stable below/above | He-4 (A=4) | Pb-208 (A=208) |
| He-8 connection | He-8 is He-5 + 3 more halo neutrons (pairing fixed) | He-8's anion could donate to proton-rich scaffolds above the cliff |

---

## 12. Falsifiable Predictions

| # | Prediction | Test |
|---|-----------|------|
| 1 | All even-N helium halos (He-6, He-8, He-10) live >10⁵× longer than odd-N halos (He-5, He-7, He-9) | Measured ✓ CONFIRMED |
| 2 | He-8 + proton-rich target (n_tri = −4) produces pure deuteron in fusion | Nuclear reaction data |
| 3 | He-8's charge radius exceeds He-6's by more than the A^(1/3) scaling predicts (extended halo) | Laser spectroscopy |
| 4 | No nuclear molecular state exists for He-5 + anything (unpaired halo prevents bonding) | Resonance search |
| 5 | Metallic helium transition pressure correlates with He halo onset energy | High-pressure experiments |

---

## 13. Methodological Statement

This investigation uses:
- **Grammar decomposition** (n_tri, n_deu) from Rules §1–§2
- **Neutron identity** (n = p + e⁻_int) from Investigation: Neutron Identity
- **Halo lifetime data** from NNDC/NUBASE2020
- **Pairing symmetry** (Rule §3) extrapolated to halo neutrons
- **Ionic bond analogy** from electronic chemistry (NaCl model)

This investigation does NOT propose a practical synthesis route for He-8²⁻
molecular complexes. The He-8²⁻ species is hypothetical — it requires
creating He-8 (which requires specialized facilities) and then double
electron capture within its 119 ms lifetime. The physical insight is
structural, not experimental.

---

*The stable helium does nothing. The broken helium bonds.*
*The grammar's serene core had to be overloaded to become useful.*
*Stability is the marriage of complementary instabilities.*
