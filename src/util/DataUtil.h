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

#define _pi (std::numbers::pi)
#define pi2 (_pi * 2)
#define pi_2 (_pi / 2)
#define J2000 2451545
#define cs_rEar 6378.1366                              //地球赤道半径(千米)
#define cs_rEarA (0.99834 * cs_rEar)                   //平均半径
#define cs_ba 0.99664719                               //地球极赤半径比
#define cs_ba2 (cs_ba * cs_ba)                         //地球极赤半径比的平方
#define cs_AU 1.49597870691e8                          //天文单位长度(千米)
#define cs_sinP (cs_rEar / cs_AU)                      //sin(太阳视差)
#define cs_PI asin(cs_sinP)                            //太阳视差
#define cs_GS 299792.458                               //光速(行米/秒)
#define cs_Agx (cs_AU / cs_GS / 86400.0 / 36525)       //每天文单位的光行时间(儒略世纪)
#define rad (180 * 3600 / _pi)                         //每弧度的角秒数
#define radd (180 / _pi)                               //每弧度的度数
#define cs_k 0.2725076                                 //月亮与地球的半径比(用于半影计算)
#define cs_k2 0.2722810                                //月亮与地球的半径比(用于本影计算)
#define cs_k0 109.1222                                 //太阳与地球的半径比(对应959.64)
#define cs_sMoon (cs_k * cs_rEar * 1.0000036 * rad)    //用于月亮视半径计算
#define cs_sMoon2 (cs_k2 * cs_rEar * 1.0000036 * rad)  //用于月亮视半径计算
#define cs_sSun 959.64                                 //用于太阳视半径计算
#define cs_xxHH_DATA 116, 584, 780, 399, 378, 370, 367, 367

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
