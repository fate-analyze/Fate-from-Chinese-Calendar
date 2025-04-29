import unittest
from algo_lib.DateTime import DateTime
from algo_lib.TimeUtil import TimeUtil
from datetime import timezone


class AstroTimeTestCase(unittest.TestCase):
    def test_ad_trans(self):
        """测试公元后"""
        # 公元第一天
        jd = TimeUtil.datetime_2_julian(DateTime(1, 1, 1, 12, 0, 0, tz=timezone.utc))
        self.assertAlmostEqual(jd, 1721426, places=3)

        # 格里高利历在这之后跳过10天
        jd = TimeUtil.datetime_2_julian(DateTime(1582, 10, 4, 12, 0, 0, tz=timezone.utc))
        self.assertAlmostEqual(jd, 2299150, places=3)

        # 格里高利历在中间的10天不存在
        jd = TimeUtil.datetime_2_julian(DateTime(1582, 10, 5, 12, 0, 0, tz=timezone.utc))
        self.assertAlmostEqual(jd, 2299151, places=3)
        jd = TimeUtil.datetime_2_julian(DateTime(1582, 10, 11, 12, 0, 0, tz=timezone.utc))
        self.assertAlmostEqual(jd, 2299157, places=3)

        # 格里高利历跳过10天之后
        jd = TimeUtil.datetime_2_julian(DateTime(1582, 10, 15, 12, 0, 0, tz=timezone.utc))
        self.assertAlmostEqual(jd, 2299161, places=3)

        # 格里高利历400年闰，1600年闰年
        jd = TimeUtil.datetime_2_julian(DateTime(1600, 2, 29, 12, 0, 0, tz=timezone.utc))
        self.assertAlmostEqual(jd, 2305507, places=3)

        # 格里高利历百年不闰，1700年非闰年
        jd = TimeUtil.datetime_2_julian(DateTime(1700, 2, 28, 12, 0, 0, tz=timezone.utc))
        self.assertAlmostEqual(jd, 2342031, places=3)

        # UNIX时间起点
        jd = TimeUtil.datetime_2_julian(DateTime(1970, 1, 1, 0, 0, 0, tz=timezone.utc))
        self.assertAlmostEqual(jd, 2440587.5, places=3)

        jd = TimeUtil.datetime_2_julian(DateTime(1997, 1, 1, 0, 0, 0, 500, tz=timezone.utc))
        self.assertAlmostEqual(jd, 2450449.5000057872, places=7)

        # 现代闰年
        jd = TimeUtil.datetime_2_julian(DateTime(2012, 1, 23, 6, 25, 7, 100, tz=timezone.utc))
        self.assertAlmostEqual(jd, 2455949.767443287, places=7)

        jd = TimeUtil.datetime_2_julian(DateTime(2012, 2, 29, 0, 0, 0, tz=timezone.utc))
        self.assertAlmostEqual(jd, 2455986.5, places=3)

    def test_bc_trans(self):
        """测试公元前"""
        jd = TimeUtil.datetime_2_julian(DateTime(-4713, 11, 24, 12, 0, 0, tz=timezone.utc))
        self.assertAlmostEqual(jd, 0, places=3)

        jd = TimeUtil.datetime_2_julian(DateTime(-4713, 11, 25, 12, 0, 0, tz=timezone.utc))
        self.assertAlmostEqual(jd, 1, places=3)

        # 闰年
        jd = TimeUtil.datetime_2_julian(DateTime(-4712, 11, 24, 12, 0, 0, tz=timezone.utc))
        self.assertAlmostEqual(jd, 366, places=3)

        # 公元前最后一天
        jd = TimeUtil.datetime_2_julian(DateTime(0, 12, 31, 12, 0, 0, tz=timezone.utc))
        self.assertAlmostEqual(jd, 1721425, places=3)
        dt = TimeUtil.julian_2_datetime(jd)
        self.assertEqual(dt, DateTime(0, 12, 31, 12, 0, 0, tz=timezone.utc))

    def test_lib_correct(self):
        """测试库自身的正确性"""
        # 很多工具在公元1-1-1 00:00::00和儒略日的相互转换上结果不一致
        dt = DateTime(1, 1, 1, 12, 0, 0, tz=timezone.utc)
        jd = TimeUtil.datetime_2_julian(dt)
        self.assertAlmostEqual(jd, 1721426, places=3)

        dt_2 = TimeUtil.julian_2_datetime(jd)
        self.assertEqual(dt, dt_2)


if __name__ == '__main__':
    unittest.main()
