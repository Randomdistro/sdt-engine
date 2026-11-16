# Chapter 61 — Experimental Instruments

*Volume VIII — Executable Reference, Verification and Research Closure.*
Draft of 10 November 2026. Notation: $I$, $\gamma$, $\kappa$ the inertia, damping and torsion constant of a torsion balance; $\omega_0=\sqrt{\kappa/I}$, $r=\omega/\omega_0$, $Q=I\omega_0/\gamma$; $\varphi$ the apparatus angle (rotation of the source geometry), $\Omega$ its rate; $A,B$ the coefficients of $\cos2\varphi$ and $\sin2\varphi$; $d$ a linear drift rate; $M$ the number of samples; $\sigma_n$ white-noise amplitude. Executable companion: `Textbook/examples/ch61_experimental_instruments.cpp`; pre-registration and captured output in `Textbook/validation/`. All apparatus numbers are constructed (no measured input, no engine function). The instrument reads two directory names of the repository as text. No new apparatus outcome is claimed.

## 61.1 Retrieve the apparatus before predicting

An experiment is specified by geometry, materials, boundary exposure, sensor response and controls. The repository's GOM13 occlusion, altitude and Cavendish work and its FLM15 relay-exclusion work are distinct investigations: a torsional angular test must not be replaced by an invented altitude or material narrative because a directory name contains those words. **Executed (T5).** `GOM13_Occlusion_Altitude_Cavendish` (under `06_Gravitation_and_Orbital_Mechanics`; it holds `PROMPT.md`, three HTML decks, `gom13_preflight.cpp` and a rerun record) and `FLM15_Casimir_as_Relay_Exclusion` (under `01_Foundations_and_Lattice_Mechanics`) both exist and are different directories; `gom13_preflight.cpp` is in the first. The apparatus of a prediction is taken from its own folder.

For a declared angular apparatus the actual directional occlusion integral and the sensor torque are computed. A torsion response $\kappa\theta=\tau$ applies only in the calibrated quasistatic limit; a dynamical readout needs inertia, damping, forcing frequency and transfer phase, and the calibration must be determined independently.

**Executed (V1, T1).** The torsion pendulum $I\ddot\theta+\gamma\dot\theta+\kappa\theta=\tau_0\sin\omega t$ with $I=\kappa=1$ and $Q=50$ was integrated (RK4, an integer number of steps per drive period, a window of exactly 10 periods) and the steady amplitude and lag extracted by projection. The amplitude $\kappa A/\tau_0=[(1-r^2)^2+(r/Q)^2]^{-1/2}$ and the lag $\mathrm{atan2}(r/Q,1-r^2)$ agree with the numerical values to $8.1\times10^{-10}$ (amplitude, relative) and $7.8\times10^{-9}$ rad (lag):

| $r=\omega/\omega_0$ | $\kappa A/\tau_0$ | lag (rad) |
|---|---|---|
| $0.01$ | $1.000100$ | $2.0002\times10^{-4}$ |
| $0.03$ | $1.000901$ | $6.0054\times10^{-4}$ |
| $0.1$ | $1.010099$ | $2.0202\times10^{-3}$ |
| $0.5$ | $1.333215$ | $0.013333$ |
| $0.9$ | $5.239697$ | $0.094455$ |
| $1$ | $50.0000$ | $1.570796$ ($=\pi/2$) |
| $2$ | $0.333304$ | $3.128260$ |

The quasistatic relation is wrong by $+1.0$ per cent at $r=0.1$ and by $9\times10^{-4}$ at $r=0.03$ (registered: below $10^{-3}$), and at resonance the response is $Q=50$ times the static one with a lag of $\pi/2$. A torque measured with a quasistatic calibration at a drive frequency of a tenth of the resonance is mis-scaled by one per cent; one near resonance is mis-scaled by a factor of order $Q$. The extraction was repaired once (the first window was not an integer number of periods; recorded in the pre-registration).

## 61.2 Controls select mechanisms

Rotate the source geometry while preserving thermal and mechanical load where possible. Reverse orientation, exchange materials, monitor temperature and vibration, and record environmental gradients. The control design follows the predicted angular symmetry. A model that predicts an even harmonic cannot claim an arbitrary odd drift as supporting evidence.

**Executed (T2).** Signal $s=0.7\cos2\varphi+0.3\sin2\varphi+0.05\,t$ with $\Omega=1$ over four turns (3600 samples). A linear drift projects to zero on $\cos2\varphi$ over an integer number of turns (the coefficient is $0.700000$) and leaks into the $\sin2\varphi$ coefficient as $-d/\Omega$: the forward projection is $0.249999594$, not $0.3$. Reversing the rotation flips the sign of the leak in apparatus angle: the reversed run gives $0.350000406$. Half the sum, $0.300000000$, isolates the geometric signal, and half the difference, $0.05000041$, the drift (sampling accounts for the $4\times10^{-7}$ departures from $0.25$ and $0.35$). A drift therefore mimics a quadrature component of an even harmonic, and only the counter-rotated run separates them. Over a partial turn the leak also reaches the $\cos2\varphi$ coefficient: 3.5 turns is an integer number of periods of $\cos2\varphi$ ($7\pi$), so the projection there is $-1.2\times10^{-16}$ (the registered statement that it would exceed $10^{-3}$ was **rejected**; recorded); at 3.3 turns it is $-3.157065\times10^{-2}$ against the closed form $(2d/T)[T\sin2T/2+(\cos2T-1)/4]=-3.157043\times10^{-2}$ (post-run clause; the first analytic expression omitted a term, recorded). Integer turns are part of the design.

**Blank runs (T3).** Blank, null-orientation and dummy-load runs quantify the apparatus response. Their purpose is to identify the cause of a result, not to assume the proposed mechanism absent or present. With white noise ($\sigma_n=1$, $M=3600$ samples over four turns) the fitted $\cos2\varphi$ amplitude of 4000 blank runs has a standard deviation of $0.02379$ against $\sqrt{2/M}=0.02357$ ($+0.9$ per cent) and a mean of $-4.8\times10^{-4}$ (consistent with 0); 4000 of 4000 runs carrying a registered amplitude of $0.1$ lie within $5\sigma$ of it. The amplitude and phase to be sought are registered before the comparison interval is opened.

## 61.3 Data and comparison

Store the raw sensor readings, calibration, geometry, environmental traces and time alignment with hashes. Fit only declared nuisance parameters and keep the uncertainty covariance. A source-rendered animation is not a measurement of the apparatus.

**Executed (T4).** The SHA-256 of a 10 000-byte data blob is unchanged on re-hashing and changes when one byte is flipped. For the design matrix with columns $\cos2\varphi,\sin2\varphi,1,t$ over four integer turns (3600 points): the $\cos2\varphi$ coefficient is uncorrelated with the drift ($\rho=-2.9\times10^{-17}$), the $\sin2\varphi$ coefficient is correlated with it ($\rho=0.0975$; the registered range $(0.3,1)$ was **rejected**, a post-run clause confirms $0.05<|\rho|<0.2$), and $[(X^TX)^{-1}]_{00}=5.555556\times10^{-4}=2/M$ so the standard error of the $\cos2\varphi$ coefficient is $\sigma_n\sqrt{2/M}=0.02357\,\sigma_n$. A fit that drops the covariance overstates the independence of the coefficients.

## 61.4 Input ledger and residuals

| quantity | value | label |
|---|---|---|
| $I,\gamma,\kappa$, $Q=50$, noise, rates, turns | Sections 61.1–61.3 | CONSTRUCTION (no measured input) |
| amplitudes, lags, projections, covariances, hashes | Sections 61.1–61.3 | COMPUTED |
| folder names | repository | read as text (existence) |

**Residuals.**

* **R61.1 — the registered apparatus.** No registered apparatus with a native predicted signal from the same geometry exists in this chapter; the GOM13 occlusion integral and torque were not computed.
* **R61.2 — the sensor.** The torsion model is a single linear oscillator; nonlinearity, thermal gradients, vibration and drift sources were not modelled.
* **R61.3 — the signal.** No even-harmonic amplitude predicted by the framework was used; the harmonic amplitudes are constructed.
* **R61.4 — the noise.** White noise only; coloured noise and correlated systematics change the standard errors.
* **R61.5 — publication specification.** A specification needs the registered apparatus; none is claimed.

## 61.5 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch61_experimental_instruments
```

Criteria were registered in `Textbook/validation/ch61_PRE_REGISTRATION.md` before the instrument existed. Run 1 (`ch61_run1_output.txt`) failed 14 criteria (an extraction window that was not an integer number of periods, a doubled sign flip, one registration error and one registered range that was rejected); run 2 repaired the instrument and left one error in a post-run clause (an analytic slip), all recorded. Run 3 (`ch61_run3_output.txt`) is the run of record and met every criterion, with the two rejections asserted and the post-run clauses marked.

## 61.6 Exercises and answers

**Exercise 1.** What is the error of the quasistatic relation at $r=0.2$ for $Q=50$?

*Answer.* $[(1-0.04)^2+(0.004)^2]^{-1/2}-1=0.0417$, about $4.2$ per cent.

**Exercise 2.** Why does a linear drift not affect the $\cos2\varphi$ projection over integer turns?

*Answer.* $\int_0^{2\pi N}t\cos2t\,dt=[t\sin2t/2+\cos2t/4]=0$ at $t=0$ and $t=2\pi N$.

**Exercise 3.** What does a counter-rotated run do to the drift leak?

*Answer.* In apparatus angle, the drift appears with $-d/\Omega$ in the forward run and $+d/\Omega$ in the reversed run, while the geometric signal does not change, so half the sum isolates the signal.

**Exercise 4.** What is the standard error of a harmonic amplitude with $M=10^4$ samples and $\sigma_n=0.5$?

*Answer.* $\sigma_n\sqrt{2/M}=0.5\times0.01414=7.1\times10^{-3}$.

**Exercise 5.** Why are blank runs run in the same configuration?

*Answer.* They measure the apparatus response (noise, drift, nuisance harmonics) under the conditions of the signal run, so a detected amplitude can be compared with it.

**Exercise 6.** What does a nonzero $\rho(\sin2\varphi,t)$ imply for the fit?

*Answer.* The estimates of the $\sin2\varphi$ coefficient and the drift are correlated; the fit must carry the covariance and the nuisance parameter must be declared.

## 61.7 Scope

Established: the dynamic response of a single torsion oscillator against its quasistatic calibration; the separation of a geometric even harmonic from a linear drift by integer turns and by a counter-rotated run; the blank-run standard error; the covariance structure of the fit; that the two apparatus folders are distinct.

Not established: a registered apparatus and its native predicted signal (R61.1), a realistic sensor model (R61.2), the framework's harmonic amplitude (R61.3), coloured noise (R61.4) and a publication specification (R61.5).

*Where it leads.* Chapter 62 sets out the parameter and uncertainty ledger: the roles of numbers, covariance propagation and calibration against prediction.
