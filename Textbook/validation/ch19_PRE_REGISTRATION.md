# Chapter 19 — pre-registration of the worked-example instrument

Registered 2026-11-09, before `Textbook/examples/ch19_neutron_and_conversion.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object. The conversion ledger of the neutron. (a) The energy–momentum constraints on the free conversion $n\to p+e+\text{(open-winding channel)}$ with the relativistic relation of Chapter 13: the energy released from the stored masses, the endpoint of the electron energy, and the statement that these constrain which final states are possible and give no rate; (b) the sensitivity of that endpoint to the absolute scale of the open-winding channel's mass, for the three convention values stored in `neutrino.hpp` (which the engine's header flags as conventions and not measurements); (c) the contact ledger of an in-place conversion under the contact rule of `nuclear` (unlike units only, at most three contacts per unit): contacts of the converting unit cannot persist, and the number that can be re-formed is a bipartite capacity problem solved here by max-flow; and the exact capacity against the engine's `contact_capacity(Z,N)=3\min(Z,N)`, which is an upper bound and not the exact maximum when $\max(Z,N)<3$. No lifetime is computed: the chapter retains the conversion programme without assigning an ab-initio rate.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | the unit bridge from kilograms to MeV: $m_nc^2=939.56542194$ MeV, $m_pc^2=938.27208943$ MeV, $m_ec^2=0.51099895069$ MeV (the published CODATA 2022 energy-unit values) from the stored masses | relative $10^{-8}$ |
| V2 | the max-flow capacity solver reproduces the exact bipartite maximum $\min(3Z,\,3N,\,ZN)$ for every $1\le Z,N\le12$ (degree-capped complete bipartite graph) | exact integers |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | free conversion kinematics, massless open-winding channel. $Q=(m_n-m_p-m_e)c^2$. Closed-form endpoint $E_e^{\max}=(m_n^2+m_e^2-m_p^2)c^4/(2m_nc^2)$. A sampler (fixed generator, $2\times10^6$ draws of electron momentum in $[0,1.1\,p_{\max}]$ and isotropic directions of electron and channel) solves energy conservation for the channel energy by bisection with the recoil momentum fixed by momentum conservation. Criteria: every accepted draw has residual of energy conservation $\le10^{-12}$ MeV; no accepted draw has $E_e>E_e^{\max}$; no rejected draw has $E_e<E_e^{\max}$; the largest accepted $E_e$ lies within $10^{-4}$ MeV below $E_e^{\max}$. Reported: $Q$, $E_e^{\max}$, the electron kinetic endpoint, the proton recoil kinetic energy at the endpoint | as stated | yes — an accepted draw above the closed-form endpoint, or a rejected one below it, rejects the closed form |
| T2 | endpoint sensitivity to the channel's mass: $E_e^{\max}(m_\nu)=(m_n^2+m_e^2-(m_p+m_\nu)^2)/(2m_n)$ for $m_\nu=0.02,\,0.029,\,0.06$ eV (the engine's stored convention values). Criteria: the shift from the massless case equals $-(m_pm_\nu+m_\nu^2/2)/m_n$ to $10^{-9}$ relative; each shift is below $10^{-7}Q$. Reported: shifts in eV | as stated | yes |
| T3 | contact ledger of in-place conversion, parents built as explicit contact graphs: free neutron (no contacts), deuteron p–n (1 contact), triton n–p–n chain (2), alpha ring p–n–p–n (4). Convert one neutron to a proton. The converting unit's contacts are lost (a proton touches no proton, and the converted unit's former partners are protons). Registered integers (lost, surviving, maximum contacts of the daughter containing the survivors, re-formed): free neutron (0, 0, 0, 0); deuteron (1, 0, 0, 0); triton (1, 1, 2, 1); alpha ring (2, 2, 3, 1) | exact integers | yes |
| T4 | the engine's `contact_capacity(Z,N)` against the exact maximum $\min(3Z,3N,ZN)$ for $1\le Z,N\le12$: equal exactly when $\max(Z,N)\ge3$; unequal (engine larger) for exactly $(1,1),(1,2),(2,1),(2,2)$ with engine values $3,3,3,6$ and exact values $1,2,2,4$ | exact integers | yes |

Reported, not criteria: $Q$, endpoint energies, sampler statistics, the shifts of T2.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch19_neutron_and_conversion`

## Record of run 1; correction of the T2 evaluation (2026-11-09)

Run 1 (`ch19_run1_output.txt`) met V1, V2, T1, T3, T4 and the size clause of T2 and failed the formula clause of T2 (relative deviation $1.4\times10^{-6}$ against $10^{-9}$). The shift of the endpoint is about $2\times10^{-8}$ MeV and was evaluated as a difference of two quantities $(m_p+m_\nu)^2$ and $m_p^2$ of size $9\times10^{5}$ MeV$^2$, whose resolution in double precision is about $10^{-10}$ MeV$^2$; the cancellation, not the physics, produced the deviation. The expression $-(m_pm_\nu+m_\nu^2/2)/m_n$ is algebraically exact. The clause is repaired without changing what is tested: the endpoint with a channel of mass $m_\nu$ at rest is now found by direct bisection on $E_e$ from $E_e+m_\nu+\sqrt{m_p^2+E_e^2-m_e^2}=m_n$ (no squared masses subtracted), and its shift from the massless root is compared with the closed expression at a relative tolerance of $10^{-7}$ of the shift (the resolution floor of that root-finding is near $5\times10^{-9}$). The size clause is unchanged. Run 2 is the run of record.

## Record of run 2; second correction of the T2 evaluation (2026-11-09)

Run 2 (`ch19_run2_output.txt`) reproduced the other criteria and failed the formula clause of T2 again, at $6.6\times10^{-6}$. The registered "resolution floor near $5\times10^{-9}$" in the previous record was wrong: the residual $E_e+m_\nu+\sqrt{m_p^2+E_e^2-m_e^2}-m_n$ contains $\sqrt{m_p^2+p_e^2}\approx938$ MeV, whose resolution in double precision is about $10^{-13}$ MeV, so a shift of $2\times10^{-8}$ MeV is resolved only to about $5\times10^{-6}$ of itself, which the observed deviation matches. The evaluation is repaired in kinetic energies, so that nothing of size 938 MeV is subtracted: with $Q=m_n-m_p-m_e$ evaluated once (its rounding is common to all cases and cancels in shifts), the equation $T_e+m_\nu+p_e^2/(\sqrt{m_p^2+p_e^2}+m_p)=Q$, $p_e^2=T_e(T_e+2m_e)$, is solved by bisection for $T_e$ for $m_\nu=0$ and for each $m_\nu$; the shifts of $T_e$ are compared with $-(m_pm_\nu+m_\nu^2/2)/m_n$ at relative tolerance $10^{-7}$ of the shift. The size clause is unchanged. Run 3 is the run of record.

## Record of run 3; the direct solve was misspecified (2026-11-09)

Run 3 (`ch19_run3_output.txt`) failed the formula clause of T2 at $8.06\times10^{-7}$. This is not a resolution effect. The repairs recorded for runs 2 and 3 placed the channel **at rest** in the direct solve. For a channel of mass $m_\nu>0$ the endpoint of the electron energy is reached when the recoiling proton and the channel move together with a common velocity, i.e. as one system of mass $m_p+m_\nu$ (the minimal invariant mass of the pair); the channel at rest is a different configuration, with a lower electron energy. The two coincide only at $m_\nu=0$. The deviation equals $E_p/m_p-1=8.0\times10^{-7}$ for the proton recoil energy at the endpoint, as expected for the wrong configuration. The registered closed form, which assumes the common velocity, was correct. The error was in the instrument introduced at the repair of run 1, not in the criterion. The direct solve is corrected to the common-velocity configuration, in kinetic energies: $T_e+m_\nu+p_e^2/(\sqrt{(m_p+m_\nu)^2+p_e^2}+m_p+m_\nu)=Q$, $p_e^2=T_e(T_e+2m_e)$; the tolerance remains $10^{-7}$ of the shift. Run 4 is the run of record.
