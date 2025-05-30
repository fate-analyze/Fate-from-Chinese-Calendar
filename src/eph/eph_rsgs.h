#ifndef EPH_RSGS_H
#define EPH_RSGS_H

#include <array>
#include <string>
#include <vector>

namespace sxwnl {
struct _VXY {
    double vx;
    double vy;
    double Vx;
    double Vy;
    double V;
};

struct _RSM {
    double r1;
    double r2;
    double ar2;
    double sf;
};

struct _FEATURE {
    double jdSuo;
    double dT;
    double ds;
    double vx;
    double vy;
    double ax;
    double ay;
    double v;
    double k;

    double t0;
    double jd;
    double xc;
    double yc;
    double zc;
    double D;
    double d;
    std::array<double, 3> I;
    std::array<double, 3> gk1;
    std::array<double, 3> gk2;
    std::array<double, 3> gk3;
    std::array<double, 3> gk4;
    std::array<double, 3> gk5;
    std::string lx;

    double zxJ;
    double zxW;
    double dw;
    double sf;
    double tt;
    std::array<double, 3> Sdp;

    std::vector<double> p1;
    std::vector<double> p2;
    std::vector<double> p3;
    std::vector<double> p4;
    std::vector<double> q1;
    std::vector<double> q2;
    std::vector<double> q3;
    std::vector<double> q4;
    std::vector<double> L0;
    std::vector<double> L1;
    std::vector<double> L2;
    std::vector<double> L3;
    std::vector<double> L4;
    std::vector<double> L5;
    std::vector<double> L6;
};

struct _JIEX2 {
    std::vector<double> p1;
    std::vector<double> p2;
    std::vector<double> p3;
};

struct _FLAG {
    int f;
    int f2;
};

class RS_GS {
public:
    static double Zjd;
    static void init(double jd, int n);
    static _FEATURE feature(double jd);
    static std::string jieX3(double jd);
    static std::array<double, 3> sun(double jd)
    {
        return chazhi(jd, 0);
    }  //传回值可能超过360度
    static std::array<double, 3> moon(double jd)
    {
        return chazhi(jd, 1);
    }
    static std::array<double, 3> bse(double jd)
    {
        return chazhi(jd, 2);
    }

private:
    static std::vector<double> Zs;
    static double Zdt;
    static double dT;
    static double tanf1;
    static double tanf2;
    static double srad;
    static double bba;
    static double bhc;
    static double dyj;

    static std::array<double, 3> chazhi(double jd, int xt);
    static std::array<double, 3> cd2bse(const std::array<double, 3> &z, const std::array<double, 3> &I);
    static std::array<double, 3> bse2cd(const std::array<double, 3> &z, const std::array<double, 3> &I);
    static std::array<double, 3> bse2db(const std::array<double, 3> &z, const std::array<double, 3> &I, bool f);
    static std::array<double, 3> bseXY2db(double x, double y, const std::array<double, 3> &I, bool f);
    static std::array<double, 3> bseM(double jd);
    static _VXY Vxy(double x, double y, double s, double vx, double vy);
    static _RSM rSM(double mR);
    static std::array<double, 3> qrd(double jd, double dx, double dy, bool fs);
    static void push(const std::array<double, 3> &z, std::vector<double> &p);
    static std::array<double, 4> nanbei(const std::array<double, 3> &M, double vx0, double vy0, double h, double r,
                                        const std::array<double, 3> &I);
    static bool mDian(const std::array<double, 3> &M, double vx0, double vy0, bool AB, double r, const std::array<double, 3> &I, std::vector<double> &A);
};
}  // namespace sxwnl

#endif