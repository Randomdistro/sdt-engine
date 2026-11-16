# Chapter 54 — Cosmological Accounting

*Volume VII — Correspondence, Paradoxes and Discriminating Tests.*
Draft of 10 November 2026. Notation: $z$ the spectral shift of Chapter 45 ($1+z=C_o/C_e$, convention B); $d$ the declared geometric distance; $f_E$ the energy-per-event factor and $f_R$ the event-rate factor of a flux; $d_L=d(1+z)$ the flux distance of the endpoint-ratio branch; $d_A$ the angular-diameter distance; $\eta=d_L/[(1+z)^2d_A]$ the reciprocity ratio; $\sigma_{\rm CMB}=H_{0,\rm CMB}/c$. Executable companion: `Textbook/examples/ch54_cosmological_accounting.cpp`; pre-registration and captured output in `Textbook/validation/`. Section 54.1 is an accounting of factors in generic conventions (TOY): no measured data, no engine distance law and no fitted parameter. Section 54.2 reads the engine's stored scales (observed boundary values, class X).

## 54.1 One history, several observables

A cosmological model has to predict spectral shift, distance, angular scale, timing and background intensity jointly. The selected endpoint redshift branch and the pressure–temperature calibration (Chapters 44 and 47) constrain parts of that system. They do not independently fix the source evolution, the selection effects or the distance–state map. For an unresolved source the observed flux depends on the emitted power, geometric spreading, spectral transformation, the photon-event or recurrence transformation and any material interception, and each factor needs its declared frame convention.

**Flux factors (T1).** With $F=L/(4\pi d^2)f_Ef_R$:

* branch (a), the endpoint-ratio branch (energy per event and arrival rate per observer duration both scale as $(1+z)^{-1}$, Chapter 45): $F=L/[4\pi d^2(1+z)^2]$, so $d_L=d(1+z)$;
* branch (b), only the energy per event shifts ($f_R=1$): $F=L/[4\pi d^2(1+z)]$;
* the hybrid: a distance that already contains the factor $(1+z)$ (a flux distance from another history) inserted into the flux law of branch (a) applies it twice, $F\propto(1+z)^{-4}$.

Executed for $z=0.1,0.5,1,2$ (all to $10^{-15}$ of the closed forms):

| $z$ | hybrid fainter than (a) by $5\log_{10}(1+z)$ | (b) brighter than (a) by $2.5\log_{10}(1+z)$ |
|---|---|---|
| $0.1$ | $0.206963$ mag | $0.103482$ mag |
| $0.5$ | $0.880456$ mag | $0.440228$ mag |
| $1$ | $1.505150$ mag | $0.752575$ mag |
| $2$ | $2.385606$ mag | $1.192803$ mag |

Borrowing a distance law from one history and a flux law from another creates an inconsistent hybrid; its size is the entire magnitude scale of a supernova-type test at $z\sim1$.

**Reciprocity (T2).** $\eta=d_L/[(1+z)^2d_A]$ equals $1$ when the physical size transforms with the endpoint ruler ratio ($d_A=d/(1+z)$, convention B) and $1/(1+z)$ when sizes are left unscaled ($d_A=d$, convention A). The two conventions differ by $z/(1+z)$: $0.0909$ at $z=0.1$, $0.3333$ at $z=0.5$, $0.5$ at $z=1$, $0.6667$ at $z=2$ (to $10^{-15}$). The convention for sizes has to be declared; this chapter does not decide it, and a measured $\eta(z)$ would.

**A single observable can hide a hybrid (T3).** Redefining the distance as $d'=d/(1+z)$ makes the hybrid flux equal the consistent branch-(a) flux at every $z$ (exactly), and the angular size $s/d'$ then exceeds the geometric $s/d$ by the factor $1+z$ ($\ln2=0.693$ at $z=1$). A fit to flux alone can therefore absorb the inconsistency into the distance law; a second observable at the same sources (angular size, or timing) cannot absorb it. Borrowing from one history for one observable and from another for the next creates an inconsistent hybrid; the joint prediction must come from one declared history.

## 54.2 Background composition and stored scales

The background may encode reprocessed ancestry only through a physically specified transport history. A superposition of epochs can match the integrated energy and still leave spectral distortions: Chapter 44 (T3) showed it for two energy-matched Planck components (readings $4.494$, $3.241$, $3.120$ K; best single-Planck fit residual $0.162$; $3.5\times10^{-5}$ for components 1 per cent apart). A calculation must predict the spectrum, the angular structure and the retained source-memory depth together. Baryon-acoustic structure needs the loading response and a length construction: the native standing scale ($145.8332$ Mpc, $0.9921$ of 147 Mpc) and the measured-scale-divided-by-speed durations ($830.43$ and $1098.56$ Myr for the two stored sound speeds) have different provenance (Chapter 48).

**Executed (T4, addendum).** The engine stores $R_{\rm CMB}=9.527\times10^{26}$ m (an observed boundary, class X). Then $R_{\rm CMB}/c=100.700$ Gyr. The header's relation $R_{\rm CMB}=\ln(1+z)/\sigma_0$ with $\sigma_{\rm CMB}=7.285991\times10^{-27}$ m$^{-1}$ gives $9.612932\times10^{26}$ m for $z=1100$ ($+0.902$ per cent against the stored value) and $9.599151\times10^{26}$ m for $z_{\rm release}=1089$ ($+0.757$ per cent): the comment relation is approximate, not an identity, for either redshift. The engine also stores `age_SDT_Gyr` $=48$ Gyr, $0.4767$ of $R_{\rm CMB}/c$: two stored time scales that differ by a factor of $2.10$. The cosmology header guards the $\sigma_0$-integrated distance as not an SDT derivation (an in-flight accumulation the recovered branch excludes), so none of these numbers is a derived distance or a derived age; they are stored values with their provenance recorded, and a consistent history has to say which one a given observable uses (R54.5).

## 54.3 Dataset discipline

Measured angles, spectra and timing are the primary comparison quantities. Model-dependent reconstructions can be useful and have to be labelled with their reconstruction assumptions. A framework's own derived decompositions are not neutral data for adjudicating another framework. No dataset was loaded in this chapter. The determining test is to freeze one pressure-history and source-response model, then compare several observables jointly with shared parameters and a withheld dataset (R54.6).

## 54.4 Input ledger and residuals

| quantity | value | label |
|---|---|---|
| flux factors, magnitudes, $\eta$, angular-size ratio | Section 54.1 | CONSTRUCTION (generic conventions) and COMPUTED |
| $R_{\rm CMB}$ | `law_I`, `measured` | OBSERVED (stored boundary; class X) |
| $H_{0,\rm CMB}$ | `cosmology::strain` | OBSERVED (class X unit conversion) |
| $z_{\rm rec}=1100$ | `measured` | legacy ballpark (not cited as measured) |
| $z_{\rm release}=1089$ | `measured` | OBSERVED (FIRAS frame) |
| `age_SDT_Gyr` $=48$ | `cosmology::age` | stored value (provenance: standard comoving distance reinterpreted) |
| standing scale, durations | Chapter 48 | COMPUTED; compatibility values (class X) |

**Residuals.**

* **R54.1 — a distance relation.** No $d(z)$ is derived; the engine records NO-DERIVED-$d(z)$.
* **R54.2 — sizes.** The convention for angular sizes (the value of $\eta$) is not decided.
* **R54.3 — sources.** Source evolution, selection effects and material interception were not modelled.
* **R54.4 — the background.** The spectrum, the angular structure and the retained source-memory depth were not predicted jointly.
* **R54.5 — stored scales (proposal to the author, canon untouched).** The comment relating $R_{\rm CMB}$ to $\ln(1+z)/\sigma_0$ is off by $0.76$–$0.90$ per cent, and the stored `age_SDT_Gyr` (48) and $R_{\rm CMB}/c$ (100.7 Gyr) differ by $2.1$; the two could be reconciled or labelled in `cosmology.hpp`.
* **R54.6 — a withheld dataset.** No pressure-history model was frozen and no withheld dataset defined.

## 54.5 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch54_cosmological_accounting
```

Criteria were registered in `Textbook/validation/ch54_PRE_REGISTRATION.md` before the instrument existed; test T4 was added as a dated addendum before its code existed. Run 1 (`ch54_run1_output.txt`) failed eight criteria through two instrument defects (a magnitude sign convention and a doubled factor), both recorded. Run 3 (`ch54_run3_output.txt`) is the run of record: it repeats T1–T3 unchanged and adds T4, and met every criterion.

## 54.6 Exercises and answers

**Exercise 1.** What magnitude error does the hybrid make at $z=0.3$?

*Answer.* $5\log_{10}1.3=0.5698$ mag.

**Exercise 2.** Show that $d_L=d(1+z)$ in branch (a).

*Answer.* $F=L/[4\pi d^2(1+z)^2]=L/(4\pi d_L^2)$ with $d_L=d(1+z)$.

**Exercise 3.** At what $z$ do the two size conventions differ by 25 per cent?

*Answer.* $z/(1+z)=0.25$ gives $z=1/3$.

**Exercise 4.** Why does a flux fit alone not expose the hybrid?

*Answer.* The distance law has a free function; $d'=d/(1+z)$ absorbs the extra factor exactly (T3). The angular size $s/d'$ then differs by $1+z$.

**Exercise 5.** What is the light-travel time for $R_{\rm CMB}=9.527\times10^{26}$ m?

*Answer.* $R/c=3.178\times10^{18}$ s $=100.70$ Gyr.

**Exercise 6.** Which stored numbers are derived in the engine's distance scales?

*Answer.* None: $R_{\rm CMB}$ is an observed boundary, $H_0$ an observed unit conversion and `age_SDT_Gyr` a reinterpreted standard value.

## 54.7 Scope

Established: the flux-factor ledger under declared conventions, the size of the hybrid error and of the reciprocity ambiguity, that a single observable can hide a hybrid and a joint test cannot, and the relations among the stored distance and duration scales.

Not established: a distance relation (R54.1), the size convention (R54.2), source evolution and selection (R54.3), the joint background prediction (R54.4), reconciliation of the stored scales (R54.5) and a withheld-data test (R54.6).

*Where it leads.* Chapter 55 sets out framework correspondence: the native derivation chain beside the equivalent expression, with provenance and discrimination kept as separate columns.
