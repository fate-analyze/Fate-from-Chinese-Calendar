// ===============================
// Copyright (c) 2025 fate-analyze
// File: UTMain.h
// Updated: 2025/4/21
// Author: xum
// Description: UT入口
// ===============================
#ifndef UT_MAIN_H
#define UT_MAIN_H

#include <gtest/gtest.h>

namespace sxwnl {

class UTMain : public testing::Test {
public:
  void SetUp() override;
  void TearDown() override;
};

}  // namespace sxwnl

#endif //UT_MAIN_H
