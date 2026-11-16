# NSEQ16 braid repair — cyclic quadruple helix

**Author:** James Christopher Tyndall, Melbourne  
**Registered:** 2026-08-16, before braid-repair instrumentation  
**Status:** PRE-REGISTERED TOPOLOGY REPAIR · ONE TASK ONLY

## Trigger

The existing pulled-ring control is a `(4,1)` torus centreline. It makes only
one quarter of a local helical turn per toroidal lap. That is not the clarified
construction.

The required object is:

1. four simultaneous helical lanes;
2. one complete local helix turn during each toroidal lap;
3. one additional quarter-turn lane advance during that lap;
4. a cyclic seam in which each lane tail joins the next lane head;
5. one continuous filament that returns to its original lane after four laps.

This repair changes only the nucleon braid geometry, its kinematic diagnostics
and its 3D rendering. The alpha/deuteron/triton grammar, valence-position
spherical seating, proton-neutron contact graph and NSEQ05 control remain
frozen.

## Frozen geometry

Let `P = 4` be the number of major tours and lanes. Let one full local twist
per lap contribute `P` poloidal turns over the closed filament, and let the
one-lane cyclic seam contribute one more:

\[
P=4,\qquad Q=4(1)+1=5,\qquad \gcd(P,Q)=1.
\]

The continuous filament is the `(4,5)` torus braid

\[
\phi(u)=4u,\qquad
\psi(u)=\pi+5u,
\]

\[
B(u)=\left(
(R+a\cos\psi)\cos\phi,\,
(R+a\cos\psi)\sin\phi,\,
a\sin\psi
\right),\qquad 0\le u\le2\pi.
\]

The registered dimensions are

\[
R=0.62R_p,\qquad a=0.22R_p,\qquad b=0.16R_p,
\]

where \(b\) is the physical strand-tube radius. Therefore
\(R+a+b=R_p\): the outer strand envelope reaches the nucleon rim.

The four lanes over one toroidal lap are segments of this one filament:

\[
S_j(\theta)=B\!\left(\frac{\theta+2\pi j}{4}\right),
\quad j\in\{0,1,2,3\},\quad0\le\theta\le2\pi.
\]

For each lane,

\[
\Delta\psi=\frac{5}{4}(2\pi)=2\pi+\frac{\pi}{2}.
\]

It therefore performs one full local twist and advances exactly one lane.
The seam rule is

\[
S_j(2\pi)=S_{(j+1)\bmod4}(0).
\]

## Frozen kinematic reading

Every nucleon retains one common signed major-phase period. Proton and neutron
rotors have opposite hand at a listed contact. The braid does not require
equal local line speed at every depth: at uniform master phase,

\[
\left|\frac{dB}{du}\right|
=\sqrt{(5a)^2+\left(4(R+a\cos\psi)\right)^2}.
\]

The inner and outer portions therefore cover different local distances while
the complete ring closes on the same master period. This is a kinematic
diagnostic, not an energy or self-drive claim.

## Registered gates

| Gate | Requirement |
|---|---|
| B0 | Topology reports `P=4`, `Q=5`, four lanes, one local twist per lap and one-lane seam advance; `gcd(P,Q)=1`. |
| B1 | Each lane advances by \(2\pi+\pi/2\) in unwrapped local phase within \(10^{-12}\). |
| B2 | Every lane tail equals the next lane head within \(10^{-10}R_p\), while lanes 0–2 do not self-close after one lap. |
| B3 | Unit tangents agree across every cyclic seam within \(10^{-8}\). |
| B4 | The traced filament closes only after four major laps; endpoint residual is below \(10^{-10}R_p\). |
| B5 | Successive major tours begin in the order inner, under, outer, over. |
| B6 | \(R+a+b=R_p\) within \(10^{-12}R_p\), and the inner envelope remains positive. |
| B7 | Local speed is finite and positive over the whole filament; the sampled outer/inner speed ratio agrees with the analytic ratio within \(10^{-8}\). |
| B8 | The old `(4,1)` curve fails the full-local-twist gate and remains only a rejected topology control. |
| B9 | Repeated metrics are deterministic, Release/docs braid code is byte-identical, and the 3D smoke test renders both braid and trefoil controls. |

## Decision

- B0–B9 pass: `CYCLIC_QUADRUPLE_HELIX_CANDIDATE`.
- Any gate fails: `CYCLIC_QUADRUPLE_HELIX_REJECTED`, naming the failed gate.

No result from this repair converts interleaving to mass-defect energy,
promotes an electron-force mechanism, or changes `Engine/include/sdt/laws.hpp`.
