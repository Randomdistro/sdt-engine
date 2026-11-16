# Acoustic response: B15 replay and the derivative required for closure

2026-10-28. Source-based mathematical assessment; complete corpus reading remains unfinished.

## Fresh B15 execution

The unchanged adjacent CR08 C++ source compiles against current engine headers with MSVC C++20, O2, strict floating-point and W4. Second build attempt completes without warnings. First build attempt failed because the generated batch split a compiler command across lines; the first capture remains preserved. No physical result came from that failed build.

Fresh output:

| Quantity | Current-header replay |
|---|---:|
| Equality index | 902.169741336 |
| Equality baryon count density | 1.839702920e8 m^-3 |
| Sound speed | 1.308401554e8 m/s |
| Escape response rate | 1.311573030e-14 s^-1 |
| Physical standing radius | 0.161647 Mpc |
| Present-equivalent candidate scale | 145.833161 Mpc |
| Difference from the stored 147.09 Mpc comparison | 0.8545% |
| Independent radial integration relative residual | 7.813e-11 |
| 20k to 40k radial resolution change | 2.344e-10 |
| Conservative proton opacity | 2.227330 |

The existing B15 gate passes. The historical output was 145.818917 Mpc: the current-header replay shifts by about 9.77e-5 relative. Current koppa uses the measured proton wake R_p/4; the historical capture contains no full numerical header snapshot sufficient to certify the entire difference's provenance. The expected length sensitivity to a changed wake is consistent with the shift, but exact historical attribution requires the original header version. No historical output is overwritten.

The unchanged survey portion still uses memory-transcribed rows. The later prompt references a sourced BOSS table, but the C++ DATA array does not load the replacement. Consequently the printed chi-square is a replay of that old instrument, not a new sourced survey test. The return code depends on B15, not on all printed survey gates.

## Exact cancellation and sensitivity

Let kappa denote the baryon koppa length, n0 the present count density, N the selected equality index, and R the loading. The supplied equations give

    Gamma = c sqrt[(8 pi/3) kappa n0 N^3],
    c_s = c/sqrt[3(1+R)],
    L_present = N c_s/(2 Gamma)
              = 1/[2 sqrt(8 pi (1+R) kappa n0 N)].

The common speed cancels exactly. This cancellation requires the same operational speed factor in both equations. Distinct mode-speed responses introduce their ratio. At fixed R,

    d ln L_present = -(d ln kappa + d ln n0 + d ln N)/2.

More generally, add -d ln(1+R)/2. The cancellation does not remove indirect c dependence in kappa, n0 or N under a coupled Spaz response. A state ledger must propagate all selected responses, rather than alter only the explicit speed.

At fixed reference photon density and radiation resistance density, the supplied eta dependence gives n0 proportional to eta and N proportional to eta. Thus L_present is proportional to eta^-1, with other inputs fixed. The numerical agreement is sensitive to the inferred baryon/photon ratio, not a measurement of c at equality.

## The standing-mode selection remains a physical premise

Integrating a uniform sphere gives koppa_total=(4 pi/3) kappa n r^3. Therefore escape_speed/r=c sqrt[(8 pi/3) kappa n] is independent of trial radius. This establishes the candidate response rate. The further equality

    2 L/c_s = 1/Gamma

selects a scale. A wave eigenvalue/boundary-response derivation must establish why this acoustic round trip equals this escape-response time. The radial integration check verifies the uniform-sphere coefficient; that check does not independently derive the mode-selection equality. The computed candidate remains valuable and reproducible without being promoted into complete acoustic dynamics.

## FD05: pressure ratio and acoustic derivative are different quantities

The full FD05 prompt, code, direct verdict and historical capture have been read. The prompt distinguishes fluid sound from vacuum elastic modes. The code calculates the radiation value through Law I and does not evaluate the requested discrete network moment or dispersion relation.

For a fixed local reference c and an effective density rho=u/c^2, define w=P/u. Direct differentiation gives

    c_s^2/c^2 = dP/du = w + u dw/du

along the specified acoustic perturbation. The equality c_s=c sqrt(w) requires the additional condition dw/du=0 along that path. The general mechanical definition is

    c_s^2 = (partial P/partial rho)_adiabatic,
    w_sound = c_s^2/c^2.

FD05's ordinary-fluid plot constructs w_sound from the already calculated sound speed. The plotted on-curve identity is valid, but does not independently establish w_sound=P/(rho c^2). For an ideal gas under an adiabatic perturbation the derivative contains gamma; for a liquid the relevant quantity is the bulk modulus divided by density. Recovery: retain the common derivative operator and label the pressure ratio separately from the acoustic stiffness ratio.

## Required distinction inside the Sz matrix

State evolution and an acoustic perturbation need not follow the same tangent through physical state space. For a state vector X and an acoustic perturbation tangent a,

    c_s^2 = (grad_X P dot a)/(grad_X rho dot a),

where the denominator is nonzero and the local momentum/continuity closure permits that scalar wave reduction. A cosmological tangent dX/dS supplies a different derivative unless the contact dynamics prove equality. A pressure-versus-epoch curve therefore cannot by itself supply the acoustic response. This is the smallest precise closure target: derive the acoustic tangent, stiffness and inertia from the contact operator, then propagate the same clock convention into the emission and escape calculations.

For an isotropic normalized direction distribution, rotational symmetry and unit-direction norm give the rank-two moment I/3 exactly. Isotropy fixes that static angular factor. A wave speed additionally requires the stress variation and participating resistance. Discrete-network anisotropy must be tested through the moment tensor or dispersion operator; the tensor trace alone remains one and cannot diagnose anisotropy.

For a directional second moment 1/3+delta, the conditional speed expansion is

    c sqrt(1/3+delta) = c/sqrt(3) [1 + 3 delta/2 + O(delta^2)].

FD05's prompt prints a delta/2 correction instead. That coefficient would apply if delta were defined as a fractional deviation relative to 1/3; the prompt defines delta as an additive moment deviation. Preserve the definition and use the corresponding expansion.

No acoustic constitutive operator, complete cosmic time law, independent BAO observation map or theory-wide closure is claimed by these calculations. The missing equations are explicit enough for subsequent derivation and experimental discrimination.
