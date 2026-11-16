# Mathematical closure dependencies — reading checkpoint

Status: incomplete source reading; working questions, not a final assessment of SDT. Canonical files unchanged. Historical conclusions require direct replay before citation as new results.

## CMB supply and operational quantities

Operator clarification: CMB convergence fuels every physical process in SDT. `Laws/LAW_OF_CONVERGENT_BOUNDARY_PRESSURE.md` explicitly treats pressure as the local mechanical state and the microwave spectrum as an observable mode. Replacing that premise with ordinary microwave absorption would test a different mechanism.

The mathematical task is to establish the relation between the observed spectrum, scalar convergence, directional stress, reusable phase response and net extractable power. Compression energy, continuously delivered energy, mechanical work and emitted energy require separate units and balance terms. The release-cascade text uses expanding fronts and cumulative local occupancy; causal arrival and persistence must be reconciled by the native evolution rule. FLM14 concerns electron-tour residence and is not automatically the required cosmological retention law.

## Source findings requiring reconciliation

- CQ06's fixed-total-source law `v^2=c^2*om_total*f(r)/r` with bounded `f` cannot produce a nonzero asymptotically flat speed. A finite flat interval requires the product `om_total*f` to grow proportionally to radius over that interval. Later galactic work remains unread; no theory-wide conclusion follows from CQ06.
- The common-Spaz continuation defines `Cg=Rp/RpLock`. Algebraically inserting the quotient does not establish an additional physical mechanism or a state response. Hydrogen's enclosing boundary and the proton's own circulation boundary remain distinct, as recorded in PPT18.
- FLM15's supplied-boundary lock integrals follow from an isotropic direction measure and `k(r)=sqrt(r/b)`. The executed independent check reproduces the locked and complementary volume integrals with relative errors below 1.63e-9. Boundary selection, contact curvature and outgoing-channel response are not established by that integral check.
- FLM14's assessment records multiple instrument revisions and no accepted residence exponent. The later packer-seat extension establishes nonuniform hop geometry only. Source tools and complete run log remain unread; historical numerical claims are not newly certified.
- FLM12 `flm12_d1_recovery.py` now implements a nuclear influx-regime comparison. `flm12_d1_recovery_results.txt` still reports an earlier extended/handed recovery and does not correspond to the current script. Preserve both; a new capture with source hash is required before using the current calculation as executed evidence.
- FLM12's printed anomaly statements do not substitute for a momentum-response derivation. Uniform-velocity anisotropy and acceleration-dependent resistance must be separated by an explicit contact/relay response, including outgoing momentum. No new proof of inertia is claimed at this checkpoint.

## Reading and execution limits

The source inventory includes five roots and 5892 distinct hashed contents, including generated datasets and code. Full reading is unfinished. Documents, archives, encoding-review entries and all unrecorded text remain pending. Reading receipts identify completed files only.

Independent execution: `check-lock-kernel.cjs`, registered in `KERNEL_CHECK_REGISTRATION.md`; results in `KERNEL_CHECK_RESULTS.json`. Original Python tools were not executed because available launchers could not start. No empirical data or fitted parameter enters the dimensionless check.

## Direct topology replay and proposed comment correction

Executed the unchanged `PPT09_Winding_Number_Stability/ppt09_reset_1.cpp` with MSVC C++20, optimization, UTF-8 and W4 against the present canonical header. Build and execution completed; no warnings printed. Captures: `PPT09_BUILD_2026-10-27.txt`, `PPT09_REPLAY_2026-10-27.txt`.

All registered instrument validations were met. Burau and closed-form routes agree across 25 coprime pairs. For T(2,3), the polynomial is `1-t+t^2`, determinant 3. For T(2,5), the polynomial is `1-t+t^2-t^3+t^4`, determinant 5. The canonical comment at laws.hpp line 2404 prints the symmetric cinquefoil form while identifying a trefoil. Proposed replacement: `Delta=t^-1-1+t != 1`. Canonical code and comments are unchanged pending approval. This is a mathematical comment correction; neither the particle assignment nor a reconnection-energy barrier is determined by the polynomial.

GOM22's inspected source explicitly states that the spectral depth differential agrees with the clock-ratio expression to first order. Strong-depth extension must retain that scope and specify the exact observable and endpoint clock convention before interpreting an arrest boundary.

## SAR02 and FIRAS checkpoint

Full SAR02 text set read. Its reset separates mode count, mode energy and temperature weighting. The finite-ensemble counting check missed the original R=3200 tolerance at occupation 0.1; the explicitly amended larger-ensemble run records convergence. Neither historical run has been re-executed here. Equal microstate weighting remains a premise requiring native dynamical justification.

The official NASA LAMBDA product was checked online on 2026-10-27. The repository already contains the same named FIRAS product at `Datasets/NASA_FIRAS_PPT20/firas_monopole_spec_v1.txt`, SHA-256 `df793c3dca09ebfa7dbc5aa0ec1951daa8884431bc30eff28a710d7516cf50fa`. No duplicate acquisition. Column 2 is a reconstructed 2.725 K blackbody plus column-3 residuals; columns 3 and 4 are residuals and one-sigma uncertainties in kJy/sr. No covariance matrix is supplied in this five-column file. No new fit or physical verdict performed. This observable constrains spectral transport; it does not directly measure the complete convergence-pressure reservoir.

Source: https://lambda.gsfc.nasa.gov/product/cobe/firas_monopole_spect.html and https://lambda.gsfc.nasa.gov/data/cobe/firas/monopole_spec/firas_monopole_spec_v1.txt
