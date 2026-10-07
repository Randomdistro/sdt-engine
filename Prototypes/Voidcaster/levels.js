/* VOIDCASTER · thirty missions and the Dearth. */
'use strict';
const VCLevels = (() => {
  const WORLDS = [
    { name: 'LOW ORBIT', line: '#70b8c3', intro: 'THE DEARTH HAS FOUND US. THEY CANNOT MAKE LIGHT, SO THEY HURL ROCKS AT ANYTHING THAT GLOWS.' },
    { name: 'SETTLER LANES', line: '#d8a860', intro: 'WAGON TRAINS OF SETTLER SHIPS CROSS THE LANES. THE DEARTH LIES IN WAIT BETWEEN THE STARS.' },
    { name: 'PIP REEF', line: '#6fe0b0', intro: 'THE PIPS ARE SMALL, SOFT AND GLOW LIKE LANTERNS. THE DEARTH HUNGERS FOR THAT GLOW.' },
    { name: 'THE FRONTIER', line: '#8aa0ff', intro: 'THE ARK AND THE EDGE WORLDS. THE DEARTH NOW THROW MOONS, AND SOMETHING BIGGER IS WATCHING.' },
    { name: 'DEARTH MARCHES', line: '#e07090', intro: 'WE TAKE THE FIGHT TO THEIR ROADS. NEEDLES, MOONS, WHOLE WORLDS. HOLD THE LINE.' },
    { name: 'THE HOLLOW', line: '#d070f0', intro: 'THE HOLLOW CROWN SITS AT THE CENTRE OF THE EMPTY. END IT, VOIDCASTER.' },
  ];
  // [name, mission, dur, dens, mix(met,ast,moon,pla,wpn), from(top,left,right), hint, count, boss]
  const T = [
    ['First Light', 'station', 45, 0.40, [1, 0, 0, 0, 0], [1, .2, .2], 'HOLD LEFT MOUSE ON VOID A AND DRAG IT. ROCKS FALL INTO ITS SHADOW. KEEP THEM OFF THE STATION.'],
    ['Hail', 'station', 55, 0.60, [1, 0, 0, 0, 0], [1, .3, .3], 'MOUSE WHEEL OR [ AND ] RESIZES A VOID. A BIGGER SHADOW PULLS HARDER.'],
    ['Lances', 'city', 55, 0.60, [.7, 0, 0, 0, .4], [1, .3, .3], 'HOLD LEFT MOUSE ON EMPTY SPACE TO FIRE. WASD MOVES YOU. A LANCE DIES TO ONE BOLT.'],
    ['Rockfall', 'city', 60, 0.70, [.6, .5, 0, 0, .1], [1, .3, .3], 'VOID B IS ONLINE. KEYS 1 2 3 SELECT A VOID. HOLD A ROCK IN A VOID TO ABSORB IT.'],
    ['Twin Shadows', 'station', 65, 0.80, [.5, .5, 0, 0, .2], [1, .5, .5], 'SPACE RELEASES ALL VOIDS AT ONCE AND SHOVES EVERYTHING AWAY. IT NEEDS TIME TO RECOVER.'],
    ['Wagon Train', 'convoy', 65, 0.75, [.6, .4, 0, 0, .2], [1, .4, .4], 'THE CONVOY KEEPS MOVING. PROTECT AT LEAST ONE SHIP.', 3],
    ['Cold Moon', 'convoy', 70, 0.80, [.4, .3, .2, 0, .2], [1, .4, .4], 'MOONS ARE HEAVY. BOLTS ONLY NUDGE THEM. USE A BIG VOID EARLY AND LET THE SHADOW BEND THEM.', 3],
    ['Pincer', 'city', 70, 0.90, [.4, .4, .1, 0, .3], [.4, .8, .8], 'THEY COME FROM BOTH SIDES. VOID C IS ONLINE.'],
    ['Shear Line', 'convoy', 75, 1.00, [.3, .5, .1, 0, .2], [.5, .8, .8], 'ASTEROID STREAMS CROSS THE LANE FROM THE FLANKS.', 4],
    ['The Dearth Reaver', 'station', 70, 0.25, [1, .3, 0, 0, 0], [1, 0, 0], 'THE REAVER FIRES LANCES AND HURLS ROCK. ITS OWN THROWN MASS HURTS IT WHEN YOU TURN IT BACK.', 0, 1],
    ['Pip Reef', 'critters', 60, 0.70, [1, .2, 0, 0, 0], [1, .4, .4], 'THE PIPS WANDER THE REEF. LOSE THEM ALL AND THE REEF GOES DARK.', 6],
    ['Bloom Drift', 'critters', 70, 0.80, [.4, .5, 0, 0, .2], [1, .4, .4], 'KEEP THE SHADOWS HIGH. THE REEF SHELTERS THE PIPS.', 7],
    ['Glimmer Storm', 'critters', 70, 1.30, [1, .3, 0, 0, 0], [1, .5, .5], 'A DENSE SHOWER. SMALL VOIDS ARE QUICK. BIG VOIDS ARE SLOW BUT STRONG.', 7],
    ['Moonrise', 'critters', 75, 0.90, [.3, .3, .3, 0, .2], [1, .4, .4], 'A MOON ON THE REEF IS A DISASTER. BEND IT EARLY.', 8],
    ['Reef Siege', 'critters', 80, 1.00, [.3, .4, .2, 0, .4], [1, .6, .6], 'LANCES, ROCKS AND MOONS TOGETHER. SPLIT YOUR ATTENTION.', 8],
    ['The Ark Departs', 'ark', 80, 0.90, [.4, .4, .2, 0, .2], [1, .5, .5], 'THE ARK CARRIES TEN THOUSAND SETTLERS. IT IS SLOW AND IT IS BIG.'],
    ['Ring Road', 'convoy', 80, 1.00, [.3, .5, .2, 0, .3], [.6, .8, .8], 'FIVE SHIPS ON A LONG ROAD.', 5],
    ['Wandering Giant', 'city', 85, 0.90, [.3, .3, .2, .12, .2], [1, .4, .4], 'A PLANET. IT IS SLOW. TO TURN IT YOU MUST START NOW, WITH EVERYTHING YOU HAVE.'],
    ['Crossfire', 'station', 80, 1.20, [.3, .2, .1, 0, .8], [1, .8, .8], 'LANCES FROM EVERY SIDE. KEEP FIRING.'],
    ['The Dearth Warden', 'city', 75, 0.30, [.8, .4, .2, 0, 0], [1, 0, 0], 'THE WARDEN RAISES A SHIELD. BOLTS FAIL WHILE IT HOLDS. ONLY THE MASS YOU TURN BACK WILL HURT IT.', 0, 2],
    ['Orchard Moons', 'critters', 85, 1.00, [.2, .3, .5, .05, .2], [1, .5, .5], 'MOONS ON THE REEF ORCHARD. WATCH THE SKY.', 8],
    ['Needle Season', 'convoy', 80, 1.30, [.2, .1, 0, 0, 1.2], [.7, .8, .8], 'NEEDLES EVERYWHERE. SHOOT FIRST.', 4],
    ['Two Worlds', 'city', 90, 1.00, [.2, .3, .2, .2, .2], [1, .5, .5], 'TWO PLANETS CROSS THE SKY. ONE VOID CANNOT TURN BOTH.'],
    ['Long Haul', 'convoy', 95, 1.20, [.3, .4, .3, .1, .4], [.7, .8, .8], 'THE LONGEST ROAD. SAVE YOUR RELEASE FOR THE MOONS.', 5],
    ['Shatterfield', 'station', 90, 1.60, [.7, .8, .1, 0, .2], [1, .7, .7], 'A WALL OF ROCK. ABSORB WHAT YOU CAN.'],
    ['Pip Evacuation', 'critters', 95, 1.30, [.4, .4, .3, .1, .5], [1, .6, .6], 'ALL TEN PIPS. EVERY ONE COUNTS.', 10],
    ['Ark of Ten Thousand', 'ark', 100, 1.30, [.3, .4, .3, .15, .5], [1, .6, .6], 'THE ARK SAILS THROUGH THE HEAVIEST FIRE YET.'],
    ['Planetfall', 'city', 100, 1.20, [.2, .3, .3, .3, .4], [1, .5, .5], 'WORLDS FALL ON THE CITY. TURN THEM.'],
    ['Last Light', 'station', 105, 1.70, [.4, .5, .3, .2, .7], [1, .8, .8], 'EVERYTHING THEY HAVE. HOLD THE LAST LIGHT.'],
    ['The Hollow Regent', 'city', 80, 0.30, [.5, .3, .3, .1, .2], [1, 0, 0], 'THE REGENT HURLS WORLDS. TURN THEM BACK AND CRACK THE CROWN.', 0, 3],
  ];
  const LEVELS = T.map((r, i) => ({ idx: i, name: r[0], m: r[1], dur: r[2], dens: r[3], mix: r[4], from: r[5], hint: r[6], count: r[7] || 0, boss: r[8] || 0, world: Math.floor(i / 5), unlock: i >= 7 ? 3 : i >= 3 ? 2 : 1 }));
  const BUDGET = (i) => (i >= 27 ? 31000 : i >= 21 ? 27000 : i >= 14 ? 23000 : i >= 7 ? 19000 : i >= 3 ? 14000 : 9000);

  const HZ = {
    met: { r: [8, 13], spd: [190, 270], hp: 1, dmg: 5, pts: 10, name: 'METEOR' },
    ast: { r: [20, 32], spd: [110, 170], hp: 3, dmg: 12, pts: 25, name: 'ASTEROID' },
    moon: { r: [44, 58], spd: [65, 95], hp: 999, dmg: 35, pts: 60, name: 'MOON' },
    pla: { r: [84, 108], spd: [36, 52], hp: 999, dmg: 90, pts: 120, name: 'PLANET' },
    wpn: { r: [7, 7], spd: [300, 380], hp: 1, dmg: 12, pts: 20, name: 'LANCE' },
  };
  const KINDS = ['met', 'ast', 'moon', 'pla', 'wpn'];
  const COST = { met: 1, ast: 2.2, moon: 5, pla: 12, wpn: 1.6 };

  function buildWaves(L) {
    const rnd = VCArt.rng(1000 + L.idx * 77);
    const ev = []; let t = 2.5; const tot = L.mix.reduce((a, b) => a + b, 0);
    const side = () => { const s = L.from[0] + L.from[1] + L.from[2]; let r = rnd() * s; if ((r -= L.from[0]) < 0) return 'top'; if ((r -= L.from[1]) < 0) return 'left'; return 'right'; };
    while (t < L.dur) {
      let r = rnd() * tot, k = 0; while (k < 4 && r > L.mix[k]) { r -= L.mix[k]; k++; }
      const kind = KINDS[k], sd = side(); let n = 1, gap = 0;
      if (kind === 'met' && rnd() < 0.28) { n = 2 + Math.floor(rnd() * 3); gap = 0.25; }
      if (kind === 'wpn' && rnd() < 0.4) { n = 2 + Math.floor(rnd() * 2); gap = 0.35; }
      if (kind === 'ast' && rnd() < 0.2 && L.idx >= 8) { n = 2; gap = 0.5; }
      const sx = 120 + rnd() * 1360, sy = 60 + rnd() * 460;
      for (let i = 0; i < n; i++) ev.push({ t: t + i * gap, kind, side: sd, sx: sx + i * 40, sy: sy + i * 30, seed: Math.floor(rnd() * 1e6) });
      t += (COST[kind] * (n > 1 ? n * 0.7 : 1) / L.dens) * (0.7 + rnd() * 0.6);
    }
    ev.sort((a, b) => a.t - b.t);
    return ev;
  }
  return { WORLDS, LEVELS, HZ, KINDS, BUDGET, buildWaves };
})();
