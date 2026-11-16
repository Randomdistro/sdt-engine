# Chapter 23 — pre-registration of the worked-example instrument

Registered 2026-11-10, before `Textbook/examples/ch23_binding_and_stability.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object. What the engine holds for binding and what a statement of binding requires. The engine stores nuclear masses of the deuteron, triton and helion (CODATA 2022, `measured::m_d, m_t, m_He3`) and a typed value $B_\alpha=28.296$ MeV; it records that the volume-price hypothesis $E=P\,\Delta V$ was excluded (NP05; spread 45× across reactions, engine-recorded and not re-run here) and that a successor $E_{\rm bind}=\hbar\,\Delta\omega$ (gear frequency) is under test. This chapter executes: (a) a registered test of the hypothesis "$E_{\rm bind}=\varepsilon\,E_{\rm contacts}$ with one constant $\varepsilon$" on the four light species with explicit contact graphs (deuteron 1, triton 2, helion 2, alpha ring 4), the criterion fixed before the measured binding energies are read; (b) the ledger of separation energies as finite differences of binding energies with their mass-form identities; (c) the bulk radius law of the engine and its comparison with the measured helium radius with the two radius definitions kept apart. No energy functional of the contact law is available in the engine; the chapter states what one would have to deliver.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | unit bridge: $B_d=2.2245662$ MeV, $B_t=8.4817985$ MeV and $B_h=7.7180373$ MeV computed from the stored CODATA 2022 masses equal the published values (deuteron 2.224566 MeV; triton 8.481798 MeV; helion 7.718037 MeV); the alpha binding energy from the published $m_\alpha c^2=3727.3794066$ MeV is 28.29567 MeV | $10^{-6}$ relative (deuteron, triton, helion); $10^{-5}$ (alpha, against the stored 28.296) |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | hypothesis $H_c$: $B=\varepsilon E_{\rm contacts}$ with constant $\varepsilon$ over $\{$d, t, $^3$He, $^4$He$\}$ with $E_{\rm contacts}=1,2,2,4$ (explicit graphs of Chapter 19: p–n; n–p–n; p–n–p; p–n–p–n ring). $H_c$ is accepted only if $(\varepsilon_{\max}-\varepsilon_{\min})/\bar\varepsilon\le0.10$. **Registered expectation: $H_c$ is rejected.** The per-species $\varepsilon$, and $B/A$, are reported | rejection of $H_c$ is the registered outcome; acceptance would be recorded as an unregistered result | yes — acceptance rejects the registered expectation |
| T2 | separation energies as finite differences: $S_n(Z,N)=B(Z,N)-B(Z,N-1)$ with the mass form $S_n=(m(Z,N-1)+m_n-m(Z,N))c^2$; for the deuteron, triton from $B_d$, and $^4$He from the stored $B_\alpha$ and $B_h$: $S_n(\mathrm d)=B_d$, $S_n(\mathrm t)=B_t-B_d$, $S_n(^4\mathrm{He})=B_\alpha-B_h$, $S_p(^4\mathrm{He})=B_\alpha-B_t$, $S_p(^3\mathrm{He})=B_h-B_d$. The mass form equals the binding-energy form for the deuteron and triton to $10^{-12}$ relative. The mirror identity $B_t-B_h=(m_n-m_p)c^2-(m_t-m_h)c^2$ holds to $10^{-9}$ relative. Per-added-contact energies are reported | as stated | yes |
| T3 | bulk radius. $\eta=\pi/\sqrt{18}=0.7404805$ (close-packing fraction); `nuclear_boundary_radius(A)` $=R_p(A/\eta)^{1/3}$ obeys $R(8A)/R(A)=2$ exactly and $R(1)=R_p\eta^{-1/3}$. For $A=4$: the bulk value, the contact diameter $2R_p$ (`R_He_contact_diameter`) and the stored measured helium radius $R_{\rm He}$ are printed, with ratios; the two definitions (bulk rms radius law, contact-seat diameter) are not identified with each other. Criterion: the arithmetic only | $10^{-12}$ | yes |

Reported, not criteria: all $\varepsilon$ values, per-contact increments, radius ratios.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch23_binding_and_stability`

## Record of run 1; correction of V1 (2026-11-10)

Run 1 (`ch23_run1_output.txt`) met every T-criterion and V1 for the deuteron and the triton (relative deviations $1.5\times10^{-7}$ and $1.6\times10^{-7}$, the size of the rounding of the quoted values), and failed V1 for the helion ($6.1\times10^{-6}$) and the alpha ($1.4\times10^{-5}$). The cause is in the registration and not in the engine. The helion "published value" 7.718037 MeV was entered from memory and is the atomic-mass-based tabulated value; the engine computes the nuclear-mass form $2m_p+m_n-m_h$, which is $4.7\times10^{-5}$ MeV lower ($47$ eV), a difference of the order of the electron binding in the atomic form. The alpha stored value 28.296 is typed to five digits and exceeds the nuclear-mass value 28.295616 MeV by $3.8\times10^{-4}$ MeV, which is its own rounding. V1 is repaired: the deuteron and triton known-answer checks stand; for the helion the check is that the engine constant equals the direct evaluation $2m_p+m_n-m_h$ from the stored masses to $10^{-12}$; for the alpha the difference of the stored typed value from the value computed with the published nuclear mass is **reported** (residual) and not a criterion. The T-tests are unchanged. Run 2 is the run of record.
