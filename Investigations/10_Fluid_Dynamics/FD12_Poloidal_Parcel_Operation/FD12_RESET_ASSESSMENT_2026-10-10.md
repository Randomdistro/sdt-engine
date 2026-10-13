# FD12 — The poloidal parcel operation: reset record, registration audit (2026-10-10)

**Protocol:** Investigations/RESET_2026-10-06/PROTOCOL.md. Session sdt-engine-e0. **Read:** PROMPT.md (gates pre-committed 2026-07-26). **Not opened:** FD12_VERDICT_DIRECT_2026-07-26.md, the rerun outputs, d12_poloidal_parcel.cpp.

## Audit
1. **The P2 pass classes cannot be reached by the registered sweep. This is a registration defect, found before any computation.**
   - The sweep is λ/L ∈ {1/4, 1/2, 1, 2, 4, 8, 16} and the convention is ℓ_c = λ*/2. So L/ℓ_c = 2L/λ* ∈ {8, 4, 2, 1, 1/2, 1/4, 1/8}: **at most 8**.
   - G2-STRONG needs L/ℓ_c ∈ [24, 96] and G2-ORDER needs [10, 200]. Both are empty under the sweep. Every possible outcome lands in G2-FAIL.
   - Under GATEWAY_PROCEDURAL §3.1, a criterion whose pass class is empty is not a test.
   - The 2-D planar surrogate (spanwise-uniform waves) is fixed by the prompt, so no reading of "wavelength" rescues it within the registration.
2. **P1 needs a supplier.** It requires the "FD01-earned relay/NS lattice". FD01 has not been rerun under this protocol, and a plain Navier–Stokes solver would not test the SDT relay claim. The prompt also caps P1's class at consistency (Lamb dipole), not discrimination.

## Outcome
**P2: not run; registration defect (the pass class is empty).** **P1: blocked on the FD01 supplier.** G2.

**What opens it:** a re-registered P2 whose sweep can reach the pass band. For example, λ/L down to 1/64; or an explicit spanwise-streak (3-D) optimum, if the claim is about pipe coherence. The ℓ_c convention stays fixed before any run. FD01 is rerun first, for P1.

## Comparison with the archived record
Deferred.
