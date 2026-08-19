(function () {
  "use strict";

  var field = document.querySelector(".sdt-paper-field");
  var mark = field && field.querySelector(".sdt-paper-field__mark");
  if (!field || !mark) {
    return;
  }

  function motionAllowed() {
    if (window.matchMedia("(prefers-reduced-motion: reduce)").matches) {
      return false;
    }
    var setting = document.documentElement.getAttribute("data-sdt-motion");
    return setting !== "off";
  }

  function themeAllowsField() {
    var theme = document.documentElement.getAttribute("data-theme");
    return theme !== "dark";
  }

  function syncVisibility() {
    var visible = themeAllowsField();
    field.hidden = !visible;
    field.setAttribute("aria-hidden", visible ? "true" : "true");
  }

  function updateParallax() {
    if (!motionAllowed() || field.hidden) {
      mark.style.transform = "translate3d(-50%, 0, 0)";
      return;
    }
    var drift = window.scrollY * 0.16;
    mark.style.transform = "translate3d(-50%, " + drift.toFixed(1) + "px, 0)";
  }

  syncVisibility();
  updateParallax();

  addEventListener("scroll", updateParallax, { passive: true });
  addEventListener("resize", updateParallax, { passive: true });

  new MutationObserver(function () {
    syncVisibility();
    updateParallax();
  }).observe(document.documentElement, {
    attributes: true,
    attributeFilter: ["data-theme", "data-sdt-motion"]
  });
})();
