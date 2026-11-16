"""Independent weighted coherent-overlap control; supplied spheres, not nuclear energy."""
from pathlib import Path
import json,math
import numpy as np
from numpy.polynomial.legendre import leggauss
RUN=Path(__file__).resolve().parent
b=1.1;d=2.;xmax=b-d/2
# For no triple overlap, saturated max engagement = sum(parts)-sum(pair minima).
exact_lens=8*math.pi/(5*math.sqrt(b))*((b**4.5-(b*b-2*d*xmax)**2.25)/(4.5*d)-((d/2)**3.5-(d/2-xmax)**3.5)/3.5)
rows=[]
for N in [32,64,128]:
    xx,wx=leggauss(N);tt,wt=leggauss(N);integral=0.
    for x,w in zip((xx+1)*xmax/2,wx*xmax/2):
        rho_max=math.sqrt(max(0,b*b-(d/2+x)**2));rho=(tt+1)*rho_max/2
        f=((d/2-x)**2+rho*rho)**.25/math.sqrt(b)
        integral+=w*float(np.sum(wt*rho_max/2*2*math.pi*rho*f))*2
    union=4*8*math.pi*b**3/7-4*integral
    rows.append({'N':N,'pairMinimumWeightIntegralRp3':integral,'analyticRp3':exact_lens,'relativeError':abs(integral-exact_lens)/exact_lens,'weightedUnionRp3':union})
result={'scope':'coherent saturated supplied-domain mathematical control; b=1.1Rp <sqrt(2)Rp excludes triple overlap; no alpha boundary derivation','rows':rows,'analyticUnionRp3':4*8*math.pi*b**3/7-4*exact_lens}
(RUN/'WEIGHTED_OVERLAP_CONTROL.json').write_text(json.dumps(result,indent=2))
print(json.dumps(result))
