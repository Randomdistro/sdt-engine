# GOM25 Solar Propagation Manifest

**Retrieved:** 2026-08-07. **Consumers:**
`GOM25_Solar_Depth_Propagation_Audit/`, `GOM26_Solar_Koppa_Orbital_Invariant/`,
`GOM27_Solar_Deflection_Shared_Profile/`.

All files are byte-for-byte retrievals in `raw/`; none has been transformed.
The audit instrument verifies every listed SHA-256 before parsing it.

| File | Source URL | Data class and dependency | SHA-256 | Bytes |
|---|---|---|---|---:|
| `raw/jpl_horizons_emb_sun_vectors_2025.csv` | Horizons EMB(3) vs Sun(`500@10`), 2025-01-01→2026-01-01, step 14 d | JPL DE441 state vectors; processed observational ephemeris | `99570b90b814143af450892f7ee960ab26baf125f3dde63ab4ff28fd44adc47e` | 10,537 |
| `raw/jpl_horizons_emb_sun_vectors_2024.csv` | Horizons header: EMB(3) vs Sun(10), DE441, 2024-01-01→2025-01-01, 14 d | `MODEL_PROCESSED_OBSERVATION`; present on disk at audit discovery. Header, interval, center, and row-count accepted for pre-registered GOM26 C4 only; original transfer actor and exact request URL are not locally retained. | `c194718c09f3ed4d18e4c3397226f2304b1d1a9c9aeb15cc2289e0d3ea5c319f` | 10,537 |
| `raw/jpl_horizons_emb_WRONG_CENTER_earth_2024.csv` | Horizons with `CENTER=10` (resolved to Earth 399) | Rejected fetch retained as provenance; not admissible for solar depth | `3498ac833657c31885b4449d70f1fec191b1a1662b8e4a37dbbd68b70eb5eaf6` | 10,727 |
| `raw/iau_2015_resolution_b3.pdf` | `https://arxiv.org/pdf/1510.07674` | IAU nominal conversion-radius source; conventional scale | `a4a38ecf4ab6ac71a38780456beffbc43c17c98ed320e82585a127057e498417` | 39,218 |
| `raw/haberreiter_solar_radius_2008.pdf` | `https://arxiv.org/pdf/0711.2392` | photospheric radius analysis cited by IAU B3 | `e7251f224e02286bcdce682e820a74d67ba9e0b8590957d156825c7de08c6be8` | 189,759 |
| `raw/harps_lfc_solar_redshift_2020.pdf` | `https://arxiv.org/pdf/2009.10558` | HARPS-LFC primary article | `3141bb0c56d9c26eb7f540447538a49c1cbe6f030593b145572271fb7a67ca50` | 3,007,351 |
| `raw/harps_lfc_cds_ReadMe.txt` | CDS J/A+A/643/A146 ReadMe | CDS schema | `bb134a95206bc832a313cc4eb2e18bea5c43a1d884bb0955b3797fe71fe52372` | 10,393 |
| `raw/harps_lfc_tablea1.dat` | CDS tablea1 | 188 line shifts; lab-λ dependencies | `1b662d02add6dcec4457aaa677e42ef567c18ab8ff72b3e07a3b09bdff199a14` | 14,288 |
| `raw/harps_lfc_tablea2.dat` | CDS tablea2 | 97 global shifts; CO5BOLD 3D-atmosphere dependency | `70be075001f8ae8401b5be994eebf42b4c8cac791338d856d957a8531a96ebca` | 7,275 |
| `raw/cassini_sce1_aareadme.txt` | PDS SCE1 aareadme | archive organisation | `c90ce316b64d3245d26279b1e371351e3042e7f34f76648d3b934388e976cc15` | 16,189 |
| `raw/cassini_sce1_cors0021_cumindex.tab` | PDS cumindex | file index | `25db333fb215c549360af3ac420f22b24b84d05f758fc5419a6edf1810399a00` | 17,286 |
| `raw/cassini_sce1_157_tdf.lbl` | PDS TDF label | binary-record definition | `b64981fb2c4b2e39d4fdd936753ff0fc11ece50e49c4083756fb620bf6e45081` | 90,851 |
| `raw/cassini_sce1_157_tdf.tdf` | PDS ATDF binary | primary tracking data; frozen for decoder readiness, not a residual target | `354d6904bc19431894a921df4a9f9b8ca95fca7d490a8cb03dd8819f0164be30` | 18,668,160 |
| `raw/cassini_trk_2_25_tdf_unpack.pdf` | `https://pds-geosciences.wustl.edu/radiosciencedocs/urn-nasa-pds-radiosci_documentation/DSN_TRK-2-25/tdf_unpack.pdf` | PDS Radio Science decoder grammar and examples; tool documentation, not observational data | `2a826779dfa96bfe39658711e936eb156e324ce2c1c41cd526c4b93588bcc33a` | 3,973,132 |
| `raw/cassini_rss_sis_io_ar_021.txt` | PDS CORS0021 `document/casrssis.txt` | archive SIS; identifies TDF as TRK-2-25 and required ancillary products | `daa759b2338fc4ca53d7474d7c17f83a1068470c0c5a00bcc17cf2d17e5ad84b` | 309,479 |
| `raw/cassini_document_directory_info.txt` | PDS CORS0021 `document/docinfo.txt` | document-directory index; verifies archived documentation availability | `7b87dba2f1fe65d16e9de52b2eed2dcbbbc0375a9b4670c4570384d92aac69ee` | 1,173 |
| `raw/cassini_sce1_157_odf.odf` | PDS CORS0021 SCE1_157 ODF binary | Orbit Data File sample; 8064-byte blocks; decoder fixture, not residual target | `c2ea51d9b5e795bd3eb9b4f1c5174cc44325080623188dce5e01c0ea914bfaf7` | 274,176 |
| `raw/cassini_sce1_157_odf.lbl` | paired PDS ODF label | schema | `b27da74ca62187475860e8214c2b76b8b69af760bbe44d27aac93d1c1a5593bf` | 54,675 |
| `raw/fomalont_vlba_deflection_2009.pdf` | `https://arxiv.org/pdf/0904.3992` | VLBA solar deflection paper; Table 4 is (γ−1) residual after GR correlator | `66c1f9a90b3b5481d04b9ecc36f8ee4bd3a4a39b7f44b2c00042b4f23275fb6b` | 225,755 |
| `raw/fomalont_vlba_2009_ar5iv.html` | `https://ar5iv.labs.arxiv.org/html/0904.3992` | HTML tables for GOM26b elongation ledger | `bb970a51d97cb171fa37ebd6910dd8fcc7b361b07776421d9c24f9bdaba0c9ce` | 402,992 |
| `raw/trk225_tdf_unpack.pdf` | duplicate byte-copy of `cassini_trk_2_25_tdf_unpack.pdf` | same SHA-256; retained path alias from Iteration 3 fetch | `2a826779dfa96bfe39658711e936eb156e324ce2c1c41cd526c4b93588bcc33a` | 3,973,132 |
| `raw/nrao_bf080_obscore_catalogue.csv` | NRAO TAP `tap_schema.obscore`, pre-registered query in `GOM27_D5_BF080_CATALOG_EXTRACT.md` | primary archive catalogue metadata for public VLBA BF080 products; provenance/access only, not a deflection observable | `d5116e07f356015ae4211b0842c6d8b992af87adc41e98c50a46a2172688497d` | 2,116,407 |
| `raw/nrao_vlba_data_retrieval.html` | `https://science.nrao.edu/facilities/vlba/data-archive/index` | NRAO archive access documentation; raw VLBA format/retrieval requirements, not an observational input | `f4a4405297dd1fe72ab6dc89417e80dba96889a6e1b2a9632ad5079d167d9112` | 41,171 |
| `raw/nrao_tap_scripted_access.html` | `https://science.nrao.edu/facilities/vla/archive/scripted-access-to-the-nrao-archive` | NRAO TAP query documentation; metadata access limitation, not an observational input | `74264f370f81db999d6e3d4249f4711476cba4b4178062b123da24fe8372b80c` | 41,719 |
| `raw/nrao_bf080_file3_product_details.json` | NRAO Archive Service `restapi_product_details_view?sdm_id=VLBA_VSN005016_file3.uvfits` | public raw-product metadata for the first pre-registered BF080 execution block; scan/provenance only, not downloaded UVFITS data | `2c1908cb9c1ce482f21100a9efde058a2a18bf0da7c35359abf84a5be0ae605b` | 29,467 |

| `raw/dsn_trk-2-18.1996-08-15.pdf` | `https://pds-geosciences.wustl.edu/radiosciencedocs/urn-nasa-pds-radiosci_documentation/dsn_trk-2-18/dsn_trk-2-18.1996-08-15.pdf` | PDS technical interface candidate for the frozen label's 1996 revision claim; documentation only, not observational evidence | `d9f1ad6b3b2e3a57d77dc45929a06a6f73a2c14131fa0d2e2e66ae2c7fcf5e2c` | 1,164,899 |
| `raw/dsn_trk-2-18.1996-08-15.xml` | `https://pds-geosciences.wustl.edu/radiosciencedocs/urn-nasa-pds-radiosci_documentation/dsn_trk-2-18/dsn_trk-2-18.1996-08-15.xml` | PDS4 product label for the 1996 candidate; technical metadata only | `b3f0632343994421aeac1436130544bd1c0e97d3ade16e5f16004cc09a2367d9` | 2,742 |
| `raw/dsn_trk-2-18.2000-06-15.pdf` | `https://pds-geosciences.wustl.edu/radiosciencedocs/urn-nasa-pds-radiosci_documentation/dsn_trk-2-18/dsn_trk-2-18.2000-06-15.pdf` | PDS technical interface candidate cited by the frozen Cassini SIS; documentation only, not observational evidence | `59c45204b231d5c08e8918038a4c605348d9722487664cf73325050843c77c46` | 274,301 |
| `raw/dsn_trk-2-18.2000-06-15.xml` | `https://pds-geosciences.wustl.edu/radiosciencedocs/urn-nasa-pds-radiosci_documentation/dsn_trk-2-18/dsn_trk-2-18.2000-06-15.xml` | PDS4 product label for the 2000 candidate; technical metadata only | `56adae070cad6304530a347d3fdc93e9f13d8342188f2e512b4490988bc2f8c5` | 2,711 |

| `raw/collection_dsn_trk-2-25.xml` | `https://pds-geosciences.wustl.edu/radiosciencedocs/urn-nasa-pds-radiosci_documentation/dsn_trk-2-25/collection_dsn_trk-2-25.xml` | PDS4 inventory for available TRK-2-25 technical documents; documentation metadata only | `bf142b66ceeb058a9d074dd8d0cbf9ebea44a9b88cdfda7b39d4ed248cdc839b` | 5,684 |
| `raw/dsn_trk-2-25.1996-07-31.pdf` | `https://pds-geosciences.wustl.edu/radiosciencedocs/urn-nasa-pds-radiosci_documentation/dsn_trk-2-25/dsn_trk-2-25.1996-07-31.pdf` | PDS technical grammar candidate for the TDF format conflict; documentation only, not observational evidence | `3d47f1372c76a73d1bed60f13403a402f7ded54984cf9bad53855bbfe4946dce` | 1,101,066 |
| `raw/dsn_trk-2-25.1996-07-31.xml` | `https://pds-geosciences.wustl.edu/radiosciencedocs/urn-nasa-pds-radiosci_documentation/dsn_trk-2-25/dsn_trk-2-25.1996-07-31.xml` | PDS4 product label for the 1996 TRK-2-25 candidate; technical metadata only | `322d8b1c46518987bce9af63827c48115e09806c1f9701137fd06342139e82d6` | 3,394 |

| `raw/collection_dsn_trk-2-25.csv` | `https://pds-geosciences.wustl.edu/radiosciencedocs/urn-nasa-pds-radiosci_documentation/dsn_trk-2-25/collection_dsn_trk-2-25.csv` | PDS collection member inventory for the TDF documentation audit; documentation metadata only | `ae10d3e8a41896bb2d176e76c8af2a1fbe0452b3f0930971aa7cea522b5f1522` | 540 |

## Availability and exclusions

- HARPS tables are published processed outputs; 3D-atmosphere and lab-λ steps remain dependencies.
- Horizons tables are processed ephemerides (TRACEABLE DERIVED), not raw ranging.
- `CENTER=10` without `500@` resolves to Earth(399); retained only under the WRONG_CENTER filename.
- No Cassini delay value is extracted in GOM25/GOM26/GOM27 (PENDING_DATA).
- Fomalont Table 4/5 are MODEL-PROCESSED (PPN/γ); GOM27 does not use them as absolute δ(b) targets.
- The NRAO BF080 catalogue extract establishes raw-product availability and campaign identity only; it contains no calibrated angular offsets, solar impact parameters, or uncertainty-bearing deflection values.
- NRAO access and TAP pages were inspected in browser search before their frozen copies were added to this manifest. No numerical observable, archive product, or comparison result was extracted before manifest registration; the ordering deviation is retained as procedural provenance.
- The BF080 product-detail endpoint was inspected once before its frozen JSON response was added to this manifest. The early inspection was limited to raw-product metadata; no file delivery, numeric deflection value, or calibration was requested or performed.
- The TDF label names `TRK_2_25.TXT`, but that revision is absent from the
  CORS0021 `document/` directory.  The PDS `tdf_unpack.pdf` guide is frozen as
  the public decoding reference; every field remains cross-checked against the
  paired label.
- **ODF document-resolution provenance, 2026-08-09:** the official PDS
  directory listing was inspected before the four TRK-2-18 files were frozen;
  discovery identified filenames, revision dates, and byte counts only. The
  files were then downloaded, checksummed, and registered here before any body
  text was opened. No raw ODF observable byte, observable value, residual, or
  physical inference was accessed during discovery or retrieval.
- **TDF document-resolution provenance, 2026-08-09:** the official PDS
  directory listing was inspected before the three TRK-2-25 files were frozen;
  discovery identified filenames, revision dates, and byte counts only. The
  files were then downloaded, checksummed, and registered here before any body
  text was opened. No raw TDF observable byte, observable value, residual, or
  physical inference was accessed during discovery or retrieval.
- **Procedural note, 2026-08-07:** these three decoder documents were
  downloaded, checksum-verified, and inspected for record-type definitions
  immediately before this manifest entry was added.  This manifest-ordering
  deviation did not extract an observational value or a physical residual.
