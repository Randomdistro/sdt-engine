# E13: Charge-State EC Rate Scan (Ge-68)

> Source: [INV 17 §10.2](../ATOMICUS/EC%20Investigations/INVESTIGATION_17_Spallation_Damage_EC_Repair.md)
> SDT Finding: #29, #31, #32

---

## 1. Background

Ge-68 is a spallation product created by Ga-69(p,2n)Ge-68. The
reaction ejects 2 neutrons from the outermost neutron positions of
the target nucleus. The resulting Ge-68 then undergoes 2 successive
EC events (Ge-68 → Ga-68 → Zn-68), restoring the neutron count
to its original value (N=38).

SDT analysis indicates the neutron vacancies are at outer nuclear
shell positions (4p/4s region), not at the 1s core. However, GSI
data on H-like ions show that K-shell electrons dominate EC rate
regardless of vacancy position. This creates a diagnostic problem:
the L/K capture ratio does not resolve vacancy position because it
is dominated by Z-dependent atomic physics.

A charge-state scan may reveal secondary coupling between outer
electrons and the nuclear rearrangement mechanism.

## 2. SDT Prediction

If the outer electron at the damaged nuclear position participates
in the rearrangement coupling (even though the K-shell electron
performs the capture), then stripping the corresponding outer
electron should produce a measurable discontinuity in the EC rate.

Predicted rate profile:

```text
Charge state:    0     4+     10+    30+    31+    32+
Electrons:      32     28      22      2      1      0
Shells stripped: none  4p     4p+4s  L+M+N  K(1)   ALL
                              +3d
Standard model: 100%  ~100%  ~100%  ~91%   ~45%    0%
SDT (if 4p      100%  <100%  <100%  ~91%   ~45%    0%
 coupled):              ↑
              possible step at 4p ionisation
```

**Null hypothesis**: EC rate tracks ONLY the K-shell electron
density at the nucleus. No discontinuity at outer shell stripping.
The rate is flat until K-shell stripping begins.

**SDT hypothesis**: A secondary rate step appears at the charge
state corresponding to the damaged nuclear position (~Ge⁴⁺),
indicating the outer electron participates in the repair coupling.

## 3. Observable

Measure the EC half-life of Ge-68 at the following charge states:
- Ge⁰ (neutral, reference)
- Ge⁴⁺ (4p electrons stripped)
- Ge¹⁰⁺ (4p + 4s stripped)
- Ge¹⁴⁺ (4p + 4s + 3d partially stripped)
- Ge³⁰⁺ (He-like, only 1s² remaining)
- Ge³¹⁺ (H-like, single 1s electron)
- Ge³²⁺ (bare, if achievable)

Compare the measured half-lives. A statistically significant
deviation from the standard smooth scaling (proportional to total
s-electron density at r=0) at any intermediate charge state would
indicate outer-shell coupling.

## 4. Apparatus

- Ion source capable of producing Ge-68 at controlled charge states
- Storage ring or ion trap to contain ions for time periods
  comparable to the EC half-life (t½ = 270.9 d for neutral Ge-68)
- Particle detector to identify EC events (daughter Ga-68 has
  different mass-to-charge ratio)
- Facility: GSI/FAIR (Darmstadt) ESR or CRYRING, or ISOLDE (CERN)

## 5. Feasibility

**Difficulty: HIGH**

- Ge-68 half-life (270.9 d) is very long for storage ring
  measurements; requires extended beam storage or a different
  time-domain approach
- Intermediate charge states (Ge⁴⁺ to Ge¹⁴⁺) are straightforward
  to produce but the expected rate change may be < 1%, requiring
  extreme statistical precision
- The H-like (Ge³¹⁺) and bare (Ge³²⁺) measurements are feasible
  at GSI/FAIR but have not been performed for this isotope
- Existing GSI infrastructure can produce and store highly charged
  Ge ions; Ge-68 sources are widely available (PET generator waste)

## 6. Existing Constraints

| Measurement | Ion | Result | Source |
|------------|-----|--------|--------|
| Ho-163⁶⁷⁺ (bare) | Z=67 | EC halted entirely | GSI |
| Pr-140⁵⁸⁺ (H-like) | Z=59 | EC ≈ P_K of neutral | GSI |
| Pm-142⁶⁰⁺ (H-like) | Z=61 | EC ≈ P_K of neutral | GSI |
| Dy-163⁶⁶⁺ (bare) | Z=66 | Bound-state β⁻ appears | GSI |

No measurements exist for INTERMEDIATE charge states of any
spallation-produced EC isotope. The proposed experiment fills
a gap in the existing data.

## 7. Impact

- **If step detected**: Confirms outer-shell coupling in nuclear
  rearrangement. Opens a diagnostic pathway for identifying damage
  positions in spallation products. Direct implications for targeted
  nuclear medicine (ionisation-controlled dose delivery).
- **If no step detected**: Confirms that EC is purely a K-shell
  atomic process with no nuclear position sensitivity in the
  electron sector. The vacancy position must be diagnosed by
  other means (gamma spectroscopy, nuclear moments).
