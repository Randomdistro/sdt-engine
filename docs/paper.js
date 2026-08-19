(function () {
  "use strict";

  var main = document.querySelector("main[data-paper-id]");
  if (!main) return;

  document.querySelectorAll(".eq[id]").forEach(function (equation) {
    var number = equation.querySelector(".no");
    if (!number) return;
    var link = document.createElement("a");
    link.href = "#" + equation.id;
    link.setAttribute("aria-label", "Permanent link to equation " + number.textContent.trim());
    while (number.firstChild) link.appendChild(number.firstChild);
    number.appendChild(link);
  });

  document.querySelectorAll('a[href^="#ref-"]').forEach(function (citation) {
    var reference = document.querySelector(citation.getAttribute("href"));
    if (!reference) return;
    var backlink = document.createElement("a");
    backlink.href = "#" + (citation.id || "");
    backlink.className = "citation";
    backlink.textContent = " ↩";
    backlink.setAttribute("aria-label", "Return to citation");
    if (citation.id) reference.appendChild(backlink);
  });
})();
