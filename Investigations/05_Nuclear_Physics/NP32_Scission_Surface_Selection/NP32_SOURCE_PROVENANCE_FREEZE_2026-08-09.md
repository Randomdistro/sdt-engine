# NP32 source-provenance freeze — 2026-08-09

This record implements the identity gate in `NP32_ELIGIBILITY_AUDIT_PRE_REGISTRATION_2026-08-09.md`.  Hashing occurred after pre-registration and before this audit parsed a fission-yield CSV.  SHA-256 values are lowercase and byte counts are exact.

| Path | Bytes | SHA-256 |
|---|---:|---|
| `PROMPT.md` | 9743 | `ccf81f26efd301c968a3a50b386061bd2b9583e96c45cef4a68a3d582ec1197b` |
| `NP32_PREDICT_PRECOMMIT_2026-07-25.md` | 3641 | `9246b48fe0b5959bd2b0c4c44057eebf4d8060e3afe66fe5239fefbe8fb72b7b` |
| `np32_predict_check.py` | 3072 | `6f995b81b405ad5764e68cc93aeefa3bb403c19626d67e482aef783a41d7fc3c` |
| `NP32_PREDICT_RESULTS_2026-07-25.md` | 6632 | `cef9ccb53a6acabe7f2126def2a2ac987ef4bffe4799e4d73ecef5960963fc5d` |
| `Datasets/nuclear/IAEA_U235_independent_FY.csv` | 121193 | `87fcd49503a56b57f98eb785183d778dbfa72551b89f2112a8898fbe0aad6c78` |
| `Datasets/nuclear/fission_yields/IAEA_233U_independent_FY.csv` | 128347 | `878e4e6c1f39fa781cc903006506f66331a4ef0ebd6a9613be30093664daca62` |
| `Datasets/nuclear/fission_yields/IAEA_239Pu_independent_FY.csv` | 98073 | `8e9272960f5405f15ac1191ad70bef338b7cdef4b65a451d3cf4426a85dcc425` |
| `Datasets/nuclear/fission_yields/IAEA_241Pu_independent_FY.csv` | 93869 | `52bbb5be8087bf6145aee289c6558e18a6a32e3bd7389fa0f9c0f7d30a383732` |
| `Datasets/nuclear/fission_yields/IAEA_237Np_independent_FY.csv` | 88035 | `a14c5e3540fef662d341e4f9e026fb0edf0a462946444379f3478c186fc220bc` |
| `Datasets/nuclear/fission_yields/IAEA_241Am_independent_FY.csv` | 100715 | `a75a4ecd510939227d4502b3b41144f557427af0905bf343eab2174e54740e6c` |
| `Datasets/nuclear/fission_yields/IAEA_238U_independent_FY.csv` | 90478 | `e602f666aeb3d9957655774be2deef05534db6d6a464de7ee4da166a8452aa4a` |
| `Datasets/nuclear/fission_yields/IAEA_232Th_independent_FY.csv` | 85712 | `6641d35d4f2c9bc66b86980fc1a6e9c37c6d16137dd3157550a8aa97f7540bc8` |

All eight yield files have the exact byte count and a SHA-256 beginning with the checksum prefix registered in `Datasets/MANIFEST.md`.  This confirms file identity only; it does not certify the underlying IAEA evaluation or turn an observational regularity into a model prediction.
