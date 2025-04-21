// ===============================
// Copyright (c) 2025 fate-analyze
// File: DataUtil.cpp
// Updated: 2025/4/18
// Author: xum
// ===============================
#include "DataUtil.h"
#include <cmath>
#include <format>
#include <numbers>
#include "util/TimeUtil.h"

using namespace sxwnl;

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

std::string DataUtil::rad2str(double radian, bool flag, int precision)
{
    bool negative = radian < 0;
    radian = std::abs(radian);

    // 单位转换
    double converted = flag ? (radian * 12 / std::numbers::pi_v<double>) : (radian * 180.0 / std::numbers::pi_v<double>);

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

    // 格式符号和单位
    const auto [u1, u2, u3] = flag ? std::make_tuple("h", "m", "s") : std::make_tuple("°", "'", "\"");

    // 构建字符串
    auto fmt_str = precision > 0 ? std::format("{:3d}{}{:02d}{}{:02d}.{:0{}d}{}", a, u1, b, u2, c, decimal, precision, u3)
                                 : std::format("{:3d}{}{:02d}{}{:02d}{}", a, u1, b, u2, c, u3);

    // 替换空格为符号占位符
    auto pos = fmt_str.find_first_not_of(" ");
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