import unittest
from datetime import timezone, timedelta
from algo_lib.DateTime import DateTime


class TestDateTime(unittest.TestCase):
    # 测试字段校验逻辑
    def test_validation(self):
        # 月份校验
        with self.assertRaises(ValueError):
            DateTime(month=0)
        with self.assertRaises(ValueError):
            DateTime(month=13)

        # 日期校验
        with self.assertRaises(ValueError):
            DateTime(2023, 2, 29)  # 非闰年2月
        DateTime(2024, 2, 29)  # 闰年2月应该成功

        # 时间校验
        with self.assertRaises(ValueError):
            DateTime(hour=24)
        with self.assertRaises(ValueError):
            DateTime(minute=60)
        with self.assertRaises(ValueError):
            DateTime(second=60)
        with self.assertRaises(ValueError):
            DateTime(millisecond=1000)

    # 测试闰年判断
    def test_leap_year(self):
        self.assertTrue(DateTime._is_leap_year(2000))
        self.assertFalse(DateTime._is_leap_year(1900))
        self.assertTrue(DateTime._is_leap_year(2020))
        self.assertFalse(DateTime._is_leap_year(2021))

    # 测试月份天数计算
    def test_days_in_month(self):
        self.assertEqual(DateTime._days_in_month(2023, 2), 28)
        self.assertEqual(DateTime._days_in_month(2024, 2), 29)
        self.assertEqual(DateTime._days_in_month(2023, 4), 30)
        self.assertEqual(DateTime._days_in_month(2023, 1), 31)

    # 测试日期增减计算
    def test_add_day(self):
        # 普通日期增减
        dt = DateTime(2023, 10, 1)
        self.assertEqual(dt.add_day(1), (2023, 10, 2))
        self.assertEqual(dt.add_day(-1), (2023, 9, 30))

        # 跨年测试
        dt = DateTime(1, 1, 1)
        self.assertEqual(dt.add_day(-1), (0, 12, 31))  # 公元前1年

        # 闰年测试
        dt = DateTime(2024, 2, 28)
        self.assertEqual(dt.add_day(1), (2024, 2, 29))
        self.assertEqual(dt.add_day(2), (2024, 3, 1))

    # 测试时区转换
    def test_astimezone(self):
        # 创建时区对象（unittest需要固定偏移时区）
        tz_utc_plus_8 = timezone(timedelta(hours=8))
        tz_utc_minus_5 = timezone(timedelta(hours=-5))

        # UTC时间转换
        utc_time = DateTime(2023, 10, 1, 12, tz=timezone.utc)
        self.assertEqual(utc_time.astimezone(tz_utc_plus_8).hour, 20)
        self.assertEqual(utc_time.astimezone(tz_utc_minus_5).hour, 7)

        # 跨日转换
        dt = DateTime(2023, 10, 1, 23, tz=tz_utc_plus_8)
        converted = dt.astimezone(timezone.utc)
        self.assertEqual(converted.hour, 15)
        self.assertEqual(converted.day, 1)

    # 测试字符串格式化
    def test_to_str(self):
        # 普通格式
        dt = DateTime(2023, 10, 1, 12, 34, 56, 789)
        self.assertEqual(dt.to_str(), "+02023-10-01T12:34:56.789")

        # 公元前格式
        dt = DateTime(-2023, 1, 1)
        self.assertEqual(dt.to_str(), "-02023-01-01T00:00:00.000")

        # UTC转换格式
        dt = DateTime(2023, 10, 1, 20, tz=timezone(timedelta(hours=8)))
        self.assertEqual(dt.to_str(utc=True), "+02023-10-01T12:00:00.000")

    # 测试边界条件
    def test_edge_cases(self):
        # 闰秒（虽然代码中未处理闰秒）
        DateTime(second=59)

        # 毫秒进位
        dt = DateTime(2023, 10, 1, 23, 59, 59, 999)
        new_dt = dt.add_day(1)
        self.assertEqual(new_dt, (2023, 10, 2))

        # 时区偏移导致日期变化
        tz_p12 = timezone(timedelta(hours=12))
        dt = DateTime(2023, 10, 1, 23, tz=timezone.utc)
        converted = dt.astimezone(tz_p12)
        self.assertEqual(converted.day, 2)
        self.assertEqual(converted.hour, 11)

    def test_BCE_dates(self):
        # 测试公元前日期初始化
        dt = DateTime(-1, 1, 1)  # 公元前1年
        self.assertEqual(dt.year, -1)
        self.assertEqual(dt.to_str(), "-00001-01-01T00:00:00.000")

        # 测试零年（特殊处理）
        dt = DateTime(0, 12, 31)
        self.assertEqual(dt.year, 0)
        self.assertEqual(dt.to_str(), "-00000-12-31T00:00:00.000")

    def test_year_zero_operations(self):
        # 零年日期增减
        dt = DateTime(0, 1, 1)
        self.assertEqual(dt.add_day(1), (0, 1, 2))
        self.assertEqual(dt.add_day(-1), (-1, 12, 31))  # 0年1月0日转为-1年12月31日

        # 跨零年操作
        dt = DateTime(1, 1, 1)
        self.assertEqual(dt.add_day(-1), (0, 12, 31))

        dt = DateTime(-1, 12, 31)
        self.assertEqual(dt.add_day(1), (0, 1, 1))

    def test_BCE_leap_year(self):
        # 测试公元前闰年
        self.assertTrue(DateTime._is_leap_year(-4))  # 公元前4年是闰年
        self.assertFalse(DateTime._is_leap_year(-1))  # 公元前1年不是闰年

    def test_BCE_days_in_month(self):
        # 测试公元前年份的月份天数
        self.assertEqual(DateTime._days_in_month(-4, 2), 29)  # 公元前4年是闰年
        self.assertEqual(DateTime._days_in_month(-1, 2), 28)  # 公元前1年不是闰年

    def test_BCE_timezone_conversion(self):
        # 测试公元前日期时区转换
        tz_sh = timezone(timedelta(hours=8))
        dt = DateTime(-2023, 3, 1, 23, tz=timezone.utc)
        converted = dt.astimezone(tz_sh)
        self.assertEqual(converted.to_str(), "-02023-03-02T07:00:00.000")

    def test_year_zero_edge_cases(self):
        # 测试零年边界
        # 零年二月（需要处理闰年）
        self.assertEqual(DateTime._days_in_month(0, 2), 29)  # 0年按闰年处理
        DateTime(0, 2, 29)  # 应该正常创建

        # 零年12月31日+1天
        dt = DateTime(0, 12, 31)
        self.assertEqual(dt.add_day(1), (1, 1, 1))

if __name__ == '__main__':
    unittest.main()
