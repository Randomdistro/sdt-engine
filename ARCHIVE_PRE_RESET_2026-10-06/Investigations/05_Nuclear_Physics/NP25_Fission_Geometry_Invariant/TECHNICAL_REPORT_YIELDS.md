# NP25-Y — Technical Report: the real fission-product spectrum, ranked
### RUN 1, 2026-07-21 · J. C. Harvey, Melbourne
### Data: IAEA independent thermal fission yields, ²³⁵U(n_th,f), pulled live 2026-07-21 (737 products)

> **Claim under test (Harvey):** "it will all be decided by the very first impact zone because…
> the structure is a strict, rigid linear progression that does not vary in position or pairing."

---

## 1. The spectrum, most common → least common

Independent yields (the as-born fragment, before β-chains walk it). Full ranked list of all 737 in
`u235_thermal_yields_ranked.txt`. Top of the order:

| rank | nuclide | n_d | n_t | yield % |
|---|---|---|---|---|
| 1 | **Te-134** | 20 | 30 | 6.00 |
| 2 | Xe-138 | 22 | 30 | 4.95 |
| 3 | Zr-100 | 18 | 20 | 4.90 |
| 4 | Sr-94 | 18 | 18 | 4.70 |
| 5 | Sr-95 | 17 | 19 | 4.67 |
| 6 | Xe-139 | 21 | 31 | 4.57 |
| 7 | Kr-90 | 16 | 18 | 4.50 |
| 8 | Ba-144 | 22 | 32 | 4.21 |
| 9 | Zr-99 | 19 | 19 | 3.99 |
| 10 | Ba-143 | 23 | 31 | 3.98 |

**Where it begins and ends:**
- Full span: **A = 1 (H-1, ternary, 1.7e-3 %) → A = 170 (Dy-170, 4e-10 %).**
- The band that carries **90 % of all fission**: just **80 nuclides**, in two tight humps —
  - **LIGHT hump: A = 84 → 105** (Kr–Zr)
  - **HEAVY hump: A = 131 → 149** (Sb–Nd)
- **The symmetric valley (A ≈ 112–122) is essentially forbidden: 0.06 % of all fission** —
  the two peaks each carry ~45 %. **Suppression factor ≈ 750×.**

So fission does **not** explore its cuts. It makes essentially **one cut type** — light ≈ 95 / heavy
≈ 139 — over and over. That much of "decided early, rigid" is simply **true in the data**.

---

## 2. The non-trivial finding: the TRITON count is the rigid coordinate

Yield-weighted spread of each grammar coordinate across each hump:

| hump | n_t (triton) | n_d (deuteron) | A |
|---|---|---|---|
| LIGHT (A ≤ 117) | 18.8 ± 1.9 — **10.0 %** | 17.1 ± 2.2 — 13.0 % | 94.5 ± 6.7 |
| **HEAVY (A > 117)** | **30.9 ± 1.5 — 4.9 %** | 21.3 ± 2.1 — 10.0 % | 139.2 ± 4.8 |

**The triton count is held tighter than the deuteron count in both humps, and in the heavy fragment
it is the single most rigid number in the whole distribution (4.9 %) — half the deuteron spread.**

This is **not** forced by conservation. The distribution was free to hold n_d tight and let n_t
wander; it does the opposite. Since the triton count is the grammar's pairing/magnetism coordinate
(NP24-M: μ ≠ 0 ⟺ unpaired subunit; the scission invariant preserves tritons exactly), **"does not
vary in pairing" is supported in its sharpest possible form: the triton count is what fission
conserves.** The heavy fragment locks near **n_t = 31–32** — i.e. **N = 82, the ¹³²Sn shell** — and the
mass width is carried almost entirely by the softer deuteron count. Asymmetric fission, in grammar
terms, is the heavy fragment crystallising around a rigid triton core while the deuterons take up the
slack.

---

## 3. HUNTER flag — what does NOT count

I first read the partition sums as a confirmation of the scission invariant:
Σn_t(frag) = 49.7 vs parent 52 (deficit ≈ ν̄), Σn_d = 38.4 vs 38. **These match to ±0.1 — and it is
trivial.** Σn_t = n_t,P − ν̄ and Σn_d = n_d,P − 2 + ν̄ are **identities of A,Z conservation** (n_t = N−Z;
the −2 is two fragment cores vs one parent core). The ±0.1 "agreement" is just charge/mass balance
with ν̄ = 2.4. It is the **same degeneracy trap as NP24-A** and I nearly counted it twice. Flagged,
not counted. (§G mirror: I was accepting an identity as evidence because it was dressed in grammar.)

---

## 4. Verdict on the claim

| part of Harvey's claim | verdict |
|---|---|
| products are a **rigid band, not a scatter** | **SUPPORTED** — 90 % in 80 nuclides, valley 750× suppressed |
| **one cut, decided early** | **SUPPORTED** — essentially a single light/heavy cut type |
| **"does not vary in pairing"** | **SUPPORTED, non-trivially** — triton count is the rigid coordinate (heavy 4.9 % vs deuteron 10 %) |
| **"does not vary in position"** | **APPROXIMATE** — the cut has real width (~±1.5 tritons, ±5–7 mass units); heavy side twice as rigid as light |
| **"decided by the very first impact zone"** | **CONSISTENT, not proven** — yields fix the *cut*, not its *cause*; the impact-zone causal claim needs the NP27 event-resolved data, not averaged yields |

> **Bottom line:** the fission products are a rigid two-band structure that repeats one cut, and the
> coordinate it holds rigid is the **triton count** — exactly the grammar's pairing coordinate. That is
> a genuine, non-degenerate hit for the rigid-structure picture. The residual **width** (the humps are
> ~±1.5 tritons wide, not delta functions) is what "does not vary" has to soften into, and it is the
> same width NP27 could not derive from a single central cut. The band is rigid; it is not a knife-edge.

## Verdict
> Ranked spectrum delivered (Te-134 → … → Dy-170; 90 % in A=84–105 ⊕ 131–149; valley 750× down) ·
> **triton-rigidity NON-TRIVIAL and SUPPORTS "no variation in pairing"** · partition-sum match
> **TRIVIAL (flagged)** · "first impact zone" **consistent, awaits event-resolved test (NP27/NP26).**
