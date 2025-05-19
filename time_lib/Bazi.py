from enum import Enum
from dataclasses import dataclass


class JieQiStrategy(Enum):
    PING_QI = "平气法"
    DING_QI = "定气法"


class JieQi(Enum):
    LI_CHUN = "立春"
    YU_SHUI = "雨水"
    JING_ZHE = "惊蛰"
    CHUN_FEN = "春分"
    QING_MING = "清明"
    GU_YU = "谷雨"
    LI_XIA = "立夏"
    XIAO_MAN = "小满"
    MANG_ZHONG = "芒种"
    XIA_ZHI = "夏至"
    XIAO_SHU = "小暑"
    DA_SHU = "大暑"
    LI_QIU = "立秋"
    CHU_SHU = "处暑"
    BAI_LU = "白露"
    QIU_FEN = "秋分"
    HAN_LU = "寒露"
    SHUANG_JIANG = "霜降"
    LI_DONG = "立冬"
    XIAO_XUE = "小雪"
    DA_XUE = "大雪"
    DONG_ZHI = "冬至"
    XIAO_HAN = "小寒"
    DA_HAN = "大寒"


class TianGan(Enum):
    JIA = "甲"
    YI = "乙"
    BING = "丙"
    DING = "丁"
    WU = "戊"
    JI = "己"
    GENG = "庚"
    XIN = "辛"
    REN = "壬"
    GUI = "癸"


class DiZhi(Enum):
    ZI = "子"
    CHOU = "丑"
    YIN = "寅"
    MAO = "卯"
    CHEN = "辰"
    SI = "巳"
    WU = "午"
    WEI = "未"
    SHEN = "申"
    YOU = "酉"
    XU = "戌"
    HAI = "亥"


@dataclass
class BaZi:
    def __init__(self, year1: TianGan, year2: DiZhi, month1: TianGan, month2: DiZhi, day1: TianGan, day2: DiZhi,
                 hour1: TianGan, hour2: DiZhi):
        self._year1 = year1
        self._year2 = year2
        self._month1 = month1
        self._month2 = month2
        self._day1 = day1
        self._day2 = day2
        self._hour1 = hour1
        self._hour2 = hour2

    @property
    def year_gan(self):
        return self._year1

    @property
    def year_zhi(self):
        return self._year2

    @property
    def month_gan(self):
        return self._month1

    @property
    def month_zhi(self):
        return self._month2

    @property
    def day1_gan(self):
        return self._day1

    @property
    def day_zhi(self):
        return self._day2

    @property
    def hour_gan(self):
        return self._hour1

    @property
    def hour_zhi(self):
        return self._hour2
