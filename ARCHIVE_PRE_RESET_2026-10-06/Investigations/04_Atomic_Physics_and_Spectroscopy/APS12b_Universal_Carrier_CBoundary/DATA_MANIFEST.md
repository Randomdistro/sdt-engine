# APS12b Data Manifest

**Collection date:** 2026-08-13  
**Isolation:** no APS12 or APS12a generated file was read.

## Processed corpora

### `data/atomic_lines.csv`

- Rows: 52
- SHA256:
  `daff61572155489e1ac85e8f0add1b58c73c65e0db9f194e1f1455ab5e22a75e`
- H I lines: 14 (5 train, 9 held out)
- He II / Li III lines: 6 element-held-out rows
- Hydrogenic series limits: 28, Z=2–29, from the final ionisation energy
  in `Datasets/nuclear/ionisation_energies.json`
- Multi-electron final hold-out: He I, Be I, Na I, Fe XXV

The H, He II, and Li III wavelengths are the NIST ASD comparison columns
cached by APS01. APS01 predictions are not read. The series-limit corpus is
measured ionisation energy, not a calculated line wavelength. Zn has no final
IE in the cached ladder and remains absent rather than being imputed.

### `data/nuclear_radii.csv`

- Rows: 908 measured positive-radius nuclides
- SHA256:
  `afd041057c8fbda58aec7ef460229dc6b99928f6f9bbf02ca45607bcfba00939`
- Source:
  `Datasets/nuclear/IAEA_ground_states_radii.csv`
- Upstream provenance: IAEA LiveChart ground states / Angeli–Marinova radii

The radius column is measured RMS radius. It is used only for the geometric
ratio `beta=R/(q Z r_e)`, not as a spectral fit input.

### `data/gamma_transitions.csv`

- Rows: 3,576 adopted gamma transitions
- SHA256:
  `0c4bf4e70452bcfdcf175438bc437e7d23ddc3fc94cad5bc7276f7f2bf8552bb`
- Rows with total conversion coefficient: 639
- Rows with multipolarity: 1,247
- Rows with matched measured radius: 3,576
- Source: IAEA LiveChart API, ENSDF adopted gamma datasets
- Endpoint:
  `https://nds.iaea.org/relnsd/v1/data?fields=gammas&nuclides=<nuclide>`

Nuclides: C-12, O-16, Mg-24, Ca-40, Fe-57, Ni-60, Zr-90, Sn-119, Ba-137,
Sm-152, Au-197, Pb-208, Am-241.

Raw API responses are retained under `data/raw/`.

## Gamma interpretation limits

`relative_intensity` is an ENSDF transition intensity within an adopted level
scheme. It is evidence that gamma emission is observed, but it is not by
itself an absolute escape probability.

For rows with total internal-conversion coefficient `ICC`, APS12b computes
`f_gamma=1/(1+ICC)`. This is a gamma-versus-conversion branch fraction for the
transition. It is suitable for a calibrated branching benchmark once
multipolarity is controlled, but it does not measure photons absorbed after
leaving the nucleus.

The strict-opacity claim is stronger: it predicts no direct gamma transition
from a source inside the boundary. The existence of evaluated gamma
transitions is therefore sufficient to test that strict form.

## Collector

`collect_aps12b_data.py` reproduces all three processed files and saves the raw
IAEA responses. It uses a browser-identifying User-Agent because the IAEA
endpoint rejects the Python default User-Agent.
