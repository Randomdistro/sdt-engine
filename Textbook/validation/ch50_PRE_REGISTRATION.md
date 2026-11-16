# Chapter 50 — pre-registration of the worked-example instrument

Registered 2026-11-10, before `Textbook/examples/ch50_interference_and_detection.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object. A disturbance propagating through two open apertures and recombining at a detector; the detector's response rule. All models are generic stand-ins (TOY), with no measured input and no engine function. (a) In the linear regime the complex amplitude is a bookkeeping representation of physical phase, $A=A_1+A_2$; a quadratic detector gives $|A|^2=|A_1|^2+|A_2|^2+2\mathrm{Re}(A_1A_2^*)$; for amplitudes $1$ and $r$ the visibility is $V=2r/(1+r^2)$. Maxima of two point apertures at separation $d$ lie where the exact path difference is $n\lambda$; the small-angle spacing $\lambda L/d$ is its limit. (b) Finite bandwidth reduces visibility: for a Gaussian spectrum of width $\sigma_k$ the visibility at path difference $\Delta\ell$ is $\exp(-\sigma_k^2\Delta\ell^2/2)$. (c) Blocking one aperture changes the boundary-value problem: the single-aperture pattern is the envelope without fringes, so deleting half the detector events from the two-aperture pattern does not reproduce it; the total-variation distance between the normalised patterns is about $1/\pi$ when many fringes lie under the envelope. (d) Detection as the endpoint of transfer: a stored-excitation accumulate-and-fire detector with deterministic accumulation gives counts $n=\lfloor\mu+\varphi\rfloor$ ($\varphi$ the initial phase, uniform), a variance $\{\mu\}(1-\{\mu\})\le1/4$ and so a Fano factor $\mathrm{var}/\mathrm{mean}\le1/(4\mu)$ (sub-Poissonian), whereas sampling events from the intensity as a comparison rule gives a Poisson count (Fano factor $1$) by assumption: the statistics of single registrations are an input of the second rule and a prediction of the first, and the two differ.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | $|A_1+A_2|^2=|A_1|^2+|A_2|^2+2\mathrm{Re}(A_1A_2^*)$ for $A_1=1+2i$, $A_2=-0.5+0.25i$; for the Gaussian spectrum the zeroth moment $\int S\,dk=\sigma\sqrt{2\pi}$; for $\mu=20.5$ and $\varphi$ uniform on $[0,1)$ the variance of $\lfloor\mu+\varphi\rfloor$ computed by quadrature over $\varphi$ is $0.25$ | $10^{-12}$ |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | two apertures. $\lambda=500$ nm, $d=1$ mm, $L=1$ m, equal amplitudes: the exact maxima $y_n$ ($r_1-r_2=n\lambda$, $n=1\ldots5$) give $I=4$ to $10^{-10}$ and differ from the small-angle $n\lambda L/d$ by less than $10^{-4}$ relative; for amplitudes $1$ and $0.5$ the visibility from the scanned maximum and minimum over one period is $0.8$ | $10^{-10}$, $10^{-4}$, $10^{-9}$ | yes |
| T2 | coherence. Gaussian spectrum centred at $k_0=2\pi/500$ nm with $\sigma_k=0.05k_0$: the visibility $|\int S(k)e^{ik\Delta\ell}dk|/\int S\,dk$ at $\Delta\ell=1,3,10\,\mu$m equals $\exp(-\sigma_k^2\Delta\ell^2/2)$ | $10^{-8}$ relative | yes |
| T3 | blocking. Two slits of width $a=0.1$ mm at separation $d=1$ mm, $\lambda=500$ nm, $L=1$ m, window $y\in[-5,5]$ mm, exact path lengths, numerical integration over each slit: the total-variation distance between the normalised two-slit pattern and the normalised single-slit pattern lies in $[0.28,0.35]$; the two-slit pattern equals the sum of the single-slit patterns plus a nonzero cross term (the cross-term integral over the window is below 5 per cent of the single-slit integral) | as stated | yes |
| T4 | detection rule. $\mu=20.37$: threshold accumulate-and-fire counts over $2\times10^5$ random initial phases give a Fano factor in $[0.010,0.0125]$ (predicted $0.01144$) and always at most $1/(4\mu)$; counts drawn as Poisson variates with the same mean ($2\times10^5$ draws, fixed seed) give a Fano factor in $[0.98,1.02]$; sampling $2\times10^5$ event positions from the two-slit pattern by inversion and binning in 40 bins gives $\chi^2/\mathrm{dof}$ in $[0.7,1.3]$ against the pattern (a comparison-rule consistency, not a derivation) | as stated | yes |

Reported, not criteria: the maxima positions and the small-angle differences; the visibilities; the total-variation distance; the Fano factors; $\chi^2/\mathrm{dof}$.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch50_interference_and_detection`

## Record of run 1; one registration error (2026-11-10)

Run 1 (`ch50_run1_output.txt`): every criterion was met except one: T2 at $\Delta\ell=10\ \mu$m. The visibility there is $2.6753\times10^{-9}$; the instrument's value differs from $\exp(-\sigma_k^2\Delta\ell^2/2)=2.6753\times10^{-9}$ by $1.5\times10^{-15}$ in absolute terms, which is $5.5\times10^{-7}$ relative, against the registered $10^{-8}$ relative. The visibility is the modulus of an oscillatory integral whose integrand is of order 1; the double-precision floor of such a sum is about $10^{-15}$ absolute, so a relative tolerance on a result nine orders below that scale cannot be met by any correct implementation. This is a registration error (the same class as Chapter 45), not a finding on the object. The criteria for $\Delta\ell=1$ and $3\ \mu$m (values $0.82$ and $0.17$) are unchanged and were met to $3\times10^{-15}$ and $1.3\times10^{-14}$; the criterion at $10\ \mu$m is evaluated in absolute terms with tolerance $10^{-14}$ (the floor), and the relative error is reported. Run 2 is the run of record.
