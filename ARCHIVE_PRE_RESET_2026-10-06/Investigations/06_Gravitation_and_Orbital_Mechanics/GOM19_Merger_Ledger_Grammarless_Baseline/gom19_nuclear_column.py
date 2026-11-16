import re
U=931494.10242  # keV per u (c^2 conversion); only bookkeeping for sum of masses
ME={}
for l in open('../../../Datasets/nuclear/AME2020_mass_excess.txt',encoding='latin-1'):
    if not re.match(r'^\s*-?\d+\s+\d+\s+\d+\s+\d+\s',l): continue
    try:
        Z=int(l[9:14]); A=int(l[14:19]); el=l[20:23].strip(); me=float(l[28:42].replace('#','').strip())
    except: continue
    ME[(Z,A)]=me
assert abs(ME[(0,1)]-8071.31806)<1e-4 and abs(ME[(1,1)]-7288.971064)<1e-6 and abs(ME[(2,4)]-2424.91587)<1e-4
print('P0: AME2020 file parsed, %d nuclides; n, 1H, 4He mass excess checks pass'%len(ME))
N={'n':(0,1),'p':(1,1),'d':(1,2),'t':(1,3),'3He':(2,3),'4He':(2,4),'6Li':(3,6),'7Li':(3,7),'7Be':(4,7)}
def f(ins,outs):
    zin=sum(N[x][0] for x in ins); ain=sum(N[x][1] for x in ins); zout=sum(N[x][0] for x in outs); aout=sum(N[x][1] for x in outs); assert (zin,ain)==(zout,aout),(ins,outs)
    Q=sum(ME[N[x]] for x in ins)-sum(ME[N[x]] for x in outs)
    M=sum(N[x][1]*U+ME[N[x]] for x in ins)
    return Q,Q/M
ev=[('p+n->d',['p','n'],['d'],1.0,0.1185),('p+d->3He',['p','d'],['3He'],2.0,0.1952),('p+t->4He',['p','t'],['4He'],3.0,0.5288),
    ('d+d->4He',['d','d'],['4He'],1.0,0.6357),('d+t->4He+n',['d','t'],['4He','n'],1.5,0.3754),('n+3He->4He',['n','3He'],['4He'],3.0,0.5490),
    ('p+6Li->7Be',['p','6Li'],['7Be'],6.0,None),('n+6Li->7Li',['n','6Li'],['7Li'],6.0,None),('d+4He->6Li',['d','4He'],['6Li'],2.0,None),
    ('t+4He->7Li',['t','4He'],['7Li'],4/3,None),('3He+4He->7Be',['3He','4He'],['7Be'],4/3,None)]
print('\nP3 nuclear column: f = Q/sum(m c^2) (atomic masses; electrons cancel)')
res={}
for nm,i,o,q,anch in ev:
    Q,fr=f(i,o); res[nm]=fr*100
    tag='' if anch is None else '  anchor %.4f%%  rel %+.2f%%  %s'%(anch,(fr*100/anch-1)*100,'PASS' if abs(fr*100/anch-1)<0.005 else 'FAIL')
    print(f'  {nm:14s} q={q:5.2f} Q={Q:10.3f} keV  f={fr*100:.4f}%{tag}')
print('\nF4 fixed-q composition check at q=1: p+n->d f=%.4f%%, d+d->4He f=%.4f%%, ratio %.2f (spec 5.4x); flat would be ratio ~1'%(res['p+n->d'],res['d+d->4He'],res['d+d->4He']/res['p+n->d']))
print('q=3: p+t->4He %.4f%% vs n+3He->4He %.4f%% (same q, different composition); q=6: p+6Li %.4f%% vs n+6Li %.4f%%'%(res['p+t->4He'],res['n+3He->4He'],res['p+6Li->7Be'],res['n+6Li->7Li']))
print('\nP2 gate arithmetic on declared anchors only: ledger f(1)=1/16=6.25%%; NR 4.83%% -> ratio %.3f; GW150914 4.6%% -> ratio %.3f; within factor 2: %s'%(6.25/4.83,6.25/4.6,(0.5<6.25/4.83<2 and 0.5<6.25/4.6<2)))
print('a* fork: OPEN (no P1a mechanism; no catalog comparison made, per F1)')
