# NP12b observable-admissibility audit — amendment 01

**Date:** 2026-08-09
**Reason:** A repository-wide static search, performed after the original audit's source gate, located a prior NP12 implementation containing a `sqrt(3/5)` conversion applied to the same close-pack form.  This amendment freezes those historical artifacts before their contents are inspected.

| Additional artifact | Role | Permitted use |
|---|---|---|
| `Investigations/05_Nuclear_Physics/NP12_Nuclear_Charge_Radius_Scaling/np12_radius_scaling.py` | identifies whether a boundary-to-RMS conversion was previously stated | static provenance and observable-definition audit only |
| `Investigations/05_Nuclear_Physics/NP12_Nuclear_Charge_Radius_Scaling/NP12_VERDICT.md` | records historical interpretation of that conversion | static provenance and observable-definition audit only |

Neither artifact may set a numerical pass/fail result, introduce a fitted coefficient, or substitute a rival model.  The NP12b numerical reconstruction remains defined solely by the pre-registration and the hash-registered IAEA CSV.  If the added artifacts show a transformation, the audit will determine only whether it is a frozen, executable SDT-native derivation; a convention or an asserted density profile does not satisfy that requirement.
