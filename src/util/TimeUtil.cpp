// ===============================
// Copyright (c) 2025 fate-analyze
// File: TimeUtil.cpp
// Updated: 2025/4/18
// Author: xum
// ===============================
#include "TimeUtil.h"
#include <erfa.h>
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
    Date date {0};
    double fd;
    eraJd2cal(jd, 0.0, &date.year_, &date.month_, &date.day_, &fd);

    char sign;
    int ihmsf[4];  // [时, 分, 秒, 毫秒]
    eraD2tf(3, fd, &sign, ihmsf);
    date.hour_ = ihmsf[0];
    date.min_ = ihmsf[1];
    date.sec_ = ihmsf[2];

    return date;
}