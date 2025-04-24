// ===============================
// Copyright (c) 2025 fate-analyze
// File: TimeUtil.cpp
// Updated: 2025/4/18
// Author: xum
// ===============================
#include "TimeUtil.h"
#include <erfa.h>
#include "Error.h"
#include "util/DataUtil.h"

using namespace sxwnl;

double TimeUtil::date2Jd(const Date &date)
{
    double fd1, fd2;
    double sec = date.sec_ + date.msec_ / 1000.0;

    int ret = eraDtf2d("UTC", date.year_, date.month_, date.day_, date.hour_, date.min_, sec, &fd1, &fd2);
    if (ret != 0) {
        throw SxwnlExcept(ErrorCode::THIRD_PARTY_ERROR, THIRD_LIB_ERFA, " has error ", ret);
    }

    return fd1 + fd2;
}

Date TimeUtil::jd2Date(double jd)
{
    Date date {0};
    double fd;
    double jd_main = std::floor(jd);
    int ret = eraJd2cal(jd_main, jd - jd_main, &date.year_, &date.month_, &date.day_, &fd);
    if (ret != 0) {
        throw SxwnlExcept(ErrorCode::THIRD_PARTY_ERROR, THIRD_LIB_ERFA, " has error ", ret);
    }

    char sign;
    int hmsf[4];
    eraD2tf(3, fd, &sign, hmsf);
    date.hour_ = hmsf[0];
    date.min_ = hmsf[1];
    date.sec_ = hmsf[2];
    date.msec_ = hmsf[3];
    return date;
}