// ===============================
// Copyright (c) 2025 fate-analyze
// File: TimeUtil.cpp
// Updated: 2025/4/18
// Author: xum
// ===============================
#include "TimeUtil.h"
#include "util/DataUtil.h"

using namespace sxwnl;

double TimeUtil::date2Jd(const Date &date)
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

Date TimeUtil::jd2Date(double jd)
{
    jd += 0.5;
    int Z = static_cast<int>(jd);
    double F = jd - Z;

    int A;
    if (Z >= 2299161) {
        A = DataUtil::intFloor((Z - 1867216.25) / 36524.25);
        A = Z + 1 + A - DataUtil::intFloor(A / 4);
    } else {
        A = Z;
    }

    int B = A + 1524;
    double C = DataUtil::intFloor((B - 122.1) / 365.25);
    double D = DataUtil::intFloor(365.25 * C);
    int days = B - D + DataUtil::intFloor((B - D) / 30.6001);

    Date result {};
    result.month_ = days < 14 ? days - 1 : days - 13;
    result.year_ = static_cast<int>(result.month_ > 2 ? C - 4716 : C - 4715);
    result.day_ = days - static_cast<int>(30.6001 * (result.month_ - 1));

    // 处理时间部分
    F *= 24.0;
    result.hour_ = static_cast<int>(F);
    F -= result.hour_;
    F *= 60.0;
    result.min_ = static_cast<int>(F);
    F -= result.min_;
    result.sec_ = static_cast<int>(std::round(F * 60.0));
    return result;
}