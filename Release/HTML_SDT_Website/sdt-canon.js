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
            "ord": "The first irreducible",
            "name": "Space",
            "sdt": "The superfluidic hypercrystal",
            "brief": "SDT describes space as a particulate medium. Spations constrain material forms and transfer movement through neighbouring contacts.",
            "facets": [
                  [
                        "As a fluid",
                        "The medium is proposed to rearrange without viscosity. Collective rearrangement allows displacement while individual spations remain incompressible."
                  ],
                  [
                        "As a crystal",
                        "The lattice description concerns local packing and contact geometry. Packing constraints and defects must be distinguished from a completed dynamical model."
                  ],
                  [
                        "As a relay",
                        "Radiation is described as contact-mediated transfer at c. The contact and medium-response laws remain necessary for a quantitative microscopic account."
                  ]
            ]
      },
      {
            "ord": "The second irreducible",
            "name": "Matter",
            "sdt": "Constrained material form",
            "brief": "Matter has a boundary and displaces the surrounding medium. Spation constraint maintains the form; winding alone does not establish self-sustaining matter.",
            "facets": [
                  [
                        "Structure",
                        "The proton is assigned a continuous (2,3) trefoil structure. A geometric description specifies a path, while physical tube width and contact response require separate definitions."
                  ],
                  [
                        "Displacement",
                        "Displaced volume, geometrical envelope volume and engaged volume describe different quantities. A shared input does not make the resulting calculations independent predictions."
                  ],
                  [
                        "Boundary scale",
                        "The measured proton boundary radius and the proposed relation R_p = 4ℏ/(m_p c) have different evidential roles. Numerical agreement does not complete the derivation of the factor four."
                  ]
            ]
      },
      {
            "ord": "The third irreducible",
            "name": "Movement",
            "sdt": "Transfer and actuation",
            "brief": "Movement includes material motion and contact-mediated transfer. Available freedom describes capacity; actual movement describes actuation.",
            "facets": [
                  [
                        "The movement budget",
                        "Law V imposes v_circ² + v² = c². Increasing translation reduces the circulation component under the assumed budget."
                  ],
                  [
                        "Conditional consequences",
                        "Clock-rate and length relations require a stated mapping from the movement budget to the measuring apparatus. Algebraic closure alone is not an independent experiment."
                  ],
                  [
                        "The unresolved mechanism",
                        "Structural freedom, contact actuation and measured response remain separate until a physical law connects the quantities."
                  ]
            ]
      },
      {
            "ord": "The fourth irreducible",
            "name": "The Ever-Present Now",
            "sdt": "Present existence",
            "brief": "The Ever-Present Now names the present existence of matter, space and movement. Clocks measure accumulated physical change.",
            "facets": [
                  [
                        "Time as a count",
                        "Elapsed time is represented through counts of physical processes. Past records and future expectations do not constitute additional material locations."
                  ],
                  [
                        "Physical clocks",
                        "A clock comparison requires a specified process, trajectory and measurement protocol. The ontology alone does not supply a clock-rate prediction."
                  ],
                  [
                        "An open question",
                        "The relationship between irreversible records and reversible mathematical descriptions requires a physical account of the relay."
                  ]
            ]
      }
],

    glyphs: { 'Space': '◈', 'Matter': '◉', 'Movement': '⟳', 'The Ever-Present Now': '⧖' },

    /* ── the six laws ─────────────────────────────────────────────────── */
    laws: [
      {
            "n": "I",
            "name": "Cosmological Relay Throughput",
            "one": "Law I proposes a cosmological relay throughput. The shell construction and the physical normalisation must be assessed separately."
      },
      {
            "n": "II",
            "name": "The Release Cascade",
            "one": "Law II describes release across pressure domains. The mechanism must specify the boundary and transfer conditions for each domain."
      },
      {
            "n": "III",
            "name": "Convergent Boundary Pressure",
            "one": "Law III relates occlusion geometry to a pressure imbalance. An inverse-square factor does not independently determine the effective pressure or coupling coefficient."
      },
      {
            "n": "IV",
            "name": "Inertial Mass from Throughput Asymmetry",
            "one": "Law IV attributes inertia to the response of the medium to changing material motion. A quantitative contact-response derivation remains required."
      },
      {
            "n": "V",
            "name": "The Movement Budget",
            "one": "Law V imposes v_circ² + v² = c². The equation defines the assumed partition between circulation and translation."
      },
      {
            "n": "VI",
            "name": "Vortex Topology Quantisation",
            "one": "Law VI assigns particle structures to closed winding modes. The proton uses the (2,3) trefoil; topology alone does not establish a stability law."
      }
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
