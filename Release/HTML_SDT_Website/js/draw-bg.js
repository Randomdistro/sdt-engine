function drawBackground(ctx) {
  const pad = 80;

  // ────────────────────────────────────────────────────────────────────────────
  // 1. Golden Boundary Line (nd = nt) — BACKGROUND VERSION (faint)
  // ────────────────────────────────────────────────────────────────────────────
  if (cbGoldenLine.checked) {
    const goldenPts = [];
    for (let v = vMin % 2 === 0 ? vMin : vMin + 1; v <= vMax; v += 2) {
      const half = v / 2;
      if (half < 0) continue;
      const p = gridPos(half, half);
      if (p.x > -200 && p.x < W + 200) goldenPts.push(p);
    }
    if (goldenPts.length > 1) {
      ctx.save();
      ctx.shadowColor = "rgba(255,220,40,0.5)";
      ctx.shadowBlur = 10;
      ctx.strokeStyle = "rgba(255,215,0,0.12)";
      ctx.lineWidth = 7;
      ctx.lineJoin = "round";
      ctx.beginPath();
      goldenPts.forEach((p,i) => i===0 ? ctx.moveTo(p.x,p.y) : ctx.lineTo(p.x,p.y));
      ctx.stroke();
      ctx.restore();
      ctx.strokeStyle = "rgba(255,210,30,0.40)";
      ctx.lineWidth = 1.5;
      ctx.lineJoin = "round";
      ctx.setLineDash([]);
      ctx.beginPath();
      goldenPts.forEach((p,i) => i===0 ? ctx.moveTo(p.x,p.y) : ctx.lineTo(p.x,p.y));
      ctx.stroke();
      const topPt = goldenPts[0];
      ctx.save();
      ctx.font = "600 10px 'Segoe UI',sans-serif";
      ctx.fillStyle = "rgba(255,215,0,0.35)";
      ctx.textAlign = "left";
      ctx.fillText("n\u2099 = n\u209c  (50/50)", topPt.x + 5, topPt.y + 14);
      ctx.restore();
    }
  }

  // ── 2. GS chains + spine coverage stats ──────────────────────────────────
  {
    const hiByV = new Map(), loByV = new Map();
    ISO.forEach(iso => {
      if (iso.abd <= 0 || iso.be <= 0) return;
      const v   = iso.nd + iso.nt;
      const tbe = iso.be * iso.A;
      if (!hiByV.has(v) || tbe > hiByV.get(v).tbe) hiByV.set(v, { iso, tbe });
      if (!loByV.has(v) || tbe < loByV.get(v).tbe) loByV.set(v, { iso, tbe });
    });

    // Spine coverage statistics
    let spNatural = 0, spStable = 0, spUnstable = 0;
    Object.values(energySpineByV).forEach(sp => {
      if (!sp.iso) { spUnstable++; return; }
      if (sp.iso.abd > 0)         spNatural++;
      else if (sp.iso.stable)     spStable++;
      else                        spUnstable++;
    });
    const spTotal = spNatural + spStable + spUnstable;
    window._spineCoverage = { spNatural, spStable, spUnstable, spTotal,
      pctNatural:  spTotal ? (spNatural  / spTotal * 100).toFixed(1) : '?',
      pctStable:   spTotal ? (spStable   / spTotal * 100).toFixed(1) : '?',
      pctUnstable: spTotal ? (spUnstable / spTotal * 100).toFixed(1) : '?',
    };

    // ─ Highest GS chain (amber)
    if (cbHighestGS && cbHighestGS.checked) {
      const pts = [];
      hiByV.forEach(({ iso }) => {
        const p = isoPos(iso);
        if (p.x > -100 && p.x < W + 100 && p.y > -50 && p.y < H + 50)
          pts.push({ x: p.x, y: p.y });
      });
      pts.sort((a, b) => a.y - b.y);
      if (pts.length > 1) {
        ctx.save();
        ctx.strokeStyle = 'rgba(220,170,40,0.65)';
        ctx.lineWidth   = 1.3;
        ctx.lineJoin    = 'round'; ctx.lineCap = 'round';
        ctx.setLineDash([]);
        ctx.beginPath();
        pts.forEach((p, i) => i === 0 ? ctx.moveTo(p.x, p.y) : ctx.lineTo(p.x, p.y));
        ctx.stroke();
        ctx.restore();
      }
    }

    // ─ Lowest GS chain (violet)
    if (cbLowestGS && cbLowestGS.checked) {
      const pts = [];
      loByV.forEach(({ iso }) => {
        const p = isoPos(iso);
        if (p.x > -100 && p.x < W + 100 && p.y > -50 && p.y < H + 50)
          pts.push({ x: p.x, y: p.y });
      });
      pts.sort((a, b) => a.y - b.y);
      if (pts.length > 1) {
        ctx.save();
        ctx.strokeStyle = 'rgba(180,100,255,0.65)';
        ctx.lineWidth   = 1.3;
        ctx.lineJoin    = 'round'; ctx.lineCap = 'round';
        ctx.setLineDash([]);
        ctx.beginPath();
        pts.forEach((p, i) => i === 0 ? ctx.moveTo(p.x, p.y) : ctx.lineTo(p.x, p.y));
        ctx.stroke();
        ctx.restore();
      }
    }
  }

  // ── 3. Energy Functional Spine (background) ──────────────────────────────
  if (cbEnergySpine.checked) {
    const ePts = [];
    vVals.forEach(v => {
      const sp = energySpineByV[v]; if (!sp) return;
      const nd_synth = (v + sp.u) / 2, nt_synth = (v - sp.u) / 2;
      if (nt_synth >= 0) {
        const p = gridPos(nd_synth, nt_synth);
        if (p.x > -100 && p.x < W + 100) ePts.push({ x: p.x, y: p.y });
      }
    });
    if (ePts.length > 1) {
      ctx.save();
      ctx.strokeStyle = 'rgba(40,180,180,0.32)';
      ctx.lineWidth   = 1.2;
      ctx.lineJoin    = 'round';
      ctx.lineCap     = 'round';
      ctx.setLineDash([6, 5]);
      ctx.shadowBlur  = 0;
      ctx.beginPath();
      ePts.forEach((p, i) => i === 0 ? ctx.moveTo(p.x, p.y) : ctx.lineTo(p.x, p.y));
      ctx.stroke();
      ctx.restore();
    }
  }

  // ── 4. Mono spine overlay (orange, background) ────────────────────────────
  if (cbMonoSpineOv && cbMonoSpineOv.checked) {
    const mPts = [];
    monoPts.forEach(pt => {
      const nd_m = (pt.v + pt.u) / 2, nt_m = (pt.v - pt.u) / 2;
      if (nt_m < 0) return;
      const p = gridPos(nd_m, nt_m);
      if (p.x > -100 && p.x < W+100) mPts.push({ x:p.x, y:p.y });
    });
    if (mPts.length > 1) {
      ctx.save();
      ctx.shadowColor = 'rgba(255,160,40,0.25)'; ctx.shadowBlur = 5;
      ctx.strokeStyle = 'rgba(255,160,40,0.10)'; ctx.lineWidth = 5;
      ctx.lineJoin = 'round';
      ctx.beginPath();
      mPts.forEach((p,i) => i===0 ? ctx.moveTo(p.x,p.y) : ctx.lineTo(p.x,p.y));
      ctx.stroke();
      ctx.restore();
      ctx.strokeStyle = 'rgba(255,170,60,0.35)'; ctx.lineWidth = 1.2;
      ctx.setLineDash([5,4]);
      ctx.beginPath();
      mPts.forEach((p,i) => i===0 ? ctx.moveTo(p.x,p.y) : ctx.lineTo(p.x,p.y));
      ctx.stroke();
      ctx.setLineDash([]);
      if (mPts.length > 0) {
        ctx.font = "600 9px 'Segoe UI',sans-serif"; ctx.textAlign = 'left';
        ctx.fillStyle = 'rgba(255,170,60,0.30)';
        ctx.fillText('u_mono (monoisotope)', mPts[0].x + 6, mPts[0].y - 4);
      }
    }
  }

  // ── 5. Sole element chain ─────────────────────────────────────────────────
  if (cbSC && cbSC.checked && SOLE_Z.length > 1) {
    const solePoints = [];
    for (let i = 0; i < SOLE_Z.length; i++) {
      const iso = ISO.find(e => e.Z === SOLE_Z[i] && e.stable);
      if (iso) solePoints.push(isoPos(iso));
    }
    if (solePoints.length > 1) {
      ctx.strokeStyle = "rgba(255,230,70,0.20)";
      ctx.lineWidth = 1.0;
      ctx.setLineDash([4,3]);
      ctx.beginPath();
      solePoints.forEach((p, i) => i === 0 ? ctx.moveTo(p.x, p.y) : ctx.lineTo(p.x, p.y));
      ctx.stroke();
      ctx.setLineDash([]);
    }
  }

  // ── 6. Hex lattice grid lines ─────────────────────────────────────────────
  {
    const lineCol = 'rgba(160,130,90,0.10)';
    ctx.strokeStyle = lineCol;
    ctx.lineWidth = 0.7;
    ctx.setLineDash([]);

    // a) Horizontal: for each v level
    const byV = new Map();
    ISO.forEach(iso => {
      const v = iso.nd + iso.nt;
      if (!byV.has(v)) byV.set(v, []);
      byV.get(v).push(iso);
    });
    byV.forEach(isos => {
      const pts = isos.map(iso => isoPos(iso)).sort((a,b) => a.x - b.x);
      if (pts.length < 2) return;
      ctx.beginPath();
      ctx.moveTo(pts[0].x, pts[0].y);
      pts.forEach((p,i) => { if (i > 0) ctx.lineTo(p.x, p.y); });
      ctx.stroke();
    });

    // b) Diagonal-right: constant nt
    const byNt = new Map();
    ISO.forEach(iso => {
      if (!byNt.has(iso.nt)) byNt.set(iso.nt, []);
      byNt.get(iso.nt).push(iso);
    });
    byNt.forEach(isos => {
      const pts = isos.sort((a,b) => a.nd - b.nd).map(iso => isoPos(iso));
      if (pts.length < 2) return;
      ctx.beginPath();
      ctx.moveTo(pts[0].x, pts[0].y);
      pts.forEach((p,i) => { if (i > 0) ctx.lineTo(p.x, p.y); });
      ctx.stroke();
    });

    // c) Diagonal-left: constant nd
    const byNd = new Map();
    ISO.forEach(iso => {
      if (!byNd.has(iso.nd)) byNd.set(iso.nd, []);
      byNd.get(iso.nd).push(iso);
    });
    byNd.forEach(isos => {
      const pts = isos.sort((a,b) => a.nt - b.nt).map(iso => isoPos(iso));
      if (pts.length < 2) return;
      ctx.beginPath();
      ctx.moveTo(pts[0].x, pts[0].y);
      pts.forEach((p,i) => { if (i > 0) ctx.lineTo(p.x, p.y); });
      ctx.stroke();
    });
  }

  // Axis labels
  ctx.fillStyle = "#666";
  ctx.textAlign = "center";
  ctx.font = "400 10px 'Segoe UI',sans-serif";
  ctx.fillText("deuteron excess  (n_d − n_t)  →", W/2, H - 15);
  ctx.save();
  ctx.translate(15, H/2);
  ctx.rotate(-Math.PI/2);
  ctx.fillText("total subunits  (n_d + n_t)  →", 0, 0);
  ctx.restore();

  // ── 7. Shell bands ────────────────────────────────────────────────────────
  if (cbShells.checked) {
    SHELL_BANDS.forEach(sh => {
      const shIsos = ISO.filter(e => e.Z >= sh.zMin && e.Z <= sh.zMax);
      if (shIsos.length === 0) return;
      const vValsInShell = shIsos.map(e => e.nd + e.nt);
      const vBotRaw = Math.min(...vValsInShell);
      const vTopRaw = Math.max(...vValsInShell);

      const vRange = (vMax - vMin) || 1;
      const shPad = 80;
      const scale = (H - shPad*2) / vRange;
      const byBot = shPad + (vBotRaw - vMin) * scale;
      const byTop = shPad + (vTopRaw - vMin) * scale;
      const yBot = H/2 + (byBot - H/2 + panY) * zoom;
      const yTop = H/2 + (byTop - H/2 + panY) * zoom;
      const halfStep = scale * zoom / 2;

      ctx.fillStyle = sh.fill;
      ctx.fillRect(0, yBot - halfStep, W, yTop - yBot + scale * zoom);

      ctx.font = "700 11px 'Segoe UI',sans-serif";
      ctx.fillStyle = sh.stroke;
      ctx.textAlign = "right";
      const yMid = (yBot + yTop) / 2;
      ctx.fillText(`Shell ${sh.name}`, W - 6, yMid + 4);

      ctx.strokeStyle = sh.stroke.replace(/[\.\d]+\)$/, "0.25)");
      ctx.lineWidth = 0.8;
      ctx.setLineDash([4, 6]);
      ctx.beginPath();
      ctx.moveTo(0, yBot - halfStep); ctx.lineTo(W, yBot - halfStep);
      ctx.moveTo(0, yTop + halfStep); ctx.lineTo(W, yTop + halfStep);
      ctx.stroke();
      ctx.setLineDash([]);
    });
  }

  // ── 8. Golden Boundary Line — FOREGROUND VERSION (bright) ────────────────
  if (cbGoldenLine.checked) {
    const goldenPts = [];
    for (let v = vMin % 2 === 0 ? vMin : vMin + 1; v <= vMax; v += 2) {
      const half = v / 2;
      if (half < 0) continue;
      const p = gridPos(half, half);
      if (p.x > -200 && p.x < W + 200) goldenPts.push(p);
    }
    if (goldenPts.length > 1) {
      ctx.save();
      ctx.shadowColor = "rgba(255,220,40,0.7)";
      ctx.shadowBlur = 14;
      ctx.strokeStyle = "rgba(255,215,0,0.20)";
      ctx.lineWidth = 7;
      ctx.lineJoin = "round";
      ctx.beginPath();
      goldenPts.forEach((p,i) => i===0 ? ctx.moveTo(p.x,p.y) : ctx.lineTo(p.x,p.y));
      ctx.stroke();
      ctx.restore();
      ctx.strokeStyle = "rgba(255,210,30,0.80)";
      ctx.lineWidth = 1.5;
      ctx.lineJoin = "round";
      ctx.setLineDash([]);
      ctx.beginPath();
      goldenPts.forEach((p,i) => i===0 ? ctx.moveTo(p.x,p.y) : ctx.lineTo(p.x,p.y));
      ctx.stroke();
      const topPt = goldenPts[0];
      ctx.save();
      ctx.font = "600 10px 'Segoe UI',sans-serif";
      ctx.fillStyle = "rgba(255,215,0,0.60)";
      ctx.textAlign = "left";
      ctx.fillText("n\u2099 = n\u209c  (50/50)", topPt.x + 5, topPt.y + 14);
      ctx.restore();
    }
  }

  // ── Energy Functional Spine overlay (foreground) ──────────────────────────
  if (cbEnergySpine.checked) {
    const ePts = [];
    vVals.forEach(v => {
      const sp = energySpineByV[v]; if (!sp) return;
      const nd_synth = (v + sp.u) / 2, nt_synth = (v - sp.u) / 2;
      if (nt_synth >= 0) {
        const p = gridPos(nd_synth, nt_synth);
        if (p.x > -100 && p.x < W + 100) {
          ePts.push({ x: p.x, y: p.y, v, sp });
        }
      }
    });
    if (ePts.length > 1) {
      ctx.save();
      ctx.strokeStyle = 'rgba(40,180,180,0.42)';
      ctx.lineWidth   = 1.2;
      ctx.lineJoin    = 'round';
      ctx.lineCap     = 'round';
      ctx.setLineDash([6, 5]);
      ctx.shadowBlur  = 0;
      ctx.beginPath();
      ePts.forEach((p, i) => i === 0 ? ctx.moveTo(p.x, p.y) : ctx.lineTo(p.x, p.y));
      ctx.stroke();
      ctx.restore();
    }
  }

  // ── Mono spine overlay (foreground) ──────────────────────────────────────
  if (cbMonoSpineOv && cbMonoSpineOv.checked) {
    const mPts = [];
    monoPts.forEach(pt => {
      const nd_m = (pt.v + pt.u) / 2, nt_m = (pt.v - pt.u) / 2;
      if (nt_m < 0) return;
      const p = gridPos(nd_m, nt_m);
      if (p.x > -100 && p.x < W+100) mPts.push({ x:p.x, y:p.y });
    });
    if (mPts.length > 1) {
      ctx.save();
      ctx.shadowColor = 'rgba(255,160,40,0.60)'; ctx.shadowBlur = 8;
      ctx.strokeStyle = 'rgba(255,160,40,0.22)'; ctx.lineWidth = 5;
      ctx.lineJoin = 'round';
      ctx.beginPath();
      mPts.forEach((p,i) => i===0 ? ctx.moveTo(p.x,p.y) : ctx.lineTo(p.x,p.y));
      ctx.stroke();
      ctx.restore();
      ctx.strokeStyle = 'rgba(255,170,60,0.75)'; ctx.lineWidth = 1.2;
      ctx.setLineDash([5,4]);
      ctx.beginPath();
      mPts.forEach((p,i) => i===0 ? ctx.moveTo(p.x,p.y) : ctx.lineTo(p.x,p.y));
      ctx.stroke();
      ctx.setLineDash([]);
      if (mPts.length > 0) {
        ctx.font = "600 9px 'Segoe UI',sans-serif"; ctx.textAlign = 'left';
        ctx.fillStyle = 'rgba(255,170,60,0.60)';
        ctx.fillText('u_mono (monoisotope)', mPts[0].x + 6, mPts[0].y - 4);
      }
    }
  }
}
