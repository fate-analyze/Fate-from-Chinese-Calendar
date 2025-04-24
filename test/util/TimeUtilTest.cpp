// ===============================
// Copyright (c) 2025 fate-analyze
// File: TimeUtilTest.cpp
// Updated: 2025/4/21
// Author: xum
// ===============================
#include "TimeGeo.h"
#include "UTMain.h"

using namespace sxwnl;

TEST_F(UTMain, date2Jd)
{
    Date input {1970, 1, 1, 0, 0, 0};
    EXPECT_EQ(date2Jd(input), 2440587.5);
    input = {1997, 1, 1, 0, 0, 0, 500};
    EXPECT_EQ(date2Jd(input), 2450449.5000057872);

    input = {2000, 1, 1, 0, 0, 0};
    EXPECT_EQ(date2Jd(input), 2451544.5);
    input = {2000, 1, 1, 12, 0, 0};
    EXPECT_EQ(date2Jd(input), 2451545.0);
    input = {2000, 1, 1, 18, 0, 0};
    EXPECT_EQ(date2Jd(input), 2451545.25);

    input = {2012, 1, 23, 6, 25, 7, 100};
    EXPECT_EQ(date2Jd(input), 2455949.767443287);
    input = {2012, 2, 29, 0, 0, 0};
    EXPECT_EQ(date2Jd(input), 2455986.5);
    input = {2012, 5, 1, 0, 0, 0};
    EXPECT_EQ(date2Jd(input), 2456048.5);
}

TEST_F(UTMain, jd2Date)
{
    Date exp {1970, 1, 1, 0, 0, 0};
    EXPECT_EQ(jd2Date(2440587.5), exp);
    exp = {1997, 1, 1, 0, 0, 0, 500};
    EXPECT_EQ(jd2Date(2450449.5000057872), exp);

    exp = {2000, 1, 1, 0, 0, 0};
    EXPECT_EQ(jd2Date(2451544.5), exp);
    exp = {2000, 1, 1, 12, 0, 0};
    EXPECT_EQ(jd2Date(2451545.0), exp);
    exp = {2000, 1, 1, 18, 0, 0};
    EXPECT_EQ(jd2Date(2451545.25), exp);

    exp = {2012, 1, 23, 6, 25, 7, 100};
    EXPECT_EQ(jd2Date(2455949.767443287), exp);
    exp = {2012, 2, 29, 0, 0, 0};
    EXPECT_EQ(jd2Date(2455986.5), exp);
    exp = {2012, 5, 1, 0, 0, 0};
    EXPECT_EQ(jd2Date(2456048.5), exp);
}