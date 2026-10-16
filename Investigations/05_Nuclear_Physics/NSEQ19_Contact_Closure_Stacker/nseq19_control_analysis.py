# NSEQ19 post-seen control: like contact allowed (T8 series, 5 seeds) against the registered rule. Also corrects the significance quoted in the results note.
import statistics as s, glob, math, sys
sys.stdout.reconfigure(encoding='utf-8')
def load(pat):
    d = {}
    for f in sorted(glob.glob(pat)):
        for l in open(f).readlines()[1:]:
            p = l.split()
            if p[7] == 'OK': d.setdefault((int(p[0]), int(p[1])), []).append((float(p[9]), float(p[10]), float(p[11]), float(p[13])))
    return d
reg = load('nseq19_series_off[0-4].txt'); ctl = load('nseq19_ctrl_likefree_off[0-4].txt')
ETA = math.pi / math.sqrt(18)
def row(d, A):
    v = d[(20 + (A - 40) // 3, A)]; cp = v[0][2]; rcp = math.sqrt(3 / 5) * (cp - 1)
    return (s.mean(x[0] for x in v), s.stdev(x[0] for x in v), s.mean(x[1] for x in v), s.stdev(x[1] for x in v), s.mean(x[1] for x in v) / rcp, s.mean(x[3] for x in v), len(v))
print('T8 series: rms radius and r0-type ratio rms/rms_cp, rms_cp = sqrt(3/5) (A/eta)^(1/3); registered rule (no like contact) vs control (like contact allowed); mean degree')
print(' n_t   A | registered: rms+-sd   ratio   deg | control: rms+-sd   ratio   deg')
for nt in range(9):
    A = 40 + 3 * nt
    a = row(reg, A); b = row(ctl, A)
    print(f' {nt:3d} {A:3d} |   {a[2]:.3f}+-{a[3]:.3f}  {a[4]:.4f}  {a[5]:.2f} |   {b[2]:.3f}+-{b[3]:.3f}  {b[4]:.4f}  {b[5]:.2f}   (n={a[6]}/{b[6]})')
def slope(d):
    r = [row(d, 40 + 3 * nt)[4] for nt in range(9)]
    return (r[8] - r[0]) / 8, r
for name, d in (('registered', reg), ('control', ctl)):
    sl, r = slope(d)
    print(f'{name}: ratio n_t=0 -> 8: {r[0]:.4f} -> {r[8]:.4f}; slope per triton {sl:+.5f} of r0_cp = {sl * 0.9300 * 1000:+.2f} mfm per triton (corpus measured: -4 median, -11 heavy chains; NP30 section 6)')
# significance with standard errors (n = 5 seeds each)
def se_diff(sd0, sd1, n=5): return math.sqrt((sd0 ** 2 + sd1 ** 2) / n)
for lab, d in (('registered', reg), ('control', ctl)):
    a0 = row(d, 40); a1 = row(d, 43)
    print(f'{lab}: opening n_t 0->1: E {a1[0] - a0[0]:+.3f} (SE {se_diff(a0[1], a1[1]):.3f}, {(a1[0] - a0[0]) / se_diff(a0[1], a1[1]):.1f} sigma); rms {a1[2] - a0[2]:+.3f} (SE {se_diff(a0[3], a1[3]):.3f}, {(a1[2] - a0[2]) / se_diff(a0[3], a1[3]):.1f} sigma)')
