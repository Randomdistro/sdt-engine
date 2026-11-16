from pathlib import Path
import json,itertools,math
import numpy as np
RUN=Path(__file__).resolve().parent
baseline=json.loads((RUN/'BASELINE.json').read_text())
centres=np.array([n['pos'] for n in baseline['nodes']])/0.8414
rows=[]
for b in [1.,1.1,1.5]:
    bound=math.sqrt(2)+b
    for N in [32,64,128]:
        step=2*bound/N;axis=-bound+(np.arange(N)+.5)*step
        weighted_sum=weighted_union=geom_union=pair_sum=triple_sum=quad_sum=0.
        multiplicities=np.zeros(5,dtype=np.int64)
        yy,zz=np.meshgrid(axis,axis,indexing='ij')
        for x in axis:
            p=np.stack([np.full_like(yy,x),yy,zz],axis=-1)
            radii=np.linalg.norm(p[None]-centres[:,None,None,:],axis=-1)
            inside=radii<b;counts=inside.sum(axis=0)
            weights=np.where(inside,np.sqrt(radii/b),0)
            weighted_sum+=weights.sum();weighted_union+=weights.max(axis=0).sum()
            geom_union+=np.count_nonzero(counts)
            for k in range(5):multiplicities[k]+=np.count_nonzero(counts==k)
            pair_sum+=np.sum(counts*(counts-1)/2)
            triple_sum+=np.sum(counts*(counts-1)*(counts-2)/6)
            quad_sum+=np.sum(counts==4)
        dv=step**3;single=4*math.pi*b**3/3;eng_single=8*math.pi*b**3/7
        exact_pairs=0
        for i,j in itertools.combinations(range(4),2):
            d=np.linalg.norm(centres[i]-centres[j])
            if d<2*b:exact_pairs+=math.pi*(4*b+d)*(2*b-d)**2/12
        direct=geom_union*dv
        inclusion_exclusion=sum(k*multiplicities[k] for k in range(5))*dv-pair_sum*dv+triple_sum*dv-quad_sum*dv
        pair_only=4*single-exact_pairs
        rows.append({'b_over_Rp':b,'N':N,'units':'Rp^3','geometricUnion':direct,'geometricPairOnlyAnalytic':pair_only,'tripleOverlapSum':triple_sum*dv,'fourBodyOverlap':quad_sum*dv,'inclusionExclusionResidual':abs(direct-inclusion_exclusion),'coherentSaturatedWeightedUnion':weighted_union*dv,'numericalSumWeightedParts':weighted_sum*dv,'analyticSumWeightedParts':4*eng_single,'weightedSaving':4*eng_single-weighted_union*dv,'multiplicityCounts':multiplicities.tolist(),'physicalAlphaEnergyStatus':'OPEN: supplied spherical domains, phase response and energy map absent'})
for b in [1.,1.1,1.5]:
    group=[r for r in rows if r['b_over_Rp']==b]
    for prev,r in zip(group,group[1:]):r['unionRelativeChange']=abs(r['coherentSaturatedWeightedUnion']-prev['coherentSaturatedWeightedUnion'])/r['coherentSaturatedWeightedUnion']
(RUN/'JOINT_RESPONSE.json').write_text(json.dumps({'model':'conditional coherent saturated max-weight union from FLM15 R4; not a derived alpha boundary','rows':rows,'exactBoundaryAtRp':'four spheres touch on zero-measure sets; joint engagement equals sum of parts; synchrony saving exactly zero'},indent=2))
print(json.dumps([{'b':r['b_over_Rp'],'relativeChange':r.get('unionRelativeChange'),'triple':r['tripleOverlapSum'],'four':r['fourBodyOverlap']} for r in rows if r['N']==128]))
