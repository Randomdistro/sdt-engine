import csv
import random
import math

def generate_mock_sparc(filename="sparc_mock.csv", num_galaxies=175):
    # Constants
    c = 299792458.0
    koppa_Sun = 1477.046
    Sigma_sat_Msun_pc2 = 175.0
    km_s = 1000.0
    
    with open(filename, mode='w', newline='') as f:
        writer = csv.writer(f)
        writer.writerow(["Galaxy_Name", "M_bar_Msun", "h_R_kpc", "Sigma_0_Msun_pc2", "v_flat_meas_km_s"])
        
        for i in range(num_galaxies):
            name = f"MockGal_{i:03d}"
            
            # 1. Random mass between 1e7 and 5e11 (log uniform)
            log_M = random.uniform(7.0, 11.7)
            M_bar = 10**log_M
            
            # 2. Random h_R scaling roughly with M_bar (larger galaxies are wider)
            # typical scale length is ~0.5 kpc for dwarfs, ~3-8 kpc for massive spirals
            expected_hR = 0.5 * (M_bar / 1e8)**0.33
            h_R = expected_hR * random.uniform(0.5, 2.0)
            
            # 3. Random Sigma_0 (dwarfs are LSB ~10-50, spirals are HSB ~200-1000)
            expected_S0 = 30.0 * (M_bar / 1e8)**0.25
            Sigma_0 = expected_S0 * random.uniform(0.3, 3.0)
            
            # If a galaxy happens to not saturate at all, boost its Sigma_0
            threshold = Sigma_sat_Msun_pc2 * math.log(2.0)
            if Sigma_0 <= threshold:
                Sigma_0 = threshold + random.uniform(10.0, 50.0)
            
            # 4. Compute the ideal SDT v_flat to ensure we test exactly what we derived
            # We add ~5% gaussian noise to simulate observational errors in the "measured" v_flat
            koppa_g = M_bar * koppa_Sun
            
            r_sat_kpc = h_R * math.log(Sigma_0 / threshold)
            r_sat_m = r_sat_kpc * 3.085677581e19
            
            v_ideal_m_s = c * math.sqrt(0.5 * koppa_g / r_sat_m)
            v_ideal_km_s = v_ideal_m_s / km_s
            
            # Add scatter (5%)
            v_flat_meas = v_ideal_km_s * random.gauss(1.0, 0.05)
            
            writer.writerow([name, f"{M_bar:.3e}", f"{h_R:.3f}", f"{Sigma_0:.1f}", f"{v_flat_meas:.2f}"])

if __name__ == "__main__":
    generate_mock_sparc()
    print("Generated sparc_mock.csv with 175 mock galaxies.")
