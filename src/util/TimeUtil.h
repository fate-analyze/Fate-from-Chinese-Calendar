// ===============================
// Copyright (c) 2025 $ORGANIZATION_NAME$
// File: TimeUtil.h
// Updated: 2025/4/18
// Author: xum
// Description: 时间相关工具类
// ===============================
#ifndef TIMEUTIL_H
#define TIMEUTIL_H

#include "TimeGeo.h"

namespace sxwnl {

/**
 * 儒略历（Julian Calendar）向格里高利历（Gregorian Calendar）的转换点
 * 1. 儒略日 2299160 → 儒略历 1582年10月4日
 * 2. 儒略日 2299161 → 格里高利历 1582年10月15日
 */
constexpr int JULIAN_2_GREGORIAN = 2299161;



class TimeUtil {
public:
    static double date2Jd(const Date &date);
    /**
     * @brief 算法详见doc/儒略日转公历时间.pdf
     */
    static Date jd2Date(double jd);
};
}  // namespace sxwnl

#endif  //TIMEUTIL_H
