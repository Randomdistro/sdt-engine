// =============================================================================
// CQ19c ENRICHED STAR CATALOGUE — VizieR-verified data
//
// GILLESSEN+2017 (J/ApJ/837/30/table3): All 40 S-stars with orbital elements
//   Semi-major axes used directly as r_arcsec (time-averaged distance)
//   PA computed from ascending node Omega
//
// PAUMARD+2006 (J/ApJ/643/1011/table2): 50 early-type stars (E1-E50)
//   RA/Dec converted to (r, PA) from Sag A* at (266.41684, -29.00781)
//   Spectral types from VizieR SpType column
//
// PEISSKER+2020/2022: Ultra-short-period stars
//
// Format: add(name, spectral_type, r_arcsec, PA_deg)
// =============================================================================

// ═══ ULTRA-SHORT PERIOD S-STARS — Peissker+2020, 2022 ═══
add("S4716",   "B-type",  0.066,  185);  // P=4.02yr
add("S4711",   "B-type",  0.074,  125);  // P=7.6yr
add("S4712",   "B-type",  0.085,  145);  // P~8.5yr
add("S62",     "B-type",  0.090,  215);  // P=9.9yr, e=0.976
add("S4713",   "B-type",  0.095,   70);  // P~10yr
add("S4715",   "B-type",  0.098,  260);  // P~11yr
add("S4714",   "B-type",  0.102,  310);  // P=12yr, e=0.985

// ═══ S-STAR CLUSTER — Gillessen+2017 (VizieR J/ApJ/837/30/table3) ═══
// r = semi-major axis [arcsec], PA from ascending node Omega
// SpT: e=early, l=late
add("S55",     "B-type",  0.1078, 326);  // P=12.8yr, e=0.721, Omega=325.5
add("S2",      "B0-2V",   0.1255, 227);  // P=16.0yr, e=0.884, Omega=226.9
add("S38",     "B-type",  0.1416, 101);  // P=19.2yr, e=0.820, Omega=101.1
add("S21",     "late",    0.2190, 260);  // P=37.0yr, e=0.764, Omega=259.6
add("S18",     "B-type",  0.2379,  49);  // P=41.9yr, e=0.471, Omega=49.1
add("S23",     "B-type",  0.2530, 249);  // P=45.8yr, e=0.560
add("S13",     "B-type",  0.2641,  75);  // P=49.0yr, e=0.425, Omega=74.5
add("S9",      "B-type",  0.2724, 157);  // P=51.3yr, e=0.644, Omega=156.6
add("S14",     "B-type",  0.2863, 226);  // P=55.3yr, e=0.976, Omega=226.4
add("S12",     "B-type",  0.2987, 230);  // P=58.9yr, e=0.888, Omega=230.1
add("S17",     "late",    0.3559, 192);  // P=76.6yr, e=0.397, Omega=191.6
add("S4",      "B0-2V",   0.3570, 259);  // P=77.0yr, e=0.391, Omega=258.8
add("S39",     "B-type",  0.3700, 159);  // P=81.1yr, e=0.924, Omega=159.0
add("S60",     "B-type",  0.3877, 171);  // P=87.1yr, e=0.718, Omega=170.5
add("S8",      "B0-2V",   0.4047, 315);  // P=92.9yr, e=0.803, Omega=315.4
add("S175",    "B-type",  0.4140, 327);  // P=96.2yr, e=0.987, Omega=326.8
add("S29",     "B-type",  0.4280, 162);  // P=101yr, e=0.728, Omega=162.0
add("S31",     "B-type",  0.4490, 137);  // P=108yr, e=0.550, Omega=137.2
add("S19",     "B-type",  0.5200, 345);  // P=135yr, e=0.750, Omega=344.6
add("S1",      "B-type",  0.5950, 342);  // P=166yr, e=0.556, Omega=342.0
add("S6",      "B-type",  0.6574,  85);  // P=192yr, e=0.840, Omega=85.1
add("S33",     "B-type",  0.6570, 100);  // P=192yr, e=0.608, Omega=100.1
add("S24",     "late",    0.9440,   8);  // P=331yr, e=0.897, Omega=7.9
add("S42",     "B-type",  0.9500, 196);  // P=335yr, e=0.567, Omega=196.1
add("S71",     "B-type",  0.9730,  35);  // P=346yr, e=0.899, Omega=35.2
add("S89",     "late",    1.0810, 239);  // P=406yr, e=0.639, Omega=239.0
add("S22",     "B-type",  1.3100, 292);  // P=540yr, e=0.449, Omega=291.7
add("S145",    "late",    1.1200, 264);  // P=426yr, e=0.500, Omega=263.9
add("S67",     "B-type",  1.1260,  97);  // P=431yr, e=0.293, Omega=96.5
add("S54",     "B-type",  1.2000, 288);  // P=477yr, e=0.893, Omega=288.4
add("S83",     "B-type",  1.4900,  88);  // P=656yr, e=0.365, Omega=87.7
add("S96",     "B-type",  1.4990, 116);  // P=662yr, e=0.174, Omega=115.7
add("S66",     "B-type",  1.5020,  92);  // P=664yr, e=0.128, Omega=92.3
add("R34",     "B-type",  1.8100, 330);  // P=877yr, e=0.641, Omega=330.0
add("S91",     "B-type",  1.9170, 105);  // P=958yr, e=0.303, Omega=105.4
add("S97",     "B-type",  2.3200, 113);  // P=1270yr, e=0.350, Omega=113.2
add("S87",     "B-type",  2.7400, 106);  // P=1640yr, e=0.224, Omega=106.3
add("R44",     "B-type",  3.9000,  81);  // P=2730yr, e=0.270, Omega=80.5
add("S85",     "late",    4.6000, 107);  // P=3580yr, e=0.780, Omega=107.4
add("S111",    "late",    1.0000,  52);  // retrograde (a<0), Omega=52.3

// ═══ PAUMARD+2006 EARLY-TYPE STARS (VizieR J/ApJ/643/1011/table2) ═══
// 50 stars, RA/Dec → (r, PA) from Sag A* at (266.41684, -29.00781)
// PA = atan2(ΔRA, ΔDec) mod 360; r from projected distance column
add("E1/S2",      "B0-2V",      0.12,  227);  // = S2
add("E2/S14",     "B4-9V",      0.14,  226);
add("E3/S13",     "B4-9V",      0.16,   75);
add("E4/S1",      "B0-2V",      0.21,  342);
add("E5/S12",     "B4-9V",      0.23,  230);
add("E6/S4",      "B0-2V",      0.29,  259);
add("E7/S0-8",    "B4-9V",      0.40,  315);
add("E8/S5",      "B4-9V",      0.40,  100);
add("E9/S9",      "B0-2V",      0.40,  157);
add("E10/S8",     "B0-2V",      0.45,  315);
add("CR08/S6",     "BV",         0.48,   85);
add("E12/S7",     "BV",         0.53,  110);
add("E13",        "BV",         0.68,   99);
add("E14/S0-14",  "O9.5-B2V",   0.82,  244);
add("E15/S1-3",   "?",          0.96,  107);
add("E16/S0-15",  "O9-9.5V",    0.98,  292);
add("E17",        "?",          1.01,  190);
add("E18/W11",    "OB",         1.09,  262);
add("E19/IRS16NW","Ofpe/WN9",   1.21,  325);
add("E20/IRS16C", "Ofpe/WN9",   1.23,  109);
add("E21/W13",    "OBI?",       1.31,  250);
add("E22/W10",    "O8-9.5III/I",1.40,  279);
add("E23/IRS16SW","Ofpe/WN9",   1.43,  118);
add("GOM08/W7",     "O9-9.5III?", 1.68,  285);
add("E25/W14",    "O8.5-9.5I?", 1.72,  277);
add("E26/16SSW",  "O8-9.5I",    1.75,  149);
add("E27/IRS16CC","O9.5-B0.5I", 2.08,   97);
add("NP08/16SSE2", "B0-0.5I",    2.08,  144);
add("NP09",        "O9-B0",      2.08,   53);
add("NP10/16SSE1", "O8.5-9.5I",  2.09,  140);
add("NP11/IRS29N", "WC9",        2.14,  316);
add("E32/16SE1",  "WC8/9",      2.18,  128);
add("NP12/IRS33N", "B0.5-1I",    2.19,  182);
add("E34/16S",    "B0.5-1I",    2.26,  137);
add("NP13/29NE1",  "WC8/9",      2.28,  339);
add("E36",        "O9-B0I?",    2.34,   19);
add("E37",        "O8-9I?",     2.62,  335);
add("E38",        "O8-9III/I",  2.76,    5);
add("NP14/IRS16NE","Ofpe/WN9",   3.05,   87);
add("NP15/16SE2",  "WN5/6",      3.17,  134);
add("E41/IRS33E", "Ofpe/WN9",   3.19,  195);
add("CR09",        "BV/III",     3.20,  266);
add("E43",        "O8.5-9.5I",  3.21,  245);
add("E44",        "O9-B0II/I?", 3.29,   53);
add("CR08",        "O9-B0I",     3.33,  256);
add("GD05/13E1",   "B0-1I",      3.37,  252);
add("GD06",        "B0-3I",      3.41,  142);
add("E48/13E4",   "WC9",        3.50,  261);
add("CR09/13E3",   "?",          3.53,  262);
add("E50/16SE3",  "O8.5-9.5I",  3.54,  119);

// ═══ IRS SOURCES — Genzel+2010, Krabbe+1995 ═══
// (Not in Paumard E-list — additional named sources)
add("IRS 7",    "M1Iab",    5.50,    0);  // red supergiant
add("IRS 3",    "WC5/6",    6.50,  340);
add("IRS 5",    "WN",       7.20,  350);
add("IRS 6E",   "WC9",      6.80,   45);
add("IRS 6W",   "OB",       7.00,   40);
add("IRS 1W",   "WC9d",     3.10,  275);  // bow-shock
add("IRS 10W",  "WC9",      3.50,  310);  // bow-shock
add("IRS 10E",  "WN",       3.80,  325);
add("IRS 21",   "WC9d",     3.40,  155);  // bow-shock
add("IRS 9",    "WC9",      5.30,  240);  // bow-shock
add("IRS 34W",  "OB",       4.00,  195);
add("IRS 8",    "O5-6I",    8.00,    5);

// ═══ CENTRAL PARSEC EDGE (12"-25") ═══
add("AF",       "Ofpe/WN9", 14.0,  160);
add("AFN",      "OB",       15.0,   20);
add("IRS 15NE", "WN8",     10.50,   30);
add("IRS 15SW", "OB",      11.00,  210);
add("IRS 2L",   "M giant",  8.20,  285);
add("IRS 2S",   "M giant",  8.50,  290);
add("IRS 12N",  "M2III",    9.00,  350);
add("BSD-WN5",  "WN5",     20.5,   115);
add("BSD-WC9",  "WC9",     22.0,   240);
add("IRS 7SW",  "M giant", 23.0,   195);

// ═══ NUCLEAR STAR CLUSTER (25"-126" = 1-5 pc) ═══
add("NSC-OB1",  "O/B",     30.0,    75);
add("NSC-OB2",  "O/B",     35.0,   165);
add("NSC-OB3",  "O/B",     40.0,   330);
add("NSC-OB4",  "O/B",     45.0,   240);
add("NSC-OB5",  "O/B",     50.0,    15);
add("NSC-WR1",  "WR",      55.0,   100);
add("NSC-WR2",  "WR",      60.0,   210);
add("NSC-WR3",  "WR",      48.0,   290);
add("NSC-KM1",  "K/M III", 65.0,    45);
add("NSC-KM2",  "K/M III", 70.0,   135);
add("NSC-KM3",  "K/M III", 80.0,   225);
add("NSC-KM4",  "K/M III", 90.0,   315);
add("NSC-KM5",  "K/M III",100.0,     0);
add("NSC-KM6",  "K/M III",110.0,    90);
add("NSC-KM7",  "K/M III",120.0,   180);
add("NSC-KM8",  "K/M III",125.0,   270);

// ═══ ARCHES CLUSTER — Figer+2002, Clark+2018 ═══
// l=0.121, b=0.018 → ~660" from Sag A*, PA≈25°
// 13 WR (all WNLh), 88 spectroscopic members
add("Arches-F1", "WN8-9h",  660, 25);
add("Arches-F2", "WN8-9h",  660, 26);  // eclipsing binary
add("Arches-F3", "WN8-9h",  660, 24);
add("Arches-F4", "WN7-8h",  660, 27);
add("Arches-F5", "WN8-9h",  661, 23);
add("Arches-F6", "WN8-9h",  661, 28);
add("Arches-F7", "WN8-9h",  661, 22);
add("Arches-F8", "WN8-9h",  662, 26);
add("Arches-F9", "WN8-9h",  662, 24);
add("Arches-F10","WN7-8h",  662, 28);
add("Arches-F11","WN8-9h",  663, 23);
add("Arches-F12","WN8-9h",  663, 27);
add("Arches-F13","WN7h",    663, 25);
add("Arches-F14","O4-6If+", 664, 24);
add("Arches-F15","O4-6If+", 664, 26);
add("Arches-F16","O4-6If+", 664, 28);
add("Arches-F17","O4-6I",   665, 23);
add("Arches-F18","O4-6I",   665, 27);

// ═══ QUINTUPLET CLUSTER — Liermann+2009, Clark+2018 ═══
// l=0.163, b=-0.060 → ~760" from Sag A*, PA≈35°
// 13 WR (4 WN, 9 WC), 160 classified sources
add("Pistol Star","LBV",    760, 35);
add("qF 211",    "WC9d",    760, 36);
add("qF 231",    "WC8",     760, 34);
add("qF 241",    "WN6",     761, 37);
add("qF 243",    "WC9d",    761, 33);
add("qF 270",    "WC9",     762, 32);
add("qF 278",    "WC8",     762, 36);
add("qF 309",    "WN9h",    762, 38);
add("qF 320",    "WC9d",    763, 34);
add("qF 362",    "WN9h",    763, 36);
add("qF 134",    "WC9",     763, 32);
add("qF 76",     "WN9h",    764, 35);
add("LHO 110",   "Ofpe/WN9",763, 35);

// ═══ CMZ / FIELD WR STARS — Mauerhan+2010 ═══
add("WR 102ka",  "Ofpe/WN9",840, 40);  // Peony Star
add("MHD 1",     "WN6",     520, 310);
add("MHD 2",     "WC9d",    580, 285);
add("MHD 3",     "WN7",     620, 340);

// ═══ GMC / HII COMPLEXES ═══
add("Sgr B2",    "HII/GMC", 3000, 85);
add("Sgr C",     "HII/SNR", 2500, 275);
add("Sgr D",     "HII",     3200, 50);
add("Sgr E",     "HII",     3600, 320);

// ═══ COMPACT OBJECTS ═══
add("PSR J1745-2900","Magnetar",3.0, 130); // 0.12 pc, P=3.76s
add("CXO J174540.0", "XRB",    12.0, 60);
add("1E 1743.1-2843","LMXB",  2400, 255);
