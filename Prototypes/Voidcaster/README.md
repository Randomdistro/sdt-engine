# Voidcaster

Pixel-art defence game built on the A/B/C convergence toy (`Prototypes/Convergence_ABC_Influx_Toy`, commit `efdf672`).
Open `index.html` in a browser (it fills the screen; F toggles fullscreen). Thirty missions, three bosses.

Mechanics follow the toy: influx lines are cut by occluders, and bodies are driven into the deficit by
`F = k r1^2 r2^2 / d^2` with mass `r^3`. Voidcaster's voids are crescents that turn their convex side to the nearest
closing body; the pull each exerts uses the cross-section presented, `r_eff^2 = r^2 (0.35 + 0.65 |cos a|)`.
Collisions and the budget use the bounding circle.

Controls: drag a void with the mouse, left-click empty space to fire, WASD move, wheel or `[ ]` resize, `1 2 3` select,
Space release, P pause, M mute.

Author: James Christopher Tyndall, Melbourne.
