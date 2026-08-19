/* ════════════════════════════════════════════════════════════════════════════
   SPATIAL DISPLACEMENT THEORY — Main Script
   ════════════════════════════════════════════════════════════════════════════ */

(function () {
  "use strict";
  window.__SDT_LOCAL_MOTION_CONTROL__ = true;

  /* ── Element Data (Z, Symbol, Name, most-stable A) ──────────────────────── */
  const ELEMENTS = [
    [1,"H","Hydrogen",1],[2,"He","Helium",4],[3,"Li","Lithium",7],
    [4,"Be","Beryllium",9],[5,"B","Boron",11],[6,"C","Carbon",12],
    [7,"N","Nitrogen",14],[8,"O","Oxygen",16],[9,"F","Fluorine",19],
    [10,"Ne","Neon",20],[11,"Na","Sodium",23],[12,"Mg","Magnesium",24],
    [13,"Al","Aluminium",27],[14,"Si","Silicon",28],[15,"P","Phosphorus",31],
    [16,"S","Sulfur",32],[17,"Cl","Chlorine",35],[18,"Ar","Argon",40],
    [19,"K","Potassium",39],[20,"Ca","Calcium",40],[21,"Sc","Scandium",45],
    [22,"Ti","Titanium",48],[23,"V","Vanadium",51],[24,"Cr","Chromium",52],
    [25,"Mn","Manganese",55],[26,"Fe","Iron",56],[27,"Co","Cobalt",59],
    [28,"Ni","Nickel",58],[29,"Cu","Copper",63],[30,"Zn","Zinc",64],
    [31,"Ga","Gallium",69],[32,"Ge","Germanium",74],[33,"As","Arsenic",75],
    [34,"Se","Selenium",80],[35,"Br","Bromine",79],[36,"Kr","Krypton",84],
    [37,"Rb","Rubidium",85],[38,"Sr","Strontium",88],[39,"Y","Yttrium",89],
    [40,"Zr","Zirconium",90],[41,"Nb","Niobium",93],[42,"Mo","Molybdenum",98],
    [43,"Tc","Technetium",98],[44,"Ru","Ruthenium",102],[45,"Rh","Rhodium",103],
    [46,"Pd","Palladium",106],[47,"Ag","Silver",107],[48,"Cd","Cadmium",114],
    [49,"In","Indium",115],[50,"Sn","Tin",120],[51,"Sb","Antimony",121],
    [52,"Te","Tellurium",130],[53,"I","Iodine",127],[54,"Xe","Xenon",132],
    [55,"Cs","Caesium",133],[56,"Ba","Barium",138],[57,"La","Lanthanum",139],
    [58,"Ce","Cerium",140],[59,"Pr","Praseodymium",141],[60,"Nd","Neodymium",142],
    [61,"Pm","Promethium",145],[62,"Sm","Samarium",152],[63,"Eu","Europium",153],
    [64,"Gd","Gadolinium",158],[65,"Tb","Terbium",159],[66,"Dy","Dysprosium",164],
    [67,"Ho","Holmium",165],[68,"Er","Erbium",166],[69,"Tm","Thulium",169],
    [70,"Yb","Ytterbium",174],[71,"Lu","Lutetium",175],[72,"Hf","Hafnium",180],
    [73,"Ta","Tantalum",181],[74,"W","Tungsten",184],[75,"Re","Rhenium",187],
    [76,"Os","Osmium",192],[77,"Ir","Iridium",193],[78,"Pt","Platinum",195],
    [79,"Au","Gold",197],[80,"Hg","Mercury",202],[81,"Tl","Thallium",205],
    [82,"Pb","Lead",208],[83,"Bi","Bismuth",209],[84,"Po","Polonium",209],
    [85,"At","Astatine",210],[86,"Rn","Radon",222],[87,"Fr","Francium",223],
    [88,"Ra","Radium",226],[89,"Ac","Actinium",227],[90,"Th","Thorium",232],
    [91,"Pa","Protactinium",231],[92,"U","Uranium",238]
  ];

  /* Compute grammar */
  function grammar(Z, A) {
    if (Z < 2) return { nd: 0, nt: 0, valid: false };
    const nt = A - 2 * Z;
    const nd = 3 * Z - A - 2;
    return { nd, nt, valid: nd >= 0 && nt >= 0 };
  }

  /* ── Scrolled nav ───────────────────────────────────────────────────────── */
  const nav = document.getElementById("nav");
  let lastScroll = 0;
  function onScroll() {
    const y = window.scrollY;
    nav.classList.toggle("nav--scrolled", y > 60);
    lastScroll = y;
  }
  window.addEventListener("scroll", onScroll, { passive: true });
  onScroll();

  /* ── Reveal on scroll ───────────────────────────────────────────────────── */
  const revealEls = document.querySelectorAll(".reveal, .reveal-stagger");
  const revealObs = new IntersectionObserver((entries) => {
    entries.forEach(e => {
      if (e.isIntersecting) {
        e.target.classList.add(
          e.target.classList.contains("reveal-stagger")
            ? "reveal-stagger--visible"
            : "reveal--visible"
        );
        revealObs.unobserve(e.target);
      }
    });
  }, { threshold: 0.12 });
  revealEls.forEach(el => revealObs.observe(el));

  /* ── Hubble bar animation ───────────────────────────────────────────────── */
  const hubbleBars = document.querySelectorAll(".hubble-bar__fill");
  const hubbleObs = new IntersectionObserver((entries) => {
    entries.forEach(e => {
      if (e.isIntersecting) {
        const w = e.target.getAttribute("data-w");
        e.target.style.width = w + "%";
        hubbleObs.unobserve(e.target);
      }
    });
  }, { threshold: 0.5 });
  hubbleBars.forEach(el => {
    el.style.width = "0%";
    hubbleObs.observe(el);
  });

  const stillFrames = new Set();
  ["pointerdown", "input", "change", "click"].forEach(type => {
    document.addEventListener(type, () => stillFrames.clear(), { passive: true });
  });

  function motionEnabled(element) {
    if (document.hidden) return false;
    const rect = element.getBoundingClientRect();
    const visible = (
      rect.bottom >= 0
      && rect.top <= window.innerHeight
      && rect.right >= 0
      && rect.left <= window.innerWidth
    );
    if (!visible) return false;
    const setting = document.documentElement.getAttribute("data-sdt-motion");
    const off =
      setting === "off"
      || (
        setting == null
        && window.matchMedia("(prefers-reduced-motion: reduce)").matches
      );
    if (off) {
      if (stillFrames.has(element)) return false;
      stillFrames.add(element);
      return true;
    }
    stillFrames.delete(element);
    return true;
  }

  document.querySelectorAll("iframe[data-sdt-visibility]").forEach(frame => {
    const sendVisibility = visible => {
      frame.contentWindow?.postMessage(
        { type: "sdt-visibility", visible },
        window.location.origin
      );
    };
    const observer = new IntersectionObserver(entries => {
      entries.forEach(entry => sendVisibility(entry.isIntersecting));
    }, { threshold: 0.01 });
    frame.addEventListener("load", () => {
      const rect = frame.getBoundingClientRect();
      sendVisibility(rect.bottom >= 0 && rect.top <= window.innerHeight);
    });
    observer.observe(frame);
  });


  /* ════════════════════════════════════════════════════════════════════════
     LATTICE CANVAS — Subtle background animation
     ════════════════════════════════════════════════════════════════════════ */
  const latticeCanvas = document.getElementById("latticeCanvas");
  if (latticeCanvas) {
    const ctx = latticeCanvas.getContext("2d");
    let w, h, cols, rows;
    const spacing = 40;
    let time = 0;

    function resizeLattice() {
      const r = window.devicePixelRatio || 1;
      const rect = latticeCanvas.parentElement.getBoundingClientRect();
      w = rect.width;
      h = rect.height;
      latticeCanvas.width = w * r;
      latticeCanvas.height = h * r;
      latticeCanvas.style.width = w + "px";
      latticeCanvas.style.height = h + "px";
      ctx.setTransform(r, 0, 0, r, 0, 0);
      cols = Math.ceil(w / spacing) + 2;
      rows = Math.ceil(h / spacing) + 2;
    }

    function drawLattice() {
      if (motionEnabled(latticeCanvas)) {
        ctx.clearRect(0, 0, w, h);
        time += 0.003;

        for (let i = 0; i < cols; i++) {
          for (let j = 0; j < rows; j++) {
            const x = i * spacing;
            const y = j * spacing;
            const dx = Math.sin(time + i * 0.3 + j * 0.2) * 2.5;
            const dy = Math.cos(time + j * 0.3 + i * 0.15) * 2.5;

            const cx = w / 2;
            const cy = h / 2;
            const dist = Math.sqrt((x - cx) ** 2 + (y - cy) ** 2);
            const maxDist = Math.sqrt(cx * cx + cy * cy);
            const fade = 1 - Math.min(dist / (maxDist * 0.8), 1);
            const alpha = fade * 0.35;

            if (alpha > 0.01) {
              ctx.beginPath();
              ctx.arc(x + dx, y + dy, 1.2, 0, Math.PI * 2);
              ctx.fillStyle = `rgba(176, 116, 48, ${alpha})`;
              ctx.fill();
            }
          }
        }
      }
      requestAnimationFrame(drawLattice);
    }

    resizeLattice();
    window.addEventListener("resize", resizeLattice);
    drawLattice();
  }


  /* ════════════════════════════════════════════════════════════════════════
     PARTICLE TOPOLOGY CANVASES
     ════════════════════════════════════════════════════════════════════════ */

  function drawParticle(canvasId, type) {
    const canvas = document.getElementById(canvasId);
    if (!canvas) return;
    const ctx = canvas.getContext("2d");
    const r = window.devicePixelRatio || 1;
    const size = 160;
    canvas.width = size * r;
    canvas.height = size * r;
    canvas.style.width = size + "px";
    canvas.style.height = size + "px";
    ctx.setTransform(r, 0, 0, r, 0, 0);

    const cx = size / 2, cy = size / 2;
    let t = 0;

    function draw() {
      if (!motionEnabled(canvas)) {
        requestAnimationFrame(draw);
        return;
      }
      ctx.clearRect(0, 0, size, size);
      t += 0.012;

      if (type === "neutrino") {
        // Open winding — a drifting sinusoidal path
        ctx.beginPath();
        ctx.strokeStyle = "rgba(176, 116, 48, 0.25)";
        ctx.lineWidth = 1.5;
        for (let i = 0; i < 200; i++) {
          const frac = i / 200;
          const x = 20 + frac * (size - 40);
          const y = cy + Math.sin(frac * Math.PI * 4 + t) * 25 * (1 - Math.abs(frac - 0.5) * 1.2);
          i === 0 ? ctx.moveTo(x, y) : ctx.lineTo(x, y);
        }
        ctx.stroke();

        // Faint glow dot at leading edge
        const lx = 20 + (((t * 30) % (size - 40)));
        const ly = cy + Math.sin((lx - 20) / (size - 40) * Math.PI * 4 + t) * 25 * (1 - Math.abs((lx - 20) / (size - 40) - 0.5) * 1.2);
        ctx.beginPath();
        ctx.arc(lx, ly, 3, 0, Math.PI * 2);
        ctx.fillStyle = "rgba(176, 116, 48, 0.5)";
        ctx.fill();

      } else if (type === "electron") {
        // Torus cross-section — a circle with circulating dots
        const R = 36;
        const tubeR = 14;

        // Draw torus outline
        ctx.strokeStyle = "rgba(74, 109, 130, 0.2)";
        ctx.lineWidth = 1;
        ctx.beginPath();
        for (let i = 0; i <= 100; i++) {
          const a = (i / 100) * Math.PI * 2;
          const x = cx + (R + tubeR * Math.cos(a * 3 + t)) * Math.cos(a);
          const y = cy + (R + tubeR * Math.cos(a * 3 + t)) * Math.sin(a) * 0.45;
          i === 0 ? ctx.moveTo(x, y) : ctx.lineTo(x, y);
        }
        ctx.stroke();

        // Inner ring
        ctx.beginPath();
        ctx.strokeStyle = "rgba(74, 109, 130, 0.12)";
        for (let i = 0; i <= 100; i++) {
          const a = (i / 100) * Math.PI * 2;
          const x = cx + (R - tubeR * Math.cos(a * 3 + t)) * Math.cos(a);
          const y = cy + (R - tubeR * Math.cos(a * 3 + t)) * Math.sin(a) * 0.45;
          i === 0 ? ctx.moveTo(x, y) : ctx.lineTo(x, y);
        }
        ctx.stroke();

        // Circulating points
        for (let i = 0; i < 8; i++) {
          const a = (i / 8) * Math.PI * 2 + t * 1.5;
          const x = cx + R * Math.cos(a);
          const y = cy + R * Math.sin(a) * 0.45;
          ctx.beginPath();
          ctx.arc(x, y, 2.5, 0, Math.PI * 2);
          ctx.fillStyle = `rgba(74, 109, 130, ${0.3 + 0.3 * Math.sin(a)})`;
          ctx.fill();
        }

      } else if (type === "proton") {
        // Trefoil knot — (2,3) torus knot
        const R = 34, r2 = 16;

        ctx.strokeStyle = "rgba(176, 116, 48, 0.3)";
        ctx.lineWidth = 1.8;
        ctx.beginPath();
        for (let i = 0; i <= 360; i++) {
          const a = (i / 360) * Math.PI * 2;
          const rr = R + r2 * Math.cos(3 * a + t);
          const x = cx + rr * Math.cos(2 * a);
          const y = cy + rr * Math.sin(2 * a) * 0.65;
          i === 0 ? ctx.moveTo(x, y) : ctx.lineTo(x, y);
        }
        ctx.stroke();

        // Second pass — slight offset for depth
        ctx.strokeStyle = "rgba(176, 116, 48, 0.12)";
        ctx.lineWidth = 1;
        ctx.beginPath();
        for (let i = 0; i <= 360; i++) {
          const a = (i / 360) * Math.PI * 2;
          const rr = R + r2 * Math.cos(3 * a + t + 0.5);
          const x = cx + rr * Math.cos(2 * a) + 3;
          const y = cy + rr * Math.sin(2 * a) * 0.65 + 2;
          i === 0 ? ctx.moveTo(x, y) : ctx.lineTo(x, y);
        }
        ctx.stroke();

        // Circulating points on the knot
        for (let i = 0; i < 6; i++) {
          const a = (i / 6) * Math.PI * 2 + t * 0.8;
          const rr = R + r2 * Math.cos(3 * a + t);
          const x = cx + rr * Math.cos(2 * a);
          const y = cy + rr * Math.sin(2 * a) * 0.65;
          ctx.beginPath();
          ctx.arc(x, y, 2, 0, Math.PI * 2);
          ctx.fillStyle = `rgba(176, 116, 48, ${0.4 + 0.3 * Math.sin(a * 2)})`;
          ctx.fill();
        }
      }
      requestAnimationFrame(draw);
    }
    draw();
  }

  drawParticle("neutrinoCanvas", "neutrino");
  drawParticle("electronCanvas", "electron");
  drawParticle("protonCanvas", "proton");


  /* ════════════════════════════════════════════════════════════════════════
     ATOMICUS — Nuclear Construction Map
     Three modes: grammar (default), magnetic character, EC lineage
     ════════════════════════════════════════════════════════════════════════ */

  const atomCanvas = document.getElementById("atomicusCanvas");
  if (atomCanvas) {
    const ctx = atomCanvas.getContext("2d");
    const dpr = window.devicePixelRatio || 1;
    let cw, ch;
    let viewMode = "grammar"; // "grammar" | "magnetic" | "lineage"

    /* Known EC isotopes (Z) — elements with common EC-decaying isotopes
       These have He-3 cores (incomplete tetrahedra) in SDT grammar */
    const EC_ELEMENTS = new Set([
      4,  // Be-7
      18, // Ar-37
      19, // K-40 (partial EC)
      23, // V-49
      24, // Cr-51
      25, // Mn-54
      26, // Fe-55
      27, // Co-57
      28, // Ni-56
      29, // Cu-64
      30, // Zn-65
      31, // Ga-67
      32, // Ge-68
      33, // As-73
      34, // Se-75
      37, // Rb-83
      38, // Sr-85
      39, // Y-88
      40, // Zr-88
      42, // Mo-93
      43, // Tc-97
      44, // Ru-97
      45, // Rh-100
      46, // Pd-100
      47, // Ag-106
      48, // Cd-109
      49, // In-111
      50, // Sn-113
      51, // Sb-119
      52, // Te-123
      53, // I-125
      55, // Cs-131
      56, // Ba-133
      57, // La-137
      58, // Ce-139
      61, // Pm-145
      62, // Sm-145
      63, // Eu-150
      64, // Gd-153
      65, // Tb-157
      66, // Dy-159
      67, // Ho-163
      68, // Er-165
      69, // Tm-168
      70, // Yb-169
      71, // Lu-174
      72, // Hf-175
      73, // Ta-179
      74, // W-181
      75, // Re-183
      76, // Os-185
      77, // Ir-192
      78, // Pt-193
      79, // Au-195
      80, // Hg-194
      81, // Tl-201
      82, // Pb-205
      83, // Bi-207
    ]);

    /* Ferromagnetic / strongly magnetic elements (by Z) */
    const FERROMAGNETIC = new Set([26, 27, 28]); // Fe, Co, Ni
    const PARAMAGNETIC = new Set([
      3,13,21,22,23,24,25,29,39,40,41,42,44,45,46,
      57,58,59,60,62,63,64,65,66,67,68,69,70,71,90,91,92
    ]);

    // Computed element grammar data
    const elData = ELEMENTS.map(([Z, sym, name, A]) => {
      const g = grammar(Z, A);
      const isEC = EC_ELEMENTS.has(Z);
      // EC grammar: He-3 core → nt_ec = A - 2Z + 1, nd_ec = 3Z - A - 3
      const nt_ec = isEC ? A - 2 * Z + 1 : 0;
      const nd_ec = isEC ? 3 * Z - A - 3 : 0;
      const ecValid = isEC && nt_ec >= 0 && nd_ec >= 0;
      let magClass = "diamagnetic";
      if (FERROMAGNETIC.has(Z)) magClass = "ferromagnetic";
      else if (PARAMAGNETIC.has(Z)) magClass = "paramagnetic";

      return {
        Z, sym, name, A, ...g,
        tritonFrac: g.valid ? g.nt / Math.max(g.nd + g.nt, 1) : 0,
        isEC, nt_ec, nd_ec, ecValid, magClass
      };
    }).filter(e => e.valid);

    const maxNd = Math.max(...elData.map(e => e.nd));
    const maxNt = Math.max(...elData.map(e => e.nt));

    let hoveredEl = null;
    let selectedEl = elData.find(e => e.Z === 26); // Fe default

    /* Mode toggle buttons */
    const modeBar = document.getElementById("atomicusMode");
    if (modeBar) {
      modeBar.addEventListener("click", (e) => {
        const btn = e.target.closest("[data-mode]");
        if (!btn) return;
        modeBar.querySelectorAll(".exp-cat").forEach(b => b.classList.remove("exp-cat--active"));
        btn.classList.add("exp-cat--active");
        viewMode = btn.getAttribute("data-mode");
        drawAtomicus();
      });
    }

    function resizeAtomCanvas() {
      const rect = atomCanvas.parentElement.getBoundingClientRect();
      cw = rect.width;
      ch = Math.max(500, cw * 0.56);
      atomCanvas.width = cw * dpr;
      atomCanvas.height = ch * dpr;
      atomCanvas.style.width = cw + "px";
      atomCanvas.style.height = ch + "px";
      ctx.setTransform(dpr, 0, 0, dpr, 0, 0);
    }

    function elPos(el) {
      const pad = 60;
      const x = pad + (el.nd / (maxNd + 1)) * (cw - pad * 2);
      const y = pad + (el.nt / (maxNt + 1)) * (ch - pad * 2);
      return { x, y };
    }

    // Color by triton fraction (grammar mode default)
    function elColorGrammar(el, alpha) {
      const f = el.tritonFrac;
      if (el.Z === 79) return `rgba(212, 160, 92, ${alpha})`;
      if (f >= 0.5) {
        const t = (f - 0.5) / 0.5;
        const r = Math.round(194 + t * 30);
        const g = Math.round(122 - t * 40);
        const b = Math.round(138 - t * 20);
        return `rgba(${r},${g},${b},${alpha})`;
      } else {
        const t = f / 0.5;
        const r = Math.round(74 + t * 102);
        const g2 = Math.round(109 + t * 7);
        const b = Math.round(130 - t * 82);
        return `rgba(${r},${g2},${b},${alpha})`;
      }
    }

    // Color by magnetic character
    function elColorMagnetic(el, alpha) {
      if (el.magClass === "ferromagnetic") return `rgba(220, 80, 60, ${alpha})`;
      if (el.magClass === "paramagnetic") return `rgba(190, 130, 60, ${alpha})`;
      return `rgba(120, 140, 155, ${alpha})`; // diamagnetic
    }

    // Color by lineage (α-core vs EC)
    function elColorLineage(el, alpha) {
      if (el.isEC) return `rgba(74, 109, 130, ${alpha})`;  // He-3 core — steel blue
      return `rgba(176, 116, 48, ${alpha})`;                // α-core — copper
    }

    function elColor(el, alpha) {
      if (viewMode === "magnetic") return elColorMagnetic(el, alpha);
      if (viewMode === "lineage") return elColorLineage(el, alpha);
      return elColorGrammar(el, alpha);
    }

    function drawAtomicus() {
      ctx.clearRect(0, 0, cw, ch);
      const pad = 60;

      // Axis labels
      ctx.font = "500 11px 'Inter', sans-serif";
      ctx.fillStyle = "#a49d92";
      ctx.textAlign = "center";
      ctx.fillText("DEUTERON COUNT  n\u2084  →", cw / 2, ch - 12);

      ctx.save();
      ctx.translate(16, ch / 2);
      ctx.rotate(-Math.PI / 2);
      ctx.fillText("TRITON COUNT  n\u209C  →", 0, 0);
      ctx.restore();

      // Faint grid lines
      ctx.strokeStyle = "rgba(200, 193, 182, 0.15)";
      ctx.lineWidth = 0.5;

      for (let nt = 0; nt <= maxNt; nt += 5) {
        const y = pad + (nt / (maxNt + 1)) * (ch - pad * 2);
        ctx.beginPath(); ctx.moveTo(pad, y); ctx.lineTo(cw - pad, y); ctx.stroke();
        if (nt % 10 === 0) {
          ctx.fillStyle = "#c8c1b6"; ctx.font = "400 9px 'JetBrains Mono', monospace";
          ctx.textAlign = "right"; ctx.fillText(nt.toString(), pad - 8, y + 3);
        }
      }
      for (let nd = 0; nd <= maxNd; nd += 5) {
        const x = pad + (nd / (maxNd + 1)) * (cw - pad * 2);
        ctx.beginPath(); ctx.moveTo(x, pad); ctx.lineTo(x, ch - pad); ctx.stroke();
        if (nd % 10 === 0) {
          ctx.fillStyle = "#c8c1b6"; ctx.font = "400 9px 'JetBrains Mono', monospace";
          ctx.textAlign = "center"; ctx.fillText(nd.toString(), x, pad - 8);
        }
      }

      // Golden Boundary diagonal
      ctx.strokeStyle = "rgba(176, 116, 48, 0.2)"; ctx.lineWidth = 1;
      ctx.setLineDash([6, 4]);
      ctx.beginPath();
      const maxCommon = Math.min(maxNd, maxNt);
      const gx1 = pad, gy1 = pad;
      const gx2 = pad + (maxCommon / (maxNd + 1)) * (cw - pad * 2);
      const gy2 = pad + (maxCommon / (maxNt + 1)) * (ch - pad * 2);
      ctx.moveTo(gx1, gy1); ctx.lineTo(gx2, gy2); ctx.stroke();
      ctx.setLineDash([]);

      // Diagonal label
      ctx.save();
      const midx = (gx1 + gx2) / 2, midy = (gy1 + gy2) / 2;
      const angle = Math.atan2(gy2 - gy1, gx2 - gx1);
      ctx.translate(midx, midy); ctx.rotate(angle);
      ctx.fillStyle = "rgba(176, 116, 48, 0.35)";
      ctx.font = "italic 500 10px 'Source Serif 4', 'Georgia', serif";
      ctx.textAlign = "center";
      ctx.fillText("n_t = n_d  (Golden Boundary)", 0, -8);
      ctx.restore();

      // Z-order connection curves
      ctx.strokeStyle = "rgba(200, 193, 182, 0.1)"; ctx.lineWidth = 0.7;
      for (let i = 1; i < elData.length; i++) {
        const a = elPos(elData[i - 1]), b = elPos(elData[i]);
        const mx = (a.x + b.x) / 2, my = (a.y + b.y) / 2;
        const dx = b.x - a.x, dy = b.y - a.y;
        ctx.beginPath(); ctx.moveTo(a.x, a.y);
        ctx.quadraticCurveTo(mx - dy * 0.15, my + dx * 0.15, b.x, b.y);
        ctx.stroke();
      }

      // Lineage connections (same n_t)
      const byNt = {};
      elData.forEach(el => { if (!byNt[el.nt]) byNt[el.nt] = []; byNt[el.nt].push(el); });
      Object.values(byNt).forEach(family => {
        if (family.length < 2) return;
        family.sort((a, b) => a.nd - b.nd);
        ctx.strokeStyle = "rgba(74, 109, 130, 0.06)"; ctx.lineWidth = 0.5;
        ctx.beginPath();
        family.forEach((el, i) => { const p = elPos(el); i === 0 ? ctx.moveTo(p.x, p.y) : ctx.lineTo(p.x, p.y); });
        ctx.stroke();
      });

      /* ── Mode-specific overlays ──────────────────────────────── */

      if (viewMode === "magnetic") {
        // Draw magnetic field lines radiating from ferromagnetic elements
        [26, 27, 28].forEach(z => {
          const el = elData.find(e => e.Z === z);
          if (!el) return;
          const p = elPos(el);
          // Concentric rings representing magnetic field strength
          for (let ring = 1; ring <= 4; ring++) {
            ctx.beginPath();
            ctx.arc(p.x, p.y, 10 + ring * 12, 0, Math.PI * 2);
            ctx.strokeStyle = `rgba(220, 80, 60, ${0.12 - ring * 0.025})`;
            ctx.lineWidth = 1;
            ctx.stroke();
          }
          // "Magnetic" label
          ctx.font = "600 9px 'Inter', sans-serif";
          ctx.fillStyle = "rgba(220, 80, 60, 0.6)";
          ctx.textAlign = "center";
          ctx.fillText("FERROMAGNETIC", p.x, p.y + 28);
        });

        // Triton-magnetic axis labels
        ctx.font = "italic 400 10px 'Source Serif 4', 'Georgia', serif";
        ctx.fillStyle = "rgba(220, 80, 60, 0.4)";
        ctx.textAlign = "left";
        ctx.fillText("← magnetically silent (n_t = 0)", pad + 10, pad + 15);
        ctx.textAlign = "right";
        ctx.fillText("increasing magnetic moment →", cw - pad - 10, ch - pad - 10);
      }

      if (viewMode === "lineage") {
        // Highlight EC elements with a distinctive ring and draw
        // arrows showing EC transition (He-3 → α-core repair)
        elData.forEach(el => {
          if (!el.isEC) return;
          const p = elPos(el);
          // Dashed ring around EC elements
          ctx.beginPath();
          ctx.arc(p.x, p.y, 12, 0, Math.PI * 2);
          ctx.strokeStyle = "rgba(74, 109, 130, 0.35)";
          ctx.lineWidth = 1;
          ctx.setLineDash([3, 3]);
          ctx.stroke();
          ctx.setLineDash([]);

          // Small downward arrow indicating EC transition
          // (EC converts p→n, shifting element toward α-core grammar)
          ctx.beginPath();
          ctx.moveTo(p.x + 9, p.y + 4);
          ctx.lineTo(p.x + 14, p.y + 9);
          ctx.lineTo(p.x + 9, p.y + 9);
          ctx.closePath();
          ctx.fillStyle = "rgba(74, 109, 130, 0.3)";
          ctx.fill();
        });

        // Legend labels
        ctx.font = "500 10px 'Inter', sans-serif";
        ctx.fillStyle = "rgba(74, 109, 130, 0.6)";
        ctx.textAlign = "left";
        ctx.fillText("◯  He-3 core — EC-eligible (incomplete tetrahedron)", pad + 10, pad + 15);
        ctx.fillStyle = "rgba(176, 116, 48, 0.6)";
        ctx.fillText("●  α core — complete He-4 tetrahedron", pad + 10, pad + 30);
        ctx.fillStyle = "rgba(100, 100, 100, 0.4)";
        ctx.font = "italic 400 9px 'Source Serif 4', 'Georgia', serif";
        ctx.fillText("▸ arrows show EC self-repair direction: He-3 → α", pad + 10, pad + 44);
      }

      // Draw element nodes
      elData.forEach(el => {
        const p = elPos(el);
        const isHovered = hoveredEl && hoveredEl.Z === el.Z;
        const isSelected = selectedEl && selectedEl.Z === el.Z;
        const isGolden = el.Z === 79;

        const baseRadius = 4 + (el.Z / 92) * 3;
        let radius = isHovered ? baseRadius + 3 : (isSelected ? baseRadius + 2 : baseRadius);

        // Magnetic mode: scale radius by triton fraction to show magnetic weight
        if (viewMode === "magnetic") {
          radius = 3 + el.tritonFrac * 7 + (el.magClass === "ferromagnetic" ? 3 : 0);
          if (isHovered) radius += 3;
          if (isSelected) radius += 2;
        }

        // EC lineage mode: different shape for EC vs standard
        if (viewMode === "lineage" && el.isEC && !isHovered && !isSelected) {
          // Draw as ring instead of filled circle
          ctx.beginPath();
          ctx.arc(p.x, p.y, radius, 0, Math.PI * 2);
          ctx.strokeStyle = elColor(el, 0.7);
          ctx.lineWidth = 1.5;
          ctx.stroke();
        } else {
          // Glow
          if (isHovered || isSelected || isGolden) {
            ctx.beginPath();
            ctx.arc(p.x, p.y, radius + 6, 0, Math.PI * 2);
            ctx.fillStyle = isGolden ? "rgba(212, 160, 92, 0.12)" : elColor(el, 0.08);
            ctx.fill();
          }

          // Node
          ctx.beginPath();
          ctx.arc(p.x, p.y, radius, 0, Math.PI * 2);
          ctx.fillStyle = elColor(el, isHovered || isSelected ? 0.9 : 0.55);
          ctx.fill();

          if (isSelected) {
            ctx.strokeStyle = elColor(el, 0.8);
            ctx.lineWidth = 1.5;
            ctx.stroke();
          }
        }

        // Labels
        const alwaysLabel = [2, 6, 8, 14, 20, 26, 27, 28, 50, 79, 82, 92];
        const showLabel = isHovered || isSelected || isGolden || alwaysLabel.includes(el.Z) ||
          (viewMode === "grammar" && el.nt === 0) ||
          (viewMode === "magnetic" && el.magClass === "ferromagnetic") ||
          (viewMode === "lineage" && el.isEC && el.Z <= 40);

        if (showLabel) {
          ctx.font = `${isHovered || isSelected ? "600" : "500"} ${isHovered || isSelected ? "12" : "10"}px 'Source Serif 4', 'Georgia', serif`;
          ctx.fillStyle = isHovered || isSelected ? "#1e1c18" : "#7a7265";
          ctx.textAlign = "center";
          ctx.fillText(el.sym, p.x, p.y - radius - 5);
        }
      });

      // Grammar mode: pure deuteron label
      if (viewMode === "grammar") {
        const pureDeutFamily = elData.filter(e => e.nt === 0);
        if (pureDeutFamily.length > 0) {
          const lastPure = pureDeutFamily[pureDeutFamily.length - 1];
          const pp = elPos(lastPure);
          ctx.font = "italic 400 9px 'Source Serif 4', 'Georgia', serif";
          ctx.fillStyle = "rgba(74, 109, 130, 0.5)";
          ctx.textAlign = "left";
          ctx.fillText("← pure deuteron scaffolds (magnetically silent, most stable)", pp.x + 12, pp.y + 3);
        }
      }
    }

    // Tooltip & interaction
    const tooltip = document.getElementById("atomicusTooltip");

    function getElAtPos(mx, my) {
      let closest = null, minDist = 20;
      elData.forEach(el => {
        const p = elPos(el);
        const d = Math.sqrt((p.x - mx) ** 2 + (p.y - my) ** 2);
        if (d < minDist) { closest = el; minDist = d; }
      });
      return closest;
    }

    atomCanvas.addEventListener("mousemove", (e) => {
      const rect = atomCanvas.getBoundingClientRect();
      const mx = e.clientX - rect.left;
      const my = e.clientY - rect.top;
      const el = getElAtPos(mx, my);
      hoveredEl = el;
      drawAtomicus();

      if (el) {
        atomCanvas.style.cursor = "pointer";
        tooltip.style.display = "block";
        tooltip.style.left = (mx + 16) + "px";
        tooltip.style.top = (my - 10) + "px";

        const ecTag = el.isEC ? ` · <span style="color:#6a95b0;">EC-eligible</span>` : "";
        const magTag = el.magClass === "ferromagnetic"
          ? ` · <span style="color:#dc503c;">ferromagnetic</span>`
          : el.magClass === "paramagnetic"
          ? ` · <span style="color:#be823c;">paramagnetic</span>`
          : "";

        tooltip.innerHTML = `
          <div style="background:rgba(30,28,24,0.92);color:#faf6ef;padding:8px 12px;border-radius:4px;font-size:12px;font-family:'Inter',sans-serif;white-space:nowrap;box-shadow:0 4px 16px rgba(0,0,0,0.2);">
            <strong style="font-family:'Source Serif 4','Georgia',serif;font-size:14px;">${el.sym}</strong>
            <span style="color:#a49d92;margin-left:6px;">${el.name} · Z=${el.Z}</span><br>
            <span style="color:#d4a05c;">1α</span> <span style="color:#6b7280">+</span>
            <span style="color:#6a95b0;">${el.nd}d</span> <span style="color:#6b7280">+</span>
            <span style="color:#a49d92;">${el.nt}t</span>
            <span style="color:#6b7280;margin-left:8px;">${(el.tritonFrac * 100).toFixed(1)}% triton</span>
            ${ecTag}${magTag}
          </div>`;
      } else {
        atomCanvas.style.cursor = "crosshair";
        tooltip.style.display = "none";
      }
    });

    atomCanvas.addEventListener("mouseleave", () => {
      hoveredEl = null;
      tooltip.style.display = "none";
      drawAtomicus();
    });

    atomCanvas.addEventListener("click", (e) => {
      const rect = atomCanvas.getBoundingClientRect();
      const el = getElAtPos(e.clientX - rect.left, e.clientY - rect.top);
      if (el) {
        selectedEl = el;
        updateElementPanel(el);
        drawAtomicus();
      }
    });

    function updateElementPanel(el) {
      document.getElementById("epZ").textContent = "Z = " + el.Z;
      document.getElementById("epSym").textContent = el.sym;
      document.getElementById("epName").textContent = el.name;

      let grammarHtml =
        `<span class="alpha">1α</span> <span class="op">+</span> ` +
        `<span class="deut">${el.nd}d</span> <span class="op">+</span> ` +
        `<span class="trit">${el.nt}t</span>`;

      if (el.isEC && el.ecValid) {
        grammarHtml += `<br><span style="font-size:0.85em;color:var(--steel);">EC: ` +
          `<span style="color:var(--steel);">1 He-3</span> <span class="op">+</span> ` +
          `<span class="deut">${el.nd_ec}d</span> <span class="op">+</span> ` +
          `<span class="trit">${el.nt_ec}t</span></span>`;
      }
      document.getElementById("epGrammar").innerHTML = grammarHtml;

      const total = el.nd + el.nt;
      const tfrac = (el.tritonFrac * 100).toFixed(1);
      let notes = [];
      if (el.nt === 0) notes.push("Pure deuteron scaffold — magnetically silent, maximum stability.");
      if (el.Z === 26) notes.push("Peak binding energy — geometric optimum of nuclear construction.");
      if (el.Z === 79) notes.push("The Golden Boundary — tritons first exceed deuterons.");
      if (el.nt > el.nd && el.Z !== 79) notes.push("Triton-dominated — beyond the Golden Boundary.");
      if (el.magClass === "ferromagnetic") notes.push("Ferromagnetic — triton fraction geometrically optimised for magnetic coupling.");
      if (el.isEC) notes.push("EC-eligible — He-3 core seeks tetrahedral completion via electron capture.");

      document.getElementById("epMeta").innerHTML =
        `A = ${el.A} · Total subunits: ${total} · Triton fraction: ${tfrac}%` +
        (notes.length ? `<br><em style="color:var(--copper);">${notes.join(" ")}</em>` : "");

      document.getElementById("epNd").textContent = el.nd;
      document.getElementById("epNt").textContent = el.nt;

      const epMag = document.getElementById("epMag");
      if (epMag) {
        const magLabels = { ferromagnetic: "Ferro ⬤", paramagnetic: "Para ◐", diamagnetic: "Dia ◯" };
        epMag.textContent = magLabels[el.magClass] || "—";
        epMag.style.color = el.magClass === "ferromagnetic" ? "#dc503c" :
                            el.magClass === "paramagnetic" ? "#be823c" : "";
      }
    }

    resizeAtomCanvas();
    window.addEventListener("resize", () => { resizeAtomCanvas(); drawAtomicus(); });
    drawAtomicus();
    updateElementPanel(selectedEl);
  }


  /* ════════════════════════════════════════════════════════════════════════
     EXPERIMENT FILTERS
     ════════════════════════════════════════════════════════════════════════ */

  const expFilters = document.getElementById("expFilters");
  const expGrid = document.getElementById("expGrid");
  if (expFilters && expGrid) {
    const cards = expGrid.querySelectorAll(".exp-card");
    expFilters.addEventListener("click", (e) => {
      const btn = e.target.closest(".exp-cat");
      if (!btn) return;
      expFilters.querySelectorAll(".exp-cat").forEach(b => b.classList.remove("exp-cat--active"));
      btn.classList.add("exp-cat--active");
      const f = btn.getAttribute("data-f");
      cards.forEach(c => {
        c.style.display = (f === "all" || c.getAttribute("data-cat") === f) ? "" : "none";
      });
    });
  }


  /* ════════════════════════════════════════════════════════════════════════
     GLOSSARY SEARCH
     ════════════════════════════════════════════════════════════════════════ */

  const glossarySearch = document.getElementById("glossarySearch");
  const glossaryGrid = document.getElementById("glossaryGrid");
  if (glossarySearch && glossaryGrid) {
    const entries = glossaryGrid.querySelectorAll(".gloss-entry");
    glossarySearch.addEventListener("input", () => {
      const q = glossarySearch.value.toLowerCase().trim();
      entries.forEach(e => {
        const term = e.getAttribute("data-term") || "";
        const text = e.textContent.toLowerCase();
        e.hidden = q.length > 0 && !term.includes(q) && !text.includes(q);
      });
    });
  }


  /* ════════════════════════════════════════════════════════════════════════
     SMOOTH SCROLL FOR NAV LINKS
     ════════════════════════════════════════════════════════════════════════ */

  document.querySelectorAll('a[href^="#"]').forEach(a => {
    a.addEventListener("click", (e) => {
      const target = document.querySelector(a.getAttribute("href"));
      if (target) {
        e.preventDefault();
        target.scrollIntoView({ behavior: "smooth", block: "start" });
      }
    });
  });

})();
