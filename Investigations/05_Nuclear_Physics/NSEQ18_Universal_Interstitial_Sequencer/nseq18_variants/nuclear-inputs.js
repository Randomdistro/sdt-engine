// GENERATED MIRROR — Engine/include/sdt/laws.hpp (CODATA 2022 nuclear inputs).
// Regenerate with the benchmark website-data export; do not fit values here.
(() => {
  'use strict';
  const c = 299792458;
  const eV = 1.602176634e-19;
  const protonMassKg = 1.67262192595e-27;
  const neutronMassKg = 1.67492750056e-27;
  const deuteronMassKg = 3.3435837768e-27;
  const tritonMassKg = 5.0073567512e-27;
  const helionMassKg = 5.0064127862e-27;
  const shellSchedule = Object.freeze([
    Object.freeze({ species: 'd', capacity: 6, geometry: 'oct', label: 'D6' }),
    Object.freeze({ species: 'd', capacity: 12, geometry: 'ico', label: 'D12-pre' }),
    Object.freeze({ species: 't', capacity: 8, geometry: 'stella', label: 'T8' }),
    Object.freeze({ species: 'd', capacity: 12, geometry: 'cuboct-3-6-3', label: 'D12-cuboct' }),
    Object.freeze({ species: 't', capacity: 10, geometry: 'polar', label: 'T10' }),
    Object.freeze({ species: 'd', capacity: 20, geometry: 'triangular-links', label: 'D20' }),
    Object.freeze({ species: 't', capacity: 12, geometry: 'polar', label: 'T12' }),
    Object.freeze({ species: 'd', capacity: 30, geometry: 'triangular-links', label: 'D30' }),
    Object.freeze({ species: 't', capacity: 14, geometry: 'face-normal-14', label: 'T14' }),
    Object.freeze({ species: 'd', capacity: 42, geometry: 'triangular-links', label: 'D42' }),
    Object.freeze({ species: 't', capacity: 16, geometry: 'polar', label: 'T16' })
  ]);
  const observables = Object.freeze({
    H1: Object.freeze({ magneticMomentMuN: 2.79284734463, source: 'CODATA 2022' }),
    H2: Object.freeze({ magneticMomentMuN: 0.8574382335, quadrupoleFm2: 0.285699, source: 'CODATA 2022 / spectroscopy' }),
    H3: Object.freeze({ magneticMomentMuN: 2.9789624650, source: 'CODATA 2022' }),
    He3: Object.freeze({ magneticMomentMuN: -2.1276253498, source: 'CODATA 2022' }),
    He4: Object.freeze({ magneticMomentMuN: 0, source: 'spin-zero measured anchor' }),
    Li7: Object.freeze({ magneticMomentMuN: 3.256427, source: 'Stone nuclear-moment table' }),
    Be9: Object.freeze({ magneticMomentMuN: -1.1778, source: 'Stone nuclear-moment table' })
  });
  const toMeV = mass =>
    mass * c * c / (1e6 * eV);
  globalThis.SDT_NUCLEAR_INPUTS = Object.freeze({
    speedOfLightMetresPerSecond: c,
    electronVoltJoules: eV,
    protonMassKg,
    neutronMassKg,
    deuteronMassKg,
    tritonMassKg,
    helionMassKg,
    fineStructureConstant: 7.2973525693e-3,
    hbarJouleSeconds: 1.054571817e-34,
    protonRadiusFm: 0.8414,
    magicNumbers: Object.freeze([2, 8, 20, 28, 50, 82, 126]),
    deuteronTiers: Object.freeze([6, 12, 12, 20, 30, 42]),
    tritonShellCapacities: Object.freeze([8, 10, 12, 14, 16]),
    shellSchedule,
    tritonOpeningScale: 1.05,
    tritonClosingScale: 0.95,
    observables,
    protonMomentMuN: 2.79284734463,
    neutronMomentMuN: -1.91304276,
    deuteronMomentMuN: 0.8574382335,
    tritonMomentMuN: 2.9789624650,
    helionMomentMuN: -2.1276253498,
    deuteronQuadrupoleFm2: 0.285699,
    deuteronBindingMeV:
      toMeV(protonMassKg + neutronMassKg - deuteronMassKg),
    tritonBindingMeV:
      toMeV(protonMassKg + 2 * neutronMassKg - tritonMassKg),
    helionBindingMeV:
      toMeV(2 * protonMassKg + neutronMassKg - helionMassKg)
  });
})();
