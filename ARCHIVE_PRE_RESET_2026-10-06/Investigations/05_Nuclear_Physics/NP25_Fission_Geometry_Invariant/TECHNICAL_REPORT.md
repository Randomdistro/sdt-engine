# NP25 — Technical Report (RUN 1, 2026-07-19)
### The scission invariant, the G_core selection rule, and one retracted claim

## 1. The invariant — proved, not fitted

For any binary split in which **each daughter carries its own alpha core**, with D = n_d1+n_d2 and T = n_t1+n_t2:

```
A:  8 + 2D + 3T = 4 + 2n_dP + 3n_tP
Z:  4 +  D +  T = 2 +  n_dP +  n_tP      =>  D+T = n_dP+n_tP-2
(A) - 2*(Z):        T = n_tP                  TRITONS PRESERVED EXACTLY
back-substitute:    D = n_dP - 2              DEUTERONS DROP BY EXACTLY 2
```

$$\boxed{T = n_{tP}} \qquad \boxed{D = n_{dP}-2}$$

**Therefore the unique scission operation is `2d → α`** — A=4, Z=2, **zero neutrons emitted.**

**Verified on 8 complementary pre-neutron pairs** of ²³⁶U* (38d + 52t), every one giving D=36, T=52:

| light | n_d | n_t | heavy | n_d | n_t | D | T |
|---|---|---|---|---|---|---|---|
| Se-92 | 8 | 24 | Ce-144 | 28 | 28 | 36 | 52 |
| Kr-96 | 10 | 24 | Ba-140 | 26 | 28 | 36 | 52 |
| Sr-98 | 14 | 22 | Xe-138 | 22 | 30 | 36 | 52 |
| Zr-100 | 18 | 20 | Te-136 | 18 | 32 | 36 | 52 |
| **Mo-104** | **20** | **20** | **Sn-132** | 16 | 32 | 36 | 52 |
| Ru-108 | 22 | 20 | Cd-128 | 14 | 32 | 36 | 52 |
| Pd-112 | 24 | 20 | Pd-124 | 12 | 32 | 36 | 52 |
| Pd-118 | 18 | 26 | Pd-118 | 18 | 26 | 36 | 52 |

## 2. RETRACTED: my `2t → α + 2n` and the ν=2 floor

I proposed `2t → α + 2n`, giving a **mandatory ν = 2**. **This is falsified.** Measured U-235(n_th,f) prompt multiplicity:

| ν | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
|---|---|---|---|---|---|---|---|
| P(ν) | 3.17% | 17.20% | 33.63% | 30.38% | 12.68% | 2.66% | 0.26% |

**P(ν<2) = 20.4% of all fissions.** A hard floor of 2 forbids one fifth of observed events. Mean = 2.412 (evaluated ~2.41).

**Root cause of the error:** I fused the *scission* step with the *evaporation* step. Corrected sequence:

- **scission:** `2d → α` — forms the second core, emits **nothing**
- **post-scission:** `ν × (t → d + n)` — excited fragments boil off, **event-dependent**
- **net:** Δn_t = −ν, Δn_d = +ν − 2

This also predicts the *right* emission site: prompt neutrons come from **fully-accelerated fragments**, not from the neck — which is what is measured. My version put them at scission and would have given the wrong angular distribution.

## 3. The G_core selection rule (recovered from `atomicus-stick.html`, not reconstructed)

$$G_{core} = |n_d - n_t| + (n_t \bmod 2)$$

G_core = 0 ⟹ n_d = n_t (**the golden line, u = 0**) with even n_t. This forces an integer series with no freedom:

$$n_d = n_t = k \;\Rightarrow\; A = 4+5k,\quad Z = 2+2k,\quad k \text{ even}$$

| k | light | complement in ²³⁸U (+2n) | magic? |
|---|---|---|---|
| 16 | Se-84 | Ce-152 | — |
| 18 | Sr-94 | Xe-142 | — |
| **20** | **Mo-104** | **Sn-132 (Z=50, N=82)** | **DOUBLY MAGIC** |
| 22 | Pd-114 | Pd-122 | — |
| 24 | Sn-124 | Mo-112 | — |

**k=20 is the only member of the entire series whose complement is magic in either Z or N.** Golden-line light fragment ⟹ doubly-magic heavy partner. One geometric condition, shell closure falling out the other end. 104+132+2 = 238 ✓, 42+50 = 92 ✓.

This is the stick model's `primarySpike` (¹⁰⁴Mo + ¹³²Sn + 2n), labelled *"the primary G_core=0 prediction channels."*

## 4. Forced topology
Conservation alone (no coordinates assumed) gives: **two alpha-seeded lobes** — one inheriting the parent core, one carrying a **latent 2d seed** — joined by a **triton-bearing neck**. "Coreless daughter" is retired: the second fragment carries its core *in potential* and realises it at scission.

**G_core and the invariant are complementary, not competing:** G_core selects *which* cut is preferred; the invariant fixes *what the cut costs*.

## 5. Open, and honestly blocked
The ordered (r,θ,φ) placement is **not** in the repo. `092_U235.md` holds counts only (1α + 39d + 51t) and flags its own unresolved point ("unpaired electrons = 4 → no match"). NP17 states heavy-nucleus geometry must be imported from absent companion files. **Counts cannot fix coordinates uniquely** — reconstruction requires event-resolved Y(A,Z,TKE,ν), not averaged mass peaks. → NP26.

## 6. Prose slip (minor, invariant untouched)
Sr-98/Xe-138 given as (12d+22t)+(24d+30t); actual n_d(Sr-98)=**14**, n_d(Xe-138)=**22**. Totals agree (36d). Kr-96/Ba-140 correct as written.

## Verdict
> Prompt completion **B** · Physics class **NATIVE** on the invariant (proved from conservation) · **G_core: recovered, not derived** — it was already in the canon · ν-floor claim **KILLED (mine)** · coordinates **DEFERRED to NP26**.
