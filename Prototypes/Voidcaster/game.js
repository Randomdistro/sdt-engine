/* VOIDCASTER · game logic.
   Rules come from the A/B/C convergence toy: influx lines are cut by occluders, and bodies are driven into
   the deficit by F = k r1^2 r2^2 / d^2 with mass r^3. Voidcaster's voids are crescents that turn to present
   the relevant cross-section to the body they act on.
   Author: James Christopher Tyndall, Melbourne. */
'use strict';
(() => {
  const { WORLDS, LEVELS, HZ, BUDGET } = VCLevels;
  const A = VCArt, F = VCFont;
  const W = 1600, H = 900, BW = 640, BH = 360, S = BW / W, GP = 16800;
  const cv = document.getElementById('c'), cx = cv.getContext('2d');
  const buf = document.createElement('canvas'); buf.width = BW; buf.height = BH;
  const b = buf.getContext('2d');
  const view = { x: 0, y: 0, k: 1 };
  const clamp = (v, lo, hi) => Math.max(lo, Math.min(hi, v));
  const mass = (r) => Math.pow(r / 18, 3);
  const angDiff = (a, c) => { let d = (c - a) % (Math.PI * 2); if (d > Math.PI) d -= Math.PI * 2; if (d < -Math.PI) d += Math.PI * 2; return d; };

  /* ---------- save ---------- */
  let save = { stars: Array(30).fill(0) };
  try { const s = JSON.parse(localStorage.getItem('voidcaster.save') || 'null'); if (s && s.stars) save = s; } catch (e) { /* storage unavailable */ }
  const persist = () => { try { localStorage.setItem('voidcaster.save', JSON.stringify(save)); } catch (e) { /* ignore */ } };
  const unlockedUpTo = () => { let n = 0; while (n < 29 && save.stars[n] > 0) n++; return n; };

  /* ---------- state ---------- */
  let scene = 'title', sel = 0, cur = 0, R = null, now = 0, last = 0, tScene = 0;
  const mouse = { x: 800, y: 450, down: false };
  const keys = {};
  function resize() {
    const dpr = window.devicePixelRatio || 1;
    cv.width = Math.max(1, Math.round(innerWidth * dpr)); cv.height = Math.max(1, Math.round(innerHeight * dpr));
    view.k = Math.min(cv.width / BW, cv.height / BH);
    view.x = Math.round((cv.width - BW * view.k) / 2); view.y = Math.round((cv.height - BH * view.k) / 2);
  }
  addEventListener('resize', resize); resize();
  function toWorld(e) {
    const dpr = window.devicePixelRatio || 1;
    const bx = (e.clientX * dpr - view.x) / view.k, by = (e.clientY * dpr - view.y) / view.k;
    return { x: clamp(bx / S, 0, W), y: clamp(by / S, 0, H) };
  }

  /* ---------- influx lines ---------- */
  const LINES = [];
  for (let ang = 0; ang < 180; ang += 9) {
    const th = ang * Math.PI / 180, ux = Math.cos(th), uy = Math.sin(th), nx = -uy, ny = ux;
    for (let off = -990 + ((ang * 29) % 110); off <= 990; off += 110) LINES.push({ x: 800 + nx * off, y: 450 + ny * off, ux, uy, key: ang + off });
  }
  const segAmb = [], segEdgeT = [], segEdgeV = [], segPulse = [];
  function crescentCut(v) { return { x: v.x - Math.cos(v.ang) * v.r * 0.5, y: v.y - Math.sin(v.ang) * v.r * 0.5, r: v.r * 0.82 }; }
  function interval(L, c) {
    const dx = c.x - L.x, dy = c.y - L.y, along = dx * L.ux + dy * L.uy, perp = -dx * L.uy + dy * L.ux;
    if (Math.abs(perp) >= c.r) return null;
    const ch = Math.sqrt(c.r * c.r - perp * perp); return [along - ch, along + ch];
  }
  function drawInflux(occ, t, col) {
    segAmb.length = segEdgeT.length = segEdgeV.length = segPulse.length = 0;
    const EXT = 1200;
    for (const L of LINES) {
      const iv = [];
      for (const o of occ) {
        const a = interval(L, o); if (!a) continue;
        if (o.cut) {
          const c = interval(L, o.cut);
          if (c) { if (c[0] > a[0]) iv.push([a[0], c[0], o.v]); if (c[1] < a[1]) iv.push([c[1], a[1], o.v]); continue; }
        }
        iv.push([a[0], a[1], o.v]);
      }
      if (!iv.length) { segAmb.push(L.x - L.ux * EXT, L.y - L.uy * EXT, L.x + L.ux * EXT, L.y + L.uy * EXT); continue; }
      iv.sort((p, q) => p[0] - q[0]);
      const m = []; for (const i of iv) { const l = m[m.length - 1]; if (l && i[0] <= l[1]) { if (i[1] > l[1]) { l[1] = i[1]; l[3] = i[2]; } } else m.push([i[0], i[1], i[2], i[2]]); }
      let s = -EXT;
      m.forEach((g, gi) => {
        if (g[0] > s) {
          segAmb.push(L.x + L.ux * s, L.y + L.uy * s, L.x + L.ux * g[0], L.y + L.uy * g[0]);
          const e = (g[2] ? segEdgeV : segEdgeT); e.push(L.x + L.ux * (g[0] - 14), L.y + L.uy * (g[0] - 14), L.x + L.ux * g[0], L.y + L.uy * g[0]);
          if (gi === 0) { const p = g[0] - 420 + ((t * 150 + L.key * 53) % 420); if (p > s + 12 && p < g[0] - 24) segPulse.push(L.x + L.ux * (p - 10), L.y + L.uy * (p - 10), L.x + L.ux * (p + 10), L.y + L.uy * (p + 10)); }
        }
        s = g[1];
        const e = (g[3] ? segEdgeV : segEdgeT); e.push(L.x + L.ux * g[1], L.y + L.uy * g[1], L.x + L.ux * (g[1] + 14), L.y + L.uy * (g[1] + 14));
      });
      if (s < EXT) segAmb.push(L.x + L.ux * s, L.y + L.uy * s, L.x + L.ux * EXT, L.y + L.uy * EXT);
    }
    b.save(); b.scale(S, S); b.lineWidth = 2.5;
    const pass = (arr, style, alpha) => { b.strokeStyle = style; b.globalAlpha = alpha; b.beginPath(); for (let i = 0; i < arr.length; i += 4) { b.moveTo(arr[i], arr[i + 1]); b.lineTo(arr[i + 2], arr[i + 3]); } b.stroke(); };
    pass(segAmb, col, 0.10); pass(segEdgeT, col, 0.5); pass(segEdgeV, '#c89bff', 0.65); pass(segPulse, '#ffffff', 0.5);
    b.restore(); b.globalAlpha = 1;
  }
  function pxCrescent(c, v, col, rim) {
    const x = Math.round(v.x * S), y = Math.round(v.y * S), r = Math.max(2, Math.round(v.r * S));
    const k = crescentCut({ x: v.x * S, y: v.y * S, r, ang: v.ang }); const kr = k.r;
    for (let dy = -r; dy <= r; dy++) {
      const w = Math.floor(Math.sqrt(r * r - dy * dy + r * 0.5));
      const ky = y + dy - k.y; let cw = -1; if (Math.abs(ky) <= kr) cw = Math.floor(Math.sqrt(kr * kr - ky * ky));
      c.fillStyle = col;
      if (cw < 0) c.fillRect(x - w, y + dy, w * 2 + 1, 1);
      else { const c0 = Math.round(k.x - cw), c1 = Math.round(k.x + cw); if (c0 > x - w) c.fillRect(x - w, y + dy, Math.min(c0, x + w + 1) - (x - w), 1); if (c1 < x + w) c.fillRect(Math.max(c1 + 1, x - w), y + dy, x + w - Math.max(c1 + 1, x - w) + 1, 1); }
    }
    if (rim) { c.fillStyle = rim; const tip = (s) => { const a = v.ang + s * (Math.PI / 2 + 0.55); c.fillRect(Math.round(x + Math.cos(a) * r), Math.round(y + Math.sin(a) * r), 1, 1); }; tip(1); tip(-1); const ax = Math.round(x + Math.cos(v.ang) * r), ay = Math.round(y + Math.sin(v.ang) * r); c.fillRect(ax, ay, 1, 1); }
  }

  /* ---------- missions ---------- */
  function makeMission(L) {
    const M = { type: L.m, parts: [], t: 0, ground: null, reef: null };
    const part = (x, y, r, hp, pullR) => ({ x, y, r, hp, max: hp, pullR, alive: true, flash: 0, vx: 0, vy: 0 });
    if (L.m === 'station') M.parts.push(part(800, 600, 46, 100, 64));
    if (L.m === 'ark') { const a = part(260, 600, 66, 160, 70); a.vx = (1340 - 260) / (L.dur + 15); M.parts.push(a); }
    if (L.m === 'convoy') for (let i = 0; i < L.count; i++) { const s = part(130 + (i % 2) * 30 - i * 15, 540 + i * 36, 22, 36, 28); s.vx = (1380 - 200) / (L.dur + 12); s.k = i; M.parts.push(s); }
    if (L.m === 'critters') {
      M.reef = part(800, 640, 56, 1e9, 56); M.parts.push(M.reef); M.reef.isReef = true;
      for (let i = 0; i < L.count; i++) { const p = part(800, 600, 14, 1, 0); p.a = i * 6.283 / L.count; p.rx = 170 + (i % 3) * 110; p.ry = 70 + (i % 2) * 50; p.sp = (i % 2 ? 1 : -1) * (0.12 + 0.03 * (i % 4)); p.k = i; M.parts.push(p); }
    }
    if (L.m === 'city') { M.ground = { x: 800, y: 1450, r: 700 }; for (let i = 0; i < 7; i++) { const x = 560 + i * 80, y = 1450 - Math.sqrt(700 * 700 - (x - 800) ** 2); const d = part(x, y, 26, 16, 0); d.dome = true; M.parts.push(d); } M.pullPt = part(800, 840, 10, 1, 72); }
    return M;
  }
  const mVuln = (M) => M.parts.filter((p) => p.alive && !p.isReef);
  function missionFrac(M) {
    if (M.type === 'critters') { const p = M.parts.filter((q) => !q.isReef); return p.filter((q) => q.alive).length / p.length; }
    const p = M.parts.filter((q) => !q.isReef); return p.reduce((s, q) => s + Math.max(0, q.hp), 0) / p.reduce((s, q) => s + q.max, 0);
  }
  function missionDead(M) {
    if (M.type === 'critters' || M.type === 'convoy') return mVuln(M).length === 0;
    if (M.type === 'city') return missionFrac(M) <= 0.001; return !M.parts[0].alive;
  }
  function missionUpdate(M, dt) {
    M.t += dt;
    for (const p of M.parts) {
      if (p.isReef) continue;
      if (M.type === 'critters') { if (!p.alive) continue; p.a += p.sp * dt; p.x = 800 + Math.cos(p.a) * p.rx; p.y = 600 + Math.sin(p.a) * p.ry * 0.7 - 40; }
      else { p.x += p.vx * dt; p.y += (M.type === 'convoy' ? Math.sin(M.t * 0.6 + (p.k || 0)) * 8 * dt : 0); }
      p.flash = Math.max(0, p.flash - dt);
    }
  }
  function pullSources(M) {
    const out = [];
    if (M.type === 'city') out.push(M.pullPt);
    else for (const p of M.parts) if ((p.alive || p.isReef) && p.pullR) out.push(p);
    return out;
  }
  function pickAim(M, rnd) {
    if (M.type === 'city') { const d = M.parts.filter((p) => p.alive); const p = d.length ? d[Math.floor(rnd() * d.length)] : M.pullPt; return { x: p.x, y: p.y }; }
    const v = mVuln(M); const p = v.length ? v[Math.floor(rnd() * v.length)] : M.parts[0];
    return { x: p.x + p.vx * 4, y: p.y };
  }

  /* ---------- run ---------- */
  function newRun(i) {
    const L = LEVELS[i];
    const r = {
      i, L, t: 0, hz: [], bolts: [], fx: [], pk: [], score: 0, shake: 0, ev: VCLevels.buildWaves(L), evi: 0, warned: new Set(), cdRel: 0, relFx: 0,
      rnd: A.rng(99 + i), held: null, selV: 0, firing: false, fireT: 0, over: 0, result: null, absorbed: 0, diverted: 0, boss: null, budget: BUDGET(i), tail: 0,
      hero: { x: 800, y: 340, vx: 0, vy: 0, hp: 5, inv: 0, face: 1, cast: 0, hurt: 0 },
      mission: makeMission(L),
      voids: [
        { id: 'A', x: 800, y: 430, vx: 0, vy: 0, r: 58, ang: -Math.PI / 2, on: true, isVoid: true },
        { id: 'B', x: 560, y: 480, vx: 0, vy: 0, r: 42, ang: -Math.PI / 2, on: L.unlock >= 2, isVoid: true },
        { id: 'C', x: 1040, y: 480, vx: 0, vy: 0, r: 34, ang: -Math.PI / 2, on: L.unlock >= 3, isVoid: true },
      ],
    };
    if (L.boss) { const v = L.boss; r.boss = { x: 800, y: 170, r: [0, 70, 80, 95][v], hp: [0, 30, 45, 90][v], max: [0, 30, 45, 90][v], variant: v, t: 0, a1: 2.5, a2: 5, a3: 7, hurt: 0, open: 0, shield: v === 2, pullR: 70, dead: false }; }
    return r;
  }
  const bodyBudget = () => R.voids.filter((v) => v.on).reduce((s, v) => s + v.r * v.r, 0);
  function resizeVoid(v, dr) {
    const others = bodyBudget() - v.r * v.r; const maxR = Math.min(125, Math.sqrt(Math.max(0, R.budget - others)));
    v.r = clamp(v.r + dr, 18, Math.max(18, maxR));
  }

  function spawnHaz(kind, x, y, aim, seed, extra = {}) {
    const d = HZ[kind], rd = A.rng(seed);
    const r = d.r[0] + (d.r[1] - d.r[0]) * rd();
    const spd = (d.spd[0] + (d.spd[1] - d.spd[0]) * rd()) * (1 + R.i * 0.012);
    const dx = aim.x - x, dy = aim.y - y, l = Math.hypot(dx, dy) || 1; const spread = (rd() - 0.5) * 0.22;
    const c = Math.cos(spread), s = Math.sin(spread);
    const ux = (dx / l) * c - (dy / l) * s, uy = (dx / l) * s + (dy / l) * c;
    const h = { kind, x, y, vx: ux * spd, vy: uy * spd, r, m: mass(r), hp: d.hp, age: 0, seed, ang: 0, spin: (rd() - 0.5) * 2, contact: 0, cv: null, hitT: 0, ...extra };
    h.spr = kind === 'wpn' ? null : A.bodySprite(kind, Math.max(2, Math.round(r * S)), seed);
    R.hz.push(h); return h;
  }
  function spawnPos(ev, kind) {
    const r = HZ[kind].r[1] + 40;
    if (ev.side === 'top') return { x: ev.sx, y: -r };
    if (ev.side === 'left') return { x: -r, y: ev.sy }; return { x: W + r, y: ev.sy };
  }
  function boom(x, y, n, cols, sp = 160) {
    for (let i = 0; i < n; i++) { const a = Math.random() * 6.28, s = sp * (0.3 + Math.random()); R.fx.push({ t: 'p', x, y, vx: Math.cos(a) * s, vy: Math.sin(a) * s, life: 0.5 + Math.random() * 0.5, max: 1, col: cols[i % cols.length] }); }
    R.fx.push({ t: 'ring', x, y, r: 6, life: 0.35, max: 0.35, col: cols[0] });
  }
  const pop = (x, y, txt, col = '#fff') => R.fx.push({ t: 'txt', x, y, txt, life: 0.9, max: 0.9, col });
  function dmgMission(p, amount, x, y) {
    p.hp -= amount; p.flash = 0.25; R.shake = Math.min(14, R.shake + 3 + amount * 0.25);
    if (R.mission.type === 'critters') p.hp = 0;
    if (p.hp <= 0 && p.alive) { p.alive = false; boom(p.x, p.y, 24, ['#ffcf70', '#ff7a3c', '#fff'], 220); VCAudio.play('boom'); pop(p.x, p.y - 20, R.mission.type === 'critters' ? 'LOST' : 'DOWN', '#ff7a8a'); }
  }
  function hazHitMission(h) {
    const M = R.mission, dmg = HZ[h.kind].dmg * (h.kind === 'moon' || h.kind === 'pla' ? h.r / HZ[h.kind].r[0] : 1);
    if (M.ground) {
      const d = Math.hypot(h.x - M.ground.x, h.y - M.ground.y);
      if (d < M.ground.r + h.r) {
        let any = false;
        for (const p of M.parts) if (p.alive) { const dx = Math.abs(p.x - h.x); const rg = h.kind === 'pla' ? 9999 : h.kind === 'moon' ? 260 : 130; if (dx < rg) { dmgMission(p, dmg * (1 - dx / (rg + 40)) * 1.2, h.x, h.y); any = true; } }
        return true;
      }
      return false;
    }
    for (const p of M.parts) {
      if (!p.alive) continue;
      if (Math.hypot(h.x - p.x, h.y - p.y) < p.r + h.r) {
        if (p.isReef) { for (const q of M.parts) if (q.alive && !q.isReef && Math.hypot(q.x - h.x, q.y - h.y) < (h.kind === 'pla' ? 700 : h.kind === 'moon' ? 260 : 110)) dmgMission(q, 1, h.x, h.y); return true; }
        dmgMission(p, dmg, h.x, h.y); return true;
      }
    }
    return false;
  }
  function killHaz(h, how) {
    h.dead = true; const d = HZ[h.kind];
    boom(h.x, h.y, 6 + Math.round(h.r / 4), h.kind === 'wpn' ? ['#ff3d7a', '#fff'] : ['#ffb04a', '#8a4a24', '#fff'], 120 + h.r);
    if (how === 'shot' || how === 'absorb') { R.score += d.pts; pop(h.x, h.y - h.r, '+' + d.pts, how === 'absorb' ? '#8affc8' : '#fff'); if (how === 'absorb') R.absorbed++; }
    if (how === 'shot' && h.kind === 'ast') for (let i = 0; i < 2; i++) { const m = spawnHaz('met', h.x + (i ? 10 : -10), h.y, { x: h.x + h.vx, y: h.y + h.vy }, h.seed + i, {}); m.vx = h.vx * 0.6 + (i ? 70 : -70); m.vy = h.vy * 0.6 + (i ? -40 : 40); }
    if (h.kind !== 'met' && h.kind !== 'wpn' && Math.random() < 0.3) R.pk.push({ x: h.x, y: h.y, vx: h.vx * 0.2, vy: h.vy * 0.2, t: 0, kind: Math.random() < 0.5 ? 'heart' : 'patch' });
    VCAudio.play('pop');
  }

  /* ---------- physics ---------- */
  function effR(src, tx, ty) {
    if (!src.isVoid) return src.r; const dx = tx - src.x, dy = ty - src.y, l = Math.hypot(dx, dy) || 1;
    const c = Math.abs(Math.cos(src.ang) * dx / l + Math.sin(src.ang) * dy / l); return src.r * Math.sqrt(0.35 + 0.65 * c);
  }
  function bounce(a, c, e, ia, ic) {
    let dx = c.x - a.x, dy = c.y - a.y, d = Math.hypot(dx, dy); const contact = a.r + c.r; if (d >= contact) return false;
    if (d < 0.001) { dx = 1; dy = 0; d = 1; } const ux = dx / d, uy = dy / d, it = ia + ic; if (it === 0) return true;
    const corr = (contact - d) / it; a.x -= ux * corr * ia; a.y -= uy * corr * ia; c.x += ux * corr * ic; c.y += uy * corr * ic;
    const rv = (c.vx - a.vx) * ux + (c.vy - a.vy) * uy;
    if (rv < 0) { const j = -(1 + e) * rv / it; a.vx -= j * ux * ia; a.vy -= j * uy * ia; c.vx += j * ux * ic; c.vy += j * uy * ic; }
    return true;
  }
  function aimThreat() {
    // crescents turn the convex side toward the nearest approaching body
    const M = R.mission, src = pullSources(M)[0] || { x: 800, y: 600 };
    let best = null, bd = 1e9;
    for (const h of R.hz) { if (h.dead) continue; const d = Math.hypot(h.x - src.x, h.y - src.y); const closing = (src.x - h.x) * h.vx + (src.y - h.y) * h.vy; if (closing > 0 && d < bd) { bd = d; best = h; } }
    return best;
  }
  function step(dt) {
    const hero = R.hero, voids = R.voids.filter((v) => v.on), hz = R.hz;
    const anchors = pullSources(R.mission); if (R.boss && !R.boss.dead) anchors.push({ x: R.boss.x, y: R.boss.y, r: 0, pullR: R.boss.pullR });
    const dyn = voids.concat(hz);
    for (const v of voids) { const th = aimThreat(); let want = th ? Math.atan2(th.y - v.y, th.x - v.x) : -Math.PI / 2; v.ang += angDiff(v.ang, want) * Math.min(1, 9 * dt); }
    const acc = dyn.map(() => [0, 0]);
    for (let i = 0; i < dyn.length; i++) {
      const a = dyn[i];
      for (let j = i + 1; j < dyn.length; j++) {
        const c = dyn[j]; if (a.isVoid && c.isVoid) { /* voids share a budget and do not attract each other */ continue; }
        const dx = c.x - a.x, dy = c.y - a.y; const dist = Math.max(Math.hypot(dx, dy), a.r + c.r + 2), d2 = dist * dist, ux = dx / dist, uy = dy / dist;
        const ra = effR(a, c.x, c.y), rc = effR(c, a.x, a.y);
        const fa = GP * rc * rc / (a.r * d2), fc = GP * ra * ra / (c.r * d2);
        acc[i][0] += ux * fa; acc[i][1] += uy * fa; acc[j][0] -= ux * fc; acc[j][1] -= uy * fc;
      }
      if (!a.isVoid) for (const s of anchors) {
        const dx = s.x - a.x, dy = s.y - a.y; const dist = Math.max(Math.hypot(dx, dy), a.r + s.pullR * 0.5 + 2), f = GP * s.pullR * s.pullR / (a.r * dist * dist);
        acc[i][0] += dx / dist * f; acc[i][1] += dy / dist * f;
      }
      if (a.kind === 'wpn' && !a.dead) { const t = pickAim(R.mission, () => 0.5); const dx = t.x - a.x, dy = t.y - a.y, l = Math.hypot(dx, dy) || 1; acc[i][0] += dx / l * 90; acc[i][1] += dy / l * 90; }
    }
    dyn.forEach((a, i) => {
      if (a.isVoid) {
        if (a === R.held) { const nx = a.x + (mouse.x - a.x) * Math.min(1, 20 * dt), ny = a.y + (mouse.y - a.y) * Math.min(1, 20 * dt); a.vx = clamp((nx - a.x) / dt, -1400, 1400); a.vy = clamp((ny - a.y) / dt, -1400, 1400); a.x = nx; a.y = ny; return; }
        a.vx *= Math.exp(-0.9 * dt); a.vy *= Math.exp(-0.9 * dt);
      }
      a.vx += acc[i][0] * dt; a.vy += acc[i][1] * dt;
      const sp = Math.hypot(a.vx, a.vy); if (sp > 760) { a.vx *= 760 / sp; a.vy *= 760 / sp; }
      a.x += a.vx * dt; a.y += a.vy * dt;
      if (a.isVoid) { if (a.x < a.r) { a.x = a.r; a.vx = Math.abs(a.vx) * 0.5; } if (a.x > W - a.r) { a.x = W - a.r; a.vx = -Math.abs(a.vx) * 0.5; } if (a.y < a.r) { a.y = a.r; a.vy = Math.abs(a.vy) * 0.5; } if (a.y > H - a.r) { a.y = H - a.r; a.vy = -Math.abs(a.vy) * 0.5; } }
      else { a.age += dt; a.ang += a.spin * dt; }
    });
    // collisions
    for (let i = 0; i < hz.length; i++) {
      const h = hz[i]; if (h.dead) continue; h.cv = null;
      for (let j = i + 1; j < hz.length; j++) { const o = hz[j]; if (!o.dead) bounce(h, o, 0.85, 1 / h.m, 1 / o.m); }
      for (const v of voids) {
        const touch = bounce(h, v, 0.6, 1 / h.m, v === R.held ? 0 : 1 / mass(v.r));
        if (touch) { h.cv = v; h.contact += dt; } else if (h.cv === v) h.cv = null;
        if (touch && h.contact > 1.4 + h.r / 40 && v.r >= h.r * 0.7 && h.kind !== 'wpn') { killHaz(h, 'absorb'); VCAudio.play('absorb'); break; }
      }
      if (h.dead) continue; if (!h.cv) h.contact = Math.max(0, h.contact - dt * 2);
      for (const v of voids) for (const o of voids) if (v !== o) bounce(v, o, 0.5, v === R.held ? 0 : 1 / mass(v.r), o === R.held ? 0 : 1 / mass(o.r));
      if (hazHitMission(h)) { killHaz(h, 'hit'); R.diverted--; continue; }
      const bo = R.boss;
      if (bo && !bo.dead && h.age > 0.9 && Math.hypot(h.x - bo.x, h.y - bo.y) < bo.r + h.r) {
        const mom = h.m * Math.hypot(h.vx, h.vy) / 300; bo.hp -= Math.max(0.4, mom); bo.hurt = 0.2; R.shake = Math.min(14, R.shake + 4); pop(h.x, h.y, '-' + Math.max(1, Math.round(mom)), '#ff9ad0');
        if (h.kind === 'met' || h.kind === 'wpn' || h.kind === 'ast') killHaz(h, 'boss'); else { const dx = h.x - bo.x, dy = h.y - bo.y, l = Math.hypot(dx, dy) || 1; h.vx = dx / l * 120; h.vy = dy / l * 120; h.x = bo.x + dx / l * (bo.r + h.r + 2); h.y = bo.y + dy / l * (bo.r + h.r + 2); }
      }
      if (hero.inv <= 0 && Math.hypot(h.x - hero.x, h.y - hero.y) < 22 + h.r) {
        hero.hp--; hero.inv = 1.3; hero.hurt = 0.4; VCAudio.play('hurt'); R.shake = 10; const dx = hero.x - h.x, dy = hero.y - h.y, l = Math.hypot(dx, dy) || 1; hero.vx = dx / l * 500; hero.vy = dy / l * 500;
        if (h.kind === 'met' || h.kind === 'wpn') killHaz(h, 'hit');
      }
      if (h.x < -450 || h.x > W + 450 || h.y < -450 || h.y > H + 450) { h.dead = true; if (h.age > 2) { R.diverted++; R.score += Math.round(HZ[h.kind].pts * 0.4); } }
    }
    R.hz = hz.filter((h) => !h.dead);
  }

  /* ---------- hero ---------- */
  function updateHero(dt) {
    const h = R.hero; const ax = (keys.d || keys.arrowright ? 1 : 0) - (keys.a || keys.arrowleft ? 1 : 0), ay = (keys.s || keys.arrowdown ? 1 : 0) - (keys.w || keys.arrowup ? 1 : 0);
    const n = Math.hypot(ax, ay) || 1; h.vx += ax / n * 3200 * dt; h.vy += ay / n * 3200 * dt;
    h.vx *= Math.exp(-6 * dt); h.vy *= Math.exp(-6 * dt);
    const sp = Math.hypot(h.vx, h.vy); if (sp > 560) { h.vx *= 560 / sp; h.vy *= 560 / sp; }
    h.x = clamp(h.x + h.vx * dt, 40, W - 40); h.y = clamp(h.y + h.vy * dt, 90, 760);
    h.inv = Math.max(0, h.inv - dt); h.hurt = Math.max(0, h.hurt - dt); h.cast = Math.max(0, h.cast - dt);
    h.face = (R.held ? R.held.x : mouse.x) >= h.x ? 1 : -1;
    if (R.held) h.cast = 0.1;
    R.fireT -= dt;
    if (R.firing && !R.held && R.fireT <= 0) {
      R.fireT = 0.18; h.cast = 0.15; const gx = h.x + h.face * 62, gy = h.y - 40; let dx = mouse.x - gx, dy = mouse.y - gy; const l = Math.hypot(dx, dy) || 1; dx /= l; dy /= l;
      R.bolts.push({ x: gx, y: gy, vx: dx * 1300, vy: dy * 1300, life: 1.1 }); VCAudio.play('bolt');
    }
    for (const b2 of R.bolts) {
      b2.x += b2.vx * dt; b2.y += b2.vy * dt; b2.life -= dt;
      for (const z of R.hz) if (!z.dead && Math.hypot(z.x - b2.x, z.y - b2.y) < z.r + 6) {
        b2.life = 0; z.hp -= 1; z.vx += b2.vx * 0.05 / z.m; z.vy += b2.vy * 0.05 / z.m; boom(b2.x, b2.y, 3, ['#ff5fd2', '#fff'], 80);
        if (z.hp <= 0) killHaz(z, 'shot'); break;
      }
      const bo = R.boss; if (bo && !bo.dead && b2.life > 0 && Math.hypot(bo.x - b2.x, bo.y - b2.y) < bo.r + 6) {
        b2.life = 0; if (bo.shield) { boom(b2.x, b2.y, 3, ['#5ff3ff'], 60); } else { bo.hp -= 1; bo.hurt = 0.15; boom(b2.x, b2.y, 4, ['#ff5fd2', '#fff'], 90); }
      }
    }
    R.bolts = R.bolts.filter((q) => q.life > 0);
    for (const p of R.pk) { p.t += dt; p.x += p.vx * dt; p.y += p.vy * dt; if (Math.hypot(p.x - h.x, p.y - h.y) < 44) { p.t = 99; VCAudio.play('pick'); if (p.kind === 'heart') h.hp = Math.min(5, h.hp + 1); else { const v = mVuln(R.mission); v.forEach((q) => { if (R.mission.type !== 'critters') q.hp = Math.min(q.max, q.hp + 12); }); } pop(h.x, h.y - 50, p.kind === 'heart' ? '+LIFE' : '+REPAIR', '#8affc8'); } }
    R.pk = R.pk.filter((p) => p.t < 10);
    R.cdRel = Math.max(0, R.cdRel - dt);
  }
  function release() {
    if (R.cdRel > 0) return; R.cdRel = 9; R.relFx = 0.5; VCAudio.play('release'); R.shake = 8;
    for (const v of R.voids) if (v.on) for (const z of R.hz) { const dx = z.x - v.x, dy = z.y - v.y, d = Math.hypot(dx, dy) || 1, reach = v.r * 3.5 + 120; if (d < reach) { const k = (1 - d / reach) * 700 / Math.sqrt(z.m + 1); z.vx += dx / d * k; z.vy += dy / d * k; z.contact = 0; } }
    for (const v of R.voids) R.fx.push({ t: 'ring', x: v.x, y: v.y, r: v.r, life: 0.5, max: 0.5, col: '#c89bff', big: 1 });
  }

  /* ---------- boss ---------- */
  function updateBoss(dt) {
    const bo = R.boss; if (!bo) return; bo.t += dt; bo.hurt = Math.max(0, bo.hurt - dt); bo.open = Math.max(0, bo.open - dt);
    if (bo.dead) return;
    bo.x = 800 + Math.sin(bo.t * 0.35) * (bo.variant === 3 ? 360 : 520); bo.y = 160 + Math.sin(bo.t * 0.8) * 20;
    if (bo.variant === 2) bo.shield = (bo.t % 9) < 5; if (bo.variant === 3) bo.shield = bo.open <= 0;
    const throwAt = (kind, n = 1, gap = 0) => { for (let i = 0; i < n; i++) { const aim = pickAim(R.mission, R.rnd); const dx = aim.x - bo.x, dy = aim.y - bo.y, l = Math.hypot(dx, dy) || 1; const rr = HZ[kind].r[1]; const h = spawnHaz(kind, bo.x + dx / l * (bo.r + rr + 12), bo.y + dy / l * (bo.r + rr + 12), aim, Math.floor(R.rnd() * 1e6), { age: -0.2 - i * gap }); if (kind === 'wpn') { h.age = -0.4; } } VCAudio.play('warn'); };
    bo.a1 -= dt; bo.a2 -= dt; bo.a3 -= dt;
    if (bo.a1 <= 0) { throwAt('wpn', bo.variant === 3 ? 5 : 3, 0.12); bo.a1 = bo.variant === 3 ? 5 : bo.variant === 2 ? 3.8 : 3.2; }
    if (bo.a2 <= 0) { throwAt(bo.variant === 1 ? 'ast' : 'moon'); bo.a2 = bo.variant === 1 ? 5.5 : 7; }
    if (bo.a3 <= 0 && bo.variant === 3) { throwAt('pla'); bo.open = 3; bo.a3 = 14; }
    if (bo.hp <= 0) { bo.dead = true; boom(bo.x, bo.y, 80, ['#ffcf70', '#ff5fd2', '#fff', '#ece2d0'], 360); VCAudio.play('boom'); R.hz.forEach((h) => { h.dead = true; boom(h.x, h.y, 6, ['#fff'], 100); }); R.shake = 18; }
  }

  /* ---------- play update ---------- */
  function finish(win) {
    R.over = 0.01; R.win = win; const frac = missionFrac(R.mission);
    const stars = win ? (frac >= 0.9 && R.hero.hp >= 3 ? 3 : frac >= 0.5 ? 2 : 1) : 0;
    R.stars = stars; if (win) { save.stars[R.i] = Math.max(save.stars[R.i] || 0, stars); persist(); R.score += Math.round(frac * 500) + R.hero.hp * 100; }
    VCAudio.play(win ? 'win' : 'lose'); setTimeout(() => { scene = win ? 'win' : 'lose'; tScene = 0; }, 1400);
  }
  function updatePlay(dt) {
    if (R.over) { R.over += dt; dt *= 0.3; if (R.over > 3) return; }
    R.t += dt;
    // spawns
    while (R.evi < R.ev.length && R.ev[R.evi].t <= R.t) {
      const e = R.ev[R.evi++]; const p = spawnPos(e, e.kind); spawnHaz(e.kind, p.x, p.y, pickAim(R.mission, R.rnd), e.seed); R.tail = R.t;
    }
    for (let i = R.evi; i < R.ev.length && R.ev[i].t - R.t < 1.6; i++) { const e = R.ev[i]; if (!R.warned.has(e)) { R.warned.add(e); VCAudio.play('warn'); } }
    missionUpdate(R.mission, dt); updateBoss(dt); updateHero(dt);
    const n = Math.ceil(dt / (1 / 120)); for (let i = 0; i < n; i++) step(dt / n);
    for (const f of R.fx) { f.life -= dt; if (f.t === 'p') { f.x += f.vx * dt; f.y += f.vy * dt; f.vx *= 0.96; f.vy *= 0.96; } if (f.t === 'ring') f.r += (f.big ? 700 : 260) * dt; if (f.t === 'txt') f.y -= 30 * dt; }
    R.fx = R.fx.filter((f) => f.life > 0); R.shake = Math.max(0, R.shake - dt * 24); R.relFx = Math.max(0, R.relFx - dt);
    if (!R.over) {
      if (missionDead(R.mission) || R.hero.hp <= 0) finish(false);
      else if (R.boss ? R.boss.dead : (R.evi >= R.ev.length && R.hz.length === 0)) finish(true);
      else if (!R.boss && R.evi >= R.ev.length && R.t - R.tail > 28) R.hz.forEach((h) => { h.dead = true; });
    }
  }

  /* ---------- drawing ---------- */
  const stars = Array.from({ length: 90 }, (_, i) => { const r = A.rng(i + 5); return { x: r() * BW, y: r() * BH, c: r(), s: r() }; });
  function drawBg(t, w) {
    const g = b.createLinearGradient(0, 0, 0, BH); g.addColorStop(0, ['#0a1230', '#241606', '#0c2a22', '#10143a', '#2a0c1c', '#1c0a2e'][w % 6]); g.addColorStop(1, '#05030a');
    b.fillStyle = g; b.fillRect(0, 0, BW, BH);
    for (const s of stars) { b.fillStyle = (Math.floor(t * 2 + s.c * 9) % 7 === 0) ? '#fff' : s.s > 0.8 ? '#cfd8ff' : '#6a7090'; b.fillRect(Math.floor(s.x), Math.floor(s.y), 1, 1); }
  }
  function drawBodies() {
    for (const h of R.hz) {
      const x = h.x * S, y = h.y * S;
      if (h.kind === 'wpn') { A.drawLance(b, x, y, h.vx, h.vy, now); continue; }
      const spr = h.spr; b.save(); b.translate(Math.round(x), Math.round(y));
      if (h.kind === 'ast' || h.kind === 'met') b.rotate(Math.floor(h.ang) * Math.PI / 2);
      b.drawImage(spr, -spr.width / 2 | 0, -spr.height / 2 | 0); b.restore();
      if (h.kind === 'met') { b.fillStyle = 'rgba(255,170,70,.55)'; const l = Math.hypot(h.vx, h.vy) || 1; for (let i = 1; i < 5; i++) b.fillRect(Math.round(x - h.vx / l * i * 3), Math.round(y - h.vy / l * i * 3), 2, 2); }
      if (h.kind === 'pla' && h.seed % 3 === 0) { b.fillStyle = '#e8d8a0'; const rr = h.r * S; for (let a = 0; a < 6.28; a += 0.035) { const px = Math.cos(a) * rr * 1.7, py = Math.sin(a) * rr * 0.4; if (Math.sin(a) > 0 || Math.abs(px) > rr) b.fillRect(Math.round(x + px * 0.94 - py * 0.34), Math.round(y + py * 0.94 + px * 0.34), 1, 1); } }
      if (h.contact > 0.2) { const k = Math.min(1, h.contact / (1.4 + h.r / 40)); b.fillStyle = '#8affc8'; b.fillRect(Math.round(x - 6), Math.round(y - h.r * S - 5), Math.round(12 * k), 1); }
    }
  }
  function drawMission() {
    const M = R.mission, t = now, f = missionFrac(M);
    if (M.ground) A.drawCity(b, M, t);
    for (const p of M.parts) {
      const x = p.x * S, y = p.y * S;
      if (p.isReef) { A.drawReef(b, x, y, t); continue; }
      if (M.type === 'critters') { if (p.alive) A.drawCritter(b, x, y, t, p.k, p.flash > 0); continue; }
      if (M.type === 'station') A.drawStation(b, x, y, t, f);
      if (M.type === 'ark') A.drawArk(b, x, y, t, f);
      if (M.type === 'convoy' && p.alive) { A.drawShip(b, x, y, t, p.hp / p.max); if (p.flash > 0) { b.fillStyle = 'rgba(255,255,255,.5)'; b.fillRect(Math.round(x - 12), Math.round(y - 4), 25, 9); } }
      if (M.type === 'station' && p.flash > 0) { A.pxCircle(b, x, y, 13, 'rgba(255,255,255,.4)'); }
    }
  }
  function drawBossSprite() {
    const bo = R.boss; if (!bo || bo.dead) return; A.drawBoss(b, bo.x * S, bo.y * S, Math.round(bo.r * S), bo.variant, now, bo.hurt, bo.open > 0);
    if (bo.shield) { A.pxRing(b, bo.x * S, bo.y * S, bo.r * S + 3, 'rgba(95,243,255,.7)', 1); }
  }
  function drawHeroAndFx() {
    const h = R.hero;
    if (R.held) { const v = R.held; const gx = h.x * S + h.face * 17, gy = h.y * S - 20; for (let i = 0; i < 18; i++) { const k = i / 18; if ((i + Math.floor(now * 20)) % 2) { b.fillStyle = '#ff5fd2'; b.fillRect(Math.round(gx + (v.x * S - gx) * k), Math.round(gy + (v.y * S - gy) * k), 1, 1); } } }
    if (!(h.inv > 0 && Math.floor(now * 20) % 2)) A.drawHero(b, h.x * S, h.y * S, h.face, h.cast > 0 ? 'cast' : 'idle', now, h.vx);
    for (const q of R.bolts) { b.fillStyle = '#ff5fd2'; b.fillRect(Math.round(q.x * S) - 1, Math.round(q.y * S) - 1, 3, 3); b.fillStyle = '#fff'; b.fillRect(Math.round(q.x * S), Math.round(q.y * S), 1, 1); }
    for (const p of R.pk) { const x = Math.round(p.x * S), y = Math.round(p.y * S + Math.sin(p.t * 5) * 2); if (p.kind === 'heart') { b.fillStyle = '#ff4a7a'; b.fillRect(x - 3, y - 2, 3, 3); b.fillRect(x + 1, y - 2, 3, 3); b.fillRect(x - 2, y + 1, 5, 2); b.fillRect(x - 1, y + 3, 3, 1); } else { b.fillStyle = '#8affc8'; b.fillRect(x - 3, y - 1, 7, 3); b.fillRect(x - 1, y - 3, 3, 7); } }
    for (const f of R.fx) {
      const k = f.life / (f.max || 1);
      if (f.t === 'p') { b.fillStyle = f.col; b.globalAlpha = Math.min(1, k * 1.5); b.fillRect(Math.round(f.x * S), Math.round(f.y * S), 2, 2); b.globalAlpha = 1; }
      else if (f.t === 'ring') { b.globalAlpha = k; A.pxRing(b, f.x * S, f.y * S, Math.max(2, f.r * S), f.col, 1); b.globalAlpha = 1; }
      else if (f.t === 'txt') { b.globalAlpha = Math.min(1, k * 2); F.draw(b, f.txt, f.x * S, f.y * S, f.col, 1, 'c', '#000'); b.globalAlpha = 1; }
    }
  }
  function drawWarnings() {
    for (let i = R.evi; i < R.ev.length && R.ev[i].t - R.t < 1.6; i++) {
      const e = R.ev[i], p = spawnPos(e, e.kind); const x = clamp(p.x * S, 8, BW - 8), y = clamp(p.y * S, 8, BH - 8);
      if (Math.floor(now * 8) % 2) { b.fillStyle = e.kind === 'pla' || e.kind === 'moon' ? '#ff4a4a' : '#ffcf4a'; b.fillRect(x - 3, y - 4, 7, 2); b.fillRect(x - 2, y - 2, 5, 2); b.fillRect(x - 1, y, 3, 2); b.fillRect(x, y + 2, 1, 1); }
    }
  }
  function bar(x, y, w, h, f, col, bg = '#1a1030') { b.fillStyle = '#000'; b.fillRect(x - 1, y - 1, w + 2, h + 2); b.fillStyle = bg; b.fillRect(x, y, w, h); b.fillStyle = col; b.fillRect(x, y, Math.round(w * clamp(f, 0, 1)), h); }
  function drawHud() {
    const L = R.L, M = R.mission; F.draw(b, 'L' + (R.i + 1) + ' ' + L.name, 6, 5, '#e6dcff', 1, 'l', '#000');
    const prog = R.boss ? R.boss.hp / R.boss.max : Math.min(1, R.t / (L.dur + 4));
    bar(6, 16, 120, 4, R.boss ? prog : prog, R.boss ? '#ff5fd2' : '#7447c8'); F.draw(b, R.boss ? 'BOSS' : 'WAVE', 130, 15, '#a98bff', 1, 'l', '#000');
    const nm = { station: 'STATION', city: 'CITY', convoy: 'CONVOY', critters: 'PIPS', ark: 'THE ARK' }[M.type]; const f = missionFrac(M);
    F.draw(b, nm, 6, 26, '#9ae0ff', 1, 'l', '#000'); bar(6, 36, 120, 5, f, f > 0.5 ? '#5ff3a0' : f > 0.25 ? '#ffcf4a' : '#ff4a4a');
    F.draw(b, 'SCORE ' + R.score, BW - 6, 5, '#fff', 1, 'r', '#000');
    for (let i = 0; i < 5; i++) { const x = BW - 10 - i * 10; b.fillStyle = i < R.hero.hp ? '#ff4a7a' : '#3a2040'; b.fillRect(x - 3, 16, 3, 3); b.fillRect(x + 1, 16, 3, 3); b.fillRect(x - 2, 19, 5, 2); b.fillRect(x - 1, 21, 3, 1); }
    // voids panel
    const used = bodyBudget(); F.draw(b, 'VOID MASS', 6, BH - 38, '#a98bff', 1, 'l', '#000'); bar(6, BH - 28, 90, 4, used / R.budget, '#7447c8');
    R.voids.forEach((v, i) => { if (!v.on) return; F.draw(b, v.id + ' ' + Math.round(v.r), 6 + i * 36, BH - 20, i === R.selV ? '#fff' : '#a98bff', 1, 'l', '#000'); });
    F.draw(b, 'RELEASE', BW - 6, BH - 20, R.cdRel > 0 ? '#6a5a8a' : '#ff5fd2', 1, 'r', '#000'); bar(BW - 66, BH - 10, 60, 3, 1 - R.cdRel / 9, R.cdRel > 0 ? '#6a5a8a' : '#ff5fd2');
    if (R.t < 9 && L.hint) { const lines = F.wrap(L.hint, 84); lines.forEach((ln, i) => F.draw(b, ln, BW / 2, BH - 62 + i * 9, '#ffe9a0', 1, 'c', '#000')); }
    if (R.over) { F.draw(b, R.win ? 'MISSION COMPLETE' : 'MISSION LOST', BW / 2, BH / 2 - 10, R.win ? '#8affc8' : '#ff7a8a', 3, 'c', '#000'); }
  }
  function drawPlay() {
    const sx = R.shake ? Math.round((Math.random() - 0.5) * R.shake) : 0, sy = R.shake ? Math.round((Math.random() - 0.5) * R.shake) : 0;
    b.save(); b.translate(sx, sy); drawBg(now, R.L.world);
    const occ = [];
    for (const v of R.voids) if (v.on) occ.push({ x: v.x, y: v.y, r: v.r, v: true, cut: crescentCut(v) });
    for (const h of R.hz) occ.push({ x: h.x, y: h.y, r: h.r });
    if (R.boss && !R.boss.dead) occ.push({ x: R.boss.x, y: R.boss.y, r: R.boss.r });
    for (const p of R.mission.parts) if (p.alive && p.r > 20 && !p.isReef) occ.push({ x: p.x, y: p.y, r: p.r });
    if (R.mission.ground) occ.push(R.mission.ground);
    if (R.mission.reef) occ.push(R.mission.reef);
    drawInflux(occ, now, WORLDS[R.L.world].line);
    drawMission(); drawBodies(); drawBossSprite();
    R.voids.forEach((v, i) => { if (!v.on) return; pxCrescent(b, v, v === R.held ? '#c85ff0' : '#5a2fb0', '#fff'); const iv = Math.max(2, Math.round(v.r * S)); pxCrescent(b, { x: v.x, y: v.y, r: v.r * 0.82, ang: v.ang }, v === R.held ? '#ff5fd2' : '#8a5ff0'); pxCrescent(b, { x: v.x - Math.cos(v.ang) * 2 / S, y: v.y - Math.sin(v.ang) * 2 / S, r: v.r * 0.55, ang: v.ang }, '#1a0b33'); F.draw(b, v.id, v.x * S, v.y * S - 3, i === R.selV ? '#fff' : '#d8c8ff', 1, 'c'); });
    if (R.relFx > 0) { b.fillStyle = `rgba(200,155,255,${R.relFx * 0.4})`; b.fillRect(0, 0, BW, BH); }
    drawHeroAndFx(); drawWarnings(); b.restore(); drawHud();
    // reticle
    const mx = Math.round(mouse.x * S), my = Math.round(mouse.y * S); b.fillStyle = R.held ? '#ff5fd2' : '#fff'; b.fillRect(mx - 4, my, 3, 1); b.fillRect(mx + 2, my, 3, 1); b.fillRect(mx, my - 4, 1, 3); b.fillRect(mx, my + 2, 1, 3);
  }

  /* ---------- menus ---------- */
  function drawTitle() {
    drawBg(now, 5); const occ = [{ x: 560 + Math.sin(now * 0.7) * 40, y: 450, r: 150, v: true, cut: crescentCut({ x: 560 + Math.sin(now * 0.7) * 40, y: 450, r: 150, ang: -0.4 }) }, { x: 1180, y: 300 + Math.cos(now) * 30, r: 90 }];
    drawInflux(occ, now, '#70b8c3');
    A.drawHero(b, 150, 250, 1, 'cast', now, 0); b.save(); b.translate(150, 250); b.restore();
    F.draw(b, 'VOIDCASTER', BW / 2, 60, '#c89bff', 5, 'c', '#2a1550');
    F.draw(b, 'BLOCK THE INFLUX. DEFEND THE LIGHT.', BW / 2, 112, '#e6dcff', 1, 'c', '#000');
    const lore = ['THE DEARTH IS A HUNGER BETWEEN THE STARS. IT CANNOT MAKE LIGHT,', 'SO IT HURLS METEORS, MOONS AND WORLDS AT EVERYTHING THAT GLOWS.', 'VOIDCASTER WIELDS CRESCENT VOIDS THAT TURN TO SHADOW THE INFLUX.', 'THE DEFICIT DRAWS THE FALLING MASS INTO THE SHADOW. NOT ONTO YOU.'];
    lore.forEach((l, i) => F.draw(b, l, BW / 2, 170 + i * 11, '#b8a8e8', 1, 'c', '#000'));
    if (Math.floor(now * 2) % 2) F.draw(b, 'PRESS ENTER OR CLICK TO PLAY', BW / 2, 262, '#fff', 2, 'c', '#000');
    F.draw(b, 'L LEVELS   F FULLSCREEN   M MUTE', BW / 2, 292, '#8a7ab8', 1, 'c', '#000');
    F.draw(b, 'MOUSE: DRAG VOIDS, FIRE   WASD: MOVE   WHEEL OR [ ]: SIZE   1 2 3: SELECT   SPACE: RELEASE', BW / 2, 316, '#8a7ab8', 1, 'c', '#000');
    F.draw(b, 'A SPATIAL DISPLACEMENT THEORY GAME', BW / 2, 344, '#5a4a88', 1, 'c');
  }
  function drawSelect() {
    drawBg(now, 0); F.draw(b, 'SELECT MISSION', BW / 2, 12, '#c89bff', 2, 'c', '#2a1550');
    const un = unlockedUpTo();
    for (let w = 0; w < 6; w++) {
      F.draw(b, WORLDS[w].name, 12, 62 + w * 49, '#a98bff', 1, 'l', '#000');
      for (let k = 0; k < 5; k++) {
        const i = w * 5 + k, x = 150 + k * 90, y = 48 + w * 49, locked = i > un;
        b.fillStyle = i === sel ? '#c89bff' : locked ? '#2a2038' : '#4a2a8c'; b.fillRect(x - 1, y - 1, 82, 40);
        b.fillStyle = locked ? '#150d20' : '#1d1038'; b.fillRect(x, y, 80, 38);
        F.draw(b, (i + 1), x + 6, y + 5, locked ? '#4a3a5a' : '#fff', 2);
        F.draw(b, (locked ? '???' : LEVELS[i].name).slice(0, 13), x + 5, y + 26, locked ? '#4a3a5a' : '#b8a8e8', 1);
        for (let s = 0; s < 3; s++) { b.fillStyle = s < (save.stars[i] || 0) ? '#ffd24a' : '#3a2a4a'; b.fillRect(x + 50 + s * 9, y + 6, 6, 6); }
        if (LEVELS[i].boss) F.draw(b, 'BOSS', x + 44, y + 17, '#ff5fd2', 1);
      }
    }
    F.draw(b, 'ARROWS + ENTER, OR CLICK     ESC: TITLE', BW / 2, 347, '#8a7ab8', 1, 'c', '#000');
  }
  function drawBrief() {
    const L = LEVELS[cur]; drawBg(now, L.world); drawInflux([{ x: 1250, y: 450, r: 130, v: true, cut: crescentCut({ x: 1250, y: 450, r: 130, ang: -0.3 }) }], now, WORLDS[L.world].line);
    A.drawHero(b, 90, 200, 1, 'cast', now, 0);
    F.draw(b, 'MISSION ' + (cur + 1), 150, 24, '#a98bff', 1, 'l', '#000'); F.draw(b, L.name, 150, 38, '#fff', 3, 'l', '#2a1550');
    F.draw(b, WORLDS[L.world].name, 150, 66, '#c89bff', 1, 'l', '#000');
    let y = 84; if (cur % 5 === 0) { F.wrap(WORLDS[L.world].intro, 70).forEach((ln) => { F.draw(b, ln, 150, y, '#e6dcff', 1, 'l', '#000'); y += 10; }); y += 8; }
    const goal = { station: 'DEFEND THE STATION.', city: 'DEFEND THE CITY DOMES.', convoy: 'KEEP THE SETTLER SHIPS ALIVE.', critters: 'PROTECT THE PIPS.', ark: 'ESCORT THE SETTLER ARK.' }[L.m]; F.draw(b, 'OBJECTIVE: ' + goal, 150, y, '#9ae0ff', 1, 'l', '#000'); y += 14;
    F.draw(b, 'HOSTILES:', 150, y, '#ff9ab0', 1, 'l', '#000'); y += 12;
    ['met', 'ast', 'moon', 'pla', 'wpn'].forEach((k, i) => { if (L.mix[i] > 0) { const d = HZ[k]; if (k === 'wpn') A.drawLance(b, 160, y + 6, 1, 0, now); else { const sp = A.bodySprite(k, Math.max(3, Math.min(9, Math.round(d.r[0] * S))), 3); b.drawImage(sp, Math.round(160 - sp.width / 2), Math.round(y + 6 - sp.height / 2)); } F.draw(b, d.name, 176, y + 3, '#d8c8ff', 1, 'l', '#000'); y += 16; } });
    if (L.boss) { F.draw(b, 'BOSS: ' + ['', 'DEARTH REAVER', 'DEARTH WARDEN', 'THE HOLLOW REGENT'][L.boss], 150, y, '#ff5fd2', 1, 'l', '#000'); y += 12; }
    y += 6; F.wrap('TIP: ' + L.hint, 76).forEach((ln) => { F.draw(b, ln, 150, y, '#ffe9a0', 1, 'l', '#000'); y += 10; });
    if (Math.floor(now * 2) % 2) F.draw(b, 'PRESS ENTER TO DEPLOY', BW / 2, 332, '#fff', 2, 'c', '#000');
  }
  function drawEnd(win) {
    drawBg(now, 5); drawInflux([{ x: 800, y: 450, r: 200, v: true, cut: crescentCut({ x: 800, y: 450, r: 200, ang: now * 0.5 }) }], now, win ? '#70c8a0' : '#c87090');
    F.draw(b, win ? 'MISSION COMPLETE' : 'MISSION LOST', BW / 2, 70, win ? '#8affc8' : '#ff7a8a', 4, 'c', '#000');
    if (win) { for (let s = 0; s < 3; s++) { const x = BW / 2 - 40 + s * 40, y = 130; b.fillStyle = s < R.stars ? '#ffd24a' : '#3a2a4a'; A.pxCircle(b, x, y, 12, b.fillStyle); } }
    else F.draw(b, R.hero.hp <= 0 ? 'VOIDCASTER FELL' : 'THE LIGHT WENT OUT', BW / 2, 130, '#e6dcff', 2, 'c', '#000');
    F.draw(b, 'SCORE ' + R.score, BW / 2, 175, '#fff', 2, 'c', '#000');
    F.draw(b, win ? 'ENTER: NEXT MISSION' : 'ENTER: RETRY', BW / 2, 240, '#fff', 1, 'c', '#000'); F.draw(b, 'R: REPLAY   L: LEVELS', BW / 2, 256, '#a98bff', 1, 'c', '#000');
    if (win && R.i === 29) F.draw(b, 'THE HOLLOW CROWN IS BROKEN. THE LIGHT HOLDS. THANK YOU, VOIDCASTER.', BW / 2, 290, '#ffe9a0', 1, 'c', '#000');
  }
  function drawPause() { b.fillStyle = 'rgba(5,3,10,.7)'; b.fillRect(0, 0, BW, BH); F.draw(b, 'PAUSED', BW / 2, 130, '#fff', 4, 'c', '#2a1550'); F.draw(b, 'P / ESC: RESUME   R: RESTART   L: LEVELS', BW / 2, 190, '#e6dcff', 1, 'c'); }

  /* ---------- flow ---------- */
  function go(s) { scene = s; tScene = 0; }
  function startRun(i) { cur = i; R = newRun(i); go('play'); VCAudio.music(LEVELS[i].world); }
  function enter() {
    VCAudio.init(); VCAudio.play('ui');
    if (scene === 'title') { if (!document.fullscreenElement && document.documentElement.requestFullscreen) { try { document.documentElement.requestFullscreen().catch(() => {}); } catch (e) { /* ignore */ } } cur = Math.min(unlockedUpTo(), 29); sel = cur; go('brief'); }
    else if (scene === 'select') { if (sel <= unlockedUpTo()) { cur = sel; go('brief'); } }
    else if (scene === 'brief') startRun(cur);
    else if (scene === 'win') { if (cur < 29) { cur++; go('brief'); } else go('select'); }
    else if (scene === 'lose') startRun(cur);
  }
  addEventListener('keydown', (e) => {
    const k = e.key.toLowerCase(); if (keys[k] && e.repeat && k !== '[' && k !== ']') { /* held */ } keys[k] = true;
    if (['arrowup', 'arrowdown', 'arrowleft', 'arrowright', ' '].includes(k)) e.preventDefault();
    VCAudio.init();
    if (k === 'f') { if (!document.fullscreenElement) document.documentElement.requestFullscreen?.().catch(() => {}); else document.exitFullscreen?.(); }
    if (k === 'm') VCAudio.toggle();
    if (scene === 'play') {
      if (k === 'p' || k === 'escape') go('pause');
      if (k === ' ') release();
      if (k === '1' || k === '2' || k === '3') { const v = R.voids[+k - 1]; if (v.on) R.selV = +k - 1; }
      if (k === '[') resizeVoid(R.held || R.voids[R.selV], -8); if (k === ']') resizeVoid(R.held || R.voids[R.selV], 8);
      if (k === 'r' && e.shiftKey) startRun(cur);
    } else if (scene === 'pause') { if (k === 'p' || k === 'escape') go('play'); if (k === 'r') startRun(cur); if (k === 'l') go('select'); }
    else if (scene === 'select') {
      if (k === 'arrowright' || k === 'd') sel = Math.min(29, sel + 1); if (k === 'arrowleft' || k === 'a') sel = Math.max(0, sel - 1);
      if (k === 'arrowdown' || k === 's') sel = Math.min(29, sel + 5); if (k === 'arrowup' || k === 'w') sel = Math.max(0, sel - 5);
      if (k === 'enter') enter(); if (k === 'escape') go('title');
    } else {
      if (k === 'enter' || k === ' ') enter(); if (k === 'l') { sel = cur; go('select'); }
      if (k === 'r' && (scene === 'win' || scene === 'lose')) startRun(cur); if (k === 'escape' && scene === 'brief') go('select');
    }
  });
  addEventListener('keyup', (e) => { keys[e.key.toLowerCase()] = false; });
  addEventListener('blur', () => { for (const k in keys) keys[k] = false; if (scene === 'play') go('pause'); if (R) { R.firing = false; R.held = null; } });
  cv.addEventListener('contextmenu', (e) => e.preventDefault());
  cv.addEventListener('pointermove', (e) => { const p = toWorld(e); mouse.x = p.x; mouse.y = p.y; });
  cv.addEventListener('pointerdown', (e) => {
    VCAudio.init(); const p = toWorld(e); mouse.x = p.x; mouse.y = p.y; mouse.down = true; cv.setPointerCapture?.(e.pointerId);
    if (scene === 'play') {
      let best = null, bd = 1e9; R.voids.forEach((v, i) => { if (!v.on) return; const d = Math.hypot(p.x - v.x, p.y - v.y); if (d < v.r + 14 && d < bd) { bd = d; best = v; R.selV = i; } });
      if (best) { R.held = best; best.vx = best.vy = 0; VCAudio.play('grab'); } else R.firing = true;
    } else if (scene === 'select') {
      const bx = p.x * S, by = p.y * S; for (let i = 0; i < 30; i++) { const x = 150 + (i % 5) * 90, y = 48 + Math.floor(i / 5) * 49; if (bx >= x && bx <= x + 80 && by >= y && by <= y + 38) { if (sel === i) enter(); else sel = i; } }
    } else if (scene === 'pause') go('play'); else enter();
  });
  const up = () => { mouse.down = false; if (R) { if (R.held) { const v = R.held; v.vx *= 0.6; v.vy *= 0.6; VCAudio.play('drop'); } R.held = null; R.firing = false; } };
  addEventListener('pointerup', up); addEventListener('pointercancel', up);
  cv.addEventListener('wheel', (e) => { e.preventDefault(); if (scene === 'play') { const v = R.held || (R.voids.filter((q) => q.on && Math.hypot(mouse.x - q.x, mouse.y - q.y) < q.r + 30)[0]) || R.voids[R.selV]; resizeVoid(v, -Math.sign(e.deltaY) * 6); } }, { passive: false });

  function frame(ts) {
    requestAnimationFrame(frame); now = ts / 1000; const dt = Math.min(0.033, now - last || 0); last = now; tScene += dt;
    cv.style.cursor = scene === 'play' ? 'none' : 'default';
    if (scene === 'play') updatePlay(dt);
    if (scene === 'title') drawTitle(); else if (scene === 'select') drawSelect(); else if (scene === 'brief') drawBrief();
    else if (scene === 'play') drawPlay(); else if (scene === 'pause') { drawPlay(); drawPause(); } else if (scene === 'win') drawEnd(true); else if (scene === 'lose') drawEnd(false);
    cx.imageSmoothingEnabled = false; cx.fillStyle = '#05030a'; cx.fillRect(0, 0, cv.width, cv.height);
    cx.drawImage(buf, 0, 0, BW, BH, view.x, view.y, Math.round(BW * view.k), Math.round(BH * view.k));
  }
  window.__vc = { get scene() { return scene; }, get run() { return R; }, startRun, keys, mouse, release };
  requestAnimationFrame(frame);
})();
