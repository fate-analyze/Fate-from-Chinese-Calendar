// ===============================
// Copyright (c) 2025 fate-analyze
// File: TimeGeo.h
// Updated: 2025/4/21
// Author: xum
// Description: 时间地理相关接口
// ===============================
#ifndef API_TIME_H
#define API_TIME_H

#include <cmath>

namespace sxwnl {

struct Date {
    int year_;
    int month_;
    int day_;
    int hour_;
    int min_;
    double sec_;

    bool operator==(const Date &other) const
    {
        return year_ == other.year_ && month_ == other.month_ && day_ == other.day_ && hour_ == other.hour_ && min_ == other.min_
               && std::abs(sec_ - other.sec_) < 1e-3;
    }
};

/**
 * @brief 将公历转为儒略日数
 * @param[in] date 公历
 * @return 儒略日数，是一个连续的日期计数系统，从公元前4713年1月1日中午开始算起
 */
double date2Jd(const Date &date);

/**
 * 将儒略日数转公历
 * @param[in] jd 儒略日
 * @return 公历
 */
Date jd2Date(double jd);

}  // namespace sxwnl

#endif  //API_TIME_H
