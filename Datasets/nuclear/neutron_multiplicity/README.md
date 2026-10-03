# Prompt-neutron multiplicity ν(A) cache — per-fragment, three fissioning systems

*Pulled 2026-10-01, direct, for the reorganisation/sawtooth hypothesis (ν as the count of
D/T units that fail to find an admissible seat after flay, tested against `laws.hpp`
`magic_numbers` shell closures). Source: IAEA EXFOR (`www-nds.iaea.org/exfor`), fetched via
the `X4sGetSubent` plain-text servlet (`?subID=<subentry>`, no `reqx`/`plus` params — those
trigger the HTML-wrapped rendering, not the raw X4 text). Parsed with a local script that
normalises EXFOR's split-exponent number format (`.935  E-01` → `0.0935`); no values were
read off a plotted curve.*

## Files

| file | reaction | EXFOR entry/subent | A range | points | status |
|---|---|---|---|---|---|
| `Nishio1998_U235_nth_f_nuA.csv` | ²³⁵U(n_th,f) | 22464 / 004 | 76–112, 126–154 (gap: low statistics near symmetry) | 66 | `TABLE` — author's own table |
| `Nishio1998_U233_nth_f_nuA.csv` | ²³³U(n_th,f) | 22660 / 005 | 70–159 | 90 | `TABLE` — author's own table |
| `BudtzJorgensen1988_Cf252_sf_nuA.csv` | ²⁵²Cf(sf) | 23175 / 008 | 72.9–179.15 | 106 | `CURVE` — digitized from Fig. 11 of the paper; carries `MASS-ERR-D`/`ERR-DIG` digitizing-error terms, lower fidelity than the two `TABLE` entries |

Columns: `MASS` (fragment mass number, dimensionless), `DATA` (ν̄, particles/fission),
`ERR-S`/`DATA-ERR` (1σ statistical uncertainty; blank where EXFOR's source table omitted it).

## References

- K. Nishio, Y. Nakagome, H. Yamamoto, I. Kimura, *Multiplicity and energy of neutrons from
  ²³⁵U(n_th,f) fission fragments*, Nucl. Phys. A **632**, 540 (1998).
  DOI: 10.1016/S0375-9474(98)00008-6
- K. Nishio, M. Nakashima, I. Kimura, Y. Nakagome, *Multi-parametric measurement of prompt
  neutrons and fission fragments for ²³³U(n_th,f)*, J. Nucl. Sci. Technol. **35**, 631 (1998).
  DOI: 10.1080/18811248.1998.9733919
- C. Budtz-Jørgensen, H.-H. Knitter, *Simultaneous investigation of fission fragments and
  neutrons in ²⁵²Cf(SF)*, Nucl. Phys. A **490**, 307 (1988).

## Why these three

²³⁵U(n_th,f) and ²³³U(n_th,f) are both neutron-induced, same experimental group/method
(KURRI, TOF+coincidence) — a same-mechanism pair. ²⁵²Cf(sf) is spontaneous fission, a
different compound-nucleus formation with no incident particle — the genuine cross-mechanism
held-out system. All three place their ν(A) minimum near the N=82 shell region (U-235 ≈ A130,
U-233 ≈ A127–130, Cf-252 ≈ A130), consistent with the T12 closure in `laws.hpp`
`magic_numbers` — that much is a literature fact independent of any fit.

## What this does NOT yet resolve

Not superseded and still open before any fit is pre-registered: **"unseated nucleons" has no
precise definition on file.** `laws.hpp` has `magic_numbers[7] = {2,8,20,28,50,82,126}`,
`deuteron_tiers[5]`, `triton_shell_pairs[4]` — the shell-closure scaffolding exists, but the
formula mapping a fragment's (Z,N) to a specific unseated-nucleon count (and hence to a
predicted ν) is not yet written down anywhere in the repo. That has to be pinned and
pre-registered before this cache is used to fit or test anything, per gateway procedure.

## Provenance / integrity

sha256(12) + byte counts in `Datasets/MANIFEST.md`. Fetched via `curl` directly (not the
WebFetch tool, which returned HTTP 402 against this IAEA servlet for reasons not diagnosed —
curl with a standard browser User-Agent succeeded cleanly).
