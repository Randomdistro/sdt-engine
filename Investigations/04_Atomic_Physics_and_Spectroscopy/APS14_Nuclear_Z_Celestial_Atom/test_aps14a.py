"""Controls for APS14a orbital pathways and transition grammar."""

import csv
import unittest
from pathlib import Path

from aps14.configurations import expand_configuration
from aps14.angular_dynamics import AngularParameters, optimise_phases
from aps14.angular_geometry import angular_directions
from aps14.orbital_pathway import hlike_pathway_controls
from aps14.transitions import build_hlike, build_transition

HERE = Path(__file__).resolve().parent


class APS14aControls(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        with (HERE / "data/elements.csv").open(encoding="utf-8") as handle:
            cls.elements = {
                int(row["Z"]): expand_configuration(row["configuration"])
                for row in csv.DictReader(handle)
            }
        with (HERE / "data/resonance.csv").open(encoding="utf-8") as handle:
            cls.lines = list(csv.DictReader(handle))

    def test_all_transition_labels_conserve_electrons(self):
        for row in self.lines:
            if row["set"] == "HLIKE_CONTROL":
                transition = build_hlike(
                    int(row["lower_n"]), int(row["upper_n"])
                )
            else:
                transition = build_transition(
                    self.elements[int(row["Z"])], row["transition"]
                )
            self.assertEqual(len(transition.lower), len(transition.upper))

    def test_h_lyman_is_cross_n(self):
        transition = build_transition(self.elements[1], "1s→2p")
        self.assertEqual(transition.removed_subshell, (1, "s"))
        self.assertEqual(transition.added_subshell, (2, "p"))

    def test_same_n_alkali(self):
        transition = build_transition(self.elements[11], "3s→3p")
        self.assertEqual(transition.removed_subshell[0], transition.added_subshell[0])

    def test_hlike_path_scaling_and_action(self):
        for row in hlike_pathway_controls():
            self.assertAlmostEqual(row["path_ratio"], row["path_expected"], places=12)
            self.assertAlmostEqual(row["period_ratio"], row["period_expected"], places=12)
            self.assertAlmostEqual(
                row["angular_rate_ratio"], row["angular_rate_expected"], places=12
            )
            self.assertLess(abs(row["lower_action_residual"]), 1e-9)
            self.assertLess(abs(row["upper_action_residual"]), 1e-9)

    def test_axis_around_geometry_is_unit_and_deterministic(self):
        seats = expand_configuration("[Ne]3s2 3p4")
        first = angular_directions(seats)
        second = angular_directions(seats)
        self.assertTrue((first == second).all())
        for norm in (first * first).sum(axis=1):
            self.assertAlmostEqual(float(norm), 1.0, places=12)

    def test_phase_minimisation_is_physical(self):
        seats = expand_configuration("[He]2s1")
        result = optimise_phases(
            3, seats, AngularParameters(), swept=True, divisions=4
        )
        self.assertTrue(result.state.physical)
        self.assertTrue(result.energy_eV < 0)


if __name__ == "__main__":
    unittest.main()
