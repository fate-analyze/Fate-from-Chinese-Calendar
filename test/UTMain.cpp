// ===============================
// Copyright (c) 2025 fate-analyze
// File: UTMain.cpp
// Updated: 2025/4/21
// Author: xum
// ===============================
#include "UTMain.h"

using namespace sxwnl;

void UTMain::SetUp() {}

void UTMain::TearDown() {}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}