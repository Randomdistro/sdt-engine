"""APS14 instrument controls."""

import math
import unittest

from aps14 import constants as K
from aps14.configurations import SeatLabel, expand_configuration
from aps14.dynamics import ModelParameters, solve_state
from aps14.observables import excitation_observables
from aps14.state_energy import state_energy_eV


class APS14Controls(unittest.TestCase):
    def test_hydrogenic_exact_limit(self):
        for z in (1, 2, 3, 10):
            for n in (1, 2, 3):
                state = solve_state(z, [SeatLabel(n, "s", 0)], ModelParameters())
                self.assertAlmostEqual(state.radii[0], K.A0 * n * n / z, delta=1e-22)
                self.assertAlmostEqual(
                    state.velocities[0], z * K.ALPHA * K.C / n, delta=1e-5
                )
                self.assertAlmostEqual(
                    state.depth_z[0], (z * K.ALPHA / n) ** 2, delta=1e-16
                )
                self.assertAlmostEqual(
                    -state_energy_eV(state, ModelParameters()),
                    K.RY_EV * z * z / (n * n), delta=5e-8,
                )

    def test_scaling(self):
        states = [
            solve_state(z, [SeatLabel(1, "s", 0)], ModelParameters())
            for z in (1, 2, 3)
        ]
        for z, state in enumerate(states, 1):
            self.assertAlmostEqual(state.radii[0] / states[0].radii[0], 1 / z)
            self.assertAlmostEqual(
                state.force_nuclear[0] / states[0].force_nuclear[0], z ** 3
            )
            self.assertAlmostEqual(
                state.stiffness[0] / states[0].stiffness[0], z ** 4
            )

    def test_cr_cu_configuration_exceptions(self):
        self.assertEqual(len(expand_configuration("[Ar]3d5 4s1")), 24)
        self.assertEqual(len(expand_configuration("[Ar]3d10 4s1")), 29)

    def test_same_n_transition_requires_geometry(self):
        seats = expand_configuration("[Ne]3s1")
        emission, _, _ = excitation_observables(
            11, seats, ModelParameters(0.6, 0.6, 0.05, 0.10, 0.0)
        )
        self.assertTrue(math.isfinite(emission.energy_eV))
        self.assertNotEqual(emission.energy_eV, 0.0)


if __name__ == "__main__":
    unittest.main()
