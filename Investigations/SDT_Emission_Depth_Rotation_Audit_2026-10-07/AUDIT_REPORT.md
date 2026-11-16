# Emission-depth, relay mechanics and galactic rotation: complete transcript audit

Date: 7 October 2026, Australia/Sydney.

**Result:** the transcript supplies an investigable substrate hypothesis, a valid far-field excluded-volume identity, and several unsupported promotions of identities into physical results. The proposed pressure interpretation of galactic spectra requires separation of spectral midpoint, red/blue splitting, and propagation law. Common emission depth cancels exactly from a paired spectral ratio. A variable-carrier rescue of a Keplerian decline requires an outward-decreasing carrier speed. The transcript specifies the opposite pressure-relief trend.

The full attachment contains 2,280 lines. Historical, mechanical, spectral and cosmological arguments received separate checks. Claims concerning complete particle physics, nuclear stability, n-body integrability and universal paradox elimination lack the corresponding derivations in the attachment; the audit therefore establishes no result for the unsupplied proofs. The spherical baryon remains an explicit surrogate, preserving the operator-defined toroidal geometry.

## 1. Exact spectral separation

Assume paired positions at equal radius, equal source pressure and equal orbital speed, a common spectral transfer factor, and the standard Doppler response with a specified local carrier speed. Let

\[
L_\pm=\lambda_\pm/\lambda_0,
\quad A(r)>0,
\quad b=v/c_D,
\quad B=b\sin i,
\quad \gamma=(1-b^2)^{-1/2}.
\]

The receding and approaching spectral wavelengths satisfy

\[
L_+=A\gamma(1+B),\qquad L_-=A\gamma(1-B).
\]

Here \(A\) includes common source pressure, common propagation transfer, systemic shift and clock calibration. The parameter \(c_D\) denotes the speed entering the Doppler law; identification with relay group speed, phase speed or far-frame coordinate speed requires a separate derivation.

The exact pressure-independent observable is

\[
\boxed{B=\frac{L_+-L_-}{L_++L_-}
=\tanh\!\left[\frac12\ln\frac{L_+}{L_-}\right].}
\]

The midpoint and log-even channel obey

\[
\frac{L_++L_-}{2}=A\gamma,
\qquad \frac12\ln(L_+L_-)=\ln A+\ln\gamma+
\frac12\ln(1-B^2).
\]

At edge-on inclination, the transverse correction disappears from the log-even channel. At general inclination, an independently specified Doppler law and orbital geometry permit the correction. Spectroscopy measures \(v\sin i/c_D\); paired spectra alone cannot separately recover physical velocity and an unconstrained carrier speed.

For unequal pressure transfer on opposite sides,

\[
\frac12\ln\frac{L_+}{L_-}
=\frac12\ln\frac{A_+}{A_-}+\operatorname{atanh}B.
\]

Pressure contamination of rotation therefore requires an azimuthally odd pressure component, differential propagation or an altered Doppler response. A scalar axisymmetric radial depth supplies an even channel. Actual cubes require line blending, beam convolution, inclination, warps, turbulence and noncircular-flow modelling before paired-centroid interpretation.

**Important estimator qualification:** a wavelength difference divided by a fixed laboratory reference rather than a local midpoint obeys

\[
v_{\rm optical,raw}=\frac{c_0(L_+-L_-)}{2\sin i}
=A\gamma\,\frac{c_0v}{c_D}.
\]

A common pressure factor can rescale such an unnormalized estimator. The same factor also shifts the observable midpoint. A source-pressure explanation therefore cannot be rejected solely from a raw velocity table, but cannot remain hidden after even/odd spectral separation. For constant \(c_D\), compensating a factor-two Keplerian speed decline requires an approximately factor-two radial change in \(A\gamma\). Radio-frequency velocity conventions have a different raw normalization; a complete model must reproduce original frequency centroids and optical line centroids before velocity conversion. No raw side-pair reanalysis occurred during the SPARC calculation.

## 2. Carrier-speed inversion and sign constraint

For an inferred ratio-normalized speed \(v_{\rm app}=c_0 B/\sin i\),

\[
\boxed{v_{\rm real}=\frac{c_D}{c_0}v_{\rm app}.}
\]

Given an independently calculated baryonic circular speed \(v_b\), the carrier profile required by the hypothesis is

\[
\boxed{c_{D,\rm required}(r)/c_0=v_b(r)/v_{\rm app}(r).}
\]

For constant enclosed mass, \(v_b\propto r^{-1/2}\). For a flat apparent curve,

\[
\boxed{c_{D,\rm required}\propto r^{-1/2},\qquad
d\ln c_D/d\ln r=-1/2.}
\]

Pressure declining outward and carrier speed increasing outward instead steepen the apparent decline. Radius quadrupling reduces Keplerian speed from 200 to 100 km/s. Carrier speed halving preserves apparent 200 km/s; carrier speed doubling gives apparent 50 km/s. Galaxies with extended disks require the disk gravitational kernel, gas and bulge contributions rather than an unconditional point-mass law.

## 3. Public-data calculation

Public sources: [SPARC project](https://astroweb.case.edu/SPARC/), [Lelli, McGaugh and Schombert 2016](https://arxiv.org/abs/1606.09251). Fresh original data downloads match the published archive checksums. Source hashes appear in `source_manifest.json`.

The fixed comparison model uses 3.6-micron stellar mass-to-light ratios 0.5 for disks and 0.7 for bulges:

\[
v_b^2=V_{\rm gas}|V_{\rm gas}|+
0.5V_{\rm disk}|V_{\rm disk}|+
0.7V_{\rm bul}|V_{\rm bul}|.
\]

Signed gas contributions preserve outward forces from central gas depressions. SPARC gas terms already include the gas-mass convention; no duplicate helium factor enters the calculation.

- 175 galaxies; 3,391 radial records; 3,389 records with positive radius, observed velocity and baryonic squared speed.
- Outer selection: radius at least `max(2 Rdisk, 0.5 rmax)`, at least four valid points, quality flag at most 2 and inclination at least 30 degrees.
- 123 galaxies pass the selection; 100 have negative outer log-slope in the required carrier profile, 23 positive.
- 90 have slope below −0.1; median selected slope −0.22507.

| Galaxy | Final radius, kpc | Published speed, km/s | Conditional baryonic speed, km/s | Required carrier ratio | Outer log-slope |
|---|---:|---:|---:|---:|---:|
| DDO154 | 5.92 | 45.5 | 16.254 | 0.35724 | −0.26546 |
| NGC2403 | 20.87 | 134.0 | 51.442 | 0.38389 | −0.46375 |
| NGC3198 | 44.08 | 149.0 | 64.713 | 0.43432 | −0.22507 |

**Scope:** the ratios are required profiles obtained by inversion, not measured carrier speeds or independent SDT predictions. SPARC tabulates reduced velocities, not original paired line centroids. Distance, inclination, stellar mass, gas conversion and the baryonic force law remain conditional. Selection slopes are descriptive; a complete nuisance-covariance likelihood was not calculated. An unconstrained function fitted at every radius can reproduce any curve and supplies no independent physical evidence.

Executable verification includes 10,000 paired spectra across arbitrary common factors, transverse Doppler terms and inclination. Maximum cancellation error: \(1.87\times10^{-16}\). Exact incompressible-map Jacobian error: \(4.44\times10^{-16}\). The code checks the Keplerian/carrier sign example and canonical reciprocal parameter algebra.

## 4. Native SDT constraints

The current canonical `Engine/include/sdt/laws.hpp` uses

\[
v=(c/k)\sqrt{R/r},\quad z_{\rm depth}=1/k^2,
\quad c_{\rm far}=c_\infty(1-z_{\rm depth})^2,
\quad q_{\rm clock}=1-z_{\rm depth}.
\]

The attachment writes \(v=ck\sqrt{R/r}\). Compatibility requires a reciprocal convention \(\kappa=1/k\); a silent identification changes speed by \(k^2\). At \(k=686.3\), the discrepancy factor is 471,007.69. No canonical formula was edited.

For a 200 km/s depth scale, \(z_{\rm depth}=4.4506\times10^{-7}\) and the native far-speed deficit is approximately \(8.90\times10^{-7}\). Direct identification of the far-speed law with the required Doppler carrier speed cannot yield an order-unity mask in the weak galactic regime. Carrier ratio 0.5 would demand depth \(1-\sqrt{0.5}=0.292893\), corresponding under the same bound-speed relation to approximately \(0.5412c\).

The exact spectral ratio from the native clock law is

\[
1+z_{\rm spec}=\frac{1-z_{\rm depth,obs}}{1-z_{\rm depth,emit}},
\quad z_{\rm spec}=\frac{z_{\rm depth,emit}-z_{\rm depth,obs}}
{1-z_{\rm depth,emit}}.
\]

The header's bare depth difference is a first-order approximation. Depth, Doppler shift and observed wavelength shift require distinct symbols. A scalar source variable cannot determine a full transfer spectrum without an emission law.

## 5. Surviving geometry and missing mechanics

For the stated spherical surrogate, incompressibility gives the exact map \(r^3=a^3+R^3\). The field \(u\simeq R^3/(3r^2)\) is the far-field linearization. The stated one-Planck-diameter threshold remains approximately 3.496 μm for \(R=0.84\) fm. Close-packing changes sphere count, while packing cancels from the shell-thickness threshold.

The exact Jacobian equals unity; density remains constant. The far field has zero divergence outside the cavity and nonzero shear strain proportional to \(r^{-3}\). Excluded volume alone therefore establishes neither a compression-pressure gradient nor gravitational acceleration. A stress-energy functional, boundary preparation, traction law and matter coupling must select the physical response.

For stationary radiation, a forward all-pass phase transfer preserves power spectral density. A persistent force needs nontrivial scattering, interference correlations, mode-density response or stored-medium stress. Losslessness can permit conservative forces, including optical binding and fluctuation forces; pure delay does not derive universal inverse-square attraction. A cooling input delayed by a positive interval produces older, hotter throughput in the delayed direction, so the asserted simple pressure-deficit sign requires additional dynamics.

The current engine's convergence burden is approximately \(2.46\times10^{48}\) Pa; ordinary 2.7255 K CMB radiation pressure is approximately \(1.39\times10^{-14}\) Pa. Multiplication by the relay count supplies the enormous difference. A stored-load ledger must explain accumulation without duplicating pulse energy at each relay. Indestructible constituents alone do not establish zero heating or zero drag. Full derivations and control assumptions appear in `MECHANICS_AUDIT.md`.

## 6. Cosmological and historical correction ledger

| Transcript inference | Corrected calculation or required mechanism |
|---|---|
| \(1+z\) is an octave by addition | \(1+z=\lambda_{\rm obs}/\lambda_{\rm emit}=\nu_{\rm emit}/\nu_{\rm obs}\). An octave requires a factor of two; wavelength redshift equals one at the octave. |
| Shell-area dilution transforms 3000 K Planck radiation into 2.73 K Planck radiation | Area dilution changes amplitude. Frequency remapping plus the correct phase-space occupation law must preserve a new Planck spectrum. |
| Room temperature occurs at standard \(z=999\) | Conventional \(T=T_0(1+z)\) gives 2725.5 K; 293.15 K corresponds to \(z=106.558\). Alternative SDT mapping requires explicit evaluation. |
| Slower local clocks imply more internal assembly cycles | Cycle count is \(N=\int\nu_{\rm local}(P(t))dt\); lower frequency reduces cycles at fixed global duration. A revised duration/pressure history must compensate quantitatively. |
| Emission pressure alone falsifies inflation | A replacement redshift interpretation requires distance, light-curve stretch, angular sizes, surface brightness, CMB spectrum/anisotropy and acoustic-scale predictions. No logical falsification follows from a proposed alternative. |
| Pressure-dependent emission automatically passes supernova dilation | A source-clock law must predict the measured stretch. [DES 1504-supernova analysis](https://arxiv.org/abs/2406.05050) measures exponent \(1.003\pm0.005\) statistical and \(\pm0.010\) systematic. Source dilation remains a candidate mechanism, not an automatic quantitative match. |
| Hard gamma propagation must halt at \(10^{12}\) K | Group speed follows \(\partial\omega/\partial k\). Thermal frequency and carrier arrest require an explicit pressure-dependent dispersion branch, storage law and stability analysis. |
| Hubble would endorse source-pressure masking | Documented cosmological caution coexists with explicit acceptance of ordinary stellar Doppler interpretation. Hubble–Tolman joint paper dates to 1935. Imagined endorsement quotations supply no evidence. |
| Einstein 1911 confirmed varying locally measured vacuum speed | The primary paper distinguishes equal local-clock speed from position-dependent common-time speed. Einstein 1920 discusses physical metric qualities at Leiden, with mechanical particle motion excluded from the stated ether concept. |
| Lorentz/Poincaré phase delay automatically removes heating and bath drag | Poincaré already examined luminous-wave and Lorentz phase-lag mechanisms. Conservation and moving-body stress calculations remain essential. |

Historical primary sources, original passages and bounded comparisons across Abraham, Lorentz, Poincaré, Einstein, Mach, Minkowski, Weyl and Hubble appear in `HISTORY_AUDIT.md`. Historical opinion about an unsupplied later mechanism remains inaccessible; research requirements can be reconstructed from published arguments.

## 7. Decisive next experiment and publication threshold

The constrained mechanism study should freeze one relay/stress/emission model before spectral fitting, calculate \(A(r,\phi)\) and the Doppler response from baryonic inputs, then forward-predict approaching/receding line centroids and line profiles across multiple tracers. THINGS original H I cubes and optical velocity fields supply paired spectral tests. Astrometric proper motions and independent parallaxes supply additional constraints; a distance obtained by fitting the same H I rotation curve cannot count as independent kinematic validation.

A rigorous outcome can take either form: independently predicted pressure/relay response satisfying both spectral channels and astrometry, or a scoped rejection of the selected response law. A freely inverted carrier function alone cannot establish the proposed dark-matter replacement. The present result supports an identifiability audit; no complete physical closure or submission-ready unified-theory paper follows.

Artifacts: `crunch_rotation.py`, `results.json`, `source_manifest.json`, `pointwise_required_carrier_speed.csv`, `galaxy_summary.csv`, `MECHANICS_AUDIT.md`, `HISTORY_AUDIT.md`. Existing canonical files and prior investigations were preserved. Audit input SHA-256: `a1f992869b8eb800d1105da7b5594b29c1aca399e62f67d58bd3b64314f7d009`; canonical header snapshot SHA-256: `da72fc92d764cf4221d39714e952b5f864eabc5a3b6aa3567117afdce2024922`.
