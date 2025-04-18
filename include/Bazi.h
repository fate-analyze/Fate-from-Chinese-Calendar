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

/**
 * 根据日期、地理经度计算八字
 * @param date 日期
 * @param lng 经度，默认为北京所在经度
 * @return 八字
 */
Bazi jb2Bazi(const Date &date, double lng = (116 + 23 / 60.0));

}  // namespace sxwnl

#endif  //API_BAZI_H
