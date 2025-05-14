import math
import os
from time_lib.DateTime import DateTime
from astropy.time import Time
from datetime import timezone
from skyfield.api import load
from skyfield.framelib import ecliptic_frame
from time_lib.Bazi import JieQiStrategy, JieQi, BaZi

"""
星历离线下载说明：
https://ssd.jpl.nasa.gov/planets/eph_export.html

astropy在线模式:
from astropy.utils.data import conf
conf.dataurl_proxy = {'http': 'http://your-proxy:8080'}
conf.remote_timeout = 60
"""


class TimeUtil:
    def __init__(self, ephemeris='de430t.bsp', online_mode=False):
        if not online_mode:
            current_dir = os.path.dirname(os.path.abspath(__file__))
            ephemeris = os.path.join(current_dir, ephemeris)
            self._ephemeris = load(ephemeris)
            # iers_conf.auto_download = False
            # iers_conf.iers_auto_url = os.path.join("file://", current_dir, 'finals2000A.all')
        else:
            self._ephemeris = load(ephemeris)

    @staticmethod
    def datetime_2_julian(dt: DateTime) -> float:
        """
        日期转为儒略日
        :param dt: 时间
        """
        datetime_str = dt.to_str(True)
        t = Time(datetime_str, format='fits', scale='utc')
        return t.jd1 + t.jd2

    @staticmethod
    def julian_2_datetime(jd: float) -> DateTime:
        """
        儒略日转日期
        :param jd: 儒略日
        :return: 日期
        """
        t = Time(jd, format='jd', scale='utc')
        frac, integer = math.modf(t.ymdhms.second)
        dt = DateTime(t.ymdhms.year, t.ymdhms.month, t.ymdhms.day, t.ymdhms.hour, t.ymdhms.minute, int(integer),
                      int(round(frac * 1000)), timezone.utc)

        return dt

    def datetime_2_sun(self, dt: DateTime, lng: float) -> (float, float):
        """
        计算给定时间和经度的太阳视黄经(角度)和本地真太阳时(儒略日)
        :param dt: 时间
        :param lng: 经度(单位：度）
        """
        utc_dt = dt.astimezone(timezone.utc)
        ts = load.timescale()
        t = ts.utc(utc_dt.year, utc_dt.month, utc_dt.day, utc_dt.hour, utc_dt.minute, utc_dt.double_second)

        # 计算太阳视黄经
        sun = self._ephemeris["sun"]
        earth = self._ephemeris["earth"]
        astrometric = earth.at(t).observe(sun)
        lon_ecliptic, _, _ = astrometric.frame_latlon(ecliptic_frame)

        # 计算真太阳时
        ra = astrometric.radec()[0].hours  # 太阳赤经（小时）
        gast = t.gast  # 格林尼治视恒星时（小时）
        last = gast + lng / 15.0  # 本地视恒星时（LAST）
        hour_angle = (last - ra) % 24  # 时角（小时）
        true_solar = (hour_angle + 12) % 24  # 真太阳时（小时）

        jd_utc = t.ut1  # UTC儒略日
        delta_hours = true_solar - utc_dt.hour - utc_dt.minute / 60 - utc_dt.double_second / 3600
        delta_days = delta_hours / 24.0
        jd_true_solar = jd_utc + delta_days  # 真太阳时儒略日 = UTC儒略日 + 时差（自动处理跨日）
        return lon_ecliptic.degrees, jd_true_solar

    def datetime_2_bazi(self, dt: DateTime, lng: float, strat: JieQiStrategy = JieQiStrategy.DING_QI) -> BaZi:
        pass

    def bazi_2_datetime(self, bazi: BaZi, lng: float, strat: JieQiStrategy) -> list[DateTime]:
        pass

    def ping_2_ding_qi(self, bazi: BaZi) -> BaZi:
        """
        将平气法的八字转为定气法的八字
        """
        pass