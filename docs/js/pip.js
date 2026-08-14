/* PIP — packing-sequencer thumbnail (same geometry as nuclear-packing-sequencer.html).
   Stick / electronic-shell analog withdrawn. Click opens the sequencer on this isotope. */
(function initPip() {
  const pipEl  = document.getElementById("pip");
  const pipC   = document.getElementById("pipCanvas");
  if (!pipEl || !pipC) return;
  const pipCtx = pipC.getContext("2d");
  const pipLbl = document.getElementById("pipLabel");
  const pack = window.packNucleus;
  const R_p = window.SDT_R_p || 0.8414;
  let pipAngle = 0.6;
  let pipIso   = null;
  let pipTilt  = 0.42;
  const cache = new Map();
  const COL_P = [255, 38, 38];
  const COL_N = [47, 107, 255];

  pipEl.addEventListener("click", () => {
    if (!pipIso) return;
    window.open(`nuclear-packing-sequencer.html#Z=${pipIso.Z}&A=${pipIso.A}`, "_blank");
  });
  window.__pipSetIso = function(iso) {
    pipIso = iso;
    if (pipLbl) pipLbl.textContent = iso
      ? `${iso.sym}-${iso.A} · 1α + ${iso.nd}d + ${iso.nt}t · click→sequencer`
      : "hover an isotope";
  };

  function packed(iso) {
    if (!pack || !iso || iso.nd < 0 || iso.nt < 0) return null;
    const key = iso.Z + "," + iso.A;
    if (!cache.has(key)) cache.set(key, pack(iso.A, iso.Z, 1.45, 0));
    return cache.get(key);
  }

  function vnorm(v){const l=Math.hypot(v[0],v[1],v[2])||1;return[v[0]/l,v[1]/l,v[2]/l];}
  function cross(a,b){return[a[1]*b[2]-a[2]*b[1],a[2]*b[0]-a[0]*b[2],a[0]*b[1]-a[1]*b[0]];}

  function pipProj(v, cx, cy, scl, sinA, cosA) {
    const rx = v[0]*cosA - v[2]*sinA;
    const ry = v[1];
    const rz = v[0]*sinA + v[2]*cosA;
    const sinT=Math.sin(pipTilt), cosT=Math.cos(pipTilt);
    const ry2 = ry*cosT - rz*sinT;
    const rz2 = ry*sinT + rz*cosT;
    const fov=3.5, d=fov/(fov+rz2*0.12);
    return {sx:cx+rx*scl*d, sy:cy-ry2*scl*d, dz:rz2};
  }

  function ringWorld(pos, axis, R, n) {
    const ax = vnorm(axis);
    const up = Math.abs(ax[1]) > 0.9 ? [1,0,0] : [0,1,0];
    const u = vnorm(cross(up, ax));
    const v = cross(ax, u);
    const pts = [];
    for (let i = 0; i <= n; i++) {
      const t = i / n * Math.PI * 2;
      pts.push([
        pos[0] + R * (u[0]*Math.cos(t) + v[0]*Math.sin(t)),
        pos[1] + R * (u[1]*Math.cos(t) + v[1]*Math.sin(t)),
        pos[2] + R * (u[2]*Math.cos(t) + v[2]*Math.sin(t))
      ]);
    }
    return pts;
  }

  function drawPip() {
    requestAnimationFrame(drawPip);
    pipAngle += 0.008;
    const dpr = window.devicePixelRatio || 1;
    const pw = pipEl.clientWidth || 220, ph = pipEl.clientHeight || 150;
    if (pipC.width !== Math.floor(pw*dpr) || pipC.height !== Math.floor(ph*dpr)) {
      pipC.width = Math.floor(pw*dpr); pipC.height = Math.floor(ph*dpr);
    }
    pipCtx.setTransform(dpr,0,0,dpr,0,0);
    pipCtx.fillStyle = "#050508";
    pipCtx.fillRect(0,0,pw,ph);

    const iso = pipIso;
    if (!iso) {
      pipCtx.font = "11px 'Segoe UI',sans-serif";
      pipCtx.fillStyle = "rgba(180,170,150,0.55)";
      pipCtx.textAlign = "center";
      pipCtx.fillText("hover an isotope", pw/2, ph/2-6);
      pipCtx.fillText("click → packing sequencer", pw/2, ph/2+10);
      return;
    }

    const nuc = packed(iso);
    if (!nuc || !nuc.length) {
      pipCtx.font = "11px 'Segoe UI',sans-serif";
      pipCtx.fillStyle = "rgba(180,170,150,0.55)";
      pipCtx.textAlign = "center";
      pipCtx.fillText("pre-α — no packing", pw/2, ph/2);
      return;
    }

    const cx = pw/2, cy = ph/2 - 4;
    let maxR = 0;
    for (const n of nuc) maxR = Math.max(maxR, Math.hypot(n.pos[0], n.pos[1], n.pos[2]));
    const scl = Math.min(pw, ph) * 0.38 / (maxR + R_p * 1.4);
    const sinA = Math.sin(pipAngle), cosA = Math.cos(pipAngle);

    const spread = Math.min(pw, ph) * 0.34;
    const shg = pipCtx.createRadialGradient(cx+spread*0.45, cy+spread*0.7, spread*0.08, cx+spread*0.45, cy+spread*0.7, spread*0.95);
    shg.addColorStop(0, "rgba(0,0,0,0.45)"); shg.addColorStop(1, "transparent");
    pipCtx.save(); pipCtx.translate(cx+spread*0.45, cy+spread*0.7); pipCtx.scale(1, 0.38); pipCtx.translate(-(cx+spread*0.45), -(cy+spread*0.7));
    pipCtx.beginPath(); pipCtx.arc(cx+spread*0.45, cy+spread*0.7, spread*0.95, 0, Math.PI*2);
    pipCtx.fillStyle = shg; pipCtx.fill(); pipCtx.restore();

    if (nuc.alphaTetra) {
      const V = nuc.alphaTetra;
      const E = [[0,1],[0,2],[0,3],[1,2],[1,3],[2,3]];
      pipCtx.strokeStyle = "rgba(212,160,92,0.45)";
      pipCtx.lineWidth = 1;
      for (const [i,j] of E) {
        const a = pipProj(V[i], cx, cy, scl, sinA, cosA);
        const b = pipProj(V[j], cx, cy, scl, sinA, cosA);
        pipCtx.beginPath(); pipCtx.moveTo(a.sx, a.sy); pipCtx.lineTo(b.sx, b.sy); pipCtx.stroke();
      }
    }

    if (nuc.contacts) {
      pipCtx.strokeStyle = "rgba(68,238,187,0.28)";
      pipCtx.lineWidth = 0.8;
      for (const [i,j] of nuc.contacts) {
        const a = pipProj(nuc[i].pos, cx, cy, scl, sinA, cosA);
        const b = pipProj(nuc[j].pos, cx, cy, scl, sinA, cosA);
        pipCtx.beginPath(); pipCtx.moveTo(a.sx, a.sy); pipCtx.lineTo(b.sx, b.sy); pipCtx.stroke();
      }
    }

    const drawn = nuc.map(n => {
      const pr = pipProj(n.pos, cx, cy, scl, sinA, cosA);
      return {n, ...pr};
    }).sort((a,b) => a.dz - b.dz);

    for (const o of drawn) {
      const col = o.n.type === "p" ? COL_P : COL_N;
      const pts = ringWorld(o.n.pos, o.n.axis, R_p, 18).map(p => pipProj(p, cx, cy, scl, sinA, cosA));
      pipCtx.beginPath();
      pts.forEach((p,i) => i ? pipCtx.lineTo(p.sx, p.sy) : pipCtx.moveTo(p.sx, p.sy));
      pipCtx.closePath();
      pipCtx.strokeStyle = `rgba(${col[0]},${col[1]},${col[2]},0.92)`;
      pipCtx.lineWidth = o.n.group === "alpha" ? 1.8 : 1.15;
      pipCtx.stroke();
      pipCtx.fillStyle = `rgba(${col[0]},${col[1]},${col[2]},0.12)`;
      pipCtx.fill();
    }

    pipCtx.font = "10px 'Segoe UI',sans-serif";
    pipCtx.fillStyle = "rgba(226,208,180,0.45)";
    pipCtx.textAlign = "left";
    pipCtx.fillText("p red · n blue", 6, 12);
  }

  drawPip();
})();
