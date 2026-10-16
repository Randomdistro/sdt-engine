# NSEQ19 triton-shell series analysis (G2). Reads nseq19_series_off0..4.txt (5 independent seed offsets, as registered).
import statistics as s, glob, sys
sys.stdout.reconfigure(encoding='utf-8')
data = {}
for f in sorted(glob.glob('nseq19_series_off[0-4].txt')):
    for l in open(f).readlines()[1:]:
        p = l.split()
        if p[7] != 'OK':
            data.setdefault((int(p[0]), int(p[1])), []).append(None); continue
        data.setdefault((int(p[0]), int(p[1])), []).append((float(p[9]), float(p[10]), float(p[11])))
def stats(vals, i):
    v = [x[i] for x in vals if x]
    return (s.mean(v), s.stdev(v) if len(v) > 1 else 0.0, len(v))
for name, z0, a0, n in (('T8 series n_d=18', 20, 40, 9), ('T10 series n_d=30', 32, 64, 19)):
    print(name, '(5 independent seeds; E_ext = max radius + 1; rms = rms unit radius; cp = close-packed (A/eta)^(1/3) + 1)')
    print(' n_t  Z   A   packed  E_ext mean+-sd   rms mean+-sd   E/cp   rms/rms_cp')
    res = {}
    for nt in range(n):
        Z, A = z0 + nt, a0 + 3 * nt
        v = data.get((Z, A))
        if not v or not any(v):
            print(nt, Z, A, 'missing'); continue
        E = stats(v, 0); r = stats(v, 1); cp = [x for x in v if x][0][2]
        res[nt] = (E[0], r[0], E[1], r[1])
        print(f' {nt:3d} {Z:3d} {A:3d}  {E[2]}/5   {E[0]:.3f}+-{E[1]:.3f}   {r[0]:.3f}+-{r[1]:.3f}   {E[0] / cp:.3f}   {r[0] / (0.775 * (cp - 1)):.3f}')
    base = res[0]
    print(' opening (n_t=1 minus n_t=0): E %+.3f (pooled sd %.3f), rms %+.3f' % (res[1][0] - base[0], (res[1][2] ** 2 + base[2] ** 2) ** .5, res[1][1] - base[1]))
    if n == 9:
        print(' T8 closure (n_t=8 minus n_t=0): E %+.3f, rms %+.3f' % (res[8][0] - base[0], res[8][1] - base[1]))
    else:
        print(' T8 closure (n_t=8 minus n_t=0): E %+.3f ; T10 opening (n_t=9 minus 8): E %+.3f ; T10 closure (n_t=18 minus 8): E %+.3f' % (res[8][0] - base[0], res[9][0] - res[8][0], res[18][0] - res[8][0]))
    print()
