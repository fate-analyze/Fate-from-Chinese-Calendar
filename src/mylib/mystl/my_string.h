#ifndef MY_STRING_H
#define MY_STRING_H

#include <cstring>
#include <string>
#include "dtoa.h"
#include "itoa.h"

namespace sxwnl {
// 萃取float类型
template<typename T>
struct is_float {
    const static bool value = false;
};
template<>
struct is_float<long double> {
    const static bool value = true;
};
template<>
struct is_float<double> {
    const static bool value = true;
};
template<>
struct is_float<float> {
    const static bool value = true;
};

// length 总长度，是否右对齐
template<class T>
std::string to_str(T value, int precision = 4, int length = 0, bool right_align = false)
{
    // digits10 returns floor value, so add 1 for remainder, 1 for - and 1 for null terminator
    char str[32] = {};

    if (is_float<T>::value) {  // 浮点数
        dtoa_milo2(value, str, precision, true);
    } else {  // 整数
        jeaiii::to_text_from_integer(str, value);
    }

    char fill[64] = "";
    size_t s_len = strlen(str);
    if (length > s_len) {
        size_t len = length - s_len;
        for (size_t i = 0; i < len; i++) {
            fill[i] = ' ';
        }
    }
    return right_align ? (std::string(fill) + std::string(str)) : (std::string(str) + std::string(fill));
}
}  // namespace sxwnl

#endif  // !MY_STRING_H