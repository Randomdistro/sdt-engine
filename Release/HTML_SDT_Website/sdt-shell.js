/* ════════════════════════════════════════════════════════════════════════════
   SDT SITE SHELL — builds the three menus on every page.
   J. C. Harvey, Melbourne.  Pairs with sdt-shell.css.

     LEFT vertical column  — Navigation
     RIGHT vertical column — Scrollers
     TOP bar               — Settings
   ════════════════════════════════════════════════════════════════════════════ */
(function () {
  'use strict';
  if (window.__SDT_SHELL__) return;
  window.__SDT_SHELL__ = true;

  var here = (location.pathname.split('/').pop() || 'index.html').toLowerCase();
  var onAtlas = (here === 'index.html' || here === '' || here === 'atlas.html');

  /* section anchors live on the atlas; from any other page, jump back to it */
  function sec(hash) { return onAtlas ? ('#' + hash) : ('index.html#' + hash); }

  /* ── LEFT COLUMN — Navigation ─────────────────────────────────────────── */
  var NAV = [
    ['Start here', [
      ['Welcome',       'welcome.html'],
      ['For people',    'sdt-for-people.html'],
      ['Causal chain',  'causal-chain.html'],
      ['Walkthrough',   'sdt_walkthrough.html'],
      ['Life of the universe', 'universe-lifecycle.html'],
      ['Theoretical model', 'theoretical-model.html'],
      ['Gravity — why a ball', 'st_gom_gravity.html'],
      ['Atlas — home',  'index.html']
    ]],
    ['The framework', [
      ['The Medium',   sec('medium')],
      ['Six Laws',     sec('laws')],
      ['Topology',     sec('topology')],
      ['Atomicus',     sec('atomicus')],
      ['Lab',          sec('lab')],
      ['Engine',       sec('engine')],
      ['Cosmology',    sec('cosmology')],
      ['Experiments',  sec('experiments')],
      ['Glossary',     sec('glossary')]
    ]],
    ['Read', [
      ['What we assume','inputs.html'],
      ['Predictions',   'experiments.html'],
      ['Investigations','investigations.html'],
      ['Benchmarks',    'benchmarks.html'],
      ['Downloads',     'downloads.html'],
      ['Licence & cite','licence.html']
    ]],
    ['Domain papers', [
      ['01 · Foundations',        'paper-01-foundations.html'],
      ['02 · Particle topology',  'paper-02-particle-topology.html'],
      ['03 · Electromagnetism',   'paper-03-electromagnetism.html'],
      ['04 · Atomic spectroscopy','paper-04-atomic-spectroscopy.html'],
      ['05 · Nuclear',            'paper-05-nuclear.html'],
      ['06 · Gravitation',        'paper-06-gravitation.html'],
      ['07 · Cosmology',          'paper-07-cosmology.html'],
      ['08 · Galactic',           'paper-08-galactic.html'],
      ['09 · Stellar',            'paper-09-stellar.html'],
      ['10 · Fluid',              'paper-10-fluid.html'],
      ['11 · Thermodynamics',     'paper-11-thermodynamics.html'],
      ['12 · Condensed matter',   'paper-12-condensed-matter.html'],
      ['13 · Quantum foundations','paper-13-quantum-foundations.html'],
      ['14 · Plasma & magnetism', 'paper-14-plasma-magnetism.html'],
      ['15 · Optics',             'paper-15-optics.html'],
      ['16 · Chemistry',          'paper-16-chemistry.html']
    ]]
  ];

  /* ── RIGHT COLUMN — Scrollers ─────────────────────────────────────────── */
  var SCR = [
    ['Teaching sequence', [
      ['00 · Primitives',  'st_00_primitives.html'],
      ['01 · Law I',       'st_01_law1.html'],
      ['02 · Law II',      'st_02_law2.html'],
      ['03 · Law III',     'st_03_law3.html'],
      ['04 · Law IV',      'st_04_law4.html'],
      ['Lattice',          'st_flm01.html'],
      ['Gravity',          'st_gom_gravity.html'],
      ['Magic numbers',    'st_magic_numbers.html'],
      ['Ring moons',       'st_ring_moons.html']
    ]],
    ['Scrollthroughs', [
      ['The six laws',     'laws_scroller.html'],
      ['Depth closure',    'depth_closure_scroller.html'],
      ['Benchmarks',       'benchmarks_scroller.html'],
      ['The paradox census','st_paradox_census.html']
    ]],
    ['Nuclear', [
      ['Packing sequencer', 'nuclear-packing-sequencer.html'],
      ['Sequencer walkthrough', 'nuclear-packing-walkthrough.html'],
      ['Atomicus lab',        'atomicus-lab-subdued.html'],
      ['Fission — flay, not split', 'atomicus-fission-impact.html']
    ]],
    ['More', [
      ['Causal chain · technical', 'causal-chain-technical.html'],
      ['Causal chain · simplified', 'causal-chain-simple.html'],
      ['The koppa ladder', 'koppa-ladder.html'],
      ['The wall in the infrared', 'clearing-ladder.html'],
      ['Life of the universe', 'universe-lifecycle.html'],
      ['Eclipse',          'cq06-eclipse.html'],
      ['Solar system',     'solar-system.html']
    ]]
  ];

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
        var a = el('a', null, item[0]);
        a.href = item[1];
        if (item[1].toLowerCase() === here) a.setAttribute('aria-current', 'page');
        body.appendChild(a);
      });

      var open = holdsHere || store.get(key, '') === 'open';
      function paint() {
        head.setAttribute('aria-expanded', open ? 'true' : 'false');
        body.style.display = open ? 'block' : 'none';
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
  var APPLY = {
    theme: function (v) {
      var t = v === 'auto'
        ? (window.matchMedia && window.matchMedia('(prefers-color-scheme:dark)').matches ? 'dark' : 'light')
        : v;
      document.documentElement.setAttribute('data-theme', t);
      document.documentElement.setAttribute('data-sdt-theme', t);
    },
    text: function (v) {
      document.documentElement.style.fontSize = ({ s: '93.75%', m: '', l: '112.5%' })[v] || '';
    },
    motion: function (v) { document.documentElement.setAttribute('data-sdt-motion', v); }
  };
  var OPTS = {
    theme:  [['Auto', 'auto'], ['Light', 'light'], ['Dark', 'dark']],
    text:   [['S', 's'], ['M', 'm'], ['L', 'l']],
    motion: [['On', 'on'], ['Off', 'off']]
  };
  var DEFAULT = { theme: 'auto', text: 'm', motion: 'on' };

  function sync(key) {
    var cur = store.get(key, DEFAULT[key]);
    document.querySelectorAll('.sdtq-seg[data-key="' + key + '"] button').forEach(function (b) {
      b.setAttribute('aria-pressed', String(b.getAttribute('data-val') === cur));
    });
  }

  function settings() {
    var wrap = el('div', 'sdtq-settings');
    ['theme', 'text', 'motion'].forEach(function (key) {
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
  function toggle(key) {
    var wasOpen = (openKey === key);
    closeAll();
    if (wasOpen) return;
    openKey = key;
    panels[key].classList.add('sdtq-open');
    document.querySelectorAll('[data-sdtq-target="' + key + '"]').forEach(function (b) {
      b.setAttribute('aria-expanded', 'true');
    });
  }

  /* ── build ────────────────────────────────────────────────────────────── */
  function boot() {
    ['theme', 'text', 'motion'].forEach(function (k) { APPLY[k](store.get(k, DEFAULT[k])); });

    var root = el('div', 'sdtq');
    var bar = el('div', 'sdtq-bar');
    bar.appendChild(el('div', 'sdtq-brand',
      '<a href="index.html">S<span>.</span>D<span>.</span>T<span>.</span></a>'));
    bar.appendChild(buildSearch());
    bar.appendChild(settings());

    var left = column('Navigation', NAV, 'left');
    var right = column('Scrollers', SCR, 'right');
    var setPanel = el('div', 'sdtq-panel');
    setPanel.appendChild(settings());
    var langPanel = languagePanel();
    panels = { nav: left, set: setPanel, scr: right, lang: langPanel };

    var tabs = el('div', 'sdtq-tabs');
    var burgers = el('div', 'sdtq-burgers');
    var TABS = [['nav', 'Navigation'], ['set', 'Settings'], ['scr', 'Scrollers']];
    if (window.SDT_I18N_API) TABS.push(['lang', 'Language']);
    TABS.forEach(function (d) {
      var b = el('button', null, d[1]);
      b.type = 'button';
      b.setAttribute('data-sdtq-target', d[0]);
      b.setAttribute('aria-expanded', 'false');
      b.addEventListener('click', function (e) { e.stopPropagation(); toggle(d[0]); });
      tabs.appendChild(b);

      var h = el('button', null, '<i></i><i></i><i></i>');
      h.type = 'button';
      h.setAttribute('data-sdtq-target', d[0]);
      h.setAttribute('aria-expanded', 'false');
      h.setAttribute('aria-label', d[1]);
      h.title = d[1];
      h.addEventListener('click', function (e) { e.stopPropagation(); toggle(d[0]); });
      burgers.appendChild(h);
    });

    bar.appendChild(tabs);
    bar.appendChild(burgers);

    root.appendChild(bar);
    root.appendChild(left);
    root.appendChild(right);
    root.appendChild(setPanel);
    root.appendChild(langPanel);
    document.body.appendChild(root);

    ['theme', 'text', 'motion'].forEach(sync);

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
      var onChange = function () { if (store.get('theme', 'auto') === 'auto') APPLY.theme('auto'); };
      mq.addEventListener ? mq.addEventListener('change', onChange)
                          : (mq.addListener && mq.addListener(onChange));
    }

    /* highlight the atlas section currently in view */
    if (onAtlas && 'IntersectionObserver' in window) {
      var ids = ['medium', 'laws', 'topology', 'atomicus', 'lab', 'engine', 'cosmology', 'experiments', 'glossary'];
      var links = {};
      ids.forEach(function (id) {
        var a = left.querySelector('a[href="#' + id + '"]');
        if (a) links[id] = a;
      });
      var io = new IntersectionObserver(function (entries) {
        entries.forEach(function (en) {
          if (!en.isIntersecting) return;
          Object.keys(links).forEach(function (k) { links[k].classList.remove('sdtq-active'); });
          if (links[en.target.id]) links[en.target.id].classList.add('sdtq-active');
        });
      }, { rootMargin: '-45% 0px -50% 0px' });
      ids.forEach(function (id) {
        var s = document.getElementById(id);
        if (s) io.observe(s);
      });
    }
  }

  if (document.readyState === 'loading') document.addEventListener('DOMContentLoaded', boot);
  else boot();
})();
