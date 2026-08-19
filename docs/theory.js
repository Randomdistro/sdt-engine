(function () {
  "use strict";

  var steps = Array.prototype.slice.call(document.querySelectorAll(".theory-step[id]"));
  var rail = document.querySelector(".theory-rail");
  var progress = document.querySelector(".theory-progress span");

  function showError(message) {
    var box = document.createElement("p");
    box.className = "theory-dependency-error";
    box.setAttribute("role", "alert");
    box.textContent = "Dependency manifest error: " + message;
    document.body.insertBefore(box, document.body.firstChild);
  }

  function validateManifest(manifest) {
    if (!manifest || manifest.schema !== "sdt-theory-dependencies-1.0.0") {
      throw new Error("unsupported or missing schema");
    }
    if (!Array.isArray(manifest.nodes) || manifest.nodes.length !== 21) {
      throw new Error("expected exactly L0–L20");
    }

    var byId = Object.create(null);
    manifest.nodes.forEach(function (node, index) {
      if (!node || node.id !== "L" + index || node.order !== index) {
        throw new Error("node order is not the contiguous L0–L20 sequence");
      }
      if (byId[node.id]) {
        throw new Error("duplicate node " + node.id);
      }
      if (!document.getElementById(node.id)) {
        throw new Error("missing page section " + node.id);
      }
      byId[node.id] = node;
    });

    var visiting = Object.create(null);
    var visited = Object.create(null);

    function visit(id) {
      if (visiting[id]) {
        throw new Error("cycle at " + id);
      }
      if (visited[id]) {
        return;
      }
      visiting[id] = true;
      byId[id].requires.forEach(function (requiredId) {
        if (!byId[requiredId]) {
          throw new Error(id + " requires missing node " + requiredId);
        }
        if (byId[requiredId].order >= byId[id].order) {
          throw new Error(id + " has a forward dependency on " + requiredId);
        }
        visit(requiredId);
      });
      visiting[id] = false;
      visited[id] = true;
    }

    manifest.nodes.forEach(function (node) {
      visit(node.id);
      var section = document.getElementById(node.id);
      var requires = section.getAttribute("data-requires").trim();
      var declared = requires ? requires.split(/\s+/) : [];
      if (declared.join(" ") !== node.requires.join(" ")) {
        throw new Error(node.id + " page/manifest dependency mismatch");
      }
      section.setAttribute("data-dependency-valid", "true");
    });
  }

  fetch("theory-dependencies.json", { cache: "no-store" })
    .then(function (response) {
      if (!response.ok) {
        throw new Error("manifest request returned " + response.status);
      }
      return response.json();
    })
    .then(validateManifest)
    .catch(function (error) {
      showError(error.message);
    });

  if (rail && "IntersectionObserver" in window) {
    var railLinks = Array.prototype.slice.call(rail.querySelectorAll("a[href^='#L']"));
    var linkById = Object.create(null);
    railLinks.forEach(function (link) {
      linkById[link.getAttribute("href").slice(1)] = link;
    });
    var observer = new IntersectionObserver(
      function (entries) {
        entries.forEach(function (entry) {
          if (!entry.isIntersecting) {
            return;
          }
          railLinks.forEach(function (link) {
            link.removeAttribute("aria-current");
          });
          if (linkById[entry.target.id]) {
            linkById[entry.target.id].setAttribute("aria-current", "step");
          }
        });
      },
      { rootMargin: "-35% 0px -55% 0px", threshold: 0 }
    );
    steps.forEach(function (step) {
      observer.observe(step);
    });
  }

  function updateProgress() {
    if (!progress) {
      return;
    }
    var root = document.documentElement;
    var available = Math.max(1, root.scrollHeight - root.clientHeight);
    var ratio = Math.min(1, Math.max(0, root.scrollTop / available));
    progress.style.width = (ratio * 100).toFixed(2) + "%";
  }

  updateProgress();
  addEventListener("scroll", updateProgress, { passive: true });
  addEventListener("resize", updateProgress);

  function svgElement(name, attributes) {
    var element = document.createElementNS("http://www.w3.org/2000/svg", name);
    Object.keys(attributes).forEach(function (key) {
      element.setAttribute(key, attributes[key]);
    });
    return element;
  }

  function pointerPosition(svg, event) {
    var point = svg.createSVGPoint();
    point.x = event.clientX;
    point.y = event.clientY;
    var matrix = svg.getScreenCTM();
    return matrix ? point.matrixTransform(matrix.inverse()) : { x: 180, y: 85 };
  }

  function buildSpaceDemo() {
    var svg = document.getElementById("demo-space");
    if (!svg) {
      return;
    }
    var grains = [];
    for (var row = 0; row < 5; row += 1) {
      for (var column = 0; column < 12; column += 1) {
        var baseX = 18 + column * 29 + (row % 2 ? 14.5 : 0);
        var baseY = 22 + row * 30;
        var grain = svgElement("circle", {
          cx: baseX,
          cy: baseY,
          r: 7.2,
          fill: "none",
          stroke: "currentColor",
          "stroke-opacity": ".38"
        });
        svg.appendChild(grain);
        grains.push({ element: grain, x: baseX, y: baseY });
      }
    }
    var probe = svgElement("circle", {
      cx: 180,
      cy: 85,
      r: 13,
      fill: "var(--theory-accent)",
      opacity: ".9",
      tabindex: "0"
    });
    svg.appendChild(probe);
    var active = false;

    function move(x, y) {
      x = Math.max(14, Math.min(346, x));
      y = Math.max(14, Math.min(156, y));
      probe.setAttribute("cx", x);
      probe.setAttribute("cy", y);
      grains.forEach(function (grain) {
        var dx = grain.x - x;
        var dy = grain.y - y;
        var distance = Math.max(1, Math.hypot(dx, dy));
        var push = Math.max(0, 31 - distance) / 31 * 14;
        grain.element.setAttribute("cx", grain.x + dx / distance * push);
        grain.element.setAttribute("cy", grain.y + dy / distance * push);
      });
    }

    svg.addEventListener("pointerdown", function (event) {
      active = true;
      svg.setPointerCapture(event.pointerId);
      var p = pointerPosition(svg, event);
      move(p.x, p.y);
    });
    svg.addEventListener("pointermove", function (event) {
      if (!active) {
        return;
      }
      var p = pointerPosition(svg, event);
      move(p.x, p.y);
    });
    svg.addEventListener("pointerup", function () {
      active = false;
    });
  }

  function buildMatterDemo() {
    var svg = document.getElementById("demo-matter");
    if (!svg) {
      return;
    }
    var lines = [];
    for (var y = 15; y <= 155; y += 10) {
      var path = svgElement("path", {
        fill: "none",
        stroke: "currentColor",
        "stroke-opacity": ".34",
        "stroke-width": ".65"
      });
      svg.appendChild(path);
      lines.push({ element: path, y: y });
    }
    var body = svgElement("circle", {
      cx: 180,
      cy: 85,
      r: 24,
      fill: "var(--theory-accent)",
      opacity: ".9"
    });
    var ring = svgElement("path", {
      d: "M157 85 C164 58 195 60 202 85 C195 110 164 112 157 85 M165 69 C195 66 197 104 171 105",
      fill: "none",
      stroke: "var(--paper, #faf8f4)",
      "stroke-width": "2.3"
    });
    svg.appendChild(body);
    svg.appendChild(ring);
    var active = false;

    function redraw(x, y) {
      body.setAttribute("cx", x);
      body.setAttribute("cy", y);
      ring.setAttribute("transform", "translate(" + (x - 180) + " " + (y - 85) + ")");
      lines.forEach(function (line) {
        var dy = line.y - y;
        var bend = Math.max(0, 34 - Math.abs(dy));
        var direction = dy < 0 ? -1 : 1;
        var controlY = line.y + direction * bend;
        line.element.setAttribute(
          "d",
          "M8 " + line.y + " C110 " + line.y + " 130 " + controlY + " " + x + " " +
          controlY + " C230 " + controlY + " 250 " + line.y + " 352 " + line.y
        );
      });
    }

    redraw(180, 85);
    svg.addEventListener("pointerdown", function (event) {
      active = true;
      svg.setPointerCapture(event.pointerId);
      var p = pointerPosition(svg, event);
      redraw(p.x, p.y);
    });
    svg.addEventListener("pointermove", function (event) {
      if (!active) {
        return;
      }
      var p = pointerPosition(svg, event);
      redraw(Math.max(32, Math.min(328, p.x)), Math.max(32, Math.min(138, p.y)));
    });
    svg.addEventListener("pointerup", function () {
      active = false;
    });
  }

  function buildMovementDemo() {
    var input = document.getElementById("demo-movement");
    var output = document.getElementById("demo-movement-read");
    if (!input || !output) {
      return;
    }
    function update() {
      var translation = Number(input.value) / 100;
      var circulation = Math.sqrt(Math.max(0, 1 - translation * translation));
      output.innerHTML = "v/c = " + translation.toFixed(3) +
        " · v<sub>circ</sub>/c = " + circulation.toFixed(3);
    }
    input.addEventListener("input", update);
    update();
  }

  function buildNowDemo() {
    var button = document.getElementById("demo-now");
    var output = document.getElementById("demo-now-read");
    if (!button || !output) {
      return;
    }
    var tally = 0;
    button.addEventListener("click", function () {
      tally += 1;
      output.textContent = "Movement tally: " + tally;
    });
  }

  buildSpaceDemo();
  buildMatterDemo();
  buildMovementDemo();
  buildNowDemo();
})();
