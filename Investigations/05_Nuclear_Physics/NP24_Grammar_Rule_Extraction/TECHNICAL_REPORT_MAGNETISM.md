# NP24-M — Technical Report: Magnetism and the Grammar (RUN 1, 2026-07-19)
### An exceptionless nuclear law, and a clean negative on ferromagnetism

> ⚠️ **SUPERSEDED IN PART — see `TECHNICAL_REPORT_ANOMALY_45.md` (2026-07-21).**
> Part A below is **DEGENERATE, not NATIVE.** The grammar↔(Z,N) map is invertible
> (n_t = N−Z, n_d = 2Z−N−2), so "n_d even ∧ n_t even" *is* even-even and "n_t odd" *is* odd-A.
> The 812/812 row is the nuclear pairing rule; the 765/765 row is a tautology
> (odd A forces half-integer J). The scores stand; the interpretation below does not.
> **Part B (ferromagnetism NEGATIVE) is unaffected.**

> **Claim under test (Harvey):** *"magnetism, the sole domain of TRITON geometry."*
> Tested in two distinct senses, because they are different physics.

## PART A — Nuclear moments (μ = 0 ⟺ J = 0 for a ground state; J is the complete proxy)

All **3043** NUBASE2020 ground states with parsed spin and valid grammar (Z≥3):

| n_d parity | n_t parity | μ=0 | μ≠0 | total | %μ=0 |
|---|---|---|---|---|---|
| **even** | **even** | **812** | **0** | 812 | **100.0%** |
| even | **odd** | **0** | **765** | 765 | **0.0%** |
| odd | even | 45 | 662 | 707 | 6.4% |
| odd | odd | 1 | 758 | 759 | 0.1% |

**Two rows are exceptionless over the complete set:**

$$\boxed{n_d \text{ even} \wedge n_t \text{ even} \Rightarrow \mu = 0} \quad \textbf{812/812}$$
$$\boxed{n_t \text{ odd} \Rightarrow \mu \neq 0} \quad \textbf{765/765}$$

**Rule scores:**
- **T** (μ≠0 ⟺ n_t odd — *triton only*): **2380/3043 = 78.2%**
- **U** (μ≠0 ⟺ n_d odd **or** n_t odd — *any unpaired subunit*): **2997/3043 = 98.5%**

**All 663 failures of Rule T share one signature: 662 are n_d odd / n_t even** — an unpaired **deuteron** carrying a moment with zero tritons present. Not an artefact: the free deuteron's moment is measured at **+0.857 μ_N** (≈ μ_p + μ_n = 0.880). Li-6 (n_d=1, n_t=0, J=1, μ=+0.822) is the clean case.

**Verdict:** the triton-exclusive form is **refuted at 78%**; the corrected law scores **98.5%**:

> **μ = 0 ⟺ every subunit is paired. Magnetism is the signature of an UNPAIRED SUBUNIT — deuteron or triton.**

Mechanically consistent with identical circulation: paired subunits counter-rotate and cancel; an odd one has nothing to gear against, and that residual circulation *is* the moment.

**Unexplained:** the 45 nuclides with n_d odd, n_t even and yet μ=0 (6.4% of that cell). Worth its own look.

## PART B — Ferromagnetism (coherent bulk ordering, not susceptibility)

The lab's `FERRO_Z = {26,27,28}` covers only the room-temperature three. The **complete** set of elemental ferromagnets is **Fe, Co, Ni, Gd, Tb, Dy, Ho, Er, Tm**. (Nd, Sm, Ce, Pr, Eu are *antiferromagnetic* as elements — Nd orders at 19.9 K. Neodymium's fame is Nd₂Fe₁₄B, where Fe magnetises and Nd supplies anisotropy.)

Grammar coordinates of the dominant stable isotope, all 9:

| cluster | n_t | f_t | T_C |
|---|---|---|---|
| Fe, Co, Ni | **2–5** | 0.08–0.20 | 627–1394 K |
| Gd…Tm | **29–32** | 0.46–0.50 | 20–292 K |

**Two disjoint islands. No single n_t or f_t rule spans both.** The split lands exactly where mainstream physics already puts it (3d itinerant vs 4f localised moments).

**Failed discriminators, tested on all 80 elements with a dominant stable isotope:**
- f_t band of Fe/Co/Ni [0.077, 0.200] also contains **9 non-ferromagnets** (F, Na, Al, P, Sc, Ti, Cr, Cu, Zn).
- All 9 ferromagnets have even n_d — **but so do 77 of 80 elements.**
- Cr and Mn carry n_t = 4 and 5, **identical to Fe and Co**, yet order antiferromagnetically.

**Rejected as artefact:** T_C vs n_d = −0.955 and vs n_t = −0.887 across the 9. Two clusters, 9 points, light-and-hot vs heavy-and-cold — any mass-correlated quantity scores −0.9. Reporting it as a law would be fitting.

**Verdict: NEGATIVE.** Nuclear moments are ~10³ too weak to drive bulk ordering; ferromagnetism is a 3d/4f **electron-shell** exchange phenomenon. **Triton geometry owns the nuclear moment. It does not own ferromagnetism.**

## Combined verdict
> **PART A: NATIVE, exceptionless over a complete set — the strongest surviving grammar law in the repo.**
> **PART B: KILLED — no grammar purchase on coherent bulk ordering.**
