#ifndef LUNAR_H
#define LUNAR_H

#include "lunar_ob.h"

namespace sxwnl {
struct OB_LUN {
    int week0_;            // 本月第一天的星期
    int year_;             // 公历年份
    int month_;            // 公历月分
    int day0_;             // 月首的J2000.0起算的儒略日数
    int dayNum_;           // 本月的天数
    std::string nianHao_;  // 年号纪年信息
    OB_DAY day[31];
};

void init_ob();
OB_LUN yueLiCalc(int By, int Bm);
std::string nianLiSTR(int y);
}  // namespace sxwnl

#endif
