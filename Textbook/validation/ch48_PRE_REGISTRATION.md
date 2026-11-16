# Chapter 48 — pre-registration of the worked-example instrument

Registered 2026-11-10, before `Textbook/examples/ch48_elapsed_recurrence_and_cosmic_dynamics.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object. (a) State history versus rate history: a route $Q(S)$ supplies configurations; an evolution law $dS/d\tau=F_S$ supplies chronology; with the tick-rate ratio $C=d\tau/dt$ the elapsed remote duration is $\Delta t=\int dS/[C(S)F_S(S)]$; a zero or sign change of $C$ or $F_S$ on the route changes the integral and has to be treated explicitly. (b) Local relay cycle counts: $N=\int dt/\Delta t_{\rm hop}$ with $\Delta t_{\rm hop}=\Delta\tau_{\rm hop}/C$; mixing the remote and local duration conventions omits or double-counts $C$. (c) A static state relation can be traversed in either mathematical direction; a transport law selects the progression. A two-reservoir relaxation $dT_1/d\tau=-k(T_1-T_2)$, $dT_2/d\tau=+k(T_1-T_2)$ (heat capacity 1) conserves $T_1+T_2$ for either sign of $k$ and has the entropy-like function $\ln T_1+\ln T_2$ with rate $k(T_1-T_2)^2/(T_1T_2)$; the sign of the coupling $k$ is a property of the law, not of the relation. (d) Coupled acoustic history: the engine's release standing scale `bridge::release_acoustics` is recomputed independently from its stated formulas; a measured acoustic scale divided by an assumed speed gives a compatibility duration, not a prediction of that same scale. Inputs: $\{h,c,k_B,m_p,a_{\rm rad},T_{\rm CMB}\}$ (`measured`); $\eta_{\rm BBN}=6.1\times10^{-10}$ (external, `release_acoustics`); `bridge::koppa_per_baryon` $=\ell_P^2/(R_p/4)$ (stored $\ell_P$ carries $G$, CALIBRATED (1); measured $R_p$), used as stored. The measured BAO scale (147 Mpc) is read only after the native value is printed.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | $\int_0^1dS/(1-S/2)=2\ln2$; $\int_0^{1/2}dS/(1-2S)$ is not defined and $\int_0^{S_1}dS/(1-2S)=-\tfrac12\ln(1-2S_1)$ for $S_1<\tfrac12$ (checked at $S_1=0.25$: $\tfrac12\ln2$); the sound speed $c/\sqrt{3(1+3/4)}=c/\sqrt{5.25}$ | $10^{-10}$ |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | elapsed duration. (a) $C=0.8$, $F_S=2$, $S\in[0,1]$: $\Delta t=0.625$ ($10^{-12}$); (b) $C=1-S/2$, $F_S=1$: $\Delta t=2\ln2$ ($10^{-10}$); (c) $C=1-S$, $F_S=1$, $S\in[0,1-\epsilon]$: $\Delta t=\ln(1/\epsilon)$ at $\epsilon=10^{-2},10^{-4}$ ($10^{-8}$), increasing as $\epsilon$ falls (no finite limit at $S=1$); (d) $C=1$, $F_S=1-2S$, $S\in[0,0.5-\epsilon/2]$: $\Delta t=-\tfrac12\ln\epsilon$ at $\epsilon=10^{-3}$ ($10^{-8}$); a routine that scans $C\,F_S$ for a sign change refuses the route $S\in[0,0.7]$ (returns "not defined") | as stated | yes |
| T2 | cycle counts. For $C=0.9$, $\Delta\tau_{\rm hop}=10^{-15}$ s, remote duration $T_r=10^{-6}$ s: (i) remote convention, $N=T_r/\Delta t_{\rm hop}$ with $\Delta t_{\rm hop}=\Delta\tau_{\rm hop}/C$; (ii) local convention, $N=(CT_r)/\Delta\tau_{\rm hop}$: equal to $10^{-12}$ relative; mixing (remote duration with the local hop) omits $C$ (factor $1/C$ high); mixing (local duration with the remote hop) double-counts $C$ (factor $C$ low); both factors to $10^{-12}$ | as stated | yes |
| T3 | relaxation. Reservoirs $T_1=400$, $T_2=300$: for $k=+0.7$ and $k=-0.7$, $T_1+T_2$ is conserved to $10^{-12}$ relative over $\tau\in[0,2]$; for $k=+0.7$ the separation equals $\Delta_0e^{-2k\tau}$ ($10^{-9}$) and the entropy-like function increases; for $k=-0.7$ the separation grows as $\Delta_0e^{+2|k|\tau}$ and the function decreases; the numerical rate $d(\ln T_1+\ln T_2)/d\tau$ equals $k(T_1-T_2)^2/(T_1T_2)$ to $10^{-6}$ | as stated | yes |
| T4 | acoustic history. The standing-scale chain recomputed from its formulas (photon count $16\pi\zeta(3)(k_BT/hc)^3$; $n_b=\eta n_\gamma$; epoch index $=n_bm_p/(aT^4/c^2)$; local $n_b=n_{b,0}N^3$; $c_s=c/\sqrt{3(1+3/4)}$; $\Gamma_{\rm esc}=c\sqrt{(8\pi/3)\varpi_bn_b}$; $L_{\rm eq}=c_s/(2\Gamma_{\rm esc})$; present-equivalent $=N\,L_{\rm eq}$) equals the engine's `present_equivalent_scale_m` to $10^{-9}$ relative; the native value in Mpc is printed first and is in $[14.7,1470]$ Mpc (a registered factor-10 window about 147 Mpc; a result outside the window is a rejection and is kept); then the measured 147 Mpc is read and the ratio reported; the compatibility duration $t=147\,\mathrm{Mpc}/c_s$ reproduces 830 Myr to 1 per cent (as stated in `pre_clearing`), and doubling the assumed scale doubles that duration exactly (no prediction) | as stated | yes |

Reported, not criteria: the native standing scale and its ratio to 147 Mpc; the epoch index $N$; the escape rate; durations.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch48_elapsed_recurrence_and_cosmic_dynamics`

## Record of run 1; two registration errors, one rejection kept (2026-11-10)

Run 1 (`ch48_run1_output.txt`): V1, T1, T2 and the remaining T3 and T4 criteria were met (T4: the independent recomputation equals the engine's `present_equivalent_scale_m` exactly; native scale $145.8332$ Mpc, inside the registered window, ratio $0.9921$ to 147 Mpc). Two criteria failed, both through errors in the registration.

(1) T3, $k<0$: the registered interval $\tau\in[0,2]$ was not checked against the domain of the law. With $k=-0.7$ the separation grows as $100e^{1.4\tau}$ and the colder reservoir $T_2=350-\Delta/2$ reaches zero at $\tau=\ln7/1.4=1.3899$; beyond that $\ln T_2$ is undefined and the printed value was `nan`. The criterion "the entropy-like function decreases for $k<0$" was evaluated on a state outside the physical domain. This is a registration error. The criteria are unchanged; the interval for $k<0$ is shortened to $\tau\in[0,1]$ (inside the domain) and the exit time $\ln7/(2|k|)$ is reported as a **post-run clause**: the law with $k<0$ leaves the positive-temperature domain at that $\tau$ (checked to $10^{-9}$).

(2) T4, the compatibility duration: the registration applied the speed of `release_acoustics`, $c/\sqrt{3(1+3/4)}=1.3084\times10^8$ m/s, to the statement of `cosmology::pre_clearing` ("147 Mpc $=c_s t_{\rm coupled}$, $\approx830$ Myr"), which uses $c_s=c/\sqrt3=1.7321\times10^8$ m/s. The registered statement (with the `release_acoustics` speed) is **rejected**: the duration is $1098.6$ Myr, $32.4$ per cent above 830 Myr. The rejection is kept and asserted in run 2. Post-run clauses, marked as such: with `pre_clearing::c_s` the duration reproduces 830 Myr to 1 per cent; the two durations differ by exactly $\sqrt{1.75}$. The engine therefore carries two sound speeds for the coupled epoch (the pure-relay $c/\sqrt3$ and the loaded $c/\sqrt{3(1+R)}$ at $R=3/4$); the compatibility duration depends on which is used. Run 2 is the run of record.
