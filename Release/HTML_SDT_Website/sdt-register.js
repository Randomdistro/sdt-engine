/* ════════════════════════════════════════════════════════════════════════════
   SDT REGISTER SWITCH — Newcomers · Laymen · Academics
   James Christopher Tyndall, Melbourne.

   The same content, told at three levels. Drop <div id="sdt-register-switch">
   into a page and include this script; it paints the switch, marks the current
   level, and remembers the reader's choice so the rest of the site can follow
   it later. Pure links — it works with JavaScript disabled if the markup is
   present, and degrades to nothing if it is not.
   ════════════════════════════════════════════════════════════════════════════ */
(function () {
  'use strict';

  /* Register families. Add a family by listing its three files. */
  var FAMILIES = [
    {
      name: 'The causal chain',
      simple: 'causal-chain-simple.html',
      layman: 'theory.html#L0',
      technical: 'causal-chain-technical.html'
    }
  ];

  var LEVELS = [
    ['simple', 'Newcomers', 'a first pass with the mechanism kept visible'],
    ['layman', 'Laymen', 'the complete dependency account with visible status and residuals'],
    ['technical', 'Academics', 'relations, evidence labels, residuals and open debts']
  ];

  var here = (location.pathname.split('/').pop() || 'index.html').toLowerCase();

  function family() {
    for (var i = 0; i < FAMILIES.length; i++) {
      var f = FAMILIES[i];
      if (here === f.simple || here === f.layman || here === f.technical) return f;
    }
    return null;
  }

  function boot() {
    var mount = document.getElementById('sdt-register-switch');
    var fam = family();
    if (!mount || !fam) return;
    if (document.querySelector('.sdtq-register')) {
      mount.hidden = true;
      mount.setAttribute('aria-hidden', 'true');
      return;
    }

    var wrap = document.createElement('div');
    wrap.className = 'sdt-reg';
    wrap.setAttribute('role', 'group');
    wrap.setAttribute('aria-label', 'Reading level');

    var lab = document.createElement('span');
    lab.className = 'sdt-reg__lab';
    lab.textContent = 'Reading level';
    wrap.appendChild(lab);

    var seg = document.createElement('div');
    seg.className = 'sdt-reg__seg';

    LEVELS.forEach(function (L) {
      var href = fam[L[0]];
      var current = (href.toLowerCase() === here);
      var a = document.createElement('a');
      a.href = href;
      a.textContent = L[1];
      a.title = L[2];
      if (current) {
        a.setAttribute('aria-current', 'page');
        a.className = 'on';
      }
      a.addEventListener('click', function () {
        try { localStorage.setItem('sdt.register', L[0]); } catch (e) {}
      });
      seg.appendChild(a);
    });

    wrap.appendChild(seg);
    mount.appendChild(wrap);
  }

  if (document.readyState === 'loading') {
    document.addEventListener('DOMContentLoaded', boot);
  } else { boot(); }
})();
