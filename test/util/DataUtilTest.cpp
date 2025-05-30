// ===============================
// Copyright (c) 2025 fate-analyze
// File: TimeUtilTest.cpp
// Updated: 2025/4/21
// Author: xum
// ===============================
#include <numbers>
#include "util/DataUtil.h"
#include "UTMain.h"

using namespace sxwnl;

TEST_F(UTMain, date2str)
{
    Date date {2023, 7, 12, 15, 30, 45, 400};
    EXPECT_EQ(DataUtil::date2str(date), " 2023-07-12 15:30:45");

    date = {2023, 7, 12, 15, 30, 59, 600};
    EXPECT_EQ(DataUtil::date2str(date), " 2023-07-12 15:31:00");

    date = {2023, 7, 12, 15, 59, 59, 600};
    EXPECT_EQ(DataUtil::date2str(date), " 2023-07-12 16:00:00");

    date = {5, 3, 8, 3, 7, 8, 100};
    EXPECT_EQ(DataUtil::date2str(date), "    5-03-08 03:07:08");
}

TEST_F(UTMain, jd2hour)
{
    EXPECT_EQ(DataUtil::jd2hour(2440587.5), "00:00:00");
    EXPECT_EQ(DataUtil::jd2hour(2450449.5000057872), "00:00:01");
    EXPECT_EQ(DataUtil::jd2hour(2455949.767443287), "06:25:07");
}

TEST_F(UTMain, rad2str)
{
    EXPECT_EQ(DataUtil::DataUtil::rad2str(0, ANGLE_FORMAT::STANDARD, 0), "+0°00'00\"");
    EXPECT_EQ(DataUtil::DataUtil::rad2str2(0), "+0°00'");
    EXPECT_EQ(DataUtil::DataUtil::rad2str(std::numbers::pi, ANGLE_FORMAT::STANDARD, 2), "+180°00'00.00\"");
    EXPECT_EQ(DataUtil::DataUtil::rad2str(std::numbers::pi / 2, ANGLE_FORMAT::STANDARD, 2), "+90°00'00.00\"");
    EXPECT_EQ(DataUtil::DataUtil::rad2str(std::numbers::pi / 6, ANGLE_FORMAT::STANDARD, 2), "+30°00'00.00\"");
    EXPECT_EQ(DataUtil::DataUtil::rad2str(-std::numbers::pi / 12, ANGLE_FORMAT::STANDARD, 1), "-15°00'00.0\"");

    EXPECT_EQ(DataUtil::DataUtil::rad2str(0, ANGLE_FORMAT::TIME, 3), "+0h00m00.000s");
    EXPECT_EQ(DataUtil::DataUtil::rad2str(std::numbers::pi / 6, ANGLE_FORMAT::TIME, 2), "+2h00m00.00s");
    EXPECT_EQ(DataUtil::DataUtil::rad2str(-std::numbers::pi / 12, ANGLE_FORMAT::TIME, 1), "-1h00m00.0s");

    EXPECT_EQ(DataUtil::DataUtil::rad2str(1.23456e-4, ANGLE_FORMAT::STANDARD, 0), "+0°00'25\"");
    EXPECT_EQ(DataUtil::DataUtil::rad2str(0.123456, ANGLE_FORMAT::STANDARD, 3), "+7°04'24.628\"");
    EXPECT_EQ(DataUtil::DataUtil::rad2str(2.987654, ANGLE_FORMAT::TIME, 1), "+11h24m43.2s");

    EXPECT_EQ(DataUtil::DataUtil::rad2str(std::numbers::pi / 180.0 * 59.99999 / 60 / 60, ANGLE_FORMAT::STANDARD, 2), "+0°01'00.00\"");
    EXPECT_EQ(DataUtil::DataUtil::rad2str(2 * std::numbers::pi, ANGLE_FORMAT::TIME, 0), "+24h00m00s");
}