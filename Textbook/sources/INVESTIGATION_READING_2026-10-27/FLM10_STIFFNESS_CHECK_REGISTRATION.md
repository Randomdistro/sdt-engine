# FLM10 stiffness-ratio control

Registered 2026-10-28 before instrument execution. Full Phase-0 and Phase-1 Python machinery, assessments and Phase-1 log read. The remaining FLM10 prompt and HTML demonstration remain unread.

Question: FLM10 states that the Si-like stretch:bend ratio cancels from dimensionless anisotropy. Common multiplication of both stiffnesses cancels, but changing their ratio need not cancel. Test the distinction in the exact diamond seed before interpreting the amorphous-network result.

Instrument: independent JavaScript implementation of the supplied Keating energy, one periodic eight-site diamond cell, four nearest neighbours per site, bonds counted once and six angle pairs per vertex. Affine strains only: no claim of reproducing non-affine relaxation or the complete FLM10 execution.

Controls before ratio comparison: 8 sites, 16 bonds, coordination four; reference energy below 1e-25; C11=C22=C33 and C44=C55=C66 within 1e-7 relative/absolute; isotropic cubic relation C44=(C11-C12)/2 gives A_U=0 within 1e-7. Halve finite-difference strain from 1e-4 to 5e-5: stiffness and anisotropy agree within 1e-6 absolute/relative. Uniform stiffness scaling by three preserves A_U within 1e-7.

Compare alpha=1, beta in {0.2,0.285,0.5,0.8}. Values are diagnostic controls, not physical calibration. Different A_U values demonstrate ratio dependence only within the supplied constitutive prototype; no native stiffness ratio is selected. Save source hashes, controls and all outputs, including any failure before correction.
