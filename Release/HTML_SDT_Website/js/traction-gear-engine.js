/* NSEQ16 Atomicus contact-construction candidate.
   NSEQ05 is retained only as a legacy geometric control. This candidate
   assigns no contact energy or measured nuclear reconstruction. */
(function (global) {
  'use strict';

  const VERSION = 'NSEQ18-WEB-1';
  const TAU = 2 * Math.PI;
  const EPS = 1e-12;
  const BRAID = Object.freeze({
    majorTours: 4,
    poloidalTurns: 5,
    strandCount: 4,
    localTwistsPerLap: 1,
    seamLaneAdvance: 1,
    majorRadiusFraction: 0.62,
    helixRadiusFraction: 0.22,
    strandRadiusFraction: 0.16
  });
  const H1_NUCLEON = Object.freeze({
    canonicalRpFm: 0.8414,
    straightHelixLengthFm: 5.28,
    strandDiameterFm: 0.06,
    majorTours: 4,
    crossSectionTurns: 3,
    apparentStrands: 4,
    localHelixTurnsPerTour: 1,
    seamRetreatTurnsPerTour: 0.25,
    internalRollTurns: 3,
    majorRadiusFraction: (5.28 / TAU) / 0.8414,
    // Four equal circular strands touch their two neighbours in cross-section.
    helixRadiusFraction: (0.06 / Math.sqrt(2)) / 0.8414,
    strandRadiusFraction: (0.06 / 2) / 0.8414,
    circulationSpeedC: 1.83,
    targetMagneticMomentAm2: 1.41060679545e-26
  });
  const PRESETS = Object.freeze({
    N1: Object.freeze({ symbol: 'n', name: 'Free neutron', Z: 0, A: 1 }),
    H1: Object.freeze({ symbol: 'H', name: 'Hydrogen-1', Z: 1, A: 1 }),
    H2: Object.freeze({ symbol: 'D', name: 'Hydrogen-2', Z: 1, A: 2 }),
    H3: Object.freeze({ symbol: 'T', name: 'Hydrogen-3', Z: 1, A: 3 }),
    He3: Object.freeze({ symbol: 'He', name: 'Helium-3', Z: 2, A: 3 }),
    He4: Object.freeze({ symbol: 'He', name: 'Helium-4', Z: 2, A: 4 }),
    Li7: Object.freeze({ symbol: 'Li', name: 'Lithium-7', Z: 3, A: 7 }),
    Be9: Object.freeze({ symbol: 'Be', name: 'Beryllium-9', Z: 4, A: 9 }),
    B11: Object.freeze({ symbol: 'B', name: 'Boron-11', Z: 5, A: 11 }),
    C12: Object.freeze({ symbol: 'C', name: 'Carbon-12', Z: 6, A: 12 }),
    N14: Object.freeze({ symbol: 'N', name: 'Nitrogen-14', Z: 7, A: 14 }),
    O16: Object.freeze({ symbol: 'O', name: 'Oxygen-16', Z: 8, A: 16 })
  });
  const SEED_MEASURED = global.SDT_NUCLEAR_INPUTS;
  if (!SEED_MEASURED) {
    throw new Error(
      'traction-gear-engine requires generated js/nuclear-inputs.js'
    );
  }

  const add = (a, b) => [a[0] + b[0], a[1] + b[1], a[2] + b[2]];
  const sub = (a, b) => [a[0] - b[0], a[1] - b[1], a[2] - b[2]];
  const mul = (a, s) => [a[0] * s, a[1] * s, a[2] * s];
  const dot = (a, b) => a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
  const cross = (a, b) => [
    a[1] * b[2] - a[2] * b[1],
    a[2] * b[0] - a[0] * b[2],
    a[0] * b[1] - a[1] * b[0]
  ];
  const norm = a => Math.hypot(a[0], a[1], a[2]);
  const unit = a => {
    const length = norm(a);
    return length > 0 ? mul(a, 1 / length) : [0, 0, 1];
  };
  const rotateAround = (vector, axis, angle) => {
    const n = unit(axis);
    const cosine = Math.cos(angle);
    const sine = Math.sin(angle);
    return add(
      add(
        mul(vector, cosine),
        mul(cross(n, vector), sine)
      ),
      mul(n, dot(n, vector) * (1 - cosine))
    );
  };

  function h1Point(u, Rp = 1, rotationPhase = 0) {
    const major = H1_NUCLEON.majorRadiusFraction * Rp;
    const helix = H1_NUCLEON.helixRadiusFraction * Rp;
    const phi = H1_NUCLEON.crossSectionTurns * u + rotationPhase;
    const radial = major + helix * Math.cos(phi);
    const theta = H1_NUCLEON.majorTours * u;
    return [
      radial * Math.cos(theta),
      radial * Math.sin(theta),
      helix * Math.sin(phi)
    ];
  }

  function h1Derivative(u, Rp = 1, rotationPhase = 0) {
    const major = H1_NUCLEON.majorRadiusFraction * Rp;
    const helix = H1_NUCLEON.helixRadiusFraction * Rp;
    const phi = H1_NUCLEON.crossSectionTurns * u + rotationPhase;
    const radial = major + helix * Math.cos(phi);
    const radialRate = -H1_NUCLEON.crossSectionTurns
      * helix * Math.sin(phi);
    const theta = H1_NUCLEON.majorTours * u;
    return [
      radialRate * Math.cos(theta)
        - H1_NUCLEON.majorTours * radial * Math.sin(theta),
      radialRate * Math.sin(theta)
        + H1_NUCLEON.majorTours * radial * Math.cos(theta),
      H1_NUCLEON.crossSectionTurns * helix * Math.cos(phi)
    ];
  }

  function h1Tangent(u, Rp = 1, rotationPhase = 0) {
    return unit(h1Derivative(u, Rp, rotationPhase));
  }

  function h1LocalSpeed(u, Rp = 1) {
    return norm(h1Derivative(u, Rp));
  }

  function h1LanePoint(lane, theta, Rp = 1) {
    const index = ((lane % H1_NUCLEON.apparentStrands)
      + H1_NUCLEON.apparentStrands) % H1_NUCLEON.apparentStrands;
    // With three cross-sectional turns, path segment k occupies apparent
    // lane 3k (mod 4). The inverse is also 3, so a completed major tour
    // advances to the lane 90 degrees sooner: 0→3→2→1→0.
    const pathSegment = (
      H1_NUCLEON.crossSectionTurns * index
    ) % H1_NUCLEON.apparentStrands;
    return h1Point(
      (theta + TAU * pathSegment) / H1_NUCLEON.majorTours,
      Rp
    );
  }

  function h1ArcTable(Rp = 1, samples = 4096) {
    const count = Math.max(64, Math.trunc(samples));
    const parameters = new Float64Array(count + 1);
    const cumulative = new Float64Array(count + 1);
    const du = TAU / count;
    for (let i = 0; i < count; i++) {
      const u0 = i * du;
      const u1 = (i + 1) * du;
      const um = (u0 + u1) / 2;
      parameters[i] = u0;
      cumulative[i + 1] = cumulative[i] + du * (
        h1LocalSpeed(u0, Rp)
        + 4 * h1LocalSpeed(um, Rp)
        + h1LocalSpeed(u1, Rp)
      ) / 6;
    }
    parameters[count] = TAU;
    return {
      Rp,
      samples: count,
      parameters,
      cumulative,
      totalLength: cumulative[count]
    };
  }

  function h1ParameterAtArc(table, distance) {
    const length = table.totalLength;
    let target = distance % length;
    if (target < 0) target += length;
    let low = 0;
    let high = table.samples;
    while (high - low > 1) {
      const middle = (low + high) >> 1;
      if (table.cumulative[middle] <= target) low = middle;
      else high = middle;
    }
    const span = table.cumulative[high] - table.cumulative[low];
    const fraction = span > 0
      ? (target - table.cumulative[low]) / span
      : 0;
    return table.parameters[low]
      + fraction * (table.parameters[high] - table.parameters[low]);
  }

  function h1FrameTable(Rp = 1, segments = 512) {
    const count = Math.max(64, Math.trunc(segments));
    const points = [];
    const tangents = [];
    const normals = [];
    const binormals = [];
    const materialNormals = [];
    const materialBinormals = [];
    for (let i = 0; i <= count; i++) {
      const u = TAU * i / count;
      points.push(h1Point(u, Rp));
      tangents.push(h1Tangent(u, Rp));
    }

    const reference = Math.abs(tangents[0][2]) < 0.9
      ? [0, 0, 1]
      : [0, 1, 0];
    normals.push(unit(cross(tangents[0], reference)));
    for (let i = 1; i <= count; i++) {
      const previous = tangents[i - 1];
      const current = tangents[i];
      const axis = cross(previous, current);
      const axisLength = norm(axis);
      let next = normals[i - 1];
      if (axisLength > EPS) {
        next = rotateAround(
          next,
          mul(axis, 1 / axisLength),
          Math.atan2(axisLength, dot(previous, current))
        );
      }
      next = unit(sub(next, mul(current, dot(next, current))));
      normals.push(next);
    }

    const closureCorrection = Math.atan2(
      dot(tangents[0], cross(normals[count], normals[0])),
      dot(normals[count], normals[0])
    );
    for (let i = 0; i <= count; i++) {
      const fraction = i / count;
      normals[i] = rotateAround(
        normals[i],
        tangents[i],
        closureCorrection * fraction
      );
      const bishopB = unit(cross(tangents[i], normals[i]));
      binormals.push(bishopB);
      const roll = H1_NUCLEON.internalRollTurns * TAU * fraction;
      const director = unit(add(
        mul(normals[i], Math.cos(roll)),
        mul(bishopB, Math.sin(roll))
      ));
      materialNormals.push(director);
      materialBinormals.push(unit(cross(tangents[i], director)));
    }
    return {
      Rp,
      segments: count,
      points,
      tangents,
      normals,
      binormals,
      materialNormals,
      materialBinormals,
      closureCorrection
    };
  }

  function h1MagneticMetrics(RpMetres = 8.414e-16) {
    const c = 299792458;
    const e = 1.602176634e-19;
    const table = h1ArcTable(RpMetres, 8192);
    const major = H1_NUCLEON.majorRadiusFraction * RpMetres;
    const helix = H1_NUCLEON.helixRadiusFraction * RpMetres;
    const pathSpeed = H1_NUCLEON.circulationSpeedC * c;
    const period = table.totalLength / pathSpeed;
    const pathMoment = 2 * Math.PI * e * pathSpeed
      * (2 * major * major + helix * helix)
      / table.totalLength;
    const target = H1_NUCLEON.targetMagneticMomentAm2;
    return {
      pathLengthMetres: table.totalLength,
      circulationPeriodSeconds: period,
      pathSpeedMetresPerSecond: pathSpeed,
      pathMomentAm2: pathMoment,
      targetMomentAm2: target,
      absoluteResidualAm2: pathMoment - target,
      relativeResidual: (pathMoment - target) / target,
      wakeBridgeStatus:
        'PENDING — no dimensional spation-motion to effective-current bridge'
    };
  }

  function h1Diagnostics(Rp = 1) {
    const laneTargets = [];
    const laneTargetMap = [];
    const seamResiduals = [];
    const tangentResiduals = [];
    const selfGaps = [];
    for (let lane = 0; lane < H1_NUCLEON.apparentStrands; lane++) {
      const next = (
        lane + H1_NUCLEON.apparentStrands - 1
      ) % H1_NUCLEON.apparentStrands;
      const pathSegment = (
        H1_NUCLEON.crossSectionTurns * lane
      ) % H1_NUCLEON.apparentStrands;
      const nextPathSegment = (
        H1_NUCLEON.crossSectionTurns * next
      ) % H1_NUCLEON.apparentStrands;
      const tailU = (
        TAU + TAU * pathSegment
      ) / H1_NUCLEON.majorTours;
      const nextU = TAU * nextPathSegment / H1_NUCLEON.majorTours;
      laneTargetMap.push(next);
      seamResiduals.push(
        norm(sub(h1LanePoint(lane, TAU, Rp), h1LanePoint(next, 0, Rp))) / Rp
      );
      tangentResiduals.push(
        norm(sub(h1Tangent(tailU, Rp), h1Tangent(nextU, Rp)))
      );
      selfGaps.push(
        norm(sub(h1LanePoint(lane, TAU, Rp), h1LanePoint(lane, 0, Rp))) / Rp
      );
    }
    let traversalLane = 0;
    for (let step = 0; step < H1_NUCLEON.apparentStrands; step++) {
      traversalLane = (
        traversalLane + H1_NUCLEON.apparentStrands - 1
      ) % H1_NUCLEON.apparentStrands;
      laneTargets.push(traversalLane);
    }
    const frames = h1FrameTable(Rp, 512);
    const frameSeam = norm(sub(
      frames.materialNormals[frames.segments],
      frames.materialNormals[0]
    ));
    const arc = h1ArcTable(Rp, 4096);
    return {
      componentCount: 1,
      majorTours: H1_NUCLEON.majorTours,
      crossSectionTurns: H1_NUCLEON.crossSectionTurns,
      apparentStrands: H1_NUCLEON.apparentStrands,
      localHelixTurnsPerTour: H1_NUCLEON.localHelixTurnsPerTour,
      seamRetreatTurnsPerTour: H1_NUCLEON.seamRetreatTurnsPerTour,
      effectiveCrossSectionTurnsPerTour:
        H1_NUCLEON.crossSectionTurns / H1_NUCLEON.majorTours,
      perTourHelixRadians:
        TAU * (
          H1_NUCLEON.localHelixTurnsPerTour
          - H1_NUCLEON.seamRetreatTurnsPerTour
        ),
      perTourShortfallRadians:
        TAU * H1_NUCLEON.seamRetreatTurnsPerTour,
      laneTargets,
      laneTargetMap,
      maximumLaneSeamResidual: Math.max(...seamResiduals),
      maximumLaneTangentResidual: Math.max(...tangentResiduals),
      minimumOneTourSelfGap: Math.min(...selfGaps),
      fourTourClosure:
        norm(sub(h1Point(TAU, Rp), h1Point(0, Rp))) / Rp,
      fourTourTangentClosure:
        norm(sub(h1Tangent(TAU, Rp), h1Tangent(0, Rp))),
      materialRollRadians: H1_NUCLEON.internalRollTurns * TAU,
      frameSeamResidual: frameSeam,
      bishopHolonomyCorrection: frames.closureCorrection,
      pathLength: arc.totalLength,
      dimensions: {
        straightHelixLength:
          TAU * H1_NUCLEON.majorRadiusFraction * Rp,
        strandDiameter:
          2 * H1_NUCLEON.strandRadiusFraction * Rp,
        strandCount: H1_NUCLEON.apparentStrands,
        majorRadius: H1_NUCLEON.majorRadiusFraction * Rp,
        helixRadius: H1_NUCLEON.helixRadiusFraction * Rp,
        strandRadius: H1_NUCLEON.strandRadiusFraction * Rp,
        centralHoleResidual:
          H1_NUCLEON.majorRadiusFraction
          - H1_NUCLEON.helixRadiusFraction
          - H1_NUCLEON.strandRadiusFraction,
        outerEnvelopeResidual:
          H1_NUCLEON.majorRadiusFraction
          + H1_NUCLEON.helixRadiusFraction
          + H1_NUCLEON.strandRadiusFraction
          - 1
      }
    };
  }

  const H1_WAKE = Object.freeze({
    circuitCount: 4,
    throatFraction: 0.45,
    poloidalFraction: 0.55,
    throatRadiusRp: 0.12,
    tailRadiusRp: 0.75,
    tailLengthRp: 4.0,
    skirtRadiusRp: 2.8,
    crownHeightRp: 1.8,
    fieldCoreRp: 0.08
  });

  const wakeCylindrical = (radius, angle, z) => [
    radius * Math.cos(angle),
    radius * Math.sin(angle),
    z
  ];

  function wakeSample(count, pointAt) {
    return Array.from(
      { length: count + 1 },
      (_, index) => pointAt(index / count)
    );
  }

  function h1WakeCircuit(circuit, phase = 0, samples = 24) {
    const index = ((circuit % H1_WAKE.circuitCount)
      + H1_WAKE.circuitCount) % H1_WAKE.circuitCount;
    const chi = phase + TAU * index / H1_WAKE.circuitCount;
    const n = Math.max(8, Math.trunc(samples));
    const splitRadius = H1_WAKE.throatRadiusRp;
    const convergenceRadius = 0.85;
    const splitZ = 0.32;
    const tailEndZ = -H1_WAKE.tailLengthRp;
    const exteriorRadius = H1_WAKE.skirtRadiusRp;
    const exteriorBottomZ = tailEndZ + 0.4;
    const exteriorTopZ = H1_WAKE.crownHeightRp;

    const exteriorTop = wakeCylindrical(
      exteriorRadius,
      chi + Math.PI / 2,
      exteriorTopZ
    );
    const convergenceStart = wakeCylindrical(
      convergenceRadius,
      chi,
      1.35
    );
    const split = wakeCylindrical(splitRadius, chi, splitZ);
    const merge = wakeCylindrical(splitRadius, chi, -splitZ);
    const tailEnd = wakeCylindrical(
      H1_WAKE.tailRadiusRp,
      chi,
      tailEndZ
    );
    const exteriorBottom = wakeCylindrical(
      exteriorRadius,
      chi + Math.PI / 2,
      exteriorBottomZ
    );

    const crown = wakeSample(n, s => {
      const smooth = s * s * (3 - 2 * s);
      const radius = exteriorRadius
        + (convergenceRadius - exteriorRadius) * smooth;
      const angle = chi + Math.PI / 2 * (1 - smooth);
      const lobe = 0.16 * Math.sin(Math.PI * s);
      const z = exteriorTopZ + (1.35 - exteriorTopZ) * smooth + lobe;
      return wakeCylindrical(radius, angle, z);
    });
    crown[0] = exteriorTop;
    crown[crown.length - 1] = convergenceStart;

    const convergent = wakeSample(n, s => {
      const radius = convergenceRadius
        + (splitRadius - convergenceRadius) * s;
      const angle = chi + TAU * s;
      const z = 1.35 + (splitZ - 1.35) * s;
      return wakeCylindrical(radius, angle, z);
    });
    convergent[0] = convergenceStart;
    convergent[convergent.length - 1] = split;

    const throat = wakeSample(n, s =>
      wakeCylindrical(
        splitRadius * (1 - 0.42 * Math.sin(Math.PI * s)),
        chi,
        splitZ * (1 - 2 * s)
      ));
    throat[0] = split;
    throat[throat.length - 1] = merge;

    const poloidal = wakeSample(n * 2, s => {
      const radius = splitRadius
        + (H1_NUCLEON.majorRadiusFraction - splitRadius)
          * Math.sin(Math.PI * s);
      const z = splitZ * Math.cos(Math.PI * s);
      return wakeCylindrical(radius, chi, z);
    });
    poloidal[0] = split;
    poloidal[poloidal.length - 1] = merge;

    const tail = wakeSample(n * 3, s => {
      const radius = splitRadius
        + (H1_WAKE.tailRadiusRp - splitRadius)
          * (s * s * (3 - 2 * s));
      const angle = chi + 4 * Math.PI * s;
      const z = -splitZ + (tailEndZ + splitZ) * s;
      return wakeCylindrical(radius, angle, z);
    });
    tail[0] = merge;
    tail[tail.length - 1] = tailEnd;

    const skirt = wakeSample(n, s => {
      const smooth = s * s * (3 - 2 * s);
      return wakeCylindrical(
        H1_WAKE.tailRadiusRp
          + (exteriorRadius - H1_WAKE.tailRadiusRp) * smooth,
        chi + Math.PI / 2 * smooth,
        tailEndZ + (exteriorBottomZ - tailEndZ) * smooth
      );
    });
    skirt[0] = tailEnd;
    skirt[skirt.length - 1] = exteriorBottom;

    const exterior = wakeSample(n * 3, s =>
      wakeCylindrical(
        exteriorRadius,
        chi + Math.PI / 2 - TAU * s,
        exteriorBottomZ + (exteriorTopZ - exteriorBottomZ) * s
      ));
    exterior[0] = exteriorBottom;
    exterior[exterior.length - 1] = exteriorTop;

    return {
      circuit: index,
      phase: chi,
      flow: {
        convergent: 1,
        throat: H1_WAKE.throatFraction,
        poloidal: H1_WAKE.poloidalFraction,
        expulsive: 1,
        exterior: -1
      },
      stages: {
        crown,
        convergent,
        throat,
        poloidal,
        tail,
        skirt,
        exterior
      }
    };
  }

  function h1WakeSegments(phase = 0, samples = 18) {
    const segments = [];
    const weights = {
      crown: 1,
      convergent: 1,
      throat: H1_WAKE.throatFraction,
      poloidal: H1_WAKE.poloidalFraction,
      tail: 1,
      skirt: 1,
      exterior: 1
    };
    for (let circuit = 0; circuit < H1_WAKE.circuitCount; circuit++) {
      const network = h1WakeCircuit(circuit, phase, samples);
      for (const [family, points] of Object.entries(network.stages)) {
        for (let i = 0; i + 1 < points.length; i++) {
          segments.push({
            circuit,
            family,
            a: points[i],
            b: points[i + 1],
            weight: weights[family]
          });
        }
      }
    }
    return segments;
  }

  function wakePotentialFromSegments(point, segments) {
    const potential = [0, 0, 0];
    const core2 = H1_WAKE.fieldCoreRp * H1_WAKE.fieldCoreRp;
    for (const segment of segments) {
      const dl = sub(segment.b, segment.a);
      const middle = mul(add(segment.a, segment.b), 0.5);
      const displacement = sub(point, middle);
      const denominator = Math.sqrt(
        dot(displacement, displacement) + core2
      );
      potential[0] += segment.weight * dl[0] / denominator;
      potential[1] += segment.weight * dl[1] / denominator;
      potential[2] += segment.weight * dl[2] / denominator;
    }
    return potential;
  }

  function h1WakeVectorPotential(point, phase = 0, samples = 18) {
    return wakePotentialFromSegments(
      point,
      h1WakeSegments(phase, samples)
    );
  }

  function wakeFieldFromSegments(point, segments, step = 0.03) {
    const derivative = (component, axis) => {
      const plus = [...point];
      const minus = [...point];
      plus[axis] += step;
      minus[axis] -= step;
      return (
        wakePotentialFromSegments(plus, segments)[component]
        - wakePotentialFromSegments(minus, segments)[component]
      ) / (2 * step);
    };
    const field = [
      derivative(2, 1) - derivative(1, 2),
      derivative(0, 2) - derivative(2, 0),
      derivative(1, 0) - derivative(0, 1)
    ];
    return field;
  }

  function h1WakeField(point, phase = 0, samples = 18, step = 0.03) {
    return wakeFieldFromSegments(
      point,
      h1WakeSegments(phase, samples),
      step
    );
  }

  function analyticWakeFieldFromSegments(point, segments) {
    const field = [0, 0, 0];
    const core2 = H1_WAKE.fieldCoreRp * H1_WAKE.fieldCoreRp;
    for (const segment of segments) {
      const dl = sub(segment.b, segment.a);
      const middle = mul(add(segment.a, segment.b), 0.5);
      const displacement = sub(point, middle);
      const denominator = Math.pow(
        dot(displacement, displacement) + core2,
        1.5
      );
      const contribution = mul(
        cross(dl, displacement),
        segment.weight
          / (4 * Math.PI * Math.max(denominator, EPS))
      );
      field[0] += contribution[0];
      field[1] += contribution[1];
      field[2] += contribution[2];
    }
    return field;
  }

  function analyticWakeFieldByFamily(point, segments) {
    const families = {};
    for (const segment of segments) {
      const field = analyticWakeFieldFromSegments(point, [segment]);
      families[segment.family] = add(
        families[segment.family] || [0, 0, 0],
        field
      );
    }
    return families;
  }

  function h1WakeDivergence(point, phase = 0, step = 0.02) {
    const segments = h1WakeSegments(phase, 18);
    let divergence = 0;
    for (let axis = 0; axis < 3; axis++) {
      const plus = [...point];
      const minus = [...point];
      plus[axis] += step;
      minus[axis] -= step;
      divergence += (
        wakeFieldFromSegments(plus, segments)[axis]
        - wakeFieldFromSegments(minus, segments)[axis]
      ) / (2 * step);
    }
    return divergence;
  }

  function h1WakeDiagnostics(phase = 0) {
    const familyMoments = {};
    for (const segment of h1WakeSegments(phase, 24)) {
      const dl = sub(segment.b, segment.a);
      const middle = mul(add(segment.a, segment.b), 0.5);
      const contribution = mul(
        cross(middle, dl),
        0.5 * segment.weight
      );
      const total = familyMoments[segment.family] || [0, 0, 0];
      familyMoments[segment.family] = add(total, contribution);
    }
    let maximumDivergence = 0;
    let maximumRelativeDivergence = 0;
    for (const x of [-1.6, 0, 1.6]) {
      for (const y of [-1.6, 0, 1.6]) {
        for (const z of [-2.4, 0.8, 2.4]) {
          const point = [x, y, z];
          const divergence = Math.abs(
            h1WakeDivergence(point, phase)
          );
          const fieldScale = norm(h1WakeField(point, phase))
            / H1_WAKE.skirtRadiusRp;
          maximumDivergence = Math.max(maximumDivergence, divergence);
          maximumRelativeDivergence = Math.max(
            maximumRelativeDivergence,
            divergence / Math.max(fieldScale, EPS)
          );
        }
      }
    }
    const splitResidual = Math.abs(
      1 - H1_WAKE.throatFraction - H1_WAKE.poloidalFraction
    );
    return {
      circuitCount: H1_WAKE.circuitCount,
      convergentCount: H1_WAKE.circuitCount,
      poloidalCount: H1_WAKE.circuitCount,
      expulsiveCount: H1_WAKE.circuitCount,
      exteriorCount: H1_WAKE.circuitCount,
      splitResidual,
      rejoinResidual: splitResidual,
      pairedFluxResidual: Math.abs(1 - 1),
      maximumSampledDivergence: maximumDivergence,
      maximumRelativeDivergence,
      declaredRelativeDivergenceTolerance: 0.01,
      divergenceWithinTolerance:
        maximumRelativeDivergence <= 0.01,
      fieldConstruction: 'U = curl(A) from closed filament vector potential',
      signedGeometricMomentByFamily: familyMoments,
      electromagneticBridge:
        'PENDING — no dimensional spation-flow to effective-current mapping'
    };
  }

  const THREE_NUCLEON_MESH_BOUNDS = Object.freeze({
    separationRp: [1.4, 2.8],
    openingRadians: [2 * Math.PI / 3, Math.PI],
    tiltRadians: [Math.PI / 4, 3 * Math.PI / 4],
    toroidalPhase: [0, TAU],
    poloidalPhase: [0, TAU],
    wakeCompliance: [0, 0.45],
    splitShift: [-0.35, 0.35],
    energyBridge: [0.01, 100],
    magneticBridge: [-20, 20]
  });
  const WAKE_MESH_BOUNDS = Object.freeze({
    H2: Object.freeze({
      separationRp: [1.4, 2.6],
      tiltRadians: [Math.PI / 4, 3 * Math.PI / 4],
      toroidalPhase: [0, TAU],
      poloidalPhase: [0, TAU],
      wakeCompliance: [0, 0.45],
      splitShift: [-0.35, 0.35],
      energyBridge: [0.01, 100],
      magneticBridge: [-20, 20]
    }),
    H3: THREE_NUCLEON_MESH_BOUNDS,
    He3: THREE_NUCLEON_MESH_BOUNDS
  });

  function quaternionMultiply(a, b) {
    return [
      a[3] * b[0] + a[0] * b[3] + a[1] * b[2] - a[2] * b[1],
      a[3] * b[1] - a[0] * b[2] + a[1] * b[3] + a[2] * b[0],
      a[3] * b[2] + a[0] * b[1] - a[1] * b[0] + a[2] * b[3],
      a[3] * b[3] - a[0] * b[0] - a[1] * b[1] - a[2] * b[2]
    ];
  }

  function quaternionFromAxisAngle(axis, angle) {
    const direction = unit(axis);
    const sine = Math.sin(angle / 2);
    return [
      direction[0] * sine,
      direction[1] * sine,
      direction[2] * sine,
      Math.cos(angle / 2)
    ];
  }

  function quaternionRotate(quaternion, vector) {
    const q = quaternion;
    const qv = [q[0], q[1], q[2]];
    const uv = cross(qv, vector);
    const uuv = cross(qv, uv);
    return add(vector, add(mul(uv, 2 * q[3]), mul(uuv, 2)));
  }

  function wakePoseOrientation(tilt, poloidalPhase, azimuth = 0) {
    return quaternionMultiply(
      quaternionFromAxisAngle([0, 0, 1], azimuth),
      quaternionMultiply(
        quaternionFromAxisAngle([0, 1, 0], tilt),
        quaternionFromAxisAngle([0, 0, 1], poloidalPhase)
      )
    );
  }

  function deformWakePoint(point, compliance = 0) {
    if (!(compliance > 0)) return [...point];
    const radius = Math.hypot(point[0], point[1]);
    const angle = Math.atan2(point[1], point[0]);
    const throatInfluence = Math.exp(
      -(point[2] * point[2]) / (2 * 1.15 * 1.15)
    );
    const radialScale = 1 - compliance * 0.42 * throatInfluence;
    const axialScale = 1 + compliance * 0.30;
    const phaseWarp =
      compliance * 0.55 * Math.tanh(point[2] / 1.4);
    return [
      radius * radialScale * Math.cos(angle + phaseWarp),
      radius * radialScale * Math.sin(angle + phaseWarp),
      point[2] * axialScale
    ];
  }

  function operatingWakeSegments(pose = {}, samples = 8) {
    const compliance = pose.wakeCompliance || 0;
    const splitShift = pose.splitShift || 0;
    const throatFraction = H1_WAKE.throatFraction + splitShift;
    const poloidalFraction = 1 - throatFraction;
    if (
      throatFraction <= 0.05
      || throatFraction >= 0.95
    ) {
      return [];
    }
    const familyScale = {
      throat: throatFraction / H1_WAKE.throatFraction,
      poloidal: poloidalFraction / H1_WAKE.poloidalFraction
    };
    const handedness = pose.handedness == null ? 1 : pose.handedness;
    return h1WakeSegments(
      pose.toroidalPhase || 0,
      samples
    ).map(segment => ({
      ...segment,
      a: deformWakePoint(segment.a, compliance),
      b: deformWakePoint(segment.b, compliance),
      weight: segment.weight
        * (familyScale[segment.family] || 1)
        * handedness
    }));
  }

  function transformPreparedSegments(segments, pose) {
    const centre = pose.centreRp || [0, 0, 0];
    const orientation = pose.orientation || [0, 0, 0, 1];
    const scale = pose.scale == null ? 1 : pose.scale;
    return segments.map(segment => ({
      ...segment,
      unitIndex: pose.unitIndex,
      species: pose.type,
      a: add(centre, quaternionRotate(
        orientation,
        mul(segment.a, scale)
      )),
      b: add(centre, quaternionRotate(
        orientation,
        mul(segment.b, scale)
      ))
    }));
  }

  function transformWakeSegments(pose, samples = 8) {
    return transformPreparedSegments(
      operatingWakeSegments(pose, samples),
      pose
    );
  }

  function segmentMoment(segments) {
    return segments.reduce((sum, segment) => {
      const middle = mul(add(segment.a, segment.b), 0.5);
      const dl = sub(segment.b, segment.a);
      return add(sum, mul(cross(middle, dl), 0.5 * segment.weight));
    }, [0, 0, 0]);
  }

  function scaleSegments(segments, scale, source) {
    return segments.map(segment => ({
      ...segment,
      source,
      weight: segment.weight * scale
    }));
  }

  function neutronMagneticCalibration(samples = 12) {
    const protonBasis = operatingWakeSegments({
      handedness: 1,
      toroidalPhase: 0,
      wakeCompliance: 0,
      splitShift: 0
    }, samples);
    const electronBasis = operatingWakeSegments({
      handedness: -1,
      toroidalPhase: Math.PI / 4,
      wakeCompliance: 0,
      splitShift: 0
    }, samples);
    const protonBasisMoment = segmentMoment(protonBasis)[2];
    const electronBasisMoment = segmentMoment(electronBasis)[2];
    const protonBridge =
      SEED_MEASURED.protonMomentMuN / protonBasisMoment;
    const protonContributionMuN =
      protonBridge * protonBasisMoment;
    const requiredElectronContributionMuN =
      SEED_MEASURED.neutronMomentMuN - protonContributionMuN;
    const seatedElectronCoefficient =
      requiredElectronContributionMuN / electronBasisMoment;
    const electronContributionMuN =
      seatedElectronCoefficient * electronBasisMoment;
    const netMomentMuN =
      protonContributionMuN + electronContributionMuN;
    return {
      classification: 'CALIBRATED(1)',
      protonBridgeMuNPerGeometricMoment: protonBridge,
      seatedElectronCoefficientMuNPerGeometricMoment:
        seatedElectronCoefficient,
      protonContributionMuN,
      seatedElectronContributionMuN: electronContributionMuN,
      netMomentMuN,
      targetMomentMuN: SEED_MEASURED.neutronMomentMuN,
      residualMuN: netMomentMuN - SEED_MEASURED.neutronMomentMuN,
      suppressionRatio:
        Math.abs(netMomentMuN)
        / (
          Math.abs(protonContributionMuN)
          + Math.abs(electronContributionMuN)
        ),
      protonBasisMoment,
      seatedElectronBasisMoment: electronBasisMoment,
      phaseOffsetRadians: Math.PI / 4,
      mapping:
        'proton-form circulation + seated-electron counter-circulation'
    };
  }

  function speciesMagneticSegments(pose, samples = 12) {
    const calibration = neutronMagneticCalibration(samples);
    const common = {
      ...pose,
      handedness: 1
    };
    const protonBasis = operatingWakeSegments(common, samples);
    const proton = scaleSegments(
      protonBasis,
      calibration.protonBridgeMuNPerGeometricMoment,
      'proton-form'
    );
    if (pose.type === 'p') {
      return transformPreparedSegments(proton, pose);
    }
    const electronBasis = operatingWakeSegments({
      ...common,
      handedness: -1,
      toroidalPhase:
        (pose.toroidalPhase || 0) + calibration.phaseOffsetRadians
    }, samples);
    const electron = scaleSegments(
      electronBasis,
      calibration.seatedElectronCoefficientMuNPerGeometricMoment,
      'seated-electron-counter'
    );
    return transformPreparedSegments(
      [...proton, ...electron],
      pose
    );
  }

  function wakeMeshPairMetrics(firstPose, secondPose, samples = 8) {
    const centreDistance = norm(sub(
      firstPose.centreRp || [0, 0, 0],
      secondPose.centreRp || [0, 0, 0]
    ));
    if (centreDistance > 2.5 * H1_WAKE.tailLengthRp) {
      return {
        coupling: 0,
        contactCoupling: 0,
        signedAlignment: 0,
        minimumDistance: centreDistance,
        byFamily: {},
        integration: {
          representation: '-integral U_i dot U_j dV',
          samples: 0,
          volumeElement: 0
        }
      };
    }
    const first = transformWakeSegments(firstPose, Math.max(6, samples));
    const second = transformWakeSegments(secondPose, Math.max(6, samples));
    const endpoints = [...first, ...second].flatMap(segment => [
      segment.a,
      segment.b
    ]);
    const minimum = [0, 1, 2].map(axis =>
      Math.min(...endpoints.map(point => point[axis])) - 0.25);
    const maximum = [0, 1, 2].map(axis =>
      Math.max(...endpoints.map(point => point[axis])) + 0.25);
    const counts = [5, 5, 7];
    const spacing = counts.map((count, axis) =>
      (maximum[axis] - minimum[axis]) / count);
    const volumeElement = spacing[0] * spacing[1] * spacing[2];
    let coupling = 0;
    let contactCoupling = 0;
    let signedAlignment = 0;
    const byFamily = {};
    const contactFamilies = new Set([
      'convergent',
      'throat',
      'poloidal'
    ]);
    let sampleCount = 0;
    for (let ix = 0; ix < counts[0]; ix++) {
      for (let iy = 0; iy < counts[1]; iy++) {
        for (let iz = 0; iz < counts[2]; iz++) {
          const point = [
            minimum[0] + (ix + 0.5) * spacing[0],
            minimum[1] + (iy + 0.5) * spacing[1],
            minimum[2] + (iz + 0.5) * spacing[2]
          ];
          const firstFamilies = analyticWakeFieldByFamily(point, first);
          const secondFamilies = analyticWakeFieldByFamily(point, second);
          const firstField = Object.values(firstFamilies)
            .reduce((sum, field) => add(sum, field), [0, 0, 0]);
          const secondField = Object.values(secondFamilies)
            .reduce((sum, field) => add(sum, field), [0, 0, 0]);
          const signed = -dot(firstField, secondField) * volumeElement;
          coupling += signed;
          signedAlignment += dot(firstField, secondField) * volumeElement;
          for (const [firstFamily, firstFamilyField] of
            Object.entries(firstFamilies)) {
            for (const [secondFamily, secondFamilyField] of
              Object.entries(secondFamilies)) {
              const local = -dot(
                firstFamilyField,
                secondFamilyField
              ) * volumeElement;
              const key = `${firstFamily}:${secondFamily}`;
              byFamily[key] = (byFamily[key] || 0) + local;
              if (
                contactFamilies.has(firstFamily)
                && contactFamilies.has(secondFamily)
              ) {
                contactCoupling += Math.abs(local);
              }
            }
          }
          sampleCount++;
        }
      }
    }
    return {
      coupling,
      contactCoupling,
      signedAlignment,
      minimumDistance: centreDistance,
      byFamily,
      integration: {
        representation: '-integral U_i dot U_j dV',
        samples: sampleCount,
        volumeElement
      }
    };
  }

  function divergenceFromSegments(point, segments, step = 0.04) {
    let divergence = 0;
    for (let axis = 0; axis < 3; axis++) {
      const plus = [...point];
      const minus = [...point];
      plus[axis] += step;
      minus[axis] -= step;
      divergence += (
        wakeFieldFromSegments(plus, segments, step)[axis]
        - wakeFieldFromSegments(minus, segments, step)[axis]
      ) / (2 * step);
    }
    return divergence;
  }

  function farFieldDipoleFit(segments) {
    const extent = segments.reduce((maximum, segment) =>
      Math.max(maximum, norm(segment.a), norm(segment.b)), 0);
    const baseRadius = Math.max(80, 8 * extent);
    const radii = [baseRadius, 1.25 * baseRadius, 1.5 * baseRadius];
    const axial = radii.map(radius =>
      wakeFieldFromSegments([0, 0, radius], segments, 0.3)[2]
      * radius * radius * radius / 2);
    const equatorial = radii.map(radius =>
      -wakeFieldFromSegments([radius, 0, 0], segments, 0.3)[2]
      * radius * radius * radius);
    const mean = values =>
      values.reduce((sum, value) => sum + value, 0) / values.length;
    const axialMean = mean(axial);
    const equatorialMean = mean(equatorial);
    return {
      axial,
      equatorial,
      axialMean,
      equatorialMean,
      mean: (axialMean + equatorialMean) / 2,
      routeRelativeResidual:
        Math.abs(axialMean - equatorialMean)
        / Math.max(Math.abs(axialMean), Math.abs(equatorialMean), EPS)
    };
  }

  function compositeWakeMesh(poses, magneticBridge = 0) {
    const pairs = [];
    const interactionByUnit = poses.map(() => 0);
    const familyLedger = {};
    for (let i = 0; i < poses.length; i++) {
      for (let j = i + 1; j < poses.length; j++) {
        const metrics = wakeMeshPairMetrics(poses[i], poses[j]);
        pairs.push({ i, j, ...metrics });
        interactionByUnit[i] += metrics.coupling / 2;
        interactionByUnit[j] += metrics.coupling / 2;
        for (const [family, value] of Object.entries(metrics.byFamily)) {
          familyLedger[family] = (familyLedger[family] || 0) + value;
        }
      }
    }
    const segments = [];
    const baseSegments = [];
    const interactionSegments = [];
    const signedContributions = [];
    poses.forEach((pose, index) => {
      const unitPose = { ...pose, unitIndex: index };
      const speciesBase = speciesMagneticSegments(unitPose, 12);
      const baseMoment = segmentMoment(speciesBase)[2];
      speciesBase.forEach(segment => {
        const entry = { ...segment, ledger: 'frozen-species' };
        baseSegments.push(entry);
        segments.push(entry);
      });
      const interactionBasis = transformWakeSegments(unitPose, 12);
      const interactionBasisMoment = segmentMoment(interactionBasis)[2];
      const interactionMomentMuN =
        magneticBridge * interactionByUnit[index];
      const interactionScale = Math.abs(interactionBasisMoment) > EPS
        ? interactionMomentMuN / interactionBasisMoment
        : 0;
      scaleSegments(
        interactionBasis,
        interactionScale,
        'mesh-interaction'
      ).forEach(segment => {
        const entry = { ...segment, ledger: 'mesh-interaction' };
        interactionSegments.push(entry);
        segments.push(entry);
      });
      signedContributions.push({
        unit: index,
        type: pose.type,
        frozenSpeciesMomentMuN: baseMoment,
        interactionMomentMuN,
        totalMomentMuN: baseMoment + interactionMomentMuN,
        internal: pose.type === 'n'
          ? neutronMagneticCalibration(12)
          : {
            classification: 'CALIBRATED free-proton bridge',
            protonContributionMuN: SEED_MEASURED.protonMomentMuN
          }
      });
    });
    const integral = segmentMoment(segments);
    const farField = farFieldDipoleFit(segments);
    const probePoints = [
      [0, 0, 0],
      [1.5, 0, 0],
      [-1.5, 0, 0],
      [0, 0, 1.5],
      [0, 0, -1.5]
    ];
    let maximumRelativeDivergence = 0;
    for (const point of probePoints) {
      const divergence = Math.abs(
        divergenceFromSegments(point, segments)
      );
      const scale = norm(wakeFieldFromSegments(point, segments, 0.04));
      maximumRelativeDivergence = Math.max(
        maximumRelativeDivergence,
        divergence / Math.max(scale, EPS)
      );
    }
    return {
      poses,
      segments,
      baseSegments,
      interactionSegments,
      pairs,
      meshOverlap: pairs.reduce(
        (sum, pair) => sum + pair.coupling,
        0
      ),
      interactionByUnit,
      signedContributions,
      familyLedger,
      neutronCalibration: neutronMagneticCalibration(12),
      deformationLedger: poses.map((pose, index) => ({
        unit: index,
        type: pose.type,
        wakeCompliance: pose.wakeCompliance || 0,
        throatFraction:
          H1_WAKE.throatFraction + (pose.splitShift || 0),
        poloidalFraction:
          H1_WAKE.poloidalFraction - (pose.splitShift || 0),
        incomingPhaseSectors: H1_WAKE.circuitCount
      })),
      sectorCorrespondences: pairs.filter(pair => pair.coupling > EPS).length
        * H1_WAKE.circuitCount,
      magneticIntegralMuN: integral[2],
      magneticFarFieldMuN: farField.mean,
      magneticRouteResidual:
        Math.abs(integral[2] - farField.mean)
        / Math.max(Math.abs(integral[2]), EPS),
      farField,
      maximumRelativeDivergence,
      splitResidual: Math.max(
        0,
        ...poses.map(pose => Math.abs(
          1
          - (H1_WAKE.throatFraction + (pose.splitShift || 0))
          - (H1_WAKE.poloidalFraction - (pose.splitShift || 0))
        ))
      ),
      rejoinResidual: Math.max(
        0,
        ...poses.map(pose => Math.abs(
          1
          - (H1_WAKE.throatFraction + (pose.splitShift || 0))
          - (H1_WAKE.poloidalFraction - (pose.splitShift || 0))
        ))
      ),
      circuitCount: poses.length * H1_WAKE.circuitCount,
      closedCircuitCount: poses.length * H1_WAKE.circuitCount
    };
  }

  function electricQuadrupoleFm2(poses, RpFm) {
    const masses = poses.map(pose => pose.type === 'p'
      ? SEED_MEASURED.protonMassKg
      : SEED_MEASURED.neutronMassKg);
    const totalMass = masses.reduce((sum, value) => sum + value, 0);
    const centreOfMass = poses.reduce(
      (sum, pose, index) =>
        add(sum, mul(pose.centreRp, masses[index] / totalMass)),
      [0, 0, 0]
    );
    const protonPoints = [];
    for (const pose of poses.filter(item => item.type === 'p')) {
      for (let index = 0; index < 512; index++) {
        const local = h1Point(TAU * index / 512, pose.scale || 1);
        protonPoints.push(sub(
          add(pose.centreRp, quaternionRotate(pose.orientation, local)),
          centreOfMass
        ));
      }
    }
    const quadrupoleAxis = poses.length > 1
      ? unit(sub(poses[poses.length - 1].centreRp, poses[0].centreRp))
      : [0, 0, 1];
    const mean = protonPoints.reduce((sum, point) => {
      const axial = dot(point, quadrupoleAxis);
      return sum + 3 * axial * axial - dot(point, point);
    }, 0)
      / Math.max(protonPoints.length, 1);
    return mean * RpFm * RpFm;
  }

  function lightNucleusTargets(key) {
    if (key === 'H2') {
      return {
        bindingEnergyMeV: SEED_MEASURED.deuteronBindingMeV,
        magneticMomentMuN: SEED_MEASURED.deuteronMomentMuN,
        electricQuadrupoleFm2: SEED_MEASURED.deuteronQuadrupoleFm2
      };
    }
    if (key === 'H3') {
      return {
        bindingEnergyMeV: SEED_MEASURED.tritonBindingMeV,
        magneticMomentMuN: SEED_MEASURED.tritonMomentMuN
      };
    }
    if (key === 'He3') {
      return {
        bindingEnergyMeV: SEED_MEASURED.helionBindingMeV,
        magneticMomentMuN: SEED_MEASURED.helionMomentMuN
      };
    }
    throw new RangeError(`no light-nucleus calibration target for ${key}`);
  }

  function lightNucleusPoses(key, parameters) {
    const d = parameters.separationRp;
    const tilt = parameters.tiltRadians;
    const toroidal = parameters.toroidalPhase;
    const poloidal = parameters.poloidalPhase;
    const wakeCompliance = parameters.wakeCompliance || 0;
    const splitShift = parameters.splitShift || 0;
    if (key === 'H2') {
      return [
        {
          type: 'p',
          centreRp: [-d / 2, 0, 0],
          orientation: wakePoseOrientation(tilt / 2, 0, 0),
          scale: 1,
          toroidalPhase: 0,
          handedness: 1,
          wakeCompliance,
          splitShift
        },
        {
          type: 'n',
          centreRp: [d / 2, 0, 0],
          orientation: wakePoseOrientation(
            -tilt / 2,
            poloidal,
            Math.PI / 2
          ),
          scale: 1,
          toroidalPhase: toroidal,
          handedness: -1,
          wakeCompliance,
          splitShift,
          internalElectron: true
        }
      ];
    }
    const opening = parameters.openingRadians;
    const centreType = key === 'H3' ? 'p' : 'n';
    const outerType = key === 'H3' ? 'n' : 'p';
    const half = opening / 2;
    const outer = [Math.sin(half) * d, 0, Math.cos(half) * d];
    const outerMirror = [-outer[0], 0, outer[2]];
    return [
      {
        type: centreType,
        centreRp: [0, 0, 0],
        orientation: [0, 0, 0, 1],
        scale: 1,
        toroidalPhase: 0,
        handedness: centreType === 'p' ? 1 : -1,
        wakeCompliance,
        splitShift,
        internalElectron: centreType === 'n'
      },
      {
        type: outerType,
        centreRp: outer,
        orientation: wakePoseOrientation(tilt, poloidal, half),
        scale: 1,
        toroidalPhase: toroidal,
        handedness: outerType === 'p' ? 1 : -1,
        wakeCompliance,
        splitShift,
        internalElectron: outerType === 'n'
      },
      {
        type: outerType,
        centreRp: outerMirror,
        orientation: wakePoseOrientation(
          -tilt,
          -poloidal,
          -half
        ),
        scale: 1,
        toroidalPhase: -toroidal,
        handedness: outerType === 'p' ? 1 : -1,
        wakeCompliance,
        splitShift,
        internalElectron: outerType === 'n'
      }
    ];
  }

  function profiledMagneticRoutes(poses, pairs, magneticBridge) {
    const interactionByUnit = poses.map(() => 0);
    for (const pair of pairs) {
      interactionByUnit[pair.i] += pair.coupling / 2;
      interactionByUnit[pair.j] += pair.coupling / 2;
    }
    const segments = [];
    poses.forEach((pose, index) => {
      const unitPose = { ...pose, unitIndex: index };
      segments.push(...speciesMagneticSegments(unitPose, 12));
      const interactionBasis = transformWakeSegments(unitPose, 12);
      const basisMoment = segmentMoment(interactionBasis)[2];
      const targetMoment = magneticBridge * interactionByUnit[index];
      const scale = Math.abs(basisMoment) > EPS
        ? targetMoment / basisMoment
        : 0;
      segments.push(...scaleSegments(
        interactionBasis,
        scale,
        'mesh-interaction'
      ));
    });
    const integral = segmentMoment(segments);
    const farField = farFieldDipoleFit(segments);
    return {
      integralMuN: integral[2],
      farFieldMuN: farField.mean,
      relativeResidual:
        Math.abs(integral[2] - farField.mean)
        / Math.max(Math.abs(integral[2]), EPS)
    };
  }

  function profiledLightCalibration(key, parameters, RpFm) {
    const targets = lightNucleusTargets(key);
    const poses = lightNucleusPoses(key, parameters);
    const pairs = [];
    let overlap = 0;
    let sameSpeciesOverlap = 0;
    let weakestUnlike = Infinity;
    for (let i = 0; i < poses.length; i++) {
      for (let j = i + 1; j < poses.length; j++) {
        const pair = wakeMeshPairMetrics(poses[i], poses[j]);
        pairs.push({ i, j, ...pair });
        overlap += pair.coupling;
        if (poses[i].type === poses[j].type) {
          if (pair.minimumDistance <= 2.8) {
            sameSpeciesOverlap += pair.contactCoupling;
          }
        } else {
          weakestUnlike = Math.min(weakestUnlike, pair.contactCoupling);
        }
      }
    }
    const frozenSpeciesSegments = poses.flatMap((pose, index) =>
      speciesMagneticSegments({ ...pose, unitIndex: index }, 12));
    const additiveMoment = segmentMoment(frozenSpeciesSegments)[2];
    const energyBridge = targets.bindingEnergyMeV
      / Math.max(overlap, EPS);
    const magneticBridge = (
      targets.magneticMomentMuN - additiveMoment
    ) / Math.max(overlap, EPS);
    const magneticRoutes = profiledMagneticRoutes(
      poses,
      pairs,
      magneticBridge
    );
    const bounds = WAKE_MESH_BOUNDS[key];
    const coefficientValid =
      energyBridge > bounds.energyBridge[0] + 1e-6
      && energyBridge < bounds.energyBridge[1] - 1e-6
      && magneticBridge > bounds.magneticBridge[0] + 1e-6
      && magneticBridge < bounds.magneticBridge[1] - 1e-6;
    const sameSpeciesRatio = sameSpeciesOverlap
      / Math.max(weakestUnlike, EPS);
    const quadrupole = key === 'H2'
      ? electricQuadrupoleFm2(poses, RpFm)
      : null;
    const quadrupoleResidual = key === 'H2'
      ? (quadrupole - targets.electricQuadrupoleFm2)
        / targets.electricQuadrupoleFm2
      : 0;
    const exclusionResidual = key === 'H3'
      ? Math.max(0, sameSpeciesRatio - 0.1)
      : 0;
    const exclusionPenalty = exclusionResidual > 0
      ? 1e3 + 25 * exclusionResidual * exclusionResidual
      : 0;
    const quadrupolePenalty =
      Math.abs(quadrupoleResidual) > 1e-4
        ? 1e3 + quadrupoleResidual * quadrupoleResidual
        : quadrupoleResidual * quadrupoleResidual;
    const contactMismatchPenalty = weakestUnlike > EPS ? 0 : 1e3;
    const coefficientPenalty = coefficientValid ? 0 : 1e3;
    const deformationPenalty =
      parameters.wakeCompliance > 0.01 ? 0 : 1e3;
    const magneticRoutePenalty =
      magneticRoutes.relativeResidual <= 0.05
        ? magneticRoutes.relativeResidual
          * magneticRoutes.relativeResidual
        : 1e3 + magneticRoutes.relativeResidual
          * magneticRoutes.relativeResidual;
    const objective =
      quadrupolePenalty
      + exclusionPenalty
      + contactMismatchPenalty
      + coefficientPenalty
      + deformationPenalty
      + magneticRoutePenalty
      + 1e-4 / Math.max(overlap, EPS);
    return {
      key,
      poses,
      pairs,
      targets,
      overlap,
      sameSpeciesOverlap,
      sameSpeciesRatio,
      additiveMomentMuN: additiveMoment,
      energyBridge,
      magneticBridge,
      magneticRoutes,
      quadrupoleFm2: quadrupole,
      quadrupoleResidual,
      contactMismatch: weakestUnlike <= EPS,
      coefficientValid,
      objective
    };
  }

  function fitLightNucleus(key, RpFm = H1_NUCLEON.canonicalRpFm) {
    const isPair = key === 'H2';
    const bounds = WAKE_MESH_BOUNDS[key];
    if (!bounds) {
      throw new RangeError(`no wake-mesh bounds for ${key}`);
    }
    const names = isPair
      ? [
        'separationRp',
        'tiltRadians',
        'toroidalPhase',
        'poloidalPhase',
        'wakeCompliance',
        'splitShift'
      ]
      : [
        'separationRp',
        'openingRadians',
        'tiltRadians',
        'toroidalPhase',
        'poloidalPhase',
        'wakeCompliance',
        'splitShift'
      ];
    const parameters = isPair
      ? {
        separationRp: 2,
        tiltRadians: Math.PI / 2,
        toroidalPhase: Math.PI,
        poloidalPhase: Math.PI / 2,
        wakeCompliance: 0.18,
        splitShift: 0
      }
      : {
        separationRp: 2.1,
        openingRadians: Math.PI,
        tiltRadians: Math.PI / 2,
        toroidalPhase: key === 'H3' ? 2 * Math.PI / 3 : 4 * Math.PI / 3,
        poloidalPhase: Math.PI / 2,
        wakeCompliance: 0.18,
        splitShift: 0
      };
    const steps = Object.fromEntries(names.map(name => [
      name,
      (bounds[name][1] - bounds[name][0]) / 4
    ]));
    let best = profiledLightCalibration(key, parameters, RpFm);
    for (let round = 0; round < 14; round++) {
      for (const name of names) {
        for (const direction of [-1, 1]) {
          const candidateParameters = {
            ...parameters,
            [name]: Math.min(
              bounds[name][1],
              Math.max(
                bounds[name][0],
                parameters[name] + direction * steps[name]
              )
            )
          };
          const candidate = profiledLightCalibration(
            key,
            candidateParameters,
            RpFm
          );
          if (candidate.objective + 1e-15 < best.objective) {
            Object.assign(parameters, candidateParameters);
            best = candidate;
          }
        }
      }
      names.forEach(name => {
        steps[name] /= 2;
      });
    }
    best = profiledLightCalibration(key, parameters, RpFm);
    const mesh = compositeWakeMesh(best.poses, best.magneticBridge);
    const bindingModel =
      best.energyBridge * mesh.meshOverlap;
    const magneticModel = mesh.magneticIntegralMuN;
    const relative = (model, target) =>
      (model - target) / Math.max(Math.abs(target), EPS);
    const targetResiduals = {
      binding: relative(
        bindingModel,
        best.targets.bindingEnergyMeV
      ),
      magnetic: relative(
        magneticModel,
        best.targets.magneticMomentMuN
      ),
      quadrupole: key === 'H2'
        ? relative(
          best.quadrupoleFm2,
          best.targets.electricQuadrupoleFm2
        )
        : null
    };
    const parameterBoundsSatisfied = names.every(name =>
      parameters[name] > bounds[name][0] + 1e-6
      && parameters[name] < bounds[name][1] - 1e-6);
    const parameterCount = names.length + 2;
    const outputPoses = best.poses.map(pose => ({
      ...pose,
      centre: pose.centreRp.map(value => value * RpFm),
      phase: pose.toroidalPhase
    }));
    return {
      key,
      classification: `CALIBRATED(${parameterCount})`,
      parameterCount,
      parameters: {
        ...parameters,
        energyBridgeMeVPerOverlap: best.energyBridge,
        magneticBridgeMuNPerMoment: best.magneticBridge
      },
      bounds,
      targets: best.targets,
      model: {
        bindingEnergyMeV: bindingModel,
        magneticMomentMuN: magneticModel,
        electricQuadrupoleFm2: best.quadrupoleFm2
      },
      residuals: targetResiduals,
      poses: outputPoses,
      mesh: {
        overlap: mesh.meshOverlap,
        pairLedger: mesh.pairs.map(pair => ({
          i: pair.i,
          j: pair.j,
          coupling: pair.coupling,
          contactCoupling: pair.contactCoupling,
          signedAlignment: pair.signedAlignment,
          minimumDistanceRp: pair.minimumDistance,
          integration: pair.integration,
          byFamily: pair.byFamily
        })),
        familyLedger: mesh.familyLedger,
        signedContributions: mesh.signedContributions,
        neutronCalibration: mesh.neutronCalibration,
        deformationLedger: mesh.deformationLedger,
        sectorCorrespondences: mesh.sectorCorrespondences,
        sameSpeciesOverlapRatio: best.sameSpeciesRatio,
        circuitCount: mesh.circuitCount,
        closedCircuitCount: mesh.closedCircuitCount,
        splitResidual: mesh.splitResidual,
        rejoinResidual: mesh.rejoinResidual,
        maximumRelativeDivergence: mesh.maximumRelativeDivergence
      },
      magneticRoutes: {
        integralMuN: mesh.magneticIntegralMuN,
        farFieldMuN: mesh.magneticFarFieldMuN,
        relativeResidual: mesh.magneticRouteResidual,
        axial: mesh.farField.axial,
        equatorial: mesh.farField.equatorial
      },
      coefficientBoundsSatisfied:
        best.coefficientValid && parameterBoundsSatisfied,
      parameterBoundsSatisfied,
      contactMismatch: best.contactMismatch,
      neutronNeutronContactExcluded:
        key !== 'H3' || best.sameSpeciesRatio < 0.1,
      spinParityDiagnostic: {
        fitted: false,
        frameReturnRadians: 4 * Math.PI,
        netHandedness: best.poses.reduce(
          (sum, pose) => sum + pose.handedness,
          0
        ),
        status: 'PENDING — no native periodicity-to-spin mapping'
      }
    };
  }

  function grammar(A, Z) {
    if (Z === 0 && A === 1) {
      return { A, Z, nd: 0, nt: 0, valid: true, seed: true };
    }
    if (Z === 1 && A >= 1 && A <= 3) {
      return { A, Z, nd: 0, nt: 0, valid: true, seed: true };
    }
    if (Z === 2 && A === 3) {
      return { A, Z, nd: 0, nt: 0, valid: true, seed: true };
    }
    const nd = 3 * Z - A - 2;
    const nt = A - 2 * Z;
    return {
      A,
      Z,
      nd,
      nt,
      valid: Number.isInteger(A) && Number.isInteger(Z)
        && Z >= 2 && A >= Z && nd >= 0 && nt >= 0,
      seed: false
    };
  }

  function deuteronClosureProperties() {
    const separatedMassKg = SEED_MEASURED.protonMassKg
      + SEED_MEASURED.neutronMassKg;
    const boundMassKg = SEED_MEASURED.deuteronMassKg;
    const bindingMassKg = separatedMassKg - boundMassKg;
    const massClosureFraction = bindingMassKg / separatedMassKg;
    const linearClosureScale = Math.cbrt(1 - massClosureFraction);
    const additiveMoment = SEED_MEASURED.protonMomentMuN
      + SEED_MEASURED.neutronMomentMuN;
    return {
      bindingEnergyMeV: SEED_MEASURED.deuteronBindingMeV,
      bindingMassKg,
      separatedMassKg,
      boundMassKg,
      massClosureFraction,
      linearClosureScale,
      measuredMomentMuN: SEED_MEASURED.deuteronMomentMuN,
      additiveFreeMomentMuN: additiveMoment,
      bindingMomentResidualMuN:
        SEED_MEASURED.deuteronMomentMuN - additiveMoment
    };
  }

  function threeNucleonClosureProperties(key) {
    const isTriton = key === 'H3';
    if (!isTriton && key !== 'He3') {
      throw new RangeError(`unsupported three-nucleon seed: ${key}`);
    }
    const protonCount = isTriton ? 1 : 2;
    const neutronCount = 3 - protonCount;
    const bindingEnergyMeV = isTriton
      ? SEED_MEASURED.tritonBindingMeV
      : SEED_MEASURED.helionBindingMeV;
    const measuredMomentMuN = isTriton
      ? SEED_MEASURED.tritonMomentMuN
      : SEED_MEASURED.helionMomentMuN;
    const separatedMassKg =
      protonCount * SEED_MEASURED.protonMassKg
      + neutronCount * SEED_MEASURED.neutronMassKg;
    const boundMassKg = isTriton
      ? SEED_MEASURED.tritonMassKg
      : SEED_MEASURED.helionMassKg;
    const bindingMassKg = separatedMassKg - boundMassKg;
    const additiveFreeMomentMuN =
      protonCount * SEED_MEASURED.protonMomentMuN
      + neutronCount * SEED_MEASURED.neutronMomentMuN;
    return {
      bindingEnergyMeV,
      bindingMassKg,
      separatedMassKg,
      boundMassKg,
      massClosureFraction: bindingMassKg / separatedMassKg,
      linearClosureScale:
        Math.cbrt(1 - bindingMassKg / separatedMassKg),
      measuredMomentMuN,
      additiveFreeMomentMuN,
      bindingMomentResidualMuN:
        measuredMomentMuN - additiveFreeMomentMuN
    };
  }

  function seatDirections(count) {
    const s = 1 / Math.sqrt(3);
    if (count === 0) return [];
    if (count === 1) return [[0, 0, 1]];
    if (count === 2) return [[0, 0, 1], [0, 0, -1]];
    if (count === 3) {
      return Array.from({ length: 3 }, (_, i) => {
        const a = TAU * i / 3;
        return [Math.cos(a), Math.sin(a), 0];
      });
    }
    if (count === 4) {
      return [
        [s, s, s],
        [s, -s, -s],
        [-s, s, -s],
        [-s, -s, s]
      ];
    }
    if (count === 5) {
      return [
        [1, 0, 0],
        [-0.5, Math.sqrt(3) / 2, 0],
        [-0.5, -Math.sqrt(3) / 2, 0],
        [0, 0, 1],
        [0, 0, -1]
      ];
    }
    if (count === 6) {
      return [
        [0, 0, 1], [0, 0, -1],
        [1, 0, 0], [0, 1, 0],
        [-1, 0, 0], [0, -1, 0]
      ];
    }
    throw new RangeError('Atomicus H-to-O seating is registered only for 0–6 satellite modules');
  }

  function atomicusSeats(count) {
    return seatDirections(count).map((dir, index) => {
      return {
        constructionIndex: index + 1,
        pairsWithSeat:
          (count === 2 && index === 1) ? 1
          : ((count === 6 && index === 5) ? 3 : null),
        dir,
        region: Math.abs(dir[2]) < EPS
          ? 'equatorial'
          : (Math.abs(dir[2]) > 1 - EPS ? 'polar' : 'tropical')
      };
    });
  }

  function polarShellDirections(capacity, phase = 0) {
    const pairCount = capacity / 2 - 1;
    const z = 1 / 3;
    const rho = Math.sqrt(1 - z * z);
    const result = [[0, 0, 1], [0, 0, -1]];
    for (let i = 0; i < pairCount; i++) {
      const lower = phase + TAU * i / pairCount;
      const upper = lower + Math.PI / pairCount;
      result.push(
        [rho * Math.cos(lower), rho * Math.sin(lower), -z],
        [rho * Math.cos(upper), rho * Math.sin(upper), z]
      );
    }
    return result;
  }

  function cuboctahedralThreeSixThree() {
    const z = Math.sqrt(2 / 3);
    const rho = 1 / Math.sqrt(3);
    const result = [];
    for (let i = 0; i < 3; i++) {
      const angle = TAU * i / 3;
      result.push([rho * Math.cos(angle), rho * Math.sin(angle), z]);
    }
    for (let i = 0; i < 6; i++) {
      const angle = Math.PI / 6 + TAU * i / 6;
      result.push([Math.cos(angle), Math.sin(angle), 0]);
    }
    for (let i = 0; i < 3; i++) {
      const angle = Math.PI / 3 + TAU * i / 3;
      result.push([rho * Math.cos(angle), rho * Math.sin(angle), -z]);
    }
    return result;
  }

  function icosahedralDirections() {
    const phi = (1 + Math.sqrt(5)) / 2;
    const points = [];
    for (const a of [-1, 1]) {
      for (const b of [-phi, phi]) {
        points.push([0, a, b], [a, b, 0], [b, 0, a]);
      }
    }
    return points.map(unit).sort((a, b) =>
      (b[2] - a[2]) || (Math.atan2(a[1], a[0]) - Math.atan2(b[1], b[0])));
  }

  function triangularLinkDirections(capacity) {
    const n = Math.round((Math.sqrt(1 + 4 * capacity) - 1) / 2);
    if (n * (n + 1) !== capacity) {
      throw new RangeError(`invalid triangular-link capacity ${capacity}`);
    }
    const topZ = n === 3 ? Math.sqrt(2 / 3) : 0.58;
    const topR = Math.sqrt(1 - topZ * topZ);
    const equatorialCount = n * (n - 1);
    const result = [];
    for (let i = 0; i < n; i++) {
      const angle = TAU * i / n;
      result.push([topR * Math.cos(angle), topR * Math.sin(angle), topZ]);
    }
    for (let i = 0; i < equatorialCount; i++) {
      const angle = Math.PI / equatorialCount + TAU * i / equatorialCount;
      result.push([Math.cos(angle), Math.sin(angle), 0]);
    }
    for (let i = 0; i < n; i++) {
      const angle = Math.PI / n + TAU * i / n;
      result.push([topR * Math.cos(angle), topR * Math.sin(angle), -topZ]);
    }
    return result;
  }

  function faceNormalFourteenDirections() {
    const s = 1 / Math.sqrt(3);
    return [
      [0, 0, 1], [0, 0, -1],
      [1, 0, 0], [-1, 0, 0], [0, 1, 0], [0, -1, 0],
      [s, s, s], [s, -s, s], [-s, s, s], [-s, -s, s],
      [s, s, -s], [s, -s, -s], [-s, s, -s], [-s, -s, -s]
    ];
  }

  function completeShellDirections(shell) {
    if (shell.geometry === 'oct') return seatDirections(6);
    if (shell.geometry === 'ico') return icosahedralDirections();
    if (shell.geometry === 'stella' || shell.geometry === 'polar') {
      return polarShellDirections(shell.capacity, shell.scheduleIndex * 0.15);
    }
    if (shell.geometry === 'cuboct-3-6-3') {
      return cuboctahedralThreeSixThree();
    }
    if (shell.geometry === 'triangular-links') {
      return triangularLinkDirections(shell.capacity);
    }
    if (shell.geometry === 'face-normal-14') {
      return faceNormalFourteenDirections();
    }
    throw new RangeError(`unregistered shell geometry ${shell.geometry}`);
  }

  function partialShellDirections(shell, occupancy) {
    if (occupancy <= 6) return seatDirections(occupancy);
    return completeShellDirections(shell).slice(0, occupancy);
  }

  function parentInterstitials(directions, parentModules) {
    if (!parentModules.length) return directions.map(() => []);
    const seatedParents = parentModules.filter(module => Array.isArray(module.seat));
    if (!seatedParents.length) return directions.map(() => [0]);
    return directions.map(direction => seatedParents
      .map(module => ({
        index: module.index,
        score: dot(direction, unit(module.seat))
      }))
      .sort((a, b) => (b.score - a.score) || (a.index - b.index))
      .slice(0, 3)
      .map(entry => entry.index));
  }

  function universalShellAllocation(n_d, n_t) {
    let dLeft = n_d;
    let tLeft = n_t;
    const shells = [];
    for (const [scheduleIndex, frozen] of SEED_MEASURED.shellSchedule.entries()) {
      const remaining = frozen.species === 'd' ? dLeft : tLeft;
      if (remaining <= 0) continue;
      const occupancy = Math.min(remaining, frozen.capacity);
      const shell = {
        ...frozen,
        scheduleIndex,
        occupancy,
        full: occupancy === frozen.capacity
      };
      shell.directions = partialShellDirections(shell, occupancy);
      shells.push(shell);
      if (frozen.species === 'd') dLeft -= occupancy;
      else tLeft -= occupancy;
    }
    if (dLeft || tLeft) {
      throw new RangeError(
        `closure schedule exhausted with ${dLeft} deuterons and ${tLeft} tritons`
      );
    }
    const fullTritonClosures = shells.filter(
      shell => shell.species === 't' && shell.full
    ).length;
    const opening = SEED_MEASURED.tritonOpeningScale;
    const closing = SEED_MEASURED.tritonClosingScale;
    const contractionScale = opening
      - fullTritonClosures
        * (opening - closing)
        / SEED_MEASURED.tritonShellCapacities.length;
    return { shells, fullTritonClosures, contractionScale };
  }

  function minimumSeatAngle(directions) {
    if (directions.length < 2) return Math.PI;
    let result = Math.PI;
    for (let i = 0; i < directions.length; i++) {
      for (let j = i + 1; j < directions.length; j++) {
        const cosine = Math.max(-1, Math.min(1, dot(directions[i], directions[j])));
        result = Math.min(result, Math.acos(cosine));
      }
    }
    return result;
  }

  function torusBraidPoint(u, Rp, poloidalTurns = BRAID.poloidalTurns) {
    const major = BRAID.majorRadiusFraction * Rp;
    const helix = BRAID.helixRadiusFraction * Rp;
    const phi = BRAID.majorTours * u;
    const psi = Math.PI + poloidalTurns * u;
    const radial = major + helix * Math.cos(psi);
    return [
      radial * Math.cos(phi),
      radial * Math.sin(phi),
      helix * Math.sin(psi)
    ];
  }

  function quadrupleHelixPoint(u, Rp) {
    return torusBraidPoint(u, Rp, BRAID.poloidalTurns);
  }

  // Compatibility name retained for callers; this is now the repaired (4,5)
  // cyclic quadruple helix, not the withdrawn (4,1) shortcut.
  function fourTourPoint(u, Rp) {
    return quadrupleHelixPoint(u, Rp);
  }

  function braidStrandPoint(strand, theta, Rp) {
    const lane = ((strand % BRAID.strandCount) + BRAID.strandCount)
      % BRAID.strandCount;
    const u = (theta + TAU * lane) / BRAID.majorTours;
    return quadrupleHelixPoint(u, Rp);
  }

  function braidDerivative(u, Rp) {
    const major = BRAID.majorRadiusFraction * Rp;
    const helix = BRAID.helixRadiusFraction * Rp;
    const phi = BRAID.majorTours * u;
    const psi = Math.PI + BRAID.poloidalTurns * u;
    const radial = major + helix * Math.cos(psi);
    const radialRate =
      -BRAID.poloidalTurns * helix * Math.sin(psi);
    return [
      radialRate * Math.cos(phi)
        - BRAID.majorTours * radial * Math.sin(phi),
      radialRate * Math.sin(phi)
        + BRAID.majorTours * radial * Math.cos(phi),
      BRAID.poloidalTurns * helix * Math.cos(psi)
    ];
  }

  function braidTangent(u, Rp) {
    return unit(braidDerivative(u, Rp));
  }

  function braidLocalSpeed(u, Rp) {
    return norm(braidDerivative(u, Rp));
  }

  function integerGcd(a, b) {
    let x = Math.abs(Math.trunc(a));
    let y = Math.abs(Math.trunc(b));
    while (y) [x, y] = [y, x % y];
    return x;
  }

  function braidDiagnostics(Rp, samples = 2048) {
    const seamResiduals = [];
    const seamTangentResiduals = [];
    const selfGaps = [];
    const seamLaneTargets = [];
    for (let strand = 0; strand < BRAID.strandCount; strand++) {
      const next = (strand + BRAID.seamLaneAdvance) % BRAID.strandCount;
      const tail = braidStrandPoint(strand, TAU, Rp);
      const nextHead = braidStrandPoint(next, 0, Rp);
      const ownHead = braidStrandPoint(strand, 0, Rp);
      const tailU = (TAU + TAU * strand) / BRAID.majorTours;
      const headU = TAU * next / BRAID.majorTours;
      seamResiduals.push(norm(sub(tail, nextHead)) / Rp);
      seamTangentResiduals.push(
        norm(sub(braidTangent(tailU, Rp), braidTangent(headU, Rp)))
      );
      selfGaps.push(norm(sub(tail, ownHead)) / Rp);
      seamLaneTargets.push(next);
    }

    const stagePoints = [0, 0.25, 0.5, 0.75]
      .map(fraction => quadrupleHelixPoint(TAU * fraction, Rp));
    const fourTourStages = stagePoints.map(point => {
      const radial = Math.hypot(point[0], point[1]);
      if (point[2] < -EPS) return 'under';
      if (point[2] > EPS) return 'over';
      return radial < BRAID.majorRadiusFraction * Rp ? 'inner' : 'outer';
    });

    let minimumSpeed = Infinity;
    let maximumSpeed = 0;
    for (let i = 0; i <= samples; i++) {
      const speed = braidLocalSpeed(TAU * i / samples, Rp);
      minimumSpeed = Math.min(minimumSpeed, speed);
      maximumSpeed = Math.max(maximumSpeed, speed);
    }
    const major = BRAID.majorRadiusFraction * Rp;
    const helix = BRAID.helixRadiusFraction * Rp;
    const strandRadius = BRAID.strandRadiusFraction * Rp;
    const analyticInnerSpeed = Math.hypot(
      BRAID.poloidalTurns * helix,
      BRAID.majorTours * (major - helix)
    );
    const analyticOuterSpeed = Math.hypot(
      BRAID.poloidalTurns * helix,
      BRAID.majorTours * (major + helix)
    );
    const oneLapPhaseAdvance =
      TAU * BRAID.poloidalTurns / BRAID.majorTours;
    const seamPhaseAdvance =
      TAU * BRAID.seamLaneAdvance / BRAID.strandCount;

    return {
      majorTours: BRAID.majorTours,
      poloidalTurns: BRAID.poloidalTurns,
      strandCount: BRAID.strandCount,
      componentCount: integerGcd(
        BRAID.majorTours,
        BRAID.poloidalTurns
      ),
      localTwistsPerLap:
        (oneLapPhaseAdvance - seamPhaseAdvance) / TAU,
      seamLaneAdvance: BRAID.seamLaneAdvance,
      seamLaneTargets,
      oneLapPhaseAdvance,
      seamPhaseAdvance,
      seamResiduals,
      maximumSeamResidual: Math.max(...seamResiduals),
      seamTangentResiduals,
      maximumSeamTangentResidual: Math.max(...seamTangentResiduals),
      oneLapSelfGaps: selfGaps,
      minimumOneLapSelfGap: Math.min(...selfGaps),
      fourTourClosure: norm(sub(
        quadrupleHelixPoint(TAU, Rp),
        quadrupleHelixPoint(0, Rp)
      )) / Rp,
      fourTourStages,
      outerEnvelopeResidual:
        Math.abs(major + helix + strandRadius - Rp) / Rp,
      innerEnvelopeRatio: (major - helix - strandRadius) / Rp,
      minimumLocalSpeed: minimumSpeed,
      maximumLocalSpeed: maximumSpeed,
      sampledSpeedRatio: maximumSpeed / minimumSpeed,
      analyticSpeedRatio: analyticOuterSpeed / analyticInnerSpeed,
      oldFourOneLocalTwistsPerLap:
        ((TAU / BRAID.majorTours) - seamPhaseAdvance) / TAU
    };
  }

  function trefoilPoint(u, Rp) {
    const scale = Rp / 3.2;
    return [
      scale * (2 + Math.cos(3 * u)) * Math.cos(2 * u),
      scale * (2 + Math.cos(3 * u)) * Math.sin(2 * u),
      scale * Math.sin(3 * u)
    ];
  }

  function curvePoint(kind, u, Rp) {
    return kind === 'trefoil'
      ? trefoilPoint(u, Rp)
      : quadrupleHelixPoint(u, Rp);
  }

  function mobiusPose(u, Rp) {
    const radius = 0.28 * Rp;
    const radial = [Math.cos(u), Math.sin(u), 0];
    const vertical = [0, 0, 1];
    return {
      position: mul(radial, radius),
      director: add(
        mul(radial, Math.cos(u / 2)),
        mul(vertical, Math.sin(u / 2))
      )
    };
  }

  function contactSlip(typeA, typeB, normal, Rp) {
    const axis = [0, 0, 1];
    const signA = typeA === 'p' ? 1 : -1;
    const signB = typeB === 'p' ? 1 : -1;
    const n = unit(normal);
    const velocityA = mul(cross(axis, mul(n, Rp)), signA);
    const velocityB = mul(cross(axis, mul(n, -Rp)), signB);
    return norm(sub(velocityA, velocityB)) / Rp;
  }

  function makeBuilder(Rp) {
    const nodes = [];
    const contacts = [];
    const modules = [];
    const push = (position, type, group, module, tier) => {
      const id = nodes.length;
      nodes.push({
        id,
        pos: position,
        type,
        group,
        module,
        tier,
        spin: type === 'p' ? 1 : -1
      });
      return id;
    };
    const bond = (a, b, kind) => {
      contacts.push({ a, b, kind });
    };

    const alpha = center => {
      const radius = Math.SQRT2 * Rp;
      const ids = [
        push(add(center, [radius, 0, 0]), 'p', 'alpha', 0, 0),
        push(add(center, [0, radius, 0]), 'n', 'alpha', 0, 0),
        push(add(center, [-radius, 0, 0]), 'p', 'alpha', 0, 0),
        push(add(center, [0, -radius, 0]), 'n', 'alpha', 0, 0)
      ];
      bond(ids[0], ids[1], 'alpha');
      bond(ids[1], ids[2], 'alpha');
      bond(ids[2], ids[3], 'alpha');
      bond(ids[3], ids[0], 'alpha');
      modules.push({ kind: 'alpha', index: 0, nodes: ids, seat: null });
      return ids;
    };

    const chain = (types, origin, direction, group, module, tier) => {
      const ids = [];
      for (let i = 0; i < types.length; i++) {
        ids.push(push(
          add(origin, mul(direction, 2 * Rp * i)),
          types[i],
          group,
          module,
          tier
        ));
        if (i > 0) bond(ids[i - 1], ids[i], 'internal');
      }
      return ids;
    };

    return { nodes, contacts, modules, push, bond, alpha, chain };
  }

  function placeModule(builder, kind, direction, moduleIndex, Rp) {
    const contact = 2 * Rp;
    const candidates = [];
    const axisSamples = [unit(direction), mul(unit(direction), -1)];
    for (let latitude = 0; latitude <= 12; latitude++) {
      const polar = Math.PI * latitude / 12;
      const ringCount = latitude === 0 || latitude === 12 ? 1 : 24;
      for (let longitude = 0; longitude < ringCount; longitude++) {
        const azimuth = TAU * longitude / ringCount;
        axisSamples.push([
          Math.sin(polar) * Math.cos(azimuth),
          Math.sin(polar) * Math.sin(azimuth),
          Math.cos(polar)
        ]);
      }
    }

    for (const anchor of builder.nodes) {
      let types;
      if (kind === 'triton') {
        if (anchor.type !== 'p') continue;
        types = ['n', 'p', 'n'];
      } else {
        types = anchor.type === 'p' ? ['n', 'p'] : ['p', 'n'];
      }

      const offsets = kind === 'triton'
        ? [-contact, 0, contact]
        : [-Rp, Rp];
      const dockingOffset = -offsets[0];

      for (const axis of axisSamples) {
        const target = add(anchor.pos, mul(axis, dockingOffset));
        const projection = dot(target, direction);
        const discriminant = projection * projection
          + contact * contact
          - dot(target, target);
        if (discriminant < -contact * EPS) continue;
        const root = Math.sqrt(Math.max(0, discriminant));

        for (const centreScalar of [projection + root, projection - root]) {
          if (!(centreScalar > 0)) continue;
          const centre = mul(direction, centreScalar);
          const positions = offsets.map(offset =>
            add(centre, mul(axis, offset)));
          let valid = true;
          let clearance = Infinity;

          for (let i = 0; i < positions.length && valid; i++) {
            for (const node of builder.nodes) {
              if (i === 0 && node.id === anchor.id) continue;
              const gap = norm(sub(positions[i], node.pos)) - contact;
              if (gap <= contact * 1e-10) {
                valid = false;
                break;
              }
              clearance = Math.min(clearance, gap);
            }
            for (let j = 0; j < i && valid; j++) {
              if (i === j + 1) continue;
              const gap = norm(sub(positions[i], positions[j])) - contact;
              if (gap <= contact * 1e-10) {
                valid = false;
                break;
              }
              clearance = Math.min(clearance, gap);
            }
          }

          if (valid) {
            candidates.push({
              anchor: anchor.id,
              types,
              positions,
              axis,
              clearance,
              centreScalar,
              alphaAnchor: anchor.group === 'alpha'
            });
          }
        }
      }
    }

    candidates.sort((a, b) =>
      (Number(b.alphaAnchor) - Number(a.alphaAnchor))
      || (b.clearance - a.clearance)
      || (a.centreScalar - b.centreScalar)
      || (a.anchor - b.anchor));
    const selected = candidates[0];
    if (!selected) {
      throw new Error(`no contact-safe ${kind} placement at construction seat ${moduleIndex + 1}`);
    }

    const ids = selected.types.map((type, i) =>
      builder.push(selected.positions[i], type, kind, moduleIndex, 1));
    builder.bond(selected.anchor, ids[0], 'dock');
    for (let i = 1; i < ids.length; i++) {
      builder.bond(ids[i - 1], ids[i], 'internal');
    }
    return {
      ids,
      anchor: selected.anchor,
      clearance: selected.clearance,
      centreScalar: selected.centreScalar,
      internalAxis: selected.axis,
      orientation: selected.types.join('-'),
      admissibleOrientationCount: candidates.length,
      selectedOrientationIndex: 0
    };
  }

  function placeInterstitialModule(builder, kind, direction, moduleIndex, Rp) {
    try {
      return {
        ...placeModule(builder, kind, direction, moduleIndex, Rp),
        seatDirection: direction,
        orientationTrial: 0,
        interstitialFallback: false
      };
    } catch (primaryError) {
      const contact = 2 * Rp;
      const base = unit(direction);
      const tangentSeed = Math.abs(base[2]) < 0.9 ? [0, 0, 1] : [1, 0, 0];
      const tangentA = unit(cross(tangentSeed, base));
      const tangentB = unit(cross(base, tangentA));
      const directions = [base];
      for (const cone of [0.08, 0.16, 0.24, 0.32]) {
        for (let phase = 0; phase < 24; phase++) {
          const angle = TAU * phase / 24;
          directions.push(unit(add(
            mul(base, Math.cos(cone)),
            mul(add(
              mul(tangentA, Math.cos(angle)),
              mul(tangentB, Math.sin(angle))
            ), Math.sin(cone))
          )));
        }
      }
      const anchors = builder.nodes
        .filter(node => kind !== 'triton' || node.type === 'p')
        .sort((a, b) =>
          (dot(b.pos, base) - dot(a.pos, base)) || (a.id - b.id));
      let trial = 0;
      for (const axis of directions) {
        for (const anchor of anchors) {
          trial++;
          const types = kind === 'triton'
            ? ['n', 'p', 'n']
            : (anchor.type === 'p' ? ['n', 'p'] : ['p', 'n']);
          if (types[0] === anchor.type) continue;
          const positions = types.map((_, index) =>
            add(anchor.pos, mul(axis, contact * (index + 1))));
          let valid = true;
          for (let i = 0; i < positions.length && valid; i++) {
            for (const node of builder.nodes) {
              if (i === 0 && node.id === anchor.id) continue;
              if (norm(sub(positions[i], node.pos)) <= contact * (1 + 1e-10)) {
                valid = false;
                break;
              }
            }
            for (let j = 0; j < i && valid; j++) {
              if (i === j + 1) continue;
              if (norm(sub(positions[i], positions[j])) <= contact * (1 + 1e-10)) {
                valid = false;
              }
            }
          }
          if (!valid) continue;
          const ids = types.map((type, i) =>
            builder.push(positions[i], type, kind, moduleIndex, 1));
          builder.bond(anchor.id, ids[0], 'interstitial-dock');
          for (let i = 1; i < ids.length; i++) {
            builder.bond(ids[i - 1], ids[i], 'internal');
          }
          return {
            ids,
            anchor: anchor.id,
            clearance: 0,
            centreScalar: dot(
              mul(positions.reduce((sum, point) => add(sum, point), [0, 0, 0]), 1 / positions.length),
              base
            ),
            internalAxis: axis,
            orientation: types.join('-'),
            admissibleOrientationCount: trial,
            selectedOrientationIndex: trial - 1,
            seatDirection: axis,
            orientationTrial: trial - 1,
            interstitialFallback: true
          };
        }
      }
      throw primaryError;
    }
  }

  function build(keyOrPreset, options) {
    const supplied = typeof keyOrPreset === 'object' && keyOrPreset
      ? keyOrPreset
      : null;
    const key = supplied?.key || keyOrPreset;
    const preset = supplied || PRESETS[key];
    if (!preset) throw new RangeError(`unknown NSEQ16 preset: ${key}`);
    const Rp = options?.Rp
      || global.SDT_NUCLEAR_PACKING?.R_p
      || global.SDT_R_p;
    if (!(Rp > 0)) throw new Error('NSEQ16 requires canonical R_p');
    const g = grammar(preset.A, preset.Z);
    if (!g.valid) throw new RangeError(`invalid grammar for ${preset.name}`);
    const builder = makeBuilder(Rp);

    if (key === 'N1') {
      const id = builder.push([0, 0, 0], 'n', 'neutron', 0, 0);
      builder.modules.push({
        kind: 'neutron',
        index: 0,
        nodes: [id],
        seat: null,
        nucleonPose: {
          type: 'n',
          centre: [0, 0, 0],
          orientation: [0, 0, 0, 1],
          scale: 1,
          phase: 0,
          handedness: -1,
          envelopeRadius: Rp,
          internalElectron: true
        }
      });
    } else if (key === 'H1') {
      const id = builder.push([0, 0, 0], 'p', 'hydrogen', 0, 0);
      builder.modules.push({
        kind: 'proton',
        index: 0,
        nodes: [id],
        seat: null,
        nucleonPose: {
          type: 'p',
          centre: [0, 0, 0],
          orientation: [0, 0, 0, 1],
          scale: 1,
          phase: 0,
          handedness: 1,
          envelopeRadius: Rp
        }
      });
    } else if (key === 'H2') {
      const ids = builder.chain(['p', 'n'], [-Rp, 0, 0], [1, 0, 0], 'deuteron', 0, 0);
      const closure = deuteronClosureProperties();
      const calibration = fitLightNucleus(key, Rp);
      builder.modules.push({
        kind: 'deuteron',
        index: 0,
        nodes: ids,
        seat: null,
        nucleonPoses: calibration.poses,
        contactRule: 'phase-locked p-n wake mesh',
        closure,
        calibration
      });
    } else if (key === 'H3') {
      const ids = builder.chain(['n', 'p', 'n'], [-2 * Rp, 0, 0], [1, 0, 0], 'triton', 0, 0);
      const closure = threeNucleonClosureProperties(key);
      const calibration = fitLightNucleus(key, Rp);
      builder.modules.push({
        kind: 'triton',
        index: 0,
        nodes: ids,
        seat: null,
        nucleonPoses: calibration.poses,
        contactRule: 'two crossed p-n rims; no n-n contact',
        closure,
        calibration
      });
    } else if (key === 'He3') {
      const ids = builder.chain(['p', 'n', 'p'], [-2 * Rp, 0, 0], [1, 0, 0], 'helion', 0, 0);
      const closure = threeNucleonClosureProperties(key);
      const calibration = fitLightNucleus(key, Rp);
      builder.modules.push({
        kind: 'helion',
        index: 0,
        nodes: ids,
        seat: null,
        nucleonPoses: calibration.poses,
        contactRule: 'two crossed p-n rims; outer p rims remain separate',
        closure,
        calibration
      });
    } else if (g.nd + g.nt === 0) {
      builder.alpha([0, 0, 0]);
      const seats = atomicusSeats(g.nd + g.nt);
      const moduleKinds = seats.map((_, index) =>
        index < g.nt ? 'triton' : 'deuteron');

      moduleKinds.forEach((kind, index) => {
        const placement = placeModule(
          builder,
          kind,
          seats[index].dir,
          index,
          Rp
        );
        builder.modules.push({
          kind,
          index,
          constructionIndex: seats[index].constructionIndex,
          nodes: placement.ids,
          seat: seats[index].dir,
          region: seats[index].region,
          anchor: placement.anchor,
          clearance: placement.clearance,
          centreScalar: placement.centreScalar,
          internalAxis: placement.internalAxis,
          orientation: placement.orientation
        });
      });
    } else {
      builder.alpha([0, 0, 0]);
      const allocation = universalShellAllocation(g.nd, g.nt);
      let moduleIndex = 0;
      let previousShellModules = [];
      for (const shell of allocation.shells) {
        const kind = shell.species === 't' ? 'triton' : 'deuteron';
        const parentLists = parentInterstitials(
          shell.directions,
          previousShellModules.length
            ? previousShellModules
            : builder.modules
        );
        const currentShellModules = [];
        for (let seatIndex = 0; seatIndex < shell.directions.length; seatIndex++) {
          const direction = shell.directions[seatIndex];
          const placement = placeInterstitialModule(
            builder,
            kind,
            direction,
            moduleIndex,
            Rp
          );
          const module = {
            kind,
            index: moduleIndex,
            constructionIndex: moduleIndex + 1,
            nodes: placement.ids,
            seat: placement.seatDirection || direction,
            registeredSeat: direction,
            region: Math.abs(direction[2]) < EPS
              ? 'equatorial'
              : (Math.abs(direction[2]) > 1 - EPS ? 'polar' : 'tropical'),
            anchor: placement.anchor,
            clearance: placement.clearance,
            centreScalar: placement.centreScalar,
            internalAxis: placement.internalAxis,
            orientation: placement.orientation,
            admissibleOrientationCount: placement.admissibleOrientationCount,
            selectedOrientationIndex: placement.selectedOrientationIndex,
            orientationTrial: placement.orientationTrial,
            interstitialFallback: placement.interstitialFallback,
            shellIndex: shell.scheduleIndex,
            shellLabel: shell.label,
            shellGeometry: shell.geometry,
            shellCapacity: shell.capacity,
            shellOccupancy: shell.occupancy,
            shellFull: shell.full,
            parentInterstitials: parentLists[seatIndex],
            tritonClosure: shell.species === 't' && shell.full
          };
          builder.modules.push(module);
          currentShellModules.push(module);
          moduleIndex++;
        }
        previousShellModules = currentShellModules;
      }
      builder.universalAllocation = allocation;
    }

    const satelliteCount = Math.max(0, builder.modules.length - 1);
    const satelliteModules = builder.modules.filter(module => module.seat);
    const seatLedger = builder.universalAllocation
      ? satelliteModules.map(module => ({
        constructionIndex: module.constructionIndex,
        pairsWithSeat: null,
        dir: module.seat,
        region: module.region,
        shellIndex: module.shellIndex,
        shellLabel: module.shellLabel,
        shellGeometry: module.shellGeometry,
        parentInterstitials: module.parentInterstitials
      }))
      : atomicusSeats(satelliteCount);
    const routeRows = satelliteModules.map(module => {
      const centre = mul(
        module.nodes.reduce(
          (sum, id) => add(sum, builder.nodes[id].pos),
          [0, 0, 0]
        ),
        1 / module.nodes.length
      );
      const proton = builder.nodes[
        module.nodes.find(id => builder.nodes[id].type === 'p')
      ];
      const target = unit(module.seat);
      const moduleDirection = unit(centre);
      const protonDirection = unit(proton.pos);
      return {
        kind: module.kind,
        constructionIndex: module.constructionIndex,
        pairsWithSeat:
          seatLedger[module.constructionIndex - 1]?.pairsWithSeat || null,
        targetDirection: target,
        moduleDirection,
        protonDirection,
        moduleResidual: norm(sub(moduleDirection, target)),
        protonResidual: norm(sub(protonDirection, target))
      };
    });
    const maximumModuleRouteResidual = Math.max(
      0,
      ...routeRows.map(row => row.moduleResidual)
    );
    const maximumProtonRouteResidual = Math.max(
      0,
      ...routeRows.map(row => row.protonResidual)
    );
    const canonicalH1 = key === 'H1';
    const canonicalNeutron = key === 'N1';
    const canonicalDeuteron = key === 'H2';
    const canonicalTriton = key === 'H3';
    const canonicalHelion = key === 'He3';
    const canonicalComposite =
      canonicalDeuteron || canonicalTriton || canonicalHelion;
    const canonicalSeed =
      canonicalH1 || canonicalNeutron || canonicalComposite;
    const model = {
      version: VERSION,
      key,
      preset,
      grammar: g,
      Rp,
      poleAxis: [0, 0, 1],
      seatModel: builder.universalAllocation
        ? 'interstitial-species-pure-spherical-closure'
        : 'valence-position-spherical-code',
      seatDirections: seatLedger.map(seat => seat.dir),
      seatLedger,
      shellLedger: builder.universalAllocation?.shells || [],
      fullTritonClosures:
        builder.universalAllocation?.fullTritonClosures || 0,
      contractionScale:
        builder.universalAllocation?.contractionScale || 1,
      nodes: builder.nodes,
      contacts: builder.contacts,
      modules: builder.modules,
      routes: {
        protonByZ: routeRows.map(row => ({
          constructionIndex: row.constructionIndex,
          pairsWithSeat: row.pairsWithSeat,
          targetDirection: row.targetDirection,
          actualDirection: row.protonDirection,
          residual: row.protonResidual
        })),
        constitutional: routeRows.map(row => ({
          kind: row.kind,
          constructionIndex: row.constructionIndex,
          pairsWithSeat: row.pairsWithSeat,
          targetDirection: row.targetDirection,
          actualDirection: row.moduleDirection,
          residual: row.moduleResidual
          }))
      },
      routeComparison: {
        maximumProtonResidual: maximumProtonRouteResidual,
        maximumConstitutionalResidual: maximumModuleRouteResidual,
        geometricMatch:
          maximumModuleRouteResidual <= 1e-10
            ? 'constitutional-module-centres'
            : 'neither-route'
      },
      constructionTransition: ({
        N1: 'free neutron · p + seated e',
        H1: 'H position · p',
        H2: 'D position · p-n',
        H3: 'T position · n-p-n',
        He3: 'He-3 position · p-n-p',
        He4: 'He position · alpha',
        Li7: 'Li position · alpha+t',
        Be9: 'Be position · alpha+d+t',
        B11: 'B position · alpha+2d+t',
        C12: 'C position · alpha+4d',
        N14: 'N position · alpha+5d',
        O16: 'O position · alpha+6d'
      }[key] || `${preset.symbol}-${preset.A} · interstitial closure schedule`),
      topology: canonicalSeed
        ? {
          canonical: canonicalComposite
            ? `${builder.modules[0].nucleonPoses.length}-unit conserved wake mesh`
            : 'loaded (4,3) cyclic quadruple helix',
          centreline: 'theta=4u, phi=3u',
          majorTours: H1_NUCLEON.majorTours,
          crossSectionTurns: H1_NUCLEON.crossSectionTurns,
          localHelixTurnsPerTour:
            H1_NUCLEON.localHelixTurnsPerTour,
          seamRetreatTurnsPerTour:
            H1_NUCLEON.seamRetreatTurnsPerTour,
          strandCount: H1_NUCLEON.apparentStrands,
          internalRollRadians: H1_NUCLEON.internalRollTurns * TAU,
          seamLaneAdvance: 1,
          equivalentToOrdinaryTrefoil: false,
          internalElectron: canonicalNeutron || canonicalComposite,
          crossedComposite: canonicalComposite
        }
        : {
          canonical: '(2,3) trefoil',
          pulledCandidate: '(4,5) cyclic quadruple-helix ring',
          majorTours: BRAID.majorTours,
          poloidalTurns: BRAID.poloidalTurns,
          strandCount: BRAID.strandCount,
          localTwistsPerLap: BRAID.localTwistsPerLap,
          seamLaneAdvance: BRAID.seamLaneAdvance,
          equivalent: false
        },
      braid: canonicalSeed
        ? h1Diagnostics(Rp)
        : braidDiagnostics(Rp, 512),
      canonicalNucleon: canonicalSeed
        ? {
          kind: canonicalNeutron
            ? 'free-neutron'
            : (canonicalDeuteron
              ? 'deuteron-pair'
              : (canonicalTriton
                ? 'triton-three-unit'
                : (canonicalHelion
                  ? 'helion-three-unit'
                  : 'free-proton'))),
          spec: H1_NUCLEON,
          diagnostics: h1Diagnostics(Rp),
          units: canonicalComposite
            ? builder.modules[0].nucleonPoses
            : [builder.modules[0].nucleonPose],
          properties: canonicalNeutron
            ? {
              state: 'free',
              chargeE: 0,
              massKg: SEED_MEASURED.neutronMassKg,
              magneticMomentMuN: SEED_MEASURED.neutronMomentMuN,
              internalElectron: true
            }
            : (canonicalComposite
              ? builder.modules[0].closure
              : {
                state: 'free H+',
                chargeE: 1,
                massKg: SEED_MEASURED.protonMassKg,
                magneticMomentMuN: SEED_MEASURED.protonMomentMuN
              }),
          calibration: canonicalComposite
            ? builder.modules[0].calibration
            : (canonicalNeutron ? neutronMagneticCalibration(12) : null),
          magnetic: canonicalH1
            ? h1MagneticMetrics(Rp * 1e-15)
            : (canonicalNeutron
              ? neutronMagneticCalibration(12)
              : {
              measuredMomentMuN: canonicalNeutron
                ? SEED_MEASURED.neutronMomentMuN
                : (canonicalDeuteron
                  ? SEED_MEASURED.deuteronMomentMuN
                  : (canonicalTriton
                    ? SEED_MEASURED.tritonMomentMuN
                    : SEED_MEASURED.helionMomentMuN)),
              mappingStatus:
                'PENDING — signed wake-to-effective-current bridge'
              }),
          wake: canonicalComposite
            ? null
            : {
              spec: H1_WAKE,
              sense: canonicalNeutron
                ? 'proton-form + seated-electron counter-circulation'
                : 1,
              diagnostics: h1WakeDiagnostics(0)
            }
        }
        : null,
      massDefectStatus: canonicalComposite
        ? builder.modules[0].calibration.classification
          + ' — wake cross-term binding'
        : 'PENDING — geometric interleave ledger only',
      geometryStatus: canonicalSeed
        ? (canonicalNeutron
          ? 'CANONICAL_FREE_NEUTRON'
          : (canonicalDeuteron
            ? 'CANONICAL_CROSSED_DEUTERON'
            : (canonicalTriton
              ? 'CANONICAL_CROSSED_TRITON'
              : (canonicalHelion
                ? 'CANONICAL_CROSSED_HELION'
                : 'CANONICAL_HYDROGEN_ONE_NUCLEON'))))
        : 'ATOMICUS_CONTACT_CONSTRUCTION_CANDIDATE'
    };
    model.metrics = evaluate(model);
    model.observableLedger = canonicalSeed || options?.skipObservableLedger
      ? null
      : universalObservableLedger(model);
    model.fingerprint = fingerprint(model);
    return model;
  }

  function evaluate(model) {
    const nodes = model.nodes;
    const contacts = model.contacts;
    let maxContactResidual = 0;
    let maxSlip = 0;
    let unlike = true;
    const touched = new Set();
    const adjacency = nodes.map(() => []);
    const edgeKeys = new Set();
    for (const edge of contacts) {
      const a = nodes[edge.a];
      const b = nodes[edge.b];
      const delta = sub(b.pos, a.pos);
      const distance = norm(delta);
      maxContactResidual = Math.max(
        maxContactResidual,
        Math.abs(distance / (2 * model.Rp) - 1)
      );
      maxSlip = Math.max(
        maxSlip,
        contactSlip(a.type, b.type, delta, model.Rp)
      );
      unlike = unlike && a.type !== b.type;
      edgeKeys.add(`${Math.min(edge.a, edge.b)}:${Math.max(edge.a, edge.b)}`);
      touched.add(edge.a);
      touched.add(edge.b);
      adjacency[edge.a].push(edge.b);
      adjacency[edge.b].push(edge.a);
    }
    const seen = new Set();
    if (nodes.length) {
      const queue = [0];
      seen.add(0);
      while (queue.length) {
        const id = queue.shift();
        for (const next of adjacency[id]) {
          if (!seen.has(next)) {
            seen.add(next);
            queue.push(next);
          }
        }
      }
    }
    let likeLikeTouches = 0;
    let unlistedTouches = 0;
    let minimumUnlistedClearance = Infinity;
    for (let i = 0; i < nodes.length; i++) {
      for (let j = i + 1; j < nodes.length; j++) {
        const distance = norm(sub(nodes[j].pos, nodes[i].pos));
        const key = `${i}:${j}`;
        if (!edgeKeys.has(key)) {
          minimumUnlistedClearance = Math.min(
            minimumUnlistedClearance,
            distance - 2 * model.Rp
          );
          if (distance <= 2 * model.Rp * (1 + 1e-10)) {
            unlistedTouches++;
            if (nodes[i].type === nodes[j].type) likeLikeTouches++;
          }
        }
      }
    }
    const seatNormResidual = Math.max(
      0,
      ...model.seatDirections.map(direction => Math.abs(norm(direction) - 1))
    );
    const alpha = model.modules.find(module => module.kind === 'alpha');
    let alphaLikeDiagonalRatio = Infinity;
    let alphaEquatorialResidual = 0;
    if (alpha) {
      const alphaNodes = alpha.nodes.map(id => nodes[id]);
      alphaEquatorialResidual = Math.max(
        ...alphaNodes.map(node => Math.abs(node.pos[2]) / model.Rp)
      );
      for (let i = 0; i < alphaNodes.length; i++) {
        for (let j = i + 1; j < alphaNodes.length; j++) {
          if (alphaNodes[i].type !== alphaNodes[j].type) continue;
          alphaLikeDiagonalRatio = Math.min(
            alphaLikeDiagonalRatio,
            norm(sub(alphaNodes[j].pos, alphaNodes[i].pos)) / (2 * model.Rp)
          );
        }
      }
    }
    const protonCount = nodes.filter(node => node.type === 'p').length;
    const commonClockResidual = Math.max(
      0,
      ...nodes.map(node => Math.hypot(
        Math.cos(TAU * node.spin) - 1,
        Math.sin(TAU * node.spin)
      ))
    );
    const connected = seen.size === nodes.length;
    const allTouched = nodes.length === 1 || touched.size === nodes.length;
    const tractionConsistent =
      connected
      && allTouched
      && unlike
      && unlistedTouches === 0
      && likeLikeTouches === 0
      && maxContactResidual <= 1e-10
      && maxSlip < 1e-10;
    return {
      nucleonCount: nodes.length,
      protonCount,
      contactCount: contacts.length,
      connected,
      allTouched,
      unlikeContacts: unlike,
      likeLikeTouches,
      unlistedTouches,
      minimumUnlistedClearance,
      maxContactResidual,
      maxSlip,
      tractionConsistent,
      commonClockResidual,
      commonBoundaryPeriodTurns: 1,
      seatNormResidual,
      maxModuleSeatResidual:
        model.routeComparison.maximumConstitutionalResidual,
      maxProtonSeatResidual:
        model.routeComparison.maximumProtonResidual,
      alphaEquatorialResidual,
      alphaLikeDiagonalRatio,
      hasPolarAxis: norm(model.poleAxis) > 0
    };
  }

  function evaluateNseq05(nucleus, Rp) {
    let maxSlip = 0;
    let maxContactResidual = 0;
    let unlike = true;
    const edgeKeys = new Set();
    for (const edge of nucleus.contacts || []) {
      const a = nucleus[edge[0]];
      const b = nucleus[edge[1]];
      const distance = norm(sub(b.pos, a.pos));
      unlike = unlike && a.type !== b.type;
      maxContactResidual = Math.max(
        maxContactResidual,
        Math.abs(distance / (2 * Rp) - 1)
      );
      maxSlip = Math.max(
        maxSlip,
        contactSlip(a.type, b.type, sub(b.pos, a.pos), Rp)
      );
      edgeKeys.add(`${Math.min(edge[0], edge[1])}:${Math.max(edge[0], edge[1])}`);
    }
    let unlistedTouches = 0;
    for (let i = 0; i < nucleus.length; i++) {
      for (let j = i + 1; j < nucleus.length; j++) {
        if (edgeKeys.has(`${i}:${j}`)) continue;
        if (
          norm(sub(nucleus[j].pos, nucleus[i].pos))
          <= 2 * Rp * (1 + 1e-10)
        ) {
          unlistedTouches++;
        }
      }
    }
    const hasPolarAxis = false;
    const hasConstructionOrder = false;
    const realContact =
      maxContactResidual <= 1e-10
      && unlistedTouches === 0;
    return {
      contactCount: (nucleus.contacts || []).length,
      unlikeContacts: unlike,
      maxContactResidual,
      unlistedTouches,
      maxSlip,
      hasPolarAxis,
      hasConstructionOrder,
      tractionConsistent:
        unlike
        && realContact
        && maxSlip < 1e-10
        && hasPolarAxis
        && hasConstructionOrder,
      classification: 'LEGACY_GEOMETRIC_CONTROL'
    };
  }

  function universalObservableLedger(model) {
    const degree = model.nodes.map(() => 0);
    for (const edge of model.contacts) {
      degree[edge.a]++;
      degree[edge.b]++;
    }
    const poses = model.nodes.map((node, index) => ({
      type: node.type,
      unitIndex: index,
      centreRp: mul(node.pos, model.contractionScale / model.Rp),
      orientation: [0, 0, 0, 1],
      scale: model.contractionScale,
      handedness: node.type === 'p' ? 1 : -1,
      toroidalPhase: TAU * index / Math.max(1, model.nodes.length),
      wakeCompliance: Math.min(0.45, 0.05 * degree[index]),
      splitShift: Math.max(-0.12, Math.min(0.12, 0.018 * (degree[index] - 2)))
    }));
    const magneticSegments = [];
    const familySegments = {};
    for (const pose of poses) {
      for (const segment of speciesMagneticSegments(pose, 4)) {
        magneticSegments.push(segment);
        (familySegments[segment.family] ||= []).push(segment);
      }
    }
    const integralVector = segmentMoment(magneticSegments);
    const farField = farFieldDipoleFit(magneticSegments);
    const familyMomentsMuN = {};
    for (const [family, segments] of Object.entries(familySegments)) {
      familyMomentsMuN[family] = segmentMoment(segments)[2];
    }
    let wakeCoupling = 0;
    const contactWakeLedger = [];
    for (const edge of model.contacts) {
      const metrics = wakeMeshPairMetrics(poses[edge.a], poses[edge.b], 4);
      wakeCoupling += metrics.contactCoupling;
      contactWakeLedger.push({
        a: edge.a,
        b: edge.b,
        kind: edge.kind,
        coupling: metrics.coupling,
        contactCoupling: metrics.contactCoupling,
        signedAlignment: metrics.signedAlignment,
        minimumDistanceRp: metrics.minimumDistance
      });
    }
    const alphaHbarCMeVFm =
      SEED_MEASURED.fineStructureConstant
      * SEED_MEASURED.hbarJouleSeconds
      * SEED_MEASURED.speedOfLightMetresPerSecond
      / (1e6 * SEED_MEASURED.electronVoltJoules)
      * 1e15;
    const interactionScaleMeV =
      alphaHbarCMeVFm / SEED_MEASURED.protonRadiusFm;
    const calculatedBindingMeV =
      wakeCoupling * interactionScaleMeV * model.contractionScale;
    const observableKey = `${model.preset.symbol}${model.preset.A}`;
    const measured = SEED_MEASURED.observables[observableKey] || null;
    const measuredBindingMeV =
      Number.isFinite(model.preset.bindingEnergyMeV)
        ? model.preset.bindingEnergyMeV
        : null;
    const measuredMomentMuN = measured?.magneticMomentMuN ?? null;
    const calculatedMomentMuN = integralVector[2];
    const magneticResidualMuN = measuredMomentMuN == null
      ? null
      : calculatedMomentMuN - measuredMomentMuN;
    const bindingResidualMeV = measuredBindingMeV == null
      ? null
      : calculatedBindingMeV - measuredBindingMeV;
    const diagnostics = h1WakeDiagnostics(0);
    return {
      mapping:
        'frozen proton bridge + frozen neutron counter-circulation; no isotope coefficient',
      poses,
      orientationTrials: model.modules
        .filter(module => module.seat)
        .map(module => ({
          module: module.index,
          shell: module.shellLabel || 'valence',
          selectedOrientationIndex: module.selectedOrientationIndex || 0,
          admissibleOrientationCount: module.admissibleOrientationCount || 1,
          interstitialFallback: Boolean(module.interstitialFallback)
        })),
      wake: {
        closedCircuitCount: poses.length * H1_WAKE.circuitCount,
        splitResidual: diagnostics.splitResidual,
        rejoinResidual: diagnostics.rejoinResidual,
        pairedFluxResidual: diagnostics.pairedFluxResidual,
        maximumRelativeDivergence: diagnostics.maximumRelativeDivergence,
        contactCoupling: wakeCoupling,
        contactLedger: contactWakeLedger
      },
      magnetic: {
        integralVectorMuN: integralVector,
        integralMuN: calculatedMomentMuN,
        farFieldMuN: farField.mean,
        routeRelativeResidual: farField.routeRelativeResidual,
        familyMomentsMuN,
        measuredMuN: measuredMomentMuN,
        residualMuN: magneticResidualMuN,
        relativeResidual: measuredMomentMuN == null
          ? null
          : magneticResidualMuN / Math.max(Math.abs(measuredMomentMuN), EPS)
      },
      massDefect: {
        interactionScaleMeV,
        calculatedBindingMeV,
        measuredBindingMeV,
        residualMeV: bindingResidualMeV,
        relativeResidual: measuredBindingMeV == null
          ? null
          : bindingResidualMeV / Math.max(Math.abs(measuredBindingMeV), EPS)
      },
      quadrupole: {
        measuredFm2: measured?.quadrupoleFm2 ?? null
      },
      provenance: measured?.source || 'no magnetic observable in generated inputs'
    };
  }

  function fingerprint(model) {
    const text = JSON.stringify({
      key: model.key,
      nodes: model.nodes,
      contacts: model.contacts,
      modules: model.modules,
      topology: model.topology,
      braid: model.braid,
      canonicalNucleon: model.canonicalNucleon
    });
    let hash = 2166136261;
    for (let i = 0; i < text.length; i++) {
      hash ^= text.charCodeAt(i);
      hash = Math.imul(hash, 16777619);
    }
    return (hash >>> 0).toString(16).padStart(8, '0');
  }

  function selfTest(options) {
    const Rp = options?.Rp
      || global.SDT_NUCLEAR_PACKING?.R_p
      || global.SDT_R_p;
    if (!(Rp > 0)) throw new Error('NSEQ16 self-test requires canonical R_p');
    const expectedAngles = {
      2: Math.PI,
      3: 2 * Math.PI / 3,
      4: Math.acos(-1 / 3),
      5: Math.PI / 2,
      6: Math.PI / 2
    };
    const seatErrors = {};
    for (const count of [2, 3, 4, 5, 6]) {
      seatErrors[count] = Math.abs(
        minimumSeatAngle(seatDirections(count)) - expectedAngles[count]
      );
    }
    const seats1 = atomicusSeats(1);
    const seats2 = atomicusSeats(2);
    const seats3 = atomicusSeats(3);
    const seats4 = atomicusSeats(4);
    const seats6 = atomicusSeats(6);
    const valenceSeats = {
      firstEquatorial: Math.abs(seats1[0].dir[2]),
      oppositionResidual: Math.abs(dot(seats2[0].dir, seats2[1].dir) + 1),
      triangleEquatorial: Math.max(...seats3.map(seat => Math.abs(seat.dir[2]))),
      tropicalLatitudeResidual: Math.max(
        ...seats4.map(seat => Math.abs(Math.abs(seat.dir[2]) - 1 / Math.sqrt(3)))
      ),
      tropicalSigns:
        new Set(seats4.map(seat => Math.sign(seat.dir[2]))).size,
      thirdSixthOpposition:
        Math.abs(dot(seats6[2].dir, seats6[5].dir) + 1),
      sixthPairingMarker:
        Math.abs(seats6[5].pairsWithSeat - 3)
    };
    const braid = braidDiagnostics(Rp);
    const hydrogen = h1Diagnostics(Rp);
    const m0 = mobiusPose(0, Rp);
    const m2 = mobiusPose(TAU, Rp);
    const m4 = mobiusPose(2 * TAU, Rp);
    return {
      seatErrors,
      valenceSeats,
      braid,
      hydrogen,
      fourTourClosure: braid.fourTourClosure,
      fourTourStages: braid.fourTourStages,
      mobiusPosition2Pi: norm(sub(m2.position, m0.position)) / Rp,
      mobiusDirector2Pi: dot(m2.director, m0.director),
      mobiusPosition4Pi: norm(sub(m4.position, m0.position)) / Rp,
      mobiusDirector4Pi: dot(m4.director, m0.director),
      unlikeSlipControl: contactSlip('p', 'n', [1, 0, 0], Rp),
      likeSlipControl: contactSlip('p', 'p', [1, 0, 0], Rp)
    };
  }

  function buildNuclide(Z, A, options = {}) {
    const seedKey = {
      '0:1': 'N1',
      '1:1': 'H1',
      '1:2': 'H2',
      '1:3': 'H3',
      '2:3': 'He3',
      '2:4': 'He4'
    }[`${Z}:${A}`];
    if (seedKey) {
      const model = build(seedKey, options);
      if (
        model.observableLedger
        && Number.isFinite(options.bindingEnergyMeV)
      ) {
        model.preset = {
          ...model.preset,
          bindingEnergyMeV: options.bindingEnergyMeV
        };
        model.observableLedger.massDefect.measuredBindingMeV =
          options.bindingEnergyMeV;
        model.observableLedger.massDefect.residualMeV =
          model.observableLedger.massDefect.calculatedBindingMeV
          - options.bindingEnergyMeV;
        model.observableLedger.massDefect.relativeResidual =
          model.observableLedger.massDefect.residualMeV
          / Math.max(Math.abs(options.bindingEnergyMeV), EPS);
      }
      return model;
    }
    const symbol = options.symbol || `Z${Z}`;
    return build({
      key: `${symbol}${A}`,
      symbol,
      name: options.name || `${symbol}-${A}`,
      Z,
      A,
      bindingEnergyMeV: options.bindingEnergyMeV
    }, options);
  }

  global.SDT_TRACTION_GEAR = Object.freeze({
    version: VERSION,
    presets: PRESETS,
    grammar,
    seatDirections,
    atomicusSeats,
    polarShellDirections,
    cuboctahedralThreeSixThree,
    triangularLinkDirections,
    faceNormalFourteenDirections,
    completeShellDirections,
    partialShellDirections,
    universalShellAllocation,
    minimumSeatAngle,
    curvePoint,
    seedMeasured: SEED_MEASURED,
    deuteronClosureProperties,
    threeNucleonClosureProperties,
    h1Spec: H1_NUCLEON,
    h1Point,
    h1Derivative,
    h1Tangent,
    h1LocalSpeed,
    h1LanePoint,
    h1ArcTable,
    h1ParameterAtArc,
    h1FrameTable,
    h1MagneticMetrics,
    h1Diagnostics,
    h1WakeSpec: H1_WAKE,
    h1WakeCircuit,
    h1WakeSegments,
    h1WakeVectorPotential,
    h1WakeField,
    h1WakeDivergence,
    h1WakeDiagnostics,
    wakeMeshBounds: WAKE_MESH_BOUNDS,
    operatingWakeSegments,
    transformWakeSegments,
    segmentMoment,
    neutronMagneticCalibration,
    speciesMagneticSegments,
    wakeMeshPairMetrics,
    compositeWakeMesh,
    farFieldDipoleFit,
    electricQuadrupoleFm2,
    lightNucleusTargets,
    lightNucleusPoses,
    fitLightNucleus,
    braidSpec: BRAID,
    braidDiagnostics,
    braidStrandPoint,
    braidDerivative,
    braidTangent,
    braidLocalSpeed,
    quadrupleHelixPoint,
    fourTourPoint,
    trefoilPoint,
    mobiusPose,
    contactSlip,
    build,
    buildNuclide,
    evaluate,
    evaluateNseq05,
    selfTest
  });
})(typeof window !== 'undefined' ? window : globalThis);
