# Chapter 56 — Cross-Domain Prediction

*Volume VII — Correspondence, Paradoxes and Discriminating Tests.*
Draft of 10 November 2026. Notation: $b$ the mechanical atomic boundary; $\sigma_{\rm coll}=\tfrac67(2b)^2$ the lock-weighted collision measure (`law_IV::transport::collision_measure`); $\eta$, $\kappa$, $D$ viscosity, conductivity and self-diffusivity; $\mathrm{Pr}$, $\mathrm{Sc}$, $\mathrm{Le}$ the Prandtl, Schmidt and Lewis numbers; $Q$ production rate, $v$ outflow speed, $\sigma_{\rm ext}$ extinction cross-section; $\mathrm{Kn}$ Knudsen number; $\alpha_{\rm th}$ thermal diffusivity, $t_{\rm th}$ a relaxation time, $\delta$ penetration depth. Executable companion: `Textbook/examples/ch56_cross_domain_prediction.cpp`; pre-registration and captured output in `Textbook/validation/`. Inputs: $k_B$ and $\pi$; a generic monatomic load $m=39.948$ u and generic boundaries; no measured transport value is loaded. The outflow and thermal numbers are TOY stand-ins.

## 56.1 Freeze the common kernel

A cross-domain test fixes common parameters on one observable family and predicts another. The hard-lock transport kernel is a concrete structure: one collision measure enters viscosity, conductivity and diffusion,

$$\eta=\tfrac5{16}\frac{\sqrt{mk_BT/\pi}}{\sigma_{\rm coll}},\quad\kappa=\tfrac{75}{64}\frac{k_B\sqrt{k_BT/(\pi m)}}{\sigma_{\rm coll}},\quad D=\tfrac38\frac{\sqrt{k_BT/(\pi m)}}{n\,\sigma_{\rm coll}},\quad n=\frac{P}{k_BT}, \tag{56.1}$$

and the ratios follow jointly within the dilute-monatomic domain: $\mathrm{Pr}=c_p\eta/\kappa=2/3$ with $c_p=\tfrac52k_B/m$, $\mathrm{Sc}=\eta/(\rho D)=5/6$, $\mathrm{Le}=\kappa/(\rho c_pD)=5/4$. Only two are independent, since $\mathrm{Le}=\mathrm{Sc}/\mathrm{Pr}$. The engine labels the kernel as class C and states a whole-range argon comparison in its comment; that comparison was not re-executed here.

**Executed (V1, T1).** Over 27 states ($T=100,300,1000$ K; $P=10^3,10^5,10^7$ Pa; $b=1.0,1.9,2.5\times10^{-10}$ m) the three ratios equal $2/3$, $5/6$, $5/4$ to $4.4\times10^{-16}$ and $\mathrm{Le}=\mathrm{Sc}/\mathrm{Pr}$ to $2.2\times10^{-16}$: the ratios do not depend on temperature, pressure, load or boundary. At fixed pressure the log-log slopes are $0.5$ for $\eta$ and $\kappa$ against $T$ and $1.5$ for $D$ against $T$, and $-1$ for $D$ against $P$ (to $2\times10^{-16}$). For the generic state ($300$ K, $10^5$ Pa, $b=1.9\times10^{-10}$ m): $\eta=2.3612\times10^{-5}$ Pa s, $\kappa=1.8429\times10^{-2}$ W m$^{-1}$K$^{-1}$, $D=1.7692\times10^{-5}$ m$^2$s$^{-1}$, $\sigma_{\rm coll}=1.237714\times10^{-19}$ m$^2$ (COMPUTED from the kernel; the boundary $b$ is a supplied input, R56.2).

**One kernel, three observables (T2).** Freezing the kernel on one observable predicts the others with no further parameter. From the viscosity alone the collision measure is recovered exactly ($1.237714\times10^{-19}$ m$^2$); the conductivity ($1.842890\times10^{-2}$) and the diffusivity ($1.769174\times10^{-5}$) predicted from it equal the engine's values, and the conductivity at $1000$ K predicted from the $300$ K value by $T^{1/2}$ ($3.364642\times10^{-2}$) equals the kernel's. These predictions are identities of the kernel. Their content for a test is that the three measured coefficients, with $\sigma_{\rm coll}$ fixed by one, must obey the same ratios and exponents; a measured departure would be a departure of the kernel or of its domain (dilute, monatomic, hard-lock).

## 56.2 An optical–hydrodynamic invariant

For a steady spherical outflow $n=Q/(4\pi vr^2)$ with constant extinction cross-section and no destruction, the radial optical depth is $\tau=Q\sigma_{\rm ext}/(4\pi vr)$ and at $\tau=1$, $r_{\rm photo}=Q\sigma_{\rm ext}/(4\pi v)$. The collision mean free path is $1/(n\sigma_{\rm coll})$, so

$$\mathrm{Kn}(r_{\rm photo})=\frac{\sigma_{\rm ext}}{\sigma_{\rm coll}}. \tag{56.2}$$

Production and speed cancel: optical thickness does not imply a collisional continuum. The formal photosphere must also lie outside the nucleus and within the survival domain of the species, which is not checked here (R56.4). A full tangent column at impact radius $b$ exceeds the outward radial column at $r=b$ by $\pi$ in the infinite constant-speed model.

**Executed (T3).** Over 12 combinations ($Q=10^{20}\ldots10^{32}$ s$^{-1}$, $v=10,500,10^4$ m/s, varied cross-sections) the Knudsen number at $r_{\rm photo}$ equals $\sigma_{\rm ext}/\sigma_{\rm coll}$ to $2.2\times10^{-16}$. For the generic outflow $Q=10^{28}$ s$^{-1}$, $v=500$ m/s, $\sigma_{\rm ext}=10^{-20}$ m$^2$: $r_{\rm photo}=1.5915\times10^4$ m. The numerically integrated tangent column over $|l|\le10^4b$ equals $2\arctan(10^4)$ times the prefactor ($1.0\times10^{-14}$ agreement) and its ratio to the radial column is $3.141393$, within $6.4\times10^{-5}$ of $\pi$ (the finite range removes $2\times10^{-4}$).

## 56.3 Rotation, heat and appearance

Thermal penetration $\delta=\sqrt{2\alpha_{\rm th}/\omega}$ connects rotation, conductivity, resistance density and heat capacity. For a single relaxing reservoir the modulation gain is $[1+(\omega t_{\rm th})^2]^{-1/2}$ and the lag $\arctan(\omega t_{\rm th})$. Ring particles and comet surfaces can share this structure with different boundary flux and material functions.

**Executed (T4).** For $\alpha_{\rm th}=1.3\times10^{-6}$ m$^2$s$^{-1}$ and a one-day period $\delta=0.18908$ m; the damped travelling solution $e^{-x/\delta}\cos(\omega t-x/\delta)$ satisfies $\partial_tT=\alpha_{\rm th}\partial_x^2T$ with a worst residual $1.7\times10^{-7}$ relative to the local amplitude of $\partial_tT$ (run 1 normalised by the point value, which vanishes along the solution; recorded in the pre-registration). RK4 integration of the single reservoir gives the steady gains and lags:

| $\omega t_{\rm th}$ | gain | lag (rad) |
|---|---|---|
| $0.1$ | $0.995037$ | $0.0996687$ |
| $1$ | $0.707107$ | $0.785398$ |
| $10$ | $0.0995037$ | $1.471128$ |

all equal to the closed forms to $6.5\times10^{-12}$.

## 56.4 The determining test

Infer one sector's state independently, then predict the linked optical, thermal or flow observable without replacing the cross-section or relaxation parameter after the comparison. In this chapter that means: fix $\sigma_{\rm coll}$ from one transport measurement and predict the others (T2); fix $\sigma_{\rm ext}/\sigma_{\rm coll}$ from a measured Knudsen number at a photosphere and predict the rest of the outflow; fix $t_{\rm th}$ from one modulation and predict the lag at another frequency. No measurement was loaded and no such comparison was made (R56.1).

## 56.5 Input ledger and residuals

| quantity | value | label |
|---|---|---|
| $k_B$, $\pi$ | `measured`, math | exact SI; constant |
| load $m=39.948$ u, boundaries $b$ | generic | CONSTRUCTION (supplied, not derived) |
| kernel moments $\tfrac38$, $\tfrac5{16}$, $\tfrac{75}{64}$, $\tfrac67$ | `law_IV::transport` | COMPUTED (geometry coefficients, class C) |
| $\eta,\kappa,D$, $\sigma_{\rm coll}$ | Section 56.1 | COMPUTED (no measured transport value) |
| outflow and thermal numbers | Sections 56.2–56.3 | CONSTRUCTION (TOY stand-ins) |

**Residuals.**

* **R56.1 — the comparison.** No measured transport, Knudsen or modulation record was loaded; the determining test of Section 56.4 is not executed.
* **R56.2 — the boundary.** The mechanical atomic boundary $b$ is a supplied input; the engine's transport relations do not derive it.
* **R56.3 — the domain.** The kernel is hard-lock, dilute and monatomic; molecular gases, dense states and other domains are outside it.
* **R56.4 — the outflow model.** Constant speed, constant extinction cross-section and no destruction were assumed; the photosphere location relative to the nucleus and to the survival domain was not checked.
* **R56.5 — heat.** A single relaxing reservoir and a semi-infinite slab; the boundary flux and the material functions of real surfaces were not computed.

## 56.6 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch56_cross_domain_prediction
```

Criteria were registered in `Textbook/validation/ch56_PRE_REGISTRATION.md` before the instrument existed. Run 1 (`ch56_run1_output.txt`) failed one criterion through an unspecified normaliser of the heat-equation residual (recorded). Run 2 (`ch56_run2_output.txt`) is the run of record and met every criterion.

## 56.7 Exercises and answers

**Exercise 1.** Show $\mathrm{Pr}=2/3$ from (56.1).

*Answer.* $\eta/\kappa=\tfrac5{16}\cdot\tfrac{64}{75}\cdot\tfrac mk=\tfrac4{15}\tfrac mk$; with $c_p=\tfrac52\tfrac km$, $\mathrm{Pr}=\tfrac52\cdot\tfrac4{15}=\tfrac23$.

**Exercise 2.** Why is $D\propto T^{3/2}$ at fixed pressure?

*Answer.* $D\propto\sqrt T/n$ and $n=P/(k_BT)$, so $D\propto T^{3/2}/P$.

**Exercise 3.** Derive (56.2).

*Answer.* $n(r_{\rm photo})\,r_{\rm photo}=1/\sigma_{\rm ext}$ at $\tau=1$, so the mean free path is $\sigma_{\rm ext}r_{\rm photo}/\sigma_{\rm coll}$ and $\mathrm{Kn}=\sigma_{\rm ext}/\sigma_{\rm coll}$.

**Exercise 4.** Why is the tangent column $\pi$ times the radial one at $r=b$?

*Answer.* $\int_{-\infty}^\infty dl/(b^2+l^2)=\pi/b$ against $1/b$ for the radial column.

**Exercise 5.** Find $\delta$ for $\alpha_{\rm th}=10^{-6}$ m$^2$s$^{-1}$ and a period of 12 h.

*Answer.* $\omega=2\pi/43200=1.454\times10^{-4}$ s$^{-1}$; $\delta=\sqrt{2\times10^{-6}/1.454\times10^{-4}}=0.117$ m.

**Exercise 6.** What are the gain and lag at $\omega t_{\rm th}=3$?

*Answer.* Gain $1/\sqrt{10}=0.316$; lag $\arctan3=1.249$ rad.

## 56.8 Scope

Established: the joint ratios and exponents of the transport kernel across 27 states; that one frozen observable fixes the others within the kernel; the optical–hydrodynamic invariant (56.2) and the factor $\pi$; the penetration depth and the gain and lag of a single reservoir.

Not established: any comparison with a measured record (R56.1), the derivation of the boundary (R56.2), the domain of the kernel (R56.3), the outflow assumptions (R56.4) and real-surface heat transfer (R56.5).

*Where it leads.* Volume VIII turns to implementation and verification: Chapter 57 sets the conventions by which every number in this book is traced to a source, a label and an executed instrument.
