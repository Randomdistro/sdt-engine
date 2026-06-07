/* ── UI: hover detection, panel update, element label column ── */

const tooltip = document.getElementById("tooltip");

// ── Active group state (Change 4) ────────────────────────────────────────────
let activeGroup = [];    // array of iso objects in the current decay chain
let groupLocked = false; // true when user has clicked to lock

// ── Change 3: Hex hit test (flat-top hexagon) ────────────────────────────────
function pointInHex(px, py, cx, cy, R) {
  const x = px - cx, y = py - cy;
  const s3 = Math.sqrt(3);
  return Math.abs(x) <= R
      && Math.abs(x * 0.5 + y * s3 * 0.5) <= R
      && Math.abs(-x * 0.5 + y * s3 * 0.5) <= R;
}

function getIsoAtPos(mx, my) {
  // mx, my are already in canvas coords (no LEFT_W offset needed since
  // we pass e.clientX directly and the canvas starts at LEFT_W)
  const corrX = mx - LEFT_W;
  const hexR = gridScale * zoom * 0.9375;
  let best = null, bestD = Infinity;
  ISO.forEach(iso => {
    const p = isoPos(iso);
    if (pointInHex(corrX, my, p.x, p.y, hexR)) {
      // pick the one whose centre is closest (handles overlaps)
      const d = (p.x - corrX) ** 2 + (p.y - my) ** 2;
      if (d < bestD) { best = iso; bestD = d; }
    }
  });
  return best;
}

function buildIsoRow(iso, isActive) {
  const tfPct = (iso.tf * 100).toFixed(1);
  const stableSpan = iso.stable
    ? `<span class="iso-stable">${iso.abd > 0 ? iso.abd+'%' : 'stable'}</span>`
    : `<span class="iso-unstable">unstable</span>`;
  const soleSpan = iso.isSole && iso.stable ? ' <span class="iso-sole">SOLE</span>' : '';
  return `<div class="iso-row ${isActive ? 'active' : 'context'}" data-a="${iso.A}">
    <span class="iso-name">${iso.sym}-${iso.A}</span>${soleSpan}
    ${isActive ? `<span style="color:#888;font-weight:400;font-size:11px;margin-left:6px;">Z=${iso.Z} · spin ${iso.spin||'—'}</span>` : ''}<br>
    <span class="iso-grammar">
      <span class="a">1α</span> + <span class="d">${iso.nd}d</span> + <span class="t">${iso.nt}t</span>
      <span style="color:#666;margin-left:6px;">${tfPct}% t</span>
      ${isActive ? `<span style="color:#555;margin-left:8px;">BE ${iso.be} MeV/n</span>` : ''}
    </span><br>
    ${isActive ? `<span style="color:#777;font-size:11px;">${iso.oddA?'odd-A':'even-A'} · n_d=${iso.nd} n_t=${iso.nt}</span>` : ''}
    ${!isActive ? stableSpan : `<span style="font-size:11px;">${stableSpan}</span>`}
  </div>`;
}

function updateHoverPanel(activeIso) {
  const elemIsos = ISO.filter(e => e.Z === activeIso.Z).sort((a,b) => a.A - b.A);
  const name = ELEM_NAMES[activeIso.Z] || activeIso.sym;
  const stableCount = elemIsos.filter(e => e.stable).length;

  document.getElementById("pSym").textContent = activeIso.sym;
  document.getElementById("pElemName").textContent = name;
  document.getElementById("pElemZ").textContent = `Z=${activeIso.Z} · ${stableCount} stable isotope${stableCount!==1?'s':''}`;

  const scroll = document.getElementById("isoScroll");
  scroll.innerHTML = elemIsos.map(iso => buildIsoRow(iso, iso.A === activeIso.A)).join('');

  const activeRow = scroll.querySelector('.iso-row.active');
  if (activeRow) activeRow.scrollIntoView({ block: 'nearest', behavior: 'smooth' });

  if (window.__pipSetIso) window.__pipSetIso(activeIso);
}

function updatePanel(iso) {
  updateHoverPanel(iso);
}

// ── Change 4: Build decay chain group ───────────────────────────────────────
function buildActiveGroup(iso) {
  if (!iso) return [];
  const group = [iso];
  const seen = new Set([`${iso.nd},${iso.nt}`]);

  // Forward chain (up to 8 steps)
  const fwd = decayChain(iso, 8, false);
  fwd.forEach(step => {
    const key = `${step.to.nd},${step.to.nt}`;
    if (!seen.has(key)) { seen.add(key); group.push(step.to); }
  });

  // Backward chain (up to 2 steps)
  const bwd = decayChain(iso, 2, true);
  bwd.forEach(step => {
    const key = `${step.from.nd},${step.from.nt}`;
    if (!seen.has(key)) { seen.add(key); group.unshift(step.from); }
  });

  return group;
}

// ── Tooltip mousemove ───────────────────────────────────────────────────────
canvas.addEventListener("mousemove", e => {
  const mx = e.clientX, my = e.clientY;
  const iso = getIsoAtPos(mx, my);
  const prevZ = hoveredZ;
  hoveredIso = iso;
  hoveredZ = iso ? iso.Z : null;

  // Change 4: update activeGroup if not locked
  if (!groupLocked) {
    if (iso) {
      activeGroup = buildActiveGroup(iso);
    } else {
      activeGroup = [];
    }
  }

  if (hoveredZ !== prevZ) draw();
  else if (iso) draw();

  if (iso) {
    updateHoverPanel(iso);
    canvas.style.cursor = "pointer";
    tooltip.style.display = "block";
    tooltip.style.left = (mx + 16) + "px";
    tooltip.style.top  = (my - 10) + "px";
    const tfPct = (iso.tf * 100).toFixed(1);
    const soleTag = iso.isSole && iso.stable ? ' · <span style="color:#c8a850;">SOLE</span>' : '';
    const magicTag = MAGIC_Z.includes(iso.Z) ? ' · <span style="color:#82b482;">magic Z</span>' : '';
    tooltip.innerHTML = `
      <strong style="font-size:15px;color:#d4a05c;">${iso.sym}-${iso.A}</strong>
      <span style="color:#888;margin-left:6px;">Z=${iso.Z}</span>
      ${iso.stable ? '' : '<span style="color:#c55;margin-left:6px;">unstable</span>'}
      ${soleTag}${magicTag}
      <br>
      <span style="color:#d4a05c;">1α</span> +
      <span style="color:#6a95b0;">${iso.nd}d</span> +
      <span style="color:#c27a5a;">${iso.nt}t</span>
      <span style="color:#666;margin-left:8px;">${tfPct}% triton</span>
      <br>
      <span style="color:#888;">BE: ${iso.be} MeV/n · ${iso.abd}% · ${iso.spin || '—'}</span>
      <br><span style="color:#555;font-size:10px;">Click to lock chain · Dbl-click for datasheet</span>
    `;
  } else {
    let found = null, foundType = null;
    const checkDist = 12;
    if (cbMissing.checked) {
      for (const m of MISSING_ALPHA) {
        const p = gridPos(m.nd, m.nt);
        const corrX = mx - LEFT_W;
        if (Math.abs(p.x - corrX) < checkDist && Math.abs(p.y - my) < checkDist) { found = m; foundType = "α"; break; }
      }
    }
    if (!found && cbHe3Miss.checked) {
      for (const m of MISSING_HE3) {
        const p = gridPos(m.nd, m.nt);
        const corrX = mx - LEFT_W;
        if (Math.abs(p.x - corrX) < checkDist && Math.abs(p.y - my) < checkDist) { found = m; foundType = "He-3"; break; }
      }
    }
    if (found) {
      canvas.style.cursor = "help";
      tooltip.style.display = "block";
      tooltip.style.left = (mx + 16) + "px";
      tooltip.style.top  = (my - 10) + "px";
      const typeLabels = {"odd-odd":"odd-odd","even-even":"even-even","magic":"magic number","gap":"no natural element","mixed":"odd-even"};
      tooltip.innerHTML = `
        <strong style="font-size:13px;color:#b040ff;">MISSING ${foundType}-structure</strong><br>
        <span style="color:#aaa;">Z=${found.Z} · A=${found.A} · N=${found.N}</span><br>
        <span style="color:#d4a05c;">1${foundType === "He-3" ? " He-3" : "α"}</span> +
        <span style="color:#6a95b0;">${found.nd}d</span> +
        <span style="color:#c27a5a;">${found.nt}t</span><br>
        <span style="color:#888;">${typeLabels[found.mtype] || found.mtype}</span>
      `;
    } else {
      canvas.style.cursor = "crosshair";
      tooltip.style.display = "none";
    }
  }
});

canvas.addEventListener("mouseleave", () => {
  hoveredIso = null; tooltip.style.display = "none"; draw();
});

canvas.addEventListener("mouseleave", () => {
  if (window.__pipSetIso && !selectedIso) window.__pipSetIso(null);
}, { capture: false });

// ── Change 4: Click to lock/unlock chain ────────────────────────────────────
canvas.addEventListener("click", e => {
  const iso = getIsoAtPos(e.clientX, e.clientY);
  if (iso) {
    if (!groupLocked) {
      groupLocked = true;
      selectedIso = iso;
      updatePanel(iso);
    } else {
      groupLocked = false;
      activeGroup = buildActiveGroup(iso);
      selectedIso = iso;
      updatePanel(iso);
    }
    draw();
  } else {
    // Clicked outside — clear lock
    groupLocked = false;
    activeGroup = [];
    draw();
  }
});

// ── Change 6: Double-click datasheet ────────────────────────────────────────
canvas.addEventListener("dblclick", e => {
  const iso = getIsoAtPos(e.clientX, e.clientY);
  if (!iso) return;

  const name = ELEM_NAMES[iso.Z] || iso.sym;
  const N = iso.A - iso.Z;
  const v = iso.nd + iso.nt;
  const u = iso.nd - iso.nt;
  const sp = energySpineByV[v];
  const duE = sp ? (u - sp.u).toFixed(3) : '—';
  const decayStr = iso.stable ? 'stable (−)' : (iso.decay || '—');
  const halfLife = (() => {
    const key = `${iso.Z},${iso.A}`;
    for (const row of [...LONG_LIVED, ...SHORT_LIVED]) {
      if (row[0] === iso.Z && row[1] === iso.A) return row[3];
    }
    return iso.stable ? 'stable' : '—';
  })();

  const ds = document.getElementById('datasheet');
  document.getElementById('datasheetContent').innerHTML = `
    <h2 style="margin:0 0 4px;font-size:22px;color:#eef;">${iso.sym}-${iso.A} &nbsp;<span style="font-size:16px;color:#aaa;">${name}</span></h2>
    <div style="color:#667;font-size:13px;margin-bottom:16px;">Z=${iso.Z} &nbsp; N=${N} &nbsp; A=${iso.A} &nbsp; ${iso.oddA?'odd-A':'even-A'}</div>
    <table>
      <tr><td style="color:#889;padding:3px 8px 3px 0;width:48%;">Half-life</td><td style="color:#dde;">${halfLife}</td></tr>
      <tr><td style="color:#889;padding:3px 8px 3px 0;">Decay mode</td><td style="color:#dde;">${decayStr}</td></tr>
      <tr><td style="color:#889;padding:3px 8px 3px 0;">BE/A</td><td style="color:#dde;">${iso.be > 0 ? iso.be + ' MeV' : '—'}</td></tr>
      <tr><td style="color:#889;padding:3px 8px 3px 0;">Natural abundance</td><td style="color:#dde;">${iso.abd > 0 ? iso.abd + '%' : (iso.stable ? 'stable, 0% natural' : 'none')}</td></tr>
      <tr><td style="color:#889;padding:3px 8px 3px 0;">Spin/parity</td><td style="color:#dde;">${iso.spin || '—'}</td></tr>
      <tr><td style="color:#889;padding:3px 8px 3px 0;">SDT: nd / nt / v / u</td><td style="color:#dde;">${iso.nd} / ${iso.nt} / ${v} / ${u}</td></tr>
      <tr><td style="color:#889;padding:3px 8px 3px 0;">Δu_E</td><td style="color:#dde;">${duE}</td></tr>
    </table>
    <h3 style="margin:16px 0 8px;color:#889;font-size:12px;text-transform:uppercase;letter-spacing:0.05em;">References</h3>
    <div style="display:flex;flex-direction:column;gap:8px;font-size:12px;">
      <a href="https://www.nndc.bnl.gov/nudat3/indx_sigma.jsp?z=${iso.Z}&a=${iso.A}" target="_blank">NuDat 3.0 (NNDC)</a>
      <a href="https://en.wikipedia.org/wiki/${iso.sym}-${iso.A}" target="_blank">Wikipedia: ${iso.sym}-${iso.A}</a>
      <a href="https://www-nds.iaea.org/relnsd/NdsEnsdf/QueryForm?select=levels&nuclides=${iso.A}${iso.sym}" target="_blank">IAEA Nuclear Data</a>
    </div>
  `;
  ds.style.display = 'block';
});

// ── Morph slider (Change 1) ─────────────────────────────────────────────────
const slider = document.getElementById("morphSlider");
slider.addEventListener("input", () => {
  morphT = +slider.value / 1000;
  // Update active button highlights
  document.querySelectorAll('.morph-btn').forEach(b => {
    b.classList.toggle('active', +b.dataset.val === +slider.value);
  });
  draw();
});

// ── Print diagnostic table ───────────────────────────────────────────────────
document.getElementById('printDiagBtn').addEventListener('click', () => {
  const MAGIC_Z_D = new Set([2,8,20,28,50,82,114]);
  const MAGIC_N_D = new Set([2,8,20,28,50,82,126]);
  const rows = [];
  vVals.forEach(v => {
    const rowIsos = ISO.filter(e => (e.nd+e.nt)===v && e.be>0);
    if (!rowIsos.length) return;
    const raw = rawMaxSpine[v];
    const sp  = energySpineByV[v];
    const uMono = getUFit(v);
    const nearIso = sp ? sp.iso : (raw ? rowIsos.find(e=>e.sym===raw.sym&&e.A===raw.A) : rowIsos[0]);
    rows.push({
      v,
      rawMaxU:  raw ? raw.u.toFixed(2) : '—',
      smoothU:  sp  ? sp.u.toFixed(2)  : '—',
      monoU:    uMono.toFixed(2),
      dRawMono: raw ? (raw.u - uMono).toFixed(2) : '—',
      dRawGold: raw ? raw.u.toFixed(2) : '—',
      isotope:  nearIso ? `${nearIso.sym}-${nearIso.A}` : '—',
      bePerA:   raw ? raw.be.toFixed(4) : '—',
      magicZ:   nearIso ? MAGIC_Z_D.has(nearIso.Z) : false,
      magicN:   nearIso ? MAGIC_N_D.has(nearIso.A - nearIso.Z) : false,
      oddA:     nearIso ? nearIso.oddA : '—',
      spin:     nearIso ? (nearIso.spin||'—') : '—',
      unpaired: nearIso ? nearIso.unpaired : '—',
      conf:     sp ? sp.confidence : '—',
    });
  });
  console.table(rows);
  console.log('[Δu_E table] printed', rows.length, 'rows. Open DevTools (F12) → Console to view.');
  alert('Δu_E table printed to browser console.\nOpen DevTools (F12) → Console tab to view all ' + rows.length + ' rows.');
});

function resize() {
  const vw = window.innerWidth - LEFT_W - RIGHT_W;
  const vh = window.innerHeight;
  W = vw;
  H = vh;
  canvas.width  = W * dpr;
  canvas.height = H * dpr;
  canvas.style.width  = W + "px";
  canvas.style.height = H + "px";
  canvas.style.position = "fixed";
  canvas.style.left = LEFT_W + "px";
  canvas.style.top  = "0px";
  ctx.setTransform(dpr, 0, 0, dpr, 0, 0);
  // Resize PIP canvas
  const pip = document.getElementById("pip");
  const pc  = document.getElementById("pipCanvas");
  if (pip && pc) {
    pc.width  = pip.offsetWidth  * dpr;
    pc.height = pip.offsetHeight * dpr;
    pc.style.width  = pip.offsetWidth  + "px";
    pc.style.height = pip.offsetHeight + "px";
  }
}

// ── Element label column (drawn on top, as part of UI layer) ───────────────
function drawElemLabels(ctx) {
  const LABEL_X2 = 6;
  const LABEL_W2 = 130;
  ctx.fillStyle = "rgba(18,16,14,0.72)";
  ctx.fillRect(0, 0, LABEL_W2, H);

  const uniqueZs2 = [...new Set(ISO.map(e => e.Z))].sort((a,b) => a-b);
  let lastLY = -999;
  uniqueZs2.forEach(Z => {
    const v = ELEM_REF_V[Z];
    if (v === undefined) return;
    const vRng = (vMax - vMin) || 1;
    const sP = 80;
    const sc = (H - sP*2) / vRng;
    const by = sP + (v - vMin) * sc;
    const yS = H/2 + (by - H/2 + panY) * zoom;
    if (yS < 12 || yS > H - 8) return;
    if (yS - lastLY < 11) return;
    lastLY = yS;

    const rgb = Z_PALETTE[Z % Z_PALETTE.length];
    const elemIsos = ISO.filter(e => e.Z === Z);
    const isSole = elemIsos.filter(e => e.stable).length === 1;
    const sym = elemIsos[0].sym;
    const name = ELEM_NAMES[Z] || '';
    const isHovZ = hoveredZ === Z;

    if (isHovZ) {
      ctx.fillStyle = "rgba(255,200,40,0.08)";
      ctx.fillRect(0, yS - 7, LABEL_W2, 14);
    }

    ctx.beginPath();
    ctx.arc(LABEL_X2 + 5, yS, 3.5, 0, Math.PI*2);
    if (isSole) {
      ctx.fillStyle = "rgba(20,20,28,0.95)"; ctx.fill();
      ctx.strokeStyle = "rgba(255,200,40,0.9)"; ctx.lineWidth = 1.2; ctx.stroke();
    } else {
      ctx.fillStyle = `rgba(${rgb},0.9)`; ctx.fill();
    }

    ctx.fillStyle = isHovZ ? "#ffe066" : (isSole ? "rgba(255,200,40,0.95)" : `rgba(${rgb},1.0)`);
    ctx.font = `${isHovZ ? "800" : "700"} 10px 'Segoe UI',sans-serif`;
    ctx.textAlign = "left";
    ctx.fillText(sym, LABEL_X2 + 13, yS + 3.5);

    ctx.fillStyle = isHovZ ? "rgba(220,210,190,0.95)" : "rgba(150,140,130,0.65)";
    ctx.font = `${isHovZ ? "500" : "400"} 9px 'Segoe UI',sans-serif`;
    ctx.fillText(name, LABEL_X2 + 33, yS + 3.5);
  });
}
