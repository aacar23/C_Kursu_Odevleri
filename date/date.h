#ifndef UNTITLED_DATE_H
#define UNTITLED_DATE_H

#include <time.h>
#include <limits.h>



#define STARTING_TIME_POINT (-2208988800)
#define ENDING_TIME_POINT (2145916800)

#define CONV_FAILURE (LONG_MIN)
#define CMP_FAILURE (-2)
#define DIFF_FAILURE (LONG_MAX)
#define GET_FAILURE (-1)

#define SECONDS_IN_A_COMMON_YEAR (365 * 24 * 60 * 60)
#define SECONDS_IN_A_LEAP_YEAR (366 * 24 * 60 * 60)
#define SECONDS_IN_A_DAY (24 * 60 * 60)
#define SECONDS_IN_AN_HOUR (60 * 60)
#define SECONDS_IN_A_MINUTE (60)

#define DATE_STR_SIZE (36)

typedef struct{
    void *address;
}date;


typedef enum {DAYS, MONTHS, YEARS, HOURS, MINUTES, SECONDS, WEEKDAY,NTH_DAY_OF_THE_YEAR_GMT, NTH_DAY_OF_THE_YEAR_LOCAL, UTC}DATE_VALUE;


extern void activate_date(date *p, int utc_val);
extern void deactivate_date(date *p);


extern date *normalize_date(date *p);


extern date *copy_date(date *dest, const date *source);


extern time_t date_to_time_t_local(time_t *dest, const date *source);
extern time_t date_to_time_t_gmt(time_t *dest, const date *source);
extern date *time_t_to_date_local(date *p, time_t local_time, int utc);
extern date *time_t_to_date_gmt(date *p, time_t gmt_time);


extern date *set_utc(date *p, int utc_val);
extern date *set_day(date *p, int day_value);
extern date *set_month(date *p, int month_value);
extern date *set_year(date *p, int year_value);
extern date *set_hour(date *p, int hour_value);
extern date *set_minute(date *p, int minute_value);
extern date *set_second(date *p, int second_value);
extern date *set_date(date *p, int day_value, int month_value, int year_value, int hour_value, int minute_value, int second_value, int utc_value);


extern int get_gmt_day(const date *p);
extern int get_gmt_month(const date *p);
extern int get_gmt_year(const date *p);
extern int get_gmt_hour(const date *p);
extern int get_gmt_minute(const date *p);
extern int get_gmt_second(const date *p);
extern int get_nth_day_of_the_year_gmt(const date *p);
extern int get_local_day(const date *p);
extern int get_local_month(const date *p);
extern int get_local_year(const date *p);
extern int get_local_hour(const date *p);
extern int get_local_minute(const date *p);
extern int get_local_second(const date *p);
extern int get_nth_day_of_the_year_local(const date *p);
extern int get_utc(const date *p);


extern time_t date_difference_gmt(date *p1, date *p2, DATE_VALUE unit);
extern time_t date_difference_local(date *p1, date *p2, DATE_VALUE unit);


extern date *n_seconds_before_date(date *dest, const date *source, int n);
extern date *n_seconds_after_date(date *dest, const date *source, int n);
extern date *n_minutes_before_date(date *dest, const date *source, int n);
extern date *n_minutes_after_date(date *dest, const date *source, int n);
extern date *n_hours_before_date(date *dest, const date *source, int n);
extern date *n_hours_after_date(date *dest, const date *source, int n);
extern date *n_days_before_date(date *dest, const date *source, int n);
extern date *n_days_after_date(date *dest, const date *source, int n);
extern date *n_months_before_date(date *dest, const date *source, int n);
extern date *n_months_after_date(date *dest, const date *source, int n);
extern date *n_years_before_date(date *dest, const date *source, int n);
extern date *n_years_after_date(date *dest, const date *source, int n);

extern int compare_dates_universal_time(const date *p1, const date *p2);
extern int compare_dates_local_time(const date *p1, const date *p2);

extern date *str_to_date_gmt(date *dest, const char *source);
extern date *str_to_date_local(date *dest, const char *source, int utc);
extern char *date_to_str_gmt(char *dest, const date *source);
extern char *date_to_str_local(char *dest, const date *source);
extern int print_date_gmt(const date *p);
extern int print_date_local(const date *p);
extern int scan_date_gmt(date *p);
extern int scan_date_local(date *p);

#endif
