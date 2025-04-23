// ===============================
// Copyright (c) 2025 fate-analyze
// File: TimeGeo.cpp
// Updated: 2025/4/18
// Author: xum
// ===============================
#include "TimeGeo.h"
#include "util/TimeUtil.h"

namespace sxwnl {

double date2Jd(const Date &date)
{
    return TimeUtil::date2Jd(date);
}

Date jd2Date(double jd)
{
    return TimeUtil::jd2Date(jd);
}

}  // namespace sxwnl