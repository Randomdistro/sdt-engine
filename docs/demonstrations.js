/* Mathematical demonstrations; internal closure is not experimental validation. */
(function () {
  'use strict';
  function partition(p, q) {
    if (!Number.isInteger(p) || !Number.isInteger(q) || p <= 0 || q <= 0) {
      throw new RangeError('Mode indices must be positive integers.');
    }
    return { ratio: Math.sqrt(q / p), toroidal: Math.sqrt(p / (p + q)),
      poloidal: Math.sqrt(q / (p + q)) };
  }
  function budget(beta) {
    if (!Number.isFinite(beta) || beta < 0 || beta > 1) {
      throw new RangeError('Translation fraction must lie between zero and one.');
    }
    return Math.sqrt((1 - beta) * (1 + beta));
  }
  if (typeof module !== 'undefined' && module.exports) {
    module.exports = { partition: partition, budget: budget };
    return;
  }
  var slider = document.getElementById('budget');
  function renderBudget() {
    var beta = Number(slider.value), circ = budget(beta);
    document.getElementById('budget-point').setAttribute('cx', 40 + 200 * beta);
    document.getElementById('budget-point').setAttribute('cy', 230 - 200 * circ);
    document.getElementById('budget-result').textContent = 'v/c = ' + beta.toFixed(3) +
      '; v_circ/c = ' + circ.toFixed(6) + '; closure residual = ' +
      Math.abs(beta * beta + circ * circ - 1).toExponential(2) + '.';
  }
  var mode = document.getElementById('mode');
  function renderMode() {
    var value = mode.value === 'proton' ? partition(2, 3) : partition(1, 1);
    document.getElementById('mode-result').textContent = 'R/a = ' + value.ratio.toFixed(10) +
      '; v_T/c = ' + value.toroidal.toFixed(6) + '; v_P/c = ' + value.poloidal.toFixed(6) + '.';
  }
  slider.addEventListener('input', renderBudget);
  mode.addEventListener('change', renderMode);
  renderBudget(); renderMode();
})();
