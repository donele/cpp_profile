#include "scm_timeseries.h"
#include <gtest/gtest.h>

class XTimeTest : public ::testing::Test
{
protected:
  void SetUp() override {
    int day = 1;
    int month = 4;
    int year = 2023;
    std::tm tm = { 10, 10, 10, day, month - 1, year - 1900};
    tm.tm_isdst = 1;
    tp = std::chrono::system_clock::from_time_t(std::mktime(&tm));
  }

  TPOINT tp;
};

TEST_F(XTimeTest, TestFromString)
{

  auto us = 123456;
  auto tp1 = tp + std::chrono::microseconds(us);
  auto tstr1 = "2023-04-01 10:10:10.123456";
  auto format = "%Y%m%d %H:%M:%S";
  EXPECT_EQ(str2tp(tstr1,format), TPOINT());

  format = "%Y-%m-%d %H:%M:%S";
  EXPECT_EQ(str2tp(tstr1,format), tp1);

  auto ms = 123;
  auto tp2 = tp + std::chrono::milliseconds(ms);
  auto tstr2 = "2023-04-01 10:10:10.123000";
  EXPECT_EQ(str2tp(tstr2,format), tp2);

  auto tstr3 = "2023-04-01 10:10:10.000000";
  EXPECT_EQ(str2tp(tstr3,format), tp);

}

TEST_F(XTimeTest, TestToString)
{

  auto us = 123456;
  auto tp1 = tp + std::chrono::microseconds(us);
  auto tstr1 = "20230401 10:10:10.123456";
  EXPECT_EQ(tp2str(tp1), tstr1);

  auto ms = 123;
  auto tp2 = tp + std::chrono::milliseconds(ms);
  auto tstr2 = "20230401 10:10:10.123000";
  EXPECT_EQ(tp2str(tp2), tstr2);

  auto tstr3 = "20230401 10:10:10.000000";
  EXPECT_EQ(tp2str(tp), tstr3);

}

