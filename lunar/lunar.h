#ifndef LUNAR_H
#define LUNAR_H

#include <string>
#include <vector>
#include <array>

#include "lunar_ob.h"

struct OB_LUN
{
	int w0;			// 本月第一天的星期
	int y;		 	// 公历年份
	int m;		 	// 公历月分
	int d0;			// 月首的J2000.0起算的儒略日数
	int dn;			// 本月的天数
	std::string nianhao;  // 年号纪年信息
	OB_DAY day[31];
};

void init_ob();
OB_LUN yueLiCalc(int By, int Bm);
std::string nianLiSTR(int y);

#endif