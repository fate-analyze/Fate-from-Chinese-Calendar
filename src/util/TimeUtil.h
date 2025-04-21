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

class TimeUtil {
public:
    static double date2Jd(const Date &date);
    /**
     * @brief 儒略日转公历
     * @ref 算法详见doc/儒略日转公历时间.pdf
     */
    static Date jd2Date(double jd);
};
}  // namespace sxwnl

#endif  //TIMEUTIL_H
