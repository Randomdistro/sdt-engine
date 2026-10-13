# FD11 — Staggered-Chamber Tesla Generator on a 2 km Geothermal Pinhole

**Domain**: Fluid Dynamics (SDT lattice mechanics) · **Status**: DESIGN + first simulation run
**Author**: James Christopher Tyndall, Melbourne · Tool: `fd11_tesla_turbine.cpp`

> The FD11 bladeless turbine (drive = spation traction, FD06/PPT06) instantiated with four
> design refinements and dropped onto the return leg of a closed-loop 2 km borehole. Every
> number is provenance-tagged; the standard-engineering values are convergence targets, not
> borrowed coefficients. Numbers below are an **engineering estimate** (several ASSUMED
> efficiencies + two CALIBRATED(1) coefficients), not a sealed SDT prediction.

---

## The four design refinements

1. **Staggered / serpentine chambers.** The disk pack is split into `N=4` stages; the steam
   snakes **rim→hub** in stage 1, **hub→rim** in stage 2, rim→hub in stage 3, … Each stage takes
   a slice of the total pressure ratio, so every stage runs near its own peak tip-speed ratio
   (`λ≈0.5`) instead of one stage swallowing the whole expansion off-design. Alternating the
   radial flow direction also **balances axial thrust** (each stage's inward pull is opposed by
   the next stage's outward pull), and lets adjacent stages share a manifold at the matching
   radius. In the energy model this raises overall turbine efficiency from ~0.35 (single stage)
   to `ETA_TURB ≈ 0.45` (4-stage compounded) — the only place staging enters the power budget.

2. **Bearinged comb-ring.** Thin Tesla disks flutter at speed (the classic failure mode). All
   disk edges are interleaved into a ring of rolling elements (a "comb") that captures every rim
   and hub edge, so the pack cannot wobble — converting a stability liability into a stiff,
   bearing-supported rotor. Cost: a small parasitic drag (`ETA_MECH ≈ 0.97`). Benefit: the rotor
   can safely reach the Inconel hoop-stress rpm.

3. **Variable drive gear (CVT).** A continuously-variable transmission brokers between the steam
   side (whatever the well delivers) and the generator side (whatever the load accepts) and
   **parks the rotor at its `η_rotor(λ)` peak** regardless of either — the mechanical analogue of
   MPPT. Modeled as `ETA_CVT ≈ 0.92`.

4. **(Materials)** Tier-S build from `MATERIALS_AND_PARTS.md`: Inconel-718 disks (the hoop-stress
   rpm limit), WC/ceramic nozzles, SmCo PM generator, SiC electronics.

## The borehole ("pinhole") model

Closed-loop coaxial well, `H = 2 km`: cold water injected, heated by the geothermal gradient
along the descent/bottom (heat-exchange effectiveness `ε_hx`, CALIBRATED(1)), returns up the
centre pipe. A **single-flash separator** at `T_flash = ½(T_ret + T_cond)` produces steam fraction
`x`; the steam drives the staggered turbine and exhausts to a condenser at ~0.10 bar (`T_cond=46 °C`).
Pump power = Darcy friction over the 4 km down+up path **minus** the thermosiphon buoyancy of the
hot (lighter) return column. The narrow bore is the dominant cost: friction scales `~1/d⁵`.

---

## Results (first run)

**Turbine design point** (Inconel-718, `R_o=100 mm`, 4 staggered stages):
- Optimal disk gap `b_opt ≈ 1.25 mm` (form `b = K_b√(ν·t_res)` DERIVED; `K_b` CALIBRATED(1)).
  Tesla's measured steam gap is ~0.4 mm → **same order, ~3× high**; the assumed spiral speed
  `v_rad` and `K_b` need the proper Phase-1 calibration to close to <20% (currently a soft point).
- Hoop-stress limit ≈ **292 m/s rim = 27,900 rpm**; operating point (`λ=0.5`) = 175 m/s = 16,700 rpm.
  **rpm headroom 1.7× → falsifier F5 satisfied** (operating speed under the burst limit).

**Geothermal gradient sweep** (return pipe `d=50 mm`, `ṁ=3 kg/s`, condenser 0.10 bar):

| grad [°C/km] | T_bh [°C] | T_ret [°C] | x_steam [%] | Δh_s [kJ/kg] | P_gross [kW] | P_pump [kW] | **P_net [kW]** |
|---|---|---|---|---|---|---|---|
| 30 (normal) | 75 | 63 | 1.5 | 65 | 1.1 | 5.1 | **−4.1** |
| 50 (good) | 115 | 95 | 4.4 | 170 | 8.3 | 4.8 | **+3.5** |
| 80 (hot) | 175 | 143 | 8.9 | 300 | 29.6 | 4.2 | **+25.4** |
| 120 (volcanic) | 255 | 207 | 15.3 | 438 | 74.3 | 3.4 | **+70.9** |

**Pinhole-diameter sensitivity** (hot site, 80 °C/km):

| d_pipe [mm] | P_pump [kW] | P_net [kW] |
|---|---|---|
| 25 | 165.8 | **−136.2** |
| 40 | 16.0 | +13.6 |
| 50 | 4.2 | +25.4 |
| 75 | 0.0 | +29.6 |
| 100 | 0.0 | +29.6 |

---

## Verdict (honest ledger)

- **One pinhole well → kW-scale net power.** Net-**positive from ~50 °C/km up**; a normal
  30 °C/km / 2 km site is too cold to flash useful steam (pump > steam output) → use an ORC
  working fluid or go deeper/hotter. Site efficiency 0.4–2.9% is realistic for low-grade
  single-flash geothermal.
- **The narrow bore is the killer:** friction `~1/d⁵`. Below ~40 mm the pump eats everything
  (−136 kW at 25 mm); above ~75 mm the thermosiphon buoyancy fully drives circulation (pump→0).
  So a "pinhole" wants to be ≥ ~50 mm on the return leg, or run slower.
- **The turbine is self-consistent:** operating rpm sits comfortably under the hoop-stress
  limit; the comb-ring + CVT make that operating point reachable and stable.

**Open / soft points (future work):** `b_opt` is ~3× Tesla's gap because `v_rad` and `K_b` are
ASSUMED — the proper FD11 Phase-1 inter-disk flow solve must calibrate them. `ε_hx` and all
drivetrain efficiencies are ASSUMED/CALIBRATED(1). Steam properties use a Magnus saturation
curve + ideal-gas-steam expansion (good to ~150 °C; the 120 °C/km row is extrapolated). The
staggered serpentine raises `η` in the model via a single lumped `ETA_TURB`; a per-stage
expansion solve (true compounding) is the next step.
