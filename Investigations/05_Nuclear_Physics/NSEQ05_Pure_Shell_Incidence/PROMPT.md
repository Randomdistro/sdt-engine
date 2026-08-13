# NSEQ05 — Pure-shell incidence: T₈→D₁₂→T₁₀… and stella→cuboct→14

> **Status:** PRE-REGISTERED — 2026-08-09.  
> **Upstream:** Author — stella octahedron = all tritons; next shell all
> deuterons; next all tritons. Grouped `+12d+10t` is a closure increment, not
> one mixed shell.  
> **Canon:** no `laws.hpp` edit (propose-and-wait for comment/sequence prose).

## 0. Frozen pure-shell sequence (species-by-species)

From the repository arithmetic, expanded:

| Step | Shell | ΔN | Cumulative N |
|---|---|---|---|
| — | α core | 2 | 2 |
| D | D₆ | +6 | 8 |
| D | D₁₂ (pre) | +12 | 20 |
| T | **T₈** (stella / dual tetra) | +8 | **28** |
| D | **D₁₂** (cuboct / T₈ edge midpoints) | +12 | 40 |
| T | T₁₀ | +10 | **50** |
| D | D₂₀ | +20 | 70 |
| T | T₁₂ | +12 | **82** |
| D | D₃₀ | +30 | 112 |
| T | T₁₄ (cuboct face normals) | +14 | **126** |
| D | D₄₂ | +42 | 168 |
| T | T₁₆ | +16 | **184** (forward) |

Magic closures 28,50,82,126 are **T-shell completions**, not mixed d+t shells.

## 1. Hypotheses under test

| ID | Hypothesis |
|---|---|
| H1 | Capacities: `V=B(n)=2(n+1)`, intervening `E=R(n)=n(n+1)`, `F=V+E`. |
| H2 | **Link** rule: next D after Tₙ has E = n(n+1) seats. Predicts 12,20,30 for n=3,4,5. |
| H3 | **Face** rule (triangulated): next D has face count continuing 12→16→20. **Must fail** vs schedule 12→20→30. |
| H4 | T₈ stella nearest links = cube edges (12); midpoints = cuboctahedron; split 3+6+3 on polar axis. |
| H5 | Cuboct has 14 faces (8△+6□); face normals = T₁₄ seat set (not T₁₀). |
| H6 | On those 14 sites, polar-symmetric 6-regular contact selection yields E=42 in two branches. |

## 2. Sequencer corrections (if H1–H5 PASS)

1. Interleave pack order: D₆→D₁₂→T₈→D₁₂→T₁₀→D₂₀→T₁₂→D₃₀→T₁₄→…  
2. Second D₁₂ uses cuboct directions (not icosahedron).  
3. T₈ uses stella; T₁₄ uses cuboct face normals; T₁₀/T₁₂ use polar family `2+2n`.  
4. Capacities unchanged; `laws.hpp` symbols propose-and-wait only.

## 3. Claims

| ID | Claim |
|---|---|
| NSEQ05-C1 | Pure-shell ledger published; grouped increments disambiguated. |
| NSEQ05-C2 | H2 PASS; H3 FAIL (face rule excluded for D-schedule). |
| NSEQ05-C3 | H4–H5 PASS (stella→cuboct→14 exact). |
| NSEQ05-C4 | H6 PASS (42 edges, two orientation branches). |
| NSEQ05-C5 | Sequencer pack + dirs corrected; packing smoke He/C/O/Fe/U/Ca-48. |
| NSEQ05-C6 | No silent `laws.hpp` edit. |
