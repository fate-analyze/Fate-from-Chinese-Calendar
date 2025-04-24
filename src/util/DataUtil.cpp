// ===============================
// Copyright (c) 2025 fate-analyze
// File: DataUtil.cpp
// Updated: 2025/4/18
// Author: xum
// ===============================
#include "DataUtil.h"
#include <cmath>
#include <format>
#include <iomanip>
#include <numbers>
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
    int s = intFloor(date.sec_ + 0.5);
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
    bool negative = radian < 0;
    radian = std::abs(radian);

    // 单位转换
    double converted = (format == ANGLE_FORMAT::TIME) ? (radian * 12 / std::numbers::pi) : (radian * 180.0 / std::numbers::pi);

    // 分解各个分量
    int a = std::floor(converted);
    converted = (converted - a) * 60;
    int b = std::floor(converted);
    converted = (converted - b) * 60;
    int c = std::floor(converted);
    double remainder = converted - c;

    // 处理进位
    const int dec_num = std::pow(10, precision);
    int decimal = std::round(remainder * dec_num);
    if (decimal >= dec_num) {
        decimal -= dec_num;
        if (++c >= 60) {
            c -= 60;
            if (++b >= 60) {
                b -= 60;
                ++a;
            }
        }
    }

    // 构建字符串
    const auto &units = ANGLE_FORMAT_STR[static_cast<int>(format)];
    auto fmt_str = precision > 0 ? std::format("{:3d}{}{:02d}{}{:02d}.{:0{}d}{}", a, units[0], b, units[1], c, decimal, precision, units[2])
                                 : std::format("{:3d}{}{:02d}{}{:02d}{}", a, units[0], b, units[1], c, units[2]);

    // 替换空格为符号占位符
    const auto pos = fmt_str.find_first_not_of(' ');
    if (!negative) {
        return fmt_str.substr(pos);
    }

    if (pos == std::string::npos) {
        fmt_str.insert(0, "-");
    } else {
        fmt_str.replace(0, pos - 0, "-");
    }
    return fmt_str;
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
