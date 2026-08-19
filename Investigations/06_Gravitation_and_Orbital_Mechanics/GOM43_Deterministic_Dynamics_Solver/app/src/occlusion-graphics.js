const TWO_PI = Math.PI * 2;

const add = (a, b) => [a[0] + b[0], a[1] + b[1], a[2] + b[2]];
const subtract = (a, b) => [a[0] - b[0], a[1] - b[1], a[2] - b[2]];
const scale = (vector, factor) => vector.map((value) => value * factor);
const dot = (a, b) => a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
const cross = (a, b) => [
  a[1] * b[2] - a[2] * b[1],
  a[2] * b[0] - a[0] * b[2],
  a[0] * b[1] - a[1] * b[0],
];
const magnitude = (vector) => Math.hypot(...vector);

export function normalize(vector) {
  const length = magnitude(vector);
  if (!Number.isFinite(length) || length === 0) return [0, 0, 0];
  return scale(vector, 1 / length);
}

/** Matches sdt::occlusion::pair_frame in Engine/include/sdt/occlusion.hpp */
export function pairFrame(bodyTowardPartner) {
  const normal = normalize(bodyTowardPartner);
  const axes = [[1, 0, 0], [0, 1, 0], [0, 0, 1]];
  let selected = 0;
  let alignment = Math.abs(dot(normal, axes[0]));
  for (let index = 1; index < axes.length; index += 1) {
    const candidate = Math.abs(dot(normal, axes[index]));
    if (candidate < alignment) {
      selected = index;
      alignment = candidate;
    }
  }
  const first = normalize(cross(normal, axes[selected]));
  const second = normalize(cross(normal, first));
  return { normal, first, second };
}

/** Matches sdt::occlusion::channel_offset — offsets inside the co-facing R disc */
export function channelOffset(channel, bodyRadiusM, frame) {
  if (channel === 0) return [0, 0, 0];
  const phase = TWO_PI * (channel - 1) / 6;
  const radial = (2 * bodyRadiusM) / 3;
  return add(
    scale(frame.first, Math.cos(phase) * radial),
    scale(frame.second, Math.sin(phase) * radial),
  );
}

export function channelDiscRadius(bodyRadiusM) {
  return bodyRadiusM / 3;
}

export function coFacingCrossSectionRadius(bodyRadiusM) {
  return bodyRadiusM;
}

export function channelCentre(bodyPositionM, channel, bodyRadiusM, frame) {
  return add(bodyPositionM, channelOffset(channel, bodyRadiusM, frame));
}

/** One body’s seven-circle partition on the disc facing a specific partner. */
export function buildCoFacingCrossSection(bodyPositionM, partnerPositionM, bodyRadiusM) {
  const towardPartner = subtract(partnerPositionM, bodyPositionM);
  const frame = pairFrame(towardPartner);
  const channels = Array.from({ length: 7 }, (_, channel) => ({
    channel,
    centre_m: channelCentre(bodyPositionM, channel, bodyRadiusM, frame),
    disc_radius_m: channelDiscRadius(bodyRadiusM),
    offset_m: channelOffset(channel, bodyRadiusM, frame),
  }));
  return {
    frame,
    bodyRadiusM,
    coFacingRadiusM: coFacingCrossSectionRadius(bodyRadiusM),
    channels,
  };
}

/** Ordered-pair layout for the selected 49-link matrix (target ← source). */
export function buildPairChannelLayout(targetPositionM, sourcePositionM, targetRadiusM, sourceRadiusM) {
  const frame = pairFrame(subtract(sourcePositionM, targetPositionM));
  const targetChannels = Array.from({ length: 7 }, (_, channel) => ({
    channel,
    centre_m: channelCentre(targetPositionM, channel, targetRadiusM, frame),
    disc_radius_m: channelDiscRadius(targetRadiusM),
    offset_m: channelOffset(channel, targetRadiusM, frame),
  }));
  const sourceChannels = Array.from({ length: 7 }, (_, channel) => ({
    channel,
    centre_m: channelCentre(sourcePositionM, channel, sourceRadiusM, frame),
    disc_radius_m: channelDiscRadius(sourceRadiusM),
    offset_m: channelOffset(channel, sourceRadiusM, frame),
  }));
  return { frame, targetChannels, sourceChannels };
}

export function relationEndpoints(interaction, layout) {
  return {
    target: layout.targetChannels[interaction.target_channel].centre_m,
    source: layout.sourceChannels[interaction.source_channel].centre_m,
  };
}

export function allCoFacingSections(bodyStates, bodyDefinitions) {
  const sections = [];
  for (const [bodyId, bodyState] of bodyStates) {
    const bodyDef = bodyDefinitions.get(bodyId);
    if (!bodyDef) continue;
    for (const [partnerId, partnerState] of bodyStates) {
      if (partnerId === bodyId) continue;
      sections.push({
        bodyId,
        partnerId,
        section: buildCoFacingCrossSection(
          bodyState.position_m,
          partnerState.position_m,
          bodyDef.radius_m,
        ),
      });
    }
  }
  return sections;
}
