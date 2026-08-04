# GOM23 — Data requirements

One requirement, owed from P3:

**Real powered-ascent telemetry** — a launch vehicle's vertical leg with both books:
proper acceleration (IMU / thrust-over-mass) and kinematic state (GPS/radar-derived r(t),
v(t)). Public webcast-telemetry extractions of Falcon-class ascents carry velocity/altitude
at ~1 Hz; IMU-grade proper acceleration requires flight data or a reconstruction from
throttle/mass models — the reconstruction route must state its model inputs and is
second-class. Deliverable when acquired: ϟ_E recovered from
(a_proper − a_kinematic)·r²/c² across the profile, gate 1% against `bridge::koppa_Earth`,
whole-range single pass. Cache under `C:\sdt-data\` per repo convention.
