// ===============================
// Copyright (c) 2025 fate-analyze
// File: TimeUtil.cpp
// Updated: 2025/4/18
// Author: xum
// ===============================
#include "TimeUtil.h"
#include "util/DataUtil.h"

using namespace sxwnl;

/**
 * 儒略历（Julian Calendar）向格里高利历（Gregorian Calendar）的转换点
 * 1. 儒略日 2299160 → 儒略历 1582年10月4日
 * 2. 儒略日 2299161 → 格里高利历 1582年10月15日
 */
constexpr int JULIAN_2_GREGORIAN = 2299161;
/**
 * 月平均日，使用4位小数避免月份交界日的异常
 */
constexpr double MONTH_2_DAY = 30.6001;
/**
 * 儒略日的起点是公元前4713年1月1日中午（天文纪年为-4712年），使用4716避免出现负数
 */
constexpr int JULIAN_START = 4716;

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
        n = DataUtil::intFloor(y / 100);
        n = 2 - n + DataUtil::intFloor(n / 4);
    }

    n += DataUtil::intFloor(365.25 * (y + JULIAN_START));        //加上年引起的偏移日数
    n += DataUtil::intFloor(MONTH_2_DAY * (m + 1)) + date.day_;  //加上月引起的偏移日数及日偏移数
    n += ((date.sec_ / 60.0 + date.min_) / 60.0 + date.hour_) / 24.0 - 1524.5;
    return n;
}

Date TimeUtil::jd2Date(double jd)
{
    jd += 0.5;
    int Z = static_cast<int>(jd);
    double F = jd - Z;

    if (Z >= JULIAN_2_GREGORIAN) {
        int a = DataUtil::intFloor((Z - 1867216.25) / 36524.25);
        Z += 1 + a - DataUtil::intFloor(a / 4.0);
    }

    Z += 1524;
    int C = DataUtil::intFloor((Z - 122.1) / 365.25);
    int D = DataUtil::intFloor(365.25 * C);
    int E = DataUtil::intFloor((Z - D) / MONTH_2_DAY);

    Date result {};
    result.month_ = E < 14 ? E - 1 : E - 13;
    result.year_ = result.month_ > 2 ? C - JULIAN_START : C - JULIAN_START + 1;
    result.day_ = Z - D - DataUtil::intFloor(MONTH_2_DAY * E) + F;

    // 处理时间部分
    F *= 24.0;
    result.hour_ = DataUtil::intFloor(F);
    F -= result.hour_;
    F *= 60.0;
    result.min_ = DataUtil::intFloor(F);
    F -= result.min_;
    result.sec_ = F * 60.0;
    return result;
}