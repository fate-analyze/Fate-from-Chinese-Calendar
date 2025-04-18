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
    Date r = {0};
    int D = DataUtil::intFloor(jd + 0.5), c;
    double F = jd + 0.5 - D;  //取得日数的整数部份A及小数部分F
    if (D >= 2299161)
        c = DataUtil::intFloor((D - 1867216.25) / 36524.25), D += 1 + c - DataUtil::intFloor(c / 4.0);
    D += 1524;
    r.year_ = DataUtil::intFloor((D - 122.1) / 365.25);  //年数
    D -= DataUtil::intFloor(365.25 * r.year_);
    r.month_ = DataUtil::intFloor(D / 30.601);  //月数
    D -= DataUtil::intFloor(30.601 * r.month_);
    r.day_ = D;  //日数
    if (r.month_ > 13)
        r.month_ -= 13, r.year_ -= 4715;
    else
        r.month_ -= 1, r.year_ -= 4716;

    //日的小数转为时分秒
    F *= 24.0;
    r.hour_ = DataUtil::intFloor(F);
    F -= r.hour_;
    F *= 60.0;
    r.min_ = DataUtil::intFloor(F);
    F -= r.min_;
    F *= 60.0;
    r.sec_ = F;
    return r;
}