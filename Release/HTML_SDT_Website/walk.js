/* Mega-walk interactives. James Christopher Tyndall, Melbourne. */
(function () {
  'use strict';

  function motionOff() {
    return document.documentElement.getAttribute('data-sdt-motion') === 'off';
  }

  /* ── two bodies in the flood ─────────────────────────────────────────── */
  (function force() {
    var svg = document.getElementById('wk-force');
    if (!svg) return;
    var A = { x: 190, y: 200, r: 28 }, B = { x: 370, y: 200, r: 22 };
    var drag = null, N = 28;
    var read = document.getElementById('wk-force-read');

    function pts(c) {
      var out = [], i;
      for (i = 0; i < N; i++) {
        var t = (i / N) * Math.PI * 2;
        out.push({ x: c.x + Math.cos(t) * 150, y: c.y + Math.sin(t) * 150 });
      }
      return out;
    }
    function hits(x1, y1, x2, y2, c) {
      var dx = x2 - x1, dy = y2 - y1, fx = x1 - c.x, fy = y1 - c.y;
      var a = dx * dx + dy * dy, b = 2 * (fx * dx + fy * dy);
      var cc = fx * fx + fy * fy - c.r * c.r, d = b * b - 4 * a * cc;
      if (d < 0) return false;
      d = Math.sqrt(d);
      var t1 = (-b - d) / (2 * a), t2 = (-b + d) / (2 * a);
      return (t1 > 0.02 && t1 < 0.98) || (t2 > 0.02 && t2 < 0.98);
    }
    function dist() {
      return Math.hypot(B.x - A.x, B.y - A.y);
    }
    function paint() {
      var rim = pts({ x: 280, y: 200 });
      var lines = '', i, j, p, q, blocked;
      for (i = 0; i < rim.length; i++) {
        for (j = i + 1; j < rim.length; j++) {
          p = rim[i]; q = rim[j];
          blocked = hits(p.x, p.y, q.x, q.y, A) || hits(p.x, p.y, q.x, q.y, B);
          lines += '<line x1="' + p.x + '" y1="' + p.y + '" x2="' + q.x + '" y2="' + q.y +
            '" stroke="' + (blocked ? 'rgba(176,116,48,.12)' : 'rgba(176,116,48,.28)') +
            '" stroke-width="0.6"/>';
        }
      }
      var r = dist();
      var f = (A.r * A.r * B.r * B.r) / (r * r);
      svg.innerHTML = lines +
        '<circle cx="' + A.x + '" cy="' + A.y + '" r="' + A.r + '" fill="#1e1c18" stroke="#b07430" stroke-width="2"/>' +
        '<circle cx="' + B.x + '" cy="' + B.y + '" r="' + B.r + '" fill="#1e1c18" stroke="#b07430" stroke-width="2"/>';
      if (read) read.textContent = 'F ∝ R₁²R₂²/r² = ' + f.toFixed(2) + '×';
    }
    function which(x, y) {
      if (Math.hypot(x - A.x, y - A.y) < A.r + 12) return A;
      if (Math.hypot(x - B.x, y - B.y) < B.r + 12) return B;
      return null;
    }
    function xy(e) {
      var r = svg.getBoundingClientRect();
      return { x: (e.clientX - r.left) * (560 / r.width), y: (e.clientY - r.top) * (400 / r.height) };
    }
    svg.addEventListener('pointerdown', function (e) {
      var p = xy(e); drag = which(p.x, p.y);
      if (drag) { svg.setPointerCapture(e.pointerId); e.preventDefault(); }
    });
    svg.addEventListener('pointermove', function (e) {
      if (!drag) return;
      var p = xy(e);
      drag.x = Math.max(40, Math.min(520, p.x));
      drag.y = Math.max(40, Math.min(360, p.y));
      paint();
    });
    svg.addEventListener('pointerup', function () { drag = null; });
    paint();
  })();

  /* ── movement budget ─────────────────────────────────────────────────── */
  (function budget() {
    var svg = document.getElementById('wk-budget');
    if (!svg) return;
    var read = document.getElementById('wk-budget-read');
    var t = 0.35, drag = false;
    function paint() {
      var cx = 160, cy = 160, R = 110;
      var ang = t * Math.PI / 2;
      var x = cx + R * Math.cos(ang), y = cy - R * Math.sin(ang);
      var v = Math.sin(ang), vc = Math.cos(ang);
      svg.innerHTML =
        '<path d="M ' + (cx + R) + ' ' + cy + ' A ' + R + ' ' + R + ' 0 0 0 ' + cx + ' ' + (cy - R) +
        '" fill="none" stroke="#b07430" stroke-width="2"/>' +
        '<line x1="' + cx + '" y1="' + cy + '" x2="' + x + '" y2="' + y + '" stroke="#1e1c18" stroke-width="1.4"/>' +
        '<circle cx="' + x + '" cy="' + y + '" r="8" fill="#b07430"/>' +
        '<text x="' + (cx + R + 8) + '" y="' + (cy + 4) + '" font-size="11" fill="#7a7265">travel</text>' +
        '<text x="' + (cx - 18) + '" y="' + (cy - R - 8) + '" font-size="11" fill="#7a7265">spin</text>';
      if (read) read.textContent = 'v_circ² + v² = c² · spin ' + (vc * vc * 100).toFixed(0) + '% · travel ' + (v * v * 100).toFixed(0) + '%';
    }
    function setFrom(e) {
      var r = svg.getBoundingClientRect();
      var x = (e.clientX - r.left) * (320 / r.width) - 160;
      var y = 160 - (e.clientY - r.top) * (210 / r.height);
      var a = Math.atan2(y, x);
      t = Math.max(0, Math.min(1, a / (Math.PI / 2)));
      paint();
    }
    svg.addEventListener('pointerdown', function (e) { drag = true; svg.setPointerCapture(e.pointerId); setFrom(e); });
    svg.addEventListener('pointermove', function (e) { if (drag) setFrom(e); });
    svg.addEventListener('pointerup', function () { drag = false; });
    paint();
  })();

  /* ── Shapiro: light ran slower ───────────────────────────────────────── */
  (function shapiro() {
    var svg = document.getElementById('wk-shapiro');
    if (!svg) return;
    var read = document.getElementById('wk-shapiro-read');
    var b = 1.15, drag = false;
    var C = 299792458, z0 = 2.123e-6, delay0 = 247.24;
    function paint() {
      var sun = { x: 200, y: 130 }, R = 36;
      var y = 130 - (b - 1) * 70;
      var z = z0 / b;
      var c2 = C * Math.pow(1 - z, 2);
      var c1 = C * (1 - z);
      var d2 = delay0 / b;
      var d1 = d2 / 2;
      svg.innerHTML =
        '<circle cx="' + sun.x + '" cy="' + sun.y + '" r="' + R + '" fill="#b07430"/>' +
        '<line x1="20" y1="' + y + '" x2="380" y2="' + y + '" stroke="#1e1c18" stroke-width="1.6"/>' +
        '<circle cx="40" cy="' + y + '" r="4" fill="#1e1c18"/>' +
        '<text x="200" y="210" text-anchor="middle" font-size="11" fill="#7a7265">drag the ray · grazing is the measured pass</text>';
      if (read) {
        read.innerHTML =
          'b / R☉ = ' + b.toFixed(2) +
          ' · c_far = c(1−z)² = ' + (c2 / 1000).toFixed(3) + ' km/s' +
          ' · delay ' + d2.toFixed(2) + ' μs' +
          ' · half-law ' + d1.toFixed(2) + ' μs (falsified)';
      }
    }
    function setFrom(e) {
      var r = svg.getBoundingClientRect();
      var y = (e.clientY - r.top) * (220 / r.height);
      b = Math.max(1.0, Math.min(2.4, 1 + (130 - y) / 70));
      paint();
    }
    svg.addEventListener('pointerdown', function (e) { drag = true; svg.setPointerCapture(e.pointerId); setFrom(e); });
    svg.addEventListener('pointermove', function (e) { if (drag) setFrom(e); });
    svg.addEventListener('pointerup', function () { drag = false; });
    paint();
    if (!motionOff()) {
      /* idle: none — the visitor drags */
    }
  })();
})();
