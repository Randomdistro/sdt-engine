# PM08 — Plasma connectivity and contact loading: reset record, specification audit (2026-10-10)

**Protocol:** `Investigations/RESET_2026-10-06/PROTOCOL.md`. Session sdt-engine-e0.

**Read:**
- `PROMPT.md`
- `graph_v2.json`: layer 0, no edges. The prompt names APS15, which sits at layer 7 and has not been rerun under this protocol.

## Audit
1. **The object under test has no definition.** P1 asks for "collective electron connectivity" and a "plasma pressure on a seat" written from PM01–PM07 objects. Neither the prompt nor canon gives that definition; the ledger lists it as D48, open.
2. **Writing one now would be reverse-engineered.** P2's known answer is the Debye length, λ_D² = kT/(4π n k_e e²) = kT/(4π n αħc). A wake-contact count can be arranged to reproduce it. For example, the radius at which the coupling summed over the electrons inside it, each at αħc/r, equals kT, gives λ_D only with a geometric factor chosen to match. Choosing the definition with the target formula in view is the prompt's forbidden "redefining connectivity after seeing results" in another form, and it is not done.
3. **Supplier.** The prompt requires APS15 to be COMPUTED. APS15 is not rerun, and PM04's g++ non-reproduction (d814fb6) stands. Under the protocol an open supplier makes the consumer conditional.

## Outcome
**G2 (open): specification incomplete; no instrument.**

**What opens it:** a native statement of connectivity, a count or graph of wake contacts, written from the medium's mechanics before the Debye comparison. That is Harvey's to give: what makes two free electrons "connected", in spation terms. Then P2's known answers decide it.

**Downstream:** NP40 ran its P0–P2 without a loading. NP41 and SAR10 remain conditional on PM08.

## Comparison with the archived record
Deferred.
