/* ════════════════════════════════════════════════════════════════════════════
   SDT SITE SHELL — one path, four unfolding menus.
   James Christopher Tyndall, Melbourne.  Pairs with sdt-shell.css.

     FRONT DOOR index.html — concise arrival
     THE PATH   theory.html — the complete dependency chain
     FOUR MENUS Lab · Benchmarks · Investigations · Papers
     TOP bar    search, settings, language

   In-text links: <a href="paper-06-gravitation.html" data-sdt-open="papers:paper-06-gravitation.html">
   open the menu, pulse the item (scale 1.1 then back), then follow the href.
   Dark: light burn. Light: ink-shadow burn.
   ════════════════════════════════════════════════════════════════════════════ */
(function () {
  'use strict';
  if (window.__SDT_SHELL__) return;
  window.__SDT_SHELL__ = true;

  /*
   * Keep legacy page loops responsive to the shared motion setting. Individual
   * instruments still own viewport-level pausing; this gate covers reduced
   * motion and hidden tabs for every shell page.
   */
  if (window.requestAnimationFrame && !window.__SDT_MOTION_RAF__) {
    window.__SDT_MOTION_RAF__ = true;
    var nativeRequestFrame = window.requestAnimationFrame.bind(window);
    var nativeCancelFrame = window.cancelAnimationFrame
      ? window.cancelAnimationFrame.bind(window)
      : function () {};
    var nextFrameId = 1;
    var pendingFrames = {};

    function frameMotionOff() {
      if (document.hidden) return true;
      if (window.__SDT_LOCAL_MOTION_CONTROL__) return false;
      var setting = document.documentElement.getAttribute('data-sdt-motion');
      return setting === 'off'
        || (
          setting == null
          && window.matchMedia
          && window.matchMedia('(prefers-reduced-motion: reduce)').matches
        );
    }

    function scheduleFrame(entry) {
      entry.nativeId = nativeRequestFrame(function (timestamp) {
        if (!pendingFrames[entry.id]) return;
        if (frameMotionOff()) {
          entry.timerId = window.setTimeout(function () {
            entry.timerId = null;
            scheduleFrame(entry);
          }, 250);
          return;
        }
        delete pendingFrames[entry.id];
        entry.callback(timestamp);
      });
    }

    window.requestAnimationFrame = function (callback) {
      var entry = {
        id: nextFrameId++,
        callback: callback,
        nativeId: null,
        timerId: null
      };
      pendingFrames[entry.id] = entry;
      scheduleFrame(entry);
      return entry.id;
    };

    window.cancelAnimationFrame = function (id) {
      var entry = pendingFrames[id];
      if (!entry) {
        nativeCancelFrame(id);
        return;
      }
      delete pendingFrames[id];
      if (entry.timerId != null) window.clearTimeout(entry.timerId);
      if (entry.nativeId != null) nativeCancelFrame(entry.nativeId);
    };
  }

  var here = (location.pathname.split('/').pop() || 'index.html').toLowerCase();
  var onWalk = (here === 'theory.html');

  /* ── four unfolding menus ─────────────────────────────────────────────── */
  var MENUS = {
    lab: ['Lab', [
      ['Atomicus', [
        ['Atomicus lab', 'atomicus-lab.html'],
        ['Atomicus 3D', 'atomicus-3d.html'],
        ['Packing sequencer', 'nuclear-packing-sequencer.html'],
        ['Sequencer walkthrough', 'nuclear-packing-walkthrough.html'],
        ['Fission — flay, not split', 'atomicus-fission-impact.html']
      ]],
      ['Instruments', [
        ['Koppa ladder', 'koppa-ladder.html'],
        ['Depth closure', 'depth_closure_scroller.html'],
        ['The wall in the infrared', 'clearing-ladder.html'],
        ['Six laws scroller', 'laws_scroller.html'],
        ['Solar system', 'solar-system.html'],
        ['Celestial three-body solver', 'celestial-three-body-solver.html'],
        ['Eclipse', 'cq06-eclipse.html']
      ]]
    ]],
    bench: ['Benchmarks', [
      ['The suite', [
        ['Benchmarks — the tally', 'benchmarks.html'],
        ['Benchmarks scroller', 'benchmarks_scroller.html']
      ]]
    ]],
    inv: ['Investigations', [
      ['The programme', [
        ['All investigations', 'investigations.html'],
        ['Interactive experiment catalogue', 'experiments.html'],
        ['Interactive experiment catalogue', 'experiments.html'],
        ['Interactive experiment catalogue', 'experiments.html']
      ]],
      ['Foundations', [
        ['00 · Primitives', 'st_00_primitives.html'],
        ['Lattice', 'st_flm01.html'],
        ['FLM01 scroller', 'flm01_scroller.html'],
        ['FLM02 scroller', 'flm02_scroller.html']
      ]],
      ['Laws', [
        ['01 · Law I', 'st_01_law1.html'],
        ['02 · Law II', 'st_02_law2.html'],
        ['03 · Law III', 'st_03_law3.html'],
        ['04 · Law IV', 'st_04_law4.html']
      ]],
      ['Particles & atoms', [
        ['PPT01', 'ppt01_scroller.html'],
        ['PPT02 · 1/137', 'ppt02_scroller.html'],
        ['PPT04', 'ppt04_scroller.html'],
        ['PPT05', 'ppt05_scroller.html'],
        ['PPT06', 'ppt06_scroller.html'],
        ['APS01 · Rydberg', 'aps01_scroller.html'],
        ['APS02', 'aps02_scroller.html'],
        ['EMC01', 'emc01_scroller.html']
      ]],
      ['Gravity & worlds', [
        ['Why a ball falls', 'st_gom_gravity.html'],
        ['Magic numbers', 'st_magic_numbers.html'],
        ['Ring moons', 'st_ring_moons.html'],
        ['Paradox census', 'st_paradox_census.html']
      ]]
    ]],
    papers: ['Papers', [
      ['The path, spoken', [
        ['Complete dependency chain', 'theory.html'],
        ['For people', 'sdt-for-people.html'],
        ['Theoretical model', 'theoretical-model.html'],
        ['Inputs, rederived', 'inputs.html']
      ]],
      ['Section papers', [
        ['The Medium', 'paper-medium.html'],
        ['The Laws', 'paper-laws.html'],
        ['Topology', 'paper-topology.html'],
        ['Atomicus', 'paper-atomicus.html'],
        ['The Lab', 'paper-lab.html'],
        ['The Engine', 'paper-engine.html'],
        ['Cosmology', 'paper-cosmology.html'],
        ['Formal experiments paper', 'paper-experiments.html'],
        ['Glossary', 'paper-glossary.html']
      ]],
      ['Domain papers 01–16', [
        ['01 · Foundations', 'paper-01-foundations.html'],
        ['02 · Particle topology', 'paper-02-particle-topology.html'],
        ['03 · Electromagnetism', 'paper-03-electromagnetism.html'],
        ['04 · Atomic spectroscopy', 'paper-04-atomic-spectroscopy.html'],
        ['05 · Nuclear', 'paper-05-nuclear.html'],
        ['06 · Gravitation', 'paper-06-gravitation.html'],
        ['07 · Cosmology', 'paper-07-cosmology.html'],
        ['08 · Galactic', 'paper-08-galactic.html'],
        ['09 · Stellar', 'paper-09-stellar.html'],
        ['10 · Fluid', 'paper-10-fluid.html'],
        ['11 · Thermodynamics', 'paper-11-thermodynamics.html'],
        ['12 · Condensed matter', 'paper-12-condensed-matter.html'],
        ['13 · Quantum foundations', 'paper-13-quantum-foundations.html'],
        ['14 · Plasma & magnetism', 'paper-14-plasma-magnetism.html'],
        ['15 · Optics', 'paper-15-optics.html'],
        ['16 · Chemistry', 'paper-16-chemistry.html']
      ]]
    ]]
  };

  var MENU_BLURBS = {
    'atomicus-lab.html': 'Build nuclei from the constitutional alpha, deuteron and triton grammar.',
    'atomicus-3d.html': 'Rotate the nuclear seating model and inspect its contacts in three dimensions.',
    'nuclear-packing-sequencer.html': 'Run the packing grammar isotope by isotope.',
    'nuclear-packing-walkthrough.html': 'Follow the sequencer rules before opening the full instrument.',
    'atomicus-fission-impact.html': 'See kinetic impact flay a nuclear jacket rather than split a liquid drop.',
    'koppa-ladder.html': 'Move through the orbital gear and depth relations from particles to worlds.',
    'depth_closure_scroller.html': 'Trace depth, clocks, far-frame light speed and Shapiro delay.',
    'clearing-ladder.html': 'Climb the temperature and propagation ladder to the red–infrared wall.',
    'laws_scroller.html': 'Read the Six Laws as one illustrated mechanical sequence.',
    'solar-system.html': 'Explore planetary seats using the same koppa mechanics.',
    'celestial-three-body-solver.html': 'Run the retarded seven-cone SDT celestial solver through the shared C++/WASM core.',
    'cq06-eclipse.html': 'Inspect the eclipse investigation and its recorded outcome.',
    'benchmarks.html': 'See the current benchmark tally with evidence labels exposed.',
    'benchmarks_scroller.html': 'Walk through the benchmark chain one result at a time.',
    'investigations.html': 'Browse the active, completed, excluded and pending research programme.',
    'experiments.html': 'Search the interactive catalogue of numbered experimental specifications.',
    'experiments.html': 'Search the interactive catalogue of numbered experimental specifications.',
    'experiments.html': 'Search the interactive catalogue of numbered experimental specifications.',
    'st_00_primitives.html': 'Start with Space, Matter, Movement and the Ever-Present Now.',
    'st_flm01.html': 'Open the substrate and lattice investigation.',
    'st_gom_gravity.html': 'Follow the pressure account of why a ball falls.',
    'st_magic_numbers.html': 'See the two seating formulae behind the nuclear magic numbers.',
    'st_ring_moons.html': 'Inspect the ring-moon orbital investigation.',
    'st_paradox_census.html': 'Review the framework’s paradox and contradiction census.',
    'sdt-for-people.html': 'The theory spoken directly, without requiring the technical ledger.',
    'theory.html': 'Read the entire framework in dependency order with status, evidence and residuals exposed.',
    'theoretical-model.html': 'A compact statement of the current total model and its open debts.',
    'inputs.html': 'See every admitted input, rederivation and calibration in one place.',
    'paper-medium.html': 'The formal account of the particulate spatial medium.',
    'paper-laws.html': 'The Six Laws stated as the framework’s mechanical constitution.',
    'paper-topology.html': 'Particles, windings and closure as physical topology.',
    'paper-atomicus.html': 'The constitutional account of atoms and nuclei.',
    'paper-lab.html': 'The instruments, measurements and validation gates.',
    'paper-engine.html': 'The executable engine and its single source of numerical truth.',
    'paper-cosmology.html': 'Depth, propagation and the current cosmological claim ledger.',
    'paper-experiments.html': 'Read the formal paper defining the experimental programme and its discriminating observables.',
    'paper-glossary.html': 'Definitions, symbols and framework-specific vocabulary.'
  };

  function menuBlurb(label, href) {
    if (MENU_BLURBS[href]) return MENU_BLURBS[href];
    if (/^paper-\d\d-/.test(href)) {
      return 'Formal domain paper covering ' + label.replace(/^\d+\s*·\s*/, '').toLowerCase() + '.';
    }
    if (/_scroller\.html$/.test(href)) return 'Interactive walkthrough of ' + label + '.';
    if (/^st_\d\d_/.test(href)) return 'Investigation record and evidence status for ' + label + '.';
    return 'Open ' + label + ' and its current evidence record.';
  }

  /* ── helpers ──────────────────────────────────────────────────────────── */
  function el(tag, cls, html) {
    var n = document.createElement(tag);
    if (cls) n.className = cls;
    if (html != null) n.innerHTML = html;
    return n;
  }

  function column(title, groups, side) {
    var c = el('nav', 'sdtq-column sdtq-' + side);
    c.setAttribute('aria-label', title);

    var x = el('button', 'sdtq-close', '&times;');
    x.type = 'button';
    x.setAttribute('aria-label', 'Close ' + title);
    x.addEventListener('click', closeAll);
    c.appendChild(x);

    c.appendChild(el('h2', null, title));

    // Each group is a DROPDOWN: a disclosure button over its own link list.
    // The group holding the current page opens itself; the rest stay shut, and
    // the open/shut choice is remembered per group.
    groups.forEach(function (g, gi) {
      var key = 'grp.' + side + '.' + gi;
      var holdsHere = g[1].some(function (it) { return it[1].toLowerCase() === here; });

      var head = el('button', 'sdtq-grp', '<span>' + g[0] + '</span><i class="sdtq-chev"></i>');
      head.type = 'button';
      var body = el('div', 'sdtq-grpbody');

      g[1].forEach(function (item) {
        var a = el('a');
        a.href = item[1];
        a.appendChild(el('span', 'sdtq-item-title', item[0]));
        a.appendChild(el('p', 'sdtq-item-desc', item[2] || menuBlurb(item[0], item[1])));
        if (item[1].toLowerCase() === here) a.setAttribute('aria-current', 'page');
        body.appendChild(a);
      });

      var open = holdsHere || store.get(key, '') === 'open';
      function paint() {
        head.setAttribute('aria-expanded', open ? 'true' : 'false');
        body.setAttribute('aria-hidden', open ? 'false' : 'true');
        body.classList.toggle('sdtq-grpbody-open', open);
        body.querySelectorAll('a').forEach(function (a) { a.tabIndex = open ? 0 : -1; });
      }
      head.addEventListener('click', function (e) {
        e.stopPropagation();
        open = !open;
        store.set(key, open ? 'open' : 'shut');
        paint();
      });
      paint();

      c.appendChild(head);
      c.appendChild(body);
    });
    return c;
  }

  /* ── language ─────────────────────────────────────────────────────────────
     i18n.js used to paint its own fixed button at z-index 2000; the shell bar
     (z-index 9000, full width, top 0) buried it. The language control now lives
     IN the bar as a proper tab, and i18n.js registers its language list here.  */
  function languagePanel() {
    var p = el('div', 'sdtq-panel sdtq-langpanel');
    var api = window.SDT_I18N_API;
    if (!api) {
      p.appendChild(el('p', 'sdtq-note',
        'Translations are not loaded on this page.'));
      return p;
    }
    p.appendChild(el('h3', null, 'Language'));
    var wrap = el('div', 'sdtq-langs');
    api.langs.forEach(function (L) {
      var b = el('button', null, '<span>' + L.label + '</span><span class="tick">✓</span>');
      b.type = 'button';
      b.setAttribute('data-lang', L.code);
      if (L.code === api.current()) b.className = 'active';
      b.addEventListener('click', function (e) {
        e.stopPropagation();
        api.set(L.code);
        wrap.querySelectorAll('button').forEach(function (o) {
          o.className = (o.getAttribute('data-lang') === L.code) ? 'active' : '';
        });
      });
      wrap.appendChild(b);
    });
    p.appendChild(wrap);
    return p;
  }

  /* ── settings ─────────────────────────────────────────────────────────── */
  var store = {
    get: function (k, d) { try { return localStorage.getItem('sdt.' + k) || d; } catch (e) { return d; } },
    set: function (k, v) { try { localStorage.setItem('sdt.' + k, v); } catch (e) {} }
  };
  function pageThemeDefault() {
    var value = document.documentElement.getAttribute('data-sdt-theme-default');
    return value === 'light' || value === 'dark' ? value : '';
  }
  var APPLY = {
    theme: function (v) {
      var t = v === 'auto'
        ? (window.matchMedia && window.matchMedia('(prefers-color-scheme:dark)').matches ? 'dark' : 'light')
        : v;
      document.documentElement.setAttribute('data-theme', t);
      document.documentElement.setAttribute('data-sdt-theme', t);
      syncThemeSwitch();
    },
    text: function (v) {
      document.documentElement.style.fontSize = ({ s: '93.75%', m: '', l: '112.5%' })[v] || '';
    },
    motion: function (v) { document.documentElement.setAttribute('data-sdt-motion', v); }
  };
  var OPTS = {
    text:   [['S', 's'], ['M', 'm'], ['L', 'l']],
    motion: [['On', 'on'], ['Off', 'off']]
  };
  var reduceMotion = window.matchMedia
    && window.matchMedia('(prefers-reduced-motion: reduce)').matches;
  var DEFAULT = { theme: 'auto', text: 'm', motion: reduceMotion ? 'off' : 'on' };

  function sync(key) {
    var cur = store.get(key, DEFAULT[key]);
    document.querySelectorAll('.sdtq-seg[data-key="' + key + '"] button').forEach(function (b) {
      b.setAttribute('aria-pressed', String(b.getAttribute('data-val') === cur));
    });
  }

  function syncThemeSwitch() {
    var saved = pageThemeDefault() ? 'auto' : store.get('theme', 'auto');
    var actual = document.documentElement.getAttribute('data-theme') || 'light';
    document.querySelectorAll('.sdtq-theme-toggle').forEach(function (row) {
      var button = row.querySelector('[role="switch"]');
      var value = row.querySelector('.sdtq-theme-value');
      var state = row.querySelector('.sdtq-theme-state');
      if (button) {
        button.setAttribute('aria-checked', String(actual === 'dark'));
        button.setAttribute('aria-label', 'Use ' + (actual === 'dark' ? 'light' : 'dark') + ' theme');
      }
      if (value) value.textContent = actual === 'dark' ? 'Dark' : 'Light';
      if (state) state.textContent = saved === 'auto' ? 'Auto' : 'Manual';
    });
  }

  function themeToggle() {
    var row = el('div', 'sdtq-theme-toggle');
    row.title = 'Follows the system theme until you change it; after that the choice is manual.';
    row.appendChild(el('span', 'sdtq-theme-label', 'Theme'));
    var button = el('button', 'sdtq-theme-switch',
      '<span class="sdtq-theme-track"><i></i></span><span class="sdtq-theme-value"></span>');
    button.type = 'button';
    button.setAttribute('role', 'switch');
    button.addEventListener('click', function () {
      var actual = document.documentElement.getAttribute('data-theme') || 'light';
      var next = actual === 'dark' ? 'light' : 'dark';
      document.documentElement.removeAttribute('data-sdt-theme-default');
      store.set('theme', next);
      APPLY.theme(next);
    });
    row.appendChild(button);
    row.appendChild(el('span', 'sdtq-theme-state'));
    window.setTimeout(syncThemeSwitch, 0);
    return row;
  }

  function settings() {
    var wrap = el('div', 'sdtq-settings');
    wrap.appendChild(themeToggle());
    ['text', 'motion'].forEach(function (key) {
      var lab = el('label', null, '<span>' + key.charAt(0).toUpperCase() + key.slice(1) + '</span>');
      var seg = el('span', 'sdtq-seg');
      seg.setAttribute('data-key', key);
      OPTS[key].forEach(function (o) {
        var b = el('button', null, o[0]);
        b.type = 'button';
        b.setAttribute('data-val', o[1]);
        b.addEventListener('click', function () {
          store.set(key, o[1]);
          APPLY[key](o[1]);
          sync(key);
        });
        seg.appendChild(b);
      });
      lab.appendChild(seg);
      wrap.appendChild(lab);
    });
    return wrap;
  }

  /* ── reading register ─────────────────────────────────────────────────── */
  var REGISTER_PAGES = {
    simple: 'causal-chain-simple.html',
    layman: 'theory.html#L0',
    technical: 'causal-chain-technical.html'
  };
  var REGISTER_FROM_PAGE = {
    'causal-chain-simple.html': 'simple',
    'theory.html': 'layman',
    'causal-chain-technical.html': 'technical'
  };
  var REGISTER_LEVELS = [
    ['simple', 'Newcomers', 'A first pass with the mechanism kept visible.'],
    ['layman', 'Laymen', 'The complete dependency account with status and residuals.'],
    ['technical', 'Academics', 'Relations, evidence labels, residuals and open debts.']
  ];

  function registerSwitch() {
    var current = REGISTER_FROM_PAGE[here] || store.get('register', 'layman');
    if (REGISTER_FROM_PAGE[here]) store.set('register', current);
    document.documentElement.setAttribute('data-sdt-register', current);

    var field = el('fieldset', 'sdtq-register');
    field.setAttribute('aria-label', 'Reading version');
    field.appendChild(el('legend', 'sdtq-sr', 'Reading version'));
    field.appendChild(el('span', 'sdtq-register__lab', 'Read as'));

    REGISTER_LEVELS.forEach(function (level) {
      var label = el('label');
      label.title = level[2];
      var input = el('input');
      input.type = 'radio';
      input.name = 'sdtq-register';
      input.value = level[0];
      input.checked = level[0] === current;
      input.addEventListener('change', function () {
        if (!input.checked) return;
        store.set('register', level[0]);
        document.documentElement.setAttribute('data-sdt-register', level[0]);
        if (here !== REGISTER_PAGES[level[0]]) {
          window.location.href = REGISTER_PAGES[level[0]];
        }
      });
      label.appendChild(input);
      label.appendChild(el('span', null, level[1]));
      field.appendChild(label);
    });
    return field;
  }

  /* ── search ───────────────────────────────────────────────────────────── */
  function buildSearch() {
    var wrap = el('div', 'sdtq-search');
    var input = el('input');
    input.type = 'search';
    input.placeholder = 'search the framework...';
    input.setAttribute('aria-label', 'Search the site');
    var out = el('div', 'sdtq-results');
    out.setAttribute('role', 'listbox');
    wrap.appendChild(input);
    wrap.appendChild(out);

    var index = null, loading = false, sel = -1;

    function load() {
      if (index || loading) return;
      loading = true;
      fetch('search-index.json')
        .then(function (r) { return r.json(); })
        .then(function (j) { index = j; loading = false; if (input.value) run(); })
        .catch(function () { loading = false; index = []; });
    }

    function snippet(text, q) {
      var i = text.toLowerCase().indexOf(q);
      if (i < 0) return text.slice(0, 120);
      var s = Math.max(0, i - 45), e = Math.min(text.length, i + q.length + 85);
      var pre = (s > 0 ? '...' : '') + text.slice(s, i);
      var hit = text.slice(i, i + q.length);
      var post = text.slice(i + q.length, e) + (e < text.length ? '...' : '');
      var esc = function (t) { return t.replace(/[&<>]/g, function (c) {
        return ({ '&': '&amp;', '<': '&lt;', '>': '&gt;' })[c]; }); };
      return esc(pre) + '<mark>' + esc(hit) + '</mark>' + esc(post);
    }

    function run() {
      var q = input.value.toLowerCase().trim();
      sel = -1;
      if (q.length < 2) { out.classList.remove('sdtq-open'); out.innerHTML = ''; return; }
      if (!index) { load(); return; }

      var hits = [];
      index.forEach(function (p) {
        var score = 0, where = '';
        if (p.t && p.t.toLowerCase().indexOf(q) !== -1) { score += 100; where = p.h || p.b; }
        if (p.h && p.h.toLowerCase().indexOf(q) !== -1) { score += 40; where = where || p.h; }
        if (p.b && p.b.toLowerCase().indexOf(q) !== -1) { score += 10; where = where || p.b; }
        if (score) hits.push({ p: p, score: score, where: where || '' });
      });
      hits.sort(function (a, b) { return b.score - a.score; });
      hits = hits.slice(0, 12);

      if (!hits.length) {
        out.innerHTML = '<div class="rnone">Nothing on the lattice matches that.</div>';
      } else {
        out.innerHTML = hits.map(function (h) {
          return '<a href="' + h.p.u + '"><span class="rt">' + h.p.t +
                 '</span><span class="rs">' + snippet(h.where, q) + '</span></a>';
        }).join('');
      }
      out.classList.add('sdtq-open');
    }

    input.addEventListener('focus', load);
    input.addEventListener('input', run);
    input.addEventListener('keydown', function (e) {
      var items = out.querySelectorAll('a');
      if (e.key === 'Escape') { out.classList.remove('sdtq-open'); input.blur(); return; }
      if (!items.length) return;
      if (e.key === 'ArrowDown' || e.key === 'ArrowUp') {
        e.preventDefault();
        sel += (e.key === 'ArrowDown') ? 1 : -1;
        if (sel < 0) sel = items.length - 1;
        if (sel >= items.length) sel = 0;
        for (var i = 0; i < items.length; i++) items[i].classList.toggle('sel', i === sel);
        items[sel].scrollIntoView({ block: 'nearest' });
      } else if (e.key === 'Enter' && sel >= 0) {
        e.preventDefault();
        window.location.href = items[sel].getAttribute('href');
      }
    });
    document.addEventListener('click', function (e) {
      if (!wrap.contains(e.target)) out.classList.remove('sdtq-open');
    });
    return wrap;
  }

  /* ── open / close ─────────────────────────────────────────────────────── */
  var panels = {}, openKey = null;
  function closeAll() {
    openKey = null;
    Object.keys(panels).forEach(function (k) { panels[k].classList.remove('sdtq-open'); });
    document.querySelectorAll('[data-sdtq-target]').forEach(function (b) {
      b.setAttribute('aria-expanded', 'false');
    });
  }
  function placePanel(panel, trigger) {
    if (!panel) return;
    var right = 20;
    if (trigger && trigger.getBoundingClientRect) {
      var rect = trigger.getBoundingClientRect();
      right = Math.max(12, Math.round(window.innerWidth - rect.right));
    }
    panel.style.setProperty('--sdtq-anchor-right', right + 'px');
  }
  function toggle(key, trigger) {
    var wasOpen = (openKey === key);
    closeAll();
    if (wasOpen) return;
    reveal(key, trigger);
  }
  function reveal(key, trigger) {
    if (!panels[key]) return;
    openKey = key;
    placePanel(panels[key], trigger);
    panels[key].classList.add('sdtq-open');
    document.querySelectorAll('[data-sdtq-target="' + key + '"]').forEach(function (b) {
      b.setAttribute('aria-expanded', 'true');
    });
  }
  function fileOf(href) {
    return String(href || '').split('#')[0].split('?')[0].split('/').pop().toLowerCase();
  }
  function pulseItem(menu, href) {
    reveal(menu);
    var col = panels[menu];
    if (!col) return null;
    var want = fileOf(href);
    var link = null;
    col.querySelectorAll('a').forEach(function (a) {
      if (fileOf(a.getAttribute('href')) === want) link = a;
    });
    if (!link) return null;
    var body = link.parentElement;
    if (body && body.classList.contains('sdtq-grpbody')) {
      body.classList.add('sdtq-grpbody-open');
      body.setAttribute('aria-hidden', 'false');
      body.querySelectorAll('a').forEach(function (a) { a.tabIndex = 0; });
      var head = body.previousElementSibling;
      if (head) head.setAttribute('aria-expanded', 'true');
    }
    link.classList.remove('sdtq-pulse');
    void link.offsetWidth;
    link.classList.add('sdtq-pulse');
    if (link.scrollIntoView) link.scrollIntoView({ block: 'nearest' });
    window.setTimeout(function () { link.classList.remove('sdtq-pulse'); }, 900);
    return link;
  }
  window.SDT_SHELL = {
    open: function (menu, href) { return pulseItem(menu, href); }
  };

  /* ── build ────────────────────────────────────────────────────────────── */
  function boot() {
    ['theme', 'text', 'motion'].forEach(function (k) {
      var value = k === 'theme' && pageThemeDefault()
        ? pageThemeDefault()
        : store.get(k, DEFAULT[k]);
      APPLY[k](value);
    });

    var root = el('div', 'sdtq');
    var bar = el('div', 'sdtq-bar');
    bar.appendChild(el('div', 'sdtq-brand',
      '<a href="index.html" aria-label="SDT home"><img class="sdtq-brand-logo" src="sdt-logo.svg" alt="SDT isotope lattice"><span class="sdtq-wordmark">S<b>.</b>D<b>.</b>T<b>.</b></span></a>'));
    bar.appendChild(registerSwitch());
    bar.appendChild(buildSearch());

    var setPanel = el('div', 'sdtq-panel');
    setPanel.appendChild(settings());
    var langPanel = languagePanel();
    panels = { set: setPanel, lang: langPanel };
    Object.keys(MENUS).forEach(function (key) {
      panels[key] = column(MENUS[key][0], MENUS[key][1], key);
    });

    var tabs = el('div', 'sdtq-tabs');
    var burgers = el('div', 'sdtq-burgers');
    var TABS = [
      ['lab', 'Lab'],
      ['bench', 'Benchmarks'],
      ['inv', 'Investigations'],
      ['papers', 'Papers'],
      ['set', 'Settings']
    ];
    if (window.SDT_I18N_API) TABS.push(['lang', 'Language']);
    TABS.forEach(function (d) {
      var b = el('button', null, d[1]);
      b.type = 'button';
      b.setAttribute('data-sdtq-target', d[0]);
      b.setAttribute('aria-expanded', 'false');
      b.addEventListener('click', function (e) { e.stopPropagation(); toggle(d[0], b); });
      tabs.appendChild(b);

      var h = el('button', null, '<i></i><i></i><i></i>');
      h.type = 'button';
      h.setAttribute('data-sdtq-target', d[0]);
      h.setAttribute('aria-expanded', 'false');
      h.setAttribute('aria-label', d[1]);
      h.title = d[1];
      h.addEventListener('click', function (e) { e.stopPropagation(); toggle(d[0], h); });
      burgers.appendChild(h);
    });

    bar.appendChild(tabs);
    bar.appendChild(burgers);

    root.appendChild(bar);
    Object.keys(panels).forEach(function (k) { root.appendChild(panels[k]); });
    document.body.appendChild(root);
    document.querySelectorAll('#sdt-register-switch').forEach(function (mount) {
      mount.hidden = true;
      mount.setAttribute('aria-hidden', 'true');
    });

    ['text', 'motion'].forEach(sync);
    syncThemeSwitch();

    document.addEventListener('click', function (e) {
      if (openKey && !root.contains(e.target)) closeAll();
    });
    document.addEventListener('keydown', function (e) {
      if (e.key === 'Escape') closeAll();
    });
    /* close the flyout after following a link on small screens */
    root.addEventListener('click', function (e) {
      if (e.target.tagName === 'A' && openKey) closeAll();
    });

    if (window.matchMedia) {
      var mq = window.matchMedia('(prefers-color-scheme:dark)');
      var onChange = function () {
        if (pageThemeDefault()) APPLY.theme(pageThemeDefault());
        else if (store.get('theme', 'auto') === 'auto') APPLY.theme('auto');
      };
      mq.addEventListener ? mq.addEventListener('change', onChange)
                          : (mq.addListener && mq.addListener(onChange));
    }

    document.addEventListener('click', function (e) {
      var a = e.target.closest('[data-sdt-open]');
      if (!a || a.closest('.sdtq')) return;
      var spec = a.getAttribute('data-sdt-open') || '';
      var parts = spec.split(':');
      var menu = parts[0];
      var item = parts[1] || a.getAttribute('href');
      if (!menu || !MENUS[menu]) return;
      e.preventDefault();
      pulseItem(menu, item);
      var dest = a.getAttribute('href');
      if (!dest || dest === '#') return;
      if (dest.charAt(0) === '#') {
        var el = document.querySelector(dest);
        if (el) el.scrollIntoView({ behavior: 'smooth', block: 'start' });
        return;
      }
      window.setTimeout(function () { window.location.href = dest; }, 720);
    });

    var bootOpen = '';
    if (location.hash.indexOf('#open=') === 0) bootOpen = location.hash.slice(6);
    var q = location.search.match(/[?&]open=([^&]+)/);
    if (q) bootOpen = decodeURIComponent(q[1]);
    if (bootOpen) {
      var bp = bootOpen.split(':');
      if (bp[0] && MENUS[bp[0]]) {
        window.setTimeout(function () { pulseItem(bp[0], bp[1] || ''); }, 80);
      }
    }

    if (onWalk && 'IntersectionObserver' in window) {
      var ids = ['ix-space', 'ix-matter', 'ix-move', 'ix-now', 'ix-push', 'ix-laws', 'ix-atom', 'ix-delay', 'ix-wall', 'ix-life'];
      var io = new IntersectionObserver(function (entries) {
        entries.forEach(function (en) {
          if (!en.isIntersecting) return;
          document.querySelectorAll('.wk-rail a').forEach(function (n) { n.classList.remove('on'); });
          var rail = document.querySelector('.wk-rail a[href="#' + en.target.id + '"]');
          if (rail) rail.classList.add('on');
        });
      }, { rootMargin: '-40% 0px -50% 0px' });
      ids.forEach(function (id) {
        var s = document.getElementById(id);
        if (s) io.observe(s);
      });
    }
  }

  if (document.readyState === 'loading') document.addEventListener('DOMContentLoaded', boot);
  else boot();
})();
