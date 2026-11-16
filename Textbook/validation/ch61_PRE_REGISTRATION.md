# Chapter 61 — pre-registration of the worked-example instrument

Registered 2026-11-10, before `Textbook/examples/ch61_experimental_instruments.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents). All apparatus numbers are constructed (no measured input and no engine function). The instrument reads two directory names of the repository as text (existence only).

Object. What an apparatus specification has to carry before a prediction is made. (a) Torsion response: $I\ddot\theta+\gamma\dot\theta+\kappa\theta=\tau(t)$; the relation $\kappa\theta=\tau$ holds in the calibrated quasistatic limit only; for $\tau=\tau_0\sin\omega t$ the steady amplitude is $\tau_0/\kappa\cdot[(1-r^2)^2+(r/Q)^2]^{-1/2}$ with $r=\omega/\omega_0$, $Q=I\omega_0/\gamma$, and the lag $\varphi=\mathrm{atan2}(r/Q,1-r^2)$; with $Q=50$ the quasistatic relation is wrong by $+1.0$ per cent at $r=0.1$ and the amplitude is $Q\tau_0/\kappa$ at resonance with a lag of $\pi/2$. (b) Controls select mechanisms: for a rotating source geometry a predicted even harmonic $\cos2\varphi$ is projected onto over an integer number of turns; a linear drift $dt$ projects to zero on $\cos2\varphi$ and leaks into the $\sin2\varphi$ coefficient as $-d/\Omega$; reversing the rotation direction flips the sign of that leak, so half the sum of the two runs isolates the geometric signal and half the difference isolates the drift. (c) Blank runs quantify the apparatus response: with white noise $\sigma_n$ per sample over $M$ samples the least-squares standard error of a harmonic amplitude is $\sigma_n\sqrt{2/M}$. (d) Data and comparison: raw data, calibration and geometry are stored with hashes (any one-byte change changes the digest); a fit with declared nuisance parameters preserves the covariance: the coefficient of $\cos2\varphi$ is uncorrelated with a linear drift over an integer number of turns and the coefficient of $\sin2\varphi$ is strongly correlated with it. (e) The repository's GOM13 (occlusion, altitude, Cavendish) and FLM15 (relay-exclusion) investigations are distinct folders; a torsional angular test is retrieved from its own folder.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | SHA-256("abc") $=$ `ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad`; the least-squares solver recovers $(c_0,c_1)=(2,-3)$ exactly from $y=2-3x$ at 5 points; the RK4 integrator on $\ddot\theta=-\theta$ from $(1,0)$ at $t=2\pi$ returns $\theta=1$ | exact; $10^{-12}$; $10^{-10}$ |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | torsion. $I=\kappa=1$, $\gamma=0.02$ ($Q=50$), RK4 ($dt=0.01$, 3000 time units), steady amplitude and lag extracted by projection over 10 periods, for $r=0.01,0.03,0.1,0.5,0.9,1,2$: equal to the closed forms to $10^{-5}$ relative (amplitude) and $10^{-5}$ rad (lag); the quasistatic error $(A\kappa/\tau_0-1)$ at $r=0.1$ lies in $[0.0095,0.0107]$ and at $r=0.03$ below $10^{-3}$; the resonance amplitude is $50\pm0.5$ with lag $\pi/2$ to $10^{-4}$ | as stated | yes |
| T2 | harmonic controls. Signal $s(\varphi)=0.7\cos2\varphi+0.3\sin2\varphi+0.05\,t\ (\Omega=1)$ over $N=4$ integer turns: the projection on $\cos2\varphi$ is $0.7$ ($10^{-9}$), on $\sin2\varphi$ is $0.3-0.05=0.25$ ($10^{-9}$); the reversed run gives $0.3+0.05=0.35$; half the sum recovers 0.3 and half the difference the drift 0.05 ($10^{-9}$); over 3.5 turns the $\cos2\varphi$ projection of the drift is not zero (nonzero by more than $10^{-3}$) | as stated | yes |
| T3 | blank runs. $M=3600$ samples of white noise $\sigma_n=1$ over 4 turns, 4000 blank runs: the standard deviation of the fitted $\cos2\varphi$ amplitude is within 5 per cent of $\sqrt{2/M}=0.02357$; the estimated amplitude of a run with a registered signal of $0.1$ is within $5\sigma$ of $0.1$ in at least $99$ per cent of 4000 runs, and the blank mean is within $3\sigma/\sqrt{4000}$ of 0 | as stated | yes |
| T4 | data and covariance. SHA-256 of a raw-data blob changes when one byte changes and is unchanged otherwise; for the design matrix with columns $\cos2\varphi,\sin2\varphi,1,t$ over 4 integer turns (3600 points): $\rho(\cos2\varphi,t)=0$ ($10^{-9}$), $|\rho(\sin2\varphi,t)|\in(0.3,1)$ (reported), and the analytic standard error of the $\cos2\varphi$ coefficient $\sigma\sqrt{2/M}$ equals $\sigma\sqrt{[(X^TX)^{-1}]_{00}}$ to $10^{-6}$ | as stated | yes |
| T5 | the repository. The directories `GOM13_Occlusion_Altitude_Cavendish` and `FLM15_Casimir_as_Relay_Exclusion` both exist (under `Projects/sdt-investigations/Investigations/`) and are different directories; `gom13_preflight.cpp` is in the first | as stated | yes |

Reported, not criteria: the amplitudes, lags, projections, standard deviations, correlations.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch61_experimental_instruments`

## Record of run 1; two instrument defects, one registration error and one registered statement rejected (2026-11-10)

Run 1 (`ch61_run1_output.txt`): V1, the T1 resonance-amplitude and quasistatic-range criteria, the forward projections and the half-sum/difference arithmetic inputs of T2, all of T3, the hash and covariance-factor criteria of T4, and all of T5 were met. Fourteen criteria failed, from four causes.

(1) **T1, an instrument defect (nine criteria).** The steady amplitude and lag were extracted over a window `nper = 10 period/dt` truncated to an integer number of steps, so the window was not an exact multiple of the drive period (the leftover fraction is up to $dt/T_{\rm window}$, which is $3\times10^{-4}$ at $r=2$). The errors of $10^{-5}$ to $10^{-4}$ against the registered $10^{-5}$ followed that pattern (smallest at $r=0.01$, largest at $r=2$). The criteria are unchanged; the step is chosen as $dt=\text{period}/\lceil\text{period}/0.01\rceil$ so that every period has an integer number of steps and the window is exactly 10 periods.

(2) **T2, the reversed run: an instrument defect (four criteria).** The instrument projected the reversed-run signal onto $\sin2\varphi(t)$ with $\varphi=-t$, which is already the projection in apparatus angle ($0.350000$, as registered); it then flipped the sign a second time, and a leftover first check carried a wrong expectation ($-0.35$). The half-sum and half-difference built on the doubly flipped value were therefore wrong. The registered values ($0.35$; half sum $0.3$; half difference $0.05$) are unchanged and are tested on the single, correct projection.

(3) **T2, 3.5 turns: a registered statement rejected (one criterion).** The registered statement that the drift projects onto $\cos2\varphi$ by more than $10^{-3}$ over 3.5 turns is **rejected**: the value is $-1.2\times10^{-16}$. $\cos2\varphi$ has period $\pi$, so 3.5 turns ($7\pi$) is an integer number of its periods and the projection is exactly zero: a registration error in the choice of the partial-turn length (the correct statement needs a length that is not a multiple of $\pi$). The statement is kept and asserted in run 2; a post-run clause, marked as such, tests 3.3 turns, where the analytic value is $(d/2T)(\cos2T-1)=-2.2\times10^{-3}$ with $T=6.6\pi$.

(4) **T4, a registered statement rejected (one criterion).** The registered range $|\rho(\sin2\varphi,t)|\in(0.3,1)$ is **rejected**: $\rho=0.0975$. The correlation is nonzero but modest. The statement is kept and asserted in run 2; a post-run clause, marked as such, requires $0.05<|\rho|<0.2$ (the cross term is not zero, and its size is a property of the design: four turns of 3600 points).

Run 2 is a further run, not the run of record (see below).

## Record of run 2; one error in a post-run clause (2026-11-10)

Run 2 (`ch61_run2_output.txt`): T1 met every criterion (worst amplitude error $8.1\times10^{-10}$, worst lag error $7.8\times10^{-9}$ rad); the reversed run gave $0.350000$, half the sum $0.3$ and half the difference $0.050000$; the rejections of the 3.5-turn statement and of $|\rho(\sin2\varphi,t)|>0.3$ were asserted and the T4 post-run clause met ($\rho=0.0975$). One criterion failed: the post-run clause for 3.3 turns, where the instrument returned $-3.157\times10^{-2}$ against my stated analytic value $-2.2\times10^{-3}$. The analytic expression written in run 1's record, $(d/2T)(\cos2T-1)$, omitted the term $T\sin2T/2$ of $\int_0^Tt\cos2t\,dt$; the correct closed form is $(2d/T)[T\sin2T/2+(\cos2T-1)/4]$, which for $T=6.6\pi$ equals $-3.155\times10^{-2}$, in agreement with the instrument. The error is in the post-run clause as I wrote it (an analytic slip), not in the instrument and not in the object. The clause is corrected to the closed form with the same 2 per cent agreement criterion. Run 3 is the run of record.
