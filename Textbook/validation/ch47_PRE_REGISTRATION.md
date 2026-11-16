# Chapter 47 — pre-registration of the worked-example instrument

Registered 2026-11-10, before `Textbook/examples/ch47_clearing_and_historical_anchors.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object. The joint calibration of thermal, wavelength and loading landmarks under the selected branch $E_{\rm epoch}=T/T_0=c_0/c_{\rm epoch}$ (volume draft), with $T_0=T_{\rm CMB}=2.7255$ K (FIRAS). (a) Wavelength landmarks convert to temperatures by $T=b/\lambda$ with the Wien constant $b$ computed in Chapter 44 from $\{h,c,k_B\}$ (not the engine's rounded $2.898\times10^{-3}$). (b) Epoch landmarks convert by $T=T_0\times$ratio; the engine's release ratio is $1+z_{\rm release}=1090$ (`measured::T_release`, 2970.795 K) and the historical release ratio quoted in the volume draft is 1090.8. (c) The drag-loading landmarks quoted in the volume draft (loading 0.6 at 3073.58 K, loading 1 at 1844.15 K) come from a recovered calibration that is not re-derived here; only their internal consistency ($T\propto1/\text{loading}$) and their wavelength equivalent are tested. (d) The landmarks are distinct operational values and are not collapsed into one temperature. (e) Distance is a separate closure: the octave count across a geometric length and across a thermal wavelength are different dimensionless ratios, and a thermal conversion applied to a distance gives a formal value, not a temperature. (f) Hard gamma: in the branch $c_{\rm epoch}/c_0=T_0/T$ no finite wavelength makes $c_{\rm epoch}$ zero; a photon's equivalent peak temperature $b/\lambda$ is a spectral assignment and does not establish a bath at that temperature. The exponent of the branch (linear here; the author's later M-COS-1 programme records a squared form) is not decided by this chapter; both forms are evaluated for positivity only.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | $b=2.897771955\times10^{-3}$ m K (validated in Chapter 44); the wavelength of a 1 MeV photon, $hc/E=1.239841984\times10^{-12}$ m | $10^{-9}$, $10^{-6}$ |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | landmark conversions. $760$ nm $\to3812.86$ K and $780$ nm $\to3715.09$ K (computed from the native $b$; the volume draft quotes these values); engine `T_release` $=T_{\rm CMB}\cdot1090=2970.795$ K exactly; historical ratio $1090.8\to2972.98$ K; drag-loading consistency $T(1)/T(0.6)=0.6$ for the quoted $1844.15$ K and $3073.58$ K; the wavelength equivalent of $1844.15$ K lies in $[1570,1573]$ nm; the wavelength landmark $975$ nm $\to b/975\,\mathrm{nm}$ is reported | $2\times10^{-6}$ for the quoted decimals (relative), $3\times10^{-6}$ for the historical ratio and the loading consistency, $10^{-12}$ for `T_release` | yes |
| T2 | no collapse. The seven landmark temperatures (760 nm, 780 nm, 975 nm, loading 1, loading 0.6, release 1090, release 1090.8) are pairwise distinct at $10^{-4}$ relative resolution, and the largest exceeds the smallest by a factor of at least 2.0 | as stated | yes |
| T3 | distance is separate. $\log_2(R_{\rm CMB}/\ell_P)$ from the stored values lies in $[205,206]$; the thermal octave count from the CMB Wien peak to 760 nm is $10.4501$ to $10^{-4}$ (Chapter 44); the formal value $b/R_{\rm CMB}$ is reported and is below $10^{-30}$ K; $N\ell_P=R_{\rm CMB}$ (engine) to $10^{-12}$ | as stated | yes |
| T4 | hard gamma. $E=1$ eV $\ldots10^{15}$ eV (decades): $T_{\rm eq}=b/\lambda$ increases and $c_{\rm epoch}/c_0=T_0/T_{\rm eq}$ decreases strictly, both positive; for 1 MeV: $T_{\rm eq}\in[2.33\times10^9,2.35\times10^9]$ K, $T_0/T_{\rm eq}\in[1.1\times10^{-9},1.2\times10^{-9}]$ and $(T_0/T_{\rm eq})^2\in[1.3\times10^{-18},1.4\times10^{-18}]$; the energy density $aT_{\rm eq}^4$ of the bath that this temperature would describe is reported | as stated | yes |

Reported, not criteria: all converted temperatures, the loading-1 wavelength, the octave counts, the bath energy density.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch47_clearing_and_historical_anchors`

## Record of run 1; one registered statement rejected (2026-11-10)

Run 1 (`ch47_run1_output.txt`): every criterion was met except one in T3. The registered statement "the formal value $b/R_{\rm CMB}$ is below $10^{-30}$ K" is **rejected**: the value is $3.0416\times10^{-30}$ K ($2.897772\times10^{-3}/9.527\times10^{26}$). The registered bound came from an arithmetic slip in the registration (three orders of magnitude of $b$ miscounted as $10^{-33}$); it is a registration error and not a finding on the object, but the criterion is not retuned and the rejection is kept. Run 2 asserts the rejection (the statement is false at $10^{-30}$ K) and adds, **post-run and marked as such**, the clause the registration meant: the formal value is below $10^{-29}$ K and below $10^{-29}\,T_{\rm CMB}$ ($1.1\times10^{-30}$ of $T_{\rm CMB}$), that is, no measured temperature. Nothing else changed. Run 2 is the run of record.
