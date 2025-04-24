// ===============================
// Copyright (c) 2025 fate-analyze
// File: Error.h
// Updated: 2025/4/21
// Author: xum
// Description: 错误码与异常
// ===============================
#ifndef API_ERROR_H
#define API_ERROR_H

#include <sstream>
#include <stdexcept>
#include <string_view>
#include <utility>

namespace sxwnl {

enum ErrorCode : int
{
    ERROR = 0,          // 默认
    LUNAR,              // 农历部分
    THIRD_PARTY_ERROR,  // 来自三方库的错误
};

// 三方库名
constexpr std::string_view THIRD_LIB_ERFA = "erfa";  // https://github.com/liberfa/erfa

class SxwnlExcept final : public std::runtime_error {
public:
    template<typename... Args>
    explicit SxwnlExcept(const ErrorCode errCode, Args &&...args) : std::runtime_error(concat(errCode, std::forward<Args>(args)...))
    {}

private:
    template<typename... Args>
    static std::string concat(const ErrorCode errCode, Args &&...args)
    {
        std::ostringstream oss;
        oss << "Error code[" << errCode << "]   message: ";
        (oss << ... << std::forward<Args>(args));
        return oss.str();
    }
};

}  // namespace sxwnl

#endif  //API_ERROR_H
