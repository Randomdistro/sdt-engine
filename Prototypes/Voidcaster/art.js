/* VOIDCASTER · procedural 16-bit art: hero, bodies, mission sprites. */
'use strict';
const VCArt = (() => {
  function rng(seed) { let a = seed >>> 0; return () => { a = (a + 0x6D2B79F5) >>> 0; let t = a; t = Math.imul(t ^ (t >>> 15), t | 1); t ^= t + Math.imul(t ^ (t >>> 7), t | 61); return ((t ^ (t >>> 14)) >>> 0) / 4294967296; }; }
  const hex = (h) => [parseInt(h.slice(1, 3), 16), parseInt(h.slice(3, 5), 16), parseInt(h.slice(5, 7), 16)];

  function pxCircle(c, cx, cy, r, col) {
    cx = Math.round(cx); cy = Math.round(cy); r = Math.max(1, Math.round(r)); c.fillStyle = col;
    for (let dy = -r; dy <= r; dy++) { const w = Math.floor(Math.sqrt(r * r - dy * dy + r * 0.5)); c.fillRect(cx - w, cy + dy, w * 2 + 1, 1); }
  }
  function pxRing(c, cx, cy, r, col, th = 1) {
    cx = Math.round(cx); cy = Math.round(cy); r = Math.round(r); c.fillStyle = col;
    const ri = r - th;
    for (let dy = -r; dy <= r; dy++) {
      const wo = Math.floor(Math.sqrt(r * r - dy * dy + r * 0.5));
      if (Math.abs(dy) <= ri) {
        const wi = Math.floor(Math.sqrt(Math.max(0, ri * ri - dy * dy + ri * 0.5)));
        c.fillRect(cx - wo, cy + dy, wo - wi, 1); c.fillRect(cx + wi + 1, cy + dy, wo - wi, 1);
      } else c.fillRect(cx - wo, cy + dy, wo * 2 + 1, 1);
    }
  }
  function pxLine(c, x0, y0, x1, y1, col) {
    x0 = Math.round(x0); y0 = Math.round(y0); x1 = Math.round(x1); y1 = Math.round(y1); c.fillStyle = col;
    const dx = Math.abs(x1 - x0), dy = -Math.abs(y1 - y0), sx = x0 < x1 ? 1 : -1, sy = y0 < y1 ? 1 : -1; let e = dx + dy, n = 0;
    for (;;) { c.fillRect(x0, y0, 1, 1); if ((x0 === x1 && y0 === y1) || n++ > 400) break; const e2 = 2 * e; if (e2 >= dy) { e += dy; x0 += sx; } if (e2 <= dx) { e += dx; y0 += sy; } }
  }

  /* ---------- hero: Voidcaster ---------- */
  const HP = { k: '#0d0618', d: '#2a1550', p: '#4a2a8c', m: '#7447c8', l: '#a98bff', w: '#e6dcff', v: '#150a26', e: '#ff5fd2', c: '#5ff3ff' };
  const HW = 32, HH = 32;
  function buildHero(pose) {
    const g = Array.from({ length: HH }, () => Array(HW).fill(''));
    const R = (x, y, w, h, c) => { for (let j = 0; j < h; j++) for (let i = 0; i < w; i++) if (g[y + j] && g[y + j][x + i] !== undefined) g[y + j][x + i] = c; };
    // hood (back) + crest
    R(6, 4, 4, 10, 'd'); R(5, 6, 2, 6, 'd'); R(7, 3, 4, 1, 'm'); R(4, 4, 3, 1, 'm'); R(3, 5, 2, 1, 'd');
    // helmet
    R(10, 2, 7, 1, 'p'); R(9, 3, 9, 1, 'p'); R(8, 4, 11, 8, 'p'); R(9, 12, 9, 1, 'm');
    R(10, 3, 4, 1, 'l'); R(9, 4, 2, 3, 'l'); R(17, 6, 1, 6, 'm'); R(18, 5, 1, 6, 'd');
    R(10, 5, 9, 1, 'd'); R(11, 6, 8, 4, 'v'); R(13, 7, 2, 2, 'e'); R(16, 7, 2, 2, 'e');
    R(12, 11, 6, 1, 'd'); R(11, 13, 5, 1, 'd');
    // torso, belt, shoulders
    R(8, 14, 11, 8, 'p'); R(10, 15, 7, 4, 'm'); R(10, 15, 7, 1, 'l'); R(13, 16, 2, 2, 'c'); R(8, 21, 11, 1, 'd'); R(13, 21, 2, 1, 'c');
    R(6, 14, 3, 3, 'm'); R(6, 14, 3, 1, 'l'); R(19, 14, 3, 3, 'm'); R(19, 14, 3, 1, 'l');
    // back arm
    R(6, 17, 3, 5, 'p'); R(6, 22, 3, 2, 'd');
    // front arm: gauntlet
    if (pose === 'cast') { R(21, 15, 5, 3, 'p'); R(25, 13, 5, 7, 'm'); R(25, 13, 5, 1, 'l'); R(29, 15, 2, 3, 'c'); }
    else { R(19, 17, 3, 5, 'p'); R(19, 22, 4, 3, 'm'); R(21, 23, 1, 1, 'c'); }
    // legs, boots, jets
    R(10, 22, 4, 6, 'p'); R(15, 22, 4, 6, 'p'); R(10, 24, 4, 1, 'm'); R(15, 24, 4, 1, 'm');
    R(9, 28, 6, 2, 'd'); R(15, 28, 7, 2, 'd'); R(9, 30, 6, 1, 'c'); R(15, 30, 6, 1, 'c');
    // outline
    const o = g.map((r) => r.slice());
    for (let y = 0; y < HH; y++) for (let x = 0; x < HW; x++) if (!g[y][x]) {
      if ((g[y - 1] && g[y - 1][x]) || (g[y + 1] && g[y + 1][x]) || g[y][x - 1] || g[y][x + 1]) o[y][x] = 'k';
    }
    const c = document.createElement('canvas'); c.width = HW; c.height = HH; const x = c.getContext('2d');
    for (let j = 0; j < HH; j++) for (let i = 0; i < HW; i++) if (o[j][i]) { x.fillStyle = HP[o[j][i]]; x.fillRect(i, j, 1, 1); }
    return c;
  }
  const heroCache = {};
  function hero(pose) { return heroCache[pose] || (heroCache[pose] = buildHero(pose)); }
  // draw hero with feet-centre at (x,y) in buffer px; face = 1 right, -1 left
  function drawHero(c, x, y, face, pose, t, vx = 0) {
    const sp = hero(pose);
    const bob = Math.round(Math.sin(t * 5) * 1);
    x = Math.round(x); y = Math.round(y + bob);
    // scarf
    c.save(); c.translate(x, y);
    for (let i = 0; i < 7; i++) {
      const wob = Math.round(Math.sin(t * 9 - i * 0.9) * 1.5 + 0);
      const sx = -face * (i * 2 + 3) - Math.max(-6, Math.min(6, vx * 0.01)) * i * 0.3 * face * -1 * 0;
      c.fillStyle = i % 2 ? '#ff3d4a' : '#b01c2e';
      c.fillRect(Math.round(sx - 1 - (face > 0 ? 2 : -2)), -18 + wob + Math.floor(i / 2), 3, 3);
    }
    c.restore();
    // jet flame
    c.fillStyle = 'rgba(95,243,255,.9)'; const fl = 2 + Math.floor((t * 30) % 3);
    c.fillRect(x - face * 3 - 3, y + 1, 3, fl); c.fillRect(x + face * 3, y + 1, 3, fl);
    c.fillStyle = 'rgba(230,220,255,.9)'; c.fillRect(x - face * 3 - 2, y + 1, 1, 1); c.fillRect(x + face * 3 + 1, y + 1, 1, 1);
    c.save(); c.translate(x, y - HH + 1);
    if (face < 0) { c.scale(-1, 1); c.drawImage(sp, -HW / 2 - 2, 0); } else c.drawImage(sp, -HW / 2 + 2, 0);
    c.restore();
  }

  /* ---------- bodies (meteors, asteroids, moons, planets) ---------- */
  const RAMPS = {
    met: ['#1e1210', '#4a2a1c', '#8a4a24', '#e08a3c'],
    ast: ['#1c1a20', '#3c3944', '#6a6575', '#a39dae'],
    moon: ['#2a3350', '#4c5a86', '#8a9cc8', '#d8e4ff'],
    p0: ['#10243a', '#1f4f7a', '#3c8cb0', '#9ae0e0'],
    p1: ['#2a1020', '#6a2a3a', '#b0583c', '#f0b070'],
    p2: ['#1c2a18', '#3a6a2c', '#78a83c', '#d8e890'],
    boss: ['#2a2230', '#5a4a58', '#a89a98', '#ece2d0'],
  };
  const sprCache = {};
  function bodySprite(kind, rBuf, seed) {
    const key = kind + rBuf + '_' + (seed % 6);
    if (sprCache[key]) return sprCache[key];
    const rd = rng(seed * 977 + rBuf);
    const ramp = (kind === 'pla' ? RAMPS['p' + (seed % 3)] : RAMPS[kind] || RAMPS.ast).map(hex);
    const n = rBuf * 2 + 5, mid = (n - 1) / 2;
    const c = document.createElement('canvas'); c.width = c.height = n; const x = c.getContext('2d'); const img = x.createImageData(n, n);
    const lump = kind === 'ast' || kind === 'met';
    const ph = [rd() * 6, rd() * 6, rd() * 6];
    const craters = []; const nc = kind === 'pla' ? 0 : Math.max(1, Math.floor(rBuf / 3));
    for (let i = 0; i < nc; i++) { const a = rd() * 6.28, d = rd() * rBuf * 0.6; craters.push([Math.cos(a) * d, Math.sin(a) * d, Math.max(1, rBuf * (0.12 + rd() * 0.14))]); }
    const L = [-0.55, -0.6, 0.58]; const ln = Math.hypot(...L); L[0] /= ln; L[1] /= ln; L[2] /= ln;
    const inside = (dx, dy) => { const a = Math.atan2(dy, dx); const rr = rBuf * (lump ? 1 + 0.13 * Math.sin(a * 3 + ph[0]) + 0.07 * Math.sin(a * 5 + ph[1]) : 1); return Math.hypot(dx, dy) / (rr + 0.5); };
    const mask = [];
    for (let j = 0; j < n; j++) { mask[j] = []; for (let i = 0; i < n; i++) mask[j][i] = inside(i - mid, j - mid) <= 1; }
    for (let j = 0; j < n; j++) for (let i = 0; i < n; i++) {
      if (!mask[j][i]) continue;
      const dx = i - mid, dy = j - mid; const d = Math.min(1, inside(dx, dy)); const z = Math.sqrt(Math.max(0, 1 - d * d));
      let lum = Math.max(0, (dx / rBuf) * L[0] + (dy / rBuf) * L[1] + z * L[2]) + (((i + j) & 1) ? 0.06 : -0.02);
      if (kind === 'pla') lum += 0.1 * Math.sin(dy * 0.9 + seed);
      for (const cr of craters) { const cd = Math.hypot(dx - cr[0], dy - cr[1]); if (cd < cr[2]) lum -= 0.3; else if (cd < cr[2] + 1 && dx < cr[0]) lum += 0.15; }
      const idx = Math.max(0, Math.min(3, Math.floor(lum * 3.6)));
      let col = ramp[idx];
      const edge = !(mask[j - 1] && mask[j - 1][i] && mask[j + 1] && mask[j + 1][i] && mask[j][i - 1] && mask[j][i + 1]);
      if (edge) col = [12, 7, 20];
      const o = (j * n + i) * 4; img.data[o] = col[0]; img.data[o + 1] = col[1]; img.data[o + 2] = col[2]; img.data[o + 3] = 255;
    }
    x.putImageData(img, 0, 0);
    return (sprCache[key] = c);
  }

  /* boss faces: bone mask of the Dearth */
  function drawBoss(c, bx, by, rB, variant, t, hurt, open) {
    const ramp = RAMPS.boss;
    const spr = bodySprite('boss', rB, variant * 3);
    c.drawImage(spr, Math.round(bx - spr.width / 2), Math.round(by - spr.height / 2));
    const s = rB / 40;
    const eye = (ex) => { c.fillStyle = '#0a0410'; c.fillRect(Math.round(bx + ex * s - 5 * s), Math.round(by - 8 * s), Math.round(10 * s), Math.round(12 * s));
      c.fillStyle = '#ff3d7a'; c.fillRect(Math.round(bx + ex * s - 1), Math.round(by - 4 * s + Math.sin(t * 3 + ex) * 2), 3, 3); };
    eye(-14); eye(14);
    c.fillStyle = '#0a0410'; c.fillRect(Math.round(bx - 3 * s), Math.round(by + 2 * s), Math.round(6 * s), Math.round(8 * s));
    // jaw
    const jaw = open ? 10 * s : 3 * s;
    c.fillStyle = '#0a0410'; c.fillRect(Math.round(bx - 16 * s), Math.round(by + 16 * s), Math.round(32 * s), Math.round(jaw));
    c.fillStyle = ramp[3]; for (let i = -3; i <= 3; i++) c.fillRect(Math.round(bx + i * 4.5 * s - 1), Math.round(by + 16 * s), 2, 2);
    // crown spikes
    c.fillStyle = ramp[2];
    const spikes = variant + 2;
    for (let i = 0; i < spikes; i++) { const a = -Math.PI / 2 + (i - (spikes - 1) / 2) * 0.35; pxLine(c, bx + Math.cos(a) * rB, by + Math.sin(a) * rB, bx + Math.cos(a) * (rB + 8 * s), by + Math.sin(a) * (rB + 8 * s), ramp[3]); }
    if (hurt > 0) { c.fillStyle = 'rgba(255,255,255,.45)'; pxCircle(c, bx, by, rB, 'rgba(255,255,255,.35)'); }
  }

  /* ---------- the Void itself ---------- */
  function drawVoid(c, x, y, r, label, t, held, sel) {
    pxCircle(c, x, y, r + 2, held ? 'rgba(255,95,210,.45)' : 'rgba(155,95,255,.35)');
    pxCircle(c, x, y, r, '#08030f');
    pxCircle(c, x, y, Math.max(2, r - 3), '#0f0620');
    pxRing(c, x, y, r, held ? '#ff5fd2' : '#a98bff', 1);
    // swirling motes
    for (let i = 0; i < 6; i++) { const a = t * (1 + i * 0.15) + i * 1.05; const d = r * (0.25 + 0.12 * i); c.fillStyle = i % 2 ? '#7447c8' : '#5ff3ff'; c.fillRect(Math.round(x + Math.cos(a) * d), Math.round(y + Math.sin(a) * d * 0.9), 1, 1); }
    VCFont.draw(c, label, x, y - 3, sel ? '#fff' : '#a98bff', 1, 'c');
  }

  /* ---------- hazards: lance ---------- */
  function drawLance(c, x, y, vx, vy, t) {
    const l = Math.hypot(vx, vy) || 1; const ux = vx / l, uy = vy / l;
    for (let i = 1; i < 7; i++) { c.fillStyle = `rgba(255,61,122,${0.5 - i * 0.07})`; c.fillRect(Math.round(x - ux * i * 2), Math.round(y - uy * i * 2), 2, 2); }
    pxLine(c, x - ux * 5, y - uy * 5, x + ux * 4, y + uy * 4, '#e9dcd0');
    pxLine(c, x - ux * 5 + uy, y - uy * 5 - ux, x + ux * 2 + uy, y + uy * 2 - ux, '#5a4a58');
    c.fillStyle = '#ff3d7a'; c.fillRect(Math.round(x + ux * 4), Math.round(y + uy * 4), 2, 2);
  }

  /* ---------- missions ---------- */
  function drawStation(c, x, y, t, f) {
    x = Math.round(x); y = Math.round(y);
    const pan = (px) => { c.fillStyle = '#20378a'; c.fillRect(px, y - 4, 28, 9); c.fillStyle = '#5a7aff'; for (let i = 0; i < 28; i += 7) c.fillRect(px + i, y - 4, 1, 9); c.fillRect(px, y, 28, 1); c.fillStyle = '#0d0618'; c.fillRect(px, y - 5, 28, 1); c.fillRect(px, y + 5, 28, 1); };
    pan(x - 46); pan(x + 18);
    c.fillStyle = '#8a8fb0'; c.fillRect(x - 18, y - 1, 36, 3);
    pxCircle(c, x, y, 13, '#0d0618'); pxCircle(c, x, y, 12, '#8a8fb0'); pxCircle(c, x - 2, y - 2, 8, '#b8bdd8');
    pxRing(c, x, y, 13, '#4a4f6a', 1);
    c.fillStyle = '#ffdc70'; for (let i = -2; i <= 2; i++) c.fillRect(x + i * 4, y + 3, 2, 2);
    c.fillStyle = '#0d0618'; c.fillRect(x - 1, y - 21, 3, 8); c.fillStyle = (Math.floor(t * 2) % 2) ? '#ff5050' : '#50ff90'; c.fillRect(x - 1, y - 22, 3, 2);
    if (f < 0.6) { c.fillStyle = 'rgba(255,140,60,.8)'; c.fillRect(x + 6, y - 8 - ((t * 20) % 6), 2, 2); }
    if (f < 0.3) { c.fillStyle = 'rgba(20,20,20,.7)'; c.fillRect(x - 14, y - 6, 6, 5); }
  }
  function drawShip(c, x, y, t, f, flip) {
    x = Math.round(x); y = Math.round(y);
    c.fillStyle = '#0d0618'; c.fillRect(x - 12, y - 4, 25, 9);
    c.fillStyle = '#c9b79a'; c.fillRect(x - 11, y - 3, 22, 7); c.fillStyle = '#8a7a64'; c.fillRect(x - 11, y + 2, 22, 2);
    c.fillStyle = '#5ff3ff'; c.fillRect(x + 6, y - 2, 4, 2);
    c.fillStyle = '#e8e0f8'; c.fillRect(x - 3, y - 12, 1, 9); c.fillStyle = '#b7a6ff'; c.fillRect(x - 2, y - 12, 7, 7); c.fillRect(x - 2, y - 5, 4, 2);
    c.fillStyle = 'rgba(255,200,90,.9)'; c.fillRect(x - 17 - ((t * 25) % 3), y - 1, 5, 3);
  }
  function drawArk(c, x, y, t, f) {
    x = Math.round(x); y = Math.round(y);
    c.fillStyle = '#0d0618'; c.fillRect(x - 40, y - 12, 82, 25); c.fillStyle = '#b8a888'; c.fillRect(x - 38, y - 10, 78, 21);
    c.fillStyle = '#8a7a64'; c.fillRect(x - 38, y + 4, 78, 7); c.fillStyle = '#dcd0b0'; c.fillRect(x - 38, y - 10, 78, 2);
    pxCircle(c, x + 32, y - 2, 14, '#0d0618'); pxCircle(c, x + 32, y - 2, 12, '#9ad8ff'); pxCircle(c, x + 29, y - 5, 6, '#e0f4ff');
    c.fillStyle = '#ffdc70'; for (let i = -34; i < 16; i += 6) c.fillRect(x + i, y - 4, 3, 3);
    c.fillStyle = `rgba(255,170,80,.9)`; c.fillRect(x - 50 - ((t * 25) % 4), y - 6, 11, 4); c.fillRect(x - 50 - ((t * 25) % 4), y + 2, 11, 4);
    if (f < 0.5) { c.fillStyle = 'rgba(255,140,60,.8)'; c.fillRect(x - 10, y - 14 - ((t * 16) % 6), 2, 2); }
  }
  const CRIT = [['#ff8fc8', '#ffd0e8'], ['#8affc8', '#d0ffe8'], ['#ffe27a', '#fff4c0'], ['#b9a0ff', '#e4d8ff']];
  function drawCritter(c, x, y, t, k, scared) {
    x = Math.round(x); y = Math.round(y + Math.sin(t * 3 + k) * 1.5);
    const col = CRIT[k % 4];
    c.fillStyle = '#0d0618'; c.fillRect(x - 6, y - 5, 13, 11);
    pxCircle(c, x, y, 5, '#0d0618'); pxCircle(c, x, y, 4, col[0]); c.fillStyle = col[1]; c.fillRect(x - 2, y - 3, 3, 1);
    c.fillStyle = '#fff'; c.fillRect(x - 3, y - 1, 2, 2); c.fillRect(x + 1, y - 1, 2, 2);
    c.fillStyle = '#0d0618'; c.fillRect(x - 2 + (scared ? 0 : 1), y, 1, 1); c.fillRect(x + 2 - (scared ? 0 : 0), y, 1, 1);
    c.fillStyle = col[0]; c.fillRect(x - 3, y - 7, 1, 2); c.fillRect(x + 3, y - 7, 1, 2); c.fillStyle = '#fff'; c.fillRect(x - 3, y - 8, 1, 1); c.fillRect(x + 3, y - 8, 1, 1);
    c.fillStyle = col[0]; c.fillRect(x - 3, y + 4, 2, 1); c.fillRect(x + 1, y + 4, 2, 1);
  }
  function drawReef(c, x, y, t) {
    x = Math.round(x); y = Math.round(y);
    pxCircle(c, x, y, 22, '#0d0618'); pxCircle(c, x, y, 21, '#3a4a58'); pxCircle(c, x - 3, y - 4, 15, '#5a6e7a');
    const cols = ['#ff7aa8', '#5ff3c0', '#ffd870', '#b08cff'];
    for (let i = 0; i < 9; i++) { const a = -Math.PI + i * 0.4; const d = 20; const px = x + Math.cos(a) * d, py = y + Math.sin(a) * d * 0.9 - 2; c.fillStyle = cols[i % 4]; c.fillRect(Math.round(px), Math.round(py), 3, 4 + (i % 3)); c.fillStyle = '#fff'; c.fillRect(Math.round(px), Math.round(py - 1), 1, 1); }
    for (let i = 0; i < 5; i++) { c.fillStyle = (Math.floor(t * 2 + i) % 2) ? '#fff6a0' : '#5ff3ff'; c.fillRect(x - 14 + i * 7, y + 4 + (i % 2) * 5, 2, 2); }
  }
  function drawCity(c, M, t) {
    const gx = 320, gy = 725 * 0.4 + 0; // planet centre in buffer px
    const cy = 1450 * 0.4, R = 700 * 0.4;
    pxCircle(c, gx, cy, R + 3, '#3a5a8a'); pxCircle(c, gx, cy, R + 1, '#1b2e4a'); pxCircle(c, gx, cy, R, '#14243a');
    c.fillStyle = '#2a6a58'; for (let i = 0; i < 60; i++) { const a = -Math.PI / 2 + (i - 30) * 0.012; c.fillRect(Math.round(gx + Math.cos(a) * (R - 3)), Math.round(cy + Math.sin(a) * (R - 3)), 2, 1); }
    M.parts.forEach((d, i) => {
      const x = Math.round(d.x * 0.4), y = Math.round(d.y * 0.4 + 3);
      if (!d.alive) { c.fillStyle = '#2a2230'; c.fillRect(x - 6, y - 2, 12, 3); c.fillStyle = '#5a4a58'; c.fillRect(x - 3, y - 4, 4, 2); if (Math.floor(t * 3 + i) % 4 === 0) { c.fillStyle = 'rgba(255,140,60,.8)'; c.fillRect(x, y - 5 - ((t * 10) % 6), 2, 2); } return; }
      const h = 8 + (i % 3) * 3;
      c.fillStyle = '#0d0618'; c.fillRect(x - 7, y - h - 1, 15, h + 2);
      c.fillStyle = i % 2 ? '#8ab0d8' : '#c8d8f0'; c.fillRect(x - 6, y - h, 13, h);
      pxCircle(c, x, y - h, 6, '#0d0618'); pxCircle(c, x, y - h, 5, '#9ae0ff'); pxCircle(c, x - 1, y - h - 1, 2, '#e8fbff');
      c.fillStyle = '#ffdc70'; for (let k = 0; k < 3; k++) c.fillRect(x - 4 + k * 3, y - h + 5 + (k % 2) * 3, 2, 2);
      if (d.hp < d.max * 0.5) { c.fillStyle = '#2a2230'; c.fillRect(x - 5, y - h + 1, 4, 3); }
    });
  }

  return { rng, pxCircle, pxRing, pxLine, drawHero, bodySprite, drawBoss, drawVoid, drawLance, drawStation, drawShip, drawArk, drawCritter, drawReef, drawCity, hero };
})();
