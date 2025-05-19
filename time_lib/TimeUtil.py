import math
import os
from time_lib.DateTime import DateTime
from astropy.time import Time
from datetime import timezone
from skyfield.api import load
from skyfield.framelib import ecliptic_frame
from time_lib.Bazi import JieQiStrategy, JieQi, BaZi, TianGan, DiZhi

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
        self._jieqi = list(JieQi)
        self._gan = list(TianGan)
        self._zhi = list(DiZhi)
        self._ganzhi = []
        for i in range(60):
            tg_index = i % len(TianGan)
            dz_index = i % len(DiZhi)
            self._ganzhi.append((self._gan[tg_index], self._zhi[dz_index]))

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
        日期转为儒略日(skyfield在儒略日计算上误差较大，故采用astropy)
        :param dt: 时间
        """
        datetime_str = dt.to_str(True)
        t = Time(datetime_str, format='fits', scale='utc')
        return t.jd1 + t.jd2

    @staticmethod
    def julian_2_datetime(jd: float) -> DateTime:
        """
        儒略日转日期(skyfield在儒略日计算上误差较大，故采用astropy)
        :param jd: 儒略日
        :return: 日期
        """
        t = Time(jd, format='jd', scale='utc')
        frac, integer = math.modf(t.ymdhms.second)
        dt = DateTime(t.ymdhms.year, t.ymdhms.month, t.ymdhms.day, t.ymdhms.hour, t.ymdhms.minute, int(integer),
                      int(round(frac * 1000)), timezone.utc)

        return dt

    def datetime_2_sun(self, dt: DateTime, lng: float) -> (float, float, float):
        """
        计算给定时间和经度的太阳视黄经(角度)和本地真太阳时(儒略日)，本地真太阳时(小时)
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
        return lon_ecliptic.degrees, jd_true_solar, true_solar

    def datetime_2_bazi(self, dt: DateTime, lng: float, strat: JieQiStrategy = JieQiStrategy.DING_QI) -> BaZi:
        utc_dt = dt.astimezone(timezone.utc)
        lon, _, true_solar_hour = self.datetime_2_sun(dt, lng)
        year = utc_dt.year
        if lon < 315.0 and not math.isclose(lon, 315, abs_tol=0.1):
            year = utc_dt.year - 1

        year_gan, year_zhi = self._ganzhi[(year - 3) % 60]
        month_zhi = TimeUtil.get_month_zhi(lon, strat)
        month_gan = self._get_month_gan(year_gan, month_zhi)
        day_gan, day_zhi = self._get_day_ganzhi(utc_dt)
        hour_gan, hour_zhi = self._get_hour_ganzhi(true_solar_hour, day_gan)
        return BaZi(year_gan, year_zhi, month_gan, month_zhi, day_gan, day_zhi, hour_gan, hour_zhi)

    def bazi_2_datetime(self, bazi: BaZi, lng: float, strat: JieQiStrategy) -> list[DateTime]:
        pass

    def ping_2_ding_qi(self, bazi: BaZi) -> BaZi:
        """
        将平气法的八字转为定气法的八字
        """
        pass

    def _get_month_gan(self, year_gan: TianGan, month_zhi: DiZhi) -> TianGan:
        """
        五虎遁月表
        甲己之年丙作首，乙庚之岁戊为头，
        丙辛必定寻庚起，丁壬壬位顺行流，
        若问戊癸何方发，甲寅之上好追求。
        """
        year_2_month = {TianGan.JIA: TianGan.BING, TianGan.YI: TianGan.WU, TianGan.BING: TianGan.GENG,
                        TianGan.DING: TianGan.REN, TianGan.WU: TianGan.JIA, TianGan.JI: TianGan.BING,
                        TianGan.GENG: TianGan.WU, TianGan.XIN: TianGan.GENG, TianGan.REN: TianGan.REN,
                        TianGan.GUI: TianGan.JIA}

        month_index = self._zhi.index(month_zhi)
        start_month_gan = year_2_month[year_gan]
        gan_index = self._gan.index(start_month_gan)
        return self._gan[(gan_index + month_index) % 10]

    @staticmethod
    def get_month_zhi(sun_lon, strat: JieQiStrategy) -> DiZhi:
        # 各月份的视黄经度数，取《太初历》，正月建寅
        jieqi_deg = [
            (345, DiZhi.MAO), (315, DiZhi.YIN), (285, DiZhi.CHOU), (255, DiZhi.ZI), (225, DiZhi.HAI), (195, DiZhi.XU),
            (165, DiZhi.YOU), (135, DiZhi.SHEN), (105, DiZhi.WEI), (75, DiZhi.WU), (45, DiZhi.SI), (15, DiZhi.CHEN)
        ]
        sun_lon %= 360
        for deg, zhi in jieqi_deg:
            if sun_lon >= deg:
                return zhi
        return DiZhi.MAO

    def _get_day_ganzhi(self, utc_dt: DateTime):
        jd = TimeUtil.datetime_2_julian(utc_dt)
        # 《春秋》记载，鲁隐公三年，“春，王二月己巳，日有食”
        ref_dt = DateTime(-720, 2, 22)
        ref = TimeUtil.datetime_2_julian(ref_dt)
        days_diff = math.floor(jd - ref)
        return self._ganzhi[(5 + days_diff) % 60]

    def _get_hour_ganzhi(self, true_solar_hour, day_gan: TianGan) -> (TianGan, DiZhi):
        """
        五鼠遁日表
        甲己还生甲，乙庚丙作初，
        丙辛从戊起，丁壬庚子居，
        戊癸何方发，壬子是真途。
        """
        day_2_hour = {TianGan.JIA: TianGan.JIA, TianGan.YI: TianGan.BING, TianGan.BING: TianGan.WU,
                      TianGan.DING: TianGan.GENG, TianGan.WU: TianGan.REN, TianGan.JI: TianGan.JIA,
                      TianGan.GENG: TianGan.BING, TianGan.XIN: TianGan.WU, TianGan.REN: TianGan.GENG,
                      TianGan.GUI: TianGan.REN}
        # 时辰计算（子时为23:00-1:00）
        zhi_index = int((true_solar_hour + 1) // 2) % 12
        start_hour_gan = day_2_hour[day_gan]
        gan_index = self._gan.index(start_hour_gan)
        return self._gan[(gan_index + zhi_index) % 10], self._zhi[zhi_index]
