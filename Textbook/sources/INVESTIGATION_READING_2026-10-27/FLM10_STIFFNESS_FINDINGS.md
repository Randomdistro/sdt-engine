# FLM10: constitutive ratio control and recovery

2026-10-28. Full local text set read, including both Python tools, phase assessments, run log, production prompt and HTML illustration. The network binary and diagnostic image remain separate pending inspection. Original Python optimization was not re-executed. Independent affine control only.

## Why the anisotropy depends on the constitutive ratio

FLM10 uses a Keating stretch/bend prototype with alpha=1 and beta=0.285. A common multiplicative stiffness scale cancels from the dimensionless anisotropy. The ratio beta/alpha remains inside the elastic tensor and need not cancel.

The independent eight-site periodic diamond control reproduces the supplied energy convention: 16 undirected bonds, six angle pairs per site. All nine registered controls pass, including zero reference energy, cubic symmetry, the isotropic control, common-scale invariance and finite-difference refinement. No source or canonical file was modified.

| alpha | beta | C11 | C12 | C44 | Universal anisotropy A_U |
|---:|---:|---:|---:|---:|---:|
| 1 | 0.2 | 1.1 | 0.3 | 0.7 | 0.385714285 |
| 1 | 0.285 | 1.355 | 0.215 | 0.785 | 0.123969158 |
| 1 | 0.5 | 2 | 0 | 1 | 0 |
| 1 | 0.8 | 2.9 | -0.3 | 1.3 | 0.051923077 |

For the supplied bond-count convention, direct affine expansion gives

    C11 = alpha/2 + 3 beta,
    C12 = alpha/2 - beta,
    C44 = alpha/2 + beta.

Consequently the isotropic cubic condition C44=(C11-C12)/2 selects beta=alpha/2. That selection is a control of the prototype, not a physical calibration. Uniformly tripling both coefficients preserves A_U; changing beta/alpha changes A_U.

The independently calculated affine A_U=0.123969 at beta=0.285 lies close to FLM10's printed diamond affine fit 0.1247. The difference is not an independent reproduction of the historical optimization and fit; only the affine constitutive dependence is established.

## Recovery path

1. Derive the allowed stretch/bend relation from native contact deformation, or retain the ratio as an explicit conditional input.
2. Validate the strain-energy machinery against exact diamond coefficients, multiple strain amplitudes and positive-definiteness checks before interpreting an amorphous-network fit.
3. Separate common-stiffness scaling from ratio variation in sensitivity and uncertainty propagation.
4. Evaluate the full acoustic tensor with an explicit participating-resistance operator. Sorted eigenvalues alone do not establish exact longitudinal/transverse polarization in a finite anisotropic network; polarization projections must also be evaluated.
5. Handle residual stress explicitly. Relaxing internal nodes at fixed box does not force the box stress to vanish; fitting a linear energy term records the stress but does not remove the stress. Acoustic response around a stressed state requires the corresponding incremental equation.
6. Test a dynamically reconfiguring network separately from a frozen relaxed network. The FLM10 prompt specifies a reconfigurable medium; the current elastic calculation probes a frozen topology during each strain relaxation. Equality of those responses requires a time-scale argument.

## Scope of the existing result

FLM10 establishes a useful finite-network prototype and records limited size/ensemble coverage. Phase-1 results explicitly leave the finite-wave-number dispersion, native absolute moduli and large-network limit unfinished. The stored data support the reported finite realizations; two sizes and one larger realization do not establish an asymptotic decay law.

The phase-0 void fraction is printed from the diamond-limit expression, rather than measured from the deformed network. The HTML illustration imposes displacement and motion rules directly and contains no contact time evolution or conserved mechanical ledger. Neither artifact supplies the microscopic response kernel.

The source statement connecting isotropy to Bell correlations also needs the complete detector/channel response: spatial isotropy alone does not derive an outcome-correlation function. Later FLM14 readout must retain the explicitly traced setting dependence rather than substitute an isotropy assertion for that calculation.

The new control resolves the ratio-cancellation question. Native stiffness selection, reconfiguration dynamics and the physical mode map remain determining equations, not reasons to discard the contact-medium program.
