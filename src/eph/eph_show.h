#ifndef EPH_SHOW_H
#define EPH_SHOW_H

#include <cstdint>
#include <string>
#include "TimeGeo.h"

/*
日食时间周期定义：
  食年 346.620 eclipse_year
  沙罗 6585.32 saros
  朔望 29.5306 syzygy
*/
#define ECLPSE_YEAR 346.620
#define SAROS 6585.32
#define SYZYGY 29.5306

namespace sxwnl {
std::string rysCalc(Date d, bool is_utc, bool nasa_r);
std::string rs_search(int Y, int M, int n, bool fs);

/**
 * @brief 不同周期下的日食概略推算
 * @param fs 功能选择 1
 * @param jd0 初始儒略日
 * @param step 步长
 */
std::string rs2_calc(uint8_t fs, double jd0, double step = SYZYGY);

/**
 * @brief 打印界线图
 */
std::string rs2_jxb();

/**
 * @brief 升降相关计算
 */
std::string shengjiang(int y, int m, int d);
std::string shengjiang2(int y);
std::string shengjiang3(int y);
}  // namespace sxwnl

#endif