'use strict';
const fs=require('fs'),path=require('path');
const rows=[];
for(const x of [0.5,0.1])for(const N of [1024,2048,4096]){
 const f=t=>2*(1/t**2-1/t**3),step=(x-1)/N;
 let sum=f(1)+f(x);for(let i=1;i<N;i++)sum+=(i%2?4:2)*f(1+i*step);
 const workOverEB=step*sum/3,analytic=(1/x-1)**2,relativeError=Math.abs(workOverEB-analytic)/analytic;
 rows.push({x,N,workOverEB,analytic,relativeError,passed:relativeError<1e-6});
}
fs.writeFileSync(path.join(__dirname,'compression_quadrature.json'),JSON.stringify({method:'independent composite Simpson integral of external holding force; conditional profile',rows},null,2));
if(rows.some(r=>!r.passed))process.exitCode=1;
console.log(JSON.stringify(rows));
