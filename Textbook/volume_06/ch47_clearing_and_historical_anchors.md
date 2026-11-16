# Chapter 47 — The Clearing and Historical Anchors

*Volume VI — Sz, Pressure History and Coupled Ratios.*
Draft of 10 November 2026. Notation: $T_0=T_{\rm CMB}=2.7255$ K (FIRAS); $b$ the Wien constant computed in Chapter 44; $c_{\rm epoch}$ the relay speed at an epoch; the selected branch is $E_{\rm epoch}=T/T_0=c_0/c_{\rm epoch}$ (volume draft); "loading" is the obstacle loading of the recovered calibration. Executable companion: `Textbook/examples/ch47_clearing_and_historical_anchors.cpp`; pre-registration and captured output in `Textbook/validation/`. The drag-loading landmarks (0.6 at 3073.58 K, 1 at 1844.15 K) come from a recovered calibration that is not re-derived here; only their consistency and wavelength equivalent are tested.

## 47.1 Joint calibration

The branch joins thermal, wavelength and loading coordinates through $T_0$. The landmarks keep their separate operational definitions: the red and near-infrared edges, the release and the drag loading are not collapsed into one temperature.

**Executed (V1, T1).** With the native $b=2.897771955\times10^{-3}$ m K from Chapter 44 (not the engine's rounded constant):

| landmark | conversion | temperature |
|---|---|---|
| 760 nm | $b/\lambda$ | $3812.8578$ K (draft: 3812.86) |
| 780 nm | $b/\lambda$ | $3715.0923$ K (draft: 3715.09) |
| 975 nm (bath edge) | $b/\lambda$ | $2972.0738$ K |
| release, engine ratio 1090 | $T_0\times1090$ | $2970.795$ K (`T_release`, exact) |
| release, historical ratio 1090.8 | $T_0\times1090.8$ | $2972.9754$ K (draft: 2972.98) |
| drag loading 0.6 | draft value | $3073.58$ K |
| loading 1 | draft value | $1844.15$ K |

The quoted decimals of the draft are reproduced to $0.6\times10^{-6}$ and $1.5\times10^{-6}$ relative. The two loading values satisfy $T(1)/T(0.6)=0.6000007$ (a $1.1\times10^{-6}$ departure from the exact proportionality $T\propto1/\text{loading}$, within the rounding of the quoted values). The wavelength equivalent of $1844.15$ K is $1571.33$ nm. A changed edge or release convention changes the displayed coordinate and has to be recorded with it.

**No collapse (T2).** The seven landmarks are pairwise distinct at $10^{-4}$ relative resolution (smallest separation $3.0\times10^{-4}$, between the 975 nm edge and the 1090.8 release) and span a factor $2.0675$ ($1844.15$ K to $3812.86$ K).

## 47.2 Distance is another closure

The stored $R_{\rm CMB}$ fixes the shell count of the present engine ($N=R_{\rm CMB}/\ell_P$); the cosmology header warns against deriving that distance from an accumulated in-flight strain law, which the recovered branch excludes. A redshift–temperature relation does not determine $d(z)$ without a progression and transport history.

**Executed (T3).** Two octave counts with different measurement chains: $\log_2(R_{\rm CMB}/\ell_P)=205.1970$ (a geometric length ratio) and the thermal count from the CMB Wien peak to 760 nm, $10.4501$ (Chapter 44). Applying the thermal conversion to a distance gives the formal value $b/R_{\rm CMB}=3.0416\times10^{-30}$ K: a calibrated number, not the temperature of a shell at that distance. The registered statement that this value lies below $10^{-30}$ K is **rejected** (it is $3.04\times10^{-30}$ K; the registration miscounted three orders of magnitude in $b/R_{\rm CMB}$; recorded in the pre-registration and kept). The clause the registration meant, added after the run and marked as such, holds: the value is below $10^{-29}$ K and $1.1\times10^{-30}$ of $T_{\rm CMB}$.

## 47.3 Hard-gamma extension

In the branch $c_{\rm epoch}/c_0=T_0/T$ no finite wavelength makes $c_{\rm epoch}$ exactly zero: the limit occurs only as $T\to\infty$. A measured hard-gamma photon can be given a reference wavelength and an equivalent peak temperature $T_{\rm eq}=b/\lambda$. The assignment does not establish a homogeneous bath at that temperature.

**Executed (T4).** For $E=10^0\ldots10^{15}$ eV the equivalent temperature increases strictly and $T_0/T_{\rm eq}$ decreases strictly and stays positive. At 1 MeV ($\lambda=1.239842\times10^{-12}$ m): $T_{\rm eq}=2.337211\times10^9$ K and $T_0/T_{\rm eq}=1.166134\times10^{-9}$. The bath that this temperature would describe has $aT_{\rm eq}^4=2.2576\times10^{22}$ J m$^{-3}$ for a single photon: the assignment is a spectral label. Gamma scattering ancestry needs the full optical-depth and reprocessing ledger.

The exponent of the branch is open: the draft states $c_{\rm epoch}\propto T^{-1}$; the author's later M-COS-1 programme records $c=c_0(T_0/T)^2$, which gives $1.359868\times10^{-18}$ at 1 MeV. Both are positive for every finite $T$ (registered and met); this chapter does not decide between them (R47.2).

## 47.4 Input ledger and residuals

| quantity | value | label |
|---|---|---|
| $T_0=2.7255$ K | `measured` | OBSERVED (FIRAS) |
| $1+z_{\rm release}=1090$ | `measured` | OBSERVED (FIRAS frame) |
| historical ratio 1090.8 | volume draft | stored landmark (not re-derived) |
| loading landmarks 3073.58 K, 1844.15 K | volume draft | stored landmarks of the recovered calibration (not re-derived) |
| $b$ | Chapter 44 | COMPUTED from the Planck form |
| $R_{\rm CMB}$ | `measured` | OBSERVED (stored boundary) |
| $\ell_P$ | `measured` | stored value carrying $G$: CALIBRATED (1); contaminating input named: $G$ enters at `laws.hpp:99` |
| 975 nm, 760 nm, 780 nm | draft | wavelength landmarks (operational definitions) |

**Residuals.**

* **R47.1 — the landmarks.** The loading landmarks and the 1090.8 ratio are stored values; their calibration chain was not re-executed.
* **R47.2 — the branch exponent.** Linear ($c\propto T^{-1}$) and squared ($c\propto T^{-2}$) forms are both on record; the mechanism that fixes it is not derived here.
* **R47.3 — distance.** No $d(z)$ relation is supplied; $R_{\rm CMB}$ remains a stored boundary.
* **R47.4 — gamma ancestry.** The optical-depth and reprocessing ledger is not computed.
* **R47.5 — a loading unit.** The loading coordinate was used only as a proportionality; its definition and the acoustic quantities of the release were not computed.

## 47.5 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch47_clearing_and_historical_anchors
```

Criteria were registered in `Textbook/validation/ch47_PRE_REGISTRATION.md` before the instrument existed. Run 1 (`ch47_run1_output.txt`) met every criterion except one registered limit (an arithmetic slip in the registration, rejected and kept). Run 2 (`ch47_run2_output.txt`) is the run of record: it asserts the rejection and adds one marked post-run clause.

## 47.6 Exercises and answers

**Exercise 1.** Convert the 975 nm edge to a temperature.

*Answer.* $2.897772\times10^{-3}/9.75\times10^{-7}=2972.07$ K.

**Exercise 2.** The loading-1 landmark is $1844.15$ K. At what wavelength does a Planck spectrum at that temperature peak?

*Answer.* $b/T=1.5713\ \mu$m.

**Exercise 3.** Why is $b/R_{\rm CMB}$ not a temperature?

*Answer.* $b/\lambda$ is a temperature only for a wavelength that is the peak of a radiation spectrum; $R_{\rm CMB}$ is a length between two places, and the quotient is a calibrated number.

**Exercise 4.** Give $T_{\rm eq}$ for a 511 keV photon.

*Answer.* $\lambda=hc/E=2.4263\times10^{-12}$ m; $T_{\rm eq}=b/\lambda=1.1943\times10^{9}$ K.

**Exercise 5.** Why does no finite wavelength make $c_{\rm epoch}$ zero in the branch?

*Answer.* $c_{\rm epoch}/c_0=T_0/T$ with $T=b/\lambda$ finite and positive for every finite wavelength.

**Exercise 6.** What does the 1 MeV bath energy density show?

*Answer.* That the temperature assigned to a photon would describe a radiation field of $2.26\times10^{22}$ J m$^{-3}$; one photon does not supply it, so the assignment is not a bath.

## 47.7 Scope

Established: the conversions of the landmarks with the native $b$; the separation of the seven landmarks; that a thermal conversion applied to a distance is formal; that $c_{\rm epoch}$ stays positive for every finite photon energy over 15 decades in either branch form; one rejected registered limit.

Not established: the calibration chain of the loading landmarks (R47.1), the branch exponent (R47.2), a distance relation (R47.3), gamma ancestry (R47.4) and the loading definition (R47.5).

*Where it leads.* Chapter 48 adds the evolution law that turns a route of states into a chronology.
