# Chapter 36 — pre-registration of the worked-example instrument

Registered 2026-11-10, before `Textbook/examples/ch36_solar_system_tests.cpp` was written or run, and before any engine trajectory was compared with the ephemeris. The ephemeris files were fetched first (`Textbook/tools/fetch_horizons.py`; JPL Horizons API, DE441, barycentric, ICRF-aligned ecliptic of J2000, TDB, 731 rows per body at 10-day steps from JD 2451545.0 to JD 2458849.0) and only their first Earth rows were looked at. The ephemeris is OBSERVED-processed data: a fit of DE441 to ranging, VLBI and optical observations. No number below is entered from memory; the gravitational parameters $GM$ are read from the Horizons object data (`Textbook/data/horizons/gm.csv`).
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object. The engine's source-length kernel $\vec a_i=c^2\sum_j\varpi_j(\vec r_j-\vec r_i)/\lvert\vec r_j-\vec r_i\rvert^3$ (Chapter 15) with `dynamics::step_rk4`, applied to the Sun and the eight planetary systems (barycentres 1–8, the Earth–Moon barycentre as one body, source length $\varpi_i=GM_i/c^2$ from the ephemeris constants; the Moon's and the giant planets' satellites' masses enter only through the Earth–Moon sum; outer-planet satellite masses are omitted, of order $2\times10^{-4}$ of each giant). Initial conditions: the ephemeris state vectors at JD 2451545.0 TDB (J2000.0), barycentric. The comparison observables are fixed before execution: for each planetary system, (a) the **heliocentric angular separation** between the engine position and the ephemeris position (arcsec) and (b) the **relative error of the heliocentric distance**, at the grid epochs $t=360,\,1800,\,3650,\,7300$ days after J2000 (rows 36, 180, 365, 730). Unmodelled effects: general-relativistic terms, the asteroids and Pluto, the Sun's quadrupole, the Moon's separate orbit and the satellite masses of the giants. No retardation, no occlusion and no movement-budget response of Chapter 35 is used; the instrument tests the kernel, the integrator and the inputs, not a native correction.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | data integrity: the parsed Earth vector at JD 2451545.0 equals the first printed row ($X=-1.771350992727098\times10^{-1}$ AU, $Y=9.672416867665306\times10^{-1}$ AU); every body's file has 731 rows with JD spacing 10 d; Sun GM $=132712440041.93938$ km$^3$/s$^2$ | $10^{-14}$ relative |
| V2 | two-body check with the same code path: Sun plus Earth-sized test body on the ephemeris-scale circular orbit ($a=1$ AU, $\varpi_\odot=GM_\odot/c^2$, `circular_pair`) returns to its start after one period to $10^{-9}$ of $a$ with the step used below | $10^{-9}$ |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | step convergence. For Mercury at $t=1800$ d: the heliocentric angular position from steps of $0.125$ d and $0.0625$ d differ by at most $0.1''$ | $\le0.1''$ | yes — a larger difference rejects the step size as a basis for the comparisons below |
| T2 | comparison. With $0.125$ d steps: for all eight systems at all four epochs the heliocentric angular separation is at most $60''$ and the relative distance error is at most $10^{-5}$. Registered ordering (prediction from the size of unmodelled general-relativistic terms, 43, 8.6, 3.8, 1.35 arcsec per century for Mercury, Venus, Earth, Mars): at $t=7300$ d the Mercury error exceeds the errors of Venus, the Earth–Moon barycentre and Mars. All values are printed | as stated | yes — an error above the window, or Mercury not the largest of the inner four, rejects the stated attribution of the residuals |
| T3 | conservation. The weighted barycentre $\sum\varpi_i\vec r_i/\sum\varpi_i$ at J2000 lies within $10^{-6}$ of the Sun's radius of the ephemeris barycentre origin (printed in AU), and its drift over 20 years is below $10^{-8}$ AU; the weighted momentum $\sum\varpi_i\vec v_i$ relative to $\varpi_{\rm tot}v_{\max}$ stays at or below $10^{-12}$ at 20 years | as stated | yes |
| T4 | input dependence (reported, not criteria): changes of the 20-year heliocentric angular errors of Jupiter, Saturn and Mercury under (a) $\varpi_{\rm Jupiter}\times1.0002$ (the satellites' share), (b) removing Neptune's source, (c) displacing Mercury's initial position by 1 km radially | reported | — |

Reported, not criteria: all errors, the T4 table.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch36_solar_system_tests`

## Record of run 1 (2026-11-10)

Run 1 (`ch36_run1_output.txt`) met V1, V2 (two-body return $3.0\times10^{-12}$ of $a$), T1 (step difference $0.0203''$) and the window clause of T2 (all eight systems at all four epochs within $60''$ and $10^{-5}$ relative distance: the largest angular error is $8.15''$ (Mercury, 3650 d) and the largest distance error $2.5\times10^{-6}$ (Mercury, 1800 d)). It failed three clauses.

1. **T2 ordering: rejected, kept.** The registered prediction that Mercury's 20-year error exceeds those of Venus, the Earth–Moon barycentre and Mars is **rejected**: at 7300 d the errors are Mercury $2.453''$, Venus $3.457''$, EMB $1.447''$, Mars $0.680''$. Mercury's error is not monotonic in time ($0.125'',\,3.784'',\,8.149'',\,2.453''$ at 360, 1800, 3650, 7300 d); it is the largest of all eight planets at 1800 and 3650 d and not at 7300 d. The registered statement did not name an epoch and is not retuned after the run; the result is recorded as a finding (the heliocentric angular separation of an eccentric orbit with a precessing perihelion oscillates; it is not a monotonic measure of unmodelled terms). Run 2 keeps the criterion and reports its rejection.
2. **T3, momentum and drift: registration error.** The registered clauses (weighted momentum $\le10^{-12}$ of $\varpi_{\rm tot}v_{\max}$; barycentre drift $\le10^{-8}$ AU) assumed that the weighted momentum of the nine bodies is zero at J2000. It is not: the nine bodies omit the asteroids, Pluto and the satellites, and the ephemeris barycentre is the barycentre of all of them; the weighted momentum at J2000 is $8.6\times10^{-8}$ of $\varpi_{\rm tot}v_{\max}$. The kernel conserves $\sum\varpi_i\vec v_i$ exactly by pair antisymmetry (Chapter 15), so the quantity to test is its *change*, and the barycentre drift must equal $\vec P_0t/\varpi_{\rm tot}$, which for $\vec P_0/\varpi_{\rm tot}=8.6\times10^{-8}v_{\max}$ gives a drift of the observed size, $1.4\times10^{-5}$ AU in 20 years. Repaired clauses: $\lvert\vec P(t)-\vec P(0)\rvert\le10^{-12}\varpi_{\rm tot}v_{\max}$ at all rows, and the drift of the weighted barycentre equals $\vec P_0t/\varpi_{\rm tot}$ to $10^{-9}$ AU.
3. **T3, barycentre offset.** The registered wording ("within $10^{-6}$ of the Sun's radius of the ephemeris barycentre origin") was ambiguous, and the instrument tested the looser limit $10^{-5}$ AU without that being registered. The offset is $2.3\times10^{-6}$ AU ($4.9\times10^{-4}$ of the Sun's radius); it is reported as a result (the weighted barycentre of the nine bodies differs from the ephemeris origin by the mass distribution of the omitted bodies) and no criterion is attached to it.

Run 2 is the run of record.
