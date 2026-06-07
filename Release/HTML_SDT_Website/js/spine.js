// Monoisotopic Line Fit & Row Shifts
const monoPts = [];
const uShiftByV = {};

vVals.forEach(v => {
  const rowIsos = ISO.filter(e => (e.nd + e.nt) === v);
  const sole = rowIsos.find(e => e.isSole && e.stable);
  if (sole) {
    uShiftByV[v] = sole.nd - sole.nt;
    monoPts.push({ v: v, u: sole.nd - sole.nt });
  } else {
    const stables = rowIsos.filter(e => e.stable);
    if (stables.length > 0) {
      let sum = 0; stables.forEach(e => sum += (e.nd - e.nt));
      uShiftByV[v] = sum / stables.length;
    } else {
      let sum = 0; rowIsos.forEach(e => sum += (e.nd - e.nt));
      uShiftByV[v] = sum / rowIsos.length;
    }
  }
});

// Fallback linear fit for missing alpha structures that don't match any v in ISO
function linFit(pts) {
  const n=pts.length; let sx=0,sy=0,sxy=0,sx2=0;
  pts.forEach(p => { sx+=p.v; sy+=p.u; sxy+=p.v*p.u; sx2+=p.v*p.v; });
  const m=(n*sxy-sx*sy)/(n*sx2-sx*sx), b=(sy-m*sx)/n;
  return {m,b};
}
const fallbackFit = linFit(monoPts);

function getUFit(v) {
  if (uShiftByV[v] !== undefined) return uShiftByV[v];
  return fallbackFit.m * v + fallbackFit.b;
}

// ─────────────────────────────────────────────────────────────────
// ENERGY FUNCTIONAL SPINE
const rawMaxSpine      = {};  // { u, be, sym, A }
const energySpineByV   = {};  // { u: u_E, be: smoothed_BE_max, iso: nearest, confidence }
const deltaMonoEnergy  = {};  // u_E(v) - u_mono(v)

(function buildEnergySpine() {
  vVals.forEach(v => {
    // Gather BE data from this row AND ±2 neighbouring rows for support
    const supportRows = [v-2, v-1, v, v+1, v+2];
    const nodes = [];
    supportRows.forEach(sv => {
      ISO.filter(e => (e.nd + e.nt) === sv && e.be > 0).forEach(e => {
        nodes.push({ u: e.nd - e.nt, be: e.be, v: sv, iso: e });
      });
    });
    if (nodes.length === 0) return;

    // Raw max in THIS row only
    const rowNodes = nodes.filter(n => n.v === v);
    if (rowNodes.length > 0) {
      const bestRaw = rowNodes.reduce((a,b) => b.be > a.be ? b : a);
      rawMaxSpine[v] = { u: bestRaw.u, be: bestRaw.be, sym: bestRaw.iso.sym, A: bestRaw.iso.A };
    }

    // Smoothed max — weighted parabolic fit over all support nodes
    const rowWeights = { [v]:1.0, [v-1]:0.4, [v+1]:0.4, [v-2]:0.15, [v+2]:0.15 };
    if (nodes.length < 2) {
      const n = nodes[0];
      energySpineByV[v] = { u: n.u, be: n.be, iso: n.iso, confidence: 'low', source: 'single-node' };
    } else {
      // Weighted least-squares parabola: BE = a*u^2 + b*u + c
      let sw=0, su=0, su2=0, su3=0, su4=0, sbe=0, sube=0, su2be=0;
      nodes.forEach(n => {
        const w = rowWeights[n.v] || 0.1;
        sw   += w;
        su   += w * n.u;
        su2  += w * n.u * n.u;
        su3  += w * n.u * n.u * n.u;
        su4  += w * n.u * n.u * n.u * n.u;
        sbe  += w * n.be;
        sube += w * n.u * n.be;
        su2be+= w * n.u * n.u * n.be;
      });
      const M = [[sw,su,su2],[su,su2,su3],[su2,su3,su4]];
      const rhs = [sbe, sube, su2be];
      function det3(m) {
        return m[0][0]*(m[1][1]*m[2][2]-m[1][2]*m[2][1])
              -m[0][1]*(m[1][0]*m[2][2]-m[1][2]*m[2][0])
              +m[0][2]*(m[1][0]*m[2][1]-m[1][1]*m[2][0]);
      }
      const D = det3(M);
      let u_E, be_E, confidence = 'medium', source = 'row-fit';
      if (Math.abs(D) < 1e-9) {
        const sorted = [...nodes].sort((a,b)=>b.be-a.be);
        const top = sorted.slice(0, Math.max(1, Math.ceil(sorted.length/2)));
        u_E = top.reduce((s,n)=>s+n.u,0)/top.length;
        be_E = top[0].be;
        confidence = 'low'; source = 'neighbour-fit';
      } else {
        const Ma = [[M[0][0],M[0][1],rhs[0]],[M[1][0],M[1][1],rhs[1]],[M[2][0],M[2][1],rhs[2]]];
        const Mb = [[M[0][0],rhs[0],M[0][2]],[M[1][0],rhs[1],M[1][2]],[M[2][0],rhs[2],M[2][2]]];
        const Mc = [[rhs[0],M[0][1],M[0][2]],[rhs[1],M[1][1],M[1][2]],[rhs[2],M[2][1],M[2][2]]];
        const a = det3(Ma)/D, b_c = det3(Mb)/D, c = det3(Mc)/D;
        if (Math.abs(a) < 1e-9 || a > 0) {
          const rw = rowNodes.length > 0 ? rowNodes : nodes;
          const wSum = rw.reduce((s,n)=>s+n.be,0);
          u_E = rw.reduce((s,n)=>s+n.u*n.be,0) / wSum;
          be_E = rw.reduce((s,n)=>s+n.be,0) / rw.length;
          confidence = 'low'; source = 'no-curvature';
        } else {
          u_E = -b_c / (2 * a);
          be_E = a*u_E*u_E + b_c*u_E + c;

          if (rowNodes.length > 0) {
            const uMin_r = Math.min(...rowNodes.map(n=>n.u));
            const uMax_r = Math.max(...rowNodes.map(n=>n.u));
            const span = Math.max(4, uMax_r - uMin_r);
            if (u_E < uMin_r - span || u_E > uMax_r + span) {
              const wSum = rowNodes.reduce((s,n)=>s+n.be,0);
              u_E = rowNodes.reduce((s,n)=>s+n.u*n.be,0) / wSum;
              be_E = rowNodes.reduce((a,n)=>a.be>n.be?a:n).be;
              confidence = 'low'; source = 'clamped';
            } else {
              confidence = rowNodes.length >= 3 ? 'high' : 'medium';
              source = 'row-fit';
            }
          } else {
            confidence = 'medium'; source = 'row-fit';
          }
        }
      }
      const nearestIso = (rowNodes.length>0 ? rowNodes : nodes)
        .reduce((best, n) => Math.abs(n.u - u_E) < Math.abs(best.u - u_E) ? n : best);
      energySpineByV[v] = { u: u_E, be: be_E, iso: nearestIso.iso, confidence, source };
    }

    // Delta: u_E - u_mono
    const u_mono = getUFit(v);
    deltaMonoEnergy[v] = energySpineByV[v] ? energySpineByV[v].u - u_mono : 0;
  });

  // Diagnostic summary
  const spineRows = vVals.filter(v => energySpineByV[v]);
  const rmsSep = Math.sqrt(spineRows.reduce((s,v)=>s+deltaMonoEnergy[v]**2,0)/spineRows.length);
  const stableDelta = ISO.filter(e=>e.stable && energySpineByV[e.nd+e.nt])
    .map(e => (e.nd-e.nt) - energySpineByV[e.nd+e.nt].u);
  const meanStableDelta = stableDelta.reduce((s,d)=>s+d,0)/Math.max(1,stableDelta.length);
  const sortedSD = [...stableDelta].sort((a,b)=>a-b);
  const medianStableDelta = sortedSD[Math.floor(sortedSD.length/2)] || 0;
  window._energySpineDiag = { rmsSep, meanStableDelta, medianStableDelta, nRows: spineRows.length };
  console.log('[Energy Spine] rows fitted:', spineRows.length,
    '| RMS mono-energy sep:', rmsSep.toFixed(3),
    '| stable mean offset from u_E:', meanStableDelta.toFixed(3),
    '| stable median offset:', medianStableDelta.toFixed(3));
})();
