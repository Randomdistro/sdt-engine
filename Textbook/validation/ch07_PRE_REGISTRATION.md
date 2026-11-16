# Chapter 7 — pre-registration of the worked-example instrument

Registered 2026-11-09, before `Textbook/examples/ch07_persistence_and_topology.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object. The topological classification of the engine's winding modes `(p,q)` (`law_VI::winding` header comment and `law_VI::topology`, `laws.hpp:2396–2533`) by the Alexander polynomial of the torus knot $T(p,q)$, computed in exact integer polynomial arithmetic; the exact closure of the movement budget over all $(p,q)$ in the engine's mode formulas; the smoothing rates of `confinement::harmonic_rate_sq`; and the crossing-change relation that connects knot classes. The instrument classifies; it computes no energies, barriers or lifetimes, which Chapter 7 states are open.

The Alexander polynomial of the torus knot $T(p,q)$, $\gcd(p,q)=1$, is $\Delta_{p,q}(t)=\dfrac{(t^{pq}-1)(t-1)}{(t^{p}-1)(t^{q}-1)}$, defined up to a unit $\pm t^k$; the instrument normalises it to a polynomial with non-zero constant term and positive leading coefficient.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | integer polynomial division: $(t^2-1)/(t-1)=t+1$; $(t^6-1)/(t^2-1)=t^4+t^2+1$; a division with non-zero remainder is reported as not exact | exact |
| V2 | the formula reproduces tabulated Alexander polynomials: trefoil $T(2,3)$: $t^2-t+1$; cinquefoil $T(2,5)$: $t^4-t^3+t^2-t+1$; $T(3,4)$ (knot $8_{19}$): $t^6-t^5+t^3-t+1$ | exact |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | unknot modes: $\Delta_{1,q}=1$ for $q=1\ldots12$ (the engine's electron $(1,1)$ and the $(1,2)$ mode) | exact | yes — a non-trivial polynomial rejects |
| T2 | the engine's proton mode $(2,3)$ has $\Delta=t^2-t+1\ne1$. The polynomial quoted for it in the engine's header comment, $t^{-2}-t^{-1}+1-t+t^2$, is the polynomial of $T(2,5)$ and not of $T(2,3)$ | $\Delta_{2,3}=[1,-1,1]$; the quoted polynomial's coefficients equal those of $\Delta_{2,5}$ and differ from those of $\Delta_{2,3}$ | yes — if the quoted polynomial equalled $\Delta_{2,3}$ the statement about the header would be rejected |
| T3 | non-triviality and structure for all coprime $2\le p<q\le12$: $\Delta\ne1$; degree $(p-1)(q-1)$ (twice the genus); palindromic coefficients; $\Delta(1)=\pm1$ after normalisation to $+1$; $|\Delta(-1)|$ odd | every pair satisfies all five | yes |
| T4 | crossing-change relation. With $z=t^{1/2}-t^{-1/2}$ the Conway polynomial of the trefoil is $\nabla=1+z^2$ and equals $\Delta_{2,3}(t)/t$ evaluated at $t\in\{0.5,\,2,\,3.7\}$; the skein relation $\nabla_+-\nabla_-=z\,\nabla_0$ holds for (trefoil, unknot, Hopf link with $\nabla_0=z$) | agreement within $10^{-13}$ | yes |
| T5 | movement budget closure for the engine's mode formulas: `topology::budget_residual(p,q)` $=1$ and $v_T^2+v_P^2=c^2$ for all $1\le p,q\le12$; `v_toroidal`, `v_poloidal`, `aspect_ratio` equal $c\sqrt{p/(p+q)}$, $c\sqrt{q/(p+q)}$, $\sqrt{q/p}$; the electron $(1,1)$ has $v_T=v_P=c/\sqrt2$ and the proton $(2,3)$ has $v_T=0.632456c$, $v_P=0.774597c$ | closure within $10^{-15}$; formulas within $10^{-15}$ relative; proton speeds within $10^{-6}$ relative | yes |
| T6 | smoothing rates: `confinement::harmonic_rate_sq(m,n,v_T,R,v_P,a)` for the proton mode with $R/a=\sqrt{q/p}$ satisfies $\omega^2_{0,n}/\omega^2_{0,1}=n^2$ and $\omega^2_{m,0}/\omega^2_{1,0}=m^2$ for $m,n=1\ldots6$, and $\omega^2_{m,n}>0$ for $(m,n)\ne(0,0)$ with $\omega^2_{0,0}=0$ | within $10^{-14}$ relative | yes |

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch07_persistence_and_topology`
