#include "tool.h"
#include <cstdlib>
#include <string>
#include "math_patch.h"
#include "mylib/mystl/my_string.h"
#include "util/DataUtil.h"

namespace sxwnl {
//实现字符替换
void string_replace(std::string &strBig, const std::string &strsrc, const std::string &strdst)
{
    std::string::size_type pos = 0;
    const auto src_len = strsrc.size();
    const auto dst_len = strdst.size();

    while ((pos = strBig.find(strsrc, pos)) != std::string::npos) {
        strBig.replace(pos, src_len, strdst);
        pos += dst_len;
    }
}

//将弧度转为字串,精确到分
std::string rad2str2(double d)
{
    //输出格式示例: -23°59"
    std::string s = "+", w1 = "°", w2 = "\'", w3 = "\"";
    if (d < 0)
        d = -d, s = "-";
    d *= 180 / M_PI;
    int a = floor(d);
    int b = floor((d - a) * 60 + 0.5);
    if (b >= 60)
        b -= 60, a++;
    std::string A = "   " + std::to_string(a), B = "0" + std::to_string(b);
    s += A.substr(A.length() - 3, 3) + w1;
    s += B.substr(B.length() - 2, 2) + w2;
    return s;
}

//秒转为分秒,fx为小数点位数,fs为1转为"分秒"格式否则转为"角度分秒"格式
std::string m2fm(double v, int fx, int fs)
{
    std::string gn;
    if (v < 0)
        v = -v, gn = "-";
    int f = floor(v / 60);
    double m = v - f * 60;
    if (!fs)
        return gn + std::to_string(f) + "\'" + to_str(m, fx) + "\"";
    if (fs == 1)
        return gn + std::to_string(f) + "分" + to_str(m, fx) + "秒";
    if (fs == 2)
        return gn + std::to_string(f) + "m" + to_str(m, fx) + "s";
    else
        return "error";
}

std::string fill_str(std::string s, int n, const std::string &c)
{
    int len = s.length();
    for (int i = 0; i < n - len; i++) {
        s = c + s;
    }
    return s;
}
}  // namespace sxwnl