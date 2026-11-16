/* ════════════════════════════════════════════════════════════════════════════
   SDT CANON — the single statement of each concept.
   James Christopher Tyndall, Melbourne.

   Every page that shows the primitives or the six laws renders them FROM HERE.
   Edit a concept once, in this file, and it changes everywhere it appears.

   Visitor path:
     index.html#ix-space   the canonical path and full statement
     atlas.html#irreducibles   preserved reference room
     st_00_primitives.html briefs, then expansion
     laws_scroller.html    briefs
     causal-chain.html     briefs
     Numbers sit on inputs.html — not a fifth primitive and not eight assumed measurements.

   Usage in a page:
       <div data-sdt-canon="primitives"></div>     the four irreducibles, as cards
       <div data-sdt-canon="primitives-brief"></div>   one line each
       <div data-sdt-canon="laws"></div>           the six laws

   Rulings recorded here (do not silently vary them):
     - The fourth primitive is "The Ever-Present Now". Not "The Present",
       not bare "Now".
     - Space is a superfluidic hypercrystal, and it can be characterised
       several ways. The fluid, crystal and relay readings below are FACETS
       OF ONE OBJECT, not competing definitions. Do not collapse them into a
       single sentence.
   ════════════════════════════════════════════════════════════════════════════ */
(function () {
  'use strict';

  var CANON = {

    /* ── the four irreducibles ────────────────────────────────────────── */
    primitives: [
      {
        ord: 'The first irreducible',
        name: 'Space',
        sdt: 'The superfluidic hypercrystal',
        brief: 'Not an emptiness things sit in — a substance, one grain thick at the floor, ' +
               'that can be crowded, thinned, and made to carry a wake. A quantised particulate ' +
               'superfluid under pressure, making all fields, carrying all radiation and producing ' +
               'all forces, including gravity. Introducing — the Spation.',
        /* one object, several characterisations — all true at once */
        facets: [
          ['As a fluid',
           'A superfluid that reconfigures at the speed of light. It flows without ' +
           'viscosity, and every particle in it is a quantised vortex.'],
          ['As a crystal',
           'Grains of one size in icosahedral 12-around-1 packing at the Planck length. ' +
           'Pack twelve around one and the fit never quite closes; because everything here ' +
           'moves, that slack gathers into shaped pockets — tetrahedral, octahedral, larger. ' +
           'Atoms keep their electrons in those pockets, and the alpha core is a tetrahedron ' +
           'for a reason.'],
          ['As a relay',
           'Contact-only transfer, nearest neighbour to nearest neighbour. Individually ' +
           'incompressible, collectively deformable. Nothing travels through it; the ' +
           'hand-off travels, and it travels at c.']
        ]
      },
      {
        ord: 'The second irreducible',
        name: 'Matter',
        sdt: 'Displacement',
        brief: 'A knot — circulation wound on itself and locked by its own winding, ' +
               'crushing the space it stands in.',
        facets: [
          ['What it is',
           'Never a cloud, never a point: a made thing, with a boundary you can measure and ' +
           'a surface that runs faster than light ever travels. The proton length is derived ' +
           'several ways — most directly the way Planck built a unique length from the ' +
           'constants he had, with koppa in place of G: R_p = 4ℏ/(m_p c).'],
          ['The one new idea',
           'Matter displaces space. The displaced grains have to go somewhere, and where they ' +
           'go — the crowding ahead, the wake behind, the shadow cast — is every force you ' +
           'have ever felt.'],
          ['What it is not',
           'Not a hole, not a void, not an absence. Matter occludes, which makes it hard, ' +
           'dense and present.']
        ]
      },
      {
        ord: 'The third irreducible',
        name: 'Movement',
        sdt: 'The one currency',
        brief: 'Relayed grain to grain — that relay is light. Wound into knots — that ' +
               'winding is matter.',
        facets: [
          ['The budget',
           'Every particle spends its whole allowance at c, always: spin and travel out of ' +
           'one purse, v_circ² + v² = c². Stand still and it all turns inward. Move, and the ' +
           'travel is paid out of the spin.'],
          ['What follows',
           'The slowed clocks, the shortened rods, E = mc², the speed nothing passes — all of ' +
           'it is this one budget, spending. Nothing dilates but the bookkeeping.'],
          ['The floor',
           'Nothing in this universe ever stops. It only changes what it spends its movement on.']
        ]
      },
      {
        ord: 'The fourth irreducible',
        name: 'The Ever-Present Now',
        sdt: 'The plane of existence',
        brief: 'It is always now. It always was. Not a moment sliding along a line — the ' +
               'plane of existence itself, with everything inside it moving.',
        facets: [
          ['Time is a tally',
           'What you call time is the tally that movement keeps: the past is the tally kept, ' +
           'the future the tally expected, and neither is a place.'],
          ['Nothing coasts on having existed',
           'Every knot pays its keep this tick; every wake is arriving now; the whole history ' +
           'of the cosmos reaches you as present pressure.'],
          ['No arrow to explain',
           'Only the plane is, and the plane does not elapse. There is no arrow of time to ' +
           'account for, because un-happening is not an operation the relay has.']
        ]
      }
    ],

    glyphs: { 'Space': '◈', 'Matter': '◉', 'Movement': '⟳', 'The Ever-Present Now': '⧖' },

    /* ── the six laws ─────────────────────────────────────────────────── */
    laws: [
      { n: 'I',  name: 'Cosmological Relay Throughput',
        one: 'The lattice is globally phase-loaded. Shell cancellation preserves the same ' +
             'throughput at every point, which is why balanced space feels like nothing.' },
      { n: 'II', name: 'The Release Cascade',
        one: 'Stored convergence is released in ordered steps, setting the pressure domains ' +
             'that stars, nuclei and atoms each operate inside.' },
      { n: 'III', name: 'Convergent Boundary Pressure',
        one: 'The universal force law. One occlusion expression — bodies blocking each ' +
             'other’s share of the convergence — covers gravity, the electric force and ' +
             'the nuclear bond alike; only the pressure domain changes.' },
      { n: 'IV', name: 'Inertial Mass from Throughput Asymmetry',
        one: 'Mass is not carried, it is commanded: the medium’s resistance to a change ' +
             'in a form’s vector. Inertial and gravitational mass are the same quantity ' +
             'because both measure the same displaced volume.' },
      { n: 'V',  name: 'The Movement Budget',
        one: 'v_circ² + v² = c². Every form spends one allowance between spinning and ' +
             'travelling, and special relativity is that ledger read carefully.' },
      { n: 'VI', name: 'Vortex Topology Quantisation',
        one: 'Particles are knots, and only some windings hold. The electron is the single ' +
             'winding; the proton is the trefoil; the stable species are the codewords that ' +
             'close.' }
    ]
  };

  /* ── renderers ──────────────────────────────────────────────────────── */
  function esc(s) {
    return String(s).replace(/[&<>]/g, function (c) {
      return ({ '&': '&amp;', '<': '&lt;', '>': '&gt;' })[c];
    });
  }

  var R = {
    primitives: function () {
      return '<div class="cn-prims">' + CANON.primitives.map(function (p) {
        return '<article class="cn-prim">' +
          '<div class="cn-prim__glyph">' + (CANON.glyphs[p.name] || '') + '</div>' +
          '<p class="cn-prim__ord">' + esc(p.ord) + '</p>' +
          '<h3 class="cn-prim__name">' + esc(p.name) + '</h3>' +
          '<p class="cn-prim__sdt">' + esc(p.sdt) + '</p>' +
          '<p class="cn-prim__brief">' + esc(p.brief) + '</p>' +
          p.facets.map(function (f) {
            return '<div class="cn-facet"><h4>' + esc(f[0]) + '</h4><p>' + esc(f[1]) + '</p></div>';
          }).join('') +
        '</article>';
      }).join('') + '</div>';
    },

    'primitives-brief': function () {
      return '<div class="cn-brief">' + CANON.primitives.map(function (p) {
        return '<div class="cn-brief__row">' +
          '<span class="cn-brief__glyph">' + (CANON.glyphs[p.name] || '') + '</span>' +
          '<span class="cn-brief__name">' + esc(p.name) + '</span>' +
          '<span class="cn-brief__sdt">' + esc(p.sdt) + '</span>' +
          '<span class="cn-brief__txt">' + esc(p.brief) + '</span>' +
        '</div>';
      }).join('') + '</div>';
    },

    laws: function () {
      return '<div class="cn-laws">' + CANON.laws.map(function (l) {
        return '<div class="cn-law">' +
          '<span class="cn-law__n">Law ' + l.n + '</span>' +
          '<h3 class="cn-law__name">' + esc(l.name) + '</h3>' +
          '<p class="cn-law__one">' + esc(l.one) + '</p>' +
        '</div>';
      }).join('') + '</div>';
    }
  };

  var CSS = '' +
    '.cn-prims{display:grid;gap:1.5rem;grid-template-columns:repeat(auto-fit,minmax(17rem,1fr));margin:2rem 0}' +
    '.cn-prim{border:1px solid var(--paper-edge,#e8e0d2);border-radius:3px;background:#fffefb;padding:1.3rem 1.4rem}' +
    '.cn-prim__glyph{font-size:1.7rem;color:var(--copper,#b07430);line-height:1}' +
    '.cn-prim__ord{font-family:"JetBrains Mono",monospace;font-size:.625rem;letter-spacing:.14em;' +
      'text-transform:uppercase;color:var(--ink-faint,#a49d92);margin:.7rem 0 .2rem}' +
    '.cn-prim__name{font-family:"Source Serif 4",Georgia,serif;font-size:1.35rem;font-weight:600;' +
      'margin:0 0 .15rem;color:var(--ink,#1e1c18);line-height:1.15}' +
    '.cn-prim__sdt{font-size:.75rem;letter-spacing:.09em;text-transform:uppercase;' +
      'color:var(--copper,#b07430);margin:0 0 .7rem}' +
    '.cn-prim__brief{color:var(--ink-soft,#3d3830);line-height:1.7;font-size:.9375rem;margin:0 0 1rem}' +
    '.cn-facet{border-left:2px solid var(--paper-edge,#e8e0d2);padding-left:.8rem;margin-top:.8rem}' +
    '.cn-facet h4{font-size:.625rem;letter-spacing:.12em;text-transform:uppercase;' +
      'color:var(--ink-faint,#a49d92);margin:0 0 .25rem;font-weight:600}' +
    '.cn-facet p{font-size:.875rem;line-height:1.65;color:var(--ink-soft,#3d3830);margin:0}' +
    '.cn-brief{margin:1.6rem 0;border-top:1px solid var(--paper-edge,#e8e0d2)}' +
    '.cn-brief__row{display:grid;grid-template-columns:2rem 9rem 12rem 1fr;gap:.9rem;align-items:baseline;' +
      'padding:.85rem .2rem;border-bottom:1px solid var(--paper-edge,#e8e0d2)}' +
    '.cn-brief__glyph{font-size:1.15rem;color:var(--copper,#b07430)}' +
    '.cn-brief__name{font-family:"Source Serif 4",Georgia,serif;font-size:1.05rem;color:var(--ink,#1e1c18)}' +
    '.cn-brief__sdt{font-size:.7rem;letter-spacing:.09em;text-transform:uppercase;color:var(--copper,#b07430)}' +
    '.cn-brief__txt{font-size:.875rem;line-height:1.65;color:var(--ink-soft,#3d3830)}' +
    '@media(max-width:820px){.cn-brief__row{grid-template-columns:1.6rem 1fr}' +
      '.cn-brief__sdt,.cn-brief__txt{grid-column:2}}' +
    '.cn-laws{display:grid;gap:1rem;margin:2rem 0}' +
    '.cn-law{border-left:2px solid var(--copper,#b07430);padding:.3rem 0 .3rem 1.1rem}' +
    '.cn-law__n{font-family:"JetBrains Mono",monospace;font-size:.65rem;letter-spacing:.14em;' +
      'text-transform:uppercase;color:var(--copper,#b07430)}' +
    '.cn-law__name{font-family:"Source Serif 4",Georgia,serif;font-size:1.15rem;font-weight:600;' +
      'margin:.15rem 0 .35rem;color:var(--ink,#1e1c18)}' +
    '.cn-law__one{font-size:.9375rem;line-height:1.7;color:var(--ink-soft,#3d3830);margin:0;max-width:44rem}';

  function mount() {
    var slots = document.querySelectorAll('[data-sdt-canon]');
    var items = document.querySelectorAll('[data-sdt-canon-item]');
    if (!slots.length && !items.length) return;
    var st = document.createElement('style');
    st.textContent = CSS;
    document.head.appendChild(st);
    Array.prototype.forEach.call(slots, function (s) {
      var key = s.getAttribute('data-sdt-canon');
      if (R[key]) s.innerHTML = R[key]();
    });
    /* per-item quotes: <p data-sdt-canon-item="Space" data-sdt-canon-part="brief"></p>
       parts: brief (default) · sdt · facets — the statement stays authored ONCE, above. */
    Array.prototype.forEach.call(items, function (s) {
      var name = s.getAttribute('data-sdt-canon-item');
      var part = s.getAttribute('data-sdt-canon-part') || 'brief';
      var p = null;
      for (var i = 0; i < CANON.primitives.length; i++)
        if (CANON.primitives[i].name === name) { p = CANON.primitives[i]; break; }
      if (!p) return;
      if (part === 'facets') {
        s.innerHTML = p.facets.map(function (f) {
          return '<div class="cn-facet"><h4>' + esc(f[0]) + '</h4><p>' + esc(f[1]) + '</p></div>';
        }).join('');
      } else {
        s.textContent = part === 'sdt' ? p.sdt : p.brief;
      }
    });
  }

  window.SDT_CANON = CANON;
  if (document.readyState === 'loading') document.addEventListener('DOMContentLoaded', mount);
  else mount();
})();
