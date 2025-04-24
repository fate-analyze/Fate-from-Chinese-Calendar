#ifndef API_BAZI_H
#define API_BAZI_H

#include <string>
#include "TimeGeo.h"

namespace sxwnl {

struct Bazi {
    std::string bz_jn {};   // 年干支
    std::string bz_jy {};   // 月干支
    std::string bz_jr {};   // 日干支
    std::string bz_js {};   // 时干支
    std::string bz_JS {};   // 一天内的12个时干支
    std::string bz_zty {};  // 真太阳时，如19:30:30
};

struct GeoCoord {
    double lng_;
    double lat_;
};

constexpr GeoCoord BJ_COORD = {116 + 23 / 60.0, 39.9};

/**
 * 根据日期、地理经度计算八字
 * @param[in] date 日期
 * @param[in] lng 经度
 * @return 八字
 */
Bazi jb2Bazi(const Date &date, double lng = BJ_COORD.lng_);

}  // namespace sxwnl

#endif  //API_BAZI_H
