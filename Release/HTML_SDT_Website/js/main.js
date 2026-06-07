// Main orchestrator — replaces the monolithic draw() function
function draw() {
  ctx.clearRect(0, 0, W, H);
  drawBackground(ctx);
  drawNodes(ctx);
  drawOverlays(ctx);
  drawElemLabels(ctx);
}

// Export PNG
document.getElementById("exportBtn").addEventListener("click", () => {
  const link = document.createElement("a");
  const ts = new Date().toISOString().replace(/[:.]/g,"-").slice(0,19);
  link.download = `atomicus-v1-${ts}.png`;
  link.href = canvas.toDataURL("image/png");
  link.click();
});

// Dropdown toggle (Phase 5)
function toggleDropdown(id) {
  document.getElementById(id).classList.toggle('open');
}

resize();
draw();
if (selectedIso) updatePanel(selectedIso);
window.addEventListener("resize", () => { resize(); draw(); });
