// ===============================
// Copyright (c) 2025 fate-analyze
// File: DataUtil.cpp
// Updated: 2025/4/18
// Author: xum
// ===============================
#include "DataUtil.h"
#include <erfa.h>
#include <cmath>
#include <format>
#include <iomanip>
#include <sstream>
#include "util/TimeUtil.h"

using namespace sxwnl;

constexpr std::string_view ANGLE_FORMAT_STR[3][3] = {
    {"°",  "'",  "\""},
    {"度", "分", "秒"},
    {"h",  "m",  "s" },
};

std::string DataUtil::date2str(Date date)
{
    int s = intFloor(date.sec_ + (date.msec_ / 1000.0) + 0.5);
    int m = date.min_;
    int h = date.hour_;

    if (s >= 60) {
        s -= 60;
        m += 1;
    }
    if (m >= 60) {
        m -= 60;
        h += 1;
    }

    return std::format("{:5}-{:02}-{:02} {:02}:{:02}:{:02}", date.year_, date.month_, date.day_, h, m, s);
}

std::string DataUtil::rad2str(double radian, ANGLE_FORMAT format, int precision)
{
    char sign;
    int result[4];
    if (format == ANGLE_FORMAT::TIME) {
        eraA2tf(precision, radian, &sign, result);
    } else {
        eraA2af(precision, radian, &sign, result);
    }

    const auto &units = ANGLE_FORMAT_STR[static_cast<int>(format)];
    std::stringstream ss;
    ss << std::setfill('0');
    ss << sign << result[0] << units[0] << std::setw(2) << result[1] << units[1] << std::setw(2) << result[2];
    if (precision > 0) {
        ss << "." << std::setw(precision) << result[3] << units[2];
    } else {
        ss << units[2];
    }

    return ss.str();
}

std::string DataUtil::s2min(double sec, int precision, ANGLE_FORMAT format)
{
    std::stringstream ss;
    if (sec < 0) {
        sec = -sec;
        ss << '-';
    }

    const auto &units = ANGLE_FORMAT_STR[static_cast<int>(format)];
    int min = intFloor(sec / 60);
    double seconds = sec - min * 60;

    ss << min << units[1] << std::fixed << std::setprecision(precision) << seconds << units[2];
    return ss.str();
}

void DataUtil::strReplace(std::string &str, const std::string &from, const std::string &to)
{
    std::string::size_type pos = 0;
    while ((pos = str.find(from, pos)) != std::string::npos) {
        str.replace(pos, from.length(), to);
        pos += to.length();
    }
}

std::string DataUtil::paddingStrHead(std::string_view src, char pad, int padNum)
{
    std::stringstream ss;
    for (decltype(padNum) i = 0; i < padNum; ++i) {
        ss << pad;
    }

    ss << src;
    return ss.str();
}
