# PPT18 stage 3: radiation map of the proton's own ladder (2026-10-12)

**Registration:** PROMPT.md addendum (d), written before `ppt18_stage3.cpp`. Single pass; V1–V3 met. Output `ppt18_stage3_results.txt`. **No observed radiation is compared.**

**Ladder:** Ѻ_p = 0.15538 fm (stage 2b-r fill limit); z_p = Ѻ_p/r; v = c√z. Hydrogen's ladder (z_H = r_e/r) is shown alongside.

## 1. Stations: depth, speed and line shift

| station | r (fm) | z_p | v_p/c | z_H | v_H/c | shift (own) | shift (H) | own + H | light speed (1−z_p)² |
|---|---|---|---|---|---|---|---|---|---|
| Om_p | 0.15538 | 1.000000 | 1.00000 | 18.136334 | 4.25868 | 100.000% | 1813.633% | 1913.633% | 0.00000 |
| node R_p/3 | 0.28041 | 0.554097 | 0.74438 | 10.049290 | 3.17006 | 55.410% | 1004.929% | 1060.339% | 0.19883 |
| a=R | 0.31075 | 0.500000 | 0.70711 | 9.068167 | 3.01134 | 50.000% | 906.817% | 956.817% | 0.25000 |
| R_p | 0.84124 | 0.184699 | 0.42977 | 3.349763 | 1.83024 | 18.470% | 334.976% | 353.446% | 0.66472 |
| 2R_p (contact) | 1.68247 | 0.092350 | 0.30389 | 1.674882 | 1.29417 | 9.235% | 167.488% | 176.723% | 0.82383 |
| r_e | 2.81794 | 0.055138 | 0.23481 | 1.000000 | 1.00000 | 5.514% | 100.000% | 105.514% | 0.89276 |
| a0 | 52917.72109 | 0.000003 | 0.00171 | 0.000053 | 0.00730 | 0.000% | 0.005% | 0.006% | 0.99999 |
| inf | inf | 0.000000 | 0.00000 | 0.000000 | 0.00000 | 0.000% | 0.000% | 0.000% | 1.00000 |

## Mover: electron m_e (0.510999 MeV)

| transition (out → in) | Δz_p | F full (MeV) | H half (MeV) | B budget (MeV) | λ_F (fm) | λ_H (fm) | λ_B (fm) | band (H) | L*_H (fm) | L*_H/(2π r_in) |
|---|---|---|---|---|---|---|---|---|---|---|
| inf → 2R_p (contact) | 0.092350 | 0.0471905 | 0.0235953 | 0.0241667 | 26273.1 | 52546.2 | 51303.7 | hard X-ray | 7984 | 755.3 |
| inf → R_p | 0.184699 | 0.094381 | 0.0471905 | 0.0495975 | 13136.6 | 26273.1 | 24998.1 | hard X-ray | 5646 | 1068 |
| 2R_p (contact) → R_p | 0.092350 | 0.0471905 | 0.0235953 | 0.0254308 | 26273.1 | 52546.2 | 48753.6 | hard X-ray | 1.129e+04 | 2136 |
| r_e → R_p | 0.129561 | 0.0662056 | 0.0331028 | 0.03531 | 18727.2 | 37454.3 | 35113 | hard X-ray | 8048 | 1523 |
| R_p → a=R | 0.315301 | 0.161118 | 0.0805592 | 0.100071 | 7695.22 | 15390.4 | 12389.7 | hard X-ray | 5441 | 2787 |
| a=R → Om_p | 0.500000 | 0.255499 | 0.12775 | 0.361331 | 4852.62 | 9705.24 | 3431.32 | nuclear gamma (0.1-10 MeV) | 4853 | 4971 |
| R_p → Om_p | 0.815301 | 0.416618 | 0.208309 | 0.461401 | 2975.97 | 5951.94 | 2687.12 | nuclear gamma (0.1-10 MeV) | 2976 | 3048 |
| inf → Om_p | 1.000000 | 0.510999 | 0.255499 | 0.510999 | 2426.31 | 4852.62 | 2426.31 | nuclear gamma (0.1-10 MeV) | 2426 | 2485 |
| R_p → node R_p/3 | 0.369398 | 0.188762 | 0.094381 | 0.120177 | 6568.28 | 13136.6 | 10316.8 | hard X-ray | 4889 | 2775 |
| a0 → R_p | 0.184696 | 0.0943795 | 0.0471898 | 0.0495967 | 13136.8 | 26273.5 | 24998.5 | hard X-ray | 5646 | 1068 |

## Mover: proton m_p (938.272089 MeV)

| transition (out → in) | Δz_p | F full (MeV) | H half (MeV) | B budget (MeV) | λ_F (fm) | λ_H (fm) | λ_B (fm) | band (H) | L*_H (fm) | L*_H/(2π r_in) |
|---|---|---|---|---|---|---|---|---|---|---|
| inf → 2R_p (contact) | 0.092350 | 86.649 | 43.3245 | 44.3738 | 14.3088 | 28.6176 | 27.9409 | high-energy gamma (10-100 MeV) | 4.348 | 0.4113 |
| inf → R_p | 0.184699 | 173.298 | 86.649 | 91.0685 | 7.1544 | 14.3088 | 13.6144 | high-energy gamma (10-100 MeV) | 3.075 | 0.5817 |
| 2R_p (contact) → R_p | 0.092350 | 86.649 | 43.3245 | 46.6947 | 14.3088 | 28.6176 | 26.5521 | high-energy gamma (10-100 MeV) | 6.149 | 1.163 |
| r_e → R_p | 0.129561 | 121.564 | 60.7818 | 64.8346 | 10.1991 | 20.3983 | 19.1232 | high-energy gamma (10-100 MeV) | 4.383 | 0.8293 |
| R_p → a=R | 0.315301 | 295.838 | 147.919 | 183.745 | 4.19095 | 8.3819 | 6.74762 | very-high-energy gamma (>100 MeV) | 2.963 | 1.518 |
| a=R → Om_p | 0.500000 | 469.136 | 234.568 | 663.459 | 2.64282 | 5.28564 | 1.86876 | very-high-energy gamma (>100 MeV) | 2.643 | 2.707 |
| R_p → Om_p | 0.815301 | 764.974 | 382.487 | 847.204 | 1.62076 | 3.24153 | 1.46345 | very-high-energy gamma (>100 MeV) | 1.621 | 1.66 |
| inf → Om_p | 1.000000 | 938.272 | 469.136 | 938.272 | 1.32141 | 2.64282 | 1.32141 | very-high-energy gamma (>100 MeV) | 1.321 | 1.354 |
| R_p → node R_p/3 | 0.369398 | 346.596 | 173.298 | 220.663 | 3.5772 | 7.1544 | 5.6187 | very-high-energy gamma (>100 MeV) | 2.663 | 1.511 |
| a0 → R_p | 0.184696 | 173.295 | 86.6476 | 91.0671 | 7.15451 | 14.309 | 13.6146 | high-energy gamma (10-100 MeV) | 3.075 | 0.5817 |

## Mover: one loop m_p/4 (234.568022 MeV)

| transition (out → in) | Δz_p | F full (MeV) | H half (MeV) | B budget (MeV) | λ_F (fm) | λ_H (fm) | λ_B (fm) | band (H) | L*_H (fm) | L*_H/(2π r_in) |
|---|---|---|---|---|---|---|---|---|---|---|
| inf → 2R_p (contact) | 0.092350 | 21.6622 | 10.8311 | 11.0934 | 57.2352 | 114.47 | 111.763 | high-energy gamma (10-100 MeV) | 17.39 | 1.645 |
| inf → R_p | 0.184699 | 43.3245 | 21.6622 | 22.7671 | 28.6176 | 57.2352 | 54.4575 | high-energy gamma (10-100 MeV) | 12.3 | 2.327 |
| 2R_p (contact) → R_p | 0.092350 | 21.6622 | 10.8311 | 11.6737 | 57.2352 | 114.47 | 106.208 | high-energy gamma (10-100 MeV) | 24.6 | 4.654 |
| r_e → R_p | 0.129561 | 30.3909 | 15.1954 | 16.2086 | 40.7965 | 81.593 | 76.4926 | high-energy gamma (10-100 MeV) | 17.53 | 3.317 |
| R_p → a=R | 0.315301 | 73.9595 | 36.9798 | 45.9363 | 16.7638 | 33.5276 | 26.9905 | high-energy gamma (10-100 MeV) | 11.85 | 6.071 |
| a=R → Om_p | 0.500000 | 117.284 | 58.642 | 165.865 | 10.5713 | 21.1426 | 7.47502 | high-energy gamma (10-100 MeV) | 10.57 | 10.83 |
| R_p → Om_p | 0.815301 | 191.244 | 95.6218 | 211.801 | 6.48305 | 12.9661 | 5.85381 | high-energy gamma (10-100 MeV) | 6.483 | 6.641 |
| inf → Om_p | 1.000000 | 234.568 | 117.284 | 234.568 | 5.28564 | 10.5713 | 5.28564 | very-high-energy gamma (>100 MeV) | 5.286 | 5.414 |
| R_p → node R_p/3 | 0.369398 | 86.649 | 43.3245 | 55.1658 | 14.3088 | 28.6176 | 22.4748 | high-energy gamma (10-100 MeV) | 10.65 | 6.045 |
| a0 → R_p | 0.184696 | 43.3238 | 21.6619 | 22.7668 | 28.618 | 57.2361 | 54.4584 | high-energy gamma (10-100 MeV) | 12.3 | 2.327 |

## Hydrogen-ladder comparison (electron, z_H = r_e/r; B undefined for z_H > 1)

| transition | Δz_H | F (MeV) | H (MeV) | band (H) |
|---|---|---|---|---|
| inf → 2R_p (contact) | 1.67488 | 0.855863 | 0.427931 | nuclear gamma (0.1-10 MeV) |
| inf → R_p | 3.34976 | 1.71173 | 0.855863 | nuclear gamma (0.1-10 MeV) |
| 2R_p (contact) → R_p | 1.67488 | 0.855863 | 0.427931 | nuclear gamma (0.1-10 MeV) |
| r_e → R_p | 2.34976 | 1.20073 | 0.600363 | nuclear gamma (0.1-10 MeV) |
| R_p → a=R | 5.71840 | 2.9221 | 1.46105 | nuclear gamma (0.1-10 MeV) |
| a=R → Om_p | 9.06817 | 4.63382 | 2.31691 | nuclear gamma (0.1-10 MeV) |
| R_p → Om_p | 14.78657 | 7.55592 | 3.77796 | nuclear gamma (0.1-10 MeV) |
| inf → Om_p | 18.13633 | 9.26765 | 4.63382 | nuclear gamma (0.1-10 MeV) |
| R_p → node R_p/3 | 6.69953 | 3.42345 | 1.71173 | nuclear gamma (0.1-10 MeV) |
| a0 → R_p | 3.34971 | 1.7117 | 0.855849 | nuclear gamma (0.1-10 MeV) |

## 2. Identities inside the grid (algebra; not findings)
1. **Movers and forms alias each other.** F for one loop (m_p/4) at depth 2z equals H for the proton at depth z, and so on: one number appears in several cells. For example, 43.32 MeV is proton H at contact, proton F at contact → R_p (halved), loop F at R_p, and loop H for R_p → node. **The grid holds far fewer independent values than cells.** A match to any one cell carries the look-elsewhere count of the whole grid (3 movers × 3 forms × 10 transitions = 90 cells).
2. **The implied path in the movement law is the mover's own wavelength.** For the H form, L* = λ_H v_in/(2c) = h/(m v_in), algebraically. The column L*/(2π r_in) = ħ/(m v_in r_in) therefore **counts how many action units ħ the mover's circulation at r_in falls short of (or exceeds) one.**
   - Proton-mass movers land at 0.4–2.7: of order one action unit per circuit, comparable to the structure. That is the same family as R_p = 4ħ/(m_p c) (four action relays, FLM07).
   - Electron movers land at 750–5000 circuits: the electron would have to tour the proton's ladder thousands of times for the movement law's path to be physical.
   - **This is the one structural discriminator among movers the map supplies without any observed data.** It favours a proton-mass circulation (or a loop of it) on the proton's own ladder, and disfavours the electron there. The electron belongs on hydrogen's ladder.
3. **At z = 1 (Ѻ_p), F = B = m c².** Full movement at v = c equals the mover's rest energy: 0.511 MeV for the electron, 938.27 MeV for the proton. That is the definition of the c-boundary in movement terms, not a prediction.
4. **Hydrogen's ladder at the same stations gives MeV-scale electron movements** (0.43–4.6 MeV in the H form). These are the nuclear-gamma band and the NP17 seat unit (0.856 MeV at R_p). The proton's own ladder gives tens to hundreds of MeV for proton-mass movers.
5. **Shift reading.** Emission at nuclear contact sits at z_p = 9.2% on the proton's ladder but at z_H = 167% on hydrogen's. **The hydrogen depth dominates any line shift at nuclear scale**, and it lies beyond hydrogen's c-boundary (the flipped regime of Harvey's 2026-10-11/12 proposal).

## 3. What a single test must fix before any observed value is loaded
- One mover. Identity 2 points to a proton-mass circulation, or a loop of it.
- One form (F, H or B).
- One transition (where the mover comes from and lands).
- The observable: a gamma line, a resonance energy, or a line shift. Then one comparison, with the whole-grid look-elsewhere count of 90 stated.
