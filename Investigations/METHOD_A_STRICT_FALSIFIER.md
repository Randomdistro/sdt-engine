# METHOD A — The Strict Falsifier (the 3-front audit)
### Standalone runnable spec. A cold instance can execute this without prior context.
*Consolidated from `HUNTER_PROTOCOL.md` (§0–§K) and `PROMPT_EXECUTION_PROTOCOL.md §8`, 2026-07-23.*

## What this is
The falsifier that keeps SDT honest. It runs a claim through **three structures**, each auditing the
last. Its job is to kill fabrication, circularity, and fishing — and nothing else. It is deliberately
harsh; Method B (recovery) exists precisely to catch any legitimate claims this front throws out.

## The one gate (the fishbowl)
We are inside the medium and cannot step outside it. Looking at what we already see can only establish
**consistency with appearance**, never truth. The only thing that establishes truth from inside is
**a mechanism that predicts something not yet looked at, followed by the look.** Prediction first, then
the look. Everything below guards that gate.

**The single sin:** pretending consistency-with-a-look-already-taken is knowledge. Its four disguises are
the kill-list. Its opposite — the strongest result — is **CONVERGENCE**: an independent mechanism landing
on a look someone else already took, without having consumed it (survives the delete-test).

## The kill criterion — what counts, on THIS front, as sinking the Standard Model
This is the strict blade. It is the fishbowl gate made operational, and it is deliberately narrow. A claim
sinks the SM, **on Method A**, only if **all three** hold:

1. **Divergence** — SDT and the SM predict *different values* for a measurable quantity (not the same number by a nicer story).
2. **Pre-registration** — the SDT value is stated *before* the measurement and is *unfitted* (no knob turned to match).
3. **Feasibility** — decidable with existing data or a near-term instrument.

Anything failing any one of the three is **not a kill on this front** — it is either a re-derivation
(same number, no divergence), a post-fit (no pre-registration), or an untestable claim (no feasibility).
Method A does **not** relax this. The looser, legitimate criterion — *the SM is sunk where it cannot
account for what SDT can*, and *fitting is legitimate model-building* — belongs to **Method B**, which
exists precisely because this blade over-kills. Do not import Method B's latitude here; do not import this
blade's severity there. Two fronts, two criteria, reconciled only at the Adjudicator.

## The three structures (the "3 fronts")
1. **INVESTIGATION** — makes a claim, with a mechanism.
2. **AUDIT** — tests it; can KILL it (§A–§G).
3. **ADJUDICATOR** — audits the KILL itself, because a kill is *also* a claim and nothing else checks it.

---

## FRONT 1 — INVESTIGATION (state it so it can be shot at)
Before any test, the claim must declare:
- **The mechanism**, said aloud in the medium's own terms (what moves, what records it, what transmits it, where the rate comes from). A claim that cannot be said this way carries an inherited abstraction — and that is where the error lives.
- **The prediction** — what unlooked-at thing does it call *before* the look? If it only reproduces a look already taken, it is consistency, not a result (fishbowl gate).
- **The inputs** — every measured anchor and every engine/canon value it consumes (the dependency map).

## FRONT 2 — AUDIT (the kill instruments)

**READ THE SOURCE first.** Rule on the primary document — never a summary, an agent's characterisation, or memory. Confabulation looks like work and is worse than silence.

**§A — Kill list (any one = instant fail):**
| mode | tell |
|---|---|
| IDENTITY-PASS | output equals a value the tool read in |
| CIRCULARITY | derive X from a measurement, then "predict" that measurement |
| FISHED (exp/coeff) | a bare exponent or ×k with no prior justification |
| FISHED RECOVERY | a "fix" whose freedom is a knob, not a native quantity |
| RETRO-PASS | tolerance widened after seeing the number |
| PLUG | undocumented CALIBRATED coefficient |
| BORROW-SMUGGLE | G / M / GM / ψ / G_F / ΛCDM load-bearing in the SDT chain |
| GATE-CONTRABAND | a kill condition enforcing a rival's AXIOM, not a measured anchor |

**§B — Contamination rule:** rivals supply measured **numbers** (1836.15, 2.224 MeV, the B/A curve), never their **story**. A rival appears only as an `OBSERVED` comparison column, never in the chain. Catching SDT lean on a rival *strengthens* the audit; using a rival to kill SDT *invalidates* it.

**§C — Independence test (all three or it is not a result):** (1) Independent of the input? (2) Units close exactly? (3) **Predict**, or merely **bracket/fit**? Bracketing is not predicting.

**§D — The seven questions (on any KILL/OPEN/FAIL):** (1) why fail (exact mechanism)? (2) recoverable? (3) what did it fail to account for? (4) which **premise** errored (failure is in the premise)? (5) what freedom corrects it? (6) native quantity or bare knob? (7) does it **cascade** from another error?
**Closure Principle:** when the root is an open loop (orphan scale, dead function, un-derived constant), the correction is to **CLOSE** it, never to amputate. Amputation is a fake correction. "Eliminate vs tune" is a false pair — the third, usually correct, option is CLOSE.

**§F — Evidence:** SHOW, don't assert (timestamp / diff / delete-test / independent recompute). Own your own errors as hard as anyone's. Never touch the laws canon (`Engine/include/sdt/`, `Laws/`) without explicit OK.

**§G — The mirror (audit the auditor), asked at every hunt-start and every kill:**
1. **Faith ledger** — what am I accepting on faith, and is it a measured anchor, an internal-consistency requirement, a pre-committed native criterion, or faith? Faith is allowed only when named as faith.
2. **Gatekeeper** — am I letting the rival define admissibility? A kill condition that exists only because a rival's axioms would otherwise break is **contraband** — kill the gate, not the route.
3. **Nothing ruled out of hand** — status labels are a ledger, impossibility claims are legislation. Every "cannot be derived" carries (a) the premise-class it was proven in and (b) its re-open condition. "CALIBRATED until derived" is absolute; "never derivable" is banned.

## FRONT 3 — ADJUDICATOR (audit the kill)
**Founding axiom:** a KILL is a disagreement between investigation and audit, and a disagreement means a **faulty premise exists — in one party or the other.** Do not presume the investigation is the guilty one. Break **both** premises to their minima before ruling. Trigger on every KILL / NO-RECOVERY.

Run the four primitives (Space · Matter · Movement · Now) across both premises, six phases:
1. **Minima** — what is moving (PASS/BECOME/PRESS), what responds (count not amount), what is the causation (occlusion, never stored substance), what is the flow (in/through/out — a kill that stops the ledger mid-flow is suspect).
2. **Scope** — was the frame the right size? (too wide = can't discriminate; too narrow = strawman). Steps missed or too many?
3. **Label** — anything mislabelled (energy where movement was meant; radius where count)? Any rival mechanism imported into the *kill*?
4. **Omission** — a native quantity, an earned result elsewhere, an alternative reading the kill never considered?
5. **Neighbour test** — if this kill were held as law, would it wreck a standing earned result in an adjacent system? The neighbours are witnesses.
6. **Contraband cross-reference** — did *either* party rest on a QM/GR/SR/ΛCDM abstraction the repo has already mechanised elsewhere? Cross-reference before ruling.

**Ruling (one of four, no label moves without it):** KILL CONFIRMED · KILL RESCOPED (name the narrower class + re-open trigger) · KILL FALSE, route lives (the audit's premise was faulty) · BOTH FAULTY (shared bad floor; rebuild both).

**§H.LEASH — no ruling without a named mechanism.** Two symmetric biases: protect-the-kill (old-guard) and overturn-the-kill (people-pleasing). The single cure for both: name the **mechanism of harm** for a strike exactly as strictly as the **mechanism of death** for a kill. Cannot name it → the ruling is fabricated, in either direction. Test on your own verdict before filing: **"by what mechanism?"**

## §K — KILL-DEEPEN (hand-off to Method B)
A kill is **provisional** until the deeper regime has run. No verdict file says KILLED on a first-pass gate alone. On any kill, sort the root into four: **claim false** / **dependency upstream false** / **prompt under-specified** / **gate contraband**. Then hand the item to **Method B** for the deep re-investigation. (No auto-agents on kill re-adjudication — run it directly.)

## The verdict line (every hunt ends here)
> **Prompt completion** [A–F] · **Physics class** [NATIVE / CONVERGENCE / DEGENERATE / BORROW / KILLED / OPEN] · **Recovery** [RECOVERED / PARTIAL / NO RECOVERY] · **Cascade root** [id or none].

## Creed
*Find the fault. Trace it to the premise. Run it to the root. Correct it, or kill it clean. Show your work. The number is never the prey.*
