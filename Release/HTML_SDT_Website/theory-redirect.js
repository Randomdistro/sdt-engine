(function () {
  "use strict";

  var route = (location.pathname.split("/").pop() || "").replace(/\.html$/, "");
  var raw = location.hash ? location.hash.slice(1) : "";
  var maps = {
    welcome: {
      "": "arrival",
      "ix-space": "ix-space",
      "ix-matter": "ix-matter",
      "ix-move": "ix-move",
      "ix-present": "ix-now",
      "ix-credo": "L4"
    },
    atlas: {
      "": "arrival",
      opening: "arrival",
      irreducibles: "irreducibles",
      medium: "medium",
      laws: "laws",
      topology: "topology",
      atomicus: "atomicus",
      lab: "lab",
      engine: "engine",
      cosmology: "cosmology",
      experiments: "experiments",
      glossary: "glossary"
    },
    "causal-chain": {
      "": "L0",
      walkthroughs: "experiments"
    }
  };

  var map = maps[route] || {};
  var target = map[raw] || (/^L(?:[0-9]|1[0-9]|20)$/.test(raw) ? raw : map[""] || "arrival");
  location.replace("theory.html" + location.search + "#" + encodeURIComponent(target));
})();
