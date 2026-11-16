# Chapter 62 — pre-registration of the worked-example instrument

Registered 2026-11-10, before `Textbook/examples/ch62_parameter_and_uncertainty_ledger.py` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents). The instrument reads the manuscript chapters as text and writes `Textbook/sources/PARAMETER_LEDGER.csv`; the statistical examples are constructed (no measured input).

Object. The parameter and uncertainty ledger. (a) Roles of numbers: measured inputs, geometric constructions, derived response, fitted coefficients, conversion factors and unresolved functions are separate; a parameter with units can still be a measured anchor and a dimensionless factor can still be fitted; classification follows the measurement and derivation chain. The manuscript's own input-ledger tables (one per chapter; label per number) are extracted into one machine-readable file with chapter, row, quantity, source column, label and the recognised label token; the instrument reports which chapters lack a parsable ledger and which rows lack a recognised label. (b) Covariance: for log-linear ratios $y=Wx$ and covariance $C_x$, $C_y=WC_xW^T$; shared measurements create covariance that changes the uncertainty of a difference of ratios; ignoring it overstates or understates. (c) Nonlinear boundaries: first-order propagation is inadequate when the response crosses zero or has a vanishing derivative; a negative occupancy is a domain change, not a Gaussian uncertainty around a physical negative module count: the probability mass of a Gaussian estimate below zero is reported and the truncated (admissible) distribution used. (d) Calibration and prediction: a calibration subset is chosen, the parameters are frozen and withheld observables compared; an all-data refit measures descriptive adequacy, not predictive performance.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | none (Python) | |
| V1 | the table parser on a literal two-row table returns two rows with the label token read; the matrix product $WC_xW^T$ for $W=\begin{pmatrix}1&-1&0\\1&0&-1\end{pmatrix}$ and $C_x=\mathrm{diag}(1,4,9)\times10^{-6}$ equals $\begin{pmatrix}5&1\\1&10\end{pmatrix}\times10^{-6}$; $\Phi(-0.6)=0.27425$ from `math.erfc`; the least-squares solver returns $(2,-3)$ for $y=2-3x$ | exact; $10^{-15}$; $10^{-5}$; $10^{-12}$ |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | ledger. Over the drafted chapters (61 files `Textbook/volume_0*/ch*.md`): at least 55 have a parsable input-ledger table (a table following a heading or bold line containing "ledger"); at least 300 rows are extracted; at least 90 per cent of rows have a label token from {DERIVED, COMPUTED, CALIBRATED, OBSERVED, CONSTRUCTION, MEASURED-INPUT, PENDING, TOY, stored, unit bridge}; the file `PARAMETER_LEDGER.csv` is written with one line per row; the chapters without a parsable ledger and the rows without a token are listed | as stated | yes |
| T2 | covariance. $C_y=\begin{pmatrix}5&1\\1&10\end{pmatrix}\times10^{-6}$ (exact); the correlation of the two ratios is $0.1414$; the variance of $y_1-y_2=x_3-x_2$ is $13\times10^{-6}$ with the covariance and $15\times10^{-6}$ if it is ignored (an overstatement of $15.4$ per cent); a Monte Carlo of $2\times10^5$ draws (fixed seed) reproduces the three numbers within 2 per cent | as stated | yes |
| T3 | nonlinear boundary. An occupancy estimate $m=0.3$, $\sigma=0.5$: the Gaussian mass below zero is $\Phi(-0.6)=0.2743$ ($10^{-3}$; Monte Carlo within $0.005$); the mean of the admissible (truncated at 0) distribution lies in $[0.52,0.54]$; for $f=x^2$ with $x\sim N(0.05,0.1^2)$ the first-order standard deviation $0.01$ understates the actual $\sqrt{2\sigma^4+4\mu^2\sigma^2}=0.01732$: ratio in $[1.6,1.9]$ and a Monte Carlo agrees with $0.01732$ within 2 per cent | as stated | yes |
| T4 | calibration versus prediction. Twelve noisy samples of a quadratic (fixed seed, noise 0.05): a degree-5 polynomial fitted on 8 of them has a training RMSE below half its RMSE on the 4 withheld points; a degree-2 polynomial fitted on the same 8 has a withheld RMSE below that of the degree-5 fit; the all-data fit of degree 5 has a smaller training RMSE than the degree-2 all-data fit (descriptive adequacy rises while prediction does not) | as stated | yes |

Reported, not criteria: the per-chapter row counts, the label-token distribution, the files and rows listed as lacking.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Record of run 2; three registered statements rejected as findings on the manuscript (2026-11-10)

Run 2 (`ch62_run2_output.txt`), the first execution: V1, T2, T3 and T4 and the CSV criterion of T1 were met. Three registered statements of T1 were **rejected**, and they concern the state of the manuscript, not the tool: (i) at least 55 of the 61 drafted chapters have a parsable ledger: found 54 (`ch02`, `ch05`, `ch08`, `ch09`, `ch10`, `ch13`, `ch14` have none by the parser: the early chapters carry their inputs in prose or in tables under other headings); (ii) at least 300 rows: found 292; (iii) at least 90 per cent of rows carry a label token from the registered set: found $81.85$ per cent ($53$ of $292$ rows carry a free-text label such as "measured (FIRAS)", "posited", "reported" or a count, or none). The thresholds were registered before the corpus was scanned and are not moved. The statements are kept and asserted in run 3; the full list of the rows without a token is printed so that a repair of the manuscript (standardising the labels and adding the missing ledgers) has an exact list. Nothing in the manuscript was changed for run 3. Run 3 is the run of record; a later run after a repair would be a new, numbered run and would not replace it.

## Build line

`bash Textbook/tools/py_run.sh ch62_parameter_and_uncertainty_ledger` (from Git Bash; the `bash` found by PowerShell is WSL, which has no Python)

## Record of run 1; the instrument did not execute (2026-11-10)

Run 1 (`ch62_run1_output.txt`) is a launcher failure, not an instrument run: the command was started from PowerShell, whose `bash` is WSL, where `python` is not installed (`python: command not found`, exit 127). No criterion was evaluated. The file is kept with its number. Run 2, started from Git Bash as in Chapter 42, is the first execution of the instrument.
