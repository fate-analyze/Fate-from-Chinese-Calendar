#ifndef TOOL_H
#define TOOL_H

#include <cstdlib>
#include <string>
#include "mylib/math_patch.h"
#include "TimeGeo.h"

#define A2R(x) ((x) / 180 * M_PI)

namespace sxwnl {

void string_replace(std::string &strBig, const std::string &strsrc, const std::string &strdst);
std::string rad2str2(double d);
std::string m2fm(double v, int fx, int fs);
std::string fill_str(std::string s, int n, const std::string &c);
}  // namespace sxwnl

#endif