# Mass-free koppa consistency test on NASA Exoplanet Archive multi-planet transit data.
# Claim under test: every planet of one host must return the SAME stellar koppa-density
#   q = kappa_star / R_star^3 = (4 pi^2 / c^2) * (a/R_star)^3 / P^2
# from photometric observables alone (a/R* from transit geometry, P from timing).
# No G, no kilograms, no stellar mass anywhere in the chain.
# Negative control: reassign planets to pseudo-systems at random -> agreement must collapse.
import csv, math, random, statistics

c = 299792458.0
DAY = 86400.0

rows = []
with open("koppa_multiplanet.csv", newline="", encoding="utf-8") as f:
    for r in csv.DictReader(f):
        try:
            P = float(r["pl_orbper"]) * DAY
            aR = float(r["pl_ratdor"])
            if P > 0 and aR > 0:
                rows.append((r["hostname"], r["pl_name"], P, aR))
        except (ValueError, KeyError):
            pass

def q_of(P, aR):  # koppa-density [m^-2 -> use SI], = (4pi^2/c^2) * aR^3 / P^2
    return (4 * math.pi**2 / c**2) * aR**3 / P**2

systems = {}
for host, name, P, aR in rows:
    systems.setdefault(host, []).append(q_of(P, aR))
multi = {h: qs for h, qs in systems.items() if len(qs) >= 2}

def intra_devs(sysmap):
    devs = []
    for qs in sysmap.values():
        m = statistics.median(qs)
        devs.extend(abs(q / m - 1) for q in qs if m > 0)
    return devs

real = intra_devs(multi)

# negative control: same system-size structure, random planet assignment
random.seed(42)
allq = [q for qs in multi.values() for q in qs]
ctrl_devs = []
for _ in range(10):
    pool = allq[:]
    random.shuffle(pool)
    fake, i = {}, 0
    for h, qs in multi.items():
        fake[h] = pool[i:i + len(qs)]
        i += len(qs)
    ctrl_devs.extend(intra_devs(fake))

def pct(v, p):
    s = sorted(v)
    return s[min(len(s) - 1, int(p / 100 * len(s)))]

print(f"planets used: {len(rows)}   multi-planet hosts: {len(multi)}   planets in hosts: {len(real)}")
print(f"REAL     median |dev| = {statistics.median(real)*100:6.2f}%   75th = {pct(real,75)*100:6.2f}%   90th = {pct(real,90)*100:6.2f}%")
print(f"SHUFFLED median |dev| = {statistics.median(ctrl_devs)*100:6.2f}%   75th = {pct(ctrl_devs,75)*100:6.2f}%   90th = {pct(ctrl_devs,90)*100:6.2f}%")
frac10 = sum(1 for d in real if d < 0.10) / len(real)
cfrac10 = sum(1 for d in ctrl_devs if d < 0.10) / len(ctrl_devs)
print(f"fraction of planets within 10% of their system median:  real {frac10*100:.1f}%  vs shuffled {cfrac10*100:.1f}%")

# Anchor: the Sun from Earth's orbit, same formula (a/R_sun = 215.032, P = 365.2564 d)
q_sun = q_of(365.2564 * DAY, 215.032)
print(f"\nSun (from Earth's orbit, ratios only): kappa/R^3 = {q_sun:.3e} m^-2")
print(f"  -> kappa_sun = q * R_sun^3 = {q_sun * 6.957e8**3:.1f} m   (GM/c^2 = 1476.6 m, CODATA)")
# density gauge: kappa/R^3 = (4 pi G / 3 c^2) * rho  ->  rho = q * 3c^2/(4 pi G) [SI display only]
G = 6.674e-11
print(f"  -> implied mean density = {q_sun * 3 * c**2 / (4 * math.pi * G):.1f} kg/m^3 (Sun ~1408)")
