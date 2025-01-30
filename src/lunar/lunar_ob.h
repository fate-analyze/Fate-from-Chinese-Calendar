#ifndef LUNAR_OB_H
#define LUNAR_OB_H

#include <array>
#include <string>
#include <vector>

namespace sxwnl {

constexpr std::array<const char *, 11> str_num = {"零", "一", "二", "三", "四", "五", "六", "七", "八", "九", "十"};
constexpr std::array<const char *, 12> str_ymc = {"十一", "腊", "正", "二", "三", "四", "五", "六", "七", "八", "九", "十"};
constexpr std::array<const char *, 4> str_yxmc = {"朔", "上弦", "望", "下弦"};
constexpr std::array<const char *, 24> str_jqmc = {"冬至", "小寒", "大寒", "立春", "雨水", "惊蛰", "春分", "清明",
                                                   "谷雨", "立夏", "小满", "芒种", "夏至", "小暑", "大暑", "立秋",
                                                   "处暑", "白露", "秋分", "寒露", "霜降", "立冬", "小雪", "大雪"};
constexpr std::array<const char *, 10> str_gan = {"甲", "乙", "丙", "丁", "戊", "己", "庚", "辛", "壬", "癸"};
constexpr std::array<const char *, 12> str_zhi = {"子", "丑", "寅", "卯", "辰", "巳", "午", "未", "申", "酉", "戌", "亥"};
constexpr std::array<const char *, 12> str_sxmc = {"鼠", "牛", "虎", "兔", "龙", "蛇", "马", "羊", "猴", "鸡", "狗", "猪"};
constexpr std::array<const char *, 30> str_nywx = {"海中金", "炉中火", "大林木", "路边土", "剑峰金", "山头火", "涧下水", "城墙土",
                                                   "白腊金", "杨柳木", "泉中水", "屋上土", "霹雷火", "松柏木", "长流水", "沙中金",
                                                   "山下火", "平地木", "壁上土", "金泊金", "佛灯火", "天河水", "大泽土", "钗钏金",
                                                   "桑松木", "大溪水", "沙中土", "天上火", "石榴木", "大海水"};
constexpr std::array<const char *, 7> str_xqmc = {"日", "一", "二", "三", "四", "五", "六"};
constexpr std::array<const char *, 30> str_rmc = {"初一", "初二", "初三", "初四", "初五", "初六", "初七", "初八", "初九", "初十",
                                                  "十一", "十二", "十三", "十四", "十五", "十六", "十七", "十八", "十九", "二十",
                                                  "廿一", "廿二", "廿三", "廿四", "廿五", "廿六", "廿七", "廿八", "廿九", "三十"};
constexpr std::array<const char *, 31> str_rmc0 = {"１",   "２",   "３",   "４",   "５",   "６",   "７",   "８",   "９",   "１０", "１１",
                                                   "１２", "１３", "１４", "１５", "１６", "１７", "１８", "１９", "２０", "２１", "２２",
                                                   "２３", "２４", "２５", "２６", "２７", "２８", "２９", "３０", "３１"};
constexpr std::array<const char *, 12> str_xz = {"摩羯座♑️", "水瓶座♒️", "双鱼座♓️", "白羊座♈️", "金牛座♉️", "双子座♊️",
                                                 "巨蟹座♋️", "狮子座♌️", "处女座♍️", "天秤座♎️", "天蝎座♏️", "射手座♐️"};
constexpr std::array<const char *, 2> str_dx = {"小", "大"};
constexpr std::array<const char *, 5> str_ago = {"昨天", "今天", "明天", "天后", "天前"};
constexpr std::array<const char *, 4> str_fw = {"南", "东", "北", "西"};
constexpr std::array<const char *, 7> str_sjd = {"凌晨", "早晨", "上午", "中午", "下午", "晚上", "深夜"};
constexpr std::array<const char *, 2> str_ry = {"  ", "闰"};
constexpr std::array<const char *, 2> str_ry2 = {"", "闰"};

struct OB_DAY {
    /* 日的公历信息 */
    int d0;  // 2000.0起算儒略日,北京时12:00
    int di;  // 所在公历月内日序数
    int y;
    int m;
    int d;  // 日名称(公历)
    int dn;
    int week0;
    int week;   // 星期
    int weeki;  // 在本月中的周序号
    int weekN;  // 本月的总周数
    /* 日的农历信息 */
    int Ldi;          // 日距农历月首偏移
    std::string Ldc;  // 日名称(农历),即'初一,初二等'

    int cur_dz;  //冬至的天数
    int cur_xz;  //夏至的天数
    int cur_lq;  //立秋的天数
    int cur_mz;  //芒种的天数
    int cur_xs;  //小暑的天数
    std::string Lmc;
    std::string Lmc2;   // 月名称
    int Ldn;            // 月大小
    std::string Lleap;  // 闰状况
    /* 日的农历纪年、月、日、时及星座 */
    int Lyear;  // 农历纪年(10进制,1984年起算,分界点可以是立春也可以是春节,在程序中选择一个)
    int Lyear0;
    std::string Lyear2;   // 干支纪年
    std::string Lyear3;   // 干支纪年(春节)
    int Lyear4;           // 干支纪年(黄帝纪元)
    int Lmonth;           // 纪月处理,1998年12月7日(大雪)开始连续进行节气计数,0为甲子
    std::string Lmonth2;  // 干支纪月
    std::string Lday2;    // 纪日
    std::string Ltime2;   // 纪时
    std::string Ljq;      // 节气
    std::string XiZ;      // 星座
    /* 日的回历信息 */
    int Hyear;   // 年(回历)
    int Hmonth;  // 月(回历)
    int Hday;    // 日(回历)
    /* 日的其它信息 */
    std::string yxmc;  // 月相名称
    double yxjd;       // 月相时刻(儒略日)
    std::string yxsj;  // 月相时间串
    std::string jqmc;  // 节气名称
    double jqjd;       // 节气时刻(儒略日)
    std::string jqsj;  // 节气时间串

    bool Fjia;
    std::string A;
    std::string B;
    std::string C;
};

class OBA {
public:
    static void init();
    static void getDayName(OB_DAY &r);
    static void getHuiLi(double d0, OB_DAY &r);

private:
    static std::vector<std::vector<std::string>> sFtv;  //假日表,由init初始化
    static std::vector<std::string> wFtv;
};

/**
 * @brief 农历对象，气朔计算等
 */
class OBB {
public:
    static void init();
    static std::string getNH(int y);
    static void getDayName2(OB_DAY &r);
    static double qi_accurate(double W);
    static double so_accurate(double W);
    static double qi_accurate2(double jd);
    static double so_accurate2(double jd);

private:
    static std::vector<std::string> JNB;
};
}  // namespace sxwnl

#endif
