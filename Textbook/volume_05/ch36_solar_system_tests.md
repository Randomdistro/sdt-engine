# Chapter 36 — Solar-System Tests

*Volume V — Bodies, Fields and Propagation.*
Draft of 10 November 2026. Notation: $\varpi_i$ is the source length of body $i$ (the engine's koppa length). The ephemeris publishes the measured source strength $c^2\varpi_i$ under the symbol $GM_i$; it is read here as that measured strength, converted by $\varpi_i=GM_i/c^2$, and not as a product of $G$ and a mass; $t$ counts days after J2000.0 (JD 2451545.0 TDB). Executable companion: `Textbook/examples/ch36_solar_system_tests.cpp`; data fetch `Textbook/tools/fetch_horizons.py`; pre-registration and captured output in `Textbook/validation/`. The ephemeris values are OBSERVED-processed: JPL Horizons, DE441, a fit to ranging, VLBI and optical observations. No number was entered from memory.

## 36.1 Initial conditions are part of the experiment

A solar-system calculation needs a dated reference frame, an epoch, positions and velocities, and a ledger of source strengths. Here the frame is the barycentric ICRF-aligned ecliptic of J2000.0, the epoch JD 2451545.0 TDB, the initial vectors those of the ephemeris, and the source strengths the ephemeris gravitational parameters. **Neither input becomes a prediction merely because a native solver consumes it.** The ephemeris state vectors are themselves a fit that includes relativistic dynamics, and the gravitational parameters are fitted to the same observations. What can be tested is the dynamics: the engine's kernel (Chapter 15) and its integrator, given those inputs.

The comparison observables were fixed before execution (the pre-registration also records the order of events: the ephemeris files were fetched first, and only the first rows of the Earth file had been looked at when the criteria were registered): the **heliocentric angular separation** between the engine's and the ephemeris position, and the **relative error of the heliocentric distance**, for each planetary system at 360, 1800, 3650 and 7300 days. A visually closed orbit can coexist with a measurable phase drift; holding the Sun fixed by hand would change the boundary conditions and hide impulse exchange, so the Sun moves here with the rest.

## 36.2 The model

Nine bodies: the Sun and the barycentres of the eight planetary systems (the Earth–Moon barycentre as one body, with $GM$ the sum for the Earth and the Moon; the satellites of the giants are omitted from their $GM$, a fraction of order $2\times10^{-4}$ of each giant). The acceleration is the engine's kernel $\vec a_i=c^2\sum_j\varpi_j(\vec r_j-\vec r_i)/|\vec r_j-\vec r_i|^3$ with `dynamics::step_rk4`, steps of $0.125$ d. Not modelled: general-relativistic terms, the asteroids and Pluto, the Sun's quadrupole, the Moon's separate orbit. The retardation, occlusion and movement-budget response of Chapter 35 are not used: the instrument tests the kernel, the integrator and the inputs, not a native correction.

**Checks of the instrument.** The data files each have 731 rows at 10-day spacing and the Sun's $GM$ read equals $132\,712\,440\,041.93938$ km$^3$/s$^2$ (V1). The two-body return with the same code path (a test body on a 1 AU circular orbit about a source of length $GM_\odot/c^2$) closed to $3.0\times10^{-12}$ of $a$ after one period (V2). For Mercury at $t=1800$ d the heliocentric angular position from steps of $0.125$ d and $0.0625$ d differs by $0.0203''$, below the registered $0.1''$ (T1): the step is not what limits the comparison.

## 36.3 The comparison

**Executed (T2).** Heliocentric angular separation (arcsec) between the engine and the ephemeris:

| system | 360 d | 1800 d | 3650 d | 7300 d | largest relative distance error |
|---|---|---|---|---|---|
| Mercury | 0.125 | 3.784 | 8.149 | 2.453 | $2.5\times10^{-6}$ |
| Venus | 0.184 | 0.873 | 1.709 | 3.457 | $2.0\times10^{-7}$ |
| Earth–Moon | 0.073 | 0.366 | 0.722 | 1.447 | $5.2\times10^{-9}$ |
| Mars | 0.047 | 0.184 | 0.309 | 0.680 | $4.4\times10^{-7}$ |
| Jupiter | 0.002 | 0.125 | 0.738 | 1.182 | $9.3\times10^{-7}$ |
| Saturn | 0.001 | 0.129 | 0.560 | 1.500 | $1.4\times10^{-6}$ |
| Uranus | 0.002 | 0.032 | 0.062 | 0.125 | $1.8\times10^{-7}$ |
| Neptune | 0.001 | 0.018 | 0.025 | 0.074 | $3.7\times10^{-7}$ |

Table 36.1. Heliocentric angular error of the engine's twenty-year integration against DE441 (arcsec), and the largest relative error of the heliocentric distance over the four epochs, executed (T2).

All thirty-two values lie within the registered window ($60''$ and $10^{-5}$): the largest angular error is $8.15''$ (Mercury, ten years) and the largest distance error $2.5\times10^{-6}$ (Mercury). Over twenty years the engine's kernel, driven by the ephemeris initial conditions and source strengths, reproduces the ephemeris positions of the planets to a few arcseconds, without general-relativistic terms.

**A registered prediction that failed.** The pre-registration stated that at 7300 days Mercury's error exceeds those of Venus, the Earth–Moon barycentre and Mars, on the grounds that the unmodelled general-relativistic advance is largest for Mercury (43, 8.6, 3.8 and 1.35 arcsec per century). At 7300 days the errors are Mercury $2.453''$, Venus $3.457''$, Earth–Moon $1.447''$, Mars $0.680''$: the prediction is **rejected**. Mercury's error is not monotonic ($0.125,\,3.784,\,8.149,\,2.453$ arcseconds at the four epochs): it is the largest of all eight planets at 1800 and 3650 days and falls by 7300 days. The heliocentric angular separation of an eccentric orbit with a drifting perihelion oscillates and is not a monotonic measure of an unmodelled term. The registered statement named no epoch and was not retuned. Venus's error grows steadily, about $0.17''$ per year, of the order of the neglected relativistic advance (about $1.7''$ in twenty years) and of other unmodelled terms; the attribution is not isolated here (residual R36.2).

## 36.4 Conservation and the omitted bodies

The kernel conserves the weighted momentum $\sum\varpi_i\vec v_i$ exactly by pair antisymmetry (Chapter 15). **Executed (T3).** At J2000 the weighted momentum of the nine bodies is not zero: it is $8.6\times10^{-8}$ of $\varpi_{\rm tot}v_{\max}$ (the registration had assumed zero and was corrected). The ephemeris barycentre is the barycentre of all bodies, including the asteroids, Pluto and the satellites that this model omits, so the nine-body weighted barycentre lies $2.3\times10^{-6}$ AU from the ephemeris origin and moves at $\vec P_0/\varpi_{\rm tot}$. Over 20 years the largest change of the weighted momentum was $4.7\times10^{-18}$ of $\varpi_{\rm tot}v_{\max}$ (the integrator preserves the pairing to round-off), and the drift of the weighted barycentre, $1.412709\times10^{-5}$ AU, equals $P_0t/\varpi_{\rm tot}$ to six digits. The drift is the motion of the centre of the *omitted* mass distribution; it is not a defect of the integrator.

## 36.5 Dependence on inputs

**Executed (T4, reported).** Changes of the heliocentric angular position after twenty years, in arcsec:

| change | Mercury | Jupiter | Saturn | Neptune |
|---|---|---|---|---|
| $\varpi_{\rm Jupiter}\times1.0002$ (the satellites' share) | 0.0042 | 0.9544 | 1.3203 | 0.0576 |
| Neptune's source removed | 0.0171 | 2.2892 | 6.1870 | 1.5334 |
| Mercury's initial position $+1$ km radially | 2.5949 | 0.0000 | 0.0000 | 0.0000 |

Table 36.2. Sensitivity of the twenty-year positions to three input changes, executed (T4).

An error of 1 km in an initial position (0.004 arcsec at Mercury's distance at the start) grows to $2.6''$ in twenty years through the change of the mean motion, a growth by a factor of about 700. The satellites' share of Jupiter's source (a $2\times10^{-4}$ change) moves Jupiter and Saturn by $1.0''$ and $1.3''$, of the size of the residuals of those planets in Table 36.1; the residuals of the giants are therefore within the uncertainty of this input of the model. Removing Neptune's source moves Saturn by $6.2''$, more than any of the residuals: the outer planets are sensitive to the source ledger at the arcsecond level over twenty years. A precision claim has to name the dataset, the interval and the fitted initial conditions; it has to name the source ledger as well.

## 36.6 Baryon-input dependence and what remains

The source strengths here are ephemeris constants. The baryon ledger of the engine (Chapter 18, $\varpi_b$ per baryon, and the conversion of a measured resistance density to a baryon count in `materials.hpp`) is an explicit approximation when binding defects and composition are neglected. A test of the native ledger would replace each $GM_i$ by a baryon count from an independent measurement and compare; that was not done. The existing registered comparison in the engine's records (nine bodies, twenty steps of twelve hours, spherical-equivalence of two contracts, a maximum position difference of about $1.1\times10^{-2}$ m) establishes the correspondence of two implementations over that interval and preserves a failed residual-relative impulse clause; it is cited from the source register and was not re-run. It is not a long-baseline ephemeris comparison.

## 36.7 Input ledger and residuals

| quantity | value | label |
|---|---|---|
| state vectors at J2000 and the comparison positions | JPL Horizons (DE441) | OBSERVED (processed ephemeris) |
| $GM_i$ of the Sun and planets | read from Horizons object data | MEASURED-INPUT (ephemeris constants) |
| $c$, AU | exact conversions | MEASURED-INPUT (unit bridge) |
| kernel and integrator | Chapter 15 | the engine's |
| Table 36.1, Table 36.2 | executed | COMPUTED |

**Residuals.**

* **R36.1 — what the test establishes.** The kernel and the integrator reproduce DE441 positions to a few arcseconds in twenty years when given ephemeris inputs; the inputs were not predicted.
* **R36.2 — the residuals.** The residuals are not attributed: relativistic terms, asteroids, Pluto, the Sun's quadrupole, the Moon's orbit and the satellites of the giants are all omitted; Venus's steady growth and Mercury's oscillation are not decomposed.
* **R36.3 — the registered ordering.** The ordering by relativistic term size was rejected at 7300 days; the registration named no epoch.
* **R36.4 — a native ledger.** A baryon-ledger source strength for each body, with its approximations, has not been compared.
* **R36.5 — longer baselines and native response.** Intervals beyond twenty years, the retardation and occlusion of Chapter 35, and the movement-budget response (Chapter 13) are not exercised.

## 36.8 Implementation and verification

```
python Textbook\tools\fetch_horizons.py
powershell -File Textbook\tools\tb_run.ps1 -Stem ch36_solar_system_tests
```

Criteria were registered in `Textbook/validation/ch36_PRE_REGISTRATION.md` before the instrument existed and before any trajectory was compared. Run 1 (`ch36_run1_output.txt`) met the window, the step convergence and the instrument checks and failed three clauses: the ordering by relativistic term size (a finding, kept as rejected), and two conservation clauses that assumed a zero initial momentum (a registration error, corrected). Run 2 (`ch36_run2_output.txt`) is the run of record and met every criterion as recorded, including the rejection.

## 36.9 Exercises and answers

**Exercise 1.** Convert $GM_\odot=132712440041.94$ km$^3$/s$^2$ to the source length.

*Answer.* $\varpi_\odot=GM/c^2=1.3271244\times10^{20}\,\mathrm{m^3/s^2}/(2.99792458\times10^8)^2\,\mathrm{m^2/s^2}=1476.625$ m.

**Exercise 2.** How large is 1 km at Mercury's distance (0.387 AU) in arcseconds?

*Answer.* $10^3/(0.387\times1.496\times10^{11})=1.73\times10^{-8}$ rad, $0.0036''$.

**Exercise 3.** Why is the weighted momentum conserved but non-zero?

*Answer.* The kernel conserves $\sum\varpi_i\vec v_i$ by pair antisymmetry, but the nine bodies omit mass that the ephemeris barycentre includes, so its initial value is not zero.

**Exercise 4.** Why does a 1 km radial error grow to arcseconds?

*Answer.* It changes the semi-major axis and so the mean motion, producing a phase error that grows linearly with time.

**Exercise 5.** Which of Table 36.2's changes is comparable to the residuals of Jupiter and Saturn?

*Answer.* The satellite share of Jupiter's source: $1.0''$ and $1.3''$ against residuals $1.2''$ and $1.5''$.

**Exercise 6.** Why does a smaller heliocentric angular error at 20 years than at 10 years for Mercury not indicate improvement?

*Answer.* The angular separation oscillates as the error vector rotates with the orbit and the perihelion; it is not monotonic.

## 36.10 Scope

Established: that the engine's kernel and integrator, given the ephemeris state vectors and source strengths, reproduce the planetary positions of DE441 over twenty years within $8.2''$ and $2.5\times10^{-6}$ in distance without general-relativistic terms; the step convergence; the conservation properties of the nine-body model and the origin of its barycentre drift; and the sensitivity of the positions to the inputs.

Not established: any prediction of the initial conditions or the source strengths (R36.1), the attribution of the residuals (R36.2), a comparison with a native baryon ledger (R36.4) and longer baselines or native corrections (R36.5).

*Where it leads.* Chapter 37 turns from the planets to the star: pressure balance, composition, transport, reaction rates and stability.
