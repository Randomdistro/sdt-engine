# GOM41 corpus sources — provenance (2026-10-14)

Fetched 2026-10-14 by plain HTTP GET (curl), stored unmodified. Nothing was recalled from memory; every number used in GOM41 Round 2 is read from these files by `gom41_reset_2.py`.

| file | source URL | bytes | SHA-256 | content used |
|---|---|---|---|---|
| `jpl_ssd_planet_phys_par.html` | https://ssd.jpl.nasa.gov/planets/phys_par.html | 58 244 | `e49a487947295c389ba6e5833dd8fb04b63e826d39f70c123881882096e5e68b` | JPL SSD Planetary Physical Parameters: equatorial radius, mean radius (IAU/IAG 2015, Archinal et al. 2018), sidereal rotation period (days). Mass, density, gravity columns are not used. |
| `nasa_earthfact.html` | https://nssdc.gsfc.nasa.gov/planetary/factsheet/earthfact.html | 5 490 | `1b06e3ec31249d063d40d1b38837fac89ddcd2f4b25268b38e8a6d5f413e70ef` | NASA NSSDCA Earth fact sheet: equatorial radius, polar radius, rotation period (hours); J2 row (comparison-only, read in stage 2). |
| `nasa_marsfact.html` | …/marsfact.html | 13 261 | `366b0ce9b69cbee370be904956748af954468a41b93dc71a796a986519aa8d74` | same fields |
| `nasa_jupiterfact.html` | …/jupiterfact.html | 11 195 | `9ac7835ae5387261bc02019a641bbfc8450122ffebebffea5678c3de6c54d0cb` | same fields (1-bar level radii) |
| `nasa_saturnfact.html` | …/saturnfact.html | 11 257 | `6d09ba010cacef61c8ae1a1ff137b06e5464e99461faf8f32c107419c474d06d` | same fields (1-bar level radii) |
| `nasa_uranusfact.html` | …/uranusfact.html | 10 941 | `02389139f8345a4328fc8f8956012cb72f691c6c7c2854c03c0b2512a063de81` | same fields (1-bar level radii) |
| `nasa_neptunefact.html` | …/neptunefact.html | 11 071 | `4b9166f959be2b507eea77a9eef56f4e5679b693ba75151072a28bb228f44328` | same fields (1-bar level radii) |
| `nasa_planetary_factsheet_metric.html` | https://nssdc.gsfc.nasa.gov/planetary/factsheet/ | 14 363 | `42bdc3f1dae470b85580c6ac66c353964a05d544ad2ac970a6b7d908337a6c3c` | summary table; no polar-radius row, so not used as a source (kept as the record of that check). |
| `jpl_ssd_sats_elem.html` | https://ssd.jpl.nasa.gov/sats/elem/ | 580 012 | `1e5e52225cf636b78d0ac602eb5352c5648aa025ba45d61593d824e70779dfdd` | JPL planetary satellite mean elements (epoch 2000-01-01.5): a (km) and P (days) for the satellites named in the registration. Already cached for GOM42 P1. |
| `FAILED_FETCH_404_jpl_ssd_planets_grav.html` | https://ssd.jpl.nasa.gov/planets/grav.html | 17 190 | `0809862934c17e2f8d5ceee58b1518ad27f240b9ab5482c97e95d5e6f7f4aff6` | **Not a source.** HTTP 404 error page from a guessed URL; kept (renamed) as the record of the failed attempt. |

Limits: the NASA per-planet sheets quote radii to the 1-bar level for the four giants; the JPL page quotes the same equatorial radii (IAU 2015). The J2 values in the fact sheets are rounded to the precision the sheets print, and are the comparison-only column (their own sources are not re-derived here). Every satellite elements row is a mean-element fit; the a and P of each row carry planetary-oblateness and third-body terms of order 10⁻⁴ to 10⁻³ (Moon: a few 10⁻³), which the registration's gate V1 measures rather than assumes.
