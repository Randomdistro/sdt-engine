"""Whole-state nuclear-z and energy accounting."""

from __future__ import annotations

import numpy as np

from . import constants as K
from .dynamics import AtomicState, ModelParameters
from .geometry import pair_distances, positions


def nuclear_z_state(state: AtomicState,
                    parameters: ModelParameters) -> float:
    if not state.seats:
        return 0.0
    attraction = state.Z * float(np.sum(1.0 / state.radii))
    pos = positions(state.radii, state.directions)
    distance = pair_distances(pos)
    n_vals = np.array([seat.n for seat in state.seats], dtype=int)
    same = n_vals[:, None] == n_vals[None, :]
    gmat = np.where(same, parameters.g_same, parameters.g_cross).astype(float)
    iu = np.triu_indices(len(state.seats), k=1)
    pair = float(np.sum(gmat[iu] / distance[iu]))
    return K.R_E * (attraction - pair)


def state_energy_eV(state: AtomicState,
                    parameters: ModelParameters,
                    A: int | None = None) -> float:
    energy = -0.5 * K.ME_C2_EV * nuclear_z_state(state, parameters)
    if A is None:
        return energy
    return energy * K.mu_over_me(A, state.Z)


def frozen_seat_binding_eV(state: AtomicState, seat_index: int,
                           A: int | None = None) -> float:
    energy = 0.5 * K.ME_C2_EV * float(state.depth_z[seat_index])
    if A is None:
        return energy
    return energy * K.mu_over_me(A, state.Z)
