# PPT20 and CR17 independent consistency check

Registered 2026-10-28 before instrument execution. Canonical and historical sources remain unchanged.

Purpose: explain the different outputs through their declared equations. No theory-wide rejection or claim of constitutive closure follows from this check.

## Inputs and scope

Read in full: PPT20 prompt, run log, calculate_closure.py, exact_algebra.py, oscillator_transport.py, resistance_transport.py, endpoint_checks.py; complete adjacent CR17 source and result set. PPT20 historical output is comparison evidence, not a fresh execution.

Use the CR17 literals for an arithmetic replay, explicitly preserving the historical calibration. No new physical fit. A JavaScript RK4 implementation independently evaluates the registered PPT20 variable-resistance witness, without modifying or executing the original Python tool.

## Controls before object calculation

1. RK4 constant-frequency displacement and velocity against cosine/sine, absolute error below 1e-7.
2. Integrated energy exchange against endpoint energy, residual relative to initial energy below 1e-5.
3. Step refinement dt=0.03 to 0.015: action ratio relative difference below 1e-5.
4. Decrease imposed rate from 0.004 to 0.002: finite-rate action residual decreases for each xi branch.
5. Independently bracket and bisect the fixed-reference sound/EM crossing; substitution relative residual below 1e-10.

## Calculations and determining equations

- B=q^-2, K=1, q=0.5 exp(epsilon t), B x'' + xi B' x' + K x=0, xi in {0,1}. Initial velocity (xi-1/2) epsilon. Integrate work E'=(1/2-xi)B'x'^2. Compare action J=E/omega, omega=q, with adiabatic ratio (B_final/B_initial)^(1-xi).
- Explain energy and momentum separately: p=B x', p'=-Kx+(1-xi)B'x'. Medium exchange must balance the second term; no microscopic contact law is supplied by choosing xi.
- Reproduce R0=(3/4)rho_b0/rho_gamma0 using CR17's stated constants. Evaluate c_EM=c0/N and the historical sound expression c_s=c0/sqrt(3(1+R0/N)). Compare with the alternative same-state-speed expression c_s=c_EM/sqrt(3(1+R0/N)). The second expression is a conditional interpretation, not an authorized replacement.
- Under the first expression, crossing solves N^3-3N-3R0=0. Under the second expression, c_s/c_EM<1 for all positive loading. A physical selection requires a common operational clock and the medium's acoustic constitutive response.
- c0/N is strictly positive for finite positive N; the branch has no finite-temperature halt unless another mechanism terminates the branch.
- Compare historical fixed-coefficient thermal powers with PPT20's S10 completion using exponents only. With c~q, hbar~q^-2, kB fixed, T~q^-1, the comparison formula a_rad~kB^4/(hbar^3 c^3) gives a_rad~q^3, u~q^-1; the Wien coefficient b~h c/kB gives b~q^-1 and intrinsic peak wavelength~q^0. These follow conditionally from the comparison completion. Received wavelengths and present-instrument temperature labels require the specified transfer map.

## Reporting

Save source hashes, controls, numerical results and limitations. Preserve failed controls without changing tolerances. No cosmic chronology, independent BAO measurement, native action law or luminosity derivation is inferred.
