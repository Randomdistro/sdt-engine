function drawOverlays(ctx) {
  // ── 1. Grammar Sheets (4 types of tiers) ────────────────────────────────
  const showLL    = cbLongLived.checked;
  const showMid   = cbMid.checked;
  const showShort = cbShort.checked;
  const showDec   = cbDecade.checked;
  const showT4    = cbTier4.checked;
  const showT5    = cbTier5.checked;
  const showT6    = cbTier6.checked;
  const showT7    = cbTier7.checked;
  const showT8    = cbTier8.checked;
  const showT9    = cbTier9.checked;

  // Render LONG_LIVED
  if (showLL || showMid || showShort || showDec) {
    LONG_LIVED.forEach(([Z, A, sym, hl, decay, nd, nt, tier]) => {
      const shouldShow =
        (tier === 3 && showLL)  ||
        (tier === 2 && showMid) ||
        (tier === 1 && showShort) ||
        (tier === 0 && showDec);
      if (!shouldShow) return;
      if (ISO.find(e => e.Z===Z && e.A===A)) return; // already drawn as real iso
      const p = gridPos(nd, nt);
      if (p.x < 60 || p.x > W - 10 || p.y < 20 || p.y > H - 20) return;
      const R = Math.max(3, gridScale * zoom * 0.75);
      const tierCols = ['rgba(200,160,50,', 'rgba(160,120,40,', 'rgba(120,90,30,', 'rgba(80,60,20,'];
      const col = tierCols[Math.min(tier, 3)];
      ctx.beginPath(); ctx.arc(p.x, p.y, R, 0, Math.PI*2);
      ctx.fillStyle = col + '0.4)';
      ctx.fill();
      ctx.beginPath(); ctx.arc(p.x, p.y, R, 0, Math.PI*2);
      ctx.strokeStyle = col + '0.7)'; ctx.lineWidth = 0.6; ctx.stroke();
      if (R >= 6) {
        ctx.font = `500 ${Math.min(R*0.7, 10)}px 'Segoe UI',sans-serif`;
        ctx.textAlign = 'center'; ctx.textBaseline = 'middle';
        ctx.fillStyle = 'rgba(255,200,100,0.8)';
        ctx.fillText(sym, p.x, p.y - R*0.08);
        ctx.font = `400 ${Math.min(R*0.5, 8)}px 'Segoe UI',sans-serif`;
        ctx.fillStyle = 'rgba(255,200,100,0.5)';
        ctx.fillText(hl, p.x, p.y + R*0.42);
        ctx.textBaseline = 'alphabetic';
      }
    });
  }

  // Render SHORT_LIVED
  if (showT4 || showT5 || showT6 || showT7 || showT8 || showT9) {
    const tierShows = [false, false, false, false, showT4, showT5, showT6, showT7, showT8, showT9];
    const tierCols = {
      4:'rgba(160,100,40,', 5:'rgba(140,80,200,', 6:'rgba(60,160,200,',
      7:'rgba(80,180,80,',  8:'rgba(200,80,180,', 9:'rgba(255,80,80,'
    };
    SHORT_LIVED.forEach(([Z, A, sym, hl, decay, nd, nt, tier]) => {
      if (!tierShows[tier]) return;
      if (nd < 0 || nt < 0) return;
      if (ISO.find(e => e.Z===Z && e.A===A)) return;
      const p = gridPos(nd, nt);
      if (p.x < 60 || p.x > W - 10 || p.y < 20 || p.y > H - 20) return;
      const R = Math.max(2, gridScale * zoom * 0.65);
      const col = tierCols[tier] || 'rgba(180,180,180,';
      ctx.beginPath(); ctx.arc(p.x, p.y, R, 0, Math.PI*2);
      ctx.fillStyle = col + '0.35)';
      ctx.fill();
      ctx.beginPath(); ctx.arc(p.x, p.y, R, 0, Math.PI*2);
      ctx.strokeStyle = col + '0.65)'; ctx.lineWidth = 0.6; ctx.stroke();
      if (R >= 5) {
        ctx.font = `500 ${Math.min(R*0.7, 9)}px 'Segoe UI',sans-serif`;
        ctx.textAlign = 'center'; ctx.textBaseline = 'middle';
        ctx.fillStyle = col + '0.8)';
        ctx.fillText(sym, p.x, p.y);
        ctx.textBaseline = 'alphabetic';
      }
    });
  }

  // ── 2. Missing Alpha Positions ─────────────────────────────────────────
  if (cbMissing.checked) {
    const typeColors = {
      "even-even": "rgba(80,120,200,0.20)",
      "magic":     "rgba(80,200,80,0.25)",
      "odd-odd":   "rgba(200,80,80,0.18)",
      "mixed":     "rgba(180,140,60,0.18)",
      "gap":       "rgba(120,120,120,0.18)"
    };
    MISSING_ALPHA.forEach(m => {
      const p = gridPos(m.nd, m.nt);
      if (p.x < 60 || p.x > W - 10 || p.y < 20 || p.y > H - 20) return;
      const R = Math.max(1, gridScale * zoom * 0.45);
      hexPath(ctx, p.x, p.y, R * 0.80);
      ctx.fillStyle = typeColors[m.mtype] || "rgba(100,100,120,0.18)";
      ctx.fill();
      ctx.strokeStyle = ctx.fillStyle.replace(/[\.\d]+\)$/, "0.40)");
      ctx.lineWidth = 0.5;
      ctx.stroke();
    });
  }

  // ── 3. Missing He-3 Structures ────────────────────────────────────────
  if (cbHe3Miss && cbHe3Miss.checked) {
    const typeColors = {
      "even-even": "rgba(40,220,180,0.20)",
      "magic":     "rgba(40,220,80,0.25)",
      "odd-odd":   "rgba(220,80,160,0.18)",
      "mixed":     "rgba(160,200,60,0.18)",
      "gap":       "rgba(120,120,120,0.18)"
    };
    MISSING_HE3.forEach(m => {
      const nd3 = m.nd, nt3 = m.nt;
      const Z  = 2 + nd3 + nt3;
      const p  = gridPos(nd3, nt3);
      if (p.x < 60 || p.x > W - 10 || p.y < 20 || p.y > H - 20) return;
      const R = Math.max(1, gridScale * zoom * 0.38);
      hexPath(ctx, p.x, p.y, R);
      ctx.fillStyle = typeColors[m.mtype] || "rgba(80,220,180,0.15)";
      ctx.fill();
      ctx.strokeStyle = ctx.fillStyle.replace(/[\.\d]+\)$/, "0.40)");
      ctx.lineWidth = 0.4;
      ctx.stroke();
    });
  }

  // ── 4. He-3 grammar overlay on existing isos ──────────────────────────
  if (cbHe3 && cbHe3.checked) {
    HE3_EXISTING.forEach(iso => {
      const p = isoPos(iso);
      if (p.x < 60 || p.x > W - 10 || p.y < 20 || p.y > H - 20) return;
      const R = Math.max(2, gridScale * zoom * 0.52);
      hexPath(ctx, p.x, p.y, R);
      ctx.strokeStyle = 'rgba(40,220,180,0.45)';
      ctx.lineWidth = 1.2;
      ctx.stroke();
    });
  }

  // ── 5. Deuteron Chain ─────────────────────────────────────────────────
  if (cbDeut.checked) {
    const dIsos = ISO.filter(e => e.nt === 0).sort((a,b) => a.nd - b.nd);
    if (dIsos.length > 1) {
      ctx.save();
      ctx.shadowColor = 'rgba(100,180,255,0.5)'; ctx.shadowBlur = 6;
      ctx.strokeStyle = 'rgba(100,180,255,0.40)'; ctx.lineWidth = 1.2;
      ctx.setLineDash([6,5]);
      ctx.beginPath();
      dIsos.forEach((iso,i) => { const p = isoPos(iso); i===0 ? ctx.moveTo(p.x,p.y) : ctx.lineTo(p.x,p.y); });
      ctx.stroke();
      ctx.restore();
    }
  }

  // ── 6. Decay Pathway Arrows ──────────────────────────────────────────
  if (cbDecayVec.checked) {
    const ARROWSZ = Math.max(3, gridScale * zoom * 1.5);
    const ARROW_ALPHA = 0.65;
    const isoSel = selectedIso || hoveredIso;
    if (isoSel && isoSel.decay && isoSel.decay !== '-' && isoSel.decay !== 'stable') {
      const dv = DECAY_VECTORS[isoSel.decay];
      if (dv) {
        const steps = decayChain(isoSel, 8, false);
        steps.forEach(step => {
          const from = isoPos(step.from);
          const to   = isoPos(step.to);
          if (from.x < 0 || from.x > W || to.x < 0 || to.x > W) return;
          ctx.save();
          ctx.strokeStyle = step.color;
          ctx.lineWidth = 1.8 * zoom;
          ctx.globalAlpha = ARROW_ALPHA;
          ctx.beginPath(); ctx.moveTo(from.x, from.y); ctx.lineTo(to.x, to.y); ctx.stroke();
          const angle = Math.atan2(to.y - from.y, to.x - from.x);
          const asz = ARROWSZ;
          ctx.fillStyle = step.color;
          ctx.beginPath();
          ctx.moveTo(to.x, to.y);
          ctx.lineTo(to.x - asz * Math.cos(angle - Math.PI/6), to.y - asz * Math.sin(angle - Math.PI/6));
          ctx.lineTo(to.x - asz * Math.cos(angle + Math.PI/6), to.y - asz * Math.sin(angle + Math.PI/6));
          ctx.closePath(); ctx.fill();
          ctx.restore();
        });
      }
    }
  }

  // ── 7. Energy Functional diagnostics panel ───────────────────────────
  if (cbDeltaUE.checked && window._energySpineDiag) {
    const d = window._energySpineDiag;
    ctx.save();
    ctx.fillStyle = 'rgba(0,0,0,0.70)';
    ctx.fillRect(W - 215, H - 95, 210, 88);
    ctx.strokeStyle = 'rgba(40,180,180,0.35)';
    ctx.lineWidth = 0.8;
    ctx.strokeRect(W - 215, H - 95, 210, 88);
    ctx.font = '600 10px "Segoe UI",sans-serif';
    ctx.fillStyle = 'rgba(40,200,200,0.90)';
    ctx.textAlign = 'left';
    ctx.fillText('Δu_E diagnostics', W - 209, H - 78);
    const lines = [
      `Rows fitted: ${d.nRows}`,
      `RMS mono–energy sep: ${d.rmsSep.toFixed(3)}`,
      `Stable mean offset: ${d.meanStableDelta.toFixed(3)}`,
      `Stable median offset: ${d.medianStableDelta.toFixed(3)}`,
    ];
    ctx.font = '500 9px "Segoe UI",sans-serif';
    ctx.fillStyle = 'rgba(160,210,210,0.85)';
    lines.forEach((l,i) => ctx.fillText(l, W - 209, H - 62 + i * 13));
    ctx.restore();

    // ── Δu_E colour legend strip ──────────────────────────────────────────
    const legX = W - 215, legY = H - 110;
    const legendCols = [
      ['rgba(40,230,255,0.80)','< 0.5'],
      ['rgba(40,220,100,0.80)','0.5–1.5'],
      ['rgba(190,230,40,0.80)','1.5–2.5'],
      ['rgba(255,190,20,0.80)','2.5–3.5'],
      ['rgba(255,100,20,0.80)','3.5–5'],
      ['rgba(130,100,100,0.80)','> 5'],
    ];
    ctx.save();
    ctx.font = '600 9px "Segoe UI",sans-serif';
    ctx.fillStyle = 'rgba(40,200,200,0.75)';
    ctx.textAlign = 'left';
    ctx.fillText('|Δu_E|:', legX, legY + 3);
    legendCols.forEach((lc, i) => {
      const lx = legX + 40 + i * 28;
      ctx.fillStyle = lc[0];
      ctx.fillRect(lx, legY - 8, 22, 12);
      ctx.fillStyle = 'rgba(200,200,200,0.70)';
      ctx.font = '8px "Segoe UI",sans-serif';
      ctx.fillText(lc[1], lx, legY + 12);
    });
    ctx.restore();
  }

  // ── 8. BE / nucleon overlay rings ────────────────────────────────────
  if (cbBE.checked) {
    ISO.forEach(iso => {
      if (!iso.be || iso.be <= 0) return;
      const p = isoPos(iso);
      if (p.x < 60 || p.x > W - 10) return;
      const R = Math.max(2, gridScale * zoom * 0.9);
      const t = Math.max(0, Math.min(1, (iso.be - 4) / 5));
      const r = Math.round(40 + (1-t)*200);
      const g = Math.round(40 + t*200);
      const b = 80;
      ctx.beginPath(); ctx.arc(p.x, p.y, R * 0.9, 0, Math.PI*2);
      ctx.strokeStyle = `rgba(${r},${g},${b},0.40)`;
      ctx.lineWidth = R * 0.10;
      ctx.stroke();
    });
  }

  // ── 9. Element label column ──────────────────────────────────────────
  if (cbLabels.checked) {
    ctx.font = "500 11px 'Segoe UI',sans-serif";
    ctx.textAlign = "right";
    const zs = [...new Set(ISO.map(e => e.Z))];
    zs.forEach(Z => {
      const ref = ELEM_REF_V[Z];
      if (ref === undefined) return;
      const v = ref;
      const isoRef = ISO.find(e => e.Z === Z && (e.nd + e.nt) === v);
      if (!isoRef) return;
      const p = isoPos(isoRef);
      if (p.y < 20 || p.y > H - 20) return;
      ctx.fillStyle = Z === (hoveredZ || -1) ? "rgba(255,255,200,0.8)" : "rgba(190,170,140,0.45)";
      ctx.fillText(isoRef.sym, 122, p.y + 4);
      ctx.fillStyle = "rgba(130,115,95,0.35)";
      ctx.font = "400 9px 'Segoe UI',sans-serif";
      ctx.fillText(Z, 108, p.y + 4);
      ctx.font = "500 11px 'Segoe UI',sans-serif";
    });
  }

  // ── 10. Hover panel update ─────────────────────────────────────────
  const hIso = hoveredIso || selectedIso;
  if (hIso) updateHoverPanel(hIso);
}
