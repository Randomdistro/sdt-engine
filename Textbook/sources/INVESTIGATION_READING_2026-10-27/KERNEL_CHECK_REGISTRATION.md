# Independent dimensionless relay-lock check

Registered 2026-10-27 before creating the instrument.

Purpose: check the mathematical integrals in FLM15 MODEL_SPEC.md and the supplied Python source. No particle prediction, physical pressure measurement or native boundary selection follows from this check. No canonical edit.

Premises: isotropic directions; mu=abs(cos(theta)) uniform on [0,1]; supplied positive boundary b; k(r)=sqrt(r/b) inside b; locked fraction k, complementary fraction 1-k.

Route A integrates analytically: V_locked=8*pi*b^3/7, V_wake=4*pi*b^3/21. Route B uses composite midpoint quadrature in normalized radius and explicit midpoint direction counting. Test b in {0.125,1,7}; radial grids 1024,4096,16384. At the finest grid each integral must agree to relative 1e-7. Refinement must reduce the error at every grid for both components. Angular fractions at k={0,0.125,0.25,0.5,0.875,1} must agree within 1e-6 using 100000 midpoint directions. The isotropic second moment must agree with 1/3 within 1e-8. Partition must agree with sphere volume within relative 1e-12.

Before execution clarification: the 1e-12 partition gate concerns the analytic sum of the complementary volumes. The independently integrated midpoint sum also has finite-grid volume error; register a separate relative 1e-8 partition gate at the finest grid. No result has been evaluated before this clarification.

All quantities are dimensionless mathematical controls, not observations. Results must retain every grid and boundary. A numerical disagreement triggers instrument diagnosis before any physics conclusion. Original Python tests were not run: Windows Store Python launchers return access denied and the registered C:/Python312 executable is absent.
