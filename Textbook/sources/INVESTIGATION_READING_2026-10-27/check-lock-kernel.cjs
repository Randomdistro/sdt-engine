const fs = require('fs');
const path = require('path');
const rows = [];
let consistent = true;
for (const boundary of [0.125, 1, 7]) {
  let previous = [Infinity, Infinity];
  for (const n of [1024, 4096, 16384]) {
    let locked = 0, wake = 0;
    for (let j = 0; j < n; j++) {
      const r = (j + 0.5) / n;
      locked += r * r * Math.sqrt(r);
      wake += r * r * (1 - Math.sqrt(r));
    }
    const factor = 4 * Math.PI * boundary ** 3 / n;
    locked *= factor; wake *= factor;
    const exact = [8 * Math.PI * boundary ** 3 / 7, 4 * Math.PI * boundary ** 3 / 21];
    const errors = [Math.abs(locked / exact[0] - 1), Math.abs(wake / exact[1] - 1)];
    const refinement = errors.every((e, j) => e < previous[j]);
    const partitionError = Math.abs((locked + wake) / (4 * Math.PI * boundary ** 3 / 3) - 1);
    // Midpoint volume integration also has finite-grid error: partition gate
    // below uses the exact pointwise partition, integrated analytically.
    rows.push({boundary, n, locked, wake, errors, refinement, finiteGridPartitionError: partitionError});
    consistent &&= refinement && (n !== 16384 || (errors.every(e => e < 1e-7) && partitionError < 1e-8));
    previous = errors;
  }
}
const angular = [];
const count = 100000;
for (const k of [0, 0.125, 0.25, 0.5, 0.875, 1]) {
  let accepted = 0;
  for (let j = 0; j < count; j++) accepted += (j + 0.5) / count <= k;
  const error = Math.abs(accepted / count - k);
  angular.push({k, fraction: accepted / count, error});
  consistent &&= error <= 1e-6;
}
let secondMoment = 0;
for (let j = 0; j < count; j++) secondMoment += ((j + 0.5) / count) ** 2 / count;
const secondMomentError = Math.abs(secondMoment - 1 / 3);
const exactPartitionError = Math.abs((8 * Math.PI / 7 + 4 * Math.PI / 21) / (4 * Math.PI / 3) - 1);
consistent &&= secondMomentError < 1e-8 && exactPartitionError < 1e-12;
const result = {classification:'COMPUTED dimensionless controls only', consistent, rows, angular, secondMoment, secondMomentError, exactPartitionError, originalPythonSuiteExecuted:false};
fs.writeFileSync(path.join(__dirname, 'KERNEL_CHECK_RESULTS.json'), JSON.stringify(result, null, 2) + '\n');
console.log(JSON.stringify(result, null, 2));
process.exitCode = consistent ? 0 : 1;
