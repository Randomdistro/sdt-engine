# FD11 — Modern-Day Materials & Parts (Tesla Steam Generator)

> Build specification for a buildable, modern Tesla (bladeless boundary-layer) steam turbine-
> generator. Two tiers: **Tier-P** (low-temperature prototype / saturated steam ≤ ~180 °C, for
> validating the FD11 model cheaply) and **Tier-S** (superheated-steam performance unit,
> 300–540 °C). Materials are chosen against the FD11 loads: rim **hoop stress** at high rpm
> (`σ_θ ≈ ρ_disk ω² R²`), **steam erosion** at the nozzles, **creep/oxidation** at temperature,
> and **gap stability** (the disk gap `b_opt` from FD11 Phase 1 must hold under thermal growth).
> Author: James Christopher Tyndall, Melbourne. Status: SPEC (design intent, not yet built).

---

## Parts list (function → modern material → why)

| # | Part | Function | Tier-P material | Tier-S material (superheated steam) | Why this material | Op. limit / note |
|---|------|----------|-----------------|--------------------------------------|-------------------|------------------|
| 1 | **Rotor disks** (the heart) | Take steam momentum by surface traction (FD06) | Ti-6Al-4V (Grade 5) or 17-4 PH H900 stainless, 0.5–1.0 mm, laser/waterjet-cut | **Inconel 718** (aged) or **maraging steel C300**; 0.8–1.5 mm | Highest *specific* strength → max safe rpm (hoop-stress limited); smooth, polishable face; erosion + oxidation resistance in wet/superheated steam | Ti limited to ~350 °C in steam (oxidation) → Tier-P only; Inconel 718 good to ~650 °C; surface finish ≤ 0.2 µm Ra |
| 2 | **Shaft** | Carry torque to the generator | 17-4 PH or 4340 steel | **Inconel 718** or maraging C300, integral or Hirth-coupled | Match disk thermal expansion to hold `b_opt`; fatigue + creep margin | Balance the rotor assembly to **ISO 1940 G2.5** |
| 3 | **Disk spacers / shims** | Set & hold the gap `b_opt` (FD11 Ph.1) | Precision-ground stainless shims | **Same alloy as the disks** (thermal-expansion matched) | A mismatched spacer changes `b` with temperature → drifts off the FD06 optimum | Tolerance ±5 µm on `b` |
| 4 | **Nozzles** (convergent / de-Laval, FD05) | Accelerate steam to `V_j`, often choked/supersonic | Tungsten carbide (WC-Co) inserts | **WC-Co or sintered SiC / PSZ ceramic**, optionally Stellite-faced | Wet-steam droplet erosion is brutal here; carbide/ceramic survive it | Replaceable cartridge; throat ground to size |
| 5 | **Volute / casing** | Route steam in, contain pressure, **burst containment** | Machined 6061-T6 Al or 316L | **Cast/forged Inconel 625** or 316/347H stainless | Corrosion + creep at temperature; must contain a disk burst (huge stored KE) | Design to **ASME BPVC Sec. VIII**; containment ring sized to rotor KE |
| 6 | **Bearings** | Support rotor at high rpm, low loss | Hybrid ceramic (Si₃N₄ balls / steel races), PEEK cage, oil-mist | **Foil air bearings** or **active magnetic bearings** (oil-free, hot) | High DN value; oil-free avoids steam contamination; lower windage (FD09) | Magnetic bearings need an overspeed touchdown bearing |
| 7 | **Seals** | Limit leakage past rotor & shaft | PTFE / Viton lip + labyrinth | **Flexible graphite (Grafoil)** + Inconel labyrinth; carbon-graphite face seal | Non-contact labyrinth at speed; graphite handles 540 °C steam | Steam-rated; dry-running capable |
| 8 | **Generator / alternator** | Convert shaft power to electricity | NdFeB (N42) PM generator, Halbach option | **SmCo (Sm₂Co₁₇)** PM generator, or switched-reluctance | High power density at high rpm; SmCo keeps magnetisation hot (higher Curie temp than NdFeB) | Keep magnets below Curie temp; cool the stator |
| 9 | **Power electronics** | Rectify/condition variable-freq output | Si MOSFET active rectifier | **SiC** MOSFET active rectifier + DC-link | High-rpm → high electrical frequency; SiC handles it efficiently | MPPT-style speed control to ride the `η_rotor(λ)` peak (FD11 Ph.2) |
| 10 | **Steam source / boiler** | Supply `(P₀,T₀)`, `ṁ` (FD05) | Electric resistance kettle-boiler | **Inconel-625 once-through coil boiler**; solar-concentrator or waste-heat fed | Compact, fast, clean; once-through gives superheat | Inputs feed FD11 Phase 3 (`ṁ`, `V_j`) |
| 11 | **Thermal insulation** | Keep heat in, surfaces safe | Ceramic-fibre blanket | **Silica aerogel blanket** / microporous (Microtherm) | Lowest conductivity per thickness; compact lagging | — |
| 12 | **Exhaust / condenser ports** | Central low-pressure exit | 316L tube | 316L / 347H, condenser optional | Recovers exhaust KE loss term (FD11 Ph.3 `η_exhaust`) | — |

---

## Additive-manufacturing option (integral bladeless rotor)

The whole disk-pack + shaft can be printed as one piece by **laser powder-bed fusion (LPBF / DMLS)** in **Ti-6Al-4V** (Tier-P) or **Inconel 718** (Tier-S), then HIP'd (hot-isostatic-pressed) to close porosity, solution-treated/aged, and the gas-path faces finished by abrasive-flow machining to the required ≤0.2 µm Ra. This removes the spacer-stack tolerance problem (part #3) by printing the gaps `b_opt` directly — but the as-built gap must still be inspected (CT) against the FD11 Phase-1 value.

---

## Material-driven design bounds (feed FD11 Phase 5)

- **Max safe rpm** from disk hoop stress `σ_θ ≈ ρ_disk ω² R_o²` ≤ allowable: Inconel 718 (ρ≈8190 kg/m³, σ_allow≈1000 MPa aged) gives a far higher rim speed than 316L; Ti-6Al-4V (ρ≈4430, σ≈900 MPa) gives the best rim speed of all → highest `U`, hence highest `λ`-reachable. This bound sets the rpm cap in FD11 falsifier **F5**.
- **Temperature** picks the tier: Ti/17-4 for ≤~350 °C saturated steam (Tier-P); Inconel/maraging + SmCo magnets for 300–540 °C superheat (Tier-S).
- **Gap stability:** spacers, disks, and shaft share one alloy so differential thermal growth does not walk `b` off the FD06 optimum.
- **Erosion:** carbide/ceramic only where steam is fastest (nozzle throat, part #4); the disks see low relative velocity and tolerate alloy.

---

## Safety (non-negotiable, this is a high-energy steam machine)

- **Pressure vessel:** boiler and casing to **ASME BPVC** (Sec. I boiler, Sec. VIII casing); relief valve sized to boiler capacity.
- **Rotor burst:** the disk pack stores large kinetic energy at design rpm; the casing (#5) must be a rated **containment ring**, with an **overspeed trip** that cuts steam if `ω` exceeds the hoop-stress limit.
- **Hot surfaces / steam:** lagging (#11), guarding, and condensate handling.
- This is a benign mechanical-engineering / educational build; standard steam-plant and rotating-machinery codes apply.
