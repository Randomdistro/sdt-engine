import re
rows={}
for l in open('../../../Datasets/nuclear/NUBASE2020.txt',encoding='latin-1'):
    if l.startswith('#') or len(l)<120: continue
    try: A=int(l[0:3]); zz=l[4:8]; Z=int(zz[:3]); i=int(zz[3])
    except: continue
    if i!=0: continue
    try: me=float(l[18:31].replace('#','').strip())
    except: continue
    rows[(Z,A)]=dict(me=me,hl=l[69:80].strip(),dm=l[119:209].strip(),syst='#' in l[18:31],stable='stbl' in l[69:80])
print('ground-state rows:',len(rows))
def is_ec(dm): return bool(re.search(r'(^|;)(EC|B\+)\s*[=?~]?',dm)) and re.search(r'(^|;)(EC|B\+)=',dm) is not None
ec=[(Z,A) for (Z,A),r in rows.items() if is_ec(r['dm']) and (Z-1,A) in rows]
meas=[k for k in ec if not rows[k]['syst'] and not rows[(k[0]-1,k[1])]['syst']]
print('EC/B+ parents with daughter in table:',len(ec),'| both masses measured (no # systematics):',len(meas))
pos=[k for k in meas if rows[k]['me']-rows[(k[0]-1,k[1])]['me']>0]
print('Q_EC>0 among measured:',len(pos),'of',len(meas))
# V: Be-7 Q_EC ~ 861.8 keV, Na-22 ~ 2842 keV (literature memory, VERIFY)
for k,lit in (((4,7),861.8),((11,22),2842.0)):
    q=rows[k]['me']-rows[(k[0]-1,k[1])]['me']; print(f'  V Q_EC {k}: {q:.1f} keV (lit memory {lit}, VERIFY)')
def valid_alt(Z,A): nt=A-2*Z+1; nd=3*Z-A-3; return nt>=0 and nd>=0
def valid_std(Z,A): nt=A-2*Z; nd=3*Z-A-2; return nt>=0 and nd>=0
for lab,S in (('EC/B+ parents (Z>=2)',[k for k in meas if k[0]>=2]),('all ground-state cells (Z>=2) null',[k for k in rows if k[0]>=2])):
    a=sum(valid_alt(*k) for k in S); s=sum(valid_std(*k) for k in S)
    print(f'{lab}: n={len(S)} alt valid {a} ({100*a/len(S):.1f}%), std valid {s} ({100*s/len(S):.1f}%), alt invalid {len(S)-a} ({100*(len(S)-a)/len(S):.1f}%)')
inv=[k for k in meas if k[0]>=2 and not valid_alt(*k)]
print('invalid-alt EC parents: N-Z range',min(k[1]-2*k[0] for k in inv) if inv else None,'..',max(k[1]-2*k[0] for k in inv) if inv else None, '| examples',inv[:6])
# split by half-life class (stable-line neighbours vs far proton-rich)
from collections import Counter
print('invalid-alt Z values:',sorted(set(k[0] for k in inv)),' max A',max(k[1] for k in inv))
print('invalid by N-Z:',Counter(k[1]-2*k[0] for k in inv))
# among EC parents, split by heavy (Z>=20) vs light
for lab,f in (('Z<20',lambda k:k[0]<20),('Z>=20',lambda k:k[0]>=20)):
    S=[k for k in meas if k[0]>=2 and f(k)]; a=sum(valid_alt(*k) for k in S); print(f'{lab}: n={len(S)} alt valid {a} ({100*a/len(S):.1f}%)')
