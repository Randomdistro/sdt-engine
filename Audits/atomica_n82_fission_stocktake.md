# SDT Atomica: compulsory D–T stocktake for the U-235 thermal A=139/95 split

## Scope and status

This run tests the conservation-consistent event

\[
{}^{235}\mathrm U+n\rightarrow{}^{236}\mathrm U^*
\rightarrow{}^{139}\mathrm I+{}^{95}\mathrm Y+2n.
\]

The event is a canonical high-yield mass-region example, not a claim that every A=95 event is jointly paired with I-139. Event-level joint-yield evidence would be required for that stronger statement.

The active alpha-core grammar is used throughout:

\[
n_T=A-2Z=N-Z,
\qquad
n_D=3Z-A-2=2Z-N-2,
\]

\[
\text{nuclide}=\alpha+ n_DD+n_TT,
\qquad
\alpha=(2p,2n),\;D=(p,n),\;T=(p,2n).
\]

Every row closes under

\[
Z=2+n_D+n_T,qquad N=2+n_D+2n_T,qquad A=4+2n_D+3n_T.
\]

The earlier bare coordinates \(D=2Z-N\), \(T=N-Z\) omit the compulsory alpha core. That omission adds two spurious deuterons to every alpha-core nuclide and prevents a physically meaningful split receipt when one parent becomes two daughters.

## 1. Complete nuclide ledger

| Nuclide | Z | N | A | alpha cores | D | T |
|---|---:|---:|---:|---:|---:|---:|
| U-236* | 92 | 144 | 236 | 1 | 38 | 52 |
| I-135, protected N=82 reference | 53 | 82 | 135 | 1 | 22 | 29 |
| I-139, heavy primary product | 53 | 86 | 139 | 1 | 18 | 33 |
| Y-95, light primary product | 39 | 56 | 95 | 1 | 20 | 17 |
| Xe-139 | 54 | 85 | 139 | 1 | 21 | 31 |
| Cs-139 | 55 | 84 | 139 | 1 | 24 | 29 |
| Ba-139 | 56 | 83 | 139 | 1 | 27 | 27 |
| La-139, stable heavy terminus | 57 | 82 | 139 | 1 | 30 | 25 |
| Zr-95 | 40 | 55 | 95 | 1 | 23 | 15 |
| Nb-95 | 41 | 54 | 95 | 1 | 26 | 13 |
| Mo-95, stable light terminus | 42 | 53 | 95 | 1 | 29 | 11 |

## 2. Whole-split stocktake

Parent stock:

\[
\boxed{\alpha_P+38D+52T}.
\]

Observed post-prompt product stock:

\[
{}^{139}\mathrm I=\alpha_H+18D+33T,
\]

\[
{}^{95}\mathrm Y=\alpha_L+20D+17T,
\]

plus two free neutrons. Therefore

\[
\boxed{2\alpha+38D+50T+2n}.
\]

Subtracting the parent receipt gives

\[
(2\alpha+38D+50T+2n)-(\alpha+38D+52T)
=\alpha-2T+2n.
\]

Hence the exact net split receipt is

\[
\boxed{2T\longrightarrow\alpha+2n}.
\]

Unlike the rejected EC statement, this identity is not produced by comparing two same-core nuclides. Fission increases the number of compulsory cores from one to two, and the exact missing stock is two tritons. Six parent nucleons are accounted for on both sides:

\[
2T=2p+4n,qquad \alpha+2n=2p+4n.
\]

The identity establishes a complete net stock receipt. The identity alone does not identify a unique geometric seat pair among 52 parent tritons.

## 3. N=82 reference cut before jacket recapture

Resolve the heavy product first as an N=82 protected object:

\[
{}^{135}\mathrm I:\quad \alpha_H+22D+29T.
\]

Pairing I-135 with Y-95 gives

\[
(\alpha_H+22D+29T)+(\alpha_L+20D+17T)
=2\alpha+42D+46T.
\]

Relative to U-236*:

\[
(2\alpha+42D+46T)-(\alpha+38D+52T)
=\alpha+4D-6T.
\]

Mass conservation leaves six neutrons:

\[
\boxed{6T\longrightarrow\alpha+4D+6n}.
\]

Nucleon closure:

\[
6T=6p+12n,
\]

\[
\alpha+4D+6n=(2p+2n)+(4p+4n)+6n=6p+12n.
\]

This is the complete pre-recapture flay receipt for the selected split.

## 4. Canonical unit-by-unit allocation

Label the parent inventory

\[
\alpha_P,\quad D_1\ldots D_{38},\quad T_1\ldots T_{52}.
\]

A conservation-valid canonical allocation is:

### 4.1 Protected heavy N=82 structure

\[
{}^{135}\mathrm I:
\alpha_H=\alpha_P,
\quad D_1\ldots D_{22},
\quad T_1\ldots T_{29}.
\]

### 4.2 Light Y-95 structure before completion

Sixteen inherited deuterons and seventeen inherited tritons enter the light side:

\[
D_{23}\ldots D_{38},
\qquad
T_{30}\ldots T_{46}.
\]

Y-95 still requires one alpha core and four deuterons.

### 4.3 Flayed stock

The remaining six parent tritons are

\[
T_{47}\ldots T_{52}.
\]

The compulsory flay receipt is

\[
T_{47}+T_{48}+T_{49}+T_{50}+T_{51}+T_{52}
\rightarrow
\alpha_L+D'_{1}+D'_{2}+D'_{3}+D'_{4}
n_1+n_2+n_3+n_4+n_5+n_6.
\]

The light daughter then closes exactly as

\[
{}^{95}\mathrm Y=
\alpha_L+
(D_{23}\ldots D_{38})+
(D'_1\ldots D'_4)+
(T_{30}\ldots T_{46}).
\]

Count:

\[
1\alpha+20D+17T=95.
\]

Every parent unit has now received a disposition:

| Parent stock | Immediate disposition |
|---|---|
| alpha_P | heavy-core alpha_H |
| D1-D22 | protected heavy I-135 |
| D23-D38 | inherited by light Y-95 |
| T1-T29 | protected heavy I-135 |
| T30-T46 | inherited by light Y-95 |
| T47-T52 | flayed into alpha_L + 4D' + 6n |

No parent D unit disappears at the pre-recapture cut. All 38 parent D units remain intact under the canonical allocation. Exactly six parent T units supply the newly required daughter core, four additional daughter D units and six unseated neutrons.

The numerical allocation is exact but the choice of labels T47-T52 is conventional until the Atomica seat-order ledger identifies the actual split-plane seats.

## 5. Four-neutron recapture: N=82 to N=86

The observed heavy primary product is I-139 rather than I-135:

\[
{}^{135}\mathrm I+4n\rightarrow{}^{139}\mathrm I.
\]

At fixed Z, adding one neutron changes the alpha-core grammar by

\[
\Delta D=-1,\qquad\Delta T=+1.
\]

Four recaptures therefore give

\[
(22D,29T)+4n\rightarrow(18D,33T).
\]

A unit-resolved canonical mapping is

\[
D_{19}+n_1\rightarrow T'_{30},
\]

\[
D_{20}+n_2\rightarrow T'_{31},
\]

\[
D_{21}+n_3\rightarrow T'_{32},
\]

\[
D_{22}+n_4\rightarrow T'_{33}.
\]

The remaining neutrons become prompt emissions:

\[
n_5+n_6\rightarrow2n_{\rm prompt}.
\]

The heavy product closes as

\[
{}^{139}\mathrm I=
\alpha_H+D_1\ldots D_{18}+T_1\ldots T_{29}+T'_{30}\ldots T'_{33}.
\]

## 6. Exact parent-daughter mirror

The pre-recapture split creates four new deuterons in the light daughter:

\[
\boxed{+4D'\text{ in Y-95}}.
\]

Heavy-side recapture consumes four heavy deuterons and produces four tritons:

\[
\boxed{-4D,+4T\text{ in I-139}}.
\]

The four-for-four relation is an exact coordinate mirror:

| Light daughter interior | Heavy parent/remnant jacket |
|---|---|
| four reconstructed D units | four inherited D units opened for neutron recapture |
| receives alpha_L from flayed stock | retains alpha_P |
| receives 16 inherited D | retains 18 inherited D after recapture |
| receives 17 inherited T | retains 29 inherited T plus four recapture T |
| contains reconstructed stock | carries four-neutron N=82+ jacket |

The correlation is stronger than the bare net identity \(2T\to\alpha+2n\): the intermediate N=82 cut exposes a six-triton flay, four daughter-side D reconstructions, four heavy-side D-to-T recaptures and two escaped neutrons.

The correlation remains a stock-level result. A geometric mirror requires proof that the four light-side D seats and four heavy-side recapture seats share split-plane adjacency or common pre-split neighbourhoods.

## 7. Post-split decomposition chains

### 7.1 Heavy chain

\[
{}^{139}\mathrm I
\xrightarrow{\beta^-}
{}^{139}\mathrm{Xe}
\xrightarrow{\beta^-}
{}^{139}\mathrm{Cs}
\xrightarrow{\beta^-}
{}^{139}\mathrm{Ba}
\xrightarrow{\beta^-}
{}^{139}\mathrm{La}.
\]

| Stage | N | D | T | Increment |
|---|---:|---:|---:|---|
| I-139 | 86 | 18 | 33 | start |
| Xe-139 | 85 | 21 | 31 | +3D, -2T |
| Cs-139 | 84 | 24 | 29 | +3D, -2T |
| Ba-139 | 83 | 27 | 27 | +3D, -2T |
| La-139 | 82 | 30 | 25 | +3D, -2T |

Four beta-minus events remove the four-neutron excess above N=82 exactly:

\[
N:86\rightarrow85\rightarrow84\rightarrow83\rightarrow82.
\]

The most economical structural hypothesis is therefore that the four recapture-generated jacket sites are the four unstable sites corrected along the heavy chain. Count and endpoint support the hypothesis; the current ledger does not identify the four individual beta-active seats.

### 7.2 Light chain

\[
{}^{95}\mathrm Y
\xrightarrow{\beta^-}
{}^{95}\mathrm{Zr}
\xrightarrow{\beta^-}
{}^{95}\mathrm{Nb}
\xrightarrow{\beta^-}
{}^{95}\mathrm{Mo}.
\]

| Stage | N | D | T | Increment |
|---|---:|---:|---:|---|
| Y-95 | 56 | 20 | 17 | start |
| Zr-95 | 55 | 23 | 15 | +3D, -2T |
| Nb-95 | 54 | 26 | 13 | +3D, -2T |
| Mo-95 | 53 | 29 | 11 | +3D, -2T |

Three beta-minus corrections occur, not four. Therefore a one-to-one claim connecting all four reconstructed light-side D units to beta-active defects fails at the count level. At most three beta-active defects can be associated with the three light-chain corrections; one reconstructed D survives the correction sequence or participates only through reseating.

## 8. Combined post-split closure

Initial post-prompt products:

\[
2\alpha+38D+50T+2n.
\]

Stable termini:

\[
{}^{139}\mathrm{La}+{}^{95}\mathrm{Mo}
=2\alpha+59D+36T.
\]

Seven beta-minus events produce

\[
\Delta D=7(3)=+21,
\qquad
\Delta T=7(-2)=-14.
\]

Thus

\[
2\alpha+38D+50T
\rightarrow
2\alpha+59D+36T,
\]

with exact closure.

The heavy side contributes four corrections; the light side contributes three. The chains share the same algebraic beta-minus direction but do not possess identical lengths or endpoints.

## 9. What is correlated and what is not

### Exact

1. One parent core becomes two daughter cores.
2. Parent stock is \(\alpha+38D+52T\).
3. Post-prompt stock is \(2\alpha+38D+50T+2n\).
4. Net split receipt is \(2T\to\alpha+2n\).
5. N=82 reference cut gives \(6T\to\alpha+4D+6n\).
6. Four neutrons are recaptured on the heavy side.
7. Four heavy D counts are replaced by four T counts during recapture.
8. Four D counts are created on the light side at the reference cut.
9. Two neutrons remain for prompt emission.
10. Heavy decay contains four beta-minus steps and returns N=86 to N=82.
11. Light decay contains three beta-minus steps and terminates at Mo-95.

### Strong structural candidate

The four N=82+ heavy-jacket sites are the four recapture-generated sites and later supply the four heavy beta-minus corrections.

### Partial correlation

Four D units are reconstructed in the light daughter while four heavy D units are converted into recapture T units. The 4:4 mirror is exact in counts, but common split-plane seat provenance remains unproven.

### Failed simple mirror

Four reconstructed light D units do not produce four light-chain beta events; only three beta-minus steps occur. Identical parent/daughter correction pathways are therefore not universal.

### Unresolved

1. Exact identities of the six flayed parent T seats.
2. Exact split-plane topology.
3. Distribution of the four reconstructed D units across daughter seats.
4. Exact four heavy D seats receiving recaptured neutrons.
5. Event-level proof that I-139 and Y-95 are correlated partners rather than conservation-compatible marginal products.
6. Energetic or pressure-depth selector choosing the A=139/95 channel.

## 10. Verdict

The compulsory stocktake produces a nontrivial correlation:

\[
\boxed{
6T_{\rm flayed}
\rightarrow
\alpha_{\rm daughter}
+4D_{\rm daughter}
+6n;
\quad
4D_{\rm heavy}+4n
\rightarrow4T_{\rm heavy};
\quad
2n\text{ escape}.
}
\]

The corresponding compressed receipt is

\[
\boxed{2T\rightarrow\alpha+2n.}
\]

Evidence supports a precise stock-level mirror between four light-side D reconstructions and four heavy-side neutron recaptures. The heavy decay chain then removes exactly the four neutrons above N=82. The light chain performs only three beta-minus corrections, preventing promotion of the mirror into a universal seat-for-seat decay law.

Final classification:

\[
\boxed{\text{partial mirrored inheritance with exact coordinate conservation}.}
\]

The next decisive input is the Atomica seat-order ledger for U-236, I-135, I-139 and Y-95. Seat geometry can convert the exact numerical mirror into either a genuine common-provenance result or a permutation coincidence.
