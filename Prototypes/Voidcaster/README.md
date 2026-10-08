# Voidcaster

Pixel-art defence game built on the A/B/C convergence toy (`Prototypes/Convergence_ABC_Influx_Toy`, commit `efdf672`).
Open `index.html` in a browser (it fills the screen; F toggles fullscreen). Thirty missions, three bosses.

Voidcaster is the lure: the Dearth's mass homes on him. He deploys up to three arcs and a kill zone (a portal to a
neutron star) and slings the hunters around the arcs and into the portal. No projectile weapons.

- Arcs are fixed-radius curved plates; the wheel or `[ ]` changes the arc length, not the radius. Each arc turns its
  convex side to the nearest body, and acts through the cross-section it presents (projected width of the arc along the
  line to that body). Hazards bounce off the arc itself.
- Bodies are driven into the deficit by `F = k r1^2 r2^2 / d^2` with mass `r^3`, as in the toy.
- Anything reaching the kill zone is consumed. Bosses lose health when what they throw is consumed.

Controls: WASD move; drag an arc or the kill zone with the mouse; click empty space deploys a stowed arc; right-click or
`X` stows; wheel or `[ ]` lengthens or shortens; `1 2 3` select; Space flares (stronger, longer-range lure); P pause; M mute.

Author: James Christopher Tyndall, Melbourne.
