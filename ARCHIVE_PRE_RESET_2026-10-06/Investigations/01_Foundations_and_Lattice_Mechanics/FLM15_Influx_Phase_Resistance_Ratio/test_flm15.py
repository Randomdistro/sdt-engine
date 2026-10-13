from __future__ import annotations

import inspect
import unittest

import numpy as np

import flm15_influx_phase_resistance as flm15


class FLM15InstrumentTests(unittest.TestCase):
    def test_curves_are_closed_and_normalised(self) -> None:
        for shape in ("circle", "trefoil"):
            p = flm15.curve(shape, 192)
            self.assertAlmostEqual(float(np.mean(np.sum(p*p, axis=1))), 1.0, places=12)
            self.assertLess(float(np.linalg.norm(p.mean(axis=0))), 1e-12)

    def test_isotropic_identity(self) -> None:
        rng = np.random.default_rng(15)
        g = rng.normal(size=(32, 3))
        n = rng.normal(size=(200000, 3))
        n /= np.linalg.norm(n, axis=1)[:, None]
        directional = np.mean((n @ g.T) ** 2)
        trace_third = np.mean(np.sum(g*g, axis=1)) / 3.0
        self.assertLess(abs(directional / trace_third - 1.0), 0.01)

    def test_circulation_squared_scaling(self) -> None:
        p = flm15.curve("circle", 64)
        x = (flm15.halton(2048, 15) * 2.0 - 1.0) * 2.0
        g1 = flm15.phase_gradient(x, p, 0.12, 1.0)
        g2 = flm15.phase_gradient(x, p, 0.12, 2.0)
        self.assertTrue(np.allclose(g2, 2.0*g1))

    def test_matched_pair_is_positive(self) -> None:
        circle, trefoil, ratio = flm15.matched_pair(
            0.5, 64, 4096, 0.12, 5.0, 15
        )
        self.assertGreater(circle.response, 0.0)
        self.assertGreater(trefoil.response, 0.0)
        self.assertGreater(ratio, 0.0)

    def test_glancing_lock_partition(self) -> None:
        radii = np.array([0.0, 0.25, 1.0, 4.0])
        locked = flm15.relay_lock_fraction(radii, 1.0)
        wake = flm15.wake_emitting_fraction(radii, 1.0)
        self.assertTrue(np.allclose(locked, [0.0, 0.5, 1.0, 1.0]))
        self.assertTrue(np.allclose(locked + wake, 1.0))

    def test_engaged_volume_matches_analytic_integral(self) -> None:
        for component in ("locked", "wake"):
            analytic = flm15.analytic_engaged_volume(2.5, component)
            numeric = flm15.integrate_engaged_volume(2.5, component)
            self.assertLess(abs(numeric / analytic - 1.0), 1e-5)
        sphere = 4.0 * np.pi * 2.5**3 / 3.0
        partition = (
            flm15.analytic_engaged_volume(2.5, "locked")
            + flm15.analytic_engaged_volume(2.5, "wake")
        )
        self.assertAlmostEqual(partition / sphere, 1.0, places=12)

    def test_synchrony_endpoint_controls(self) -> None:
        single = flm15.analytic_engaged_volume(1.0)
        coincident = flm15.joint_locked_volume_equal_spheres(1.0, 0.0)
        separate = flm15.joint_locked_volume_equal_spheres(1.0, 2.0)
        self.assertAlmostEqual(coincident, single, places=12)
        self.assertAlmostEqual(separate, 2.0 * single, places=12)
        delta = flm15.synchrony_resistance_delta(3.0, coincident, 2.0 * single)
        self.assertAlmostEqual(delta, -single, places=12)

    def test_synchrony_overlap_converges(self) -> None:
        coarse = flm15.joint_locked_volume_equal_spheres(
            1.0, 1.0, samples=65536, seed=1501
        )
        fine = flm15.joint_locked_volume_equal_spheres(
            1.0, 1.0, samples=131072, seed=1501
        )
        self.assertLess(abs(coarse / fine - 1.0), 0.005)

    def test_close_packed_void_selection_is_target_free(self) -> None:
        unit = flm15.minimum_resistance_void_seat(1.0)
        scaled = flm15.minimum_resistance_void_seat(7.0)
        self.assertEqual(unit.name, "tetrahedral")
        self.assertEqual(unit.coordination, 4)
        self.assertEqual(scaled.name, unit.name)
        self.assertAlmostEqual(
            scaled.resistance_per_pressure
            / unit.resistance_per_pressure,
            7.0**3,
            places=11,
        )

    def test_lock_kernel_controls_pass(self) -> None:
        controls = flm15.lock_kernel_controls()
        for key, value in controls.items():
            if key.endswith("_pass"):
                self.assertTrue(value, key)

    def test_forward_source_has_no_particle_data_routes(self) -> None:
        source = inspect.getsource(flm15)
        forbidden = [
            "V_" + "disp",
            "R_" + "excl",
            "m_" + "p",
            "m_" + "e",
            "183" + "6",
        ]
        self.assertFalse([token for token in forbidden if token in source])


if __name__ == "__main__":
    unittest.main()
