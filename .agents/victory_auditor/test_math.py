import math

a = 5.790905e10
e = 0.205630
delta_phi = 5.0186e-7
v_sun = 436824.28
r_sun = 6.957e8
actual_c = 299792458.0

numerator = 6.0 * math.pi * r_sun
denominator = delta_phi * a * (1.0 - (e * e))
derived_c = v_sun * math.sqrt(numerator / denominator)
error_percent = abs(derived_c - actual_c) / actual_c * 100.0

print(f"Derived c: {derived_c}")
print(f"Error: {error_percent}%")
