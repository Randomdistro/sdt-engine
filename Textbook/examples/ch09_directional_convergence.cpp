// Chapter 9 — directional convergence: worked-example instruments.
// Pre-registration: Textbook/validation/ch09_PRE_REGISTRATION.md (registered before this file existed).
// Build: cl /std:c++20 /EHsc /O2 /utf-8 /I Engine/include /Fe:ch09.exe Textbook/examples/ch09_directional_convergence.cpp
//
// Quadrature: Gauss-Legendre in mu = cos(theta), uniform trapezoid in phi. No Cartesian vector type is used;
// directions are carried as (mu, phi) and the three component functions n_x, n_y, n_z are evaluated at nodes.
#include <sdt/laws.hpp>

#include <cmath>
#include <cstdio>
#include <vector>

namespace {

constexpr double kPi = 3.14159265358979323846;

struct GL {
    std::vector<double> x, w;  // nodes and weights on [-1, 1]
};

GL gauss_legendre(int n) {
    GL g;
    g.x.resize(n);
    g.w.resize(n);
    for (int i = 0; i < n; ++i) {
        double z = std::cos(kPi * (i + 0.75) / (n + 0.5));
        double pp = 0.0;
        for (int it = 0; it < 100; ++it) {
            double p1 = 1.0, p2 = 0.0;
            for (int j = 0; j < n; ++j) {
                const double p3 = p2;
                p2 = p1;
                p1 = ((2.0 * j + 1.0) * z * p2 - j * p3) / (j + 1.0);
            }
            pp = n * (z * p1 - p2) / (z * z - 1.0);
            const double dz = p1 / pp;
            z -= dz;
            if (std::fabs(dz) < 1e-16) break;
        }
        g.x[i] = z;
        g.w[i] = 2.0 / ((1.0 - z * z) * pp * pp);
    }
    return g;
}

// Map nodes of [-1,1] to [a,b].
GL on_interval(const GL& g, double a, double b) {
    GL h = g;
    for (std::size_t i = 0; i < g.x.size(); ++i) {
        h.x[i] = 0.5 * (b - a) * g.x[i] + 0.5 * (b + a);
        h.w[i] = 0.5 * (b - a) * g.w[i];
    }
    return h;
}

// Integral over a polar cap mu in [mu0, mu1] and phi in [0, 2pi) of f(mu, nx, ny, nz).
template <class F>
double sphere_integral(const GL& gmu, int nphi, F f) {
    double sum = 0.0;
    for (std::size_t i = 0; i < gmu.x.size(); ++i) {
        const double mu = gmu.x[i];
        const double st = std::sqrt(std::fmax(0.0, 1.0 - mu * mu));
        for (int k = 0; k < nphi; ++k) {
            const double phi = 2.0 * kPi * (k + 0.5) / nphi;
            sum += gmu.w[i] * (2.0 * kPi / nphi) * f(mu, st * std::cos(phi), st * std::sin(phi), mu);
        }
    }
    return sum;
}

int failures = 0;

void check(const char* id, const char* what, double value, double expected, double tol, bool relative = true) {
    const double err = relative ? std::fabs(value - expected) / std::fabs(expected) : std::fabs(value - expected);
    const bool ok = err <= tol;
    if (!ok) ++failures;
    std::printf("[%s] %-4s %-70s value %.12e expected %.12e err %.3e (tol %.0e)\n", ok ? "PASS" : "FAIL", id,
                what, value, expected, err, tol);
}

}  // namespace

int main() {
    const GL g1 = gauss_legendre(96);
    const int nphi = 64;
    const GL full = g1;                       // mu in [-1, 1]
    const GL half = on_interval(g1, 0.0, 1.0);  // mu in [0, 1]

    std::printf("== Instrument validation ==\n");
    check("V1", "oint dOmega = 4 pi", sphere_integral(full, nphi, [](double, double, double, double) { return 1.0; }),
          4.0 * kPi, 1e-12);
    check("V1", "oint n_x n_x = 4 pi / 3",
          sphere_integral(full, nphi, [](double, double x, double, double) { return x * x; }), 4.0 * kPi / 3.0, 1e-12);
    check("V1", "oint n_z n_z = 4 pi / 3",
          sphere_integral(full, nphi, [](double, double, double, double z) { return z * z; }), 4.0 * kPi / 3.0, 1e-12);
    check("V1", "oint n_x^2 n_y^2 = 4 pi / 15",
          sphere_integral(full, nphi, [](double, double x, double y, double) { return x * x * y * y; }),
          4.0 * kPi / 15.0, 1e-12);
    check("V1", "oint n_z^4 = 4 pi / 5",
          sphere_integral(full, nphi, [](double, double, double, double z) { return z * z * z * z; }), 4.0 * kPi / 5.0,
          1e-12);
    {
        double worst = 0.0;
        const double a = sphere_integral(full, nphi, [](double, double x, double, double) { return x; });
        const double b = sphere_integral(full, nphi, [](double, double, double y, double) { return y; });
        const double c = sphere_integral(full, nphi, [](double, double, double, double z) { return z; });
        const double d = sphere_integral(full, nphi, [](double, double x, double y, double z) { return x * y * z; });
        const double e = sphere_integral(full, nphi, [](double, double x, double, double z) { return x * x * z; });
        worst = std::fmax(std::fmax(std::fabs(a), std::fabs(b)), std::fmax(std::fabs(c), std::fmax(std::fabs(d), std::fabs(e))));
        check("V2", "oint n_i, oint n_i n_j n_k (worst absolute)", worst, 0.0, 1e-12, false);
    }
    check("V3", "hemisphere int mu dOmega = pi",
          sphere_integral(half, nphi, [](double mu, double, double, double) { return mu; }), kPi, 1e-12);
    check("V3", "hemisphere int mu^2 dOmega = 2 pi / 3",
          sphere_integral(half, nphi, [](double mu, double, double, double) { return mu * mu; }), 2.0 * kPi / 3.0, 1e-12);

    std::printf("\n== T1, T2: plane tractions for isotropic incident content, U = 1, q = U/(4 pi) ==\n");
    {
        const double q = 1.0 / (4.0 * kPi);
        // Absorbing plane, outward normal m = +z; content arrives from the hemisphere n_z > 0 and its
        // momentum is carried along -n, so the plane is pushed along -z with weight (n . m) = mu.
        const double tz = sphere_integral(half, nphi, [&](double mu, double, double, double) { return q * mu * mu; });
        const double tx = sphere_integral(half, nphi, [&](double mu, double x, double, double) { return q * mu * x; });
        const double ty = sphere_integral(half, nphi, [&](double mu, double, double y, double) { return q * mu * y; });
        check("T1", "absorbing plane, normal traction / U", tz, 1.0 / 6.0, 1e-12);
        check("T1", "absorbing plane, tangential part (absolute)", std::fmax(std::fabs(tx), std::fabs(ty)), 0.0, 1e-14,
              false);
        // Specular plane: normal impulse doubled.
        const double ts = 2.0 * tz;
        // Transport tensor trace share: Pi_ij = oint q n_i n_j, tr Pi / 3 with tr Pi = oint q.
        const double trPi = sphere_integral(full, nphi, [&](double, double x, double y, double z) {
            return q * (x * x + y * y + z * z);
        });
        check("T2", "specular plane, normal traction / U", ts, 1.0 / 3.0, 1e-12);
        check("T2", "specular traction vs tr(Pi)/3", ts, trPi / 3.0, 1e-12);
    }

    std::printf("\n== T3: displaced observer, second moment of the exact ray length (kappa = eps = ell = 1) ==\n");
    {
        const double R = 1.0;
        for (double ratio : {0.01, 0.05, 0.1}) {
            const double s = ratio * R;
            // phi(n) = L(theta)/(4 pi); Pi_zz = 2 pi int phi mu^2 dmu; Pi_xx = pi int phi (1-mu^2) dmu.
            double Pzz = 0.0, Pxx = 0.0, trace = 0.0;
            for (std::size_t i = 0; i < full.x.size(); ++i) {
                const double mu = full.x[i];
                const double L = -s * mu + std::sqrt(R * R - s * s * (1.0 - mu * mu));
                const double phi = L / (4.0 * kPi);
                Pzz += full.w[i] * 2.0 * kPi * phi * mu * mu;
                Pxx += full.w[i] * kPi * phi * (1.0 - mu * mu);
                trace += full.w[i] * 2.0 * kPi * phi;
            }
            const double A = R * R - s * s;
            const double Phi_closed = 0.5 * (R + (A / s) * std::asinh(s / std::sqrt(A)));
            const double aniso = (Pzz - Pxx) * R / (s * s);
            const double rel = std::fabs(aniso - 1.0 / 15.0) / (1.0 / 15.0);
            const bool ok_series = rel <= 3.0 * ratio * ratio;
            if (!ok_series) ++failures;
            std::printf("[%s] T3   s/R=%.2f  (Pi_par - Pi_perp) R/s^2 = %.9f  vs 1/15 = %.9f  rel %.3e  (limit %.3e)\n",
                        ok_series ? "PASS" : "FAIL", ratio, aniso, 1.0 / 15.0, rel, 3.0 * ratio * ratio);
            check("T3", "trace of Pi equals closed-form Phi(s)", Pzz + 2.0 * Pxx, Phi_closed, 1e-10);
            check("T3", "scalar content from the same quadrature equals Phi(s)", trace, Phi_closed, 1e-10);
            std::printf("       Pi_par = %.9f  Pi_perp = %.9f  isotropic share Phi/3 = %.9f  anisotropy/Phi = %.3e (s^2/15R^2 = %.3e)\n",
                        Pzz, Pxx, Phi_closed / 3.0, (Pzz - Pxx) / Phi_closed, s * s / (15.0 * R * R));
        }
    }

    std::printf("\n== T4: sphere of radius a in a parallel beam (beam momentum flux 1), surface integration ==\n");
    {
        const double a = 1.0;
        const double sigma = kPi * a * a;
        // mu = cosine between the outward normal and the direction the beam comes from; illuminated hemisphere.
        // dA = a^2 dmu dphi. Force components on the body, beam travelling along -z.
        double abs_z = 0.0, spec_z = 0.0, spec_x = 0.0, spec_y = 0.0, lam_z = 0.0;
        for (std::size_t i = 0; i < half.x.size(); ++i) {
            const double mu = half.x[i];
            const double st = std::sqrt(1.0 - mu * mu);
            for (int k = 0; k < nphi; ++k) {
                const double phi = 2.0 * kPi * (k + 0.5) / nphi;
                const double dA = half.w[i] * (2.0 * kPi / nphi) * a * a;
                const double mx = st * std::cos(phi), my = st * std::sin(phi), mz = mu;
                abs_z += mu * dA;                                  // absorbed momentum, along -z (magnitude)
                spec_z += 2.0 * mu * mu * mz * dA;                 // specular: 2 mu^2 along -m
                spec_x += 2.0 * mu * mu * mx * dA;
                spec_y += 2.0 * mu * mu * my * dA;
                lam_z += (2.0 / 3.0) * mu * mz * dA;               // Lambertian recoil per unit albedo, along -m
            }
        }
        check("T4", "absorbing sphere force / (sigma q_b)", abs_z / sigma, 1.0, 1e-10);
        check("T4", "specular sphere force / (sigma q_b)", spec_z / sigma, 1.0, 1e-10);
        check("T4", "specular sphere transverse part (absolute, / sigma)",
              std::fmax(std::fabs(spec_x), std::fabs(spec_y)) / sigma, 0.0, 1e-12, false);
        for (double rho : {0.25, 0.5, 1.0}) {
            check("T4", "Lambertian sphere, albedo rho: force / (sigma q_b) vs 1 + 4 rho / 9",
                  (abs_z + rho * lam_z) / sigma, 1.0 + 4.0 * rho / 9.0, 1e-10);
        }
        std::printf("       Lambertian recoil coefficient per unit albedo = %.12f (4/9 = %.12f); flat-plate value 2/3 = %.12f\n",
                    lam_z / sigma, 4.0 / 9.0, 2.0 / 3.0);
    }

    std::printf("\n== T5: shadow of a sphere of radius R1 at distance r ==\n");
    {
        for (double ratio : {1.0, 1.5, 2.0, 5.0, 10.0, 100.0}) {
            const double x = 1.0 / (ratio * ratio);  // (R1/r)^2
            const double cosA = std::sqrt(1.0 - x);
            const GL cap = on_interval(g1, cosA, 1.0);
            const double proj = sphere_integral(cap, nphi, [](double mu, double, double, double) { return mu; });
            const double unw = sphere_integral(cap, nphi, [](double, double, double, double) { return 1.0; });
            check("T5", "projected cap int mu dOmega vs pi R1^2/r^2", proj, kPi * x, 1e-12);
            check("T5", "unweighted cap vs 2 pi (1 - sqrt(1 - R1^2/r^2))", unw, 2.0 * kPi * (1.0 - cosA), 1e-12);
            std::printf("       r/R1 = %6.1f  unweighted / projected = %.9f\n", ratio, unw / proj);
        }
    }

    std::printf("\n== T6: engine agreement (sdt::laws::law_III) ==\n");
    {
        namespace l3 = sdt::laws::law_III;
        for (double ratio : {1.0, 1.5, 2.0, 5.0, 10.0, 100.0}) {
            const double R = 1.0, r = ratio;
            const double x = (R / r) * (R / r);
            const double cosA = std::sqrt(1.0 - x);
            check("T6", "solid_angle_occluded(R, r) vs pi R^2/r^2", l3::solid_angle_occluded(R, r), kPi * x, 1e-12);
            check("T6", "solid_angle_cap(R, r) vs 2 pi (1 - sqrt(1 - x))", l3::solid_angle_cap(R, r),
                  2.0 * kPi * (1.0 - cosA), 1e-12);
            check("T6", "cap_over_projected(R, r) vs 2(1 - sqrt(1 - x))/x", l3::cap_over_projected(R, r),
                  2.0 * (1.0 - cosA) / x, 1e-12);
        }
        const double R1 = 3.0, R2 = 5.0, r = 7.0;
        check("T6", "F_occlusion / P_eff vs (pi/4) R1^2 R2^2 / r^2", l3::F_occlusion(R1, R2, r) / l3::P_eff,
              (kPi / 4.0) * R1 * R1 * R2 * R2 / (r * r), 1e-12);
    }

    std::printf("\n%s: %d failure(s)\n", failures == 0 ? "ALL CRITERIA MET" : "CRITERIA NOT MET", failures);
    return failures == 0 ? 0 : 1;
}
