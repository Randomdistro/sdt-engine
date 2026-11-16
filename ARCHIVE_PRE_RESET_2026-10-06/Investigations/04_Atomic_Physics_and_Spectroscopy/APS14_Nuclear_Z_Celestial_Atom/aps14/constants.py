"""Canonical constants mirrored from Engine/include/sdt/laws.hpp.

Read-only. No local redefinition of engine values. Line citations are the
header as of 2026-08-13.
"""

import math

# sdt::laws::measured
C = 299_792_458.0                          # laws.hpp:110
HBAR = 1.054_571_817e-34                   # laws.hpp:111
ALPHA = 7.297_352_5693e-3                  # laws.hpp:126
H = 6.626_070_15e-34                       # laws.hpp:129
E_CHARGE = 1.602_176_634e-19               # laws.hpp:131
A0 = 5.291_772_109_03e-11                  # laws.hpp:143
R_E = 2.817_940_3262e-15                   # laws.hpp:144
M_E = 9.109_383_7015e-31                   # laws.hpp:147
M_P = 1.672_621_923_69e-27                 # laws.hpp:148
M_N = 1.674_927_498_04e-27                 # laws.hpp:149
R_INF = 1.097_373_156_8160e7               # laws.hpp:150
RY_EV = 13.605_693_122_994                 # laws.hpp:151

EV_TO_J = E_CHARGE                         # laws.hpp:200
ME_C2_EV = M_E * C * C / E_CHARGE
# Coulomb identity: k_e e^2 = alpha * hbar * c  (electropause P_eff chain)
OCCLUSION_K = ALPHA * HBAR * C
TWO_PI = 2.0 * math.pi
HC_EV_NM = (H * C / E_CHARGE) * 1e9


def mu_over_me(A: int, Z: int) -> float:
    """Two-body reduced-mass factor. Nuclear mass = Z m_p + (A-Z) m_n."""
    if A <= 0:
        return 1.0
    neutrons = max(A - Z, 0)
    m_nuc = Z * M_P + neutrons * M_N
    return m_nuc / (M_E + m_nuc)
