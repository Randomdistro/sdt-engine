'use strict';
const fs=require('fs'),path=require('path'),root=path.resolve(__dirname,'../../..');
require(path.join(root,'Release/HTML_SDT_Website/js/nuclear-inputs.js'));
require(path.join(root,'Release/HTML_SDT_Website/js/traction-gear-engine.js'));
const report=global.SDT_TRACTION_GEAR.selfTest({Rp:.8414});
const checks={unlikeSphericalSlip:report.unlikeSlipControl<=1e-8,likeSlipRejection:Math.abs(report.likeSlipControl-2)<=1e-10,braidPeriod:report.braid.fourTourClosure<=1e-10,braidSeam:report.braid.maximumSeamResidual<=1e-10,H1Period:report.hydrogen.fourTourClosure<=1e-10,H1Seam:report.hydrogen.maximumLaneSeamResidual<=1e-10};
fs.writeFileSync(path.join(__dirname,'ORIGINAL_SELF_TEST.json'),JSON.stringify({scope:'existing source software/kinematic controls; no energy or physical contact promotion',checks,report},null,2));
console.log(JSON.stringify(checks));if(Object.values(checks).some(v=>!v))process.exitCode=1;
