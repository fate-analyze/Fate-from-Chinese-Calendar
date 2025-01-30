#ifndef TOOL_H
#define TOOL_H

#include <cstdlib>
#include <string>
#include "mylib/math_patch.h"
#include "time_geo.h"

#define A2R(x) ((x) / 180 * M_PI)

namespace sxwnl {
inline int int2(double v)
{
    return (int)floor(v);
};

void string_replace(std::string &strBig, const std::string &strsrc, const std::string &strdst);
std::string timeStr(double jd);
std::string rad2strE(double d, bool tim, int ext);
std::string rad2str(double d, bool tim);
std::string rad2str2(double d);
std::string m2fm(double v, int fx, int fs);
std::string DD2str(Date r);
std::string JD2str(double jd);
std::string fill_str(std::string s, int n, const std::string &c);
}  // namespace sxwnl

#endif