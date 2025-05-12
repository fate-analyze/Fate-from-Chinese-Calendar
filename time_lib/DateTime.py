from datetime import timezone, timedelta


class DateTime:
    def __init__(self, year=0, month=1, day=1, hour=0, minute=0, second=0, millisecond=0,
                 tz: timezone = timezone(timedelta(hours=8))):
        self._validate_fields(year, month, day, hour, minute, second, millisecond)
        self._year = year  # 0或者负数表示公元前
        self._month = month
        self._day = day
        self._hour = hour
        self._minute = minute
        self._second = second
        self._millisecond = millisecond
        self._tz = tz

    def __eq__(self, other) -> bool:
        if not isinstance(other, DateTime):
            return False
        return (self._year == other.year
                and self._month == other.month
                and self._day == other.day
                and self._hour == other.hour
                and self._minute == other.minute
                and self._second == other.second
                and self._millisecond == other.millisecond
                and self._tz.utcoffset(None) == other.timezone.utcoffset(None)
                )

    def _validate_fields(self, year, month, day, hour, minute, second, millisecond):
        if not 1 <= month <= 12:
            raise ValueError("month must be 1-12")
        max_day = self._days_in_month(year, month)
        if not 1 <= day <= max_day:
            raise ValueError(f"day must be 1-{max_day} for month {month}")
        if not 0 <= hour < 24:
            raise ValueError("hour must be 0-23")
        if not 0 <= minute < 60:
            raise ValueError("minute must be 0-59")
        if not 0 <= second < 60:
            raise ValueError("second must be 0-59")
        if not 0 <= millisecond < 1000:
            raise ValueError("millisecond must be 0-999")

    @staticmethod
    def _is_leap_year(year):
        if year % 4 != 0:
            return False
        elif year % 100 != 0:
            return True
        else:
            return year % 400 == 0

    @staticmethod
    def _days_in_month(year, month):
        if month == 2:
            return 29 if DateTime._is_leap_year(year) else 28
        elif month in [4, 6, 9, 11]:
            return 30
        else:
            return 31

    def _calculate_time_difference(self, tgt_tz: timezone) -> float:
        """计算时区时间差（秒）"""

        def _get_offset_seconds(tz: timezone) -> float:
            if (offset := tz.utcoffset(None)) is None:
                raise ValueError("仅支持固定偏移时区")
            return offset.total_seconds()

        src_offset = _get_offset_seconds(self.timezone)
        tgt_offset = _get_offset_seconds(tgt_tz)
        return tgt_offset - src_offset

    def add_day(self, delta_days: int) -> (int, int, int):
        """计算调整后的年月日"""
        new_year, new_month, new_day = self.year, self.month, self.day + delta_days

        # 循环调整日期至合法
        while True:
            max_day = self._days_in_month(new_year, new_month)
            if new_day < 1:
                new_month -= 1
                if new_month < 1:
                    new_year -= 1
                    new_month = 12
                new_day += self._days_in_month(new_year, new_month)
            elif new_day > max_day:
                new_day -= max_day
                new_month += 1
                if new_month > 12:
                    new_year += 1
                    new_month = 1
            else:
                break
        return new_year, new_month, new_day

    def astimezone(self, tgt_tz: timezone):
        """
        将当前时间转为目标时区的时间
        :param tgt_tz: 目标时区
        :return: DateTime
        """
        if self._tz == tgt_tz:
            return self

        delta_seconds = self._calculate_time_difference(tgt_tz)

        # 计算总秒数和天数变化
        total_seconds = (self.hour * 3600 + self.minute * 60 + self.second + self.millisecond / 1000) + delta_seconds
        delta_days, remainder_seconds = divmod(total_seconds, 86400)
        if remainder_seconds < 0:
            delta_days -= 1
            remainder_seconds += 86400

        # 计算新日期
        new_year, new_month, new_day = self.add_day(int(delta_days))

        # 计算新时间
        new_hour = int(remainder_seconds // 3600)
        remainder_seconds %= 3600
        new_minute = int(remainder_seconds // 60)
        new_second = int(remainder_seconds % 60)
        new_millisecond = int(round((remainder_seconds - new_second) * 1000))

        # 处理时间进位
        if new_millisecond >= 1000:
            new_second += 1
            new_millisecond -= 1000
            if new_second >= 60:
                new_minute += 1
                new_second -= 60
                if new_minute >= 60:
                    new_hour += 1
                    new_minute -= 60
                    if new_hour >= 24:
                        new_hour -= 24
                        new_day += 1

        return DateTime(new_year, new_month, new_day, new_hour, new_minute, new_second, tz=tgt_tz)

    def to_str(self, utc=False) -> str:
        """
        时间转为字符串, FITS格式
        :param utc: True表示转为UTC时间
        """
        # 时间FITS格式请参考论文https://arxiv.org/abs/1409.7583
        real_dz = self
        if utc and self._tz != timezone.utc:
            real_dz = self.astimezone(timezone.utc)

        sign = "+" if (real_dz.year > 0) else "-"
        year_abs = abs(real_dz.year)

        fits_str = (
            f"{sign}{year_abs:05d}-{real_dz.month:02d}-{real_dz.day:02d}T"
            f"{real_dz.hour:02d}:{real_dz.minute:02d}:{real_dz.second:02d}.{real_dz.millisecond:03d}"
        )
        return fits_str

    # 属性访问器
    @property
    def year(self):
        return self._year

    @property
    def month(self):
        return self._month

    @property
    def day(self):
        return self._day

    @property
    def hour(self):
        return self._hour

    @property
    def minute(self):
        return self._minute

    @property
    def second(self):
        return self._second

    @property
    def millisecond(self):
        return self._millisecond

    @property
    def double_second(self):
        return float(self._second) + float(self._millisecond)

    @property
    def timezone(self):
        return self._tz
