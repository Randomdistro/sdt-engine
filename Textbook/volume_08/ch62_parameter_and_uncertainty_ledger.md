# Chapter 62 — Parameter and Uncertainty Ledger

*Volume VIII — Executable Reference, Verification and Research Closure.*
Draft of 10 November 2026. Notation: $x$ log-quantities with covariance $C_x$; $y=Wx$ log-linear ratios with $C_y=WC_xW^T$; $m$ an occupancy estimate with standard deviation $\sigma$; $\Phi$ the standard normal distribution function. Executable companion: `Textbook/examples/ch62_parameter_and_uncertainty_ledger.py` (exact and floating arithmetic with the Python standard library; the run reads the manuscript chapters as text and writes `Textbook/sources/PARAMETER_LEDGER.csv`); pre-registration and captured output in `Textbook/validation/`. The statistical examples are constructed (no measured input).

## 62.1 Roles of numbers

The ledger separates measured inputs, geometric constructions, derived response, fitted coefficients, conversion factors and unresolved functions. A parameter with units can still be a measured anchor, and a dimensionless factor can still be fitted: classification follows the measurement and derivation chain, not the presence of units. In this book the roles are carried by the labels MEASURED-INPUT and OBSERVED (measured anchors), CONSTRUCTION (a geometric or toy construction), DERIVED and COMPUTED (derived response, exact or numerical), CALIBRATED ($n$) (fitted, with the number of fitted parameters), "unit bridge" and "stored" (conversion factors and stored values), and PENDING (unresolved). For Sz the reference-state normalisation and the evolution parameters occupy different ledger rows: fixing a unit convention does not remove a physical constitutive degree of freedom.

**Executed (V1, T1).** The table parser was checked on a literal table. It was then run over the 61 drafted chapters (`Textbook/volume_0*/ch*.md`), extracting the table that follows each heading or bold line containing "ledger". Found: 54 chapters with a parsable ledger and 292 rows. The 7 chapters without one are Chapters 2, 5, 8, 9, 10, 13 and 14 (their inputs are carried in prose or under other headings). The label tokens of the 239 labelled rows are DERIVED 61, COMPUTED 80, CALIBRATED 10, OBSERVED 21, CONSTRUCTION 33, MEASURED-INPUT 29, stored 4, unit bridge 1. The 53 remaining rows ($18.2$ per cent) carry a free-text label ("measured (FIRAS)", "posited", "reported", "engine-recorded; not re-run", a count) or none; the full list is in the run output. The registered statements that at least 55 chapters, at least 300 rows and at least 90 per cent of rows with a token would be found were **rejected** (54; 292; $81.85$ per cent): these are findings on the manuscript's own ledgers, thresholds fixed before the corpus was scanned. The extraction is the machine-readable ledger of this edition, with chapter, row, quantity, source or value, label, label token and a flag for whether the chapter mentions covariance (`PARAMETER_LEDGER.csv`, 292 rows). It does not yet carry a covariance block, a domain or the downstream equations for each number (R62.3).

## 62.2 Covariance

For log-linear ratios $y=Wx$ and covariance $C_x$, $C_y=WC_xW^T$. Shared measurements create covariance that can cancel or amplify uncertainty. A parameter quoted without covariance can overstate the independence of cross-sector comparisons.

**Executed (V1, T2).** Take $x=(\ln a,\ln b,\ln c)$ with $C_x=\mathrm{diag}(1,4,9)\times10^{-6}$ and the ratios $y_1=x_1-x_2$, $y_2=x_1-x_3$ that share $x_1$: $C_y=\begin{pmatrix}5&1\\1&10\end{pmatrix}\times10^{-6}$ (exact), a correlation of $0.1414$. The difference $y_1-y_2=x_3-x_2$ has variance $13\times10^{-6}$; ignoring the shared measurement gives $15\times10^{-6}$, an overstatement of $15.4$ per cent. A Monte Carlo of $2\times10^5$ draws reproduces $4.98\times10^{-6}$, $9.97\times10^{-6}$, the covariance $1.01\times10^{-6}$ and the variance of the difference, $12.94\times10^{-6}$, all within 2 per cent of the exact values.

## 62.3 Nonlinear boundaries

First-order propagation is inadequate when the response crosses zero, approaches a singular derivative or switches topology. The full admissible interval, or a justified probability model, is propagated with the correlated constraints. A negative occupancy is a domain change, not a Gaussian uncertainty about a physical negative module count.

**Executed (T3).** An occupancy estimate $m=0.3$ with $\sigma=0.5$: the Gaussian mass below zero is $\Phi(-0.6)=0.27425$ (Monte Carlo $0.2735$), more than a quarter of the nominal $1\sigma$ distribution lying in a domain that does not exist. Restricted to the admissible domain the mean is $0.52957$ (Monte Carlo $0.52843$), not $0.3$. For $f=x^2$ with $x\sim N(0.05,0.1^2)$ the first-order standard deviation $2|x_0|\sigma=0.01000$ understates the actual $\sqrt{2\sigma^4+4\mu^2\sigma^2}=0.01732$ by the factor $1.732$ (Monte Carlo $0.01726$): near a vanishing derivative the first-order estimate is wrong by the second-order term.

## 62.4 Calibration and prediction

Choose a calibration subset, freeze the parameters and compare withheld observables. An all-data refit measures descriptive adequacy, not predictive performance. When a coefficient is added after a residual has been seen, the original result is preserved and the new registration labelled.

**Executed (T4).** Twelve samples of a quadratic with noise $0.05$ (fixed seed). A degree-5 polynomial fitted on 8 points has a training RMSE of $0.01487$ and a withheld RMSE of $0.08676$ on the other 4 (a factor $5.8$); a degree-2 polynomial on the same 8 has a withheld RMSE of $0.02262$, smaller. The all-data fits give $0.01545$ for degree 5 and $0.02561$ for degree 2: descriptive adequacy rises with the number of parameters while the predictive error does not. The same discipline governs this book: the registered criteria were fixed before each instrument existed, a criterion failing in a run was kept as a rejection or a recorded defect, and added clauses are marked as post-run.

## 62.5 Input ledger and residuals

| quantity | value | label |
|---|---|---|
| ledger statistics | Section 62.1 | COMPUTED (text extraction of the manuscript) |
| $C_y$, variances, correlation | Section 62.2 | DERIVED (exact) and COMPUTED (Monte Carlo) |
| probability masses, truncated mean, standard deviations | Section 62.3 | DERIVED (exact) and COMPUTED |
| fits and RMSE | Section 62.4 | CONSTRUCTION (synthetic data, fixed seed) |

**Residuals.**

* **R62.1 — the labels.** 53 of 292 ledger rows carry no standard label token; the list is in `ch62_run3_output.txt`. A repair standardises them to the label set of Section 62.1 (a free-text label can be kept after the token).
* **R62.2 — the missing ledgers.** Chapters 2, 5, 8, 9, 10, 13 and 14 have no parsable input-ledger table.
* **R62.3 — covariance, domain and downstream equations.** The extracted ledger records no covariance block, domain or downstream equation per number; only whether the chapter mentions covariance.
* **R62.4 — per number.** Ledger rows are per quantity; some rows cover several numbers.
* **R62.5 — nonlinear intervals.** The propagation of the full admissible interval was illustrated for one occupancy and one square; no engine quantity was propagated.

## 62.6 Implementation and verification

```
bash Textbook/tools/py_run.sh ch62_parameter_and_uncertainty_ledger
```

(from Git Bash). Criteria were registered in `Textbook/validation/ch62_PRE_REGISTRATION.md` before the instrument existed. Run 1 (`ch62_run1_output.txt`) did not execute: the launcher started from PowerShell found a WSL `bash` without Python (recorded). Run 2 (`ch62_run2_output.txt`) met every criterion except three registered statements about the manuscript's ledgers, which were rejected as findings. Run 3 (`ch62_run3_output.txt`) is the run of record: the three rejections are asserted and the full list of unlabelled rows is printed. Note of 16 November 2026: the counts of Section 62.1 are those of run 3, made when 61 chapters were drafted. The review of the finished manuscript afterwards corrected four ledger rows (the solar source length in Chapters 39, 40 and 45, and the citation count in Chapter 57); the instrument was not re-run and `PARAMETER_LEDGER.csv` keeps the run-3 wording of those rows.

## 62.7 Exercises and answers

**Exercise 1.** Why can a dimensionless factor be a fitted coefficient?

*Answer.* Its role follows its derivation chain: a pure number adjusted to match a measured value is CALIBRATED regardless of its units.

**Exercise 2.** Find the correlation of $y_1=x_1-x_2$ and $y_2=x_1-x_3$ for independent $x_i$ with variances $s_1^2,s_2^2,s_3^2$.

*Answer.* $\mathrm{Cov}=s_1^2$; $\rho=s_1^2/\sqrt{(s_1^2+s_2^2)(s_1^2+s_3^2)}$; for $(1,4,9)\times10^{-6}$ this is $0.1414$.

**Exercise 3.** Why is the mean of the admissible distribution above $0.3$?

*Answer.* Removing the mass below zero removes only low values, so the conditional mean rises: $0.3+0.5\,\phi(0.6)/(1-\Phi(-0.6))=0.5296$.

**Exercise 4.** For $f=x^2$ at $x_0=0$, what is the first-order standard deviation?

*Answer.* Zero ($f'(0)=0$), while the actual standard deviation is $\sqrt2\sigma^2$: a first-order propagation fails completely at a vanishing derivative.

**Exercise 5.** Why does a better all-data fit not imply a better prediction?

*Answer.* Added parameters fit the noise of the training set; the withheld error does not fall (degree 5: $0.0868$ against $0.0226$ for degree 2).

**Exercise 6.** Which rows of the manuscript ledger have no token, and what is the repair?

*Answer.* The 53 listed in the run output; replace each label by one of the standard tokens, keeping the free text after it.

## 62.8 Scope

Established: the extraction of the manuscript's ledgers and their statistics (54 chapters, 292 rows, $81.85$ per cent labelled); the covariance propagation and its effect on a difference of ratios; the failure of Gaussian and first-order propagation at a boundary and at a vanishing derivative; the distinction between descriptive adequacy and prediction on a constructed case.

Not established: standard labels for all rows (R62.1), ledgers for seven chapters (R62.2), a covariance block per number (R62.3), per-number rows (R62.4) and propagation of engine quantities (R62.5).

*Where it leads.* Chapter 63 treats failed models and supersession: the chronology and causes of the failed runs recorded in this book.
