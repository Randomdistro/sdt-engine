// Build: g++ -std=c++20 -Wall -Wextra -pedantic -IEngine/include \
//   Engine/tests/om_bohr_spation_geometry_test.cpp -o /tmp/sdt_geometry_test
// Run: /tmp/sdt_geometry_test
#include <sdt/spation_geometry.hpp>
#include <sdt/om_atomic.hpp>
#include <cassert>
#include <cmath>
#include <numbers>

static bool close(double got, double expected, double rel=1e-12) {
    return std::abs(got-expected) <= rel * std::max(std::abs(expected),1e-300);
}
int main() {
    namespace s = sdt::geometry::spation;
    namespace a = sdt::geometry::om_atomic;
    constexpr double c=299792458.0;
    constexpr double h=6.62607015e-34, hbar=h/(2.0*std::numbers::pi);
    constexpr double mu=9.1093837015e-31; // infinite-nucleus baseline
    constexpr double alpha=7.2973525693e-3; // empirical normalization only
    constexpr double om=alpha*hbar/(mu*c);
    constexpr double pitch=1.616255e-35; // test geometric conventions only
    constexpr s::DiameterHypothesis spation{pitch};
    static_assert(spation.radius_m()==pitch/2);
    static_assert(spation.contact_pitch_m()==pitch);
    static_assert(s::diameter_from_radius(spation.radius_m())==pitch);
    assert(close(spation.projected_area_m2()/(pitch*pitch), std::numbers::pi/4));
    assert(close(spation.physical_volume_m3()/(pitch*pitch*pitch),std::numbers::pi/6));
    constexpr double action=hbar/mu;
    constexpr double a0=hbar/(mu*alpha*c);
    static_assert(a::rung_radius(om,action,c,1)>0);
    assert(close(a::rung_radius(om,action,c,1),a0));
    assert(close(a::rung_radius(om,action,c,2),4*a0));
    assert(close(a::rung_depth(om,action,c,2),a::rung_depth(om,action,c,1)/4));
    assert(close(a::beta_from_source(om,action,c),alpha));
    assert(close(a::velocity_ratio(om,a0),1/alpha));
    assert(close(a::far_relay_speed(c,0.1),0.81*c));
    assert(close(a::closure_length(pitch,0.1),0.9*pitch));
    const double Ry=mu*c*alpha*alpha/(2*h);
    assert(close(a::transition_wavenumber_m_inv(om,action,c,mu,h,1,2),0.75*Ry));
    // Independently varying source length must change predicted spectral output.
    assert(!close(a::transition_wavenumber_m_inv(om*1.01,action,c,mu,h,1,2),
                  a::transition_wavenumber_m_inv(om,action,c,mu,h,1,2),1e-5));
    return 0;
}
