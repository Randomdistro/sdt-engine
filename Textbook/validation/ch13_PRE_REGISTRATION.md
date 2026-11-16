# Chapter 13 — pre-registration of the worked-example instrument

Registered 2026-11-09, before `Textbook/examples/ch13_movement_budget.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

A text of this chapter and a probe (`ch13_probe2.cpp`, 69 checks, zero failures) exist from 2026-10-27 in the investigation folder `SDT_Textbook_Architecture_2026-10-27_2`. That run is a retrieval lead and is not cited as evidence here. This instrument is new, written for this edition, and its run is the one the chapter cites. It reads every constant from `laws.hpp` and the spherical response from `occlusion_sphere.hpp`.

Object. The saturated movement budget $v_{\rm circ}^2+v^2=c^2$ (`law_V`, `laws.hpp:895–954`) and its consequences as stated in the chapter: circulation fraction, clock fraction and Lorentz factor; round-trip closure and longitudinal contraction; energy and momentum; the cancellation-free kinetic energy and its series; the direction-dependent response `occlusion_sphere::law_v_response`; the depth-budget compatibility relation; the variable-parameter derivatives; and the controlled radiative limit.

Notation: $\beta=v/c$, $\chi=\sqrt{1-\beta^2}$, $\gamma=1/\chi$.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | Pythagorean fixtures: $\beta=0.6\Rightarrow\chi=0.8,\gamma=1.25$; $\beta=0.8\Rightarrow\chi=0.6,\gamma=5/3$; $\beta=0\Rightarrow\chi=\gamma=1$ computed by the instrument's own arithmetic (not the engine) | $10^{-15}$ |
| V2 | the central-difference derivative routine on $f=x^3$ at $x=2$ (exact 12) and on $f=\sin$ at $0.7$ | $10^{-8}$ relative |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | for $\beta\in\{0,0.1,0.6,0.8,0.99,0.9999\}$ the engine's `v_circ`, `time_dilation`, `gamma`, `total_energy`, `momentum` equal $\chi c$, $\chi$, $\gamma$, $\gamma m_0c^2$, $\gamma m_0v$; and $E^2-c^2p^2=E_0^2$ | each within $10^{-10}$ relative; the residual in units of $E_0^2$ within $10^{-9}$ absolute (the larger tolerance at $\beta=0.9999$ is registered because of cancellation between $E^2$ and $c^2p^2$ of size $\gamma^2\approx5\times10^3$) | yes — a different power of $\gamma$ in $E$ or $p$ rejects |
| T2 | round-trip closure: $T_{\rm round}=2Lc/(c^2-v^2)=2L\gamma^2/c$ and the synchronisation $T_{\rm round}=\gamma T_{\rm round,0}$ give $L/L_0=1/\gamma$, equal to the engine's `length_contraction` | within $10^{-12}$ relative for the six $\beta$ above | yes — omitting the factor of two on one side rejects |
| T3 | kinetic energy: the cancellation-free form $\gamma^2\beta^2E_0/(\gamma+1)$ equals the direct $(\gamma-1)E_0$ for $\beta\ge0.01$ to $10^{-9}$ relative, and at $\beta=0.01$ the series $\beta^2/2+3\beta^4/8+5\beta^6/16$ equals $K/E_0$ to $10^{-14}$ relative; the direct form at $\beta=10^{-4}$ shows a loss of at least 4 digits against the cancellation-free form | as stated | yes — the cancellation loss is the registered observation |
| T4 | directional response. Using `occlusion_sphere::law_v_response` with loci for the velocity and the budget acceleration (separation $\psi$), the magnitude equals $A\sqrt{\chi^6\cos^2\psi+\chi^2\sin^2\psi}$ and the heading relative to the velocity equals $\operatorname{atan2}(\chi\sin\psi,\chi^3\cos\psi)$, for $\beta\in\{0.1,0.6,0.8,0.99\}$, $\psi\in\{0,45^\circ,90^\circ,135^\circ,180^\circ\}$; at $\psi=0$ the factor is $\chi^3$ and at $90^\circ$ it is $\chi$; at $v=0$ the acceleration is returned unchanged | magnitude within $10^{-9}$ relative; heading within $10^{-9}$ rad; special cases within $10^{-12}$ | yes — a response by the scalar $\chi$ alone rejects at $\psi=0$ |
| T5 | independent check of the longitudinal factor: the central difference of the engine's `momentum(m_0,v)` with step $c(1-\beta)\times10^{-4}$ equals $m_0\gamma^3$ for $\beta\in\{0.1,0.6,0.8,0.99\}$; and $\gamma$'s derivative $d\gamma/d\beta=\beta\gamma^3$ | within $2\times10^{-6}$ relative (registered for the step) | yes |
| T6 | depth budget. For $z\in\{0,0.01,0.1,0.25,0.5,0.9\}$: `clock_rate(z)` $=1-z$, `c_far(c,z)`$/c=(1-z)^2$, the compatibility loading $2z-z^2$ satisfies $(1-z)^2+(2z-z^2)=1$; the linear branch $c(1-2z)$ requires the duration factor $H_h=(1-z)^2/(1-2z)$ for $z<\tfrac12$ (printed) | identity within $10^{-12}$; engine functions exact | yes |
| T7 | variable parameters. For fixed $v$ and $c(t)=c_0(1+\epsilon t)$ the derivative of $\gamma$ is $-\gamma^3\beta^2\dot c/c$ (Eq. 13.45 with $\vec v\cdot\vec a=0$), checked by central difference at $\beta_0\in\{0.3,0.8\}$, $\epsilon=10^{-3}$ | within $10^{-6}$ relative | yes |
| T8 | controlled radiative limit. With $E_0=E_*/\gamma$ the energy is $E_*$ and $pc/E_*=\beta\to1$: at $\beta=1-10^{-8}$, $\lvert pc/E_*-1\rvert=10^{-8}$ | within $10^{-12}$ of $\beta$ | yes |
| T9 | worked headings. For $\beta=0.8$ and $\psi=45^\circ$: $a_\perp/a_\parallel=\gamma^2=25/9$ and the response heading is $70.2^\circ$ (to the printed digit); for $\beta=0.6$, equal components: $\tan\psi_a=1.5625$ | as stated | yes |

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch13_movement_budget`

## Record of run 1 and repair of T3 (2026-11-09)

Run 1 (`ch13_run1_output.txt`) met every criterion except the series clause of T3: the three-term series $\beta^2/2+3\beta^4/8+5\beta^6/16$ differs from $K/E_0$ at $\beta=0.01$ by a relative $5.5\times10^{-13}$, against the registered $10^{-14}$. The registered tolerance was below the truncation error of a three-term series: the next term, $35\beta^8/128$, is a relative $\tfrac{35}{64}\beta^6=5.5\times10^{-13}$ of the leading term, which is the observed difference. This is a flaw of the registration, not of the engine. The clause is replaced by two that cannot be met by an error: (a) the difference between the three-term series and $K/E_0$ equals the next term $35\beta^8/128$ to 1% of itself; (b) the four-term series equals $K/E_0$ to $10^{-14}$ relative. All other criteria of run 1 were met. Run 2 is the run of record.
