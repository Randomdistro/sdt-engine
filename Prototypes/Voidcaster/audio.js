/* VOIDCASTER · tiny chiptune synth: effects and a brooding loop. */
'use strict';
const VCAudio = (() => {
  let ac = null, master = null, muted = false, timer = null, step = 0, nextT = 0, world = 0;
  function init() {
    if (ac) { if (ac.state === 'suspended') ac.resume(); return; }
    try { ac = new (window.AudioContext || window.webkitAudioContext)(); master = ac.createGain(); master.gain.value = 0.3; master.connect(ac.destination); } catch (e) { ac = null; }
  }
  function tone(f, d, type = 'square', v = 0.15, slide = 0, delay = 0) {
    if (!ac || muted) return;
    const t = ac.currentTime + delay, o = ac.createOscillator(), g = ac.createGain();
    o.type = type; o.frequency.setValueAtTime(f, t); if (slide) o.frequency.exponentialRampToValueAtTime(Math.max(30, f + slide), t + d);
    g.gain.setValueAtTime(v, t); g.gain.exponentialRampToValueAtTime(0.0005, t + d);
    o.connect(g); g.connect(master); o.start(t); o.stop(t + d + 0.02);
  }
  function noise(d, v = 0.2, f = 1200) {
    if (!ac || muted) return;
    const n = Math.floor(ac.sampleRate * d), buf = ac.createBuffer(1, n, ac.sampleRate), a = buf.getChannelData(0);
    for (let i = 0; i < n; i++) a[i] = (Math.random() * 2 - 1) * (1 - i / n);
    const s = ac.createBufferSource(), g = ac.createGain(), lp = ac.createBiquadFilter();
    lp.type = 'lowpass'; lp.frequency.value = f; g.gain.value = v; s.buffer = buf; s.connect(lp); lp.connect(g); g.connect(master); s.start();
  }
  const FX = {
    bolt: () => tone(900, 0.07, 'square', 0.07, -500),
    grab: () => tone(220, 0.1, 'triangle', 0.18, 140),
    drop: () => tone(300, 0.1, 'triangle', 0.12, -120),
    pop: () => { noise(0.18, 0.15, 2500); tone(160, 0.12, 'square', 0.08, -90); },
    boom: () => { noise(0.45, 0.35, 700); tone(70, 0.4, 'sawtooth', 0.15, -40); },
    hurt: () => { tone(200, 0.25, 'sawtooth', 0.2, -120); noise(0.2, 0.2, 900); },
    absorb: () => { tone(300, 0.25, 'sine', 0.2, 500); tone(600, 0.2, 'sine', 0.12, 400, 0.08); },
    release: () => { tone(110, 0.5, 'sawtooth', 0.2, 500); noise(0.4, 0.2, 3000); },
    pick: () => { tone(660, 0.07, 'square', 0.1); tone(990, 0.1, 'square', 0.1, 0, 0.07); },
    warn: () => tone(440, 0.06, 'square', 0.04),
    win: () => [523, 659, 784, 1046].forEach((f, i) => tone(f, 0.22, 'square', 0.14, 0, i * 0.13)),
    lose: () => [392, 330, 262, 196].forEach((f, i) => tone(f, 0.3, 'triangle', 0.18, 0, i * 0.2)),
    ui: () => tone(520, 0.05, 'square', 0.08),
  };
  const ROOTS = [57, 55, 52, 53, 50, 48]; // A3 G3 E3 F3 D3 C3 per world
  const ARP = [0, 3, 7, 12, 7, 3, 10, 7, 0, 3, 7, 14, 12, 7, 3, 7];
  const mf = (m) => 440 * Math.pow(2, (m - 69) / 12);
  function sched() {
    if (!ac || muted) { nextT = 0; return; }
    if (!nextT || nextT < ac.currentTime) nextT = ac.currentTime + 0.05;
    const dt = 60 / (96 + world * 6) / 2;
    while (nextT < ac.currentTime + 0.25) {
      const r = ROOTS[world % 6], i = step % 16, d = nextT - ac.currentTime;
      if (i % 4 === 0) tone(mf(r - 12), dt * 3.6, 'triangle', 0.16, 0, d);
      tone(mf(r + 12 + ARP[i]), dt * 0.8, 'square', 0.035, 0, d);
      if (i % 8 === 4) tone(mf(r + 24 + (i >> 3) * 3), dt * 2, 'square', 0.03, 0, d);
      step++; nextT += dt;
    }
  }
  return {
    init, play: (n) => { if (FX[n]) FX[n](); },
    music(w) { world = w; if (!timer) timer = setInterval(sched, 60); },
    stop() { if (timer) { clearInterval(timer); timer = null; } },
    toggle() { muted = !muted; if (master) master.gain.value = muted ? 0 : 0.3; return muted; },
    get muted() { return muted; },
  };
})();
