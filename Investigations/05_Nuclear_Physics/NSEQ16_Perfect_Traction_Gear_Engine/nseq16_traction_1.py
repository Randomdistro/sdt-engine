# NSEQ16 section 12: identical-angle traction on the wound ring. Registration: NSEQ16_RESET_ASSESSMENT_2026-10-14.md section 12 (written before this file existed).
# Run: python -I nseq16_traction_1.py        Author: J. C. Harvey, Melbourne.
import math, sys
import numpy as np
sys.stdout.reconfigure(encoding='utf-8')
R, A_ = 0.9987379362077577, 0.05042358791441983
TAU = 2 * math.pi

def tang(phi, p=4, q=3):
    """unit tangent of the curve (radial, azimuthal, vertical) at poloidal phase phi: theta = p u, phi = q u + rho"""
    rad = R + A_ * np.cos(phi)
    t = np.stack([-q * A_ * np.sin(phi), p * rad, q * A_ * np.cos(phi)], axis=-1)
    return t / np.linalg.norm(t, axis=-1, keepdims=True)

def phi_out(psi, p=4, q=3):
    """poloidal phase of the outermost strand at an azimuth where the phase of strand 0 is psi: phases psi + 2 pi q j / p, largest cosine wins"""
    psi = np.asarray(psi, dtype=float)
    cands = psi[..., None] + TAU * q * np.arange(p) / p
    j = np.argmax(np.cos(cands), axis=-1)
    ph = np.take_along_axis(cands, j[..., None], axis=-1)[..., 0]
    return (ph + math.pi) % TAU - math.pi

print('NSEQ16 section 12: identical-angle traction on the wound ring (engine H1 curve, p = 4 tours, q = 3 cross-section turns)')
# ---- V1 tangent against finite difference
rng = np.random.default_rng(20261016)
worst = 0.0
for _ in range(200):
    u = TAU * rng.random(); rho = TAU * rng.random(); h = 1e-6
    def K(uu):
        phi = 3 * uu + rho; rad = R + A_ * math.cos(phi); th = 4 * uu
        return np.array([rad * math.cos(th), rad * math.sin(th), A_ * math.sin(phi)])
    d = (K(u + h) - K(u - h)) / (2 * h)
    th = 4 * u; rh = np.array([math.cos(th), math.sin(th), 0.0]); ah = np.array([-math.sin(th), math.cos(th), 0.0])
    loc = np.array([d @ rh, d @ ah, d[2]]); loc /= np.linalg.norm(loc)
    worst = max(worst, np.linalg.norm(loc - tang(3 * u + rho)))
print(f'[V1] analytic unit tangent vs central difference, 200 random points: max difference {worst:.2e} (gate 1e-6) -> {"met" if worst < 1e-6 else "NOT MET"}')

def pair(fam, pa, pb):
    """slip |v_A - v_B| for contact families; A faces +x (radial = +x, azimuthal = +y, vertical = z); pa, pb poloidal phases of the facing outermost strands"""
    a = tang(pa); b = tang(pb)
    if fam == 'F1': v = np.stack([-b[..., 0], -b[..., 1], b[..., 2]], axis=-1)     # same chirality, same circulation, rotated pi about z
    elif fam == 'F2': v = -np.stack([-b[..., 0], -b[..., 1], b[..., 2]], axis=-1)  # same chirality, reversed circulation
    elif fam == 'F3': v = np.stack([-b[..., 0], b[..., 1], b[..., 2]], axis=-1)    # mirror across the contact plane
    elif fam == 'F4': v = np.stack([-b[..., 0], -b[..., 1], -b[..., 2]], axis=-1)  # mirror across the ring plane, circulation kept
    elif fam == 'F5': v = np.stack([b[..., 0], b[..., 1], b[..., 2]], axis=-1)     # F4 with circulation reversed
    return np.linalg.norm(a - v, axis=-1)

# ---- V2 known answers
ph = np.linspace(-math.pi / 4, math.pi / 4, 9)
f1 = pair('F1', ph, ph); f3 = pair('F3', ph, -ph)
print(f'[V2] F1 (like, co-rotating) slip at equal phases: min {f1.min():.4f}, max {f1.max():.4f} (expect about 2); F3 with phi_B = -phi_A: max slip {f3.max():.1e} (expect 0) -> {"met" if f1.min() > 1.9 and f3.max() < 1e-12 else "NOT MET"}')

# ---- V3 equator azimuths
print('[V3] azimuths per ring at which an outermost strand sits exactly on the outer equator (phi_out = 0), theta over one revolution:')
theta = np.linspace(0, TAU, 720001)[:-1]
for p in (2, 4):
    row = []
    for q in range(1, 8):
        if math.gcd(p, q) != 1: row.append(f'q={q}:coprime-fail'); continue
        po = phi_out(q * theta / p, p, q)       # rho = 0
        crossings = int(np.sum((po[:-1] < 0) & (po[1:] >= 0) & (np.abs(po[1:] - po[:-1]) < 1.0)))
        crossings += int((po[-1] < 0) and (po[0] >= 0) and abs(po[0] - po[-1]) < 1.0)
        row.append(f'q={q}:{crossings}')
    print(f'     p = {p}: ' + '  '.join(row) + '   (analytic q/gcd(q,p) = q for coprime pairs)')

# ---- slip maps over the phase pair
N = 1441
psi = np.linspace(-math.pi / 4, math.pi / 4, N)            # phi_out ranges over (-pi/4, pi/4]
PA, PB = np.meshgrid(psi, psi, indexing='ij')
print('\n[families] slip = |tau_A - tau_B| at the facing outermost strands; phi_out in (-pi/4, pi/4]; grid 1441 x 1441')
for fam, label in (('F1', 'like: same chirality, same circulation'), ('F2', 'same chirality, reversed circulation'), ('F3', 'mirror across contact plane (p/n complement)'),
                   ('F4', 'ring-plane mirror, circulation kept'), ('F5', 'ring-plane mirror, circulation reversed')):
    S = pair(fam, PA, PB)
    best = S.min(axis=1)          # best partner phase for each A phase
    same = np.diag(S)
    mir = np.array([pair(fam, psi[i], -psi[i]) for i in range(0, N, 1)])
    print(f'  {fam} {label}: global min {S.min():.3e}; worst-case best-partner slip over A phases {best.max():.3e}; literal same phase (phi_B = phi_A): min {same.min():.3e}, max {same.max():.3e}; mirrored phase (phi_B = -phi_A): min {mir.min():.3e}, max {mir.max():.3e}')

# ---- reading R1 closed form check, hand estimate
a = A_
phi = math.pi / 4
T = math.sqrt(9 * a * a * math.sin(phi) ** 2 + 9 * a * a * math.cos(phi) ** 2 + 16 * (R + a * math.cos(phi)) ** 2)
print(f'\n[hand estimate check] |T| at phi = pi/4: sqrt(9a^2 + 16(R + a cos phi)^2) = {T:.4f}; radial component 3a sin phi = {3 * a * math.sin(phi):.5f}; 2 x 3a sin phi / |T| = {2 * 3 * a * math.sin(phi) / T:.5f}')

# ---- orientation quantisation: identical rings (same rho), partner free to turn about its own axis by alpha
print('\n[orientation] identical rings (rho = 0 for both). Ring A turned by alpha_A about its axis faces the contact at local azimuth -alpha_A; the F3/F5 mesh condition (zero slip) reads')
print('     red(3 theta_B/4) = -red(3 theta_A/4)   [F3, partner phase mirrored]   and   red(...) equal   [F5]; scanning the partner turn alpha_B for fixed alpha_A:')
al = np.linspace(0, TAU, 360001)[:-1]
for alpha_A in (0.0, 0.7, 2.1, 5.0):
    thA = -alpha_A; pa = phi_out(3 * thA / 4)
    thB = -al; pb = phi_out(3 * thB / 4)
    sl = pair('F3', pa * np.ones_like(al), pb)             # B0 is an A-type ring facing +x, then mirrored
    loc = np.where((sl[1:-1] <= sl[:-2]) & (sl[1:-1] <= sl[2:]) & (sl[1:-1] < 1e-5))[0] + 1
    centres = [float(al[i]) for i in loc]
    pred = sorted(((-alpha_A + TAU * m / 3) % TAU) for m in range(3))
    print(f'     alpha_A = {alpha_A:.3f}: zero-slip partner turns alpha_B0 = ' + ', '.join(f'{c:.4f}' for c in centres) + f' (count {len(centres)}); predicted -alpha_A + 2 pi m/3 = ' + ', '.join(f'{c:.4f}' for c in pred))
# worst slip anywhere
Sall = pair('F3', PA, PB)
print(f'     worst slip of a mirror partner at an unmatched turn (any phases): {Sall.max():.4f} of s (i.e. {100 * Sall.max():.2f} %)')

# ---- contact distance spread
c1 = 2 * R + 0.0713 + 2 * A_ * math.cos(math.pi / 4); c2 = 2 * R + 0.0713 + 2 * A_
print(f'\n[contact distance] D = 2R + 2s + a(cos phi_A + cos phi_B), s = 0.03565: phi = pi/4 both: {c1:.4f}; phi = 0 both: {c2:.4f}; spread {100 * (c2 - c1) / c2:.2f} %')
