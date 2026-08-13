# NSEQ05 Assessment — Pure-shell incidence formalized

**Date:** 2026-08-09  
**Instruments:** `nseq05_pure_shell_incidence.py`, `nseq05_packer_smoke.py`  
**Stdout:** `.audit-tmp/nseq05_run.txt`, `.audit-tmp/nseq05_smoke.txt`  
**Edited:** sequencers (site + docs) — interleaved pure-shell packer  
**Canon (`laws.hpp`):** not edited — proposal amended  

## 1. Formal relations (proved)

### Pure-shell species order

```
2 —D6→ 8 —D12→ 20 —T8→ 28 —D12→ 40 —T10→ 50 —D20→ 70
  —T12→ 82 —D30→ 112 —T14→ 126 —D42→ 168 —T16→ 184
```

Grouped engine increments such as `+12d+10t → 50` are **closure sums**, not
evidence of a mixed d+t shell. Stella = tritons; next shell = deuterons; next =
tritons.

### Capacities as vertex / link

| Form | Value | Role |
|---|---|---|
| `B(n)=V=2(n+1)` | 8,10,12,14,… | triton shell seats |
| `R(n)=E=n(n+1)` | 12,20,30,42,… | intervening deuteron seats |
| `F(n)=V+E` | (n+1)(n+2) | tier total |

**Link rule PASS** for D-schedule 12→20→30.  
**Face rule 12→16→20 EXCLUDED** (first “12” was lucky, not mechanism).

### Stella → cuboct → 14

| Step | Result |
|---|---|
| T₈ nearest links | 12 (= cube edges) |
| Edge midpoints | cuboctahedron; polar split **3+6+3** |
| Cuboct faces | 8△ + 6□ = 14 |
| Face normals (△-polar) | 2 poles + 6 @≈19.47° + 6 @≈35.26° |

**Adjacency:** that 14-set orients **T₁₄**, not the immediate post-D₁₂ triton
shell (**T₁₀**).

### 14 → 42 contact graph

`24 (T−Q) + 12 (T−T) + 6 (Q−Q polar) = 42`, two branches, both 6-regular on 14
vertices, connected. Midpoint directions: 36 oriented uniques (radial doublets
present).  
**OPEN debt:** `E=42 > 3V−6=36` ⇒ not a simple spherical polyhedron — internal /
crossing topology required, or D₄₂ extrapolation revised.

## 2. Sequencer corrections applied

1. Pack order interleaved by `SHELL_SEQ` (species-pure).  
2. Post-T₈ D₁₂ uses **cuboct** directions (not a second icosahedron).  
3. T₈ = polar/stella; T₁₄ = cuboct face normals; T₁₀/T₁₂ = polar family.  
4. Capacities unchanged; packing smoke He/C/O/Fe/U/Ca-48 **PASS**.

## 3. Claim ledger

| ID | Status |
|---|---|
| NSEQ05-C1 | **PASS** |
| NSEQ05-C2 | **PASS** (H2; H3 excluded) |
| NSEQ05-C3 | **PASS** |
| NSEQ05-C4 | **PASS** (two branches; D₄₂ bound debt recorded) |
| NSEQ05-C5 | **PASS** |
| NSEQ05-C6 | **PASS** |

## 4. Headline

**`PURE_SHELL_INCIDENCE_FORMALIZED`**

## 5. Propose-and-wait (`laws.hpp`)

Amend prior belt→shell rename proposal:

- Expand grouped `+12d+10t` comments into pure-shell sequence above.  
- Replace rolling-equator derivation text with vertex/link (`V`/`E`) reading.  
- Note T₁₄ = cuboct face normals; D₁₂(post-T₈) = cuboct vertices.  
- Keep numeric `static_assert`s.

Reply **approve laws.hpp belt→shell rename** (covers this prose) to apply.
