# Chapter 58 — pre-registration of the worked-example instrument

Registered 2026-11-10, before `Textbook/examples/ch58_spherical_numerical_mechanics.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents). The instrument consumes the engine's `sdt::sphere::Locus` (`sphere_frame.hpp`, an untracked header, Chapter 57); no physical value is read.

Object. Stable numerical differences on the spherical frame. A place is a positive radius and a direction; for two loci with angular separation $\psi$ the distance is $d^2=(r_2-r_1)^2+4r_1r_2\sin^2(\psi/2)$ (58.1), whose terms are nonnegative. (a) The law-of-cosines form $r_1^2+r_2^2-2r_1r_2\cos\psi$ cancels for small $\psi$: at $r_1=r_2=1$ and $\psi=10^{-9}$ it returns exactly 0 in double precision (the true value is $\approx10^{-18}$); `Locus::distance_to` uses (58.1) and returns the chord to $10^{-12}$ relative of the value implied by the stored angles. (b) The haversine angle is accurate for small separations and loses accuracy near $\pi$ ($\mathrm{asin}$ near 1); the engine's five-part form `atan2` is accurate there: for $\psi=\pi-\delta$ with $\delta=10^{-7}$ the haversine value of $\pi-\psi$ has a relative error above $10^{-3}$ and the engine's `angular_distance` has a relative error of $\delta$ below $10^{-8}$. (c) Double-precision angular storage gives a positional resolution of order $\epsilon_{\rm machine}r$: at $r=10^7$ m, $\theta=\pi/2$, two loci that differ by the next representable $\varphi$ are separated by $\mathrm{ulp}(\varphi)\,r\approx2.2\times10^{-9}$ m for $\varphi\in[1,2)$, and a shift smaller than half an ulp is not representable (distance 0); a step $s$ cannot round-trip with a relative accuracy better than order $\epsilon_{\rm machine}r|\varphi|/s$; this is a property of the representation, not a physical minimum distance. (d) A regular centre-crossing chart: for a straight trajectory with direction $a$, a transverse origin offset $b$ and a polar axis $p\perp a,b$, every relative position lies in the plane of $a$ and $b$, so the polar angle is $\pi/2$ and the radius is at least $|b|$; with the origin on the line the radius reaches 0 and the locus constructor refuses it. Converting a Cartesian point near the pole with $\mathrm{acos}(z/r)$ loses the polar angle ($\theta=0$ at $(10^{-9},0,1)$ instead of $10^{-9}$) while $\mathrm{atan2}(\sqrt{x^2+y^2},z)$ is accurate. The azimuth has a branch cut: an unwrapped sequence is continuous where the raw sequence jumps by $2\pi$.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | two unit loci at $\theta=\pi/2$, $\varphi=1$ and $1+\pi/2$: distance $\sqrt2$; antipodal loci of radii 2 and 3: distance 5; one direction with radii 2 and 5: distance 3 | $10^{-14}$ relative |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | stable differences. $r_1=r_2=1$, $\theta=\pi/2$, $\varphi_2=\varphi_1+10^{-9}$ (stored values): the naive law of cosines returns a value below $10^{-17}$ while `distance_to` equals $2\sin(\psi_{\rm stored}/2)$ to $10^{-12}$ relative; the radii-difference case $r_2=1+10^{-9}$, $\psi=0$: `distance_to` equals $10^{-9}$ to $10^{-6}$ relative; near-antipodal: haversine relative error of $\delta$ above $10^{-3}$, engine below $10^{-8}$ | as stated | yes |
| T2 | resolution. $r=10^7$ m, $\theta=\pi/2$, $\varphi_1=1.2345$: the loci $\varphi_1$ and `nextafter` differ by a distance in $[2.0,2.4]\times10^{-9}$ m; a shift of $0.4\,\mathrm{ulp}$ gives the same locus (distance 0); for a step $s=10^{-3}$ m realised as $\Delta\varphi=s/r$ over 200 starting azimuths in $[1,2)$ the maximum relative error of `distance_to`$/s$ is below $3\times10^{-6}$ and above $10^{-8}$ (order $\epsilon r\varphi/s=2.2\times10^{-6}$ to $4.4\times10^{-6}$) | as stated | yes |
| T3 | regular chart. Relative position $p(t)=(t,\,1000\ \mathrm{m},\,0)$ (direction $a=(1,0,0)$, transverse offset $b=(0,1000,0)$ m, polar axis $z\perp a,b$), $t\in[-10^5,10^5]$ m in 2001 points: polar angle $=\pi/2$ to $10^{-15}$ and $r\ge1000$ m for every point, and the azimuth range is $\pi-2\arctan(0.01)=3.12159$ to $10^{-4}$; with the origin on the line ($b=0$) the locus at $t=0$ is refused (`domain_error`); the $\mathrm{acos}$ route gives $\theta=0$ at $(10^{-9},0,1)$ and the `atan2` route $10^{-9}$ to $10^{-12}$ relative; a path crossing the azimuth cut, $\varphi_k=6.2+0.02k$ ($k=0\ldots9$) wrapped modulo $2\pi$, has a raw maximum step above 6 and an unwrapped maximum step below 0.1 | as stated | yes |

Reported, not criteria: the realised separations, the errors, the azimuth range.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch58_spherical_numerical_mechanics`

## Record of run 1; one instrument defect (2026-11-10)

Run 1 (`ch58_run1_output.txt`): every criterion was met except one, the lower limit of the T2 round-trip error (registered: the maximum relative error over 200 azimuths lies above $10^{-8}$). The instrument reported $0$: it had measured `distance_to` against the *stored* step $(\varphi_2-\varphi_1)r$, which the engine reproduces exactly (the engine returns the distance implied by the stored angles). The registered statement concerns the accuracy of a step *as intended*, $s=10^{-3}$ m realised as $\Delta\varphi=s/r$: the round trip from the intended step to the stored step to the distance. This is an instrument defect, not a finding on the object. The criterion and its limits are unchanged; the instrument compares `distance_to` with the intended $s$. T1 and T3 results of run 1 are unchanged (naive law of cosines $0$; `distance_to` $1.000000083\times10^{-9}$; near-antipodal engine relative error $0$ against haversine $1.16\times10^{-2}$; polar angle $\pi/2$ exactly; azimuth range $3.121593$; acos route $\theta=0$ against atan2 $10^{-9}$). Run 2 is the run of record.
