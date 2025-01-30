#include "tool.h"
#include <cstdlib>
#include <string>
#include "math_patch.h"
#include "mylib/mystl/my_string.h"

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

//提取jd中的时间(去除日期)
std::string timeStr(double jd)
{
    jd += 0.5;
    jd = (jd - int2(jd));
    int s = int2(jd * 86400 + 0.5);
    int h = int2(s / 3600.0);
    s -= h * 3600;
    int m = int2(s / 60.0);
    s -= m * 60;
    std::string H = "0" + std::to_string(h);
    std::string M = "0" + std::to_string(m);
    std::string S = "0" + std::to_string(s);
    return H.substr(H.length() - 2, 2) + ":" + M.substr(M.length() - 2, 2) + ":" + S.substr(S.length() - 2, 2);
}

//===============角度格式化==================
std::string rad2strE(double d, bool flag, int ext)
{
    //将弧度转为字串,ext为小数保留位数
    //flag=0输出格式示例: -23°59" 48.23"
    //flag=1输出格式示例:  18h 29m 44.52s
    std::string s = " ", w1 = "°", w2 = "\'", w3 = "\"";
    if (d < 0)
        d = -d, s = "-";
    if (flag) {
        d *= 12 / M_PI;
        w1 = "h", w2 = "m", w3 = "s";
    } else
        d *= 180 / M_PI;
    int a = floor(d);
    d = (d - a) * 60;
    int b = floor(d);
    d = (d - b) * 60;
    int c = floor(d);

    double Q = pow(10, ext);

    d = floor((d - c) * Q + 0.5);
    if (d >= Q)
        d -= Q, c++;
    if (c >= 60)
        c -= 60, b++;
    if (b >= 60)
        b -= 60, a++;

    std::string A, B, C, D;
    A = "   " + std::to_string(a);
    B = "0" + std::to_string(b);
    C = "0" + std::to_string(c);
    D = "00000" + std::to_string((int)d);
    s += A.substr(A.length() - 3, 3) + w1;
    s += B.substr(B.length() - 2, 2) + w2;
    s += C.substr(C.length() - 2, 2);
    if (ext)
        s += "." + D.substr(D.length() - ext, ext) + w3;
    return s;
}

//将弧度转为字串,保留2位
std::string rad2str(double d, bool tim)
{
    return rad2strE(d, tim, 2);
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

double date2Jd(const Date &date)
{
    double y = date.year_, m = date.month_, n = 0;  //取出年月
    if (m <= 2) {
        m += 12;
        y--;
    }

    //判断是否为格里高利历日1582*372+10*31+15
    if (date.year_ * 372 + date.month_ * 31 + date.day_ >= 588829) {
        //加百年闰
        n = static_cast<int>(y / 100);
        n = 2 - n + static_cast<int>(n / 4);
    }

    n += static_cast<int>(365.25 * (y + 4716) + 0.01);  //加上年引起的偏移日数
    n += static_cast<int>(30.6 * (m + 1)) + date.day_;  //加上月引起的偏移日数及日偏移数
    n += ((date.sec_ / 60.0 + date.min_) / 60.0 + date.hour_) / 24.0 - 1524.5;
    return n;
}

Date jd2Date(double jd)
{
    Date r = {0};
    int D = int2(jd + 0.5), c;
    double F = jd + 0.5 - D;  //取得日数的整数部份A及小数部分F
    if (D >= 2299161)
        c = int2((D - 1867216.25) / 36524.25), D += 1 + c - int2(c / 4.0);
    D += 1524;
    r.year_ = int2((D - 122.1) / 365.25);  //年数
    D -= int2(365.25 * r.year_);
    r.month_ = int2(D / 30.601);  //月数
    D -= int2(30.601 * r.month_);
    r.day_ = D;  //日数
    if (r.month_ > 13)
        r.month_ -= 13, r.year_ -= 4715;
    else
        r.month_ -= 1, r.year_ -= 4716;

    //日的小数转为时分秒
    F *= 24.0;
    r.hour_ = int2(F);
    F -= r.hour_;
    F *= 60.0;
    r.min_ = int2(F);
    F -= r.min_;
    F *= 60.0;
    r.sec_ = F;
    return r;
}

// 日期对象转为字符串
std::string DD2str(Date r)
{
    std::string Y = "     " + std::to_string(r.year_), M = "0" + std::to_string(r.month_), D = "0" + std::to_string(r.day_);

    int h = r.hour_, m = r.min_, s = int2(r.sec_ + .5);
    if (s >= 60)
        s -= 60, m++;
    if (m >= 60)
        m -= 60, h++;

    std::string _h, _m, _s;
    _h = "0" + std::to_string(h);
    _m = "0" + std::to_string(m);
    _s = "0" + std::to_string(s);
    Y = Y.substr(Y.length() - 5, 5);
    M = M.substr(M.length() - 2, 2);
    D = D.substr(D.length() - 2, 2);
    _h = _h.substr(_h.length() - 2, 2);
    _m = _m.substr(_m.length() - 2, 2);
    _s = _s.substr(_s.length() - 2, 2);

    return Y + "-" + M + "-" + D + " " + _h + ":" + _m + ":" + _s;
}

// JD转为字符串
std::string JD2str(double jd)
{
    auto r = jd2Date(jd);
    return DD2str(r);
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