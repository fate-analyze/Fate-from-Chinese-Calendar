#ifndef EPH_0_H
#define EPH_0_H

#include <array>

namespace sxwnl {
extern double cs_xxHH[];
double rad2mrad(double v);
double rad2rrad(double v);

std::array<double, 3> llr2xyz(const std::array<double, 3> &JW);
std::array<double, 3> xyz2llr(const std::array<double, 3> &xyz);
std::array<double, 3> llrConv(const std::array<double, 3> &JW, double E);
std::array<double, 3> CD2DP(const std::array<double, 3> &z, double L, double fa, double gst);
double j1_j2(double J1, double W1, double J2, double W2);
std::array<double, 3> h2g(std::array<double, 3> z, std::array<double, 3> a);
double shiChaJ(double gst, double L, double fa, double J, double W);
double hcjj(double t);
double dt_calc(double y);
double dt_T(double t);
std::array<double, 3> CDllr_J2D(double t, const std::array<double, 3> &llr, const char *mx);
std::array<double, 3> CDllr_D2J(double t, const std::array<double, 3> &llr, const char *mx);
std::array<double, 3> HDllr_J2D(double t, const std::array<double, 3> &llr, const char *mx);
std::array<double, 3> HDllr_D2J(double t, const std::array<double, 3> &llr, const char *mx);
double MQC(double h);
double MQC2(double ho);
std::array<double, 3> parallax(std::array<double, 3> z, double H, double fa, double high);
std::array<double, 2> nutation2(double t);
std::array<double, 2> nutation(double t, int zq);
double nutationLon2(double t);
double XL0_calc(int xt, int zn, double t, int n);
std::array<double, 3> pluto_coord(double t);
std::array<double, 3> p_coord(int xt, double t, int n1, int n2, int n3);
std::array<double, 3> e_coord(double t, int n1, int n2, int n3);
double XL1_calc(int zn, double t, int n);
std::array<double, 3> m_coord(double t, int n1, int n2, int n3);
double gxc_sunLon(double t);
double gxc_sunLat(double t);
double gxc_moonLon(double t);
double gxc_moonLat(double t);
double E_Lon(double t, int n);
double M_Lon(double t, int n);
double pGST(double T, double dt);
double pGST2(double jd);
double E_v(double t);
double M_v(double t);
double MS_aLon(double t, int Mn, int Sn);
double S_aLon(double t, int n);
double MS_aLon_t(double W);
double S_aLon_t(double W);
double MS_aLon_t2(double W);
double S_aLon_t2(double W);

std::array<double, 2> moonMinR(double t, bool min);
std::array<double, 2> moonNode(double t, double asc);
std::array<double, 2> earthMinR(double t, bool min);

int suoN(double jd);
double sunShengJ(double jd, double L, double fa, int sj);
double pty_zty(double t);
double pty_zty2(double t);
double moonIll(double t);
double moonRad(double r, double h);
}  // namespace sxwnl

#endif