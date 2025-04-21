// ===============================
// Copyright (c) 2025 fate-analyze
// File: DataUtil.h
// Updated: 2025/4/18
// Author: xum
// Description: 数据类型相关工具类
// ===============================
#ifndef DATAUTIL_H
#define DATAUTIL_H

#include <cmath>
#include <string>
#include "TimeGeo.h"

namespace sxwnl {

class DataUtil {
public:
    static int intFloor(const double v) { return static_cast<int>(std::floor(v)); }
    static std::string date2str(Date date);
    static std::string jd2str(const double jd) { return date2str(jd2Date(jd)); }
    static std::string jd2hour(const double jd)
    {
        auto date_str = jd2str(jd);
        return date_str.substr(date_str.length() - 8, 8);  // 提取时分秒
    }

    /**
     * @param radian 弧度
     * @param flag true采用18h 29m 44.52s格式；false采用23°59" 48.23"格式
     * @param precision 小数保留位数
     */
    static std::string rad2str(double radian, bool flag, int precision = 2);
};

}  // namespace sxwnl

#endif  //DATAUTIL_H
