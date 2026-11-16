# Chapter 6 — State Dimensions and Metrology

*Volume I — Ontology, Geometry and Admissible States.*
Draft of 9 November 2026. Notation: $\mathrm{Om}=R/k^2$, $k=c/v$ as in the production default of `Textbook/NOTATION_LEDGER.md`. Executable companion: `Textbook/examples/ch06_state_dimensions_and_metrology.cpp`; pre-registration and captured output in `Textbook/validation/`; classification of the engine's measured constants in `Textbook/sources/MEASURED_CLASSIFICATION.md`.

## 6.1 The physical question

A reported number has a role, a unit, a reference state and a measurement chain. A speed depends on a length standard, a counting standard and the frame in which it is read. A temperature depends on the spectral variable and on whether the thing measured is a distribution or a single quantum. This chapter sets down which dimensions the book uses, how many independent dimensionless numbers the engine's seed constants leave, which stored constants are inputs, which are unit bridges and which are outputs, and how the mechanical, spectral and thermal chains connect.

## 6.2 Dimensions and the count of independent numbers

The base dimensions are mass M, length L, count T of a declared oscillator, and temperature K. The SI second is a unit bridge from the count of the caesium oscillator to the count of any other, and the kelvin is a unit bridge from a temperature to an energy through $k_B$. No dimension for electric quantities is introduced: the elementary unit $e$ is a unit bridge, and $k_ee^2$ enters the framework only through the Coulomb identity $k_ee^2=\alpha\hbar c$.

Let $Q_1\ldots Q_n$ be positive quantities and $Q_{i0}$ reference values, and write $x_i=\ln(Q_i/Q_{i0})$. Let $D$ be the $4\times n$ matrix whose column $i$ holds the exponents of $\mathrm{M},\mathrm L,\mathrm T,\mathrm K$ in $Q_i$. A change of units multiplies each $Q_i$ by a product of unit factors, so $x$ moves by a vector in the row space of $D^{\!\top}$. A product $\prod_iQ_i^{w_i}$ is unaffected by a change of units exactly when

$$D\,w=0. \tag{6.1}$$

The independent dimensionless products are the null space of $D$, and their number is $n-\operatorname{rank}D$ (the Buckingham count). A pure change of units cannot alter such a product. A physical change of state can.

**Relations of the book are homogeneous.** The instrument checked 32 relations of Chapters 1–9 and the engine's seed relations (for example $mc^2=P_{\rm conv}V_{\rm disp}/3$, $V_{\rm disp}=3m\ell_P^3c^2/\Phi$, $\Gamma=2\pi c_{\rm b}\mathrm{Om}$, $F=(\pi/4)UR_1^2R_2^2/r^2$, $P_{\rm eff}=4\alpha\hbar c/(\pi R_p^2r_e^2)$ and $a_{\rm rad}=8\pi^5k_B^4/(15h^3c^3)$). All have equal dimensions on both sides, and three deliberately wrong relations ($F=PR$, $E=mc$, $P_{\rm conv}=\Phi/\ell_P$) were flagged (test T1; the algebra was first checked on force, pressure and the half-unit exponent of a square root, V2).

**The seed has few free numbers.** The exact rational rank and null space of $D$ for four sets of seed constants gave Table 6.1 (test T2; the routine was validated on matrices of known rank and null space, V0r).

| set | quantities | rank | independent dimensionless numbers | values |
|---|---|---|---|---|
| $S_1$ | $\ell_P,\ c,\ \hbar,\ k_B,\ T_{\rm CMB}$ | 4 | 1 | $\theta=\ell_Pk_BT_{\rm CMB}/(\hbar c)=1.923723\times10^{-32}$ |
| $S_2$ | $S_1$ and $R_{\rm CMB}$ | 4 | 2 | $\theta$; $N=R_{\rm CMB}/\ell_P=5.894491\times10^{61}$ |
| $S_3$ | $c,\ \hbar,\ m_e,\ \ell_P,\ m_p$ | 3 | 2 | $m_p/m_e=1836.152673$; $\ell_Pm_ec/\hbar=4.185462\times10^{-23}$ |
| $S_4$ | $S_2\cup\{m_e,m_p,a_0,R_p\}$ | 4 | 6 | $\theta$; $\ell_Pm_ec/\hbar$; $\ell_Pm_pc/\hbar=7.685148\times10^{-20}$; $N$; $a_0/\ell_P=3.274095\times10^{24}$; $R_p/\ell_P=5.205862\times10^{19}$ |

Table 6.1. Dimension matrices of seed constants, executed. $m_p/m_e$ agrees with the CODATA 2022 value $1836.152673426$ to $2.4\times10^{-12}$.

The fine-structure constant $\alpha$ is dimensionless already and adds one more number to each set. Table 6.1 states what dimensional analysis alone allows. With the five constants of $S_1$ the state of the medium and its present boundary temperature fix one number, $\theta$, the ratio of the thermal energy $k_BT_{\rm CMB}$ to the energy $\hbar c/\ell_P$. Which of these numbers are inputs and which are outputs of the framework is not a dimensional question: the sources collapse $\hbar$, $m_e$ and $m_p$ to one mass and action seat (derivelist items 2, 5, 6), so $m_p/m_e$ is a relation within the seat and not a separate input (Chapters 18 and 56).

## 6.3 Matched operational definitions

A ratio such as $k=c/v$ is meaningful only when numerator and denominator have compatible roles. A far-frame numerator divided by a local circulation speed is a mixed comparison unless an explicit transformation connects them. The six speed roles of Chapter 3 (Table 3.0) are kept separate in every ratio, and an observable is written as a dimensionless count or ratio: counts per light-crossing, a speed over $c$, a rate over a rate.

## 6.4 Three chains

**Mechanical.** Lengths enter from atomic spectroscopy ($a_0$), from IAU definitions (the astronomical unit, the solar radius) and from the stored $\ell_P$. Speeds of bound motion are kinematic. Mass is an output of Law IV (the exclusion volume, Chapter 12). The kilogram is a unit bridge fixed by the exact value of $h$ with the metre and the second. The measured masses $m_e$ and $m_p$ are the mass seat, and the nuclear masses are measured anchors.

**Spectral.** Wavelength, frequency and energy are tied by the unit bridges $\lambda=c/\nu$, $E=h\nu$ and, for electron-volts, by $e$. The hydrogen ladder measured as a frequency and as a wavenumber returns one relay speed; the derivelist treats that spectroscopic route as primary and draws the line at $c$ as a unit bridge. The redundancies among the stored constants are checks of the stored numbers (test T3):

| relation | stored values compared | relative difference |
|---|---|---|
| $h=2\pi\hbar$ | `h`, `hbar` | $3.9\times10^{-16}$ |
| $r_e=\alpha\hbar/(m_ec)$ | `r_e` ($=\alpha^2a_0$), `alpha`, `hbar`, `m_e` | $5.2\times10^{-12}$ |
| $R_\infty=\alpha^2m_ec/(2h)$ | `R_inf` | $1.1\times10^{-11}$ |
| $\mathrm{Ry_{eV}}=hcR_\infty/e$ | `Ry_eV`, `R_inf`, `eV_to_J` | $3.8\times10^{-14}$ |
| $k_ee^2=\alpha\hbar c$ | `k_e_e2_codata`, `k_e_e2` | $7.8\times10^{-12}$ |
| $a_{\rm rad}=8\pi^5k_B^4/(15h^3c^3)$ | `a_rad` | $4.4\times10^{-6}$ |

Table 6.2. Redundancies of the stored constants, executed.

The first five agree to $10^{-11}$ or better, which is the signature of a single edition of the constants (the engine's comment records that all were aligned to CODATA 2022 on 2026-10-16). The last is the five stored digits of $a_{\rm rad}$: the stored value is $4.4\times10^{-6}$ below the computed one, and the radiation energy density, the content $\varepsilon$, the throughput $\Phi$ and $P_{\rm conv}$ inherit that shift (Chapter 4).

**Thermal.** $T_{\rm CMB}=2.7255$ K is a measured mechanical boundary state, the present convergence state, and not a fitted parameter. The energy density $u_{\rm CMB}=a_{\rm rad}T^4=4.174783\times10^{-14}$ J m$^{-3}$ equals the Planck energy density $8\pi^5(k_BT)^4/(15h^3c^3)$, obtained by quadrature of $\int_0^\infty x^3/(e^x-1)\,dx=\pi^4/15$ (validated, V3), to $4.4\times10^{-6}$ (T4). Three pressure-like quantities must not be confused: the radiation pressure $u/3=1.391594\times10^{-14}$ Pa, the engine's convergence pressure $P_{\rm conv}=Nu=2.460822\times10^{48}$ Pa, and the resistance pressure $P_{\rm conv}/3$.

A temperature read from a spectrum depends on the spectral variable. The maximum of the Planck function per unit wavelength lies at $x_\lambda=4.965114$ and per unit frequency at $x_\nu=2.821439$, in $x=hc/(\lambda k_BT)$ and $x=h\nu/(k_BT)$ respectively (roots of $(n-x)e^x=n$, validated, and found independently by golden-section search to $7\times10^{-9}$). At $T_{\rm CMB}$ the wavelength maximum is $\lambda_{\rm peak}=b/T=1.063207$ mm with $b=2.897771955\times10^{-3}$ m K, the frequency maximum is at $\nu_{\rm peak}=1.602301\times10^{11}$ per SI second (a unit bridge), whose wavelength $c/\nu_{\rm peak}=1.871012$ mm is larger by the factor $x_\lambda/x_\nu=1.759781$ (T4, to $10^{-16}$). The conversion $T_W=b/\lambda_{\rm peak}$ therefore names a convention, and a frequency maximum gives a different peak location for the same spectrum. A single energetic quantum does not define a bath temperature; a temperature fitted to a spectrum, one inferred from material populations and a branch-calibrated wavelength temperature are three records. The reference-calibrated radiation pressure $a_{\rm rad,ref}T_W^4/3$ is a conversion, not a constitutive law; if the radiation constant of a changing medium evolves, $a_{\rm rad}(S)$ must remain visible in the expression (Chapter 44).

## 6.5 What the engine's measured namespace contains

The `measured` namespace holds 47 identifiers. Membership confers no derivational status; each entry's role is the engine's own statement and is recorded in `Textbook/sources/MEASURED_CLASSIFICATION.md`, whose identifiers the instrument compared with the namespace (T5: the two sets are equal, 47 and 47).

| role | entries | count |
|---|---|---|
| unit bridge | `c`, `h`, `k_B`, `e_charge`, `eV_to_J`, `MeV_to_J` | 6 |
| mass and action seat | `hbar`, `m_e`, `m_p` | 3 |
| geometric closure with a stored number | `l_P` | 1 |
| spectroscopic derivation | `alpha` | 1 |
| measured mechanical boundary | `T_CMB` | 1 |
| measured anchor | `a_0`, `R_p`, `m_n`, `m_d`, `m_t`, `m_He3`, `z_release`, `R_Sun`, `AU`, `R_He`, `mu_P`, `mu_N`, `mu_D`, `mu_T`, `mu_He3`, `mu_alpha`, `Q_deuteron_fm2`, `B_alpha` | 18 |
| comparison datum | `R_inf`, `Ry_eV`, `a_rad` | 3 |
| derived inside the header | `alpha_inv`, `r_e`, `lambda_C_e`, `lambda_C_p`, `t_P`, `l_P3`, `T_release`, `k_e`, `B_deuteron`, `B_triton`, `B_helion` | 11 |
| legacy ballpark, not a measurement | `T_rec`, `z_rec` | 2 |
| external input conditioning a law | `R_CMB` | 1 |

Table 6.3. Roles of the 47 entries of `measured`. Where the table names an identifier it quotes the engine; the unit bridge $e$ is the entry `e_charge`.

The acyclic basis the derivelist records is: $\ell_P$ (geometric closure), one mass seat $\{\hbar\equiv m_e\equiv m_p\}$, $\alpha$ (spectroscopic derivation), $a_0$ (measured), $T_{\rm CMB}$ (measured boundary state) and the unit bridges $c$, $k_B$, $e$; $R_p$ and $m_p$ are one fact, with a shared 0.02% residual. Several entries carry a disclosure that this book repeats at each use:

* **`l_P`.** The relation $\ell_P=\sqrt{\mathrm{Om}_b\,\bar\lambda_p}$ (baryon koppa length and proton wake length $\bar\lambda_p=R_p/4$; Chapter 18) is geometric, but the stored number is the CODATA Planck length, whose definition carries $G$ numerically. The engine's review of 2026-10-16 assigns the stored number the tier CALIBRATED(1) (`laws.hpp:111–119`). No symbol $G$ appears, and the number enters $N$, $P_{\rm conv}$ and the cell volume.
* **`R_CMB`.** Distance to the Clearing, from $H_0$ and a reference epoch. It conditions the Law I chain and fails the delete-test (class X).
* **`T_rec`, `z_rec`.** Round ballparks (3000 K, 1100) of the account the framework does not follow, retained at their old values so that downstream tools do not change; the native pair is `z_release` $=1089$ (observed in the FIRAS frame) and `T_release` $=T_{\rm CMB}(1+z_{\rm release})=2970.8$ K, computed.
* **`mu_*`.** Magnetic moments in nuclear magnetons, a borrowed unit; they are recast to a native ratio before use (Chapter 24).

## 6.6 Uncertainty and traceability

For $y=f(q)$, first-order propagation gives $C_y=J\,C_q\,J^{\!\top}$, with the off-diagonal terms of correlated inputs kept. When two displayed quantities come from one reading, their ratio can have a far smaller uncertainty than either. Independent corroboration needs an independent measurement chain and not another arrangement of the same input. Every quantity in this book therefore carries a role, a reference state, dimensions, a covariance source and a chain: the roles of Table 6.3 are the first of these, and the full ledger with covariances is assembled in Chapter 62.

## 6.7 Input ledger and residuals

| quantity | role | label |
|---|---|---|
| dimensions, ranks, null spaces | Section 6.2 | DERIVED (exact rational) |
| redundancies of Table 6.2 | checks of stored numbers | COMPUTED |
| thermal chain values | Section 6.4 | COMPUTED from MEASURED-INPUT ($T_{\rm CMB}$, constants) |
| roles of Table 6.3 | engine statements and derivelist | the engine's own labels, quoted |

**Residuals.**

* **R6.1 — the stored $\ell_P$.** A derivation of the number from the c-boundary per baryon and the proton wake without the Planck-length definition is open; until then every quantity built on $N$ and $P_{\rm conv}$ carries CALIBRATED(1) through $\ell_P$.
* **R6.2 — $R_{\rm CMB}$.** A value of the Clearing distance derived from the Law I chain without the $H_0$ input is open (CONDENSA §7).
* **R6.3 — legacy ballparks.** Migration of the downstream tools off `T_rec` and `z_rec` is outstanding in the engine.
* **R6.4 — borrowed unit.** The moments in `mu_*` need a native ratio (Chapter 24).
* **R6.5 — radiation constant digits.** `a_rad` is stored to five digits, $4.4\times10^{-6}$ below the value computed from $k_B$, $h$, $c$; the shift propagates to $\varepsilon$, $\Phi$ and $P_{\rm conv}$ equally. A proposal to store more digits is canon work and waits for approval.
* **R6.6 — the one number of the seed.** The sources do not state whether $\theta=1.9237\times10^{-32}$ is an input, an output of the cosmology, or a relation to $N$.

## 6.8 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch06_state_dimensions_and_metrology
```

Criteria were registered in `Textbook/validation/ch06_PRE_REGISTRATION.md` before the instrument existed. Run 1 met every criterion except one clause of V2, whose test code contradicted its own registration (a square root of a length is represented in half units and is not refused); the clause was repaired and the repair recorded. Run 2 (`ch06_run2_output.txt`) is the run of record and met every criterion, including the coverage test T5.

## 6.9 Exercises and answers

**Exercise 1.** Find the dimensionless product of $c$, $\hbar$, $\ell_P$ and $m_e$.

*Answer.* $\ell_Pm_ec/\hbar$: the dimension of $m_ec/\hbar$ is $\mathrm L^{-1}$, so multiplying by $\ell_P$ is dimensionless. Value $4.185462\times10^{-23}$, the ratio of $\ell_P$ to the reduced Compton wavelength.

**Exercise 2.** Show that $S_1$ has exactly one independent dimensionless number.

*Answer.* Five quantities, rank 4 (M, L, T, K are all used and independent), so $5-4=1$. Solving $Dw=0$ for $(\ell_P,c,\hbar,k_B,T)$ gives $w\propto(1,-1,-1,1,1)$.

**Exercise 3.** Show that the factor between the two peak wavelengths of a Planck spectrum is $x_\lambda/x_\nu$.

*Answer.* $\lambda_{\rm peak}=hc/(x_\lambda k_BT)$ and $c/\nu_{\rm peak}=hc/(x_\nu k_BT)$, so $c/(\nu_{\rm peak}\lambda_{\rm peak})=x_\lambda/x_\nu=4.965114/2.821439=1.759781$.

**Exercise 4.** How does the five-digit storage of $a_{\rm rad}$ move $P_{\rm conv}$?

*Answer.* $P_{\rm conv}=Nu=N a_{\rm rad}T^4$ is linear in $a_{\rm rad}$, so the relative shift is that of $a_{\rm rad}$: $-4.4\times10^{-6}$, from $2.460833\times10^{48}$ Pa (computed constant) to $2.460822\times10^{48}$ Pa (stored).

**Exercise 5.** Why does one 160-GHz quantum not define a temperature of 2.73 K?

*Answer.* A temperature is a property of a distribution of quanta. One quantum has one energy; reading $T=h\nu/(x_\nu k_B)$ from it presumes a Planck distribution and a chosen spectral variable.

**Exercise 6.** A claimed relation reads $F=P_{\rm conv}R_p$. Show that it is dimensionally inconsistent.

*Answer.* $P_{\rm conv}$ is $\mathrm{M\,L^{-1}T^{-2}}$ and $R_p$ is $\mathrm L$, so the product is $\mathrm{M\,T^{-2}}$, not the $\mathrm{M\,L\,T^{-2}}$ of a force; the area $R_p^2$ is required.

## 6.10 Scope

Established in this chapter: the dimensions of the book; the criterion (6.1) for a unit-independent product and the Buckingham count for the engine's seed, with four sets worked out exactly; the homogeneity of the relations of Chapters 1–9; the single-edition consistency of the stored constants to $10^{-11}$ (and the five-digit limit of the radiation constant); the thermal chain with its two peak conventions; and the roles of all 47 entries of the measured namespace.

Not established: a derivation of the stored $\ell_P$ (R6.1) or of $R_{\rm CMB}$ (R6.2), the status of the one dimensionless number $\theta$ of the seed (R6.6), and a native ratio for the nuclear moments (R6.4).

*Where it leads.* Chapter 7 uses the dimensionless winding numbers. Chapter 12 reads the exclusion volume as the output that the mass seat measures. Chapter 44 returns to the thermal chain, and Chapter 62 assembles the covariance ledger.
