# Convergence Lattice Toy

Working prototype based on the interactive convergence lattice in
`Release/HTML_SDT_Website/st_00_primitives.html`.

## Run

Open `index.html` in a modern browser with WebGL enabled.

- Drag the canvas to orbit the concentric-shell lattice.
- Use the mouse wheel or trackpad to zoom.
- Select **Replay influx**, press `Space`, or select a primitive to run the
  inward pulse.
- Select **Reset view** or press `R` to restore the starting camera position.

The scene renders real three-dimensional point coordinates through WebGL. It is
still a visual prototype: it does not calculate a physical pressure, force, or
particle interaction.

## 3D Upgrade

The source page's manual 2D-canvas projection has been replaced in `index.html`
with a self-contained WebGL renderer. It draws six Fibonacci-distributed
spherical shells plus a compact central displacement, with orbit camera, zoom,
depth-scaled point sprites, reduced-motion support, and an inward pulse.

Only the local prototype changed; the release website source remains untouched.

## Source Freeze

| Release source | SHA-256 |
|---|---|
| `Release/HTML_SDT_Website/st_00_primitives.html` | `892b470513231774ceae720f0569325d37fa4e1be9c99bef8a58cbc709bf664b` |
| `Release/HTML_SDT_Website/style.css` | `d3f60dae27c0513c9f0706b127a6ee89c012f3d4854bba2f141a2ce2740ffa99` |
| `Release/HTML_SDT_Website/sdt-shell.css` | `ed54eaac4f5394ad1c341ac1ffee4bf88497daa885892c200eb762107bdb893a` |
| `Release/HTML_SDT_Website/sdt-shell.js` | `245885242c57bff400dd6385248b1709642765e73c42762dce8e4639075495b5` |
| `Release/HTML_SDT_Website/favicon.svg` | `b34294e42c680e49fe339c53012ff952b229087fef28ca803c2838ad00095fc7` |
| `Release/HTML_SDT_Website/favicon.ico` | `733380bdd8f7af6869d40316d984a56ddd663db71dce50ae593fa6b976b53e6d` |
| `Release/HTML_SDT_Website/apple-touch-icon.png` | `a510ff89fa46a3e7fa4e0e1f0e89760e63773e6c119bfc971300c9d09ffb3b6a` |
| `Release/HTML_SDT_Website/site.webmanifest` | `19f2a60fcd1069e0e1e94aef54d490e9a654dd6b8d0d3ddf46fb7847e5db4cfa` |
| `Release/HTML_SDT_Website/i18n_dict_st.js` | `103a6c23950085b47f5de5f029bfd1386565aede7008afb8310cbb9da04a942d` |
| `Release/HTML_SDT_Website/i18n.js` | `7b77a7bb6cba1bfaf2ba3d1210f3974d12a988d0d8e5a8cf860bc87f601b1262` |

The listed hashes freeze the release baseline. The local `index.html`
intentionally differs because it contains the WebGL 3D upgrade.

## Verification

The in-app browser had no available backend during this work, so rendered visual
inspection was unavailable. JavaScript syntax and local asset resolution are
checked statically; all untouched copied assets are hash-checked against the
frozen release sources.
