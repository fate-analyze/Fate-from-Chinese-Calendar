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

namespace sxwnl {

class DataUtil {
public:
    static int intFloor(const double v) { return static_cast<int>(floor(v)); }
};

}  // namespace sxwnl

#endif  //DATAUTIL_H
