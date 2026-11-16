# Chapter 48 — Elapsed Recurrence and Cosmic Dynamics

*Volume VI — Sz, Pressure History and Coupled Ratios.*
Draft of 10 November 2026. Notation: $S$ the state coordinate (Chapter 41); $F_S=dS/d\tau$ the evolution law; $C=d\tau/dt$ the tick-rate ratio (local duration per remote duration); $\Delta t_{\rm hop}=\Delta\tau_{\rm hop}/C$ the remote hop duration; $c_s$ a relay sound speed. Executable companion: `Textbook/examples/ch48_elapsed_recurrence_and_cosmic_dynamics.cpp`; pre-registration and captured output in `Textbook/validation/`. Inputs for the acoustic section: $\{h,c,k_B,m_p,a_{\rm rad},T_{\rm CMB}\}$ (`measured`), $\eta_{\rm BBN}=6.1\times10^{-10}$ (external input of `release_acoustics`) and `bridge::koppa_per_baryon` as stored (named below).

## 48.1 State history versus rate history

A route $Q(S)$ supplies configurations. An evolution law $dS/d\tau=F_S$ supplies chronology. With the tick-rate ratio $C$, the elapsed remote duration along a route is

$$\Delta t=\int\frac{dS}{C(S)\,F_S(S)}. \tag{48.1}$$

A zero or a sign change of $C$ or $F_S$ on the route changes the integral and has to be treated explicitly.

**Executed (V1, T1).** (a) $C=0.8$, $F_S=2$, $S\in[0,1]$: $\Delta t=0.625$. (b) $C=1-S/2$, $F_S=1$: $2\ln2=1.3862943611$ (to $10^{-15}$). (c) A zero of $C$ at the end of the route: $C=1-S$, $F_S=1$ gives $\Delta t=4.6051702$ to $S=0.99$ and $9.2103404$ to $S=0.9999$, both equal to $\ln(1/\epsilon)$; the duration grows without a finite limit as the route approaches $S=1$ (the logarithm). (d) A zero of $F_S$: $C=1$, $F_S=1-2S$ gives $3.4538776$ up to $S=0.4995$, equal to $-\tfrac12\ln\epsilon$ at $\epsilon=10^{-3}$. A routine that scans $C\,F_S$ along the route for a sign change refuses the route $S\in[0,0.7]$ (returns "not defined"), because the integrand passes through a singularity at $S=0.5$. A duration across such an event is not a number to be quoted; the route has to be split at the event and the event itself given a physical account (a turning point, an arrest, a change of branch).

A local relay cycle count is $N=\int dt/\Delta t_{\rm hop}$ with the remote hop $\Delta t_{\rm hop}=\Delta\tau_{\rm hop}/C$. **Executed (T2).** For $C=0.9$, $\Delta\tau_{\rm hop}=10^{-15}$ s and a remote duration $10^{-6}$ s, the remote convention ($T_r/\Delta t_{\rm hop}$) and the local convention ($CT_r/\Delta\tau_{\rm hop}$) both give $9.000\times10^{8}$ cycles. Mixing them is wrong in a definite way: the remote duration with the local hop counts $1.000\times10^{9}$ ($1/C$ too high, omitting the tick-rate ratio) and the local duration with the remote hop counts $8.1\times10^{8}$ ($C$ too low, applying it twice).

## 48.2 Progression is a property of the law

An equilibrium state relation can be traversed in either mathematical direction. A physical progression requires transport, loss of recoverable correlations, boundary export or a coarse-graining rule; cooling, chemical conversion and lattice rearrangement can each supply a progression variable; a static octave label does not.

**Executed (T3).** Two reservoirs with unit heat capacity, $T_1=400$ and $T_2=300$, exchange by $dT_1/d\tau=-k(T_1-T_2)$, $dT_2/d\tau=+k(T_1-T_2)$. The state relation $T_1+T_2=700$ holds to $10^{-14}$ for $k=+0.7$ and for $k=-0.7$: the relation does not distinguish the two laws. The separation follows $\Delta_0e^{-2k\tau}$ ($6.081006$ at $\tau=2$ for $k=+0.7$, equal to the exact value to $7\times10^{-13}$) and the function $\ln T_1+\ln T_2$ rises from $11.69524702$ to $11.71579084$ with the rate $k(T_1-T_2)^2/(T_1T_2)$ (confirmed to $7\times10^{-9}$). For $k=-0.7$ the separation grows ($405.52$ at $\tau=1$) and the function falls to $11.30698783$. The law with $k<0$ takes the colder reservoir through zero temperature at $\tau=\ln7/(2|k|)=1.389936$ (a post-run clause; the registered interval $[0,2]$ ran past it, recorded in the pre-registration): the relation survives, the physical domain does not. The sign of the coupling is a property of the transport law and has to be supplied with the relation.

## 48.3 Coupled acoustic history

A present-equivalent standing scale can be computed from a declared release construction. An integrated sound horizon needs, instead, the time-dependent acoustic speed and an evolution law. A measured acoustic scale divided by an assumed speed gives a compatibility duration, not a prediction of that same scale.

**Executed (T4).** The chain of `bridge::release_acoustics` was recomputed independently from its stated formulas: photon count $n_\gamma=16\pi\zeta(3)(k_BT_0/hc)^3=4.107268\times10^{8}$ m$^{-3}$; present baryon count $\eta n_\gamma=0.2505434$ m$^{-3}$; epoch index (baryon resistance density over radiation resistance density) $N=902.169741$; local baryon count $n_{b,0}N^3$; loaded sound speed $c_s=c/\sqrt{3(1+3/4)}=1.308402\times10^{8}$ m/s; escape rate $\Gamma_{\rm esc}=c\sqrt{(8\pi/3)\varpi_bn_b}=1.311573\times10^{-14}$ s$^{-1}$; standing radius $L_{\rm eq}=c_s/(2\Gamma_{\rm esc})=4.987910\times10^{21}$ m; present-equivalent scale $NL_{\rm eq}=4.499941\times10^{24}$ m $=145.8332$ Mpc. The independent recomputation equals the engine's `present_equivalent_scale_m` exactly. Only after this value was printed was the measured acoustic scale read: $147$ Mpc is $4.535946\times10^{24}$ m, and the ratio is $0.9921$. The inputs are those named in the header: the external $\eta_{\rm BBN}$ (shared BBN/FIRAS provenance) and `koppa_per_baryon`$=\ell_P^2/(R_p/4)$, which carries the stored $\ell_P$ (CALIBRATED (1); contaminating input named: $G$ enters at `laws.hpp:99`) and the measured proton boundary radius $R_p$. No BAO ruler, $H_0$ or $R_{\rm CMB}$ enters the chain. The agreement at 0.8 per cent is convergence with a measured scale, and the chain's inputs are named above.

**The duration is a compatibility value (T4).** In `cosmology::pre_clearing` the coupled-epoch duration is defined as $147\ \mathrm{Mpc}/c_s$ with $c_s=c/\sqrt3$, giving $830.43$ Myr (reproducing the stated 830 Myr to $5\times10^{-4}$). Doubling the assumed scale doubles that duration exactly: the quantity is the measured scale in different units, and the header marks it class X. The engine carries two sound speeds for the coupled epoch: $c/\sqrt3$ in `pre_clearing` and the loaded $c/\sqrt{3(1+R)}$ at $R=3/4$ in `release_acoustics`. With the loaded speed the same arithmetic gives $1098.56$ Myr, larger by exactly $\sqrt{1.75}=1.322876$. The registered statement that the loaded speed reproduces 830 Myr was rejected (it is $32.4$ per cent high; the registration applied the wrong speed; kept). Which speed belongs to which question is not settled by this chapter (R48.3).

## 48.4 Input ledger and residuals

| quantity | value | label |
|---|---|---|
| $h,c,k_B,m_p,a_{\rm rad},T_{\rm CMB}$ | `measured` | CODATA/FIRAS; $a_{\rm rad}$ rounded (Chapter 44) |
| $\eta_{\rm BBN}$ | `release_acoustics` | OBSERVED (external BBN-deuterium input; not fitted) |
| `koppa_per_baryon` | `bridge` | stored: $\ell_P$ carries $G$, CALIBRATED (1) (`laws.hpp:99`); $R_p$ measured |
| standing scale $145.8332$ Mpc | Section 48.3 | COMPUTED (shared-input with BBN/FIRAS) |
| 147 Mpc | `pre_clearing` | OBSERVED, read after the native value |
| 830 Myr, 1098.56 Myr | Section 48.3 | compatibility durations (class X) |
| routes, laws, reservoirs | Sections 48.1–48.2 | CONSTRUCTION (no measured input) |

**Residuals.**

* **R48.1 — the evolution law.** No $F_S$ is derived from contact relaxation; durations were computed for stand-in laws only.
* **R48.2 — events.** The physical account of a zero of $C$ or $F_S$ (turning point, arrest, branch change) is not supplied.
* **R48.3 — two sound speeds.** $c/\sqrt3$ and $c/\sqrt{3(1+3/4)}$ both appear for the coupled epoch; the choice per question is not derived.
* **R48.4 — the integrated horizon.** No time-dependent acoustic speed and no integrated horizon were computed; only the present-equivalent standing scale.
* **R48.5 — inputs of the standing scale.** The scale depends on $\eta_{\rm BBN}$, on the stored $\ell_P$ and on the measured $R_p$; their covariance was not propagated.

## 48.5 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch48_elapsed_recurrence_and_cosmic_dynamics
```

Criteria were registered in `Textbook/validation/ch48_PRE_REGISTRATION.md` before the instrument existed. Run 1 (`ch48_run1_output.txt`) failed two criteria through errors in the registration (an interval that left the physical domain, and a sound speed applied to the statement of a different one); both are recorded, the second kept as a rejection. Run 2 (`ch48_run2_output.txt`) is the run of record and met every criterion, with the post-run clauses marked.

## 48.6 Exercises and answers

**Exercise 1.** Find the duration for $C=1-S$, $F_S=1$ up to $S=0.9$.

*Answer.* $\int_0^{0.9}dS/(1-S)=\ln10=2.3026$.

**Exercise 2.** Count the cycles for $C=0.8$, $\Delta\tau_{\rm hop}=10^{-15}$ s and a remote duration of $10^{-6}$ s.

*Answer.* $N=CT_r/\Delta\tau_{\rm hop}=0.8\times10^{-6}/10^{-15}=8\times10^{8}$.

**Exercise 3.** Why does the integral (48.1) not extend across $S=0.5$ for $F_S=1-2S$?

*Answer.* $F_S$ vanishes at $S=0.5$ and the integrand $1/F_S$ has a non-integrable singularity there; the route has to be split and the event interpreted.

**Exercise 4.** Show that $T_1+T_2$ is conserved for either sign of $k$.

*Answer.* $d(T_1+T_2)/d\tau=-k(T_1-T_2)+k(T_1-T_2)=0$.

**Exercise 5.** When does the law with $k=-0.7$ take the colder reservoir to zero?

*Answer.* The separation is $100e^{1.4\tau}$ and the mean 350; $T_2=0$ when the separation is 700, $\tau=\ln7/1.4=1.3899$.

**Exercise 6.** The two sound speeds give compatibility durations 830.43 and 1098.56 Myr. Check their ratio.

*Answer.* $c/\sqrt3\div c/\sqrt{5.25}=\sqrt{1.75}=1.3229$, and $1098.56/830.43=1.3229$.

## 48.7 Scope

Established: the duration integral (48.1) with exact checks, including the logarithmic growth near a zero of $C$ and the refusal of a route that crosses a zero of $F_S$; the cycle-count conventions and the exact factors of a mixed convention; that a relation conserved under either sign of the coupling does not select the progression; the independent recomputation of the engine's standing scale ($145.8332$ Mpc, $0.9921$ of 147 Mpc) with its inputs named; that the compatibility duration is a restatement of the scale and depends on which sound speed is used.

Not established: an evolution law from contact relaxation (R48.1), the interpretation of events (R48.2), the choice of sound speed (R48.3), an integrated horizon (R48.4) and the propagated input covariance (R48.5).

*Where it leads.* Volume VII turns to correspondence, paradoxes and discriminating tests; it begins with inertia and equivalence (Chapter 49).
