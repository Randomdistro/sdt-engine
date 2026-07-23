# NP24-A — Technical Report: the 45 anomalies, and what they exposed
### RUN 1, 2026-07-21 · J. C. Harvey, Melbourne
### Status: **SELF-CORRECTION.** The strongest claimed grammar law is demoted to DEGENERATE.

> **Task:** NP24-M flagged 45 nuclides with n_d odd, n_t even and yet μ = 0 (6.4% of that cell)
> as "worth its own look" and did not look. All 45 examined here, in sequence, no sampling.

---

## 1. The 45, complete

All from NUBASE2020 ground states with parsed spin (3043 valid-grammar nuclides).

| # | nuclide | Z | N | n_d | n_t | J | tentative | half-life | class |
|---|---|---|---|---|---|---|---|---|---|
| 1 | Cl-34 | 17 | 17 | 15 | 0 | 0 | | 1.5267 s | N=Z |
| 2 | K-50 | 19 | 31 | 5 | 12 | 0 | | 472 ms | n-rich |
| 3 | Sc-42 | 21 | 21 | 19 | 0 | 0 | | 680.72 ms | N=Z |
| 4 | V-46 | 23 | 23 | 21 | 0 | 0 | | 422.62 ms | N=Z |
| 5 | Mn-50 | 25 | 25 | 23 | 0 | 0 | | 283.21 ms | N=Z |
| 6 | Co-54 | 27 | 27 | 25 | 0 | 0 | | 193.27 ms | N=Z |
| 7 | Ga-62 | 31 | 31 | 29 | 0 | 0 | | 116.122 ms | N=Z |
| 8 | Ga-64 | 31 | 33 | 27 | 2 | 0 | | 2.627 m | n-rich |
| 9 | Ga-66 | 31 | 35 | 25 | 4 | 0 | | 9.304 h | n-rich |
| 10 | Ga-84 | 31 | 53 | 7 | 22 | 0 | | 97.6 ms | n-rich |
| 11 | As-66 | 33 | 33 | 31 | 0 | 0 | | 95.77 ms | N=Z |
| 12 | Br-70 | 35 | 35 | 33 | 0 | 0 | | 78.8 ms | N=Z |
| 13 | Br-74 | 35 | 39 | 29 | 4 | 0 | yes | 25.4 m | n-rich |
| 14 | Rb-74 | 37 | 37 | 35 | 0 | 0 | | 64.78 ms | N=Z |
| 15 | Rb-78 | 37 | 41 | 31 | 4 | 0 | | 17.66 m | n-rich |
| 16 | Rb-90 | 37 | 53 | 19 | 16 | 0 | | 158 s | n-rich |
| 17 | Rb-92 | 37 | 55 | 17 | 18 | 0 | | 4.48 s | n-rich |
| 18 | Rb-98 | 37 | 61 | 11 | 24 | 0 | yes | 115 ms | n-rich |
| 19 | Y-78 | 39 | 39 | 37 | 0 | 0 | yes | 54 ms | N=Z |
| 20 | Y-96 | 39 | 57 | 19 | 18 | 0 | | 5.34 s | n-rich |
| 21 | Y-98 | 39 | 59 | 17 | 20 | 0 | | 548 ms | n-rich |
| 22 | Y-104 | 39 | 65 | 11 | 26 | 0 | yes | 197 ms | n-rich |
| 23 | Nb-82 | 41 | 41 | 39 | 0 | 0 | yes | 51 ms | N=Z |
| 24 | Tc-86 | 43 | 43 | 41 | 0 | 0 | yes | 55 ms | N=Z |
| 25 | Rh-90 | 45 | 45 | 43 | 0 | 0 | yes | 29 ms | N=Z |
| 26 | Ag-94 | 47 | 47 | 45 | 0 | 0 | | 27 ms | N=Z |
| 27 | Ag-116 | 47 | 69 | 23 | 22 | 0 | yes | 3.83 m | n-rich |
| 28 | In-98 | 49 | 49 | 47 | 0 | 0 | yes | 30 ms | N=Z |
| 29 | Sb-134 | 51 | 83 | 17 | 32 | 0 | yes | 674 ms | n-rich |
| 30 | Cs-142 | 55 | 87 | 21 | 32 | 0 | | 1.687 s | n-rich |
| 31 | Pr-144 | 59 | 85 | 31 | 26 | 0 | | 17.28 m | n-rich |
| 32 | Pm-158 | 61 | 97 | 23 | 36 | 0 | yes | 4.8 s | n-rich |
| 33 | Eu-156 | 63 | 93 | 31 | 30 | 0 | | 15.19 d | n-rich |
| 34 | Eu-166 | 63 | 103 | 21 | 40 | 0 | | 1.24 s | n-rich |
| 35 | Ho-166 | 67 | 99 | 33 | 32 | 0 | | 26.812 h | n-rich |
| 36 | Ho-172 | 67 | 105 | 27 | 38 | 0 | | 25 s | n-rich |
| 37 | Lu-170 | 71 | 99 | 41 | 28 | 0 | | 2.012 d | n-rich |
| 38 | Re-192 | 75 | 117 | 31 | 42 | 0 | yes | 15.4 s | n-rich |
| 39 | Tl-206 | 81 | 125 | 35 | 44 | 0 | | 4.202 m | n-rich |
| 40 | Ac-224 | 89 | 135 | 41 | 46 | 0 | yes | 2.78 h | n-rich |
| 41 | Np-234 | 93 | 141 | 43 | 48 | 0 | yes | 4.4 d | n-rich |
| 42 | Am-234 | 95 | 139 | 49 | 44 | 0 | | 2.32 m | n-rich |
| 43 | Md-254 | 101 | 153 | 47 | 52 | 0 | | 10 m | n-rich |
| 44 | Lr-256 | 103 | 153 | 51 | 50 | 0 | yes | 27.9 s | n-rich |
| 45 | Db-258 | 105 | 153 | 55 | 48 | 0 | | 2.17 s | n-rich |

**Sample-quality facts that must be stated before any law is drawn:**
- **0 of 45 are stable.** Every one is a short-lived β emitter.
- **15 of 45 carry parenthesised (tentative) J assignments.** A third of the "anomalies" are evaluator
  systematics, not measurements — and the systematic used to assign them is *the very pattern being tested*.
  Those 15 cannot serve as independent evidence.
- All 45 are Z-odd and N-odd. This is **forced by the cell definition**, not a finding (see §3).

---

## 2. The one real sub-structure: the n_t = 0 sequence

n_t = 0 means N = Z. Taking every such nuclide with n_d odd, in order:

| n_d | 1 | 3 | 5 | 7 | 9 | 11 | 13 | **15** | 17 | **19** | **21** | **23** | **25** | 27 | **29** | **31** | **33** | **35** | **37** | **39** | **41** | **43** | **45** | **47** |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| | Li-6 | B-10 | N-14 | F-18 | Na-22 | Al-26 | P-30 | **Cl-34** | K-38 | **Sc-42** | **V-46** | **Mn-50** | **Co-54** | Cu-58 | **Ga-62** | **As-66** | **Br-70** | **Rb-74** | **Y-78** | **Nb-82** | **Tc-86** | **Rh-90** | **Ag-94** | **In-98** |
| J | 1 | 3 | 1 | 1 | 3 | 5 | 1 | **0** | 3 | **0** | **0** | **0** | **0** | 1 | **0** | **0** | **0** | **0** | **0** | **0** | **0** | **0** | **0** | **0** |

Below n_d = 15: **7/7 have J ≠ 0.** At and above: **15/17 have J = 0**, with exactly two violations:

- **K-38** (Z = N = 19) — one nucleon below the doubly-magic self-conjugate Ca-40
- **Cu-58** (Z = N = 29) — one nucleon above the doubly-magic self-conjugate Ni-56

Both violations sit adjacent to the only two doubly-magic N=Z cores in the range. That is a genuine
structural signature — **and it is a shell-model signature.** The grammar coordinates contain no
magic numbers; the explanation had to be imported. **The crossover at n_d ≈ 15 is the known
T = 0 → T = 1 ground-state transition in odd-odd N=Z nuclei.** Nothing here is native to the grammar.

**The other 30 (neutron-rich) show no structure at all.** Best discriminators over the full 707-nuclide cell:

| candidate rule | captures | purity |
|---|---|---|
| n_t = 0 and n_d ≥ 15 | 15/45 | 88.2% |
| n_t = 0 (N=Z) | 15/45 | 62.5% |
| n_t ≡ 0 mod 4 | 33/45 | 9.3% |
| v ≡ 1 mod 4 | 27/45 | 7.6% |
| n_d ≡ 3 mod 4 | 26/45 | 7.3% |
| n_d = n_t + 1 | 5/45 | 19.2% |

The mod-4 rules capture more only by firing on 320+ false positives. **No function of (n_d, n_t)
separates the 45 from the 662.** 98.5% is a ceiling, not a way-station.

---

## 3. What the 45 actually exposed — the load-bearing result

Chasing the cell definition back to its algebra:

$$n_t = A - 2Z = \boxed{N - Z} \qquad n_d = 3Z - A - 2 = \boxed{2Z - N - 2} \qquad n_d + n_t = \boxed{Z - 2}$$

Verified exactly on all 3043 nuclides, **0 violations**. So:

> **The grammar coordinates are an invertible linear map of (Z, N).**
> n_t *is* the neutron excess. v *is* Z − 2. The transform adds no information and removes none.

The parity consequences follow immediately, and were checked with **0 mismatches** across all 3043:

| grammar statement | is *identically* |
|---|---|
| n_d even ∧ n_t even | **even-even** |
| n_t odd | **odd-A** |
| n_d odd ∧ n_t even | **odd-odd** |

Which re-reads NP24-M's two headline laws:

| claimed law | score | what it actually is |
|---|---|---|
| n_d even ∧ n_t even ⟹ μ = 0 — **812/812** | 812/812 | **"even-even nuclei have J = 0 ground states."** The pairing rule. Known since the 1930s. |
| n_t odd ⟹ μ ≠ 0 — **765/765** | 1523/1524 | **"odd-A nuclei have J ≠ 0."** *Trivially true*: odd A forces half-integer J, which cannot be 0. |

The single apparent exception — Te-145 listed as `0+` — is a **NUBASE entry error**: A = 145 is odd,
so an integer J is impossible. Not physics.

**Verdict on NP24-M Part A: DEGENERATE.** It was called "the strongest surviving grammar law in the
repo." It is the nuclear pairing rule wearing grammar notation, plus a tautology. It is *true* — and
it is *not evidence for the grammar*, in exactly the way I1 was true and not evidence (Moseley).

---

## 4. Scope of the demotion — what this does and does not touch

Because (n_d, n_t) ↔ (Z, N) is invertible, **every claim expressed purely in grammar coordinates is a
(Z, N) claim in disguise.** Applying that test to the rest of the cascade:

| claim | re-reads as | status after this run |
|---|---|---|
| magnetism law (NP24-M A) | even-even pairing + a tautology | **DEGENERATE** (demoted here) |
| stability band f_t ≤ 0.551 | (N−Z)/(Z−2) ≤ 0.551 — a neutron-excess-vs-Z band | **DEGENERATE** — a restatement of the valley of stability. Was already logged NECESSARY-NOT-SUFFICIENT; now also non-native. |
| G_core = \|n_d−n_t\| + (n_t mod 2) | \|3Z−2N−2\| + ((N−Z) mod 2) | still a **selection rule**, but its content is a (Z,N) function — it must earn its keep by *prediction*, not by derivation |
| scission invariant T = n_tP, D = n_dP − 2 | "N−Z is conserved when no neutrons are emitted" | **UNCHANGED and still sound** — it was *proved from A,Z conservation*, and was labelled as such. The mystique is gone; the proof is not. |
| R6 residual law (f_t + A^−1/3 + pairing, OOS R² = +0.933) | a (Z,N) fit | **UNCHANGED as an empirical fit**, but it can no longer be called a *grammar* discovery |

**What is NOT killed:** the grammar as a *constructional claim* — that a nucleus is physically
assembled from one α core plus n_d deuterons and n_t tritons. That claim is about **structure**, and
this run says nothing about it either way. What this run establishes is narrower and sharper:

> **Arithmetic identities in grammar coordinates cannot be evidence for the grammar,
> because the coordinates are a relabelling of the data they are tested against.**
> Evidence for the grammar must come from something (Z, N) does not already fix —
> geometry, ordering, or a prediction that fails under the standard parameterisation.

That is the standing requirement the cascade now has to meet.

---

## 5. §G mirror — what I was accepting on faith

I ran the NP24-M tables, saw 812/812 and 765/765, and reported "exceptionless over a complete set"
without once asking **what the cell definition was in (Z, N)**. One line of algebra — available from
the start, requiring no data — would have caught it. The 100% score was not a sign of a deep law; a
100% score on a large heterogeneous set is a sign that *the two sides of the test are not independent*,
and that should have been the first hypothesis rather than the last.

The tell I missed: I described it as "the strongest surviving grammar law in the repo" — a
superlative, generated by me, about my own output, with no independence check performed.

---

## Verdict

> Prompt completion **A** (all 45 run in sequence, none sampled, none reordered) ·
> **45 anomalies: no grammar rule found — 98.5% is a ceiling** ·
> One real sub-structure (n_t = 0, n_d ≥ 15) which is the **T=0→T=1 crossover, imported not derived**,
> with both violations explained by adjacency to doubly-magic N=Z cores ·
> **NP24-M Part A demoted: NATIVE → DEGENERATE** ·
> **New standing constraint: the grammar↔(Z,N) map is invertible; identities in grammar coordinates
> are not evidence.** ·
> Data flaw logged: NUBASE2020 lists Te-145 as `0+` (impossible for odd A).
