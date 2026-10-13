"""PPT01 blank-slate pass (2026-10-13). Registration: PPT01_RESET_ASSESSMENT_2026-10-13.md sections 0-2 (written before this file existed).
Run from the repository root: python -I Investigations/02_Particle_Physics_and_Topology/PPT01_Vortex_Equilibrium_Quantisation/ppt01_reset_1.py
Author: J. C. Harvey, Melbourne."""
import math

# measured constants as in sdt::laws::measured (CODATA 2018 values used by the engine)
c = 299792458.0
hbar = 1.054571817e-34
m_e = 9.1093837015e-31
m_p = 1.67262192369e-27


def solve_rho(p, q):
    """fixed-point solve of rho = (q/p)/rho (Eq. 1 generalised with Eq. 4), damped geometric mean; independent of the closed form"""
    rho = 3.0
    for _ in range(200):
        rho = math.sqrt(rho * ((q / p) / rho)) if False else 0.5 * (rho + (q / p) / rho)
    return rho


def speeds(p, q):
    rho = solve_rho(p, q)
    vT = 1.0 / math.sqrt(1.0 + rho * rho)   # in units of c, from the budget with vP = rho vT
    vP = rho * vT
    return rho, vT, vP


def closed(p, q):
    return math.sqrt(q / p), math.sqrt(p / (p + q)), math.sqrt(q / (p + q))


cases = [('W=1 (1,1)', 1, 1), ('W=2 (1,2)', 1, 2), ('W=3 (1,3)', 1, 3), ('trefoil (2,3)', 2, 3), ('(2,5)', 2, 5), ('(3,4)', 3, 4)]
worst = 0.0
print('case            R/a        v_T/c      v_P/c      budget residual   closed-form diff   knot?')
for name, p, q in cases:
    rho, vT, vP = speeds(p, q)
    cr, cT, cP = closed(p, q)
    d = max(abs(rho - cr), abs(vT - cT), abs(vP - cP))
    worst = max(worst, d)
    knot = math.gcd(p, q) == 1 and min(p, q) >= 2
    print('%-14s %9.6f  %9.6f  %9.6f  %15.2e  %16.2e   %s' % (name, rho, vT, vP, vT * vT + vP * vP - 1.0, d, 'knot' if knot else 'unknot'))
print('[VERIFICATION] independent solve against the closed forms (6)-(11): worst difference %.2e (gate 1e-12): %s' % (worst, 'met' if worst < 1e-12 else 'NOT MET'))

print()
print('Electron (1,1), mass m_e:')
re_, te, pe = speeds(1, 1)
a_e = hbar / (m_e * pe * c)
R_e = hbar / (m_e * te * c)
print('  a_e = hbar/(m_e v_P) = %.6e m ; R_e = hbar/(m_e v_T) = %.6e m ; sqrt(2) lambda-bar_C = %.6e m' % (a_e, R_e, math.sqrt(2) * hbar / (m_e * c)))
print()
for label, (p, q) in (('(a) proton as W = 3 (1,3)', (1, 3)), ('(b) proton as trefoil (2,3)', (2, 3))):
    rho, vT, vP = speeds(p, q)
    a_p = hbar / (m_p * vP * c)
    R_p = hbar / (m_p * vT * c)
    print('%s: R/a %.6f, v_T %.6f c, v_P %.6f c ; a_p = %.6e m, R_p = %.6e m ; a_e/a_p = %.4f, R_e/R_p = %.4f (mass ratio m_p/m_e = %.5f is a census input)' % (label, rho, vT, vP, a_p, R_p, a_e / a_p, R_e / R_p, m_p / m_e))
print()
print('Dual-proton discrepancy (D5): v_T(a) = %.4f c vs v_T(b) = %.4f c ; R/a (a) = %.4f vs (b) = %.4f' % (speeds(1, 3)[1], speeds(2, 3)[1], speeds(1, 3)[0], speeds(2, 3)[0]))
