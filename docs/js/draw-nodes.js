function drawNodes(ctx) {
  const pad = 80;
  const showFam  = cbFam.checked;
  const showConn = cbConn.checked;
  const showMag  = cbMag.checked;

  // ── Background position circles for all known unstable isotopes ──────────
  if (cbUnstPos.checked) {
    const baseR = Math.max(2.5, gridScale * zoom / 2 - 1);
    UNSTABLE_GRID.forEach(([Z, A, nd, nt]) => {
      const p = gridPos(nd, nt);
      if (p.x < 130 || p.x > W - 20 || p.y < 20 || p.y > H - 20) return;
      const evenA = (A % 2 === 0);
      ctx.beginPath();
      ctx.arc(p.x, p.y, baseR, 0, Math.PI*2);
      ctx.strokeStyle = evenA
        ? "rgba(100,165,230,0.22)"
        : "rgba(220,155,70,0.22)";
      ctx.lineWidth = 0.9;
      ctx.stroke();
    });
  }

  // Triton family connections
  if (showFam) {
    const byNt = {};
    ISO.forEach(iso => { if (!byNt[iso.nt]) byNt[iso.nt] = []; byNt[iso.nt].push(iso); });
    Object.entries(byNt).forEach(([nt, family]) => {
      if (family.length < 2) return;
      family.sort((a,b) => a.nd - b.nd);
      ctx.strokeStyle = `rgba(200,180,140,0.06)`;
      ctx.lineWidth = 0.5;
      ctx.beginPath();
      family.forEach((iso,i) => { const p = isoPos(iso); i===0 ? ctx.moveTo(p.x,p.y) : ctx.lineTo(p.x,p.y); });
      ctx.stroke();
    });
  }

  // Z-chain connections
  if (showConn) {
    const sorted = [...ISO].sort((a,b) => a.Z - b.Z || a.A - b.A);
    ctx.lineWidth = 0.4;
    for (let i = 1; i < sorted.length; i++) {
      if (sorted[i].Z !== sorted[i-1].Z) continue;
      const a = isoPos(sorted[i-1]), b = isoPos(sorted[i]);
      ctx.strokeStyle = "rgba(255,255,255,0.07)";
      ctx.beginPath(); ctx.moveTo(a.x,a.y); ctx.lineTo(b.x,b.y); ctx.stroke();
    }
  }

  // Magnetic overlay
  if (showMag) {
    const FERRO_Z    = new Set([26,27,28]);
    const STRONGPARA_Z = new Set([24,25,23,57,58,59,60,62,64,65,66,67,68,69,70]);
    const PARA_Z     = new Set([3,8,11,13,15,16,19,20,21,22,23,29,37,38,39,40,41,42,43,44,45,46,47,48,55,56,74,75,76,77,78,79,90,92]);
    const DIA_Z      = new Set([1,2,4,6,7,9,10,12,14,17,18,30,32,33,34,35,36,50,51,52,53,54,80,82,83]);

    const magTypes = [
      { label:"Ferromagnetic",   zSet:FERRO_Z,     glow:"rgba(255,60,80,",  ring:"rgba(255,100,120,", haloR:55 },
      { label:"Strong para.",    zSet:STRONGPARA_Z,glow:"rgba(255,160,40,",  ring:"rgba(255,190,80,",  haloR:38 },
      { label:"Paramagnetic",    zSet:PARA_Z,      glow:"rgba(120,200,255,", ring:"rgba(150,220,255,", haloR:28 },
      { label:"Diamagnetic",     zSet:DIA_Z,       glow:"rgba(160,180,220,", ring:"rgba(190,210,240,", haloR:22 },
    ];

    ISO.forEach(iso => {
      let mt = null;
      if (FERRO_Z.has(iso.Z)) mt = magTypes[0];
      else if (STRONGPARA_Z.has(iso.Z)) mt = magTypes[1];
      else if (PARA_Z.has(iso.Z)) mt = magTypes[2];
      else if (DIA_Z.has(iso.Z)) mt = magTypes[3];
      if (!mt) return;
      const p = isoPos(iso);
      const hR = mt.haloR * zoom;
      const grad = ctx.createRadialGradient(p.x, p.y, 0, p.x, p.y, hR);
      grad.addColorStop(0,   mt.glow + "0.22)");
      grad.addColorStop(0.4, mt.glow + "0.10)");
      grad.addColorStop(1,   mt.glow + "0.00)");
      ctx.beginPath();
      ctx.arc(p.x, p.y, hR, 0, Math.PI*2);
      ctx.fillStyle = grad;
      ctx.fill();
    });

    const ferroIsos = ISO.filter(e => FERRO_Z.has(e.Z));
    if (ferroIsos.length > 0) {
      let cx = 0, cy = 0;
      ferroIsos.forEach(e => { const p = isoPos(e); cx += p.x; cy += p.y; });
      cx /= ferroIsos.length; cy /= ferroIsos.length;

      ctx.save();
      for (let ring = 1; ring <= 8; ring++) {
        const rr = (20 + ring * 22) * zoom;
        const alpha = Math.max(0, 0.14 - ring * 0.015);
        const grad2 = ctx.createRadialGradient(cx, cy, rr * 0.7, cx, cy, rr);
        grad2.addColorStop(0, `rgba(255,60,80,${alpha})`);
        grad2.addColorStop(1, `rgba(255,60,80,0)`);
        ctx.beginPath();
        ctx.arc(cx, cy, rr, 0, Math.PI*2);
        ctx.fillStyle = grad2;
        ctx.fill();
      }
      const fieldLineCount = 12;
      for (let i = 0; i < fieldLineCount; i++) {
        const angle = (i / fieldLineCount) * Math.PI * 2;
        const r1 = 14 * zoom;
        const r2 = 140 * zoom;
        ctx.beginPath();
        ctx.moveTo(cx + Math.cos(angle) * r1, cy + Math.sin(angle) * r1);
        ctx.lineTo(cx + Math.cos(angle) * r2, cy + Math.sin(angle) * r2);
        ctx.strokeStyle = `rgba(255,80,100,0.12)`;
        ctx.lineWidth = 1.2 * zoom;
        ctx.stroke();
      }
      const hotGrad = ctx.createRadialGradient(cx, cy, 0, cx, cy, 30 * zoom);
      hotGrad.addColorStop(0,   "rgba(255,200,210,0.30)");
      hotGrad.addColorStop(0.5, "rgba(255,80,100,0.12)");
      hotGrad.addColorStop(1,   "rgba(255,60,80,0)");
      ctx.beginPath();
      ctx.arc(cx, cy, 30 * zoom, 0, Math.PI*2);
      ctx.fillStyle = hotGrad;
      ctx.fill();
      ctx.restore();

      ctx.font = "700 11px 'Segoe UI',sans-serif";
      ctx.fillStyle = "rgba(255,100,120,0.75)";
      ctx.textAlign = "center";
      ctx.fillText("Fe · Co · Ni", cx, cy + 145 * zoom);
      ctx.font = "500 9px 'Segoe UI',sans-serif";
      ctx.fillStyle = "rgba(255,100,120,0.45)";
      ctx.fillText("ferromagnetic zone", cx, cy + 158 * zoom);
    }

    const lx = 140, ly = H - 110;
    ctx.font = "700 10px 'Segoe UI',sans-serif";
    ctx.fillStyle = "rgba(200,190,180,0.7)";
    ctx.textAlign = "left";
    ctx.fillText("Magnetic character", lx, ly - 4);
    magTypes.forEach((mt, i) => {
      const gy = ly + 14 + i * 16;
      const grad3 = ctx.createRadialGradient(lx + 6, gy, 0, lx + 6, gy, 10);
      grad3.addColorStop(0, mt.glow + "0.7)");
      grad3.addColorStop(1, mt.glow + "0)");
      ctx.beginPath(); ctx.arc(lx + 6, gy, 6, 0, Math.PI*2);
      ctx.fillStyle = grad3; ctx.fill();
      ctx.beginPath(); ctx.arc(lx + 6, gy, 4, 0, Math.PI*2);
      ctx.fillStyle = mt.glow + "0.4)"; ctx.fill();
      ctx.font = "500 9px 'Segoe UI',sans-serif";
      ctx.fillStyle = mt.ring + "0.85)";
      ctx.fillText(mt.label, lx + 16, gy + 3);
    });
  }

  // Shell closure background bands only
  if (cbShells.checked) {
    MAGIC_Z.forEach(mz => {
      const magIsos = ISO.filter(e => e.Z === mz);
      if (!magIsos.length) return;
      const positions = magIsos.map(e => isoPos(e));
      const minY = Math.min(...positions.map(p => p.y));
      const maxY = Math.max(...positions.map(p => p.y));
      ctx.fillStyle = 'rgba(80,200,80,0.03)';
      ctx.fillRect(0, minY - 6, W, maxY - minY + 12);
    });
  }

  // Sole vs Spread legend
  if (cbSS.checked) {
    ctx.font = "500 10px 'Segoe UI',sans-serif";
    ctx.textAlign = "left";
    ctx.fillStyle = "rgba(230,180,70,0.6)";
    ctx.fillText("● sole (1 stable isotope)", pad + 5, H - pad + 15);
    ctx.fillStyle = "rgba(90,120,150,0.6)";
    ctx.fillText("● spread (2+ stable isotopes)", pad + 175, H - pad + 15);
    ctx.fillStyle = "rgba(120,80,70,0.5)";
    ctx.fillText("○ unstable", pad + 375, H - pad + 15);
  }

  // Unpaired electrons legend
  if (cbUnp.checked) {
    ctx.font = "500 10px 'Segoe UI',sans-serif";
    ctx.textAlign = "left";
    for (let u = 0; u <= 7; u++) {
      const t = u / 7;
      const cr = Math.round(80 + t * 160);
      const cg = Math.round(130 - t * 60);
      const cb2 = Math.round(170 - t * 130);
      ctx.fillStyle = `rgba(${cr},${cg},${cb2},0.7)`;
      ctx.beginPath(); ctx.arc(pad + 5 + u * 30, H - pad + 18, 4, 0, Math.PI*2); ctx.fill();
      ctx.fillStyle = "#888";
      ctx.fillText(u.toString(), pad + 12 + u * 30, H - pad + 22);
    }
    ctx.fillStyle = "#888";
    ctx.fillText("← unpaired electrons", pad + 5 + 8 * 30, H - pad + 22);
  }

  // Odd/Even legend
  if (cbOddEven.checked) {
    ctx.font = "500 10px 'Segoe UI',sans-serif";
    ctx.textAlign = "left";
    ctx.fillStyle = "rgba(200,140,80,0.6)";
    ctx.fillText("● odd-A (half-integer spin)", pad + 5, H - pad + 15);
    ctx.fillStyle = "rgba(80,130,170,0.6)";
    ctx.fillText("● even-A (integer spin)", pad + 220, H - pad + 15);
  }

  // ── CHANGE 4: Pre-compute active group state ──────────────────────────────
  // Build a Set of group keys and find connected components for scaling
  const groupSet = new Set();
  activeGroup.forEach(iso => groupSet.add(`${iso.nd},${iso.nt}`));

  // Flat-top hex neighbours in (nd,nt) space
  const HEX_NEIGHBOURS = [[1,0],[-1,0],[0,1],[0,-1],[1,-1],[-1,1]];

  function hexNeighbours(nd, nt) {
    return HEX_NEIGHBOURS.map(([dnd,dnt]) => ({nd: nd+dnd, nt: nt+dnt}));
  }

  // Find connected components among activeGroup members
  function findComponents(group) {
    const visited = new Set();
    const components = [];
    group.forEach(iso => {
      const key = `${iso.nd},${iso.nt}`;
      if (visited.has(key)) return;
      // BFS
      const comp = [];
      const queue = [iso];
      visited.add(key);
      while (queue.length) {
        const cur = queue.shift();
        comp.push(cur);
        hexNeighbours(cur.nd, cur.nt).forEach(nb => {
          const nkey = `${nb.nd},${nb.nt}`;
          if (!visited.has(nkey) && groupSet.has(nkey)) {
            visited.add(nkey);
            const nbIso = group.find(g => g.nd === nb.nd && g.nt === nb.nt);
            if (nbIso) queue.push(nbIso);
          }
        });
      }
      components.push(comp);
    });
    return components;
  }

  // Map each iso key → its component's screen centroid
  const groupCentroidMap = new Map();
  if (activeGroup.length > 0) {
    const components = findComponents(activeGroup);
    components.forEach(comp => {
      let cx = 0, cy = 0;
      comp.forEach(iso => { const p = isoPos(iso); cx += p.x; cy += p.y; });
      cx /= comp.length; cy /= comp.length;
      comp.forEach(iso => {
        groupCentroidMap.set(`${iso.nd},${iso.nt}`, { cx, cy, compSize: comp.length });
      });
    });
  }

  // ── Draw isotope nodes — flat-top hexagons ──────────────────────────────
  ISO.forEach(iso => {
    const rawP = isoPos(iso);
    const isElemHov = hoveredZ !== null && iso.Z === hoveredZ;
    const isHov = hoveredIso && hoveredIso.Z === iso.Z && hoveredIso.A === iso.A;
    const isSel = selectedIso && selectedIso.Z === iso.Z && selectedIso.A === iso.A;
    const isSoleStable = iso.isSole && iso.stable;
    const isoKey = `${iso.nd},${iso.nt}`;
    const inGroup = groupSet.has(isoKey);

    const gsY = gridScale * zoom;
    const R0  = gsY * 0.9375;

    // Determine scale origin and draw position for group members
    let p = rawP;
    let R = R0;
    let scaleFactor = 1.0;

    if (inGroup) {
      const comp = groupCentroidMap.get(isoKey);
      if (comp) {
        scaleFactor = 1.5;
        const { cx, cy } = comp;
        // Scale position outward from component centroid
        const dx = rawP.x - cx;
        const dy = rawP.y - cy;
        p = { x: cx + dx * scaleFactor, y: cy + dy * scaleFactor };
        R = R0 * scaleFactor;
      }
    } else {
      if (isHov || isSel)                R = R0 * 1.06;
      if (isElemHov && !isHov && !isSel) R = R0 * 1.02;
    }
    R = Math.max(R, 4);

    const relAbd = iso.abd > 0 && maxAbdByZ[iso.Z]
      ? iso.abd / maxAbdByZ[iso.Z] : 0;

    // Group glow / back-glow
    if (inGroup) {
      const rgb = isoColor(iso, 1.0);
      ctx.save();
      ctx.shadowColor = rgb.replace(/[\d.]+\)$/, '0.6)');
      ctx.shadowBlur = 20 * zoom;
      hexPath(ctx, p.x, p.y, R);
      ctx.fillStyle = 'rgba(0,0,0,0)';
      ctx.fill();
      ctx.restore();
    } else if (isHov || isSel || isElemHov) {
      // Normal hover glow
      const gf = isHov ? 1.5 : 1.25;
      hexPath(ctx, p.x, p.y, R * gf);
      ctx.fillStyle = isoColor(iso, isHov ? 0.20 : 0.09);
      ctx.fill();
    }

    hexPath(ctx, p.x, p.y, R);
    if (iso.stable) {
      ctx.fillStyle = isSoleStable
        ? `rgba(20,20,28,${(isHov||isSel||inGroup) ? 1.0 : 0.92})`
        : isoColor(iso, (isHov||isSel||inGroup) ? 0.85 : isElemHov ? 0.72 : 0.58);
    } else {
      ctx.fillStyle = isoColor(iso, (isHov||isSel||inGroup) ? 0.50 : isElemHov ? 0.30 : 0.20);
    }
    ctx.fill();

    // ── Border drawing: for group members, skip edges shared with other group members ──
    if (inGroup) {
      // Draw each edge individually, skipping edges adjacent to other group members
      const R_used = R;
      ctx.save();
      ctx.strokeStyle = isoColor(iso, 0.70);
      ctx.lineWidth = 1.5 * zoom;
      // Flat-top hex: vertex i is at angle i*PI/3
      for (let edge = 0; edge < 6; edge++) {
        // Edge i connects vertex[edge] to vertex[(edge+1)%6]
        // The neighbour sharing this edge in (nd,nt) space:
        // For flat-top hex, edge directions map to HEX_NEIGHBOURS
        const nb = hexNeighbours(iso.nd, iso.nt)[edge];
        const nbKey = `${nb.nd},${nb.nt}`;
        if (groupSet.has(nbKey)) continue; // skip shared edge
        const a1 = (edge * Math.PI) / 3;
        const a2 = ((edge + 1) * Math.PI) / 3;
        ctx.beginPath();
        ctx.moveTo(p.x + R_used * Math.cos(a1), p.y + R_used * Math.sin(a1));
        ctx.lineTo(p.x + R_used * Math.cos(a2), p.y + R_used * Math.sin(a2));
        ctx.stroke();
      }
      ctx.restore();
    } else {
      hexPath(ctx, p.x, p.y, R);
      ctx.strokeStyle = isoColor(iso, iso.stable
        ? (isHov||isSel ? 0.80 : 0.40)
        : (isHov||isSel ? 0.55 : 0.22));
      ctx.lineWidth = isHov||isSel ? 1.2 * zoom : 0.7 * zoom;
      ctx.stroke();
    }

    // Inner abundance hex
    if (relAbd > 0.01) {
      const innerR = Math.max(2, R * relAbd * 0.72);
      hexPath(ctx, p.x, p.y, innerR);
      ctx.fillStyle = isSoleStable
        ? `rgba(255,200,40,${(isHov||isSel||inGroup) ? 1.0 : 0.88})`
        : isoColor(iso, (isHov||isSel||inGroup) ? 1.0 : 0.94);
      ctx.fill();
    }

    if (isSoleStable) {
      hexPath(ctx, p.x, p.y, R + 2 * zoom);
      ctx.strokeStyle = `rgba(255,215,0,${(isHov||isSel||inGroup) ? 0.85 : 0.50})`;
      ctx.lineWidth = 1.0 * zoom;
      ctx.stroke();
    }
    if (isSel) {
      hexPath(ctx, p.x, p.y, R + 4 * zoom);
      ctx.strokeStyle = 'rgba(255,255,255,0.90)';
      ctx.lineWidth = 1.8 * zoom;
      ctx.stroke();
    }

    // Group dotted ring on outer perimeter of isolated members or at outer edges
    if (inGroup) {
      const rgb = isoColor(iso, 1.0);
      const glowColor = rgb.replace(/rgba\((\d+),(\d+),(\d+),[^)]+\)/, 'rgba($1,$2,$3,0.75)');
      ctx.save();
      ctx.shadowColor = glowColor;
      ctx.shadowBlur = 8 * zoom;
      ctx.strokeStyle = glowColor;
      ctx.lineWidth = 2 * zoom;
      ctx.setLineDash([4, 3]);
      hexPath(ctx, p.x, p.y, R + 2 * zoom);
      ctx.stroke();
      ctx.setLineDash([]);
      ctx.restore();
    }

    // Δu_E sideband colour overlay
    if (cbDeltaUE.checked) {
      const v = iso.nd + iso.nt;
      const sp = energySpineByV[v];
      if (sp) {
        const du = (iso.nd - iso.nt) - sp.u;
        const adu = Math.abs(du);
        let dc;
        if      (adu < 0.5) dc = 'rgba(40,230,255,';
        else if (adu < 1.5) dc = 'rgba(40,220,100,';
        else if (adu < 2.5) dc = 'rgba(190,230,40,';
        else if (adu < 3.5) dc = 'rgba(255,190,20,';
        else if (adu < 5.0) dc = 'rgba(255,100,20,';
        else                dc = 'rgba(130,100,100,';
        const alpha = iso.stable ? 0.72 : 0.38;
        hexPath(ctx, p.x, p.y, R * 0.68);
        ctx.fillStyle = dc + alpha + ')';
        ctx.fill();
      }
    }

    // Periodic-table text: sym + mass number inside hex (Change 2 styling)
    if (R >= 7) {
      const symSize = Math.round(Math.min(R * 0.55, 16));
      const numSize = Math.round(Math.min(R * 0.38, 12));

      // Background pill colour
      let pillFill, textFill;
      if (iso.abd > 0) {
        pillFill = 'rgba(0,0,0,0.88)';      textFill = 'rgba(255,255,255,0.95)';
      } else if (iso.stable) {
        pillFill = 'rgba(180,20,20,0.88)';  textFill = 'rgba(255,255,255,0.95)';
      } else {
        pillFill = 'rgba(255,255,255,0.88)'; textFill = 'rgba(0,0,0,0.90)';
      }

      // Measure symbol with Georgia serif
      ctx.font = `bold ${symSize}px Georgia,'Times New Roman',serif`;
      const sw = ctx.measureText(iso.sym).width;

      // Draw pill behind symbol
      const ph = symSize * 1.1, pw = sw + 4;
      const px2 = p.x - pw/2, py_sym = p.y + R * 0.10;
      ctx.fillStyle = pillFill;
      roundRect(ctx, px2, py_sym - ph*0.85, pw, ph, 2);
      ctx.fill();

      // Mass number above — sans-serif
      ctx.font = `400 ${numSize}px 'Segoe UI',Arial,sans-serif`;
      const isTextActive = (isHov || isSel || inGroup);
      ctx.fillStyle = isTextActive ? 'rgba(255,255,255,0.95)' : 'rgba(180,180,180,0.80)';
      ctx.textAlign = 'center';
      ctx.fillText(String(iso.A), p.x, p.y - R * 0.12);

      // Symbol — serif bold
      ctx.font = `bold ${symSize}px Georgia,'Times New Roman',serif`;
      ctx.fillStyle = textFill;
      ctx.fillText(iso.sym, p.x, py_sym);
    }
  });

  // ── CHANGE 4: Draw connecting lines between chain members ─────────────────
  if (activeGroup.length > 1) {
    ctx.save();
    ctx.globalAlpha = 0.5;
    ctx.strokeStyle = 'rgba(255,255,255,0.6)';
    ctx.lineWidth = 1.5 * zoom;
    ctx.setLineDash([4, 4]);
    ctx.shadowColor = 'rgba(255,255,255,0.4)';
    ctx.shadowBlur = 4;
    for (let i = 1; i < activeGroup.length; i++) {
      const a = activeGroup[i-1];
      const b = activeGroup[i];
      const aKey = `${a.nd},${a.nt}`;
      const bKey = `${b.nd},${b.nt}`;
      const aComp = groupCentroidMap.get(aKey);
      const bComp = groupCentroidMap.get(bKey);
      if (!aComp || !bComp) continue;
      const aRawP = isoPos(a);
      const bRawP = isoPos(b);
      const ax = aComp.cx + (aRawP.x - aComp.cx) * 1.5;
      const ay = aComp.cy + (aRawP.y - aComp.cy) * 1.5;
      const bx = bComp.cx + (bRawP.x - bComp.cx) * 1.5;
      const by_ = bComp.cy + (bRawP.y - bComp.cy) * 1.5;
      // Skip if they are adjacent (already visually merged)
      const nbrs = HEX_NEIGHBOURS.map(([dnd,dnt]) => `${a.nd+dnd},${a.nt+dnt}`);
      if (nbrs.includes(bKey)) continue;
      ctx.beginPath();
      ctx.moveTo(ax, ay);
      ctx.lineTo(bx, by_);
      ctx.stroke();
    }
    ctx.setLineDash([]);
    ctx.restore();
  }

  // ── CHANGE 4: Canvas chain panel on right ────────────────────────────────
  if (activeGroup.length > 0) {
    const panX2 = W - 195;
    const panY2 = 60;
    const panW = 185;
    const lineH = 22;
    const panH2 = 16 + activeGroup.length * lineH + 8;

    ctx.save();
    ctx.fillStyle = 'rgba(8,10,18,0.85)';
    roundRect(ctx, panX2, panY2, panW, panH2, 6);
    ctx.fill();
    ctx.strokeStyle = 'rgba(212,160,92,0.25)';
    ctx.lineWidth = 0.8;
    roundRect(ctx, panX2, panY2, panW, panH2, 6);
    ctx.stroke();

    ctx.font = '600 10px "Segoe UI",sans-serif';
    ctx.fillStyle = groupLocked ? 'rgba(212,160,92,0.90)' : 'rgba(170,180,200,0.80)';
    ctx.textAlign = 'left';
    ctx.fillText(groupLocked ? '🔒 Decay Chain (locked)' : 'Decay Chain', panX2 + 8, panY2 + 12);

    activeGroup.forEach((iso, i) => {
      const yRow = panY2 + 20 + i * lineH;
      const rgb = isoColor(iso, 1.0);
      const dotColor = rgb.replace(/rgba\((\d+),(\d+),(\d+),[^)]+\)/, 'rgba($1,$2,$3,0.85)');

      ctx.fillStyle = dotColor;
      ctx.beginPath();
      ctx.arc(panX2 + 10, yRow + 5, 3.5, 0, Math.PI*2);
      ctx.fill();

      ctx.font = '600 10px "Segoe UI",sans-serif';
      ctx.fillStyle = 'rgba(220,215,200,0.92)';
      ctx.fillText(`${iso.sym}-${iso.A}`, panX2 + 18, yRow + 9);

      const decay = iso.stable ? 'stable' : (iso.decay || '—');
      if (i < activeGroup.length - 1) {
        ctx.font = '400 9px "Segoe UI",sans-serif';
        ctx.fillStyle = 'rgba(160,140,100,0.70)';
        ctx.fillText(`→ ${decay}`, panX2 + 58, yRow + 9);
      }

      const beStr = iso.be > 0 ? iso.be.toFixed(3) + ' MeV' : '—';
      ctx.font = '400 9px "Segoe UI",sans-serif';
      ctx.fillStyle = 'rgba(130,150,180,0.70)';
      ctx.textAlign = 'right';
      ctx.fillText(beStr, panX2 + panW - 6, yRow + 9);
      ctx.textAlign = 'left';
    });

    ctx.restore();
  }
}

// Helper roundRect for pill labels
function roundRect(ctx, x, y, w, h, r) {
  ctx.beginPath();
  ctx.moveTo(x+r, y);
  ctx.lineTo(x+w-r, y);
  ctx.arcTo(x+w, y, x+w, y+r, r);
  ctx.lineTo(x+w, y+h-r);
  ctx.arcTo(x+w, y+h, x+w-r, y+h, r);
  ctx.lineTo(x+r, y+h);
  ctx.arcTo(x, y+h, x, y+h-r, r);
  ctx.lineTo(x, y+r);
  ctx.arcTo(x, y, x+r, y, r);
  ctx.closePath();
}
