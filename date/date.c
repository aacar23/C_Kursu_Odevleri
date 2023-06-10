#include "date.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static int month_days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static const char * const month_names[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
static const char * const weekday_names[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

#define malloc(size) (checked_malloc(size))
#define access_date(p) ((date_core *)((p) -> address))
#define const_access_date(p) ((const date_core *)((p) -> address))
#define asize(array) (sizeof((array)) / sizeof(*(array)))

#define WEEKDAY_CALC_FAILURE (-1)
#define NTH_DAY_CALC_FAILURE (-1)
#define ASSIGN (1)
#define DONT_ASSIGN (0)

#define localize_and_access(dest, source) (const_access_date(time_t_to_date_gmt((dest), date_to_time_t_local(NULL, (source)))))
#define localize(dest, source) ((time_t_to_date_gmt((dest), date_to_time_t_local(NULL, (source)))))

#define implement_difference_func(unit, func_identifier) time_t difference = (func_identifier)(p1, p2); \
                                                        return  difference == DIFF_FAILURE ? DIFF_FAILURE : difference / (unit); \

typedef struct{
    int gmt_day;
    int gmt_month;
    int gmt_year;
    int gmt_hour;
    int gmt_minute;
    int gmt_second;
    int gmt_weekday;
    int gmt_nth_day_of_the_year;
    int local_nth_day_of_the_year;
    int utc;
} date_core;


static date_core time_t_to_date_core;
static date time_t_to_date_obj = {.address = &time_t_to_date_core};

static date_core get_core;
static date get_obj = {.address = &get_core};

static date_core n_seconds_before_core;
static date n_seconds_before_obj = {.address = &n_seconds_before_core};

static date_core n_seconds_after_core;
static date n_seconds_after_obj = {.address = &n_seconds_after_core};

static date_core n_minutes_before_core;
static date n_minutes_before_obj = {.address = &n_minutes_before_core};

static date_core n_minutes_after_core;
static date n_minutes_after_obj = {.address = &n_minutes_after_core};

static date_core n_hours_before_core;
static date n_hours_before_obj = {.address = &n_hours_before_core};

static date_core n_hours_after_core;
static date n_hours_after_obj = {.address = &n_hours_after_core};

static date_core n_days_before_core;
static date n_days_before_obj = {.address = &n_days_before_core};

static date_core n_days_after_core;
static date n_days_after_obj = {.address = &n_days_after_core};

static date_core n_months_before_core;
static date n_months_before_obj = {.address = &n_months_before_core};

static date_core n_months_after_core;
static date n_months_after_obj = {.address = &n_months_after_core};

static date_core n_years_before_core;
static date n_years_before_obj = {.address = &n_years_before_core};

static date_core n_years_after_core;
static date n_years_after_obj = {.address = &n_years_after_core};

static char date_to_str_str[DATE_STR_SIZE];

static date_core str_to_date_core;
static date str_to_date_obj = {.address = &str_to_date_core};






static int is_leap(int year)
{
    return ((!(year % 4)) && (!(year % 400) || year % 100));
}

static int check_date(int day, int month, int year, int hour, int minute, int second, int utc)
{
    if (year > 2037 || year < 1900)
        return 0;
    if (month > 12 || month < 1)
        return 0;
    month_days[1] = is_leap(year) ? 29 : 28;
    if (day > month_days[month - 1] || day < 1)
        return 0;
    if (hour > 23 || hour < 0)
        return 0;
    if (minute > 59 || minute < 0)
        return 0;
    if (second > 59 || second < 0)
        return 0;
    if (utc > 12 || utc < -12)
        return 0;
    return 1;
}

static int check_date_by_ptr(const date *p)
{
    const date_core *p_accessed = const_access_date(p);
    return check_date(p_accessed -> gmt_day, p_accessed -> gmt_month, p_accessed -> gmt_year, p_accessed -> gmt_hour, p_accessed -> gmt_minute, p_accessed -> gmt_second, p_accessed -> utc);
}

static void *checked_malloc(size_t size)
{
    void *vp;
    if (!(vp = (malloc)(size))){
        fprintf(stderr, "heap is full");
        exit(EXIT_FAILURE);
    }
    return vp;
}

static int calculate_nth_day_of_the_year_gmt(date *p, int assign)
{
    if (!check_date_by_ptr(p))
        return NTH_DAY_CALC_FAILURE;
    date_core *p_accessed = access_date(p);
    int nth_day = 0;
    int month = p_accessed -> gmt_month;
    for (int i = 1;i < month;nth_day += month_days[i++ - 1])
        ;
    nth_day += p_accessed -> gmt_day;
    return assign ? p_accessed -> gmt_nth_day_of_the_year = nth_day: nth_day;
}

static int calculate_nth_day_of_the_year_local(date *p)
{
    int calc_nth_day_gmt = calculate_nth_day_of_the_year_gmt(p, DONT_ASSIGN);
    if (calc_nth_day_gmt == NTH_DAY_CALC_FAILURE)
        return NTH_DAY_CALC_FAILURE;
    time_t timer = calc_nth_day_gmt * SECONDS_IN_A_DAY + get_utc(p) * SECONDS_IN_AN_HOUR +
            get_gmt_hour(p) * SECONDS_IN_AN_HOUR;
    return access_date(p) -> local_nth_day_of_the_year = (int)(timer / SECONDS_IN_A_DAY);
}

static int calculate_weekday(date *p, int assign)
{
    if (!check_date_by_ptr(p))
        return WEEKDAY_CALC_FAILURE;
    time_t timer = date_to_time_t_gmt(NULL, p) - STARTING_TIME_POINT;
    if (timer == CONV_FAILURE)
        return WEEKDAY_CALC_FAILURE;
    return assign ? access_date(p) -> gmt_weekday = (int)((timer) % (SECONDS_IN_A_DAY * 7)) / SECONDS_IN_A_DAY : (int)((timer) % (SECONDS_IN_A_DAY * 7)) / SECONDS_IN_A_DAY;
}






extern void activate_date(date *p, int utc_val)
{
    p -> address = malloc(sizeof(date_core));
    memset(p -> address, 0, sizeof(date_core));
    access_date(p) -> utc = utc_val;
}

extern void deactivate_date(date *p)
{
    free(p -> address);
}






extern date *normalize_date(date *p)
{
    if (calculate_nth_day_of_the_year_local(p) == NTH_DAY_CALC_FAILURE || calculate_nth_day_of_the_year_gmt(p, ASSIGN) == NTH_DAY_CALC_FAILURE || calculate_weekday(p, ASSIGN) == WEEKDAY_CALC_FAILURE)
        return NULL;
    return p;
}






extern date *copy_date(date *dest, const date *source)
{
    return memcpy(dest, source, sizeof(date_core));
}






extern time_t date_to_time_t_local(time_t *dest, const date *source)
{
    if (!check_date_by_ptr(source))
        return CONV_FAILURE;
    const date_core * source_accessed = const_access_date(source);
    time_t ret = source_accessed -> utc * SECONDS_IN_AN_HOUR + STARTING_TIME_POINT - SECONDS_IN_A_DAY;
    ret += source_accessed -> gmt_hour * SECONDS_IN_AN_HOUR;
    ret += source_accessed -> gmt_minute * SECONDS_IN_A_MINUTE;
    ret += source_accessed -> gmt_second;
    ret += source_accessed -> gmt_day * SECONDS_IN_A_DAY;
    int year = 1900;
    for (; year < source_accessed -> gmt_year; ret += is_leap(year++) ? SECONDS_IN_A_LEAP_YEAR : SECONDS_IN_A_COMMON_YEAR)
        ;
    month_days[1] = is_leap(source_accessed -> gmt_year) ? 29 : 28;
    int i = 1;
    for(;i < source_accessed -> gmt_month;ret += month_days[i++ - 1] * SECONDS_IN_A_DAY)
        ;
    return dest ? (*dest = ret) : ret;
}

extern time_t date_to_time_t_gmt(time_t *dest, const date *source)
{
    time_t conv = date_to_time_t_local(dest, source);
    if (conv == DIFF_FAILURE)
        return DIFF_FAILURE;
    return date_to_time_t_local(dest, source) - const_access_date(source) -> utc * SECONDS_IN_AN_HOUR;
}

extern date *time_t_to_date_local(date *p, time_t local_time, int utc)
{
    if (local_time > ENDING_TIME_POINT || local_time < STARTING_TIME_POINT)
        return NULL;
    if (p == NULL)
        p = &time_t_to_date_obj;
    local_time += -STARTING_TIME_POINT;
    date_core *p_accessed = access_date(p);
    p_accessed -> gmt_weekday = (int)((local_time) % (SECONDS_IN_A_DAY * 7)) / SECONDS_IN_A_DAY;
    p_accessed -> gmt_second = (int)(local_time % SECONDS_IN_A_MINUTE);
    p_accessed -> gmt_minute = (int)(local_time % SECONDS_IN_AN_HOUR) / SECONDS_IN_A_MINUTE;
    p_accessed -> gmt_hour = (int)(local_time % SECONDS_IN_A_DAY) / SECONDS_IN_AN_HOUR;
    int year = 1900;
    for (int minus = is_leap(year) ? SECONDS_IN_A_LEAP_YEAR : SECONDS_IN_A_COMMON_YEAR; local_time - minus > 0; local_time -= minus = (is_leap(year++) ? SECONDS_IN_A_LEAP_YEAR : SECONDS_IN_A_COMMON_YEAR))
        ;
    month_days[1] = is_leap(year) ? 29 : 28;
    p_accessed -> gmt_year = year;
    int month = 1;
    for(;local_time - month_days[month - 1] * SECONDS_IN_A_DAY >= 0; local_time -= month_days[month++ - 1] * SECONDS_IN_A_DAY)
        ;
    p_accessed -> gmt_month = month;
    p_accessed -> gmt_day = (int)(local_time / SECONDS_IN_A_DAY) + 1;
    p_accessed -> utc = utc;
    calculate_nth_day_of_the_year_gmt(p, ASSIGN);
    calculate_nth_day_of_the_year_local(p);
    return p;
}

extern date *time_t_to_date_gmt(date *p, time_t gmt_time)
{
    return time_t_to_date_local(p, gmt_time, 0);
}






extern date *set_utc(date *p, int utc_val)
{
    if (utc_val > 12 || utc_val < -12)
        return NULL;
    access_date(p) -> utc = utc_val;
    return p;
}

static date *set_date_value(date *p, DATE_VALUE member, int value, int start_edge, int end_edge)
{
    if (value < start_edge || value > end_edge)
        return NULL;
    ((int *)access_date(p))[member] = value;
    return p;
}

extern date *set_day(date *p, int day_value)
{
    access_date(p) -> gmt_day = day_value;
    return p;
}

extern date *set_month(date *p, int month_value)
{
    return set_date_value(p, MONTHS, month_value, 1, 12);
}

extern date *set_year(date *p, int year_value)
{
    return set_date_value(p, YEARS, year_value, 1900, 2037);
}

extern date *set_hour(date *p, int hour_value)
{
    return set_date_value(p, HOURS, hour_value, 0, 23);
}

extern date *set_minute(date *p, int minute_value)
{
    return set_date_value(p, MINUTES, minute_value, 0, 59);
}

extern date *set_second(date *p, int second_value)
{
    return set_date_value(p, SECONDS, second_value, 0, 59);
}

extern date *set_date(date *p, int day_value, int month_value, int year_value, int hour_value, int minute_value, int second_value, int utc_value)
{
    if (!check_date(day_value, month_value, year_value, hour_value, minute_value, second_value, utc_value))
        return NULL;
    set_day(p, day_value);
    set_month(p, month_value);
    set_year(p, year_value);
    set_hour(p, hour_value);
    set_minute(p, minute_value);
    set_second(p, second_value);
    set_utc(p, utc_value);
    normalize_date(p);
    return p;
}






extern int get_gmt_value(const date *p, DATE_VALUE member)
{
    if (!check_date_by_ptr(p))
        return GET_FAILURE;
    return ((const int *)const_access_date(p))[member];
}

extern int get_gmt_day(const date *p)
{
    return get_gmt_value(p, DAYS);
}

extern int get_gmt_month(const date *p)
{
    return get_gmt_value(p, MONTHS);
}

extern int get_gmt_year(const date *p)
{
    return get_gmt_value(p, YEARS);
}

extern int get_gmt_hour(const date *p)
{
    return get_gmt_value(p, HOURS);
}

extern int get_gmt_minute(const date *p)
{
    return get_gmt_value(p, MINUTES);
}

extern int get_gmt_second(const date *p)
{
    return get_gmt_value(p, SECONDS);
}

extern int get_nth_day_of_the_year_gmt(const date *p)
{
    return get_gmt_value(p, NTH_DAY_OF_THE_YEAR_GMT);
}

extern int get_local_value(const date *p, DATE_VALUE member)
{
    if (!check_date_by_ptr(p))
        return GET_FAILURE;
    const date_core *p_localized = localize_and_access(&get_obj, p);
    return ((const int *)p_localized)[member];

}

extern int get_local_day(const date *p)
{
    return get_local_value(p, DAYS);
}

extern int get_local_month(const date *p)
{
    return get_local_value(p, MONTHS);
}

extern int get_local_year(const date *p)
{
    return get_local_value(p, YEARS);
}

extern int get_local_hour(const date *p)
{
    return get_local_value(p, HOURS);
}

extern int get_local_minute(const date *p)
{
    return get_local_value(p, MINUTES);
}

extern int get_local_second(const date *p)
{
    return get_local_value(p, SECONDS);
}

extern int get_nth_day_of_the_year_local(const date *p)
{
    return get_local_value(p, NTH_DAY_OF_THE_YEAR_LOCAL);
}

extern int get_utc(const date *p)
{
    return get_gmt_value(p, UTC);
}






static time_t date_difference_seconds_gmt(const date *p1, const date *p2)
{
    time_t time_p1 = date_to_time_t_gmt(NULL, p1);
    time_t time_p2 = date_to_time_t_gmt(NULL, p2);
    if (time_p1 == CONV_FAILURE || time_p2 == CONV_FAILURE)
        return DIFF_FAILURE;
    return time_p1 - time_p2;
}

static time_t date_difference_minutes_gmt(const date *p1, const date *p2)
{
    implement_difference_func(SECONDS_IN_A_MINUTE, date_difference_seconds_gmt)
}

static time_t date_difference_hours_gmt(const date *p1, const date *p2)
{
    implement_difference_func(SECONDS_IN_AN_HOUR, date_difference_seconds_gmt)
}

static time_t date_difference_days_gmt(const date *p1, const date *p2)
{
    implement_difference_func(SECONDS_IN_A_DAY, date_difference_seconds_gmt)
}

static time_t date_difference_months_gmt(const date *p1, const date *p2)
{
    time_t days = date_difference_days_gmt(p1, p2);
    if (days == DIFF_FAILURE)
        return DIFF_FAILURE;
    int sign = 1;
    if (days < 0) {
        const date *temp = p1;
        p1 = p2;
        p2 = temp;
        sign = -1;
        days *= sign;
    }
    int year = const_access_date(p2) -> gmt_year;
    int i = const_access_date(p2) -> gmt_month - 1;
    month_days[1] = is_leap(year) ? 29 : 28;
    for (;days - month_days[i % 12] > 0;days -= month_days[i++ % 12])
        if (!(i % 11))
            month_days[1] = is_leap(++year) ? 29 : 28;
    return sign * (i - const_access_date(p2) -> gmt_month + 1);
}

static time_t date_difference_years_gmt(date *p1, date *p2)
{
    implement_difference_func(12, date_difference_months_gmt)
}

extern time_t date_difference_gmt(date *p1, date *p2, DATE_VALUE unit)
{
    switch (unit) {
        case YEARS: return date_difference_years_gmt(p1, p2);
        case MONTHS: return date_difference_months_gmt(p1, p2);
        case DAYS: return date_difference_days_gmt(p1, p2);
        case HOURS: return date_difference_hours_gmt(p1, p2);
        case MINUTES: return date_difference_minutes_gmt(p1, p2);
        case SECONDS: return date_difference_seconds_gmt(p1, p2);
        default: return DIFF_FAILURE;
    }
}

static time_t date_difference_seconds_local(const date *p1, const date *p2)
{
    time_t time_t_p1 = date_to_time_t_local(NULL, p1);
    time_t time_t_p2 = date_to_time_t_local(NULL, p2);
    if (time_t_p1 == CONV_FAILURE || time_t_p2 == CONV_FAILURE)
        return DIFF_FAILURE;
    return time_t_p1 - time_t_p2;
}

static time_t date_difference_hours_local(const date *p1, const date *p2)
{
    time_t difference = date_difference_seconds_local(p1, p2);
    if (difference == DIFF_FAILURE)
        return DIFF_FAILURE;
    return difference / SECONDS_IN_AN_HOUR;
}

static time_t date_difference_minutes_local(const date *p1, const date *p2)
{
    implement_difference_func(SECONDS_IN_A_MINUTE, date_difference_seconds_local)
}

static time_t date_difference_days_local(const date *p1, const date *p2)
{
    implement_difference_func(SECONDS_IN_A_DAY, date_difference_seconds_local);
}

static time_t date_difference_months_local(const date *p1, const date *p2)
{
    if (!check_date_by_ptr(p1))
        return DIFF_FAILURE;
    if (!check_date_by_ptr(p2))
        return DIFF_FAILURE;
    static date_core p1_localized;
    static date_core p2_localized;
    date p1_local = {.address = &p1_localized};
    date p2_local = {.address = &p2_localized};

    localize(&p1_local, p1);
    localize(&p2_local, p2);

    return date_difference_months_gmt(&p1_local, &p2_local);
}

static time_t date_difference_years_local(const date *p1, const date *p2)
{
    implement_difference_func(12, date_difference_months_local)
}

extern time_t date_difference_local(date *p1, date *p2, DATE_VALUE unit)
{
    switch (unit) {
        case YEARS: return date_difference_years_local(p1, p2);
        case MONTHS: return date_difference_months_local(p1, p2);
        case DAYS: return date_difference_days_local(p1, p2);
        case HOURS: return date_difference_hours_local(p1, p2);
        case MINUTES: return date_difference_minutes_local(p1, p2);
        case SECONDS: return date_difference_seconds_local(p1, p2);
        default: return DIFF_FAILURE;
    }
}






extern date *n_time_before_date(date *dest, const date *source, int n, const date *static_shared_object)
{
    if (!dest)
        dest = (date *)static_shared_object;
    if (!check_date_by_ptr(source))
        return NULL;
    time_t source_to_time = date_to_time_t_gmt(NULL, source);
    if (source_to_time == CONV_FAILURE)
        return NULL;
    return time_t_to_date_local(dest, source_to_time - n, const_access_date(source) -> utc);
}

extern date *n_seconds_before_date(date *dest, const date *source, int n)
{
    return n_time_before_date(dest, source, n, &n_seconds_before_obj);
}

extern date *n_seconds_after_date(date *dest, const date *source, int n)
{
    return n_time_before_date(dest, source, -n, &n_seconds_after_obj);
}

extern date *n_minutes_before_date(date *dest, const date *source, int n)
{
    return n_time_before_date(dest, source, n * SECONDS_IN_A_MINUTE, &n_minutes_before_obj);
}

extern date *n_minutes_after_date(date *dest, const date *source, int n)
{
    return n_time_before_date(dest, source, -n * SECONDS_IN_A_MINUTE, &n_minutes_after_obj);
}

extern date *n_hours_before_date(date *dest, const date *source, int n)
{
    return n_time_before_date(dest, source, n * SECONDS_IN_AN_HOUR, &n_hours_before_obj);
}

extern date *n_hours_after_date(date *dest, const date *source, int n)
{
    return n_time_before_date(dest, source, -n * SECONDS_IN_AN_HOUR, &n_hours_after_obj);
}

extern date *n_days_before_date(date *dest, const date *source, int n)
{
    return n_time_before_date(dest, source, n * SECONDS_IN_A_DAY, &n_days_before_obj);
}

extern date *n_days_after_date(date *dest, const date *source, int n)
{
    return n_time_before_date(dest, source, -n * SECONDS_IN_A_DAY, &n_days_after_obj);
}

extern date *n_months_before_date(date *dest, const date *source, int n)
{
    if (!dest)
        dest = &n_months_before_obj;
    int month = const_access_date(source) -> gmt_month;
    time_t source_to_time = date_to_time_t_gmt(NULL, source);
    for (int i = month;n > 0;source_to_time -= month_days[(12 * 10000 + i--) % 12] * SECONDS_IN_A_DAY, n--)
        ;
    return time_t_to_date_local(dest, source_to_time, const_access_date(source) -> utc);
}

extern date *n_months_after_date(date *dest, const date *source, int n)
{
    if (!dest)
        dest = &n_months_after_obj;
    int month = const_access_date(source) -> gmt_month;
    time_t source_to_time = date_to_time_t_gmt(NULL, source);
    for (int i = month;n > 0;source_to_time += month_days[i++ % 12] * SECONDS_IN_A_DAY, n--)
        ;
    return time_t_to_date_local(dest, source_to_time, const_access_date(source) -> utc);
}

extern date *n_years_before_date(date *dest, const date *source, int n)
{
    if (!dest)
        dest = &n_years_before_obj;
    return n_months_before_date(dest, source, n * 12);
}

extern date *n_years_after_date(date *dest, const date *source, int n)
{
    if (!dest)
        dest = &n_years_after_obj;
    return n_months_after_date(dest, source, n * 12);
}






extern int compare_dates_universal_time(const date *p1, const date *p2)
{
    time_t p1_to_time = date_to_time_t_gmt(NULL, p1);
    time_t p2_to_time = date_to_time_t_gmt(NULL, p2);
    if (p1_to_time == CONV_FAILURE || p2_to_time == CONV_FAILURE)
        return CMP_FAILURE;
    time_t cmp = date_to_time_t_gmt(NULL, p1) - date_to_time_t_gmt(NULL, p2);
    return cmp > 0 ? 1 : (cmp < 0 ? -1 : 0);
}

extern int compare_dates_local_time(const date *p1, const date *p2)
{
    time_t p1_to_time = date_to_time_t_gmt(NULL, p1);
    time_t p2_to_time = date_to_time_t_gmt(NULL, p2);
    if (p1_to_time == CONV_FAILURE || p2_to_time == CONV_FAILURE)
        return CMP_FAILURE;
    time_t cmp = date_to_time_t_local(NULL, p1) - date_to_time_t_local(NULL, p2);
    return cmp > 0 ? 1 : (cmp < 0 ? -1 : 0);
}






extern int assign_value(int *member, const char *end)
{
    char *value_end;
    int value = (int)strtol(end, &value_end, 10);
    if (end == value_end)
        return 1;
    *member = value;
    return 0;
}

extern date *str_to_date_gmt(date *dest, const char *source)
{
    size_t source_size = strlen(source) + 1;
    if (source_size > DATE_STR_SIZE)
        return NULL;
    if (!dest)
        dest = &str_to_date_obj;
    char source_copy[DATE_STR_SIZE] = {0};
    date_core *dest_accessed = access_date(dest);
    memcpy(source_copy, source, source_size);
    char *prev = source_copy;
    char *end = strtok(source_copy, " ");
    for (int i = 0;i < 7;i++) {
        if (!memcmp(end, weekday_names[i], 3)) {
            dest_accessed -> gmt_weekday = i;
            goto outside;
        }
    }

    return NULL;

    outside:
    end = strtok(NULL, " ");
    if (end == prev)
        return NULL;
    for (int i = 0;i < 12;i++) {
        if (!memcmp(end, month_names[i], 3)) {
            dest_accessed -> gmt_month = i + 1;
            goto out;
        }
    }

    return NULL;

    out:
    prev = end;
    end = strtok(NULL, " ");
    if (end == prev)
        return NULL;
    if (assign_value(&dest_accessed -> gmt_day, end))
        return NULL;
    end = strtok(end + strlen(end) + 1, ":");
    if (assign_value(&dest_accessed -> gmt_hour, end))
        return NULL;
    prev = end;
    end = strtok(NULL, ":");
    if (end == prev)
        return NULL;
    if (assign_value(&dest_accessed -> gmt_minute, end))
        return NULL;
    prev = end;
    end = strtok(NULL, ":");
    if (end == prev)
        return NULL;
    if (assign_value(&dest_accessed -> gmt_second, end))
        return NULL;
    prev = end;
    end = (strtok(end, " "), strtok(NULL, " "));
    if (end == prev)
        return NULL;
    if (assign_value(&dest_accessed -> gmt_year, end))
        return NULL;
    dest_accessed -> utc = 0;
    int weekday_calc = calculate_weekday(dest, DONT_ASSIGN);
    if (weekday_calc == WEEKDAY_CALC_FAILURE)
        return NULL;
    if (weekday_calc != dest_accessed -> gmt_weekday)
        return NULL;
    if (!check_date_by_ptr(dest))
        return NULL;
    normalize_date(dest);
    return dest;
}

extern date* str_to_date_local(date *dest, const char *source, int utc)
{
    void *str_to_date = str_to_date_gmt(dest, source);
    if (!str_to_date)
        return NULL;
    return n_hours_before_date(dest, dest, utc);
}

extern char *date_to_str_gmt(char *dest, const date *source)
{
    if (!dest)
        dest = date_to_str_str;
    if (!check_date_by_ptr(source))
        return NULL;
    const date_core *source_accessed = const_access_date(source);
    sprintf(dest, "%.3s %.3s %2d %.2d:%.2d:%.2d %.4d", weekday_names[source_accessed -> gmt_weekday],
            month_names[source_accessed -> gmt_month - 1], source_accessed -> gmt_day, source_accessed -> gmt_hour, source_accessed -> gmt_minute
            , source_accessed -> gmt_second, source_accessed -> gmt_year);
    return dest;
}

extern char *date_to_str_local(char *dest, const date *source)
{
    if (!dest)
        dest = date_to_str_str;
    if (!check_date_by_ptr(source))
        return NULL;
    if (!check_date_by_ptr(source))
        return NULL;
    const date_core *source_accessed = localize_and_access(NULL, source);
    sprintf(dest, "%.3s %.3s %2d %.2d:%.2d:%.2d %.4d", weekday_names[source_accessed -> gmt_weekday],
            month_names[source_accessed -> gmt_month - 1], source_accessed -> gmt_day, source_accessed -> gmt_hour, source_accessed -> gmt_minute
            , source_accessed -> gmt_second, source_accessed -> gmt_year);
    return dest;
}

extern int print_date_gmt(const date *p)
{
    if (!check_date_by_ptr(p))
        return EOF;
    puts(date_to_str_gmt(NULL, p));
    return 0;
}

extern int print_date_local(const date *p)
{
    if (!check_date_by_ptr(p))
        return EOF;
    puts(date_to_str_local(NULL, p));
    return 0;
}

extern int scan_date_local(date *p)
{
    char str[DATE_STR_SIZE] = {0};
    int scan_result_date = scanf("%[^\n]", str);
    if (scan_result_date == EOF || !scan_result_date)
        return EOF;
    printf("utc:");
    int utc;
    int scan_result_utc = scanf("%d", &utc);
    if (scan_result_utc == EOF || !scan_result_utc)
        return EOF;
    if(!str_to_date_local(p, str, utc))
        return EOF;
    return 0;
}

extern int scan_date_gmt(date *p)
{
    char str[DATE_STR_SIZE] = {0};
    int scan_result = scanf("%[^\n]", str);
    if (scan_result == EOF || !scan_result)
        return EOF;
    if(!str_to_date_gmt(p, str))
        return EOF;
    return 0;
}
