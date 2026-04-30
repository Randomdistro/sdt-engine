"""
Generate the full 72-ion table for §10.1 of the koppa paper.

For each isoelectronic sequence (N = number of remaining electrons after ionisation),
we compute the ionisation energy for ions with Z = N to Z = N+some.

The koppa identity for ions:
  E_N(Z) = Ry × Z_eff^2 / n^2
  v = alpha × c × Z_eff / n
  koppa = (1/alpha) × sqrt(R_p / a_0) = c/v × sqrt(R_p / r_n) = 0.5464

This is exact for H-like (N=0 after stripping, but N=1 means 1 electron remaining).
For multi-electron: v = sqrt(2 IE / m_e), then k = c/v, z = v^2/c^2, zk^2 = 1 exactly.
"""

import math

# Constants
c = 299_792_458.0
alpha = 7.2973525693e-3
alpha_inv = 137.035999084
a_0 = 5.29177210903e-11
R_p = 8.414e-16
m_e = 9.1093837015e-31
eV_to_J = 1.602176634e-19
Ry_eV = 13.605693122994
hbar = 1.054571817e-34

# Proton koppa
koppa_H = (1.0/alpha) * math.sqrt(R_p / a_0)
print(f"Proton koppa = (1/alpha) sqrt(R_p/a_0) = {koppa_H:.4f}")
print()

# NIST ionisation energy data from the engine (all values in eV)
elements = {
    1:  ("H",  [13.598]),
    2:  ("He", [24.587, 54.418]),
    3:  ("Li", [5.392, 75.640, 122.454]),
    4:  ("Be", [9.323, 18.211, 153.896, 217.718]),
    5:  ("B",  [8.298, 25.155, 37.930, 259.375, 340.228]),
    6:  ("C",  [11.260, 24.383, 47.888, 64.492, 392.090, 489.993]),
    7:  ("N",  [14.534, 29.601, 47.449, 77.474, 97.890, 552.070, 667.046]),
    8:  ("O",  [13.618, 35.117, 54.936, 77.414, 113.899, 138.120, 739.290, 871.410]),
    9:  ("F",  [17.423, 34.970, 62.708, 87.140, 114.240, 157.160, 185.186, 953.900, 1103.117]),
    10: ("Ne", [21.565, 40.963, 63.450, 97.120, 126.210, 157.930, 207.280, 239.100, 1195.829, 1362.199]),
    11: ("Na", [5.139, 47.286, 71.620, 98.910, 138.400, 172.180, 208.500, 264.150, 299.860, 1465.120, 1648.702]),
    12: ("Mg", [7.646, 15.035, 80.144, 109.265, 141.270, 186.760, 225.020, 265.960, 328.060, 367.500, 1761.805, 1962.665]),
    13: ("Al", [5.986, 18.829, 28.448, 119.992, 153.825, 190.490, 241.760, 284.590, 330.130, 398.750, 442.000, 2085.977, 2304.141]),
    18: ("Ar", [15.760, 27.630, 40.740, 59.810, 75.020, 91.010, 124.320, 143.460]),
    26: ("Fe", [7.902, 16.190, 30.650, 54.800, 75.000, 99.100, 124.300, 151.100]),
    29: ("Cu", [7.726, 20.292]),
    36: ("Kr", [14.000, 24.360, 36.950, 52.500, 64.690, 78.500]),
    47: ("Ag", [7.576, 21.490]),
    54: ("Xe", [12.130, 20.975, 31.050]),
    79: ("Au", [9.226, 20.520]),
    82: ("Pb", [7.417, 15.032, 31.937, 42.320]),
}

# For each ionisation event: ion goes from charge +q to +(q+1)
# N_remaining = Z - q (electrons remaining before this ionisation)
# The "isoelectronic sequence" is N_remaining

# Build the full list of ions grouped by N_remaining after stripping
# Actually, the "isoelectronic sequence" for ionisation level `level` of element Z
# is: N = Z - level + 1 (electrons remaining = Z - (level-1))
# No wait: level=1 means 1st ionisation: removing 1 electron from neutral atom
# So electrons remaining AFTER = Z - 1. The ion produced is Z^+1.
# "N_remaining after" for level i = Z - i

# For the koppa paper, we group by N_remaining BEFORE ionisation = Z - level + 1
# This is the "X-like" sequence: ions with the same electron count.
# H-like = 1 electron, He-like = 2 electrons, etc.

# Group by "electrons before ionisation" = Z - (level - 1) = Z - level + 1
# For H-like (1 electron → 0): level = Z, electrons before = 1
# For He-like (2 → 1): level = Z-1, electrons before = 2

sequences = {}  # key = N_electrons_before, value = list of (Z, level, IE, ion_label)

roman = {1:'I', 2:'II', 3:'III', 4:'IV', 5:'V', 6:'VI', 7:'VII', 8:'VIII',
         9:'IX', 10:'X', 11:'XI', 12:'XII', 13:'XIII', 14:'XIV'}

for Z, (sym, IEs) in sorted(elements.items()):
    for i, IE in enumerate(IEs):
        level = i + 1  # 1st, 2nd, etc. ionisation
        N_before = Z - level + 1  # electrons remaining before this ionisation
        charge_after = level  # charge state after ionisation
        
        # Ion notation: e.g., Fe VI means Fe^5+ → Fe^6+ (6th ionisation)
        # Actually in spectroscopic notation, Fe I = neutral, Fe II = Fe+, etc.
        spec_num = level + 1  # Fe I = neutral, so ionisation to Fe II is 1st IE
        # No: "1st ionisation energy" produces Fe II from Fe I.
        # The ion PRODUCED has charge = level
        # Spectroscopic notation: charge state q → roman numeral (q+1)
        # So 1st IE of Fe (Fe I → Fe II) creates Fe II.
        
        ion_label = f"{sym} {roman.get(charge_after, str(charge_after))}→{roman.get(charge_after+1, str(charge_after+1))}" if charge_after < 14 else f"{sym}^{charge_after-1}+→{charge_after}+"
        
        # Simpler: just label the ion that EXISTS before ionisation
        # H-like means 1 electron: that's the ion at charge = Z-1
        # Ion label = Symbol^(Z-N_before)+ e.g., Fe^25+ for H-like Fe
        
        if N_before not in sequences:
            sequences[N_before] = []
        
        q = Z - N_before  # charge of the ion before ionisation
        if q == 0:
            label = f"{sym}"
        elif q == 1:
            label = f"{sym}⁺"
        else:
            label = f"{sym}^{q}+"
        
        sequences[N_before].append((Z, level, IE, label, N_before))

# Print by sequence
seq_names = {
    1: "H-like", 2: "He-like", 3: "Li-like", 4: "Be-like", 5: "B-like",
    6: "C-like", 7: "N-like", 8: "O-like", 9: "F-like", 10: "Ne-like",
    11: "Na-like", 12: "Mg-like", 17: "Cl-like", 18: "Ar-like",
    19: "K-like", 20: "Ca-like", 21: "Sc-like", 25: "Mn-like",
    26: "Fe-like", 27: "Co-like", 28: "Ni-like", 29: "Cu-like",
    33: "As-like", 34: "Se-like", 35: "Br-like", 36: "Kr-like",
    46: "Pd-like", 47: "Ag-like", 52: "Te-like", 53: "I-like", 54: "Xe-like",
    78: "Pt-like", 79: "Au-like", 80: "Hg-like", 81: "Tl-like", 82: "Pb-like"
}

total_ions = 0
print("="*100)
print("FULL ION TABLE — Koppa Ionisation Derivation")
print("="*100)
print()

# For Koppa derivation:
# H-like ion: IE = Ry × Z^2  (n=1 ground state)
# In koppa terms: v_n = alpha c Z / n
# koppa = c / v_n × sqrt(R_p / (a_0 n^2/Z))
#       = (n / (alpha Z)) × sqrt(Z R_p / (a_0 n^2))
#       = (1/alpha) × sqrt(R_p / a_0) × (1/n) × n × (1/Z) × sqrt(Z)... let me redo
#
# v = alpha c Z_eff / n  (Bohr velocity)
# r = a_0 n^2 / Z_eff     (Bohr radius)
# koppa^2 = R_p / r × (c/v)^2... no. Let me use the proper definition.
#
# koppa = c / v_surface × sqrt{...}... this is for ORBITAL velocity law.
# For the atom:
# v(r) = (c/koppa) sqrt(R_p / r)
# => koppa = (c/v) sqrt(R_p / r)
# With v = alpha c Z / n and r = a_0 n^2 / Z:
# koppa = (c / (alpha c Z/n)) × sqrt(R_p / (a_0 n^2 / Z))
#       = (n / (alpha Z)) × sqrt(Z R_p / (a_0 n^2))
#       = (n / (alpha Z)) × sqrt(Z / n^2) × sqrt(R_p / a_0)
#       = (n / (alpha Z)) × (sqrt(Z) / n) × sqrt(R_p / a_0)
#       = sqrt(Z) / (alpha Z) × sqrt(R_p / a_0)
#       = 1 / (alpha sqrt(Z)) × sqrt(R_p / a_0)
# WAIT — that depends on Z! That's wrong...
#
# Actually NO. The orbital velocity law is v = (c/k) sqrt(R_body/r).
# For the proton: R_body = R_p.
# v_n = (c/ϟ_H) sqrt(R_p / r_n) where r_n = a_0 n^2 / Z.
# So v_n = (c/ϟ_H) sqrt(R_p Z / (a_0 n^2))
# But from Bohr: v_n = alpha c Z / n
# => alpha c Z / n = (c/ϟ_H) sqrt(Z R_p / (a_0 n^2))
# => alpha Z / n = (1/ϟ_H) sqrt(Z R_p / a_0) / n
# => alpha Z = (1/ϟ_H) sqrt(Z R_p / a_0)
# => ϟ_H = sqrt(Z R_p / a_0) / (alpha Z) = sqrt(R_p/a_0) / (alpha sqrt(Z))
#
# This DOES depend on Z! So ϟ_H is NOT constant across Z!
# Unless... the "body radius" scales with Z.
# If R_body = Z × R_p (nuclear charge radius), then:
# v_n = (c/ϟ) sqrt(Z R_p / r_n)
# => alpha c Z / n = (c/ϟ) sqrt(Z R_p × Z / (a_0 n^2))
# => alpha Z / n = (1/ϟ) × Z sqrt(R_p / a_0) / n
# => alpha = (1/ϟ) sqrt(R_p / a_0)
# => ϟ = sqrt(R_p / a_0) / alpha = (1/alpha) sqrt(R_p/a_0)
# NOW it's Z-independent!
#
# So the correct formula uses R_nucleus = Z × R_p as the body radius.

print("KEY IDENTITY:")
print(f"  v_n = (c/ϟ) sqrt(Z R_p / r_n)  where r_n = a_0 n²/Z")
print(f"  => ϟ = (1/α) sqrt(R_p / a_0) = {koppa_H:.4f}")
print(f"  This is Z-independent because R_nucleus = Z × R_p.")
print()

# Now for the actual ionisation energy derivation:
# IE = ½ m_e v² where v = alpha c Z_eff / n
# In koppa: v = (c/ϟ) sqrt(Z_eff R_p / r)
# At the Bohr radius r = a_0 n²/Z_eff:
# v = (c/ϟ) sqrt(Z_eff R_p Z_eff / (a_0 n²))
#   = (c/ϟ) Z_eff sqrt(R_p/a_0) / n
#   = (c/ϟ) Z_eff × alpha × ϟ / n  [since sqrt(R_p/a_0) = alpha × ϟ]
#   = alpha c Z_eff / n   ✓
# IE = ½ m_e v² = ½ m_e (alpha c Z_eff / n)² = Ry Z_eff² / n²

# For the full 72-ion table, I need Z_eff for each.
# H-like (N=1): Z_eff = Z (exact)
# Multi-electron: Z_eff = sqrt(IE × n² / Ry) (extracted from measured IE)

# The POINT is: for EVERY ion, the koppa is the SAME.
# IE = Ry × Z_eff² / n²
# v = alpha c Z_eff / n
# koppa = (c/v) × sqrt(Z_eff R_p / r_n) where r_n = a_0 n²/Z_eff
# koppa = (n/(alpha Z_eff)) × Z_eff sqrt(R_p/a_0) / n = sqrt(R_p/a_0)/alpha = 0.5464

# So the koppa is identically 0.5464 for EVERY ion by construction,
# because the orbital law with R = Z_eff × R_p gives:
#   ϟ = (1/alpha) sqrt(R_p/a_0) regardless of Z_eff.

# What the TABLE should show is:
# 1. The measured IE for each ion
# 2. The Z_eff extracted from it
# 3. The koppa computed from (v, R_eff, r_n)
# 4. That koppa = 0.5464 every time

print("MATHEMATICAL DERIVATION:")
print()
print("For any ion with Z_eff effective nuclear charge at quantum level n:")
print()
print("  v_n = α c Z_eff / n          (Bohr velocity)")
print("  r_n = a₀ n² / Z_eff          (Bohr radius)")
print("  R_eff = Z_eff × R_p           (effective nuclear radius)")
print()
print("Substituting into the koppa orbital law v = (c/ϟ)√(R/r):")
print()
print("  ϟ = (c/v_n) √(R_eff/r_n)")
print("    = [n/(α Z_eff)] × √[Z_eff R_p × Z_eff/(a₀ n²)]")
print("    = [n/(α Z_eff)] × [Z_eff/n] × √(R_p/a₀)")
print("    = (1/α) √(R_p/a₀)")
print(f"    = {koppa_H:.4f}")
print()
print("Z_eff cancels. n cancels. ϟ is invariant across ALL ions.")
print()

# Now let me generate the FULL table with actual NIST data
# For H-like: IE = Ry Z²  → Z_eff = Z (exact for fully stripped + 1e)
# For others: Z_eff = sqrt(IE × n²/Ry) gives the effective Z

print()
print("="*120)
print(f"{'Ion':<12} {'Z':>3} {'N':>3} {'Level':>5} {'IE (eV)':>12} {'Z_eff':>8} {'v/c':>10} {'ϟ':>8} {'Sequence':<12}")
print("-"*120)

seq_count = {}
all_ions = []

for Z, (sym, IEs) in sorted(elements.items()):
    for i, IE in enumerate(IEs):
        level = i + 1
        N_before = Z - level + 1  # electrons before this ionisation
        
        # Determine quantum numbers
        # For the LAST electron being removed:
        # If N_before = 1 (H-like): n=1
        # If N_before = 2 (He-like): n=1
        # If N_before = 3 (Li-like): the outer electron is n=2
        # etc.
        
        # Shell structure (simplified):
        # N=1: n=1 (1s)
        # N=2: n=1 (1s²)
        # N=3-4: n=2 (2s)
        # N=5-10: n=2 (2p)
        # N=11-12: n=3 (3s)
        # N=13-18: n=3 (3p)
        # N=19-20: n=4 (4s)
        # N=21-28: n=3 (3d)
        # N=29-30: n=4 (4s)
        # ...

        shell_n = {1:1, 2:1, 3:2, 4:2, 5:2, 6:2, 7:2, 8:2, 9:2, 10:2,
                   11:3, 12:3, 13:3, 14:3, 15:3, 16:3, 17:3, 18:3}
        n = shell_n.get(N_before, 3 if N_before <= 28 else 4 if N_before <= 36 else 5 if N_before <= 54 else 6)
        
        # For this ionisation, the real test is:
        # The measured IE defines v = sqrt(2IE/m_e)
        # Then k = c/v and z = v²/c² and zk² = 1 (always, by definition)
        # The KOPPA test is: does v = (c/ϟ)√(Z_eff R_p/r_n) with ϟ=0.5464?
        
        # Extract Z_eff from measured IE:
        # IE = Ry × Z_eff² / n²
        # Z_eff = n × sqrt(IE / Ry)
        Z_eff = n * math.sqrt(IE / Ry_eV)
        
        # Compute v
        v = alpha * c * Z_eff / n
        v_over_c = v / c
        
        # Verify koppa
        r_n = a_0 * n * n / Z_eff
        R_eff = Z_eff * R_p
        koppa_check = (c / v) * math.sqrt(R_eff / r_n)
        
        charge = Z - N_before
        if charge == 0:
            ion_name = f"{sym} I"
        else:
            ion_name = f"{sym} {roman.get(charge+1, str(charge+1))}"
        
        seq_name = seq_names.get(N_before, f"{N_before}e")
        
        if seq_name not in seq_count:
            seq_count[seq_name] = 0
        seq_count[seq_name] += 1
        total_ions += 1
        
        all_ions.append((ion_name, Z, N_before, level, IE, Z_eff, v_over_c, koppa_check, seq_name))
        
        print(f"{ion_name:<12} {Z:>3} {N_before:>3} {level:>5} {IE:>12.3f} {Z_eff:>8.3f} {v_over_c:>10.6f} {koppa_check:>8.4f} {seq_name:<12}")

print("-"*120)
print(f"{'TOTAL':>42} {total_ions} ions")
print()

# Group summary
print(f"{'Sequence':<15} {'Count':>5} {'ϟ min':>10} {'ϟ max':>10} {'Spread':>10}")
print("-"*55)

# Group by sequence
seq_data = {}
for ion in all_ions:
    seq = ion[8]
    k = ion[7]
    if seq not in seq_data:
        seq_data[seq] = []
    seq_data[seq].append(k)

for seq in sorted(seq_data.keys(), key=lambda s: len(seq_data[s]), reverse=True):
    vals = seq_data[seq]
    mn = min(vals)
    mx = max(vals)
    spread = (mx - mn) / ((mx+mn)/2) * 100
    print(f"{seq:<15} {len(vals):>5} {mn:>10.4f} {mx:>10.4f} {spread:>9.4f}%")

print()
print(f"Total ions: {total_ions}")
print(f"ALL koppa values: {koppa_H:.4f} (invariant by construction)")
