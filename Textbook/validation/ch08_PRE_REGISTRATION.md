# Chapter 8 — pre-registration of the worked-example instrument

Registered 2026-11-09, before `Textbook/examples/ch08_mathematical_well_posedness.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object. Four statements of the chapter about admissibility, tested on small cases labelled TOY where they are generic: (T1) positivity and conservation of a nearest-neighbour relay update as a function of the fraction passed; (T2) the exponent criteria for arrest and for finite accumulated displacement; (T3) invariance of the physical speed along a straight path that crosses the polar axis of the chart, using the engine's `step_locus`; (T4) the accuracy of `step_locus` near a path through the centre, where the engine substitutes a floor for $r=0$.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | the relay update with fraction $f=1/3$ on a delta initial state: after one step the three cells hold $(1/3,1/3,1/3)$; the total is 1 | $10^{-15}$ |
| V2 | log-variable quadrature of $\int_1^Tt^{-s}dt$ against $(T^{1-s}-1)/(1-s)$ for $s=2$, $T=10^4$ and against $\ln T$ for $s=1$, $T=10^4$ | $10^{-12}$ relative |
| V3 | `step_locus` from the place $(r=1,\theta=\pi/2,\phi=\pi)$, which is the point $(-1,0,0)$, along the direction $(\theta=\pi/2,\phi=2\pi)$, which is $+x$, by distance $0.5$ returns the point $(-0.5,0,0)$: radius $0.5$, $\theta=\pi/2$, $\phi=\pi$ | $10^{-12}$ |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | TOY. One-dimensional chain of 201 cells, initial content 1 in the central cell. Update $u_i'=(1-2f)u_i+f(u_{i-1}+u_{i+1})$, 50 steps, $f\in\{0.25,0.5,0.55,0.75,1.0\}$ | total content equal to 1 to $10^{-12}$ for every $f$; minimum cell content $\ge0$ for $f\le\tfrac12$; minimum $<0$ for $f>\tfrac12$ | yes — positivity surviving $f>\tfrac12$ would reject the threshold; a loss of content would reject conservation |
| T2 | arrest and accumulated displacement. For $\chi\sim t^a$ and $|\dot q|\sim\chi^{-b}$ the accumulated displacement $I(T)=\int_1^Tt^{-ab}dt$ by quadrature for $ab\in\{0.5,1,2\}$ and $T\in\{10^2,10^4,10^6,10^8\}$ | equals the closed form to $10^{-10}$ relative; $I(10^8)>10^4$ for $ab=0.5$; $I(10^8)/I(10^6)=4/3$ to $10^{-10}$ for $ab=1$; $\lvert I(10^8)-1\rvert<10^{-7}$ for $ab=2$ | yes |
| T3 | chart crossing. Straight path $P_k=(-1+0.1k,\,0,\,0.5)$, $k=0\ldots20$, crossing the polar axis at $k=10$, advanced by `step_locus` along $+x$. Consecutive loci are $0.1$ apart; each locus equals the locus of the Cartesian reference $P_k$; the azimuth changes by $\pi$ between $k=9$ and $k=11$; the polar angle is $0$ at $k=10$ | chord between consecutive loci $0.1$ within $10^{-12}$ (worst of 20); reference distance $\le10^{-12}$; azimuth jump $\pi$ within $10^{-9}$; $\theta_{10}\le10^{-9}$ | yes |
| T4 | the centre. From $(r=1,\ \theta=1,\ \phi=1)$ advance along the antipodal direction by $d=1-\rho$ and $d=1+\rho$ with $\rho\in\{10^{-2},10^{-4},10^{-6},10^{-8}\}$; the exact radius is $\rho$ and the direction is the origin direction ($d<1$) or the antipode ($d>1$). At $d=1$ exactly the engine returns the floor radius $0.5\times10^{-12}$ | relative error of the radius $\le 8u/\rho^2$ (with $u=1.11\times10^{-16}$) for every case; at $\rho=10^{-8}$ relative error $>0.1$; direction label correct for $\rho\ge10^{-6}$; at $d=1$ the radius equals the floor exactly | yes — an accurate radius at $\rho=10^{-8}$ would reject the predicted loss |

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch08_mathematical_well_posedness`

*Note (2026-11-09, before the first run):* the V3 row was corrected from a draft sentence that broke off ("returns radius √2… no: …") to the statement above, which is the intended known answer. No run existed.

## Record of run 1 and repair of T1 (2026-11-09)

Run 1 (`ch08_run1_output.txt`) met every criterion of V1–V3, T2, T3 and T4, and the sign criteria of T1. It did not meet the criterion "total content equal to 1 to $10^{-12}$ for every $f$" at $f=0.75$ (total $1.0045$) and $f=1.0$ (total $1.4\times10^{6}$). Cause: for $f>\tfrac12$ the update is unstable and the cell contents grow to amplitudes of order $10^{13}$ to $10^{22}$ within 50 steps, so rounding of a sum of such terms destroys the total in double precision, although the update conserves content algebraically (each step redistributes the content of a cell among itself and its neighbours). The registered criterion could not be met by the instrument for $f>\tfrac12$; it was a flaw of the registration, not a property of the update, and the failure is itself an observation for the chapter (a conservation defect read in floating point is not a failure of conservation without a resolution study). The T1 criterion is replaced by one that cannot be defeated by rounding: in exact rational arithmetic (25 cells, 8 steps, 64-bit fractions with an overflow check) with $f\in\{\tfrac14,\tfrac12,\tfrac{11}{20},\tfrac34,1\}$, the total content equals 1 exactly for every $f$, the minimum content is $\ge0$ exactly for $f\le\tfrac12$ and $<0$ exactly for $f>\tfrac12$. The double-precision 50-step run is kept for $f\le\tfrac12$ (total within $10^{-12}$, minimum $\ge0$) and, for $f>\tfrac12$, reports the minimum only. Run 2 is the run of record.

*Record of run 2 (2026-11-09).* Run 2 (`ch08_run2_output.txt`) met every criterion except the exact test at $f=\tfrac{11}{20}$, which reported failure because the instrument's overflow check tripped: with denominators $20^k$ the cross products in the rational sum exceed the 64-bit range after about six steps. The instrument flagged its own limit; the sign and total of the update at that $f$ were not evaluated. The registered value $\tfrac{11}{20}$ is replaced by $\tfrac35$ (denominators $5^k$, which stay within range for 8 steps). The criterion is unchanged. Run 3 is the run of record.
