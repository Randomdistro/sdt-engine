'use strict';
const assert = require('node:assert/strict');
const fs = require('node:fs');
const path = require('node:path');
const {budget, partition} = require('./HTML_SDT_Website/demonstrations.js');
for (let n = 0; n <= 1000; n++) {
  const b = n / 1000;
  assert.ok(Math.abs(b * b + budget(b) ** 2 - 1) < 5e-16);
}
assert.equal(budget(0), 1);
assert.equal(budget(1), 0);
for (const b of [-1, 1.01, NaN, Infinity]) assert.throws(() => budget(b), RangeError);
for (const pair of [[0, 1], [1, -1], [1.5, 2]]) assert.throws(() => partition(...pair), RangeError);
const proton = partition(2, 3);
assert.ok(Math.abs(proton.ratio - 1.224744871391589) < 1e-14);
assert.ok(Math.abs(proton.toroidal ** 2 - 0.4) < 1e-15);
assert.ok(Math.abs(proton.poloidal ** 2 - 0.6) < 1e-15);
assert.equal(partition(1, 1).ratio, 1);
// Fail if the source equation changes without a browser implementation review.
const header = fs.readFileSync(path.join(__dirname, '../Engine/include/sdt/laws.hpp'), 'utf8');
assert.match(header, /aspect_ratio\(int p, int q\)[\s\S]*?return std::sqrt\(static_cast<double>\(q\) \/ static_cast<double>\(p\)\)/);
assert.match(header, /proton_p\s*=\s*2, proton_q\s*=\s*3/);
console.log('PASS: endpoint, domain, 1001 closure samples, registered modes and engine equation checks.');
