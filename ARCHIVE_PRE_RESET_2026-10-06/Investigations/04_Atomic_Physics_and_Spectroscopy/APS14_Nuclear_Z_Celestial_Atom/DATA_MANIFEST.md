# APS14 Data Manifest

All forward-model targets are external measured values or explicit `NO_DATA`.
Generated predictions are never inputs.

| File | SHA256 | Status |
|---|---|---|
| `data/covalent_radii.csv` | `3dfba82351cf7efc86ecf6db865f387828ed7ae4895cdd1c376963d984421051` | cached input |
| `data/elements.csv` | `3bc9b567e82a473336386c1f0ecb08d9d0e4f7cc8459c34af9dc08a5f69d89fd` | cached input |
| `data/ionisation.csv` | `068d8bf31de6b3f63c023e9ef99e773732f60dc7abc33fed1deeb96b52e73a6f` | cached input |
| `data/raw/horton_elements.csv` | `3ffb2b448805480be685dcf5cb59cce2693e7bd922f6157fb347e1419990cae8` | cached input |
| `data/resonance.csv` | `785fce6d215cf022c10e91462cbb808df4db083af25a7158f71207402167cc5c` | cached input |

## Sources

- Sequential IE: repository JSON compiled from NIST/CRC.
- Configurations and resonance lines: APS01 measured columns.
- Covalent radii: Cordero et al., Dalton Trans. 2008, DOI 10.1039/B801115J.
- Raw NIST ASD responses are discovery cache only; the untouched scored
  resonance set is the APS01 measured comparison corpus.
- Zn absent sequential entries are `NO_DATA`, not zeros or fitted values.
