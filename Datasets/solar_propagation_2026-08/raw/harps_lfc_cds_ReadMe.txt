J/A+A/643/A146      The solar gravitational redshift (Gonzalez Hernandez+, 2020)
================================================================================
The solar gravitational redshift from HARPS-LFC Moon spectra.
A test of the general theory of relativity.
    Gonzalez Hernandez J.I., Rebolo R., Pasquini L., Lo Curto G., Molaro P.,
    Caffau E., Ludwig H.-G., Steffen M., Esposito M., Suarez Mascarenno A.,
    Toledo-Padron B., Probst R.A., Hansch T.W., Holzwarth R., Manescau A.,
    Steinmetz T., Udem T., Wilken T.
    <Astron. Astrophys. 643, A146 (2020)>
    =2020A&A...643A.146G        (SIMBAD/NED BibCode)
================================================================================
ADC_Keywords: Solar system ; Sun ; Equivalent widths ; Line Profiles
Keywords: instrumentation: spectrographs - techniques: spectroscopic -
          Sun: granulation - Sun: photosphere - Sun: activity - atlases

Abstract:
    The General Theory of Relativity predicts the redshift of spectral
    lines in the solar photosphere, as a consequence of the gravitational
    potential of the Sun.

    This effect can be measured from a solar disk-integrated flux spectrum
    of the Sun's reflected light on solar system bodies.

    The laser frequency comb (LFC) calibration system attached to the
    HARPS spectrograph offers the possibility to perform an accurate
    measurement of the solar gravitational redshift (GRS) by observing the
    Moon or other solar system bodies.

    We have analysed the line shift observed in Fe absorption lines from
    five high-quality HARPS-LFC spectra of the Moon.

    We select an initial sample of 326 photospheric Fe lines in the
    spectral range 476-585nm and measure their line positions and
    equivalent widths (EWs).

    Accurate line shifts are derived from the wavelength position of the
    core of the lines compared with the laboratory wavelengths of Fe
    lines. We also use a CO^5^BOLD 3D hydrodynamical model atmosphere of
    the Sun to compute 3D synthetic line profiles of a subsample of about
    200 spectral Fe lines centred at their laboratory wavelengths.

    We fit the observed relatively weak spectral Fe lines (with
    EW<180m{AA}) with the 3D synthetic profiles.

    Convective motions in the solar photosphere do not affect the line
    cores of Fe lines stronger than about 150m{AA}.

    In our sample, only 15 FeI lines have EWs in the range
    150<EW(m{AA})<550, providing a measurement of the solar GRS at
    639+/-14m/s, consistent with the expected theoretical value on Earth
    of 633.1m/s.

    A final sample of about 98 weak Fe lines with EW<180m{AA} allows us to
    derive a mean global line shift of 638+/-6m/s in agreement with the
    theoretical solar GRS.

    These are the most accurate measurements of the solar GRS so far.
    Ultrastable spectrographs calibrated with the LFC over a larger
    spectral range, such as HARPS or ESPRESSO, together with a further
    improvement on the laboratory wavelengths, could provide a more robust
    measurement of the solar GRS and further tests for the 3D
    hydrodynamical models.

Description:
    Line data and velocity shifts of the FeI and FeII lines, with
    laboratory wavelengths, {lambda}_lab_, from Nave et al.
    (1994ApJS...94..221N, 2013ApJS..204....1N) and excitation potentials,
    oscillator strengths from the VALD database (Piskunov et al.
    1995A&AS..112..525P).

    In Table A.1 we provide the mean line core shifts, v_core_obs,
    measured on the spectral lines from the observed HARPS-LFC spectra of
    the MOON and computed with respect to the original laboratory
    wavelengths (Nave et al. 1994ApJS...94..221N, 2013ApJS..204....1N).

    We also give the recalibrated wavelengths, lambda_nist, computed from
    recalibrated wavenumber measurements and Ritz wavelengths,
    lambda_ritz, computed from recalibrated energy levels, with their
    corresponding wavelengths uncertainties, extracted from the NIST
    database (Kramida et al. 2019APS..DMPN09004K).

    In Table A.2, we give the line core shifts measured on the observed
    spectral lines, v_core_obs_n, estimated using the recalibrated
    wavelengths, lambda_nist, as reference laboratory wavelengths, the 3D
    profiles, v_core,3D, and the global line shifts, v_fit_3D_n, from
    fitting the observed spectral lines using 3D profiles, and corrected
    using the recalibrated wavelengths lambda_nist as reference laboratory
    wavelengths.

    Wavelengths are given in Angstroms, wavelength uncertainties in
    miliAngstroems, excitation potentials in eV, equivalent widths (EW) in
    miliAngstroems, and velocity shifts in m/s.

File Summary:
--------------------------------------------------------------------------------
 FileName      Lrecl  Records   Explanations
--------------------------------------------------------------------------------
ReadMe            80        .   This file
tablea1.dat       75      188   Line data and line shifts of 188 FeI-II lines
tablea2.dat       74       97   Line data and line shifts of 97 FeI-II lines
--------------------------------------------------------------------------------

See also:
   J/ApJS/94/221 : New multiplet table for FeI (Nave+, 1994)

Byte-by-byte Description of file: tablea1.dat
--------------------------------------------------------------------------------
   Bytes Format Units   Label        Explanations
--------------------------------------------------------------------------------
   1-  9  F9.4  0.1nm   lambda-lab   Original wavelengths (1)
  11- 19  F9.4  0.1nm   lambda-nist  Recalibrated wavelengths (2)
  21- 23  F3.1  0.1pm e_lambda-nist  Uncertainty in lambda_nist (2)
  25- 33  F9.4  0.1nm   lambda-ritz  Recalibrated Ritz wavelengths (2)
  35- 37  F3.1  0.1pm e_lambda-ritz  Uncertainty in lambda_ritz (2)
  39- 40  A2    ---     El           Chemical element
      42  I1    ---     Ion          Element Ion
  44- 47  F4.2  eV      ExPot        Excitation potential (3)
  49- 53  F5.2  [-]     loggf        Oscillator strength (3)
  55- 59  F5.1  0.1pm   EW           Equivalent widths
  61- 64  F4.1  0.1pm e_EW           Uncertainty in EW
  66- 70  F5.1  m/s     v-core-obs   Line core shift (4)
  72- 75  F4.1  m/s   e_v-core-obs   Uncertainty in v_core_obs
--------------------------------------------------------------------------------
Note (1): original wavelengths of FeI lines extracted from
 Nave et al. (1994ApJS...94..221N, Cat. J/ApJS/94/221) and of FeII lines
 extracted from Nave & Johansson (2013ApJS..204....1N).
Note (2): recalibrated wavelengths of FeI-II lines, lambda-nist, computed from
 recalibrated wavenumber measurements and Ritz wavelengths, lambda_ritz,
 computed from recalibrated energy levels, with their corresponding
 wavelengths uncertainties, all values extracted from the NIST database
 (Kramida et al. 2019APS..DMPN09004K).
Note (3): excitation potentials and oscillator strengths from the VALD database
 (Piskunov et al. 1995A&AS..112..525P).
Note (4): Mean line core shift computed with respect to the original laboratory
 wavelengths of FeI lines from Nave et al.  (1994ApJS...94..221N,
 Cat. J/ApJS/94/221) and FeII lines from Nave & Johansson (2013ApJS..204....1N).
--------------------------------------------------------------------------------

Byte-by-byte Description of file: tablea2.dat
--------------------------------------------------------------------------------
   Bytes Format Units   Label         Explanations
--------------------------------------------------------------------------------
   1-  9  F9.4  0.1nm   lambda-lab    Original wavelengths (1)
  11- 19  F9.4  0.1nm   lambda-nist   Recalibrated wavelengths (2)
  21- 22  A2    ---     El            Chemical element
      24  I1    ---     Ion           Element Ion
  26- 29  F4.2  eV      ExPot         Excitation potential (3)
  31- 35  F5.2  [-]     loggf         Oscillator strength (3)
  37- 41  F5.1  0.1pm   EW            Equivalent width
  43- 45  F3.1  0.1pm e_EW            Uncertainty in EW
  47- 51  F5.1  m/s     v-core-obs-n  Line core shift (4)
  53- 56  F4.1  m/s   e_v-core-obs-n  Uncertainty in v_core_obs
  58- 63  F6.1  m/s     v-core-3D     Line core shift; 3D line profile (5)
  65- 69  F5.1  m/s     v-fit-3D-n    Global line shift; 3D profile fit (6)
  71- 74  F4.1  m/s   e_v-fit-3D-n    Uncertainty in v_fit_3D_n
--------------------------------------------------------------------------------
Note (1): original wavelengths of FeI lines extracted from
  Nave et al. (1994ApJS...94..221N, Cat. J/ApJS/94/221) and of FeII lines
  extracted from Nave & Johansson (2013ApJS..204....1N).
Note (2): recalibrated wavelengths of FeI-II lines, lambda_nist, computed from
  recalibrated wavenumber measurements, with their corresponding
  wavelengths uncertainties, all values extracted from the NIST database
  (Kramida et al. 2019APS..DMPN09004K).
Note (3): excitation potentials and oscillator strengths from the VALD database
  (Piskunov et al. 1995A&AS..112..525P).
Note (4): Mean line core shift computed with respect to the recalibrated
  wavelengths of FeI-II lines, lambda-nist, extracted from the NIST
  database (Kramida et al. 2019APS..DMPN09004K).
Note (5): Line core shift computed from the 3D line profiles interpolated to
  the observed equivalent width of the FeI-II lines.
Note (6): Global line shift estimated from fitting the observed FeI-II lines
  with 3D line profiles computed using a CO5BOLD 3D model atmosphere
  of the Sun. The line shift are corrected using the recalibrated
  wavelengths of FeI-II lines, lambda_nist, extracted from the NIST
  database (Kramida et al. 2019APS..DMPN09004K)
--------------------------------------------------------------------------------

Acknowledgements:
    Jonay I. Gonzalez Hernandez, jonay(at)iac.es

References:
    Kramida et al., 2019APS..DMPN09004K,
     NIST's atomic databases for applied and fundamental science
    Nave, G., et al., 1994ApJS...94..221N,
     A New Multiplet Table for Fe I
    Nave, G., & Johansson, S., 2013ApJS..204....1N,
     The Spectrum of Fe II
    Piskunov, N. E. et al., 1995A&AS..112..525P,
     VALD: The Vienna Atomic Line Data Base

================================================================================
(End) Jonay Gonzalez Hernandez [IAC, Spain], Patricia Vannier [CDS]  24-Sep-2020
