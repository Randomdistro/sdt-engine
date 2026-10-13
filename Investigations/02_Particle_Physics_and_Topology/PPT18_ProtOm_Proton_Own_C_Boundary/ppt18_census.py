# PPT18 stage 3 census (2026-10-12). Registration: PROMPT.md addendum (e). Not evidence (census).
import re, random, math
txt = open('ppt18_stage3_results.txt', encoding='utf-8').read().splitlines()
cells = []; mover = None; hyd = False
for L in txt:
    m = re.match(r'MOVER: (.*) \(', L)
    if m: mover = m.group(1); continue
    if L.startswith('HYDROGEN-LADDER'): mover = 'electron (hydrogen ladder)'; hyd = True; continue
    if mover and '->' in L and not L.strip().startswith('transition'):
        name = L[:30].strip(); v = L[30:].split()
        try:
            if hyd: cells += [(mover, name, 'F', float(v[1])), (mover, name, 'H', float(v[2]))]
            else:   cells += [(mover, name, 'F', float(v[1])), (mover, name, 'H', float(v[2])), (mover, name, 'B', float(v[3]))]
        except ValueError: pass
ref = {'e':0.51099895,'mu':105.6583755,'pi0':134.9768,'pi+-':139.57039,'K+-':493.677,'K0':497.611,'eta':547.862,'rho':775.26,'omega':782.66,'K*':891.67,"eta'":957.78,
       'p':938.27209,'n':939.56542,'Delta-N':293.7,'n-p':1.29333,'n-p-e':0.78233,'B_d':2.22457,'B_t':8.48180,'B_h':7.71804,'B_alpha':28.2957,
       'B_d native':1.44225,'B_t native':6.91714,'B_h native':6.93574,'B_alpha native':26.73102,'B/A peak Ni62':8.7945,'B/A alpha':7.0739,'X17':16.94,'2m_e':1.02200}
def band(r): return 'B1' if r<=1e-3 else 'B2' if r<=1e-2 else 'B3' if r<=3e-2 else None
construction = []; hits = []
for c in cells:
    for k, v in ref.items():
        r = abs(c[3]/v - 1); b = band(r)
        if b:
            is_constr = ('Om_p' in c[1] and c[1].startswith('inf') and c[2] in ('F','B') and ((k=='e' and 'electron m_e' in c[0]) or (k=='p' and 'proton' in c[0])))
            (construction if is_constr else hits).append((b, r, c, k))
vals = [c[3] for c in cells if c[3] > 0]
print(f'cells: {len(cells)} (distinct values {len(set(round(x,6) for x in vals))}); references: {len(ref)}; comparisons: {len(cells)*len(ref)}')
print('\nBY CONSTRUCTION (not counted):')
for b, r, c, k in construction: print(f'  {c[0]:28s} {c[1]:28s} {c[2]}  {c[3]:.6g} MeV = {k} ({100*r:.4f}%)')
print('\nMATCHES (B1-B3):')
for b, r, c, k in sorted(hits, key=lambda h: h[1]): print(f'  {b}  {100*r:6.3f}%   {c[0]:28s} {c[1]:28s} {c[2]}  {c[3]:.6g} MeV  ~ {k} ({ref[k]} MeV)')
nB2 = sum(1 for h in hits if h[0] in ('B1','B2')); nB3 = len(hits)
print(f'\nobserved: B1+B2 matches {nB2}; B1-B3 matches {nB3}')
random.seed(20261012); ge2 = ge3 = 0; tot2 = tot3 = 0; N = 20000
for _ in range(N):
    f = math.exp(random.uniform(math.log(0.5), math.log(2)))
    m2 = m3 = 0
    for x in vals:
        for v in ref.values():
            r = abs(x*f/v - 1)
            if r <= 1e-2: m2 += 1
            if r <= 3e-2: m3 += 1
    tot2 += m2; tot3 += m3; ge2 += m2 >= nB2; ge3 += m3 >= nB3
print(f'chance baseline (grid x random factor in [0.5,2], {N} trials): mean B1+B2 {tot2/N:.2f}, P(>= observed) {ge2/N:.3f} ; mean B1-B3 {tot3/N:.2f}, P(>= observed) {ge3/N:.3f}')
chosen = [c for c in cells if c[0].startswith('proton') and c[1].startswith('inf -> 2R_p') and c[2]=='H'][0]
best = min(ref.items(), key=lambda kv: abs(chosen[3]/kv[1]-1))
print(f'\nCHOSEN CELL: {chosen[0]} {chosen[1]} {chosen[2]} = {chosen[3]:.6g} MeV ; nearest reference {best[0]} {best[1]} MeV ({100*(chosen[3]/best[1]-1):+.1f}%)')
