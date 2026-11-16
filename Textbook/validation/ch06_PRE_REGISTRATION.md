# Chapter 6 — pre-registration of the worked-example instrument

Registered 2026-11-09, before `Textbook/examples/ch06_state_dimensions_and_metrology.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object. (a) The dimensional homogeneity of the relations stated in Chapters 1–9 and of the engine's seed relations; (b) the dimension matrix of the engine's seed constants, its rank and its null space (the independent dimensionless numbers); (c) the redundancies among the `measured` constants, which are checks of the stored numbers; (d) the thermal and spectral chain of the background temperature; (e) the completeness of `Textbook/sources/MEASURED_CLASSIFICATION.md` against the `measured` namespace. Base dimensions: mass M, length L, count T (an oscillator count; the SI second is its unit bridge), temperature K. No dimension for electric quantities is introduced: $k_ee^2$ enters only through $\alpha\hbar c$.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0, V0r | the `tb_common.hpp` helpers, including the rational rank and null-space routines | as printed |
| V1 | roots of $(n-x)e^x=n$: $x=2.821439372122079$ for $n=3$ and $x=4.965114231744276$ for $n=5$ (the Wien constants); golden-section search on $x\,e^{-x}$ returns $1$ | $10^{-12}$ |
| V2 | dimension algebra: force $=\mathrm{M\,L\,T^{-2}}$ from mass times acceleration; pressure $=$ force over area $=\mathrm{M\,L^{-1}T^{-2}}$; $\sqrt{\mathrm{L^2}}=\mathrm L$ and $\sqrt{\mathrm L}\ne$ an integer-exponent dimension is represented in half units; the checker reports a mismatch for $\mathrm{L}+\mathrm{T}$ | exact |
| V3 | $\int_0^\infty x^3/(e^x-1)\,dx=\pi^4/15$ by the instrument's quadrature on $[0,80]$ in 40 panels; the Wien displacement constant $b=hc/(4.965114231744276\,k_B)=2.897771955\times10^{-3}$ m K with the engine's $h$, $c$, $k_B$ | $10^{-12}$ and $10^{-9}$ |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | each of 32 relations (Chapters 1–9 and the engine's seed relations, listed in the instrument) has equal dimensions on both sides | every relation consistent; the three deliberately wrong relations in V2/T1 are flagged | yes — a slip in a power of $c$, $\ell_P$ or $T$ would be flagged |
| T2 | dimension matrix rank and Buckingham count. Seed $S_1=\{\ell_P,c,\hbar,k_B,T_{\rm CMB}\}$: rank 4, null space dimension 1, spanned by $\pm(1,-1,-1,1,1)$, product $\ell_Pk_BT_{\rm CMB}/(\hbar c)=1.9236\times10^{-32}$. $S_2=S_1\cup\{R_{\rm CMB}\}$: null space dimension 2, containing $N=R_{\rm CMB}/\ell_P$ and the product of $S_1$. $S_3=\{c,\hbar,m_e,\ell_P,m_p\}$: null space dimension 2, containing $m_p/m_e$ and $\ell_Pm_ec/\hbar$. $S_4=\{\ell_P,c,\hbar,k_B,T_{\rm CMB},m_e,m_p,R_{\rm CMB},a_0,R_p\}$: rank 4, null space dimension 6 | ranks and dimensions exact; products within $10^{-3}$ (first), $10^{-8}$ of 1836.152673426 for $m_p/m_e$ | yes — a different rank or nullity rejects |
| T3 | redundancies of the stored constants: $h=2\pi\hbar$; $r_e=\alpha\hbar/(m_ec)$ against the engine's $r_e=\alpha^2a_0$; $R_\infty=\alpha^2m_ec/(2h)$; $\mathrm{Ry_{eV}}=hcR_\infty/e$ (with the engine's `eV_to_J`); $k_ee^2=\alpha\hbar c$ (`coulomb_identity::k_e_e2_codata` against `k_e_e2`); $a_{\rm rad}=8\pi^5k_B^4/(15h^3c^3)$ | $10^{-14}$ for $h$; $10^{-9}$ for the four CODATA relations; $10^{-5}$ for $a_{\rm rad}$ (five stored digits) | yes — a mistyped digit at the $10^{-8}$ level or a mixed CODATA edition rejects |
| T4 | thermal and spectral chain at $T_{\rm CMB}$. (i) Golden-section maxima of $x^3/(e^x-1)$ and $x^5/(e^x-1)$ agree with the roots of V1; (ii) $\lambda_{\rm peak}=b/T$ and $\nu_{\rm peak}=2.821439372\,k_BT/h$, with $c/(\nu_{\rm peak}\lambda_{\rm peak})=4.965114231744276/2.821439372122079=1.7597$; (iii) $u_{\rm CMB}=a_{\rm rad}T^4$ (engine, `law_I::u_CMB`) equals the Planck energy density from the quadrature of V3, $8\pi^5(k_BT)^4/(15h^3c^3)$ | (i) $10^{-7}$; (ii) $10^{-12}$; (iii) $10^{-5}$ | yes |
| T5 | coverage: the set of identifiers defined in `namespace measured` of `laws.hpp` equals the set of identifiers in the first column of `Textbook/sources/MEASURED_CLASSIFICATION.md` | sets equal; count printed | yes — a missing or extra entry rejects |

Reported, not criteria: the dimensionless numbers of $S_1$–$S_4$ with their values.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch06_state_dimensions_and_metrology`

## Record of run 1 and repair of V2 (2026-11-09)

Run 1 (`ch06_run1_output.txt`) met every criterion except one clause of V2. That clause asserted that the square root of a length is refused by the dimension algebra, which contradicts the registered statement of V2 itself (a length to the power one half is *represented* in half units; what the algebra refuses is a quarter exponent). The test code, not the algebra, was wrong: an instrument-validation fault. V2 is replaced by two clauses that follow its registration: $\sqrt{\mathrm L}$ is represented as the half-unit exponent, and $\sqrt{\sqrt{\mathrm L}}$ is refused. The T-results of run 1 are unchanged by this and met their criteria; run 2 is the run of record. The `measured` namespace contains 47 identifiers (a count of 48 made while drafting the classification table was a miscount); the coverage test T5 compares the sets and was not affected.
